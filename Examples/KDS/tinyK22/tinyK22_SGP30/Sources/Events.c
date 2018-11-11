/* ###################################################################
**     Filename    : Events.c
**     Project     : tinyK22_SGP30
**     Processor   : MK22FN512VLH12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-09-30, 18:31, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
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
#include "Init_Config.h"
#include "PDD_Includes.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Platform.h"
#include "RNG1.h"
#include "gui/lv.h"
#if PL_CONFIG_HAS_SPI
  #include "SPI.h"
#endif

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK22FN512DC12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
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
void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

/*
** ===================================================================
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationTickHook(void)
{
  /* Called for every RTOS tick. */
  /* Write your code here ... */
}

/*
** ===================================================================
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationIdleHook(void)
{
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
  /* Write your code here ... */
}

/*
** ===================================================================
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the FreeRTOS heap.  pvPortMalloc() is called
     internally by FreeRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the FreeRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
#if PL_CONFIG_HAS_SSD1351 //&& !PL_CONFIG_HAS_SD_CARD
  LCD1_OnDataReceived();
#endif
}

/*
** ===================================================================
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyPressed(uint8_t keys)
{
  uint16_t buttonInfo;

  if (keys&1) {
    buttonInfo = LV_BUTTON_SW0 | LV_MASK_PRESSED;
    RNG1_Put(buttonInfo);
  } else if (keys&2) {
    buttonInfo = LV_BUTTON_SW1 | LV_MASK_PRESSED;
    RNG1_Put(buttonInfo);
  }
}

/*
** ===================================================================
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyReleased(uint8_t keys)
{
  uint16_t buttonInfo;

  if (keys&1) {
    buttonInfo = LV_BUTTON_SW0 | LV_MASK_RELEASED;
    RNG1_Put(buttonInfo);
  } else if (keys&2) {
    buttonInfo = LV_BUTTON_SW1 | LV_MASK_RELEASED;
    RNG1_Put(buttonInfo);
  }
}

/*
** ===================================================================
**     Description :
**         Event generated at the time a long key press has been
**         detected.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyPressedLong(uint8_t keys)
{
  uint16_t buttonInfo;

  if (keys&1) {
    buttonInfo = LV_BUTTON_SW0 | LV_MASK_PRESSED_LONG;
    RNG1_Put(buttonInfo);
  } else if (keys&2) {
    buttonInfo = LV_BUTTON_SW1 | LV_MASK_PRESSED_LONG;
    RNG1_Put(buttonInfo);
  }
}

/*
** ===================================================================
**     Description :
**         Event generated after a key has been released (long key
**         press).
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY1_OnKeyReleasedLong(uint8_t keys)
{
  uint16_t buttonInfo;

  if (keys&1) {
    buttonInfo = LV_BUTTON_SW0 | LV_MASK_RELEASED_LONG;
    RNG1_Put(buttonInfo);
  } else if (keys&2) {
    buttonInfo = LV_BUTTON_SW1 | LV_MASK_RELEASED_LONG;
    RNG1_Put(buttonInfo);
  }
}

/*
** ===================================================================
**     Description :
**         Event called when Activate() method is called. This gives an
**         opportunity to the application to synchronize access to a
**         shared bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**         mode            - 0: slow mode, 1: fast mode
**     Returns     : Nothing
** ===================================================================
*/
void SD1_OnActivate(uint8_t mode)
{
  (void)mode;
#if PL_CONFIG_HAS_SPI
  SPI_OnSPIActivate(SPI_BAUD_INDEX_SD_FAST);
#endif
}

/*
** ===================================================================
**     Description :
**         Event called when Deactivate() method is called. This gives
**         an opportunity to the application to synchronize access to a
**         shared bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**         mode            - 0: slow mode, 1: fast mode
**     Returns     : Nothing
** ===================================================================
*/
void SD1_OnDeactivate(uint8_t mode)
{
#if PL_CONFIG_HAS_SPI
  SPI_OnSPIDeactivate((SPI_BaudIndex)mode);
#else
  (void)mode;
#endif
}


/*
** ===================================================================
**     Description :
**         Event called in the event of GetLCD() method called.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_OnGetLCD(void)
{
#if PL_CONFIG_HAS_SPI
  SPI_OnSPIActivate(SPI_BAUD_INDEX_SSD1351);
#endif
}

/*
** ===================================================================
**     Description :
**         Event called in the event of GiveLCD() method called.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_OnGiveLCD(void)
{
#if PL_CONFIG_HAS_SPI
  SPI_OnSPIDeactivate(SPI_BAUD_INDEX_SSD1351);
#endif
}

/*
** ===================================================================
**     Description :
**         Event called from GetDisplay() method. This callback is
**         useful if you want to share the communication to the display
**         (e.g. SPI) with other peripherals, as this gives you a
**         chance to protect the access to it.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GDisp1_OnGetDisplay(void)
{
#if PL_CONFIG_HAS_SPI
  //SPI_OnSPIActivate(SPI_BAUD_INDEX_SSD1351);
#endif
}

/*
** ===================================================================
**     Description :
**         Event called from GetDisplay() method. This callback is
**         useful if you want to share the communication to the display
**         (e.g. SPI) with other peripherals, as this gives you a
**         chance to protect the access to it.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GDisp1_OnGiveDisplay(void)
{
#if PL_CONFIG_HAS_SPI
 // SPI_OnSPIDeactivate(SPI_BAUD_INDEX_SSD1351);
#endif
}

/*
** ===================================================================
**     Description :
**         Called for SPI bus sharing
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_OnGetBus(void)
{
#if PL_CONFIG_HAS_SPI
  SPI_OnSPIActivate(SPI_BAUD_INDEX_SSD1351);
#endif
}

/*
** ===================================================================
**     Description :
**         Used for SPI bus sharing
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_OnGiveBus(void)
{
#if PL_CONFIG_HAS_SPI
  SPI_OnSPIDeactivate(SPI_BAUD_INDEX_SSD1351);
#endif
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
