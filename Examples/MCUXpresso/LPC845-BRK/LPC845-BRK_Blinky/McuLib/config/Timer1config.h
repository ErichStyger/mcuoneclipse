/**
 * \file
 * \brief Configuration header file for SDK_Timer
 *
 * This header file is used to configure settings of the SDK Timer module.
 */
#ifndef __Timer1_CONFIG_H
#define __Timer1_CONFIG_H

#ifndef Timer1_CONFIG_TIMER_NAME
  #define Timer1_CONFIG_TIMER_NAME       TPM0
    /*!< name of TIMER, is pointer to TPM_Type */
#endif

#ifndef Timer1_CONFIG_TIMER_INIT_PERIOD_US
  #define Timer1_CONFIG_TIMER_INIT_PERIOD_US       1000
    /*!< Initial period in micro-seconds */
#endif

#ifndef Timer1_CONFIG_TIMER_INIT_ENABLE_TIMER
  #define Timer1_CONFIG_TIMER_INIT_ENABLE_TIMER       (0)
    /*!< 1: Enable the timer in Init(); 0: Timer is disabled in Init() */
#endif

#ifndef Timer1_CONFIG_TIMER_INIT_ENABLE_IRQ
  #define Timer1_CONFIG_TIMER_INIT_ENABLE_IRQ       (1)
    /*!< 1: Enable NVIC IRQ for the timer in Init(); 0: Timer IRQ is disabled in Init() */
#endif

#ifndef Timer1_CONFIG_TIMER_INIT_ENABLE_OVERFLOW_IRQ
  #define Timer1_CONFIG_TIMER_INIT_ENABLE_OVERFLOW_IRQ       (1)
    /*!< 1: Enable the timer overflow interrupt in Init(); 0: Timer overflow interrupt is disabled in Init() */
#endif

#define Timer1_CONFIG_TIMER_IRQ                             TPM0##_IRQn
  /*!< Interrupt vector number */

#define Timer1_CONFIG_TIMER_IRQ_HANDLER_NAME                TPM0##_IRQHandler
  /*!< Interrupt handler name */

#define Timer1_CONFIG_TIMER_IRQ_PRIORITY                    0
  /*!< NVIC timer IRQ priority, unshifted */

#endif /* __Timer1_CONFIG_H */
