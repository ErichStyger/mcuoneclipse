/**
 * \file
 * \brief Configuration header file for 1-Wire
 *
 * This header file is used to configure settings of the 1-Wire module.
 */

#ifndef __OW1_CONFIG_H
#define __OW1_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* protocol timing in micro seconds */
/* write */
#define OW1_CONFIG_A_WRITE_1_LOW_TIME                       5        /* A: standard 6 us, low time to write one bit */
#define OW1_CONFIG_B_WRITE_1_HIGH_TIME                      64       /* B: standard 64 us, high time after writing one bit (A) */
#define OW1_CONFIG_C_WRITE_0_LOW_TIME                       60       /* C: standard 60 us, Low time writing zero bit */
#define OW1_CONFIG_D_WRITE_0_HIGH_TIME                      10       /* D: standard 10 us, High time after writing zero bit (C) */
/* read */
#define OW1_CONFIG_A_READ_LOW_TIME                          6 /* Low time to start read */
#define OW1_CONFIG_E_BEFORE_READ_DELAY_TIME                 1        /* E: standard 9 us, wait time after starting read (when to read bit) */
#define OW1_CONFIG_F_AFTER_READ_DELAY_TIME                  55       /* F: standard 55 us, wait time after reading bit (E)  */
/* reset */
#define OW1_CONFIG_H_RESET_TIME                             480      /* H: standard 480 us, reset low time */
#define OW1_CONFIG_I_RESET_RESPONSE_TIME                    70       /* I: standard 70 us, wait time after reset low time (H) until read response */
#define OW1_CONFIG_J_RESET_WAIT_TIME                        410      /* J: standard 410 us, wait time after reading presence (I)  */

#define OW1_CONFIG_SLOT_TIME                                100

#define OW1_CONFIG_DEBUG_READ_PIN_ENABLED                   (1)
  /*!< 1: Toggle extra GPIO pin during 1-wire read access; 0: no debug */

#if OW1_CONFIG_DEBUG_READ_PIN_ENABLED
  #include "DbgRd1.h" /* SDK and API used */
  #define OW1_CONFIG_DEBUG_READ_PIN_INIT                    DbgRd1_Init()
  #define OW1_CONFIG_DEBUG_READ_PIN_DEINIT                  DbgRd1_Deinit()
  #define OW1_CONFIG_DEBUG_READ_PIN_TOGGLE                  DbgRd1_NegVal()
#endif

#ifndef OW1_CONFIG_WRITE_PIN
  #define OW1_CONFIG_WRITE_PIN                              (0)
    /*!< 1: using dedicated write pin; 0: using single pin for read/write */
#endif

#if OW1_CONFIG_WRITE_PIN
  #include "WritePin.h"
  #define OW1_CONFIG_WRITE_PIN_INIT                         WritePin_Init()
  #define OW1_CONFIG_WRITE_PIN_DEINIT                       WritePin_Deinit()
  #define OW1_CONFIG_WRITE_PIN_LOW                          WritePin_ClrVal()
  #define OW1_CONFIG_WRITE_PIN_HIGH                         WritePin_SetVal()
  #define OW1_CONFIG_WRITE_PIN_SET_OUTPUT                   WritePin_SetOutput()
#endif

#if !defined(OW1_CONFIG_PARSE_COMMAND_ENABLED)
  #define OW1_CONFIG_PARSE_COMMAND_ENABLED                 (1)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __OW1_CONFIG_H */
