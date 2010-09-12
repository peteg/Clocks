/*
 * Simple SP0256 driver.
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef _SP0256_H_
#define _SP0256_H_

#include <stdint.h>

#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

/* **************************************** */
/* Port connections. */

#define SP0256_ENABLE (_BV(PB1))
#define SP0256_ALD    (_BV(PB0))
#define SP0256_RESET  (_BV(PB7))
#define SP0256_SBY    (_BV(PB6))

#define SP0256_CTRL     PORTB
#define SP0256_CTRL_IN  PINB
#define SP0256_CTRL_DDR DDRB

#define SP0256_DATA     PORTD
#define SP0256_DATA_DDR DDRD

/* **************************************** */

static inline void
sp0256_turn_on(void)
{
  /* Turn the SP0256 on. */
  SP0256_CTRL |= SP0256_ENABLE;
  _delay_ms(1);

  /* Reset must be held low for at least 100ns, here 1ms, overkill. */
  PORTB |= SP0256_RESET;
  _delay_ms(1);
  PORTB &= ~SP0256_RESET;
  _delay_ms(1);
  // _delay_loop_1(); FIXME 3 cycles per loop.
  PORTB |= SP0256_RESET;
}

static inline void
sp0256_turn_off(void)
{
  SP0256_CTRL &= ~SP0256_ENABLE;
}

static inline void
sp0256_init(void)
{
  // Port D:
  //   D2 - D7 data
  SP0256_DATA = 0x0;
  SP0256_DATA_DDR = 0xFC;

  // Port B:
  //   B0: ALD, active-low (address load)
  //   B1: power switch
  //   B6: SBY, active high (standby, chip idle, input)
  //   B7: RESET, active low.
  SP0256_CTRL = 0x0;
  SP0256_CTRL_DDR &= SP0256_SBY;
  SP0256_CTRL_DDR |= SP0256_ALD | SP0256_RESET | SP0256_ENABLE;
}

#endif /* _SP0256_H_ */
