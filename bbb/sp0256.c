/*
 * SP0256 driver via the BeagleBone Black's GPIO.
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

/* nanosleep */
#define _POSIX_C_SOURCE 200112L
#include <time.h>

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/select.h>

#include "allophones.h"
#include "gpio.h"
#include "sp0256.h"

/*
SP0256 inputs / BBB outputs
GPIO3 14-19, 20, 21
gpio110 - gpio115, gpio116, gpio117
*/
#define SP0256_DATA(x) (((uint8_t)x & 0x3F) << 14)
#define SP0256_ALD (1<<20) /* active low */
#define SP0256_RESET (1<<21) /* active low */

#define OUTPUT_PINS (SP0256_DATA(0xFF) | SP0256_ALD | SP0256_RESET)

/* SP0256 outputs / BBB inputs. Use SYSFS so we can block on it. */
/* P9_26 = GPIO0[14] = /sys/class/gpio/gpio14 */
#define SP0256_LRQ_GPIO 14 /* active high */

int
sp0256_init(struct sp0256 *sp0256)
{
  uint32_t reg;
  struct timespec ts;

  if(gpio_mmap_open(&sp0256->gpio, 3) < 0) {
    return -1;
  }

  if(gpio_export(SP0256_LRQ_GPIO) < 0) {
    return -1;
  }
  if(gpio_set_dir(SP0256_LRQ_GPIO, d_in) < 0) {
    return -1;
  }
  if(gpio_set_edge(SP0256_LRQ_GPIO, e_falling) < 0) {
    return -1;
  }
  if((sp0256->fd = gpio_fd_open(SP0256_LRQ_GPIO, O_RDONLY)) < 0) {
    return -1;
  }

  reg = *gpio_oe(&sp0256->gpio);
  printf("GPIO configuration before: %X\n", reg);
  reg = reg & (~(uint32_t)OUTPUT_PINS);
  *gpio_oe(&sp0256->gpio) = reg;
  printf("GPIO configuration after:  %X\n", *gpio_oe(&sp0256->gpio));

  /* Initialize: ALD high, reset for 100us */

  gpio_setdataout(&sp0256->gpio, SP0256_ALD);
  gpio_cleardataout(&sp0256->gpio, SP0256_RESET);
  ts.tv_sec = 0;
  ts.tv_nsec = 1000000; // FIXME 1ms
  nanosleep(&ts, NULL); // FIXME handle rem
  gpio_setdataout(&sp0256->gpio, SP0256_RESET);

  return 0;
}

void
sp0256_close(struct sp0256 *sp0256)
{
  gpio_mmap_close(&sp0256->gpio);
  close(sp0256->fd);
}

void
sp0256_allophone(const struct sp0256 *sp0256, allophone_t allophone)
{
  struct timespec ts;
  int rv;
  int nfds;
  fd_set rd, wr, er;
  struct timeval utimeout;

  /* Wait for the LRQ line to go low */
  while(1) {
    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&er);
    FD_SET(sp0256->fd, &er); // FIXME event or read?
    nfds = sp0256->fd;

    // FIXME arbitrary timeout
    utimeout.tv_sec = 5000;
    utimeout.tv_usec = 500000;

    if((rv = select(nfds + 1, &rd, &wr, &er, &utimeout)) < 0) {
      if(errno == EINTR) {
        continue;
      } else {
        perror("sp0256_allophone()/select()");
        exit(EXIT_FAILURE); // FIXME return 0 ?
      }
    }

    if(rv > 0 && FD_ISSET(sp0256->fd, &er)) {
      // FIXME need to clear the event somehow.
      bool v = false;
      lseek(sp0256->fd, 0, SEEK_SET);
      gpio_fd_read(sp0256->fd, &v); // FIXME handle errors
      /* printf("Got LRD event, value: %d\n", v); */

      // FIXME Set data, set ALD low, set ALD high
      gpio_setdataout(&sp0256->gpio, SP0256_DATA(allophone));
      gpio_cleardataout(&sp0256->gpio, SP0256_DATA(~allophone));
      ts.tv_sec = 0;
      ts.tv_nsec = 100;
      nanosleep(&ts, NULL); // FIXME handle rem
      gpio_cleardataout(&sp0256->gpio, SP0256_ALD);
      ts.tv_sec = 0;
      ts.tv_nsec = 1000; // 200 - 1100ns
      nanosleep(&ts, NULL); // FIXME handle rem
      gpio_setdataout(&sp0256->gpio, SP0256_ALD);
      break;
    }
  }
}
