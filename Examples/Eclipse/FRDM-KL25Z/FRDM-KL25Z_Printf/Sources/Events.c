/* ###################################################################
**     Filename    : Events.c
**     Project     : FRDM-KL25Z_Adafruit_GPS
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-05-20, 15:16, # CodeGen: 15
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         GPS_OnError                          - void GPS_OnError(void);
**         GPS_OnRxChar                         - void GPS_OnRxChar(void);
**         GPS_OnTxChar                         - void GPS_OnTxChar(void);
**         GPS_OnFullRxBuf                      - void GPS_OnFullRxBuf(void);
**         GPS_OnFreeTxBuf                      - void GPS_OnFreeTxBuf(void);
**         FRTOS1_vApplicationStackOverflowHook - void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName);
**         FRTOS1_vApplicationTickHook          - void FRTOS1_vApplicationTickHook(void);
**         FRTOS1_vApplicationMallocFailedHook  - void FRTOS1_vApplicationMallocFailedHook(void);
**         Cpu_OnNMIINT                         - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */


/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
