/* ###################################################################
**     Filename    : Events.h
**     Project     : tinyK20_Demo
**     Processor   : MK20DX128VFT5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-19, 16:16, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "TmDt1.h"
#include "RTC1.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CLS1.h"
#include "HF1.h"
#include "KIN1.h"
#include "PTC.h"
#include "MINI1.h"
#include "SYS1.h"
#include "RTT1.h"
#include "XF1.h"
#include "MCUC1.h"
#include "GI2C1.h"
#include "I2CSPY1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "BitIoLdd3.h"
#include "SCL1.h"
#include "BitIoLdd4.h"
#include "OW1.h"
#include "DQ1.h"
#include "BitIoLdd5.h"
#include "TU1.h"
#include "OutputRB1.h"
#include "InputRB1.h"
#include "TimeRB1.h"
#include "ProgramRB1.h"
#include "DbgRd1.h"
#include "BitIoLdd6.h"
#include "DS1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pxTask          - Task handle
**       * pcTaskName      - Pointer to task name
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationTickHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationIdleHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationIdleHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationMallocFailedHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TmDt1_OnTimeSet(uint8_t hour, uint8_t minute, uint8_t second, uint8_t hSecond);
/*
** ===================================================================
**     Event       :  TmDt1_OnTimeSet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         Called in the event of a new time set
**     Parameters  :
**         NAME            - DESCRIPTION
**         hour            - The new hour
**         minute          - The new minute
**         second          - The new second
**         hSecond         - The new 0.01 second part
**     Returns     : Nothing
** ===================================================================
*/

void TmDt1_OnDateSet(uint8_t day, uint8_t month, uint16_t year);
/*
** ===================================================================
**     Event       :  TmDt1_OnDateSet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         called in the event of a date set
**     Parameters  :
**         NAME            - DESCRIPTION
**         day             - the new day
**         month           - the new month
**         year            - the new year
**     Returns     : Nothing
** ===================================================================
*/

void TmDt1_OnTimeGet(uint8_t *hour, uint8_t *minute, uint8_t *second, uint8_t *hSecond);
/*
** ===================================================================
**     Event       :  TmDt1_OnTimeGet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         Called in the event of a new time get
**     Parameters  :
**         NAME            - DESCRIPTION
**       * hour            - Pointer to the hour, can be overwritten
**                           in the event routine.
**       * minute          - Pointer to the minute, can be
**                           overwritten in the event routine.
**       * second          - Pointer to the second, can be
**                           overwritten in the event routine.
**       * hSecond         - Pointer to the 0.01 second, can be
**                           overwritten in the event routine.
**     Returns     : Nothing
** ===================================================================
*/

void TmDt1_OnDateGet(uint8_t *day, uint8_t *month, uint16_t *year);
/*
** ===================================================================
**     Event       :  TmDt1_OnDateGet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         called in the event of a date get
**     Parameters  :
**         NAME            - DESCRIPTION
**       * day             - Pointer to the day, can be written in the
**                           event routine.
**       * month           - Pointer to the month, can be written
**                           in the event routine.
**       * year            - Pointer to the year, can be written in
**                           the event routine.
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  Cpu_OnLLSWakeUpINT (module Events)
**
**     Component   :  Cpu [MK20DX128FT5]
*/
/*!
**     @brief
**         This event is called when Low Leakage WakeUp interrupt
**         occurs. LLWU flags indicating source of the wakeup can be
**         obtained by calling the [GetLLSWakeUpFlags] method. Flags
**         indicating the external pin wakeup source are automatically
**         cleared after this event is executed. It is responsibility
**         of user to clear flags corresponding to internal modules.
**         This event is automatically enabled when [LLWU interrupt
**         request] is enabled.
*/
/* ===================================================================*/
void Cpu_OnLLSWakeUpINT(void);

void SM1_OnFullRxBuf(void);
/*
** ===================================================================
**     Event       :  SM1_OnFullRxBuf (module Events)
**
**     Component   :  SM1 [SynchroMaster]
**     Description :
**         This event is called when the input buffer is full, i.e.
**         after reception of the last character that was successfully
**         placed into input buffer.
**         This event is available only when the <Interrupt
**         service/event> property is enabled and the <Input buffer
**         size> property is set to non-zero value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SM1_OnFreeTxBuf(void);
/*
** ===================================================================
**     Event       :  SM1_OnFreeTxBuf (module Events)
**
**     Component   :  SM1 [SynchroMaster]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**         This event is available only when the <Interrupt
**         service/event> property is enabled and the <Output buffer
**         size> property is set to non-zero value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void DS1_OnError(OW1_Error error);
/*
** ===================================================================
**     Event       :  DS1_OnError (module Events)
**
**     Component   :  DS1 [DS18B20]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**       * error           - 
**     Returns     : Nothing
** ===================================================================
*/
void DS1_OnTemperatureGet(uint8_t sensor_index, int32_t temperature);
/*
** ===================================================================
**     Event       :  DS1_OnTemperatureGet (module Events)
**
**     Component   :  DS1 [DS18B20]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**       * sensor_index    - 
**       * temperature     - 
**     Returns     : Nothing
** ===================================================================
*/
void DS1_OnRomRead(uint8_t sensor_index, uint8_t *rom_code);
/*
** ===================================================================
**     Event       :  DS1_OnRomRead (module Events)
**
**     Component   :  DS1 [DS18B20]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**       * sensor_index    - 
**       * rom_code        - 
**     Returns     : Nothing
** ===================================================================
*/
void OW1_OnProgramEvent(uint8_t key);
/*
** ===================================================================
**     Event       :  OW1_OnProgramEvent (module Events)
**
**     Component   :  OW1 [OneWire]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         key4            - Key to identify the source of the event
**     Returns     : Nothing
** ===================================================================
*/

void OW1_OnWaitEnd(uint8_t key2);
/*
** ===================================================================
**     Event       :  OW1_OnWaitEnd (module Events)
**
**     Component   :  OW1 [OneWire]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         key2            - Key to identificate the source of the
**                           event.
**     Returns     : Nothing
** ===================================================================
*/
void DS1_OnAllConverted(void);
/*
** ===================================================================
**     Event       :  DS1_OnAllConverted (module Events)
**
**     Component   :  DS1 [DS18B20]
**     Description :
**         event called after all sensors have been converted
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
