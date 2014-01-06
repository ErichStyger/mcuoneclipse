/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "FAT1.h"
#include "w5100.h"

static bool cardMounted = FALSE;
static FAT1_FATFS fileSystemObject;

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    CLS1_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of app commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  mount|unmount", (const unsigned char*)"mount or unmount file system\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "app status")==0) {
    CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
    CLS1_SendStatusStr((unsigned char*)"  mounted", cardMounted?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "app mount")==0) {
    *handled = TRUE;
    if (cardMounted) {
      CLS1_SendStr((unsigned char*)"card already mounted!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (FAT1_MountFileSystem(&fileSystemObject, 0, io)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      cardMounted = TRUE;
    }
  } else if (UTIL1_strcmp((char*)cmd, "app unmount")==0) {
    *handled = TRUE;
    if (!cardMounted) {
      CLS1_SendStr((unsigned char*)"card not mounted!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (FAT1_UnMountFileSystem(0, io)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      cardMounted = FALSE;
    }
  }
  return ERR_OK; /* no error */
}


void W5100_Test(void);
static const w5100_config_t W5100_config = {
  {192, 168, 1, 1}, /* gateway */
  {255, 255, 255, 0}, /* netmask */
  {0x90, 0xa2, 0xda,0x0D, 0x42, 0xdd}, /* hw/mac address */
  {192, 168, 0, 80} /* ip address */
};

static void WiznetSetup(void) {
  CLS1_SendStr((unsigned char*)"Reset W5100.\r\n", CLS1_GetStdio()->stdOut);
  /* reset device */
  if (W5100_MemWriteByte(W5100_MR, W5100_MR_BIT_RST)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed to reset device!\r\n", CLS1_GetStdio()->stdErr);
  }
  CLS1_SendStr((unsigned char*)"Configure network.\r\n", CLS1_GetStdio()->stdOut);
  /* configure network: IP address, gateway, netmask, MAC */
  if (W5100_WriteConfig((w5100_config_t*)&W5100_config)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed to set Net Configuration!\r\n", CLS1_GetStdio()->stdErr);
  }
  CLS1_SendStr((unsigned char*)"Configure RX/TX memory.\r\n", CLS1_GetStdio()->stdOut);
  /* we have 8 KByte we can use for the RX and TX sockets: */
  if (W5100_MemWriteByte(W5100_RMSR, 
       W5100_xMSR_SOCKET_1_MEM_SIZE_2KB
      |W5100_xMSR_SOCKET_2_MEM_SIZE_2KB
      |W5100_xMSR_SOCKET_3_MEM_SIZE_2KB
      |W5100_xMSR_SOCKET_4_MEM_SIZE_2KB
     )!=ERR_OK) 
  {
    CLS1_SendStr((unsigned char*)"Failed to set RX socket memory size!\r\n", CLS1_GetStdio()->stdErr);
  }
  if (W5100_MemWriteByte(W5100_TMSR, 
       W5100_xMSR_SOCKET_1_MEM_SIZE_2KB
      |W5100_xMSR_SOCKET_2_MEM_SIZE_2KB
      |W5100_xMSR_SOCKET_3_MEM_SIZE_2KB
      |W5100_xMSR_SOCKET_4_MEM_SIZE_2KB
     )!=ERR_OK) 
  {
    CLS1_SendStr((unsigned char*)"Failed to set TX socket memory size!\r\n", CLS1_GetStdio()->stdErr);
  }
  CLS1_SendStr((unsigned char*)"done!\r\n", CLS1_GetStdio()->stdOut);
}

static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  WiznetSetup();
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  cardMounted = FALSE;
  SHELL_Init();
  W5100_Init();
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        (signed char *)"Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+100, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}
