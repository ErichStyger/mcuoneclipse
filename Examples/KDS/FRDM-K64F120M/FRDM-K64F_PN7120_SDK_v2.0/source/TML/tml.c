#include <stdint.h>
#include "board.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include <tool.h>
#include "board.h" /* << EST */

SemaphoreHandle_t IrqSem = NULL;
i2c_master_transfer_t masterXfer;

typedef enum {ERROR = 0, SUCCESS = !ERROR} Status;

#if 0 && NXPNCI_PORTA_IRQ
void PORTA_IRQHandler(void)
#else
void PORTC_IRQHandler(void)
#endif
{
	if (GPIO_ReadPinInput(NXPNCI_IRQ_GPIO, NXPNCI_IRQ_PIN) == 1)
	{
	    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		GPIO_ClearPinsInterruptFlags(NXPNCI_IRQ_GPIO, 1U << NXPNCI_IRQ_PIN);
		xSemaphoreGiveFromISR(IrqSem, &xHigherPriorityTaskWoken);
	}
}

static status_t I2C_WRITE(uint8_t *pBuff, uint16_t buffLen)
{
    masterXfer.direction = kI2C_Write;
    masterXfer.data = pBuff;
    masterXfer.dataSize = buffLen;

    return I2C_MasterTransferBlocking(NXPNCI_I2C_INSTANCE, &masterXfer);
}

static status_t I2C_READ(uint8_t *pBuff, uint16_t buffLen)
{
    masterXfer.direction = kI2C_Read;
    masterXfer.data = pBuff;
    masterXfer.dataSize = buffLen;

    return I2C_MasterTransferBlocking(NXPNCI_I2C_INSTANCE, &masterXfer);
}

static Status tml_Init(void) {
    i2c_master_config_t masterConfig;
    uint32_t sourceClock;

    gpio_pin_config_t irq_config = {kGPIO_DigitalInput, 0,};
    gpio_pin_config_t ven_config = {kGPIO_DigitalOutput, 0,};

    GPIO_PinInit(NXPNCI_IRQ_GPIO, NXPNCI_IRQ_PIN, &irq_config);
    GPIO_PinInit(NXPNCI_VEN_GPIO, NXPNCI_VEN_PIN, &ven_config);

    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = NXPNCI_I2C_BAUDRATE;
    sourceClock = CLOCK_GetFreq(I2C0_CLK_SRC);
    masterXfer.slaveAddress = NXPNCI_I2C_ADDR_7BIT;
    masterXfer.subaddress = 0;
    masterXfer.subaddressSize = 0;
    masterXfer.flags = kI2C_TransferDefaultFlag;
    I2C_MasterInit(NXPNCI_I2C_INSTANCE, &masterConfig, sourceClock);

    IrqSem = xSemaphoreCreateBinary();

    return SUCCESS;
}

static Status tml_Reset(void) {
	GPIO_ClearPinsOutput(NXPNCI_VEN_GPIO, 1U << NXPNCI_VEN_PIN);
	Sleep(10);
	GPIO_SetPinsOutput(NXPNCI_VEN_GPIO, 1U << NXPNCI_VEN_PIN);
	Sleep(10);
	return SUCCESS;
}

static Status tml_Tx(uint8_t *pBuff, uint16_t buffLen) {
    if (I2C_WRITE(pBuff, buffLen) != kStatus_Success)
    {
    	Sleep(10);
    	if(I2C_WRITE(pBuff, buffLen) != kStatus_Success)
    	{
    		return ERROR;
    	}
    }

	return SUCCESS;
}

static Status tml_Rx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead) {
    if(I2C_READ(pBuff, 3) == kStatus_Success)
    {
    	if ((pBuff[2] + 3) <= buffLen)
    	{
			if (pBuff[2] > 0)
			{
				if(I2C_READ(&pBuff[3], pBuff[2]) == kStatus_Success)
				{
					*pBytesRead = pBuff[2] + 3;
				}
				else return ERROR;
			} else
			{
				*pBytesRead = 3;
			}
    	}
		else return ERROR;
   }
    else return ERROR;

	return SUCCESS;
}

static Status tml_WaitForRx(uint32_t timeout) {
	if (xSemaphoreTake(IrqSem, (timeout==0)?(portMAX_DELAY):(portTICK_PERIOD_MS*timeout)) != pdTRUE) return ERROR;
	return SUCCESS;
}

void tml_Connect(void) {
	tml_Init();
	tml_Reset();
}

void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent) {
	if(tml_Tx(pBuffer, BufferLen) == ERROR) *pBytesSent = 0;
	else *pBytesSent = BufferLen;
}

void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint16_t timeout) {
	if (tml_WaitForRx(timeout) == ERROR) *pBytes = 0;
	else tml_Rx(pBuffer, BufferLen, pBytes);
}


