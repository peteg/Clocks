Licence
-------

This is some code for a simple talking clock and thermometer.

All original code is placed in the public domain as much as possible
using the CC0 v1.0 licence (see COPYING) and:

https://creativecommons.org/publicdomain/zero/1.0/

See the individual source files for details of code reused from
others.

The DS18B20 code is due to Martin Thomas and others:

http://www.siwawi.arubi.uni-kl.de/avr_projects/tempsensor/index.html

Related recent effort:

http://hackaday.com/2017/02/22/microvox-puts-the-80s-back-into-your-computers-voice/

To Do
-----

Hardware:
 - switch off the sp0256 when we're not talking
 - backup battery for the time
 - check accuracy and current draw

Serial port interface. Commands:
 - speak these allophones
 - set the time/date/alarm/...
 - arduino bootloader?

Bugs
====

- uart_debug_putstringP sometimes seems to drop things.
 - I thought uart_tx does enough synchronisation, i.e. we wait for the
   buffer to be ready.
- rename commands -> events and move more stuff in there
- shuffle more stuff out of headers into c files

Hardware
--------

The hardware I used is as follows.

* A Beaglebone Black, for ease of hacking.
* An AVR ATmega328P processor.
* A DS1307 TWI/I2C real-time clock.
* A DS18B20 1-wire temperature sensor.
* An SP0256 speech synthesiser.
* A MMA7660FC accelerometer.

The circuitry is completely stock. The connections between the AVR and
the other chips can be easily inferred from the source code.

I ran most of the circuit from 4 NiMH AAs, which yield 5v. The options
are limited as both the DS1307 and the SP0256 need 5v to function.

MMA7660FC
=========

I bought one mounted on a breakout board from http://madscientisthut.com/

I used a couple of FETs to do I2C/TWI level conversion between the 5v
used by the AVR and the 3v (approx) for the MMA7660FC. See
http://www.sparkfun.com/tutorials/65

The interrupt pin of the MMA7660FC can be directly connected to a GPIO
on the AVR. Be careful not to set that pin as an output though!

Software
--------

Beaglebone Black
================

AVR
===

Watch Dog Timer
~~~~~~~~~~~~~~~

Used to generate an interrupt every 8s (approx). It isn't used to
reset the system, so we don't want the WDTON fuse to be set.

Originally I used the 1Hz oscillator on the DS1307 RTC, but it
requires a pull-up resistor and hence consumes more power.

    /* 1Hz tick from the RTC - PC2 - PCINT10 - PCI1. */
    /* Pull-up the RTC interrupt pin and listen for Pin Change interrupts. */
    PORTC |= _BV(PC2);
    PCMSK1 |= _BV(PCINT10);
    PCICR |= _BV(PCIE1);

Constants in program memory
~~~~~~~~~~~~~~~~~~~~~~~~~~~

All string constants and allophone data live in program memory.
