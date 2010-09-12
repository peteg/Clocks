/*
 * Simple SP0256 driver.
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#include <stdint.h>

// FIXME cli/sei experiment
#include <avr/interrupt.h>

#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "sp0256.h"
#include "allophones.h"

void
speak_allophone(allophone_t allophone)
{
  /* Load allophone, holding ALD high. */
  /* FIXME adhoc shift here, abstract that too. */
  SP0256_DATA = (allophone & 0x3F) << 2;
  SP0256_CTRL |= SP0256_ALD;

  // Take ALD low for at least 1.1us, overkill.
  // _delay_ms(1);
  SP0256_CTRL &= ~SP0256_ALD;
  _delay_ms(1);
  // _delay_loop_1(); FIXME 3 cycles per loop.
  SP0256_CTRL |= SP0256_ALD;

  // Wait for the chip to finish.
  // FIXME an interrupt might be the go here.
  while(! (SP0256_CTRL_IN & SP0256_SBY)) {
  }
}
