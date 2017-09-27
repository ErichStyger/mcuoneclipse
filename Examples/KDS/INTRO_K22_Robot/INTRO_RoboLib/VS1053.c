/*
 * VS1053.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_MUSIC_SHIELD
#include "VS1053.h"
#include "MCS.h" /* low active chip select */
#include "DCS.h" /* data control select */
#include "DREQ.h" /* data request, HIGH means I can send data */
#include "SM1.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "FAT1.h"
#include "FRTOS1.h"
#include "SM1.h"
#include "SPI.h"

#define VS_LDD_SPI  0  /* if using logical device driver */

#if !VS_LDD_SPI
static uint8_t rxDummy; /* dummy byte if we do not need the result. Needed to read from SPI register. */
#define SD1_SPI_WRITE(write)            \
   { \
     while(SM1_SendChar(write)!=ERR_OK) {} \
     while(SM1_RecvChar(&rxDummy)!=ERR_OK) {} \
   }
#define SD1_SPI_WRITE_READ(write, readP) \
   { \
     while(SM1_SendChar(write)!=ERR_OK) {} \
     while(SM1_RecvChar(readP)!=ERR_OK) {} \
   }
#endif

/* macros to select device and to switch between data and control mode */
#define VS_CONTROL_MODE_ON()    DCS_SetVal(); MCS_ClrVal()
#define VS_CONTROL_MODE_OFF()   MCS_SetVal()
#define VS_DATA_MODE_ON()       MCS_SetVal(); DCS_ClrVal()
#define VS_DATA_MODE_OFF()      DCS_SetVal()

#define VS_DATA_SIZE_BYTES      32  /* always 32 bytes of data */
#define VS_BAUD_SPEED_INDEX     3

#if VS_LDD_SPI
static volatile bool VS_SPIDataReceivedFlag = FALSE;
#endif

void VS_OnSPIActivate(void) {
  SPI_OnSPIActivate(SPI_BAUD_INDEX_VS1053); /* semaphore */
  SM1_Disable();
  (void)SM1_SetIdleClockPolarity(0);    /* low idle clock polarity */
  (void)SM1_SetShiftClockPolarity(0);   /* shift clock polarity: falling edge */
  SM1_SetBaudRateMode(VS_BAUD_SPEED_INDEX);
  SM1_Enable();
}

void VS_OnSPIDeactivate(void) {
  SPI_OnSPIDeactivate(SPI_BAUD_INDEX_VS1053); /* semaphore */
}

#if VS_LDD_SPI
void VS_OnSPIBlockReceived(void) {
  VS_SPIDataReceivedFlag = TRUE;
}
#endif

static void VS_SPI_WRITE(unsigned char write) {
#if VS_LDD_SPI
  unsigned char dummy;

  VS_SPIDataReceivedFlag = FALSE;
  (void)SM1_ReceiveBlock(SM1_DeviceData, &dummy, sizeof(dummy));
  (void)SM1_SendBlock(SM1_DeviceData, &write, sizeof(write));
  while(!VS_SPIDataReceivedFlag){}
#else
  SD1_SPI_WRITE(write);
#endif
}

static void VS_SPI_WRITE_READ(unsigned char write, unsigned char *readP) {
#if VS_LDD_SPI
  VS_SPIDataReceivedFlag = FALSE;
  (void)SM1_ReceiveBlock(SM1_DeviceData, readP, 1);
  (void)SM1_SendBlock(SM1_DeviceData, &write, 1);
  while(!VS_SPIDataReceivedFlag){}
#else
  SD1_SPI_WRITE_READ(write, readP);
#endif
}

bool VS_Ready(void) {
  return DREQ_GetVal()!=0; /* HIGH: ready to receive data */
}

uint8_t VS_WriteRegister(uint8_t reg, uint16_t value) {
  VS_OnSPIActivate();
  VS_CONTROL_MODE_ON();
  while(!VS_Ready()) {
    /* wait until pin goes high so we know it is ready */
  }
  /* send instruction byte, address byte and 16bit data word */
  VS_SPI_WRITE(0x02); /* write instruction */
  VS_SPI_WRITE(reg);
  VS_SPI_WRITE(value>>8); /* high byte first */
  while(!VS_Ready()) {
    /* wait until pin goes high so we know it is ready */
  }
  VS_SPI_WRITE(value&0xff); /* low byte */
  while(!VS_Ready()) {
    /* wait until pin goes high so we know it is ready */
  }
  VS_CONTROL_MODE_OFF();
  VS_OnSPIDeactivate();
  return ERR_OK;
}

uint8_t VS_ReadRegister(uint8_t reg, uint16_t *value) {
  uint8_t val0, val1;

  VS_OnSPIActivate();
  VS_CONTROL_MODE_ON();
  while(!VS_Ready()) {
    /* wait until pin goes high so we know it is ready */
  }
  /* send instruction byte, address byte and 16bit data word */
  VS_SPI_WRITE(0x03); /* read instruction */
  VS_SPI_WRITE(reg);
  VS_SPI_WRITE_READ(0xff, &val0); /* read first byte */
  while(!VS_Ready()) {
    /* wait until pin goes high so we know it is ready */
  }
  VS_SPI_WRITE_READ(0xff, &val1); /* read second byte */
  while(!VS_Ready()) {
    /* wait until pin goes high so we know it is ready */
  }
  VS_CONTROL_MODE_OFF();
  *value = (val0<<8)|val1;
  VS_OnSPIDeactivate();
  return ERR_OK;
}

static uint8_t VS_SendZeroes(size_t nof) {
  size_t chunk;

  VS_OnSPIActivate();
  VS_DATA_MODE_ON();
  while(nof!=0) {
    while(!VS_Ready()) {
      /* wait until pin goes high so we know it is ready */
    }
    if (nof>VS_DATA_SIZE_BYTES) { /* max 32 bytes */
      chunk = VS_DATA_SIZE_BYTES;
    } else {
      chunk = nof;
    }
    nof -= chunk;
    while(chunk>0) {
      VS_SPI_WRITE(0);
      chunk--;
    }
  }
  VS_DATA_MODE_OFF();
  VS_OnSPIDeactivate();
  return ERR_OK;
}

uint8_t VS_SetVolume(uint16_t leftright) {
  /* max volume: 0x0000, total silence: 0xFEFE, 0xFFFF analog power down */
  return VS_WriteRegister(VS_VOL, leftright);
}

uint8_t VS_SendData(uint8_t *data, size_t dataSize) {
  if (dataSize!=VS_DATA_SIZE_BYTES) {
    return ERR_FAULT; /* need 32 bytes! */
  }
  VS_OnSPIActivate();
  VS_DATA_MODE_ON();
  while(dataSize>0) {
    while(!VS_Ready()) {
      /* wait until pin goes high so we know it is ready */
    }
    VS_SPI_WRITE(*data++);
    dataSize--;
  }
  VS_DATA_MODE_OFF();
  VS_OnSPIDeactivate();
  return ERR_OK;
}

uint8_t VS_StartSong(void) {
  return VS_SendZeroes(10);
}

uint8_t VS_StopSong(void) {
  return VS_SendZeroes(2048);
}

uint8_t VS_PlaySong(const uint8_t *fileName, const CLS1_StdIOType *io) {
  UINT bytesRead;
  uint8_t readBuf[32];
  uint8_t res = ERR_OK;
  static FIL fp;

  if (io!=NULL) {
    CLS1_SendStr("Playing file '", io->stdOut);
    CLS1_SendStr(fileName, io->stdOut);
    CLS1_SendStr("'\r\n", io->stdOut);
  }
  if (FAT1_open(&fp, fileName, FA_READ)!=FR_OK) {
    if (io!=NULL) {
      CLS1_SendStr("ERR: Failed to open song file\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  for(;;) { /* breaks */
    bytesRead = 0;
    if (FAT1_read(&fp, readBuf, sizeof(readBuf), &bytesRead)!=FR_OK) {
      if (io!=NULL) {
        CLS1_SendStr("ERR: Failed to read file\r\n", io->stdErr);
      }
      res = ERR_FAILED;
      break;
    }
    if (bytesRead==0) { /* end of file? */
      break;
    }
    while(!VS_Ready()) {
      FRTOS1_vTaskDelay(10/portTICK_PERIOD_MS);
    }
    VS_SendData(readBuf, sizeof(readBuf));
  }
  /* closing file */
  (void)FAT1_close(&fp);
  VS_StartSong();
  return res;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];
  uint16_t val;

  CLS1_SendStatusStr((unsigned char*)"VS1053", (unsigned char*)"\r\n", io->stdOut);

  if (VS_ReadRegister(VS_MODE, &val)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  MODE", buf, io->stdOut);

  if (VS_ReadRegister(VS_STATUS, &val)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  STATUS", buf, io->stdOut);

  if (VS_ReadRegister(VS_BASS, &val)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  BASS", buf, io->stdOut);

  if (VS_ReadRegister(VS_CLOCKF, &val)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  CLOCKF", buf, io->stdOut);

  if (VS_ReadRegister(VS_DECODE_TIME, &val)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), " seconds\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  DECODE", buf, io->stdOut);

  if (VS_ReadRegister(VS_AUDATA, &val)==ERR_OK) {
    buf[0] = '\0';
    UTIL1_Num16uToStr(buf, sizeof(buf), val&0xFFFE);
    UTIL1_strcat(buf, sizeof(buf), " Hz, ");
    UTIL1_strcat(buf, sizeof(buf), (val&1)?"stereo\r\n":"mono\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  AUDATA", buf, io->stdOut);

  if (VS_ReadRegister(VS_VOL, &val)==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "0x");
    UTIL1_strcatNum16Hex(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), " (0x0000 full, 0xFEFE silence)\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  VOLUME", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"VS1053", (unsigned char*)"Group of VL1053 commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  volume <number>", (unsigned char*)"Set volume, full: 0x0000, 0xFEFE silence\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  play <file>", (unsigned char*)"Play song file\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t VS_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
{
  const uint8_t *p;
  uint32_t val32u;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "VS1053 help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "VS1053 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "VS1053 volume ", sizeof("VS1053 volume ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("VS1053 volume ")-1;
    if (UTIL1_xatoi(&p, &val32u)==ERR_OK) {
      return VS_SetVolume((uint16_t)val32u);
    } else {
      CLS1_SendStr("Failed reading volume", io->stdErr);
      return ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "VS1053 play ", sizeof("VS1053 play ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("VS1053 play ")-1;
    return VS_PlaySong(p, io);
  }
  return ERR_OK;
}

void VS_Deinit(void) {
  /* nothing needed */
}

void VS_Init(void) {
  MCS_SetVal(); /* chip select is low active, deselect it */
  DCS_SetVal(); /* data mode is low active, deselect data mode */
#if VS_LDD_SPI
  VS_SPIDataReceivedFlag = FALSE; /* Initialization */
#endif
}
#endif /* PL_HAS_MUSIC_SHIELD */
