/*
 * Top-level SP0256 driver for the Beaglebone Black.
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

/* localtime_r */
#define _POSIX_C_SOURCE 200112L
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

#include "sp0256.h"

static void
speak_temp_pressure(struct sp0256 *sp0256)
{
  const char bmp085_temp[] = "/sys/bus/i2c/drivers/bmp280/2-0077/iio:device0/in_temp_input";
  const char bmp085_pressure[] = "/sys/bus/i2c/drivers/bmp280/2-0077/iio:device0/in_pressure_input";
  FILE *f;
  int i, j;

  if((f = fopen(bmp085_temp, "r")) == NULL) {
    perror("speak_temp_pressure/temp");
    return;
  }

  fscanf(f, "%d", &i);
  fclose(f);

  /* Truncated to int16_t. The BMP085 does not yield negative temperatures. */
  printf("Temperature: %d\n", i);
  sp0256_temp(sp0256, i);

  /* The Linux bmp280 driver yields a strange format for the bmp085. Adjust for that here. */
  if((f = fopen(bmp085_pressure, "r")) == NULL) {
    perror("speak_temp_pressure/pressure");
    return;
  }

  fscanf(f, "%3d.%3d", &i, &j);
  fclose(f);

  i = 1000 * i + j;
  printf("Pressure: %d\n", i);

  sp0256_allophone(sp0256, aPA5);
  sp0256_pressure(sp0256, i);
}

static void
speak_time(struct sp0256 *sp0256)
{
  time_t current_time;
  struct tm tm;

  current_time = time(NULL);
  localtime_r(&current_time, &tm);
  sp0256_time(sp0256, tm);
}

int
main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  struct sp0256 sp0256;

  if(sp0256_init(&sp0256) < 0) {
    printf("** sp0256_init() failed.\n");
    exit(1);
  }

  /* sp0256_allophones(&sp0256, a_exterminate); */
  /* sp0256_allophone(&sp0256, aPA2); */
  /* sp0256_allophones(&sp0256, a_MHz); */

  speak_time(&sp0256);
  speak_temp_pressure(&sp0256);

  /* for(int i = 0; i < a_chars_len; i++) { */
  /*   sp0256_allophones(&sp0256, a_chars[i]); */
  /*   sp0256_allophone(&sp0256, aPA2); */
  /* } */

  sp0256_close(&sp0256);

  return 0;
}
