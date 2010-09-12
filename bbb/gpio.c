/*
 * BeagleBone Black GPIO: SYSFS and MMAP.
 *
 * based on https://github.com/chiragnagpal/beaglebone_mmap
 * see also http://www.righto.com/2016/08/the-beaglebones-io-pins-inside-software.html
 *
 * This version licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

/*

FIXME describe.
FIXME figure out return codes; follow UNIX if possible
FIXME use fopen or open uniformly

*/

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include <linux/limits.h>

#include "gpio.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_FILEPATH_LEN (PATH_MAX + NAME_MAX + 1)

/* SYSFS-based GPIO */

int
gpio_export(gpio_t gpio)
{
  FILE *f;

  /* Hack around a seeming bug in 4.14.71-ti-r79 by exporting first
     https://stackoverflow.com/questions/52125581/the-gpio-folder-is-deleted-when-the-same-gpio-is-exported-again */
  printf("Exporting gpio%d ... first ", gpio);
  gpio_unexport(gpio);

  printf("Exporting gpio%d\n", gpio);

  if((f = fopen(SYSFS_GPIO_DIR "/export", "w")) == NULL) {
    perror("gpio_export");
    return -1;
  }

  if(fprintf(f, "%d", gpio) < 0) {
    perror("gpio_export");
    return -1;
  }

  fclose(f);
  return 0;
}

int
gpio_unexport(gpio_t gpio)
{
  FILE *f;

  printf("Unexporting gpio%d\n", gpio);

  if((f = fopen(SYSFS_GPIO_DIR "/unexport", "w")) == NULL) {
    perror("gpio_unexport");
    return -1;
  }

  if(fprintf(f, "%d", gpio) < 0) {
    perror("gpio_unexport");
    return -1;
  }

  fclose(f);
  return 0;
}

int
gpio_set_dir(gpio_t gpio, enum dir dir)
{
  int fd;
  char buf[MAX_FILEPATH_LEN];
  const char *dirs[] = { "in", "out" };
  int rv;
  int len;

  printf("Setting direction of gpio%d to '%s'\n", gpio, dirs[dir]);

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
  if((fd = open(buf, O_WRONLY)) < 0) {
    perror("gpio_set_dir");
    return fd;
  }

  len = strlen(dirs[dir]) + 1;
  rv = write(fd, dirs[dir], len);
  close(fd);

  return rv == len ? 0 : -1;
}

int
gpio_read_value(gpio_t gpio, bool *value)
{
  int fd;
  int rv;

  if((fd = gpio_fd_open(gpio, O_RDONLY)) < 0) {
    perror("gpio_read_value");
    return -1;
  }

  rv = gpio_fd_read(fd, value);
  close(fd);

  return rv < 0 ? -1 : 0;
}

int
gpio_write_value(gpio_t gpio, bool value)
{
  int fd;
  int rv;

  if((fd = gpio_fd_open(gpio, O_RDONLY)) < 0) {
    perror("gpio_write_value");
    return -1;
  }

  rv = gpio_fd_write(fd, value ? "1" : "0");
  close(fd);

  return rv < 0 ? -1 : 0;
}

int
gpio_set_edge(gpio_t gpio, enum edge edge)
{
  int fd;
  char buf[MAX_FILEPATH_LEN];
  const char *edges[] = { "none", "rising", "falling", "both" };
  int len;
  int rv;

  printf("Setting edge of gpio%d to '%s'\n", gpio, edges[edge]);

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

  if((fd = open(buf, O_WRONLY)) < 0) {
    perror("gpio_set_edge");
    return -1;
  }

  len = strlen(edges[edge]) + 1;
  rv = write(fd, edges[edge], len);
  close(fd);

  return rv == len ? 0 : -1;
}

int
gpio_fd_open(gpio_t gpio, int flags)
{
  int fd;
  char buf[MAX_FILEPATH_LEN];

  printf("Opening gpio%d with flags %d\n", gpio, flags);

  snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

  if((fd = open(buf, flags | O_NONBLOCK)) < 0) {
    perror("gpio_fd_open");
  }

  return fd;
}

int
gpio_fd_close(int fd)
{
  return close(fd);
}

int
gpio_fd_read(int fd, bool *value)
{
  char ch;

  if(read(fd, &ch, 1) != 1) {
    perror("gpio_fd_read()");
    return -1;
  } else {
    *value = ch != '0' ? 1 : 0;
    return 0;
  }
}

int
gpio_fd_write(int fd, bool value)
{
  if(write(fd, value ? "1" : "0", 2) < 0) {
    perror("gpio_fd_write()");
    return -1;
  } else {
    return 0;
  }
}

/* **************************************** */
/* MMAP-based GPIO */

static const unsigned int gpio_bank_size = 0xFFF; // FIXME type?

// FIXME note bank, maybe cache?
// FIXME check mmap_gpio is OK
// FIXME return meaningful values
int
gpio_mmap_open(struct mmap_gpio *h, unsigned int bank)
{
  static const off_t gpio_bank_start[] =
    { 0x44E07000, 0x4804C000, 0x481AC000, 0x481AE000 };

  if(!(bank < 4)) {
    printf("FIXME bank arg invalid\n");
    return -1;
  }

  printf("Opening /dev/mem\n");

  if((h->fd = open("/dev/mem", O_RDWR)) < 0) {
    perror("gpio_mmap_open");
    return -1;
  }

  printf("Mapping GPIO%d address %X (size: %X)\n", bank, (unsigned int)gpio_bank_start[bank], gpio_bank_size);

  if((h->ptr = mmap(0, gpio_bank_size, PROT_READ | PROT_WRITE, MAP_SHARED, h->fd, gpio_bank_start[bank])) == MAP_FAILED) {
    perror("gpio_mmap_open");
    return -1;
  }

  return 0;
}

void
gpio_mmap_close(struct mmap_gpio *h)
{
  close(h->fd);
}
