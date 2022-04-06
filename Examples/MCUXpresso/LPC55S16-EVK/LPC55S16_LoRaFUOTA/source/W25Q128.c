/*
 * W25Q128.c
 *
 *  Created on: 05.01.2019
 *      Author: Erich Styger
 */

#include "W25Q128.h"
#include "utilities.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "LPC55S16.h"
#include "fsl_spi.h"
#include "McuShell.h"
#include "spi.h"
#include "spi-board.h"
#include "McuLog.h"

#define W25_CMD_PAGE_PROGRAM  0x02
#define W25_CMD_DATA_READ     0x03

#define W25_CMD_READ_STATUS1  0x05

#define W25_CMD_WRITE_ENABLE  0x06
#define W25_CMD_WRITE_DISABLE  0x04

#define W25_CMD_GET_ID        0x9F
#define W25_ID0_WINBOND       0xEF

#define W25_CMD_GET_SERIAL    0x4B

#define W25_CMD_SECTOR_ERASE_4K 0x20
#define W25_CMD_BLOCK_ERASE_32K 0x52
#define W25_CMD_BLOCK_ERASE_64K 0xD8
#define W25_CMD_CHIP_ERASE      0xC7

static Spi_t         Spi_FC3;
McuGPIO_Handle_t SPI_NSS;

/* W25Q128 chip select is LOW active */
#define W25_CS_ENABLE()   McuGPIO_SetLow(SPI_NSS)
#define W25_CS_DISABLE()  McuGPIO_SetHigh(SPI_NSS)
#define TRANSFER_SIZE 							1
static uint8_t rxDummy; /* dummy byte if we do not need the result. Needed to read from SPI register. */



#define TRANSFER_SIZE 4U /*! Transfer dataSize */


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void SPI_MasterUserCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData);
static void W25Q_MasterInit(void);
static void W25Q_MasterDMASetup(void);
static void W25Q_MasterStartDMATransfer(void);
static void W25Q_TransferDataCheck(uint8_t *buf, uint8_t *masterRxData_temp, size_t buffSize, uint8_t offset);
static void SPI_WRITE_READ_CMD(uint8_t cmd, uint8_t *buf, size_t bufSize);
static void SPI_READ_W25(uint8_t command ,uint32_t address, uint8_t *buf, size_t bufSize);
static void SPI_WRITE_W25(uint8_t command ,uint32_t address, const uint8_t *buf, size_t bufSize);
/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t masterRxData[TRANSFER_SIZE] = {0};
uint8_t masterTxData[TRANSFER_SIZE] = {0};

dma_handle_t masterTxHandle;
dma_handle_t masterRxHandle;

spi_dma_handle_t masterHandle;

volatile bool isTransferCompleted = false;


typedef struct {
	SpiId_t id;
	SPI_Type *type;
	uint32_t srcClk;
	spi_master_config_t masterConfig;
	spi_transfer_t xfr;
	uint8_t masterRxData[TRANSFER_SIZE];
	uint8_t masterTxData[TRANSFER_SIZE];
} lpcSpiHandle_t;

#if(LPC_NUMBER_OF_SPI > 0)
static lpcSpiHandle_t spiHandle0 = {
	.id = SPI_1,
	.type = LPC_SPI3_TYPE,
};
#endif
#if(LPC_NUMBER_OF_SPI > 1)
static lpcSpiHandle_t spiHandle1 = {
	.id = SPI_2,
	.type = LPC_SPI2_TYPE,
};
#endif


/*******************************************************************************
 * Code
 ******************************************************************************/
static void SPI_MasterUserCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_Success)
    {
        isTransferCompleted = true;
    }
}

#define SPI_WRITE(write){}
//   {
//    // while(SM1_SendChar(write)!=ERR_OK) {} \
//    // while(SM1_RecvChar(&rxDummy)!=ERR_OK) {}
//   }
#define SPI_WRITE_READ(write, readP) {}
//   {
//   // while(SM1_SendChar(write)!=ERR_OK) {} \
//   //  while(SM1_RecvChar(readP)!=ERR_OK) {}
//   }



static void W25_MapSpiIdToHandle(SpiId_t spiId, lpcSpiHandle_t **handle);


uint16_t W25_SpiInOut(Spi_t *obj, uint16_t outData) {

	lpcSpiHandle_t *handle;
	W25_MapSpiIdToHandle(obj->SpiId, &handle);

	handle->masterRxData[0] = 0x00;
	handle->masterTxData[0] = (uint8_t) (outData);
	 W25_CS_ENABLE();
	CRITICAL_SECTION_BEGIN();

	/* Start master transfer, send data to slave */
	handle->xfr.txData = handle->masterTxData;
	handle->xfr.rxData = handle->masterRxData;
	handle->xfr.dataSize = TRANSFER_SIZE;
	handle->xfr.configFlags = kSPI_FrameAssert;
	if (kStatus_Success != SPI_MasterTransferBlocking(handle->type, &(handle->xfr))) {
		CRITICAL_SECTION_END();
		/* Error occured */
	}

	CRITICAL_SECTION_END();
	W25_CS_DISABLE();
	return handle->masterRxData[0];
}



bool W25_isBusy(void) {
  uint8_t status;

  W25_ReadStatus1(&status);
  return (status&1);
}

void W25_WaitIfBusy(void) {
  while(W25_isBusy()) {
	  McuWait_Waitms(1);
  }
}

uint8_t W25_Read(uint32_t address, uint8_t *buf, size_t bufSize) {
  size_t i;
  W25_WaitIfBusy();
  SPI_READ_W25(W25_CMD_DATA_READ, address, buf, bufSize);
  return ERR_OK;
}

uint8_t W25_EraseAll(void) {
  W25_WaitIfBusy();
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
  SPI_WRITE_READ_CMD(W25_CMD_CHIP_ERASE, NULL, 0);
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_DISABLE, NULL, 0);
  return ERR_OK;
}


uint8_t W25_EraseSector4K(uint32_t address) {
  W25_WaitIfBusy();
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
  SPI_WRITE_W25(W25_CMD_SECTOR_ERASE_4K, address, NULL, 0);
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_DISABLE, NULL, 0);
  return ERR_OK;
}

uint8_t W25_EraseBlock32K(uint32_t address) {
  W25_WaitIfBusy();
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
  SPI_WRITE_W25(W25_CMD_BLOCK_ERASE_32K, address, NULL, 0);
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_DISABLE, NULL, 0);
  return ERR_OK;
}

uint8_t W25_EraseBlock64K(uint32_t address) {
  W25_WaitIfBusy();
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
  SPI_WRITE_W25(W25_CMD_BLOCK_ERASE_64K, address, NULL, 0);
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_DISABLE, NULL, 0);
  return ERR_OK;
}

/*!
 * Program a page with data
 * \param address, should be aligned on page (256 bytes) if programming 256 bytes
 * \param data pointer to data
 * \param dataSize size of data in bytes, max 256
 * \return error code, ERR_OK for no error
 */
uint8_t W25_ProgramPage(uint32_t address, const uint8_t *data, size_t dataSize) {

  W25_WaitIfBusy();
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
  //SPI_WRITE_W25(W25_CMD_SECTOR_ERASE_4K, address, NULL, 0);
  //W25_WaitIfBusy();
  //SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
  W25_WaitIfBusy();
  SPI_WRITE_W25(W25_CMD_PAGE_PROGRAM, address, data, dataSize);
  W25_WaitIfBusy();
  SPI_WRITE_READ_CMD(W25_CMD_WRITE_DISABLE, NULL, 0);

  return ERR_OK;
}


uint8_t W25_GetCapacity(const uint8_t *id, uint32_t *capacity) {
  uint32_t n = 0x100000; // unknown chips, default to 1 MByte

  if (id[2] >= 16 && id[2] <= 31) {
    n = 1ul << id[2];
  } else if (id[2] >= 32 && id[2] <= 37) {
    n = 1ul << (id[2] - 6);
  } else if ((id[0]==0 && id[1]==0 && id[2]==0) || (id[0]==255 && id[1]==255 && id[2]==255)) {
    *capacity = 0;
    return ERR_FAILED;
  }
  *capacity = n;
  return ERR_OK;
}

uint8_t W25_ReadStatus1(uint8_t *status) {
	/* W25Q128 should report Serialnumber */
	SPI_WRITE_READ_CMD(W25_CMD_READ_STATUS1, status, sizeof(* status));

  return ERR_OK;
}

uint8_t W25_ReadSerialNumber(uint8_t *buf, size_t bufSize) {
  int i;

  if (bufSize<W25_SERIAL_BUF_SIZE) {
    return ERR_OVERFLOW; /* buffer not large enough */
  }

  /* W25Q128 should report Serialnumber */
  SPI_WRITE_READ_CMD(W25_CMD_GET_SERIAL, buf, bufSize);

  return ERR_OK;

}

uint8_t W25_ReadID(uint8_t *buf, size_t bufSize) {
  if (bufSize<W25_ID_BUF_SIZE) {
    return ERR_OVERFLOW; /* buffer not large enough */
  }

  /* W25Q128 should report EF 40 18 */
  SPI_WRITE_READ_CMD(W25_CMD_GET_ID, buf, bufSize);
//  W25_CS_DISABLE();
  if (buf[0]==W25_ID0_WINBOND && buf[1]==0x40 && buf[2]==0x18) {
    return ERR_OK;
  }
  return ERR_FAILED; /* not expected part */
}


static uint8_t W25_PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[60];
  uint8_t id[W25_ID_BUF_SIZE] = {0,0,0};
  uint8_t serial[W25_SERIAL_BUF_SIZE] = {0,0,0,0,0,0,0,0};
  uint8_t res, status;
  uint32_t capacity;
  int i;

  McuShell_SendStatusStr((const unsigned char*)"W25", (const unsigned char*)"\r\n", io->stdOut);

  res = W25_ReadID(id, sizeof(id)); /* check ID */
  if(res==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), id[0]);
    McuUtility_chcat(buf, sizeof(buf), ' ');
    McuUtility_strcatNum8Hex(buf, sizeof(buf), id[1]);
    McuUtility_chcat(buf, sizeof(buf), ' ');
    McuUtility_strcatNum8Hex(buf, sizeof(buf), id[2]);
    if (id[0]==W25_ID0_WINBOND && id[1]==0x40 && id[2]==0x18) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (Winbond W25Q128)\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (UNKNOWN)\r\n");
    }
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  ID", buf, io->stdOut);

  res = W25_GetCapacity(id, &capacity);
  if (res==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum32u(buf, sizeof(buf), capacity);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" bytes\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  Capacity", buf, io->stdOut);

  res = W25_ReadSerialNumber(serial, sizeof(serial)); /* check serial number */
  if(res==ERR_OK) {
    buf[0] = '\0';
    for(i=0; i<sizeof(serial); i++) {
      McuUtility_strcatNum8Hex(buf, sizeof(buf), serial[i]);
      McuUtility_chcat(buf, sizeof(buf), ' ');
    }
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  Serial", buf, io->stdOut);

  res = W25_ReadStatus1(&status);
  if(res==ERR_OK) {
	buf[0] = '\0';
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, sizeof(buf), status);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" SEC:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<6)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" TB:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<5)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BP2:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<4)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BP1:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<3)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BP0:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<2)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" WEL:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<1)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BUSY:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<0)?(unsigned char*)"1": (unsigned char*)"0");
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  Status", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t ReadBytes(void *hndl, uint32_t address, uint8_t *buf, size_t bufSize) {
  (void)hndl; /* not used */
//  size_t i;
//  W25_WaitIfBusy();
//  SPI_WRITE_READ_CMD(W25_CMD_DATA_READ, NULL, 0);
//  SPI_WRITE_READ_CMD(address>>16, NULL, 0);
//  SPI_WRITE_READ_CMD(address>>8, NULL, 0);
//  SPI_WRITE_READ_CMD(address, NULL, 0);
//  for(i=0;i<bufSize;i++) {
//	  SPI_WRITE_READ_CMD(0, &buf[i],1);
//  }

  SPI_READ_W25(W25_CMD_DATA_READ, address, buf, bufSize);
  return ERR_OK;
}

uint8_t W25_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_ConstStdIOType *io) {
  const unsigned char *p;
  uint32_t val, end;
  uint32_t res;
  uint8_t data[32];
  int i;
  uint8_t buf[60];
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "W25 help")==0) {
    McuShell_SendHelpStr((unsigned char*)"W25", (const unsigned char*)"Group of W25 commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  read <start> <end>", (const unsigned char*)"Read memory from <start> to <end> address\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  erase all", (const unsigned char*)"Erase all\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  erase 4k <addr>", (const unsigned char*)"Erase a 4K sector\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  erase 32k <addr>", (const unsigned char*)"Erase a 32K block\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  erase 64k <addr>", (const unsigned char*)"Erase a 64K block\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  enable", (const unsigned char*)"Enable/disable write action (1/0)\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  write <addr> <data>", (const unsigned char*)"Write to page (max 32 bytes data, separated by spaces)\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, "W25 status")==0) {
    *handled = TRUE;
    return W25_PrintStatus(io);

  } else if (McuUtility_strncmp((char*)cmd, "W25 enable ", sizeof("W25 enable ")-1)==0) {
	    *handled = TRUE;
  	  uint8_t status;
	    p = cmd+sizeof("W25 read ");
	    res = McuUtility_xatoi(&p, (int32_t*)&val);
	    if (res!=ERR_OK) {
	      McuShell_SendStr((unsigned char*)"wrong start address\r\n", io->stdErr);
	      return ERR_FAILED;
	    } else {

	      if (val!=true) {
	    	  SPI_WRITE_READ_CMD(W25_CMD_WRITE_DISABLE, NULL, 0);
	    	  res = W25_ReadStatus1(&status);


	      }
	      else{
	    	  SPI_WRITE_READ_CMD(W25_CMD_WRITE_ENABLE, NULL, 0);
	    	  res = W25_ReadStatus1(&status);
	      }
	      res = W25_ReadStatus1(&status);
	      if(res==ERR_OK) {
	    	buf[0] = '\0';
	        McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
	        McuUtility_strcatNum8Hex(buf, sizeof(buf), status);
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" SEC:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<6)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" TB:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<5)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BP2:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<4)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BP1:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<3)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BP0:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<2)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" WEL:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<1)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BUSY:"); McuUtility_strcat(buf, sizeof(buf), status&(1<<0)?(unsigned char*)"1": (unsigned char*)"0");
	        McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
	      } else {
	        McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
	      }
	      McuShell_SendStatusStr((const unsigned char*)"  Status", buf, io->stdOut);
	    }

  }else if (McuUtility_strncmp((char*)cmd, "W25 read ", sizeof("W25 read ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 read ")-1;
    res = McuUtility_xatoi(&p, (int32_t*)&val);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"wrong start address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = McuUtility_xatoi(&p, (int32_t*)&end);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"wrong end address\r\n", io->stdErr);
        return ERR_FAILED;
      }
      res = McuShell_PrintMemory(NULL, val, end, 3, 16, ReadBytes, io);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"memory read failed\r\n", io->stdErr);
        return ERR_FAILED;
      }
      return ERR_OK;
    }
  } else if (McuUtility_strncmp((char*)cmd, "W25 write ", sizeof("W25 write ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 write ")-1;
    res = McuUtility_xatoi(&p, (int32_t*)&val);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      for(i=0; i<sizeof(data); i++) {
        uint32_t v;
        res = McuUtility_xatoi(&p, (int32_t*)&v);
        if (res!=ERR_OK) {
          break;
        }
        data[i] = v;
      }
      if (i>0) {
        res = W25_ProgramPage(val, data, i);
        if (res!=ERR_OK) {
          McuShell_SendStr((unsigned char*)"failed programming page\r\n", io->stdErr);
          return ERR_FAILED;
        }
      }
    }
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "W25 erase all")==0) {
    *handled = TRUE;
    res = W25_EraseAll();
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"failed erasing all memory\r\n", io->stdErr);
      return ERR_FAILED;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "W25 erase 4k ", sizeof("W25 erase 4k ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 erase 4k ")-1;
    res = McuUtility_xatoi(&p, (int32_t*)&val);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_EraseSector4K(val);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed erasing 4k sector\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "W25 erase 32k ", sizeof("W25 erase 32k ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 erase 32k ")-1;
    res = McuUtility_xatoi(&p, (int32_t*)&val);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_EraseBlock32K(val);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed erasing 32k block\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "W25 erase 64k ", sizeof("W25 erase 64k ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("W25 erase 64k ")-1;
    res = McuUtility_xatoi(&p, (int32_t*)&val);
    if (res!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      res = W25_EraseBlock64K(val);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed erasing 32k block\r\n", io->stdErr);
        return ERR_FAILED;
      }
    }
    return ERR_OK;
  }
  return ERR_OK;
}

uint8_t W25_Init(void) {


    /* Initialize SPI master with configuration. */
    W25Q_MasterInit();

    /* Set up DMA for SPI master TX and RX channel. */
    W25Q_MasterDMASetup();

    /* Print project information. */
    McuLog_info("Initialisation of the W25Q SPI interface.\r\n");
    uint8_t serial_buf[W25_SERIAL_BUF_SIZE] = {0,0,0,0,0,0,0,0};
    uint8_t id_buf[W25_ID_BUF_SIZE] = {0,0,0};
    uint8_t res;
    //res = W25_ReadID(id_buf, sizeof(id_buf)); /* check ID */
    //res = W25_ReadSerialNumber(serial_buf, sizeof(serial_buf));
  return res; /* check ID */
}



/**
  * Since the LoRaMac-node stack's SPI enum (SpiId_t) goes from SPI_1 to SPI_2,
  * but the LPC series offers several SPIs on different pin settings, a short mapping
  * is required. This method sets the pointer "handle" to the corresponding handle of the given
  * spiId defined above.
  */
static void W25_MapSpiIdToHandle(SpiId_t spiId, lpcSpiHandle_t **handle) {

#if(LPC_NUMBER_OF_SPI > 0)
	if(spiHandle0.id == spiId){
		*handle = &spiHandle0;
	}
#endif
#if(LPC_NUMBER_OF_SPI > 1)
	if(spiHandle1.id == spiId){
		*handle = &spiHandle1;
	}
#endif
}




static void W25Q_MasterInit(void)
{
    /* SPI init */
    uint32_t srcClock_Hz = 0U;
    spi_master_config_t masterConfig;
    srcClock_Hz = W25Q_SPI_MASTER_CLK_FREQ;

    SPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.sselNum = (spi_ssel_t)W25Q_SPI_SSEL;
    masterConfig.sselPol = (spi_spol_t)W25Q_MASTER_SPI_SPOL;
    SPI_MasterInit(W25Q_SPI_MASTER, &masterConfig, srcClock_Hz);
}

static void W25Q_MasterDMASetup(void)
{
    /* DMA init */
    DMA_Init(W25Q_DMA);
    /* Configure the DMA channel,priority and handle. */
    DMA_EnableChannel(W25Q_DMA, W25Q_SPI_MASTER_TX_CHANNEL);
    DMA_EnableChannel(W25Q_DMA, W25Q_SPI_MASTER_RX_CHANNEL);
    DMA_SetChannelPriority(W25Q_DMA, W25Q_SPI_MASTER_TX_CHANNEL, kDMA_ChannelPriority3);
    DMA_SetChannelPriority(W25Q_DMA, W25Q_SPI_MASTER_RX_CHANNEL, kDMA_ChannelPriority2);
    DMA_CreateHandle(&masterTxHandle, W25Q_DMA, W25Q_SPI_MASTER_TX_CHANNEL);
    DMA_CreateHandle(&masterRxHandle, W25Q_DMA, W25Q_SPI_MASTER_RX_CHANNEL);
}


static void SPI_WRITE_READ_CMD(uint8_t command, uint8_t *buf, size_t buffSize){
	spi_transfer_t masterXfer;
	uint32_t i = 0U;
	uint8_t buffOffset = 1;
	uint8_t *masterRxData_temp = malloc(buffSize+buffOffset * sizeof(uint8_t));
	uint8_t *masterTxData_temp = malloc(buffSize+buffOffset * sizeof(uint8_t));
	masterTxData_temp[0]= command;
	/* Set up handle for spi master */
    SPI_MasterTransferCreateHandleDMA(W25Q_SPI_MASTER, &masterHandle, SPI_MasterUserCallback, NULL, &masterTxHandle,
                                      &masterRxHandle);
	for (int i = 0; i < buffSize; ++i)
	{
		masterTxData_temp[buffOffset+i]= 0;
	}
	/* Start master transfer */
	//0x9F
	masterXfer.txData      = (uint8_t *)masterTxData_temp;
	masterXfer.rxData      = (uint8_t *)masterRxData_temp;
	masterXfer.dataSize    = (buffSize+buffOffset) * sizeof(masterTxData_temp[0]);
	masterXfer.configFlags = kSPI_FrameAssert;

	if (kStatus_Success != SPI_MasterTransferDMA(W25Q_SPI_MASTER, &masterHandle, &masterXfer))
	{
		//PRINTF("There is an error when start SPI_MasterTransferDMA \r\n ");
	}

	W25Q_TransferDataCheck(buf, masterRxData_temp, buffSize, buffOffset);
//	McuWait_Waitus(1);
//	memcpy(buf, masterRxData_temp+1, buffSize * sizeof(masterRxData_temp[0]));
	free(masterRxData_temp);free(masterTxData_temp);
}


static void SPI_READ_W25(uint8_t command ,uint32_t address, uint8_t *buf, size_t buffSize){
	spi_transfer_t masterXfer;
	uint32_t i = 0U;
	uint8_t buffOffset = 4;
	uint8_t *masterRxData_temp = malloc(buffSize+buffOffset * sizeof(uint8_t));
	uint8_t *masterTxData_temp = malloc(buffSize+buffOffset * sizeof(uint8_t));
	masterTxData_temp[0]= command;
	masterTxData_temp[1]= address>>16;
	masterTxData_temp[2]= address>>8;
	masterTxData_temp[3]= address;
	/* Set up handle for spi master */
    SPI_MasterTransferCreateHandleDMA(W25Q_SPI_MASTER, &masterHandle, SPI_MasterUserCallback, NULL, &masterTxHandle,
                                      &masterRxHandle);

	for (int i = 0; i < buffSize; ++i)
	{
		masterTxData_temp[buffOffset+i]= 0;
	}
	/* Start master transfer */
	//0x9F
	masterXfer.txData      = (uint8_t *)masterTxData_temp;
	masterXfer.rxData      = (uint8_t *)masterRxData_temp;
	masterXfer.dataSize    = (buffSize+buffOffset) * sizeof(masterTxData_temp[0]);
	masterXfer.configFlags = kSPI_FrameAssert;

	if (kStatus_Success != SPI_MasterTransferDMA(W25Q_SPI_MASTER, &masterHandle, &masterXfer))
	{
		//PRINTF("There is an error when start SPI_MasterTransferDMA \r\n ");
	}
	W25Q_TransferDataCheck(buf, masterRxData_temp, buffSize,buffOffset);
	free(masterRxData_temp);free(masterTxData_temp);
}

static void SPI_WRITE_W25(uint8_t command, uint32_t address, const uint8_t *buf, size_t buffSize){

	spi_transfer_t masterXfer;
	uint32_t i = 0U;
	//ueberpruefen auf NULL
	//pvmalloc
	uint8_t *masterRxData_temp = malloc(buffSize+4 * sizeof(uint8_t));
	uint8_t *masterTxData_temp = malloc(buffSize+4 * sizeof(uint8_t));
	masterTxData_temp[0]= command;
	masterTxData_temp[1]= address>>16;
	masterTxData_temp[2]= address>>8;
	masterTxData_temp[3]= address;

	for (int i = 0; i < buffSize; ++i)
	{
		masterTxData_temp[4+i]= buf[i];
	}

	/* Set up handle for spi master */
    SPI_MasterTransferCreateHandleDMA(W25Q_SPI_MASTER, &masterHandle, SPI_MasterUserCallback, NULL, &masterTxHandle,
                                      &masterRxHandle);

	/* Start master transfer */
	//0x9F
	masterXfer.txData      = (uint8_t *)masterTxData_temp;
	masterXfer.rxData      = (uint8_t *)masterRxData_temp;
	masterXfer.dataSize    = (buffSize+4) * sizeof(masterTxData_temp[0]);
	masterXfer.configFlags = kSPI_FrameAssert;

	if (kStatus_Success != SPI_MasterTransferDMA(W25Q_SPI_MASTER, &masterHandle, &masterXfer))
	{
		//PRINTF("There is an error when start SPI_MasterTransferDMA \r\n ");
	}
	W25Q_TransferDataCheck(NULL,NULL,NULL,0);
	free(masterRxData_temp);free(masterTxData_temp);
}


static void W25Q_TransferDataCheck(uint8_t *buf, uint8_t *masterRxData_temp, size_t buffSize ,uint8_t offset)
{

    /* Wait until transfer completed */
    while (!isTransferCompleted)
    {
    }
	//McuWait_Waitms(1);
	memcpy(buf, masterRxData_temp+offset, buffSize * sizeof(masterRxData_temp[0]));
	isTransferCompleted = false;

}


//static void W25Q_MasterStartDMATransfer(void)
//{
//    spi_transfer_t masterXfer;
//    uint32_t i = 0U;
//
//    /* Set up the transfer data */
//    for (i = 0U; i < TRANSFER_SIZE; i++)
//    {
//        /* SPI is configured for 8 bits transfer - set only lower 8 bits of buffers */
//        masterTxData[i] = 0U;
//        masterRxData[i] = 0U;
//    }
//    masterTxData[0] = W25_CMD_GET_ID;
//    /* Set up handle for spi master */
//    SPI_MasterTransferCreateHandleDMA(W25Q_SPI_MASTER, &masterHandle, SPI_MasterUserCallback, NULL, &masterTxHandle,
//                                      &masterRxHandle);
//
//    /* Start master transfer */
//    masterXfer.txData      = (uint8_t *)&masterTxData;
//    masterXfer.rxData      = (uint8_t *)&masterRxData;
//    masterXfer.dataSize    = TRANSFER_SIZE * sizeof(masterTxData[0]);
//    masterXfer.configFlags = kSPI_FrameAssert;
//
//    if (kStatus_Success != SPI_MasterTransferDMA(W25Q_SPI_MASTER, &masterHandle, &masterXfer))
//    {
//       // PRINTF("There is an error when start SPI_MasterTransferDMA \r\n ");
//    }
//}

/* from https://github.com/PaulStoffregen/SerialFlash/blob/master/SerialFlashChip.cpp */
//                   size  sector          busy  pgm/erase chip
// Part              Mbyte kbyte ID bytes  cmd   suspend   erase
// ----               ----  ----- --------  --- -------   -----
// Winbond W25Q64CV 8 64  EF     40 17
// Winbond W25Q128FV  16  64     EF 40 18  05  single    60 & C7
// Winbond W25Q256FV  32  64     EF 40 19
// Spansion S25FL064A 8 ? 01     02 16
// Spansion S25FL127S 16  64     01 20 18  05
// Spansion S25FL128P 16  64     01 20 18
// Spansion S25FL256S 32  64     01 02 19  05      60 & C7
// Spansion S25FL512S 64  256    01 02 20
// Macronix MX25L12805D 16  ? C2 20 18
// Macronix MX66L51235F 64    C2 20 1A
// Numonyx M25P128  16  ? 20 20 18
// Micron M25P80  1 ? 20 20 14
// Micron N25Q128A  16  64  20 BA 18
// Micron N25Q512A  64  ? 20 BA 20  70  single    C4 x2
// Micron N25Q00AA  128 64  20 BA 21    single    C4 x4
// Micron MT25QL02GC  256 64  20 BA 22  70      C4 x2
// SST SST25WF010 1/8 ? BF 25 02
// SST SST25WF020 1/4 ? BF 25 03
// SST SST25WF040 1/2 ? BF 25 04
// SST SST25VF016B  1 ? BF 25 41
// SST26VF016     ? BF 26 01
// SST26VF032     ? BF 26 02
// SST25VF032   4 64  BF 25 4A
// SST26VF064   8 ? BF 26 43
// LE25U40CMC   1/2 64  62 06 13
