/**
 * \file
 * \brief Bootloader implementation.
 * \author Erich Styger
 *
 * This module implements a bootloader over SCI/UART with shell interface for the FRDM-KL25Z.
 */

#include "Bootloader.h"
#include "IFsh1.h"
#include "S19.h"
#include "Shell.h"
#include "WAIT1.h"
#include "LEDR.h"
#include "UTIL1.h"
#include "AS1.h"

#define FLASH_PAGE_SIZE             (IntFlashLdd1_ERASABLE_UNIT_SIZE) /* flash page size */
#define BL_FLASH_VECTOR_TABLE       0x0000 /* bootloader vector table in flash */

/* application flash area */
#define MIN_APP_FLASH_ADDRESS        0x4000  /* start of application flash area */
#define MAX_APP_FLASH_ADDRESS       0x1FFFF  /* end of application flash */

#define APP_FLASH_VECTOR_START      0x4000  /* application vector table in flash */
#define APP_FLASH_VECTOR_SIZE       0xc0    /* size of vector table */

#define USE_XON_XOFF  0

/*!
 * \brief Determines if the address is a valid address for the application (outside the bootloader)
 * \param addr Address to check
 * \return TRUE if an application memory address, FALSE otherwise
 */
static bool BL_ValidAppAddress(dword addr) {
  return ((addr>=MIN_APP_FLASH_ADDRESS) && (addr<=MAX_APP_FLASH_ADDRESS)); /* must be in application space */
}

/*!
 * \brief Performs flash programming
 * \param flash_addr Destination address for programming.
 * \param data_addr Pointer to data.
 * \param nofDataBytes Number of data bytes.
 * \return ERR_OK if everything was ok, ERR_FAILED otherwise.
 */
static byte BL_Flash_Prog(dword flash_addr, uint8_t *data_addr, uint16_t nofDataBytes) {
  /* only flash into application space. Everything else will be ignored */
  if(BL_ValidAppAddress(flash_addr)) {
    if (IFsh1_SetBlockFlash((IFsh1_TDataAddress)data_addr, flash_addr, nofDataBytes) != ERR_OK) {
      return ERR_FAILED; /* flash programming failed */
    }
  }
  return ERR_OK;
}

/*!
 * \brief Erases all unprotected pages of flash
 * \return ERR_OK if everything is ok; ERR_FAILED otherwise
 */
static byte BL_EraseApplicationFlash(void) {
  dword addr;

  /* erase application flash pages */
  for(addr=MIN_APP_FLASH_ADDRESS;addr<=MAX_APP_FLASH_ADDRESS;addr+=FLASH_PAGE_SIZE) {
    if(IFsh1_EraseSector(addr) != ERR_OK) { /* Error Erasing Flash */
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

#if USE_XON_XOFF
#define XON  0x11
#define XOFF 0x13

static void SendXONOFF(CLS1_ConstStdIOType *io, uint8_t ch) {
  unsigned char buf[2];
  
  buf[0] = ch;
  buf[1] = '\0';
  CLS1_SendStr(buf, io->stdOut);
}
#endif

static uint8_t BL_onS19Flash(S19_ParserStruct *info) {
  uint8_t res = ERR_OK;
  
  switch (info->currType) {
    case '1':
    case '2':
    case '3':
      if (!BL_ValidAppAddress(info->currAddress)) {
        info->status = S19_FILE_INVALID_ADDRESS;
        res = ERR_FAILED;
      } else {
        /* Write buffered data to Flash */
        if (BL_Flash_Prog(info->currAddress, info->codeBuf, info->codeSize) != ERR_OK) {
          info->status = S19_FILE_FLASH_FAILED;
          res = ERR_FAILED;
        }
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
  return res;
}

/*!
 * \brief With this function, the application can determine if it shall enter bootloader mode to load a new binary.
 * For example, it could check for a button press to enter the bootloader mode.
 * \return TRUE if the bootloader mode shall be started
 */
#include "BL_SW.h"
#include "PORT_PDD.h"

static bool BL_CheckBootloaderMode(void) {
  /* let's check if the user presses the BTLD switch. Need to configure the pin first */
  /* PTB8 as input */
  /* clock all port pins */
  SIM_SCGC5   |= SIM_SCGC5_PORTA_MASK |
             SIM_SCGC5_PORTB_MASK |
             SIM_SCGC5_PORTC_MASK |
             SIM_SCGC5_PORTD_MASK |
             SIM_SCGC5_PORTE_MASK;
  /* Configure pin as input */
#if 0
  /* GPIOB_PDDR: PDD&=~0x0100 */
  GPIOB_PDDR = (uint32_t)((GPIOB_PDDR & (uint32_t)~0x0100UL) | (uint32_t)0x00UL);

  /* Initialization of Port Control register */
  /* PORTB_PCR8: ISF=0,MUX=1 */
  PORTB_PCR8 = (uint32_t)((PORTB_PCR8 & (uint32_t)~0x01000600UL) | (uint32_t)0x0100UL);
#else
  (void)BitIoLdd3_Init(NULL); /* initialize the port pin PTB8 */
  /* enable internal pull-up on PTB8 */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 8, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 8, PORT_PDD_PULL_ENABLE);
  WAIT1_Waitms(5); /* wait get pull-up a chance to pull-up */
#endif
  if (!BL_SW_GetVal()) { /* button pressed (has pull-up!) */
    WAIT1_Waitms(50); /* wait to debounce */
    if (!BL_SW_GetVal()) { /* still pressed */
      return TRUE; /* go into bootloader mode */
    }
  }
  /* BTLD switch not pressed, and we have a valid user application vector */
  return FALSE; /* do not enter bootloader mode */
}

/*!
 * \brief This method is called during startup! It decides if we enter bootloader mode or if we run the application.
 */
void BL_CheckForUserApp(void) {
  uint32_t startup; /* assuming 32bit function pointers */
  
  startup = ((uint32_t*)APP_FLASH_VECTOR_START)[1]; /* this is the reset vector (__startup function) */
  if (startup!=-1 && !BL_CheckBootloaderMode()) { /* we do have a valid application vector? -1/0xfffffff would mean flash erased */
    ((void(*)(void))startup)(); /* Jump to application startup code */
  }
}

static uint8_t BL_EraseAppFlash(CLS1_ConstStdIOType *io) {
  CLS1_SendStr((unsigned char*)"Erasing application flash blocks...", io->stdOut);
  if (BL_EraseApplicationFlash()!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"FAILED!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  CLS1_SendStr((unsigned char*)"done!\r\n", io->stdOut);
  return ERR_OK;
}

static S19_ParserStruct parserInfo;

static uint8_t GetChar(uint8_t *data, void *q) {
  CLS1_ConstStdIOType *io;
  
  io = (CLS1_ConstStdIOType*)q;
  if (!io->keyPressed()) {
#if USE_XON_XOFF
    SendXONOFF(io, XON);
#endif
    while(!io->keyPressed()) {
      /* wait until there is something in the input buffer */
    }
#if USE_XON_XOFF
    SendXONOFF(io, XOFF);
#endif
  }
  io->stdIn(data); /* read character */
  if (*data=='\0') { /* end of input? */
    return ERR_RXEMPTY;
  }
  return ERR_OK;
}

static uint8_t codeBuf[64];

static uint8_t BL_LoadS19(CLS1_ConstStdIOType *io) {
  unsigned char buf[16];
  uint8_t res = ERR_OK;

  /* first, erase flash */
  if (BL_EraseAppFlash(io)!=ERR_OK) {
    return ERR_FAILED;
  }

  /* load S19 file */
  CLS1_SendStr((unsigned char*)"Waiting for the S19 file...", io->stdOut);
  parserInfo.GetCharIterator = GetChar;
  parserInfo.voidP = (void*)io;
  parserInfo.S19Flash = BL_onS19Flash;
  parserInfo.status = S19_FILE_STATUS_NOT_STARTED;
  parserInfo.currType = 0;
  parserInfo.currAddress = 0;
  parserInfo.codeSize = 0;
  parserInfo.codeBuf = codeBuf;
  parserInfo.codeBufSize = sizeof(codeBuf);
  while (AS1_GetCharsInRxBuf()>0) { /* clear any pending characters in rx buffer */
    AS1_ClearRxBuf();
    WAIT1_Waitms(100);
  }
  do {
    if (S19_ParseLine(&parserInfo)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"ERROR!\r\nFailed at address 0x", io->stdErr);
      buf[0] = '\0';
      UTIL1_strcatNum32Hex(buf, sizeof(buf), parserInfo.currAddress);
      CLS1_SendStr(buf, io->stdErr);    
      CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
      res = ERR_FAILED;
      break;
    } else {
      CLS1_SendStr((unsigned char*)"\r\nS", io->stdOut);
      buf[0] = parserInfo.currType;
      buf[1] = '\0';
      CLS1_SendStr(buf, io->stdOut);    
      CLS1_SendStr((unsigned char*)" address 0x", io->stdOut);
      buf[0] = '\0';
      UTIL1_strcatNum32Hex(buf, sizeof(buf), parserInfo.currAddress);
      CLS1_SendStr(buf, io->stdOut);
    }
    if (parserInfo.currType=='7' || parserInfo.currType=='8' || parserInfo.currType=='9') {
      /* end of records */
      break;
    }
  } while (1);
  if (res==ERR_OK) {
    CLS1_SendStr((unsigned char*)"\r\ndone!\r\n", io->stdOut);
  } else {
    while (AS1_GetCharsInRxBuf()>0) {/* clear buffer */
      AS1_ClearRxBuf();
      WAIT1_Waitms(100);
    }
    CLS1_SendStr((unsigned char*)"\r\nfailed!\r\n", io->stdOut);
    /* erase flash again to be sure we do not have illegal application image */
    if (BL_EraseAppFlash(io)!=ERR_OK) {
      res = ERR_FAILED;
    }
  }
  return res;
}

static void BL_PrintHelp(CLS1_ConstStdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"BL", (const unsigned char*)"Group of Bootloader commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  erase", (const unsigned char*)"Erase application flash blocks\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  restart", (const unsigned char*)"Restart application with jump to reset vector\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  load s19", (const unsigned char*)"Load S19 file\r\n", io->stdOut);
}

static void BL_PrintStatus(CLS1_ConstStdIOType *io) {
  unsigned char buf[32];
  
  CLS1_SendStatusStr((unsigned char*)"BL", (const unsigned char*)"\r\n", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum32Hex(buf, sizeof(buf), MIN_APP_FLASH_ADDRESS);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"..0x");
  UTIL1_strcatNum32Hex(buf, sizeof(buf), MAX_APP_FLASH_ADDRESS);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  App Flash", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"  @0x");
  UTIL1_strcatNum32Hex(buf, sizeof(buf), MIN_APP_FLASH_ADDRESS);
  CLS1_SendStatusStr(buf, (unsigned char*)"", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum32Hex(buf, sizeof(buf), *((uint32_t*)MIN_APP_FLASH_ADDRESS));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" 0x");
  UTIL1_strcatNum32Hex(buf, sizeof(buf), *((uint32_t*)MIN_APP_FLASH_ADDRESS+4));
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStr(buf, io->stdOut);
}

byte BL_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "BL help")==0) {
    BL_PrintHelp(io);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "BL status")==0)) {
    BL_PrintStatus(io);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, "BL erase")==0)) {
    *handled = TRUE;
    return BL_EraseAppFlash(io);
  } else if ((UTIL1_strcmp((char*)cmd, "BL restart")==0)) {
    uint32_t startup;

    *handled = TRUE;
    startup = ((uint32_t*)BL_FLASH_VECTOR_TABLE)[1];
    ((void(*)(void))startup)(); /* Jump to startup code */
    /* will never get here! */
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, "BL load s19")==0)) {
    *handled = TRUE;
    return BL_LoadS19(io);
  }
  return ERR_OK; /* no error */
}

void BL_Run(void) {
  SHELL_Init();
  for(;;) {
    SHELL_Parse();
    LEDR_Neg();
    WAIT1_Waitms(100);
  }
}
