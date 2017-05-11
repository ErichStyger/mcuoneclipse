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
void DS1_OnTemperatureGet(uint8_t sensor_index, int32_t temperature)
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
void DS1_OnRomRead(uint8_t sensor_index, uint8_t *rom_code)
{
	/* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  InputRB1_OnBufferFull (module Events)
**
**     Component   :  InputRB1 [RingBuffer]
**     Description :
**         Called in the event of buffer full.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void InputRB1_OnBufferFull(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  InputRB1_OnBufferEmpty (module Events)
**
**     Component   :  InputRB1 [RingBuffer]
**     Description :
**         Called in the event of last item has been removed from
**         buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void InputRB1_OnBufferEmpty(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  InputRB1_OnItemPut (module Events)
**
**     Component   :  InputRB1 [RingBuffer]
**     Description :
**         Optional event created for every item added with the Put()
**         method.
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - item which gets added
**     Returns     : Nothing
** ===================================================================
*/
void InputRB1_OnItemPut(InputRB1_ElementType elem)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  InputRB1_OnItemGet (module Events)
**
**     Component   :  InputRB1 [RingBuffer]
**     Description :
**         Optional event created for every item removed with the Get()
**         method.
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - item which gets removed
**     Returns     : Nothing
** ===================================================================
*/
void InputRB1_OnItemGet(InputRB1_ElementType elem)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  InputRB1_OnClear (module Events)
**
**     Component   :  InputRB1 [RingBuffer]
**     Description :
**         Optional event called in case of Clear() call.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void InputRB1_OnClear(void)
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
