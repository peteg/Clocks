/*
 * Command interpreter.
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#include "sp0256.h"
#include "ds1307.h"
#include "mma7660fc.h"
#include "uart.h"

#include "commands.h"

/*
 * The Esterel controller should guarantee single-threadedness, so we
 * can use cheesy global state here.
 */

/* **************************************** */
/* Debugging */

void
speak_the_time(void)
{
  struct ds1307_time_t t;

  if(ds1307_read(&t)) {
    uart_putstringP(PSTR("The time is "), false);
    uart_putw_dec(t.hours);
    uart_putstringP(PSTR(" hours "), false);
    uart_putw_dec(t.minutes);
    uart_putstringP(PSTR(" minutes "), false);
    uart_putw_dec(t.seconds);
    uart_putstringP(PSTR(" seconds"), true);

    speak_P(the);
    speak_P(time);
    speak_P(is);
    // FIXME pluralisation
    speak_number(t.hours);
    speak_P(hours);
    speak_number(t.minutes);
    speak_P(minutes);
    speak_number(t.seconds);
    speak_P(seconds);
  } else {
    uart_debug_putstringP(PSTR("** ds1307 read failure"));
    speak_P(time);
    speak_P(clown);
  }
}

static void
speak_acc_reading(void)
{
  int8_t x, y, z;

  if(mma7660fc_read_axes(&x, &y, &z)) {
    uart_putstringP(PSTR("Acc read successful."), true);
    uart_putw_dec(x);
    uart_putstringP(PSTR(""), true);
    uart_putw_dec(y);
    uart_putstringP(PSTR(""), true);
    uart_putw_dec(z);
    uart_putstringP(PSTR(""), true);
    uart_putstringP(PSTR("***"), true);

    speak_P(sensors);
    speak_number(x);
    speak_number(y);
    speak_number(z);
  } else {
    uart_putstringP(PSTR("*** Acc read failed."), true);
    speak_P(sensors);
    speak_P(clown);
  }
}

/* FIXME quick hack */
static bool
speak_acc_orientation(void)
{
  static mma7660fc_tilt_orientation_t o_old;
  mma7660fc_tilt_orientation_t o;
  mma7660fc_tilt_back_front_t bf;

  if(mma7660fc_read_tilt(&o, &bf)) {
    if(o != o_old) {
      switch(o) {
      case MMA7660FC_tilt_left:
        uart_debug_putstringP(PSTR("** acc left"));
        speak_P(left);
        break;
      case MMA7660FC_tilt_right:
        uart_debug_putstringP(PSTR("** acc right"));
        speak_P(right);
        break;
      case MMA7660FC_tilt_down:
        uart_debug_putstringP(PSTR("** acc down"));
        speak_P(down);
        break;
      case MMA7660FC_tilt_up:
        uart_debug_putstringP(PSTR("** acc up"));
        speak_P(up);
        break;
      }

      o_old = o;

      return true;
    } else {
      uart_debug_putstringP(PSTR("** orientation hasn't changed"));
    }
  } else {
    uart_putstringP(PSTR("*** Acc read failed."), true);
    speak_P(sensors);
    speak_P(clown);
  }

  return false;
}

static void
dump_acc_registers(void)
{
  uint8_t twsr;
  uint8_t t;

  TWI_start(MMA7660FC_ADDR, &twsr, WRITE);
  TWI_write(&twsr, 0x0);
  TWI_rep_start(MMA7660FC_ADDR, &twsr, READ);

  for(uint8_t i = 0; i <= 0x0A; i++) {
    TWI_read(&twsr, &t, true);
    uart_putw_dec(t);
    uart_tx_nl();
  }

  TWI_read(&twsr, &t, false);
  TWI_send_stop(&twsr);
}

/* **************************************** */

void
handle_accelerometer_event(void)
{
  uart_debug_putstringP(PSTR("handle_accelerometer_event()"));

  // FIXME probably not necessary
  // mma7660fc_clear_interrupt();

  /* FIXME debugging */
  sp0256_turn_on();
  dump_acc_registers();
  if(speak_acc_orientation()) {
    speak_the_time();
  }
  sp0256_turn_off();

  uart_debug_putstringP(PSTR("handle_accelerometer_event() finished"));
}

/* **************************************** */

static void
process_command(char *cmd)
{
  // FIXME
}

/* **************************************** */
/* Buffer commands coming in on the serial port. FIXME is this more or
   less efficient that giving each character to a state machine? */

#define COMMAND_BUFFER_SIZE 80

static char command_buffer[COMMAND_BUFFER_SIZE];
static uint8_t command_buffer_index = 0;

void
handle_uart_reset(void)
{
  uart_debug_putstringP(PSTR("handle_uart_reset()"));
  command_buffer_index = 0;
}

void
handle_uart_event(void)
{
  uint8_t c;

  uart_debug_putstringP(PSTR("handle_uart_event()"));

  /* Wait for a character to be received. */
  while(!uart_rx(&c))
    ;

  /* Treat each of the buffered characters. */
  do {
    command_buffer[command_buffer_index] = c;
    command_buffer_index++;

    uart_debug_putstringP(PSTR("handle_uart_event(): got character"));

    // FIXME newline, allow room for a \0
    if(c == 0x0A || c == 0x0D || command_buffer_index == COMMAND_BUFFER_SIZE - 1) {
      uart_debug_putstringP(PSTR("handle_uart_event(): processing command"));
      command_buffer[command_buffer_index] = '\0';
      uart_putstring(command_buffer, true);

      for(int i = 0; i < command_buffer_index; i++) {
        uart_tx(command_buffer[i]);
      }
      uart_tx_nl();

      process_command(command_buffer);

      command_buffer_index = 0;

      /* FIXME debugging */
      sp0256_turn_on();
      // speak_acc_reading();
      dump_acc_registers();
      speak_the_time();
      sp0256_turn_off();
    }
  } while(uart_rx(&c));

  uart_debug_putstringP(PSTR("handle_uart_event() finished"));
}
