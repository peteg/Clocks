# Licenced under CC0 v1.0
# https://creativecommons.org/publicdomain/zero/1.0/

# CC=clang-6.0
CC=gcc
CFLAGS+=-Wall -Wextra -pedantic
CFLAGS+=-std=c99
CFLAGS+=-O2
# CFLAGS+=-ggdb

CFLAGS+=-I../include

.PHONY: clean all

all: speak

words.o: ../words/words.c ../include/words.h ../include/allophones.h
	$(CC) $(CFLAGS) -c -o $@ $<

gpio.o: gpio.c gpio.h

speak.o: speak.c gpio.h sp0256.h ../include/allophones.h ../include/words.h

sp0256.o: sp0256.c gpio.h sp0256.h ../include/allophones.h ../include/words.h

speak: gpio.o speak.o sp0256.o words.o

clean:
	rm -f speak *.o
