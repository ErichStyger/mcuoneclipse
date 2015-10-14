/******************************************************************************
*                                                  
*  (c) copyright Freescale Semiconductor 2008
*  ALL RIGHTS RESERVED
*
*  File Name: Bootloader.C
*                                                                          
*  Purpose: This file is for a USB Mass-Storage Device bootloader.  This file 
*           has the main routine for the bootloader
*                                                                          
*  Assembler:  Codewarrior for Microcontrollers V6.3
*                                            
*  Version:  1.7
*                                                                          
*                                                                          
*  Author: Derek Snell                             
*                                                                                       
*  Location: Indianapolis, IN. USA                                            
*                                                                                  
* UPDATED HISTORY:
*
* REV   YYYY.MM.DD  AUTHOR        DESCRIPTION OF CHANGE
* ---   ----------  ------        --------------------- 
* 1.7   2010.02.07  Erich Styger  Updates for TWR-LCD
* 1.6	  2009.11.18  Derek Snell   Initialized vCBWBuf_flag to 0.
* 1.5   2009.04.07  Derek Snell   Made delay longer when USB re-enumerates to help with some Windows
* 1.4   2008.11.24  Derek Snell   Added EP0 stall after GetMAXLUN request to signify only one LUN
* 1.3   2008.09.17  Derek Snell   After file written, force re-enumeration to update file displayed to host
* 1.2   2008.08.26  Derek Snell   Fix MaxLUN response so only 1 drive enumerates
*                   & Jose Ruiz   Added proper Endpoint 0 stalls
*                                 Stopped accepting write data from host after successful S19 transfer
* 1.1   2008.08.14  Derek Snell   Modified to improve enumeration delay
* 1.0   2008.06.10  Derek Snell   Initial version
* 
*
******************************************************************************/                                                                        
/* Freescale  is  not  obligated  to  provide  any  support, upgrades or new */
/* releases  of  the Software. Freescale may make changes to the Software at */
/* any time, without any obligation to notify or provide updated versions of */
/* the  Software  to you. Freescale expressly disclaims any warranty for the */
/* Software.  The  Software is provided as is, without warranty of any kind, */
/* either  express  or  implied,  including, without limitation, the implied */
/* warranties  of  merchantability,  fitness  for  a  particular purpose, or */
/* non-infringement.  You  assume  the entire risk arising out of the use or */
/* performance of the Software, or any systems you design using the software */
/* (if  any).  Nothing  may  be construed as a warranty or representation by */
/* Freescale  that  the  Software  or  any derivative work developed with or */
/* incorporating  the  Software  will  be  free  from  infringement  of  the */
/* intellectual property rights of third parties. In no event will Freescale */
/* be  liable,  whether in contract, tort, or otherwise, for any incidental, */
/* special,  indirect, consequential or punitive damages, including, but not */
/* limited  to,  damages  for  any loss of use, loss of time, inconvenience, */
/* commercial loss, or lost profits, savings, or revenues to the full extent */
/* such  may be disclaimed by law. The Software is not fault tolerant and is */
/* not  designed,  manufactured  or  intended by Freescale for incorporation */
/* into  products intended for use or resale in on-line control equipment in */
/* hazardous, dangerous to life or potentially life-threatening environments */
/* requiring  fail-safe  performance,  such  as  in the operation of nuclear */
/* facilities,  aircraft  navigation  or  communication systems, air traffic */
/* control,  direct  life  support machines or weapons systems, in which the */
/* failure  of  products  could  lead  directly to death, personal injury or */
/* severe  physical  or  environmental  damage  (High  Risk Activities). You */
/* specifically  represent and warrant that you will not use the Software or */
/* any  derivative  work of the Software for High Risk Activities.           */
/* Freescale  and the Freescale logos are registered trademarks of Freescale */
/* Semiconductor Inc.                                                        */ 
/*****************************************************************************/

#include "platform.h"

#if PL_IS_BOOTLOADER || PL_HAS_BOOTLOADER

#include <hidef.h> /* for DisableInterrupts */
#include "bootloader.h"
#include "startcf.h"
#include "WAIT1.h"
#include "JM_ELE.h"
#include "UTIL1.h"

#ifdef CPU_DERIVATIVE_MCF51JM128
  #define CF_CORE
  #define MIN_RAM1_ADDRESS            0x800000
  #define MAX_RAM1_ADDRESS            0x803FFF
  #define MIN_FLASH1_ADDRESS          0x000000
  #define MAX_FLASH1_ADDRESS          0x01FFFF
  /* bootloader is in 0x410...0x47FF */
  #define FLASH_PROTECTED_ADDRESS     0x0047FF /* flash below this address will be protected (e.g. bootloader) */
  #define REDIRECT_VECTORS            0x004800
  #define USER_ENTRY_ADDRESS          0x004A00 /* stub code to _Startup */
  #define BL_APP_RAM_VECTOR_ADDRESS   0x800000  /* application vectors in RAM */
  #define FLASH_PAGE_SIZE             1024
#endif

#if PL_IS_BOOTLOADER

#include "IFsh1.h"
#include "BLUSB1.h"
#include "S191.h"
#include "BLD1.h"
#include "BuzzerPPG.h"
#if PL_BOOTLOADER_LCD
  #include "LCD1.h"
  #include "FDisp1.h"
  #include "Helv08n.h"
  #include "GDisp1.h"
#endif

#if PL_BOOTLOADER_LCD
#define TEXT_TOP_BORDER   10 /* pixels from the top border */
#define TEXT_LEFT_BORDER   5 /* pixels from the left border */
static void PrintLCDText(byte line, char *txt) {
  FDisp1_PixelDim x, y;
  FDisp1_Font *font;
  
  if (JM_ELE_GetVal()!=0) { /* JM128 has access to the LCD */
    font = Helv08n_GetFont();
    x = TEXT_LEFT_BORDER;
    y = (FDisp1_PixelDim)(line*Helv08n_GetBoxHeight()+TEXT_TOP_BORDER);
    FDisp1_WriteString(txt, GDisp1_COLOR_BLACK, &x, &y, font);
  }
}
#endif

#if PL_HAS_HW_SOUNDER
static void Beep(byte nofBeeps) {
  while(nofBeeps>0) {
    BuzzerPPG_SetFreqHz(1000);
    BuzzerPPG_Enable();
    WAIT1_Waitms(250);
    BuzzerPPG_Disable();
    nofBeeps--;
  }
}
#endif

static bool BL_flashErased;

/********************************************************************
*     Flash subroutines
********************************************************************/
/* dword(32bit) programming */
static byte BL_Flash_Prog(dword flash_addr, dword data_addr, byte number) {
  /* only flash into application space. Everything else will be ignored */
#ifdef S08_CORE
  if (   ((flash_addr >= MIN_FLASH2_ADDRESS) && (flash_addr <= MAX_FLASH2_ADDRESS)) 
      || ((flash_addr >= MIN_FLASH1_ADDRESS) && (flash_addr < FLASH_PROTECTED_ADDRESS))
     ) 
  {
#elif defined CF_CORE
  if((flash_addr > FLASH_PROTECTED_ADDRESS) && (flash_addr <= MAX_FLASH1_ADDRESS)) {
#endif /* S08_CORE */
    if (IFsh1_SetBlockFlash((IFsh1_TDataAddress)data_addr, flash_addr, (word)(number*4)) != ERR_OK) {
      return ERR_FAILED; /* flash programming failed */
    }
  }
  return ERR_OK;
}
    
static byte Flash_Verify(dword dst_addr, dword data_addr, byte length) {
  do {
    if(*(dword *)dst_addr != *(dword *)data_addr) { /* compare two values */
      return ERR_FAILED;
    } 
    dst_addr +=4;
    data_addr +=4; 
  } while(--length);
  return 0x01;
}

/*********************************************************
* Name: EraseFlash
* Desc: Erases all unprotected pages of flash
* Parameter: None
* Return: None
**********************************************************/
static byte BL_EraseFlash(void) {
  dword addr;

  /* erase each page of flash */
  for(addr=MIN_FLASH1_ADDRESS;addr<=MAX_FLASH1_ADDRESS;addr+=FLASH_PAGE_SIZE) {
    if(addr > FLASH_PROTECTED_ADDRESS) {
      if(IFsh1_EraseSector(addr) != ERR_OK) {
        /* Error Erasing Flash */
        return ERR_FAILED;
      }
    } 
  }
  return ERR_OK;
}

/*********************************************************
* Name: CheckAddressValid
* Desc: Checks if Address of S-Record is valid for device
* Parameter: Address
* Return: unsigned char, TRUE or FALSE if valid
**********************************************************/
static bool BL_CheckAddressValid(dword Address) {
  if((Address >= MIN_FLASH1_ADDRESS) && (Address <= MAX_FLASH1_ADDRESS)) {
    return TRUE;
  } else if ((Address >= MIN_RAM1_ADDRESS) && (Address <= MAX_RAM1_ADDRESS)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void BL_OnSRecord(byte *returnCode, byte type, dword addr, byte *dataBuf, byte dataBufSize, void *data) {
  switch (type) {
    case '1':
    case '2':
    case '3':
      if (!BL_CheckAddressValid(addr)) {
        *((S191_FileStatus*)data) = S191_FILE_INVALID_ADDRESS;
        *returnCode = ERR_FAILED;
        return;
      }
      if (!BL_flashErased) {
        if (BL_EraseFlash()!=ERR_OK) {
          *((S191_FileStatus*)data) = S191_FILE_ERASE_FAILED;
          *returnCode = ERR_FAILED;
          return;
        }
        BL_flashErased = TRUE;
      }
      /* Write buffered data to Flash */
      if (BL_Flash_Prog(addr, (dword) dataBuf, dataBufSize) != ERR_OK) {
        *((S191_FileStatus*)data) = S191_FILE_FLASH_FAILED;
        *returnCode = ERR_FAILED;
        return;
      }
      break;
    case '7':
    case '8':
    case '9': /* S7, S8 or S9 mark the end of the block/s-record file */
      break;
    case '0':
    case '4':
    case '5':
    case '6':
    default:
      break;
  } /* switch */
  *returnCode = ERR_OK;
}

void BL_Bootloader(void) {
  S191_FileStatus fileStatus;
  
  DisableInterrupts;
#if PL_HAS_HW_SOUNDER
  Beep(1);
#endif
#if PL_BOOTLOADER_LCD
  if (JM_ELE_GetVal()!=0) {
    /* JM_ELE switch is off: the JM128 is controlling the LCD */
    LCD1_Init();
    LCD1_Clear();
  }
  PrintLCDText(0, "Bootloader mode: waiting for S19 file...");
#endif
  BLUSB1_InitUSB();
  
  fileStatus = S191_FILE_STATUS_NOT_STARTED;
  for(;;) {
    BLUSB1_PollAndProcessUSB(&fileStatus); /* Poll USB device for any input device */
    if(fileStatus==S191_FILE_STATUS_READING) {
    #if PL_BOOTLOADER_LCD
      PrintLCDText(1, "Loading S19 file...");
    #endif
      BL_flashErased = FALSE;
      BLUSB1_ReadAndProcessS19(&fileStatus);
      switch(fileStatus) {
        case S191_FILE_STATUS_FINISHED:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "Loading successful!\nYou can reset the board now.");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(1);
          #endif
          break;
        case S191_FILE_ERASE_FAILED:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "*** Flash erase error! ***");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(4);
          #endif
          break;
        case S191_FILE_FLASH_FAILED:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "*** Flash programming error! ***");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(6);
          #endif
          break;
        default:
          #if PL_BOOTLOADER_LCD
          PrintLCDText(2, "*** Error processing file! ***");
          #endif
          #if PL_HAS_HW_SOUNDER
          Beep(8);
          #endif
          break;
      } /* switch */
    } /* if */    
  } /* for */
}
#endif /* PL_HAS_BOOTLOADER */

void BL_CheckForUserApp(void) {
  if((*((word*)(USER_ENTRY_ADDRESS+4))!=0xffff)) { /* we do have a valid application vector */
    volatile int i;
    
    /* let's check if the user presses the BTLD switch. This one is connected to the IRQ pin */
    IRQSC = 0x51;  /* IRQ on low level, pull up enabled, IRQ Pull Device disabled */
    IRQSC_IRQACK = 0x01; /* acknowledge any pending interrupt (just in case) */
    for(i=0; i<8000; i++) { /* wait some time */
      if (IRQSC_IRQF) { /* poll flag: if 1 then user has pressed button */
        IRQSC_IRQACK = 0x01; /* acknowledge interrupt */
        return; /* this will continue execution towards the bootloader */
      }
    } /* for */
    /* BTLD switch not pressed, and we have a valid user application vector */
    asm (JMP USER_ENTRY_ADDRESS);  /* Jump to user code */
  }
}

const byte _UserEntry[] @USER_ENTRY_ADDRESS = {
  0x4E,
  0x71,
  0x4E,
  0xF9 /* asm NOP(0x4E71), asm JMP(0x4EF9) */           
};

void  (*const _UserEntry2[])()@(USER_ENTRY_ADDRESS+4) = {
#if PL_HAS_BOOTLOADER
  _startup, /* this will be reflashed by the bootloader with the application _startup() */
#elif PL_IS_BOOTLOADER
  (void*)0xffffffff /*_startup*/ /* this will be reflashed by the bootloader with the application _startup() */
#endif
};

#if PL_HAS_BOOTLOADER
void BL_RedirectUserVectors(void) {
  /* !! This section needs to be here to redirect interrupt vectors !! */
  dword *pdst,*psrc;
  word i;
  
  asm (move.l  #BL_APP_RAM_VECTOR_ADDRESS,d0);
  asm (movec   d0,vbr);
  
  pdst=(dword*)BL_APP_RAM_VECTOR_ADDRESS; /* copy to RAM */
  psrc=(dword*)REDIRECT_VECTORS; /* The vector table has been placed here */
  
  for (i=0;i<111;i++,pdst++,psrc++) {
    *pdst=*psrc;
  }
}
#endif /* PL_HAS_BOOTLOADER */

#endif /* PL_IS_BOOTLOADER || PL_HAS_BOOTLOADER */
