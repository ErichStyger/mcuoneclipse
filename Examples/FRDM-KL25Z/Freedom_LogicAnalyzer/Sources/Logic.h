/*
 * Logic.h
 *
 *  Edited on:  Feb 10, 2013 by: Reiner Geiger why: started with simple trigger support
 *        Feb 11, 2013 by: Reiner Geiger why: started with 1 MHz support
 *        Feb 25, 2013 by: Reiner Geiger why: updating to Version 1.1 from E. Styger
 *        Mar 18, 2013 by: Reiner Geiger why: 1st DMA based Implementation
 */

#ifndef LOGIC_H_
#define LOGIC_H_

/* Sampling Buffer Size */
#define BUFFERSIZE 14*1024
#define MAX_SAMPLERATE 24000000   // we allow maximum speed for now
#define DEFAULT_CLOCK_DIVIDER 99    // 100MHz / (DCS+1) = 1 MHz Default

/* global */
#define DEVICE_NAME             "FRDM-KL25Z LogicLogger"  // Original by Erich Styger
#define DEVICE_FW_VERSION       "V2.1"            // first working Version with very simple DMA Support by RG
#define DEVICE_ANCILLARY        "V2.0"
#define DEVICE_NOF_PROBES       8 /* number of probes */
#define DEVICE_PROTOCOL_VERSION 2 /* always 2! */

/* SUMP Protocol */
#define SUMP_RESET 0x00 /* resets the device */
#define SUMP_RUN 0x01 /* arms the trigger */
#define SUMP_ID 0x02 /* asks for device identification. First three bytes are "SLA" followed by either 0 or 1 */
#define SUMP_SELFTEST 0x03 /* trigger self-test */
#define SUMP_GET_METADATA 0x04 /* as the name defines */
#define SUMP_RLE 0x05 /* finish now, end current RLE capture */
#define SUMP_RUN_ADVANCED_TRIGGER 0x0F
#define SUMP_SET_DIVIDER 0x80 /* set sample frequency, which is f=clock/(x+1), so it is 999 for 100 kHz, 1999 for 50 kHz */
#define SUMP_SET_READ_DELAY_COUNT 0x81
#define SUMP_SET_FLAGS 0x82
#define SUMP_FLAGS_TEST_DATA (1<<10) /* Internal test pattern mode (supplies data internally) (http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol) */
#define SUMP_WRITE_TRIGGER_SELECT 0x9E
#define SUMP_WRITE_TRIGGER_DATA 0x9F

#define SUMP_SET_TRIGGER_MASK_0 0xC0 /* trigger mask stage 0 */
#define SUMP_SET_TRIGGER_VALUE_0 0xC1 /* trigger value stage 0 */
#define SUMP_SET_TRIGGER_CONFIG_0 0xC2 /* trigger configuration stage 0 */

#define SUMP_SET_TRIGGER_MASK_1 0xC4 /* trigger mask stage 1 */
#define SUMP_SET_TRIGGER_VALUE_1 0xC5 /* trigger value stage 1 */
#define SUMP_SET_TRIGGER_CONFIG_1 0xC6 /* trigger configuration stage 1 */

#define SUMP_SET_TRIGGER_MASK_2 0xC8 /* trigger mask stage 2 */
#define SUMP_SET_TRIGGER_VALUE_2 0xC9 /* trigger value stage 2 */
#define SUMP_SET_TRIGGER_CONFIG_2 0xCA /* trigger configuration stage 2 */

#define SUMP_SET_TRIGGER_MASK_3 0xCC /* trigger mask stage 3 */
#define SUMP_SET_TRIGGER_VALUE_3 0xCD /* trigger value stage 3 */
#define SUMP_SET_TRIGGER_CONFIG_3 0xCE /* trigger configuration stage 3 */

/* actually we support only trigger stage 0 */
#define SUMP_TRIGGER_STAGES 1

/* Macros */

/* Typedefs */
typedef unsigned long triggerMask;
typedef unsigned long triggerValues;
typedef unsigned long triggerConfiguration;
typedef unsigned long triggerFlags;
typedef unsigned long frequencyDivider;
typedef unsigned long RandDCount;

typedef struct trigger_data{
  triggerMask mask;
  triggerValues values;
  triggerConfiguration configuration;
} TRIGGER_DATA;

void LOGIC_dmat1OnCompleted(void);
void LOGIC_dmat1OnError(void);
void LOGIC_Run(void);

void LOGIC_OnComplete(void);

#endif /* LOGIC_H_ */
