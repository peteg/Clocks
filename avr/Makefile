# Target AVR.
MCU=atmega328p
PROGRAMMER_MCU=m328p
F_CPU=1000000UL

# Compiler
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
REMOVE=rm -f

#CFLAGS+=-O3
CFLAGS+=-Os
CFLAGS+=-std=c99 -pedantic
CFLAGS+=-mmcu=$(MCU) -DF_CPU=$(F_CPU)           \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -pedantic -Wstrict-prototypes     \
	-Wa,-ahlms=main.lst
#CFLAGS +=-g
CFLAGS+=-DDEBUG

# Linker
LDFLAGS=-Wl,-Map,main.map -mmcu=$(MCU) \
	-lm $(LIBS) \
	-Wa,-gstabs,-ahlms=main.lst

# Assembler
ASMFLAGS =-I. $(INC) -mmcu=$(MCU)        \
	-x assembler-with-cpp            \
	-Wa,-gstabs,-ahlms=main.lst

# Esterel. FIXME sorted circuit code generation, ANSI C.
ESTEREL=/home/peteg/bin/esterel
ESTEREL_FLAGS=-Lc:-ansi -W -single
ESTEREL_EXTRA_CFLAGS=-Wno-unused -Wno-strict-prototypes

# Hex
HEXFORMAT=ihex

# avrdude
AVRDUDE=avrdude
AVRDUDE_PROGRAMMERID=stk500v2
ARVDUDE_BAUD=115200
AVRDUDE_PORT=/dev/ttyUSB0

AVRDUDE_FLAGS=-c $(AVRDUDE_PROGRAMMERID) -b $(ARVDUDE_BAUD) -p $(PROGRAMMER_MCU) -P $(AVRDUDE_PORT)

# fuses, eek, avrdude does this so badly
HIGH=fuses_high
LOW=fuses_low

# Patterns

%.S: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -S $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

# Targets.

all: main.hex

controller.c: controller.strl
	$(ESTEREL) $(ESTEREL_FLAGS) controller.strl -B controller

commands.S: commands.c commands.h ds1307.h mma7660fc.h sp0256.h TWI.h uart.h

controller.o: controller.c
	$(CC) $(CFLAGS) $(ESTEREL_EXTRA_CFLAGS) -c $< -o $@

crc.S: crc8.c crc8.h

ds18x20.o: ds18x20.c crc8.h ds18x20.h onewire.h

main.S: main.c ../include/allophones.h ds1307.h mma7660fc.h sp0256.h TWI.h TWI_init.h uart.h uart_init.h

mma7660fc.S: mma7660fc.c mma7660fc.h TWI.h

onewire.S: onewire.c onewire.h

sp0256.S: sp0256.c sp0256.h

main.elf: main.o commands.o controller.o mma7660fc.o sp0256.o uart.o # crc8.o ds18x20.o onewire.o
	$(CC) $(LDFLAGS) $^ -o $@

main.hex: main.elf
	$(OBJCOPY) -j .text                    \
		-j .data                       \
		-O $(HEXFORMAT) $< $@

main.ee.hex: main.o
	$(OBJCOPY) -j .eeprom                  \
		--change-section-lma .eeprom=0 \
		-O $(HEXFORMAT) $< $@

main.s: main.o
	$(OBJDUMP) -S $< > $@

stats: main.o
	$(OBJDUMP) -h main.elf
	$(SIZE) main.o

hex: main.hex

writeflash: hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -e -U flash:w:main.hex

install: writeflash

reset:
	$(AVRDUDE) $(AVRDUDE_FLAGS)

read:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U hfuse:r:$(HIGH):b -U lfuse:r:$(LOW):b
	# Remember 0 means 'programmed'.
	cat $(HIGH) $(LOW)

clean:
	rm -f *.elf *.o *.s *.map *.hex *.lst *.S $(HIGH) $(LOW)
