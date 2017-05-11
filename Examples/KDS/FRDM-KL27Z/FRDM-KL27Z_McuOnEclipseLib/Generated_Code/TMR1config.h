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
/*TPM2_IRQn*/

#endif /* __TMR1_CONFIG_H */
