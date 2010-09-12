/*
 * Words as SP0256 allophones.
 *
 * Lifted from various sources:
 *  - the Radio Shack SP0256 data sheet
 *  - the Talking Electronics #15 "Speech Module" article
 *  - ...
 *
 * Licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "words.h"

/* **************************************** */
/* Pauses. */

const allophone_t a_PA1[] = { 0x00, aEND }; // before BB,DD,GG,JH (10 msec)
const allophone_t a_PA2[] = { 0x01, aEND }; // before BB,DD,GG,JH (30 msec)
const allophone_t a_PA3[] = { 0x02, aEND }; // before PP,TT,KK,CH and between words (50 msec)
const allophone_t a_PA4[] = { 0x03, aEND }; // between clauses and sentences (100 msec)
const allophone_t a_PA5[] = { 0x04, aEND }; // between clauses and sentences (200 msec)

// FIXME perhaps a function: silence(ms)

/* **************************************** */
/* Letters. */

static const allophone_t a_char_A[] = { aEY, aEND };
static const allophone_t a_char_B[] = { aBB2, aIY, aEND };
static const allophone_t a_char_C[] = { aSS, aSS, aIY, aEND };
static const allophone_t a_char_D[] = { aDD2, aIY, aEND };
static const allophone_t a_char_E[] = { aIY, aEND };
static const allophone_t a_char_F[] = { aEH, aEH, aFF, aFF, aEND };
static const allophone_t a_char_G[] = { aJH, aIY, aEND };
static const allophone_t a_char_H[] = { aEY, aPA2, aPA3, aCH, aEND };
static const allophone_t a_char_I[] = { aAA, aAY, aEND };
static const allophone_t a_char_J[] = { aJH, aEH, aEY, aEND };
static const allophone_t a_char_K[] = { aKK1, aEH, aEY, aEND };
static const allophone_t a_char_L[] = { aEH, aEH, aEL, aEND };
static const allophone_t a_char_M[] = { aEH, aEH, aMM, aEND };
static const allophone_t a_char_N[] = { aEH, aEH, aNN1, aEND };
static const allophone_t a_char_O[] = { aOW, aEND };
static const allophone_t a_char_P[] = { aPP, aIY, aEND };
static const allophone_t a_char_Q[] = { aKK1, aYY1, aUW2, aEND };
static const allophone_t a_char_R[] = { aAR, aEND };
static const allophone_t a_char_S[] = { aEH, aEH, aSS, aSS, aEND };
static const allophone_t a_char_T[] = { aTT2, aIY, aEND };
static const allophone_t a_char_U[] = { aYY1, aUW2, aEND };
static const allophone_t a_char_V[] = { aVV, aIY, aEND };
static const allophone_t a_char_W[] = { aDD2, aAX, aPA2, aBB2, aEL, aYY1, aUW2, aEND };
static const allophone_t a_char_X[] = { aEH, aEH, aPA3, aKK2, aSS, aSS, aEND };
static const allophone_t a_char_Y[] = { aWW, aAY, aEND };
static const allophone_t a_char_Z[] = { aZZ, aEH, aPA3, aDD1, aEND };

const allophone_t * const
a_chars[] = {
  a_char_A, a_char_B, a_char_C, a_char_D, a_char_E, a_char_F,
  a_char_G, a_char_H, a_char_I, a_char_J, a_char_K, a_char_L,
  a_char_M, a_char_N, a_char_O, a_char_P, a_char_Q, a_char_R,
  a_char_S, a_char_T, a_char_U, a_char_V, a_char_W, a_char_X,
  a_char_Y, a_char_Z
};

/* **************************************** */
/* Words. */

const allophone_t a_AM[] = { aEY, aEH, aEH, aMM, aEND };
const allophone_t a_Hertz[] = { aHH2, aHH2, aER2, aTT1, aZZ, aEND };
const allophone_t a_PM[]  = { aPP, aIY, aPA4, aEH, aEH, aMM, aEND };
const allophone_t a_alarm[] = { aAX, aLL, aAR, aMM, aEND };
const allophone_t a_all[] = { aAO, aAO, aLL, aEND };
const allophone_t a_am[] = { aAE, aMM, aEND };
const allophone_t a_amateur[] = { aAE, aMM, aAE, aTT1, aYY1, aER1, aEND };
const allophone_t a_an[] = { aAE, aNN1, aEND };
const allophone_t a_and[]  = { aAE, aNN1, aDD1, aEND };
const allophone_t a_are[] = { aAR, aEND };
const allophone_t a_at[] = { aAE, aTT2, aEND };
const allophone_t a_baby[] = { aPA2, aBB2, aEY, aPA2, aBB2, aIY, aEND };
const allophone_t a_bathe[] = { aBB2, aEY, aDH2, aEND };
const allophone_t a_bather[] = { aBB2, aEY, aDH2, aER1, aEND };
const allophone_t a_bathing[] = { aBB2, aEY, aDH2, aIH, aNG, aEND };
const allophone_t a_be[] = { aBB2, aIY, aEND };
const allophone_t a_beer[] = { aBB2, aYR, aEND };
const allophone_t a_birthday[] = { aPA2, aBB2, aER1, aTH, aPA2, aDD2, aEH, aEY, aEND };
const allophone_t a_bite[] = { aPA2, aBB2, aAY, aPA4, aTT1, aEND };
const allophone_t a_blank[] = { aPA2, aBB2, aLL, aAE, aNN1, aPA3, aKK2, aEND };
const allophone_t a_bread[] = { aBB1, aRR2, aEH, aEH, aPA1, aDD1, aEND };
const allophone_t a_brother[] = { aPA2, aBB2, aRR2, aAX, aTH, aER1, aEND };
const allophone_t a_by[] = { aBB2, aAA, aAY, aEND };
const allophone_t a_byte[] = { aPA2, aBB2, aAY, aPA4, aTT1, aEND };
const allophone_t a_bytes[] = { aPA2, aBB2, aAY, aPA4, aTT1, aZZ, aEND };
const allophone_t a_calendar[] = { aKK1, aAE, aAE, aLL, aEH, aNN1, aPA2, aDD2, aEND };
const allophone_t a_calling[] = { aKK3, aAO, aEL, aLL, aIH, aNG, aEND };
const allophone_t a_cat[] = { aKK1, aAE, aPA3, aTT2, aEND };
const allophone_t a_check[] = { aCH, aEH, aEH, aPA3, aKK2, aEND };
const allophone_t a_checked[] = { aCH, aEH, aEH, aPA3, aKK2, aTT2, aEND };
const allophone_t a_checker[] = { aCH, aEH, aEH, aPA3, aKK1, aER1, aEND };
const allophone_t a_checkers[] = { aCH, aEH, aEH, aPA3, aKK1, aER1, aZZ, aEND };
const allophone_t a_checking[] = { aCH, aEH, aEH, aPA3, aKK1, aIH, aNG, aEND };
const allophone_t a_checks[] = { aCH, aEH, aEH, aPA3, aKK1, aSS, aEND };
const allophone_t a_clock[] = { aKK1, aLL, aAA, aAA, aPA3, aKK2, aEND };
const allophone_t a_close[] = { aKK1, aLL, aOW, aSS, aSS, aEND };
const allophone_t a_clown[] = { aKK1, aLL, aAW, aNN1, aEND };
const allophone_t a_cognitive[] = { aKK3, aAA, aAA, aGG3, aNN1, aIH, aPA3, aTT2, aIH, aVV, aEND };
const allophone_t a_collide[] = { aKK3, aAX, aLL, aAY, aDH2, aEND };
const allophone_t a_computer[] = { aKK1, aAX, aMM, aPA1, aYY1, aUW1, aTT2, aER1, aEND };
const allophone_t a_cookie[] = { aKK3, aUH, aKK1, aIY, aEND };
const allophone_t a_coop[] = { aKK3, aUW2, aPA3, aPP, aEND };
const allophone_t a_correct[] = { aKK1, aER2, aEH, aEH, aPA2, aKK2, aPA2, aTT1, aEND };
const allophone_t a_corrected[] = { aKK1, aER2, aEH, aEH, aPA2, aKK2, aPA2, aTT2, aIH, aPA2, aDD1, aEND };
const allophone_t a_correcting[] = { aKK1, aER2, aEH, aEH, aPA2, aKK2, aPA2, aTT2, aIH, aNG, aEND };
const allophone_t a_corrects[] = { aKK1, aER2, aEH, aEH, aPA2, aKK2, aPA2, aTT1, aSS, aEND };
const allophone_t a_crane[] = { aKK3, aRR2, aEY, aNN1, aEND };
const allophone_t a_crown[] = { aKK1, aRR2, aAW, aNN1, aEND };
const allophone_t a_data[] = { aDD2, aAA, aAA, aPA2, aTT1, aER1, aEND };
const allophone_t a_date[] = { aDD2, aEY, aPA3, aTT2, aEND };
const allophone_t a_daughter[] = { aDD2, aAO, aTT2, aER1, aEND };
const allophone_t a_day[] = { aPA2, aDD2, aEY, aEND };
const allophone_t a_degrees[] = { aDD2, aIY, aGG1, aRR1, aIY, aZZ, aEND };
const allophone_t a_disk[] = { aDD2, aIH, aSS, aSS, aKK2, aEND };
const allophone_t a_divided[] = { aDD2, aIH, aVV, aAY, aPA2, aDD2, aIH, aPA2, aDD1, aEND };
const allophone_t a_do[] = { aPA4, aDD2, aUW1, aUW2, aEND };
const allophone_t a_down[] = { aDD2, aAW, aNN1, aEND }; // FIXME rough
const allophone_t a_drive[] = { aDD2, aRR2, aAY, aDH2, aEND };
const allophone_t a_drives[] = { aDD2, aRR2, aAY, aDH2, aZZ, aEND };
const allophone_t a_east[] = { aIY, aSS, aTT1, aEND };
const allophone_t a_emergency[] = { aIY, aMM, aER1, aJH, aEH, aNN1, aSS, aIY, aEND };
const allophone_t a_emotional[] = { aIY, aMM, aOW, aSH, aAX, aNN1, aAX, aEL, aEND };
const allophone_t a_engage[] = { aEH, aEH, aPA1, aNN1, aGG1, aEY, aPA2, aJH, aEND };
const allophone_t a_engagement[] = { aEH, aEH, aPA1, aNN1, aGG1, aEY, aPA2, aJH, aMM, aEH, aEH, aNN1, aPA2, aPA3, aTT2, aEND };
const allophone_t a_engages[] = { aEH, aEH, aPA1, aNN1, aGG1, aEY, aPA2, aJH, aIH, aZZ, aEND };
const allophone_t a_engaging[] = { aEH, aEH, aPA1, aNN1, aGG1, aEY, aPA2, aJH, aIH, aNG, aEND };
const allophone_t a_enrage[] = { aEH, aNN1, aRR1, aEY, aPA2, aJH, aEND };
const allophone_t a_enraged[] = { aEH, aNN1, aRR1, aEY, aPA2, aJH, aPA2, aDD1, aEND };
const allophone_t a_enrages[] = { aEH, aNN1, aRR1, aEY, aPA2, aJH, aIH, aZZ, aEND };
const allophone_t a_enraging[] = { aEH, aNN1, aRR1, aEY, aPA2, aJH, aIH, aNG, aEND };
const allophone_t a_equal[] = { aIY, aPA2, aPA3, aKK3, aWH, aAX, aEL, aEND };
const allophone_t a_equals[] = { aIY, aPA2, aPA3, aKK3, aWH, aAX, aEL, aZZ, aEND };
const allophone_t a_error[] = { aEH, aEH, aRR2, aPA1, aER1, aEND };
const allophone_t a_escape[] = { aEH, aSS, aSS, aPA3, aKK1, aPA2, aPA3, aPP, aEND };
const allophone_t a_escaped[] = { aEH, aSS, aSS, aPA3, aKK1, aPA2, aPA3, aPP, aPA2, aTT2, aEND };
const allophone_t a_escapes[] = { aEH, aSS, aSS, aPA3, aKK1, aPA2, aPA3, aPP, aSS, aEND };
const allophone_t a_escaping[] = { aEH, aSS, aSS, aPA3, aKK1, aPA2, aPA3, aPP, aPA3, aPP, aIH, aNG, aEND };
const allophone_t a_extent[] = { aEH, aKK1, aSS, aTT2, aEH, aEH, aNN1, aTT2, aEND };
const allophone_t a_exterminate[] = { aEH, aKK2, aSS, aTT2, aER1, aMM, aIH, aNN1, aPA1, aEY, aTT2, aEND };
const allophone_t a_father[] = { aFF, aAR, aDH1, aER1, aEND };
const allophone_t a_fir[] = { aFF, aER2, aEND };
const allophone_t a_fool[] = { aFF, aUH, aUH, aLL, aEND };
const allophone_t a_force[] = { aFF, aOR, aSS, aSS, aEND };
const allophone_t a_freeze[] = { aFF, aFF, aRR1, aIY, aZZ, aEND };
const allophone_t a_freezers[] = { aFF, aFF, aRR1, aIY, aZZ, aER1, aZZ, aEND };
const allophone_t a_from[] = { aFF, aRR2, aAA, aMM, aEND };
const allophone_t a_frozen[] = { aFF, aFF, aRR1, aOW, aZZ, aEH, aNN1, aEND };
const allophone_t a_gauge[] = { aGG1, aEY, aPA2, aJH, aEND };
const allophone_t a_gauged[] = { aGG1, aEY, aPA2, aJH, aPA2, aDD1, aEND };
const allophone_t a_gauger[] = { aGG1, aEY, aPA2, aJH, aIH, aZZ, aEND };
const allophone_t a_gauging[] = { aGG1, aEY, aPA2, aJH, aIH, aNG, aEND };
const allophone_t a_happy[] = { aHH2, aAE, aPP, aIY, aEND };
const allophone_t a_has[] = { aHH1, aHH1, aAE, aZZ, aEND };
const allophone_t a_have[] = { aHH1, aHH1, aAE, aVV, aEND };
const allophone_t a_hello[] = { aHH1, aEH, aLL, aOW, aEND };
const allophone_t a_hour[] = { aAW, aER1, aEND };
const allophone_t a_hours[] = { aAW, aER1, aZZ, aEND };
const allophone_t a_how[] = { aHH2, aAW, aEND };
const allophone_t a_idiot[] = { aIH, aPA2, aDD2, aIH, aIH, aIH, aAX, aTT1, aEND };
const allophone_t a_in[] = { aIH, aNN1, aEND };
const allophone_t a_infinitive[] = { aIH, aNN1, aFF, aFF, aIH, aIH, aNN1, aIH, aPA2, aPA3, aTT2, aIH, aVV, aEND };
const allophone_t a_input[] = { aIH, aNN1, aPA1, aPP, aUH, aTT1, aEND };
const allophone_t a_intrigue[] = { aIH, aNN1, aPA3, aTT2, aRR2, aIY, aPA1, aGG3, aEND };
const allophone_t a_intrigued[] = { aIH, aNN1, aPA3, aTT2, aRR2, aIY, aPA1, aGG3, aPA2, aDD1, aEND };
const allophone_t a_intrigues[] = { aIH, aNN1, aPA3, aTT2, aRR2, aIY, aPA1, aGG3, aZZ, aEND };
const allophone_t a_intriguing[] = { aIH, aNN1, aPA3, aTT2, aRR2, aIY, aPA1, aGG3, aIH, aNG, aEND };
const allophone_t a_investigate[] = { aIH, aIH, aNN1, aVV, aEH, aEH, aSS, aPA2, aPA3, aTT2, aIH, aPA1, aGG1, aEY, aPA2, aTT2, aEND };
const allophone_t a_investigated[] = { aIH, aIH, aNN1, aVV, aEH, aEH, aSS, aPA2, aPA3, aTT2, aIH, aPA1, aGG1, aEY, aPA2, aTT2, aIH, aPA2, aDD1, aEND };
const allophone_t a_investigates[] = { aIH, aIH, aNN1, aVV, aEH, aEH, aSS, aPA2, aPA3, aTT2, aIH, aPA1, aGG1, aEY, aPA2, aTT2, aSS, aEND };
const allophone_t a_investigating[] = { aIH, aIH, aNN1, aVV, aEH, aEH, aSS, aPA2, aPA3, aTT2, aIH, aPA1, aGG1, aEY, aPA2, aTT2, aIH, aNG, aEND };
const allophone_t a_investigator[] = { aIH, aIH, aNN1, aVV, aEH, aEH, aSS, aPA2, aPA3, aTT2, aIH, aPA1, aGG1, aEY, aPA2, aTT2, aER1, aEND };
const allophone_t a_investigators[] = { aIH, aIH, aNN1, aVV, aEH, aEH, aSS, aPA2, aPA3, aTT2, aIH, aPA1, aGG1, aEY, aPA2, aTT2, aER1, aZZ, aEND };
const allophone_t a_is[] = { aIH, aZZ, aEND };
const allophone_t a_it[] = { aIH, aPA4, aTT1, aEND };
const allophone_t a_key[] = { aKK1, aIY, aEND };
const allophone_t a_left[] = { aLL, aEH, aFF, aTT1, aEND }; // FIXME rough
const allophone_t a_legislate[] = { aLL, aEH, aEH, aPA2, aJH, aJH, aSS, aSS, aLL, aEY, aPA2, aPA3, aTT2, aEND };
const allophone_t a_legislated[] = { aLL, aEH, aEH, aPA2, aJH, aJH, aSS, aSS, aLL, aEY, aPA2, aPA3, aTT2, aIH, aDD1, aEND };
const allophone_t a_legislates[] = { aLL, aEH, aEH, aPA2, aJH, aJH, aSS, aSS, aLL, aEY, aPA2, aPA3, aTT1, aSS, aEND };
const allophone_t a_legislating[] = { aLL, aEH, aEH, aPA2, aJH, aJH, aSS, aSS, aLL, aEY, aPA2, aPA3, aTT2, aIH, aNG, aEND };
const allophone_t a_legislature[] = { aLL, aEH, aEH, aPA2, aJH, aJH, aSS, aSS, aLL, aEY, aPA2, aPA3, aCH, aER1, aEND };
const allophone_t a_letter[] = { aLL, aEH, aEH, aPA3, aTT2, aER1, aEND };
const allophone_t a_litter[] = { aLL, aIH, aIH, aPA3, aTT2, aER1, aEND };
const allophone_t a_little[] = { aLL, aIH, aIH, aPA3, aTT2, aEL, aEND };
const allophone_t a_live[] = { aLL, aIY, aVV, aEND };
const allophone_t a_memories[] = { aMM, aEH, aEH, aMM, aER2, aIY, aZZ, aEND }; // FIXME different to a_memory
const allophone_t a_memory[] = { aMM, aEH, aMM, aAA, aRR2, aIY, aEND };
const allophone_t a_minus[] = { aMM, aAY, aNN1, aIH, aSS, aEND };
const allophone_t a_minute[] = { aMM, aIH, aNN1, aIH, aPA3, aTT2, aEND };
const allophone_t a_minutes[] = { aMM, aIH, aNN1, aIH, aPA3, aTT2, aZZ, aEND };
const allophone_t a_modem[] = { aMM, aOW, aPA2, aDD2, aEH, aMM, aEND };
const allophone_t a_month[] = { aMM, aAX, aNN1, aTH, aEND };
const allophone_t a_mother[] = { aMM, aAX, aDH2, aER1, aEND };
const allophone_t a_my[] = { aMM, aAY, aEND };
const allophone_t a_name[] = { aNN2, aEY, aMM, aEND };
const allophone_t a_naughty[] = { aNN2, aAO, aAO, aPA3, aTT1, aIY, aEND };
const allophone_t a_nip[] = { aNN1, aIH, aIH, aPA2, aPA3, aPP, aEND };
const allophone_t a_nipped[] = { aNN1, aIH, aIH, aPA2, aPA3, aPP, aPA3, aTT2, aEND };
const allophone_t a_nipping[] = { aNN1, aIH, aIH, aPA2, aPA3, aPP, aIH, aNG, aEND };
const allophone_t a_nips[] = { aNN1, aIH, aIH, aPA2, aPA3, aPP, aSS, aEND };
const allophone_t a_no[] = { aNN2, aOW, aEND }; // FIXME or aNN@, aAX, aOW
const allophone_t a_of[] = { aAA, aVV, aEND };
const allophone_t a_on[] = { aOW, aNN1, aEND };
const allophone_t a_or[] = { aOR, aEND };
const allophone_t a_our[] = { aAW, aER1, aEND };
const allophone_t a_past[] = { aPP, aAR, aSS, aTT2, aEND };
const allophone_t a_physical[] = { aFF, aFF, aIH, aZZ, aIH, aPA3, aKK1, aAX, aEL, aEND };
const allophone_t a_pin[] = { aPP, aIH, aIH, aNN1, aEND };
const allophone_t a_pinned[] = { aPP, aIH, aIH, aNN1, aPA2, aDD1, aEND };
const allophone_t a_pinning[] = { aPP, aIH, aIH, aNN1, aIH, aNG, aEND };
const allophone_t a_pins[] = { aPP, aIH, aIH, aNN1, aZZ, aEND };
const allophone_t a_pledge[] = { aPP, aLL, aEH, aEH, aPA3, aJH, aEND };
const allophone_t a_pledges[] = { aPP, aLL, aEH, aEH, aPA3, aJH, aIH, aZZ, aEND };
const allophone_t a_pledging[] = { aPP, aLL, aEH, aEH, aPA3, aJH, aIH, aNG, aEND };
const allophone_t a_plus[] = { aPP, aLL, aAX, aAX, aSS, aSS, aEND };
const allophone_t a_point[] = { aPP, aOY, aNN1, aTT1, aEND };
const allophone_t a_pressure[] = { aPP, aRR2, aEH, aSH, aER1, aEND };
const allophone_t a_ram[] = { aRR2, aPA2, aAE, aAE, aMM, aEND };
const allophone_t a_ray[] = { aRR1, aEH, aEY, aEND };
const allophone_t a_rays[] = { aRR1, aEH, aEY, aZZ, aEND };
const allophone_t a_ready[] = { aRR1, aEH, aEH, aPA1, aDD2, aIY, aEND };
const allophone_t a_red[] = { aRR1, aEH, aEH, aPA1, aDD1, aEND };
const allophone_t a_right[] = { aRR1, aIH, aTT1, aEND }; // FIXME rough
const allophone_t a_robot[] = { aRR1, aOW, aPA2, aBB2, aAA, aPA3, aTT2, aEND };
const allophone_t a_robots[] = { aRR1, aOW, aPA2, aBB2, aAA, aPA3, aTT1, aSS, aEND };
const allophone_t a_score[] = { aSS, aSS, aPA3, aKK3, aOR, aEND };
const allophone_t a_second[] = { aSS, aSS, aEH, aPA3, aKK1, aIH, aNN1, aPA2, aDD1, aEND };
const allophone_t a_seconds[] = { aSS, aSS, aEH, aPA3, aKK1, aIH, aNN1, aPA2, aDD1, aZZ, aEND };
const allophone_t a_sensitive[] = { aSS, aSS, aEH, aEH, aNN1, aSS, aSS, aIH, aPA2, aPA3, aTT2, aIH, aVV, aEND };
const allophone_t a_sensitivity[] = { aSS, aSS, aEH, aEH, aNN1, aSS, aSS, aIH, aPA2, aPA3, aTT2, aIH, aVV, aIH, aPA2, aPA3, aTT2, aIY, aEND };
const allophone_t a_sensors[] = { aSS, aSS, aEH, aEH, aNN1, aSS, aSS, aER1, aZZ, aEND };
const allophone_t a_sincere[] = { aSS, aSS, aIH, aIH, aNN1, aSS, aSS, aYR, aEND };
const allophone_t a_sincerely[] = { aSS, aSS, aIH, aIH, aNN1, aSS, aSS, aYR, aLL, aIY, aEND };
const allophone_t a_sincerity[] = { aSS, aSS, aIH, aIH, aNN1, aSS, aSS, aEH, aEH, aRR1, aIH, aPA2, aPA3, aTT2, aIY, aEND };
const allophone_t a_sister[] = { aSS, aSS, aIH, aSS, aTT2, aER1, aSS, aIH, aKK2, aSS, aEND };
const allophone_t a_son[] = { aSS, aAX, aNN1, aEND };
const allophone_t a_sound[] = { aSS, aAW, aNN1, aDD1, aEND };
const allophone_t a_south[] = { aSS, aSS, aAW, aTH, aEND };
const allophone_t a_space[] = { aSS, aPP, aEY, aSS, aEND };
const allophone_t a_speak[] = { aSS, aSS, aPA3, aIY, aPA3, aKK2, aEND }; // FIXME dodgy
const allophone_t a_speech[] = { aSS, aPP, aIY, aCH, aEND };
const allophone_t a_spell[] = { aSS, aSS, aPA3, aPP, aEH, aEH, aEL, aEND };
const allophone_t a_spelled[] = { aSS, aSS, aPA3, aPP, aEH, aEH, aEL, aPA3, aDD1, aEND };
const allophone_t a_speller[] = { aSS, aSS, aPA3, aPP, aEH, aEH, aEL, aER2, aEND };
const allophone_t a_spellers[] = { aSS, aSS, aPA3, aPP, aEH, aEH, aEL, aER2, aZZ, aEND };
const allophone_t a_spelling[] = { aSS, aSS, aPA3, aPP, aEH, aEH, aEL, aER2, aIH, aNG, aEND };
const allophone_t a_spells[] = { aSS, aSS, aPA3, aPP, aEH, aEH, aEL, aER2, aZZ, aEND };
const allophone_t a_start[] = { aSS, aSS, aPA3, aTT2, aAR, aPA3, aTT2, aEND };
const allophone_t a_started[] = { aSS, aSS, aPA3, aTT2, aAR, aPA3, aTT2, aIH, aPA1, aDD2, aEND };
const allophone_t a_starter[] = { aSS, aSS, aPA3, aTT2, aAR, aPA3, aTT2, aER1, aEND };
const allophone_t a_starting[] = { aSS, aSS, aPA3, aTT2, aAR, aPA3, aTT2, aIH, aNG, aEND };
const allophone_t a_starts[] = { aSS, aSS, aPA3, aTT2, aAR, aPA3, aTT2, aSS, aEND };
const allophone_t a_statement[] = { aSS, aPA2, aTT1, aEY, aPA2, aTT1, aMM, aEH, aNN1, aTT1, aEND };
const allophone_t a_stop[] = { aSS, aSS, aPA3, aTT2, aAA, aAA, aPA3, aPP, aEND };
const allophone_t a_stopped[] = { aSS, aSS, aPA3, aTT2, aAA, aAA, aPA3, aPP, aPA3, aTT2, aEND };
const allophone_t a_stopper[] = { aSS, aSS, aPA3, aTT2, aAA, aAA, aPA3, aPP, aPA3, aER1, aEND };
const allophone_t a_stopping[] = { aSS, aSS, aPA3, aTT2, aAA, aAA, aPA3, aPP, aPA3, aIH, aNG, aEND };
const allophone_t a_stops[] = { aSS, aSS, aPA3, aTT2, aAA, aAA, aPA3, aPP, aSS, aEND };
const allophone_t a_subject_noun[] = { aSS, aSS, aAX, aAX, aPA2, aBB1, aPA2, aJH, aEH, aPA3, aKK2, aPA3, aTT2, aEND };
const allophone_t a_subject_verb[] = { aSS, aSS, aAX, aPA2, aBB1, aPA2, aJH, aEH, aEH, aPA3, aKK2, aPA3, aTT2, aEND };
const allophone_t a_sweat[] = { aSS, aSS, aWW, aEH, aEH, aPA3, aTT2, aEND };
const allophone_t a_sweated[] = { aSS, aSS, aWW, aEH, aEH, aPA3, aTT2, aIH, aPA3, aDD1, aEND };
const allophone_t a_sweater[] = { aSS, aSS, aWW, aEH, aEH, aPA3, aTT2, aER1, aEND };
const allophone_t a_sweaters[] = { aSS, aSS, aWW, aEH, aEH, aPA3, aTT2, aER1, aZZ, aEND };
const allophone_t a_sweating[] = { aSS, aSS, aWW, aEH, aEH, aPA3, aTT2, aIH, aNG, aEND };
const allophone_t a_switch[] = { aSS, aSS, aWW, aIH, aIH, aPA3, aCH, aEND };
const allophone_t a_switched[] = { aSS, aSS, aWW, aIH, aIH, aPA3, aCH, aPA3, aTT2, aEND };
const allophone_t a_switches[] = { aSS, aSS, aWW, aIH, aIH, aPA3, aCH, aIH, aZZ, aEND };
const allophone_t a_switching[] = { aSS, aSS, aWW, aIH, aIH, aPA3, aCH, aIH, aNG, aEND };
const allophone_t a_system[] = { aSS, aSS, aIH, aIH, aPA3, aSS, aSS, aPA3, aTT2, aEH, aMM, aEND };
const allophone_t a_systems[] = { aSS, aSS, aIH, aIH, aPA3, aSS, aSS, aPA3, aTT2, aEH, aMM, aZZ, aEND };
const allophone_t a_talk[] = { aTT2, aAO, aAO, aPA2, aKK2, aEND };
const allophone_t a_talked[] = { aTT2, aAO, aAO, aPA2, aKK2, aPA3, aTT2, aEND };
const allophone_t a_talker[] = { aTT2, aAO, aAO, aPA2, aKK2, aER1, aEND };
const allophone_t a_talkers[] = { aTT2, aAO, aAO, aPA2, aKK2, aER1, aZZ, aEND };
const allophone_t a_talking[] = { aTT2, aAO, aAO, aPA3, aKK1, aIH, aNG, aEND };
const allophone_t a_talks[] = { aTT2, aAO, aAO, aPA2, aKK2, aSS, aEND };
const allophone_t a_television[] = { aTT2, aEH, aLL, aIH, aVV, aIH, aSS, aIH, aAA, aNN1, aEND };
const allophone_t a_temperature[] = { aTT2, aEH, aMM, aPP, aRR1, aIY, aCH, aOR, aEND };
const allophone_t a_test[] = { aTT2, aEH, aSS, aPA2, aTT1, aIH, aNG, aEND };
const allophone_t a_the[] = { aDH1, aIY, aEND };
const allophone_t a_then[] = { aDH1, aEH, aEH, aNN1, aEND };
const allophone_t a_there[] = { aDH2, aEH, aXR, aEND };
const allophone_t a_this[] = { aDH1, aIH, aSS, aEND };
const allophone_t a_thread[] = { aTH, aRR1, aEH, aEH, aPA2, aDD1, aEND };
const allophone_t a_threaded[] = { aTH, aRR1, aEH, aEH, aPA2, aDD2, aIH, aPA2, aDD1, aEND };
const allophone_t a_threader[] = { aTH, aRR1, aEH, aEH, aPA2, aDD2, aER1, aEND };
const allophone_t a_threaders[] = { aTH, aRR1, aEH, aEH, aPA2, aDD2, aER1, aZZ, aEND };
const allophone_t a_threading[] = { aTH, aRR1, aEH, aEH, aPA2, aDD2, aIH, aNG, aEND };
const allophone_t a_threads[] = { aTH, aRR1, aEH, aEH, aPA2, aDD2, aZZ, aEND };
const allophone_t a_time[] = { aTT2, aAA, aAY, aMM, aEND }; // FIXME aAA?
const allophone_t a_times[] = { aTT2, aAA, aAY, aMM, aZZ, aEND };
const allophone_t a_to[] = { aTT2, aUW2, aEND };
const allophone_t a_today[] = { aTT2, aUW2, aDD2, aEY, aEND };
const allophone_t a_uncle[] = { aAX, aNG, aPA3, aKK3, aEL, aEND };
const allophone_t a_up[] = { aAX, aPP, aEND }; // FIXME rough
const allophone_t a_vision[] = { aVV, aIH, aZH, aIH, aIH, aAA, aNN1, aEND };
const allophone_t a_want[] = { aWW, aAA, aNN1, aPA3, aTT1, aEND };
const allophone_t a_whale[] = { aWW, aEY, aEL, aEND };
const allophone_t a_whaler[] = { aWW, aEY, aLL, aER1, aEND };
const allophone_t a_whalers[] = { aWW, aEY, aLL, aER1, aZZ, aEND };
const allophone_t a_whales[] = { aWW, aEY, aEL, aZZ, aEND };
const allophone_t a_whaling[] = { aWW, aEY, aLL, aIH, aNG, aEND };
const allophone_t a_what[] = { aWH, aAA, aPA3, aTT1, aEND };
const allophone_t a_who[] = { aHH2, aUH, aUW2, aEND };
const allophone_t a_with[] = { aWH, aIH, aTH, aEND };
const allophone_t a_year[] = { aYY2, aYR, aEND };
const allophone_t a_yes[] = { aYY2, aEH, aEH, aSS, aSS, aEND };
const allophone_t a_you[] = { aYY2, aUW2, aEND };
const allophone_t a_your[] = { aYY2, aOR, aEND };

/* Homophones */
const allophone_t * a_fur = a_fir;
const allophone_t * a_know = a_no;

/* **************************************** */
/* Days of the week */

static const allophone_t a_Sunday[] = { aSS, aSS, aAX, aAX, aNN1, aPA2, aDD2, aEY, aEND };
static const allophone_t a_Monday[] = { aMM, aAX, aAX, aNN1, aPA2, aDD2, aEY, aEND };
static const allophone_t a_Tuesday[] = { aTT2, aUW1, aZZ, aPA2, aDD2, aEY, aEND };
static const allophone_t a_Wednesday[] = { aWW, aEH, aEH, aNN1, aZZ, aPA2, aDD2, aEY, aEND };
static const allophone_t a_Thursday[] = { aTH, aER2, aZZ, aPA2, aDD2, aEY, aEND };
static const allophone_t a_Friday[] = { aFF, aRR2, aAY, aPA2, aDD2, aEY, aEND };
static const allophone_t a_Saturday[] ={ aSS, aSS, aAE, aPA3, aTT2, aPA2, aDD2, aEY, aEND };

const allophone_t * const
a_days[] = {
  a_Sunday, a_Monday, a_Tuesday, a_Wednesday, a_Thursday, a_Friday, a_Saturday
};

/* **************************************** */
/* Months */

static const allophone_t a_January[] = { aJH, aAE, aAE, aNN1, aYY2, aXR, aIY, aEND };
static const allophone_t a_February[] = { aFF, aEH, aEH, aPA1, aBB1, aRR2, aUW2, aXR, aIY, aEND };
static const allophone_t a_March[] = { aMM, aAR, aPA3, aCH, aEND };
static const allophone_t a_April[] = { aEY, aPA3, aPP, aRR2, aIH, aIH, aLL, aEND };
static const allophone_t a_May[] = { aMM, aEY, aEND };
static const allophone_t a_June[] = { aJH, aUW2, aNN1, aEND };
static const allophone_t a_July[] = { aJH, aUW1, aLL, aAY, aEND };
static const allophone_t a_August[] = { aAO, aAO, aPA2, aGG2, aAX, aSS, aPA3, aTT1, aEND };
static const allophone_t a_September[] = { aSS, aSS, aEH, aPA3, aPP, aPA3, aTT2, aEH, aEH, aMM, aPA1, aBB2, aER2, aEND };
static const allophone_t a_October[] = { aAA, aPA2, aKK2, aPA3, aTT2, aOW, aPA1, aBB2, aER1, aEND };
static const allophone_t a_November[] = { aNN2, aOW, aVV, aEH, aEH, aMM, aPA1, aBB2, aER1, aEND };
static const allophone_t a_December[] = { aDD2, aIY, aSS, aSS, aEH, aEH, aMM, aPA1, aBB2, aER1, aEND };

const allophone_t * const
a_months[] = {
  a_January, a_February, a_March, a_April, a_May, a_June, a_July, a_August, a_September, a_October, a_November, a_December
};

/* **************************************** */
/* Numbers */

// FIXME may also want the ordinals: first, second, ...

static const allophone_t a_zero[] = { aZZ, aYR, aOW, aEND };
static const allophone_t a_one[] = { aWH, aAX, aNN1, aEND };
static const allophone_t a_two[] = { aTT2, aUW2, aEND };
static const allophone_t a_three[] = { aDH2, aRR2, aIY, aEND };
static const allophone_t a_four[] = { aFF, aAO, aAO, aRR2, aEND };
static const allophone_t a_five[] = { aFF, aAY, aVV, aEND };
static const allophone_t a_six[] = { aSS, aIH, aKK2, aSS, aEND };
static const allophone_t a_seven[] = { aSS, aSS, aEH, aEH, aVV, aIH, aNN1, aEND };
static const allophone_t a_eight[] = { aEY, aTT1, aEND };
static const allophone_t a_nine[] = { aNN2, aAY, aNN1, aEND };
static const allophone_t a_ten[] = { aTT2, aEH, aEH, aNN1, aEND };
static const allophone_t a_eleven[] = { aIY, aLL, aEH, aVV, aER1, aNN1, aEND };
static const allophone_t a_twelve[] = { aTT2, aWW, aEH, aEL, aPA2, aVV, aEND };
static const allophone_t a_thirteen[] = { aTH, aER1, aTT2, aIY, aNN1, aEND };
static const allophone_t a_fourteen[] = { aFF, aAO, aRR2, aTT2, aIY, aNN1, aEND };
static const allophone_t a_fifteen[] = { aFF, aIH, aFF, aTT2, aIY, aNN1, aEND };
static const allophone_t a_sixteen[] = { aSS, aIH, aKK2, aSS, aTT2, aIY, aNN1, aEND };
static const allophone_t a_seventeen[] = { aSS, aSS, aEH, aEH, aVV, aIH, aNN1, aTT2, aIY, aNN1, aEND };
static const allophone_t a_eighteen[] = { aEY, aTT1, aTT2, aIY, aNN1, aEND };
static const allophone_t a_nineteen[] = { aNN2, aAY, aNN1, aTT2, aIY, aNN1, aEND };
static const allophone_t a_twenty[] = { aTT2, aWW, aEH, aNN1, aTT2, aIY, aEND };
static const allophone_t a_thirty[] = { aTH, aER1, aTT2, aIY, aEND };
static const allophone_t a_forty[] = { aFF, aAO, aRR2, aTT2, aIY, aEND };
static const allophone_t a_fifty[] = { aFF, aIH, aFF, aTT2, aIY, aEND };
static const allophone_t a_sixty[] = { aSS, aIH, aKK2, aSS, aTT2, aIY, aEND };
static const allophone_t a_seventy[] = { aSS, aSS, aEH, aEH, aVV, aIH, aNN1, aTT2, aIY, aEND };
static const allophone_t a_eighty[] = { aEY, aTT1, aTT2, aIY, aEND };
static const allophone_t a_ninety[] = { aNN2, aAY, aNN1, aTT2, aIY, aEND };

const allophone_t a_hundred[] = { aHH2, aAX, aAX, aNN1, aPA2, aDD2, aRR2, aIH, aIH, aPA1, aDD1, aEND };
const allophone_t a_thousand[] = { aTH, aAW, aZZ, aAE, aNN1, aDD1, aEND };
const allophone_t a_million[] = { aMM, aIH, aIH, aLL, aYY1, aAX, aNN1, aEND };

const allophone_t * const
a_numbers[] = {
  a_zero, a_one, a_two, a_three, a_four, a_five,
  a_six, a_seven, a_eight, a_nine, a_ten,
  a_eleven, a_twelve, a_thirteen, a_fourteen, a_fifteen,
  a_sixteen, a_seventeen, a_eighteen, a_nineteen
};

const allophone_t * const
a_decades[] = {
  a_twenty, a_thirty, a_forty, a_fifty, a_sixty, a_seventy, a_eighty, a_ninety
};

void
sp0256_number(struct sp0256 *sp0256, int16_t n) // FIXME can go larger
{
  while(1) {
    if(n < 0) {
      sp0256_allophones(sp0256, a_minus);
      n = -n;
    } else if(n >= 1000) {
      uint8_t t = n / 1000;
      n = n % 1000;

      sp0256_number(sp0256, t);
      sp0256_allophones(sp0256, a_thousand);
      if(n == 0) {
        break;
      }
      sp0256_allophone(sp0256, aPA5);
      if(n < 100) {
        sp0256_allophones(sp0256, a_and);
      }
    } else if(n >= 100) {
      uint8_t h = n / 100;
      n = n % 100;

      sp0256_number(sp0256, h);
      sp0256_allophones(sp0256, a_hundred);
      if(n == 0) {
        break;
      } else {
        sp0256_allophone(sp0256, aPA5);
        sp0256_allophones(sp0256, a_and);
      }
    } else if(n >= 20) {
      uint8_t d = n / 10;
      n = n % 10;

      sp0256_allophones(sp0256, a_decades[d - 2]);
      if(n == 0) {
        break;
      }
    } else {
      sp0256_allophones(sp0256, a_numbers[n]);
      break;
    }
  }
}

/* **************************************** */
/* Metric */

const allophone_t a_mega[] = { aMM, aEH, aGG1, aAX, aEND };
const allophone_t a_kilo[] = { aKK1, aIH, aLL, aOW, aEND };
const allophone_t a_hecto[] = { aHH1, aEH, aKK2, aPA3, aTT2, aOW, aEND };

const allophone_t a_pascals[] = { aPP, aAE, aSS, aKK2, aAO, aLL, aSS, aEND };

/* **************************************** */
/* Application specific */

/* BMP085 specific: pressure is of the form 100268 -> 1002.68 hPa */
void
sp0256_pressure(struct sp0256 *sp0256, int pressure)
{
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_the, a_PA4, a_pressure, a_PA4, a_is, a_PA4, NULL });
  sp0256_number(sp0256, pressure / 100);
  sp0256_allophones(sp0256, a_point);
  sp0256_number(sp0256, pressure % 100); // FIXME round, check precision, say decimal digits
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_PA5, a_hecto, a_pascals, NULL });
}

/* BMP085 specific: temp is of the form 24900 -> 24.9 C */
void
sp0256_temp(struct sp0256 *sp0256, uint16_t temp)
{
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_the, a_PA4, a_temperature, a_PA4, a_is, a_PA4, NULL });
  sp0256_number(sp0256, temp / 1000);
  sp0256_allophones(sp0256, a_point);
  sp0256_number(sp0256, (temp % 1000) / 100); // FIXME round, check precision
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_PA5, a_degrees, NULL });
}

void
sp0256_time(struct sp0256 *sp0256, const struct tm tm)
{
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_the, a_PA4, a_time, a_PA4, a_is, a_PA4, NULL });
  sp0256_number(sp0256, tm.tm_hour % 12 == 0 ? 12 : tm.tm_hour % 12);
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_PA4, NULL });
  sp0256_number(sp0256, tm.tm_min);
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_PA4, tm.tm_hour < 12 ? a_AM : a_PM, a_PA5, a_on, a_PA4, a_days[tm.tm_wday], a_PA5, a_months[tm.tm_mon], a_PA4, NULL });
  sp0256_number(sp0256, tm.tm_mday);
  sp0256_phrase(sp0256, (const allophone_t *[]){ a_PA5, a_PA5, NULL });
  sp0256_number(sp0256, tm.tm_year + 1900);
}

/* **************************************** */
/* FIXME */

void
sp0256_allophones(const struct sp0256 *sp0256, const allophone_t *allophones)
{
  for(; *allophones != aEND; allophones++) {
    sp0256_allophone(sp0256, *allophones);
  }
}

void
sp0256_phrase(const struct sp0256 *sp0256, const allophone_t * const phrase[])
{
  for(; *phrase != NULL; phrase++) {
    sp0256_allophones(sp0256, *phrase);
  }
}

/*
Used like so:

  const allophone_t *hour[10];
  const allophone_t *mday[3];
  const allophone_t *min[10];
  const allophone_t *year[5]; // FIXME guesses at sizes

  sp0256_number(hour, tm.tm_hour % 12 == 0 ? 12 : tm.tm_hour % 12);
  sp0256_number(mday, tm.tm_mday);
  sp0256_number(min, tm.tm_min);
  sp0256_number(year, tm.tm_year + 1900);

  sp0256_sentence(sp0256,
                  (const allophone_t *[]){ a_the, a_PA4, a_time, a_PA4, a_is, a_PA4, NULL },
                  hour,
                  (const allophone_t *[]){ a_PA4, NULL },
                  min,
                  (const allophone_t *[]){ a_PA4, tm.tm_hour < 12 ? a_am : a_pm, a_PA5, a_on, a_PA4, a_days[tm.tm_wday], a_PA5, a_months[tm.tm_mon], a_PA4, NULL },
                  mday,
                  (const allophone_t *[]){ a_PA5, a_PA5, NULL },
                  year,
                  NULL);
 */
void
sp0256_sentence(const struct sp0256 *sp0256, ...)
{
  va_list ap;

  va_start(ap, sp0256);
  for(const allophone_t * const *phrase = va_arg(ap, const allophone_t * const *);
      phrase != NULL;
      phrase = va_arg(ap, const allophone_t * const *)) {
    sp0256_phrase(sp0256, phrase);
  }
}
