/*
 * SP0256 driver via the BeagleBone Black's GPIO.
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef _SP0256_H_
#define _SP0256_H_

#include <stdint.h>

#include "gpio.h"
#include "words.h"

struct sp0256 {
  struct mmap_gpio gpio;
  int fd;
};

int sp0256_init(struct sp0256 *);
void sp0256_close(struct sp0256 *);

#endif /* _SP0256_H_ */
