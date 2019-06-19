/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KE06Z_FlashPrg
**     Processor   : MKE06Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-06-19, 12:24, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "MCUC1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#define NVMC_FLASH_START_ADDR    0x1F000 /* NVRM_Config, start address of configuration data in flash */
#define NVMC_FLASH_ERASED_UINT8  0xFF
#define NVMC_FLASH_ERASED_UINT16 0xFFFF

#define NVMC_DATA_START_ADDR  (NVMC_FLASH_START_ADDR)
#define NVMC_DATA_SIZE        (128) /* maximum data size in bytes */
#define NVMC_DATA END_ADDR    (NVMC_DATA_START_ADDR+NVMC_DATA_SIZE)

static bool isErased(uint8_t *ptr, int nofBytes) {
  while (nofBytes>0) {
    if (*ptr!=0xFF) {
      return FALSE; /* byte not erased */
    }
    ptr++;
    nofBytes--;
  }
  return TRUE;
}

uint8_t NVMC_SaveData(void *data, uint16_t dataSize) {
  if (dataSize>NVMC_DATA_SIZE) {
    return ERR_OVERFLOW;
  }
  return IFsh1_SetBlockFlash(data, (IFsh1_TAddress)(NVMC_DATA_START_ADDR), dataSize);
}

void *NVMC_GetData(void) {
  if (isErased((uint8_t*)NVMC_DATA_START_ADDR, NVMC_DATA_SIZE)) {
    return NULL;
  }
  return (void*)NVMC_DATA_START_ADDR;
}


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  for(;;) {
    uint8_t *ptr, res;

    ptr = NVMC_GetData();
    if (ptr==NULL) { /* data area erased */
      res = NVMC_SaveData("hello world", sizeof("hello world"));
      if (res!=ERR_OK) {
        for(;;) {} /* error */
      }
    }
    LEDB_Neg();
    WAIT1_Waitms(100);
  }
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
