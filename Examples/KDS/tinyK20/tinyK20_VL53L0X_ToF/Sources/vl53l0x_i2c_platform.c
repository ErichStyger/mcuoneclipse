#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_platform.h"
#include "GI2C1.h"

#define VL53L0X_I2C_ADDR  0x29 ///< Default sensor I2C address

static void LOG_ERROR(const char *str) {
  /*! \todo */
}

/**
 * @brief  Initialise platform comms.
 *
 * @param  comms_type      - selects between I2C and SPI
 * @param  comms_speed_khz - unsigned short containing the I2C speed in kHz
 *
 * @return status - status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_comms_initialise(uint8_t  comms_type, uint16_t comms_speed_khz){

	if(comms_type == SPI){
	  LOG_ERROR("SPI not supported. Use I2C.\r\n");
		return 1;
	} else if(comms_type != I2C){
		LOG_ERROR("Invalid communication protocol with VL53L0X. Use I2C.\r\n");
		return 1;
	}
#if 0
	uint32_t nrf_speed;

	if(comms_speed_khz == 400){
		nrf_speed = NRF_TWI_FREQ_400K;
	} else if(comms_speed_khz == 250){
		nrf_speed = NRF_TWI_FREQ_250K;
	} else if(comms_speed_khz == 100){
		nrf_speed = NRF_TWI_FREQ_100K;
	} else {
		LOG_ERROR("Invalid TWI comms speed.");
		return 1;
	}

	ret_code_t ret;
	const nrf_drv_twi_config_t config =
	{
	   .scl                = TWI_SCL_M,
	   .sda                = TWI_SDA_M,
	   .frequency          = nrf_speed,
	   .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
	   .clear_bus_init     = false
	};

    ret = nrf_drv_twi_init(&m_twi_master, &config, NULL, NULL);

	if (NRF_SUCCESS == ret)
	{
		nrf_drv_twi_enable(&m_twi_master);
    		NRF_LOG_DEBUG("TWI init successful\r\n");
	} else {
		LOG_ERROR("TWI init failed\r\n");
	}

	return ret;
#else
	return 0;
#endif
};

/**
 * @brief  Close platform comms.
 *
 * @return status - status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_comms_close(void){
	//nrf_drv_twi_disable(&m_twi_master);
	return 0;
}

/**
 * @brief Writes the supplied byte buffer to the device
 *
 * Wrapper for SystemVerilog Write Multi task
 *
 * @code
 *
 * Example:
 *
 * uint8_t *spad_enables;
 *
 * int status = VL53L0X_write_multi(RET_SPAD_EN_0, spad_enables, 36);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index - uint8_t register index value
 * @param  pdata - pointer to uint8_t buffer containing the data to be written
 * @param  count - number of bytes in the supplied byte buffer
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_write_multi(uint8_t address, uint8_t index, uint8_t  *pdata, int32_t count)
{
  uint8_t res;

  res = GI2C1_WriteAddress(address, &index, sizeof(index), pdata, count);
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Reads the requested number of bytes from the device
 *
 * Wrapper for SystemVerilog Read Multi task
 *
 * @code
 *
 * Example:
 *
 * uint8_t buffer[COMMS_BUFFER_SIZE];
 *
 * int status = status  = VL53L0X_read_multi(DEVICE_ID, buffer, 2)
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index - uint8_t register index value
 * @param  pdata - pointer to the uint8_t buffer to store read data
 * @param  count - number of uint8_t's to read
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_read_multi(uint8_t address,  uint8_t index, uint8_t  *pdata, int32_t count)
{
  uint8_t res;

  res = GI2C1_ReadAddress(address, &index, sizeof(index), pdata, count);
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Writes a single byte to the device
 *
 * Wrapper for SystemVerilog Write Byte task
 *
 * @code
 *
 * Example:
 *
 * uint8_t page_number = MAIN_SELECT_PAGE;
 *
 * int status = VL53L0X_write_byte(PAGE_SELECT, page_number);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index - uint8_t register index value
 * @param  data  - uint8_t data value to write
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */


int32_t VL53L0X_write_byte(uint8_t address,  uint8_t index, uint8_t data)
{
  uint8_t res;

  res = GI2C1_WriteAddress(address, &index, sizeof(index), &data, sizeof(data));
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Writes a single word (16-bit unsigned) to the device
 *
 * Manages the big-endian nature of the device (first byte written is the MS byte).
 * Uses SystemVerilog Write Multi task.
 *
 * @code
 *
 * Example:
 *
 * uint16_t nvm_ctrl_pulse_width = 0x0004;
 *
 * int status = VL53L0X_write_word(NVM_CTRL__PULSE_WIDTH_MSB, nvm_ctrl_pulse_width);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index - uint8_t register index value
 * @param  data  - uin16_t data value write
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_write_word(uint8_t address,  uint8_t index, uint16_t  data)
{
  uint8_t res;

  res = GI2C1_WriteAddress(address, &index, sizeof(index), (uint8_t*)&data, sizeof(data));
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Writes a single dword (32-bit unsigned) to the device
 *
 * Manages the big-endian nature of the device (first byte written is the MS byte).
 * Uses SystemVerilog Write Multi task.
 *
 * @code
 *
 * Example:
 *
 * uint32_t nvm_data = 0x0004;
 *
 * int status = VL53L0X_write_dword(NVM_CTRL__DATAIN_MMM, nvm_data);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index - uint8_t register index value
 * @param  data  - uint32_t data value to write
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_write_dword(uint8_t address, uint8_t index, uint32_t  data)
{
  uint8_t res;

  res = GI2C1_WriteAddress(address, &index, sizeof(index), (uint8_t*)&data, sizeof(data));
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Reads a single byte from the device
 *
 * Uses SystemVerilog Read Byte task.
 *
 * @code
 *
 * Example:
 *
 * uint8_t device_status = 0;
 *
 * int status = VL53L0X_read_byte(STATUS, &device_status);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index  - uint8_t register index value
 * @param  pdata  - pointer to uint8_t data value
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_read_byte(uint8_t address,  uint8_t index, uint8_t  *pdata)
{
  uint8_t res;

  res = GI2C1_ReadAddress(address, &index, sizeof(index), pdata, 1);
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Reads a single word (16-bit unsigned) from the device
 *
 * Manages the big-endian nature of the device (first byte read is the MS byte).
 * Uses SystemVerilog Read Multi task.
 *
 * @code
 *
 * Example:
 *
 * uint16_t timeout = 0;
 *
 * int status = VL53L0X_read_word(TIMEOUT_OVERALL_PERIODS_MSB, &timeout);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index  - uint8_t register index value
 * @param  pdata  - pointer to uint16_t data value
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_read_word(uint8_t address,  uint8_t index, uint16_t *pdata)
{
  uint8_t res;

  res = GI2C1_ReadAddress(address, &index, sizeof(index), (uint8_t*)pdata, 2);
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}

/**
 * @brief  Reads a single dword (32-bit unsigned) from the device
 *
 * Manages the big-endian nature of the device (first byte read is the MS byte).
 * Uses SystemVerilog Read Multi task.
 *
 * @code
 *
 * Example:
 *
 * uint32_t range_1 = 0;
 *
 * int status = VL53L0X_read_dword(RANGE_1_MMM, &range_1);
 *
 * @endcode
 *
 * @param  address - uint8_t device address value
 * @param  index - uint8_t register index value
 * @param  pdata - pointer to uint32_t data value
 *
 * @return status - SystemVerilog status 0 = ok, 1 = error
 *
 */

int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata)
{
  uint8_t res;

  res = GI2C1_ReadAddress(address, &index, sizeof(index), (uint8_t*)pdata, 4);
  if (res!=ERR_OK) {
    return 1; /* error */
  }
  return 0; /* ok */
}


