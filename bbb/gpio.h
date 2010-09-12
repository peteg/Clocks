/*
 * BeagleBone Black GPIO: SYSFS and MMAP.
 *
 * based on https://github.com/chiragnagpal/beaglebone_mmap
 * see also http://www.righto.com/2016/08/the-beaglebones-io-pins-inside-software.html
 *
 * This version licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdbool.h>
#include <stdint.h>

/* SYSFS-based GPIO */

typedef unsigned int gpio_t;

enum dir { d_in, d_out };
enum edge { e_none = 0, e_rising = 1, e_falling = 2, e_both = 3 };

int gpio_export(gpio_t);
int gpio_unexport(gpio_t);
int gpio_set_dir(gpio_t, enum dir);
int gpio_read_value(gpio_t, bool *);
int gpio_write_value(gpio_t, bool);
int gpio_set_edge(gpio_t, enum edge);

int gpio_fd_open(gpio_t gpio, int flags);
int gpio_fd_read(int fd, bool *);
int gpio_fd_write(int fd, bool);
int gpio_fd_close(int fd);

/* MMAP-based GPIO */

struct mmap_gpio
{
  volatile uint8_t * volatile ptr;
  int fd;
};

static inline uint32_t *
gpio_oe(struct mmap_gpio *gpio) {
  return (uint32_t *)(gpio->ptr + 0x134);
}

static inline void
gpio_cleardataout(const struct mmap_gpio *gpio, uint32_t data) {
  *(uint32_t *)(gpio->ptr + 0x190) = data;
}

static inline void
gpio_setdataout(const struct mmap_gpio *gpio, uint32_t data) {
  *(uint32_t *)(gpio->ptr + 0x194) = data;
}

int gpio_mmap_open(struct mmap_gpio *h, unsigned int bank);
void gpio_mmap_close(struct mmap_gpio *h);

#endif /* _GPIO_H_ */
