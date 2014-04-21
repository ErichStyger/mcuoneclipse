/**
 * \file
 * \brief This is the application interface
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 *
 * This module is the main module of the application.
 */

#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "FAT1.h"
#include "w5100.h"
#include "socket.h"
#include "Server.h"
#if PL_USE_INI
  #include "MINI1.h"
#endif

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

#if PL_USE_INI
#define INI_FILE_NAME "config.ini"
#define INI_SECTION_NAME "W5100"

static w5100_config_t W5100_config = {
  {192, 168, 1, 1}, /* gateway */
  {255, 255, 255, 0}, /* netmask */
#if 1
  {0x90, 0xa2, 0xda, 0x0D, 0x42, 0xdd}, /* hw/mac address */
#elif 1
  {0x90, 0xa2, 0xda, 0x0F, 0x16, 0x43}, /* hw/mac address */
#endif
  {192, 168, 0, 90} /* ip address */
};
#else
static const w5100_config_t W5100_config = {
  {192, 168, 1, 1}, /* gateway */
  {255, 255, 255, 0}, /* netmask */
#if 1
  {0x90, 0xa2, 0xda, 0x0D, 0x42, 0xdd}, /* hw/mac address */
#elif 1
  {0x90, 0xa2, 0xda, 0x0F, 0x16, 0x43}, /* hw/mac address */
#endif
  {192, 168, 0, 90} /* ip address */
};
#endif

static void WiznetSetup(void) {
  CLS1_SendStr((unsigned char*)"Reset W5100.\r\n", CLS1_GetStdio()->stdOut);
  /* reset device */
  if (W5100_MemWriteByte(W5100_MR, W5100_MR_BIT_RST)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"Failed to reset device!\r\n", CLS1_GetStdio()->stdErr);
  }
  CLS1_SendStr((unsigned char*)"Configure network.\r\n", CLS1_GetStdio()->stdOut);
#if PL_USE_INI
  {
    uint8_t buf[32];
    int val;
    const unsigned char *p;
    uint8_t val8u;
    
    CLS1_SendStr((unsigned char*)"Loading values from " INI_FILE_NAME "\r\n", CLS1_GetStdio()->stdOut);
    val = MINI1_ini_gets(INI_SECTION_NAME, "Gateway", "192.168.1.1", (char*)buf, sizeof(buf), INI_FILE_NAME);
    if (val!=0) {
      p = &buf[0];
      val8u = 0;
      if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && *p=='.') {
        W5100_config.gateway[0] = val8u;
        p++;
        if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && *p=='.') {
          W5100_config.gateway[1] = val8u;
          p++;
          if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && *p=='.') {
            W5100_config.gateway[2] = val8u;
            p++;
            if (UTIL1_ScanDecimal8uNumber(&p, &val8u)==ERR_OK && *p=='\0') {
              W5100_config.gateway[3] = val8u;
            }
          }
        }
      }
    }
  }
#endif
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
  FRTOS1_vTaskDelay(1000/portTICK_RATE_MS); /* provide other tasks time to run, especially to mount file system */
  WiznetSetup();
  CLS1_SendStr((unsigned char*)"Running web server...\r\n", CLS1_GetStdio()->stdOut);
  for(;;) {
    SERVER_Process(0);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  cardMounted = FALSE;
  SHELL_Init();
  W5100_Init();
  SOCK_Init();
  SERVER_Init();
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        "Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+300, /* task stack size */
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
