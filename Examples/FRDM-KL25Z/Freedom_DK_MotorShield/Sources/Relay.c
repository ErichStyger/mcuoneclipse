/*
 * Relay.c
 *
 *  Created on: Jun 3, 2013
 *      Author: tastyger
 */

#include "Relay.h"
#include "HC595.h"
#include "PWM0A.h"
#include "PWM0B.h"
#include "PWM0A.h"
#include "PWM0B.h"
#include "PWM2A.h"
#include "PWM2B.h"

/* Bit positions in the 74HCT595 shift register output */
#define MOTOR1_A_BIT 5
#define MOTOR1_B_BIT 4
#define MOTOR2_A_BIT 6
#define MOTOR2_B_BIT 3

#define MOTOR4_A_BIT 7
#define MOTOR4_B_BIT 1
#define MOTOR3_A_BIT 2
#define MOTOR3_B_BIT 0

static void M1A_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR1_A_BIT));
}

static void M1A_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR1_A_BIT)));
}

static void M1B_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR1_B_BIT));
}

static void M1B_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR1_B_BIT)));
}

static void M2A_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR2_A_BIT));
}

static void M2A_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR2_A_BIT)));
}

static void M2B_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR2_B_BIT));
}

static void M2B_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR2_B_BIT)));
}

static void M3A_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR3_A_BIT));
}

static void M3A_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR3_A_BIT)));
}

static void M3B_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR3_B_BIT));
}

static void M3B_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR3_B_BIT)));
}

static void M4A_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR4_A_BIT));
}

static void M4A_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR4_A_BIT)));
}

static void M4B_On(void) {
  HC595_WriteByte(HC595_ReadByte()|(1<<MOTOR4_B_BIT));
}

static void M4B_Off(void) {
  HC595_WriteByte(HC595_ReadByte()&(~(1<<MOTOR4_B_BIT)));
}

void REL_On(uint8_t relNo) {
  switch(relNo) {
    case 0: M1A_On(); break;
    case 1: M1B_On(); break;
    case 2: M2A_On(); break;
    case 3: M2B_On(); break;
    case 4: M3A_On(); break;
    case 5: M3B_On(); break;
    case 6: M4A_On(); break;
    case 7: M4B_On(); break;
    default: break;
  }
}

void REL_Off(uint8_t relNo) {
  switch(relNo) {
    case 0: M1A_Off(); break;
    case 1: M1B_Off(); break;
    case 2: M2A_Off(); break;
    case 3: M2B_Off(); break;
    case 4: M3A_Off(); break;
    case 5: M3B_Off(); break;
    case 6: M4A_Off(); break;
    case 7: M4B_Off(); break;
    default: break;
  }
}

void REL_Init(void) {
  HC595_WriteByte(0); /* all off */
  /* enable all relays */
  PWM2A_SetVal(); /* M1A and M1B */
  PWM2B_SetVal(); /* M2A and M2B */
  PWM0B_SetVal(); /* M3A and M3B */
  PWM0A_SetVal(); /* M4A and M4B */
}

