/**
 * \file
 * \brief Configuration header file for SDK_Timer
 *
 * This header file is used to configure settings of the SDK Timer module.
 */
#ifndef __TMR1_CONFIG_H
#define __TMR1_CONFIG_H

#ifndef TMR1_CONFIG_TIMER_NAME
  #define TMR1_CONFIG_TIMER_NAME       TPM2
    /*!< name of TIMER, is pointer to TPM_Type */
#endif

#define TMR1_CONFIG_TIMER_IRQ  TPM2##_IRQn

#ifndef TMR1_CONFIG_TIMER_INIT_PERIOD_US
  #define TMR1_CONFIG_TIMER_INIT_PERIOD_US       1000
    /*!< Initial period in micro-seconds */
#endif

#ifndef TMR1_CONFIG_TIMER_INIT_ENABLE_TIMER
  #define TMR1_CONFIG_TIMER_INIT_ENABLE_TIMER       (1)
    /*!< 1: Enable the timer in Init(); 0: Timer is disabled in Init() */
#endif

#ifndef TMR1_CONFIG_TIMER_INIT_ENABLE_IRQ
  #define TMR1_CONFIG_TIMER_INIT_ENABLE_IRQ       (1)
    /*!< 1: Enable NVIC IRQ for the timer in Init(); 0: Timer IRQ is disabled in Init() */
#endif

#ifndef TMR1_CONFIG_TIMER_INIT_ENABLE_OVERFLOW_IRQ
  #define TMR1_CONFIG_TIMER_INIT_ENABLE_OVERFLOW_IRQ       (1)
    /*!< 1: Enable the timer overflow interrupt in Init(); 0: Timer overflow interrupt is disabled in Init() */
#endif

#endif /* __TMR1_CONFIG_H */
