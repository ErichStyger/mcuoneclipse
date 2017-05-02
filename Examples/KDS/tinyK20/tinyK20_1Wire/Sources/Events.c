/* ###################################################################
**     Filename    : Events.c
**     Project     : tinyK20_Blinky
**     Processor   : MK20DX128VFT5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-11, 13:30, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
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
**     Component   :  Cpu [MK20DX128EX5]
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
void OW1_OnProgramEvent(uint8_t key4)
{
  /* Write your code here ... */
}

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
void OW1_OnWaitEnd(uint8_t key2)
{
  /* Write your code here ... */
}

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
void DS1_OnError(OW1_Error error)
{
  /* Write your code here ... */
}

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
void DS1_OnTemperatureGet(int32_t temperature)
{
	/* Write your code here ... */
}

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
void DS1_OnRomRead(uint8_t *rom_code)
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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
