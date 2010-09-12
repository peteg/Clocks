/*
 * SP0256 allophones.
 *
 * based on http://nsd.dyndns.org/speech/
 *
 * This version licenced under CC0 v1.0
 * https://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef _ALLOPHONES_H_
#define _ALLOPHONES_H_

#include <stdint.h>

enum {
  /* Silence */
  aPA1 = 0x00, /* before BB,DD,GG,JH (10 msec) */
  aPA2 = 0x01, /* before BB,DD,GG,JH (30 msec) */
  aPA3 = 0x02, /* before PP,TT,KK,CH and between words (50 msec) */
  aPA4 = 0x03, /* between clauses and sentences (100 msec) */
  aPA5 = 0x04, /* between clauses and sentences (200 msec) */

  /* Short Vowels */
  aIH  = 0x0c, /* sIt */
  aEH  = 0x07, /* End, gEntlemen, Extend */
  aAE  = 0x1a, /* hAt, extrAct, Act */
  aUH  = 0x1e, /* bOOk, cOOkie, fUll */
  aAO  = 0x17, /* tALk, sOng, AUght */
  aAX  = 0x0f, /* sUCCeed, lApel, instrUCt */
  aAA  = 0x18, /* hOT, pOTtery, cOTten */

  /* Long Vowels */
  aIY  = 0x13, /* sEE, trEAt, pEOple, pEnny */
  aEY  = 0x14, /* bEIge, grEAt, stAte, trAY */
  aAY  = 0x06, /* skY, kIte, mIGHty */
  aOY  = 0x05, /* bOY, nOIse, vOIce */
  aUW1 = 0x16, /* compUter (after clusters with YY) */
  aUW2 = 0x1f, /* fOOd, tWO (monosyllabic words) */
  aOW  = 0x35, /* zOne, clOse, snOW, bEAU */
  aAW  = 0x20, /* OUt, sOUnd, mOUse, dOWn */
  aEL  = 0x3e, /* saddLE, littLE, angLE, gentLEmen */

  /* R-Colored Vowels */
  aER1 = 0x33, /* lettER, furnitURE, intERRupt */
  aER2 = 0x34, /* bIRd, fERn, bURn (monosyllabic words) */
  aOR  = 0x3a, /* stORe, adORn, fORtune */
  aAR  = 0x3b, /* alARm, fARm, gARment */
  aYR  = 0x3c, /* clEAR, EARring, IResponsible */
  aXR  = 0x2f, /* repaiR, haiR, declaRE, staRE */

  /* Resonants */
  aWW  = 0x2e, /* Wool, We, lingUIst */
  aRR1 = 0x0e, /* Rural, WRite, x-Ray (initial position) */
  aRR2 = 0x27, /* bRain, bRown, gRease (initial clusters) */
  aLL  = 0x2d, /* Lake, Like, heLLo, steeL */
  aYY1 = 0x31, /* cUte, bEAUty, compUter (clusters) */
  aYY2 = 0x19, /* Yes, Yarn, Yo-Yo (initial position) */

  /* Voiced Fricatives */
  aVV  = 0x23, /* Vest, proVE, eVen */
  aDH1 = 0x12, /* THis, THen, THey (initial position) */
  aDH2 = 0x36, /* baTHe, baTHing (word-final and between vowels) */
  aZZ  = 0x2b, /* Zoo, phaSE */
  aZH  = 0x26, /* aZure, beiGE, pleaSUre */

  /* Voiceless Fricatives */
  aFF  = 0x28, /* Food (can be doubled for initial position) */
  aTH  = 0x1d, /* THin (can be doubled for initial position) */
  aSS  = 0x37, /* Snake, veSt (can be doubled for initial position) */
  aSH  = 0x25, /* SHip, SHirt, leaSH, naTion */
  aHH1 = 0x1b, /* He (before front vowels YR,IY,IH,EY,EH,XR,AE) */
  aHH2 = 0x39, /* Hoe (before back vowels UW,UH,OW,OY,AO,OR,AR) */
  aWH  = 0x30, /* WHig, WHite, tWenty */

  /* Voiced Stops */
  aBB1 = 0x1c, /* riB, fiBBer, (in clusters) BLeed, BRown */
  aBB2 = 0x3f, /* Business, Beast (initial position before vowel) */
  aDD1 = 0x15, /* coulD, playeD, enD (final position) */
  aDD2 = 0x21, /* Do, Down, Drain (initial position and clusters) */
  aGG1 = 0x24, /* Got (before high front vowels YR,IY,IH,EY,EH,XR) */
  aGG2 = 0x3d, /* GUest, Glue, Green (before high back vowels UW,UH,OW,OY,AX) */
  aGG3 = 0x22, /* wiG, anGer (before low vowels AE,AW,AY,AR,AA,AO,OR,ER) */

  /* Voiceless Stops */
  aPP  = 0x09, /* Pow, triP, amPle, Pleasure */
  aTT1 = 0x11, /* parTs, tesTs, iTs (final cluster before SS) */
  aTT2 = 0x0d, /* To, TesT, sTreeT (all positions except before final SS) */
  aKK1 = 0x2a, /* Can't, Cute, Clown, sCream (before front vowels YR,IY,IH,EY,EH,XR,AY,AE,ER,AX and initial clusters) */
  aKK2 = 0x29, /* speaK, tasK (final position or final cluster) */
  aKK3 = 0x08, /* Comb, QUick, Crane, sCream (before back vowels UW,UH,OW,OY,OR,AR,AO and initial clusters) */

  /* Affricates */
  aCH  = 0x32, /* CHurCH, feaTure */
  aJH  = 0x0a, /* JudGE, inJUre, dodGE */

  /* Nasal */
  aMM  = 0x10, /* Milk, alarM, aMple */
  aNN1 = 0x0b, /* thiN, earN (before front and central vowels YR,IY,IH,EY,EH,XR,AE,ER,AX,AW,AY, and final clusters) */
  aNN2 = 0x38, /* No (before back vowels UH,OW,OY,OR,AR,AA) */
  aNG  = 0x2c, /* striNG, aNGer, aNchor */

  /* Sentinel for arrays of allophones. */
  aEND = 0xFF,
};

/* We don't know how big the enum type is, so hardwire it even though
 * GCC -fshort-enums probably gets it right. */
typedef uint8_t allophone_t;

#endif /* _ALLOPHONES_H_ */
