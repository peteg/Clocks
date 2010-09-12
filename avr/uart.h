/*
 * UART driver for an ATMEGA328. Note the constant names are specific
 * to this chip (and perhaps other closely related ones).
 *
 * (C)opyright 2010, 2011 Peter Gammie, peteg42 at gmail dot com. All rights reserved.
 * Commenced September 2010.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

FIXME add TX queue.

 */

#ifndef _UART_H_
#define _UART_H_

#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

bool uart_rx(uint8_t *v);

/* Inlining this should be cheap. */
static inline void
uart_tx(uint8_t c)
{
  while(! (UCSR0A & _BV(UDRE0)))
      ;
  UDR0 = c;
}

void uart_tx_nl(void);
void uart_putstring(const char *str, bool nl);
void uart_putstringP(const char *str, bool nl);
void uart_putw_dec(uint16_t w);

/* FIXME debugging */
#define IF_DEBUG(x)  if(DEBUG) { x; }
#define uart_debug_putstringP(x) IF_DEBUG(uart_putstringP(x, true))

#endif /* _UART_H_ */
