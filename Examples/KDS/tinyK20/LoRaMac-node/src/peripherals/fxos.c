/**
 * \file fxos.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 20.10.2015
 * \brief FXOS8700 driver implementation
 *
 */

#include "board.h"
#include "fxos.h"

static uint8_t I2cDeviceAddr = 0;

static bool FxosInitialized = false;

/*!
 * \brief Writes a byte at specified address in the device
 *
 * \param [IN]: addr
 * \param [IN]: data
 * \retval status [SUCCESS, FAIL]
 */
uint8_t FxosWrite(uint8_t addr, uint8_t data);

/*!
 * \brief Writes a buffer at specified address in the device
 *
 * \param [IN]: addr
 * \param [IN]: data
 * \param [IN]: size
 * \retval status [SUCCESS, FAIL]
 */
uint8_t FxosWriteBuffer(uint8_t addr, uint8_t *data, uint8_t size);

/*!
 * \brief Reads a byte at specified address in the device
 *
 * \param [IN]: addr
 * \param [OUT]: data
 * \retval status [SUCCESS, FAIL]
 */
uint8_t FxosRead(uint8_t addr, uint8_t *data);

/*!
 * \brief Reads a buffer at specified address in the device
 *
 * \param [IN]: addr
 * \param [OUT]: data
 * \param [IN]: size
 * \retval status [SUCCESS, FAIL]
 */
uint8_t FxosReadBuffer(uint8_t addr, uint8_t *data, uint8_t size);

/*!
 * \brief Sets the I2C device slave address
 *
 * \param [IN]: addr
 */
void FxosSetDeviceAddr(uint8_t addr);

/*!
 * \brief Gets the I2C device slave address
 *
 * \retval: addr Current device slave address
 */
uint8_t FxosGetDeviceAddr(void);

uint8_t FxosInit(uint8_t accelAddr)
{
    uint8_t regVal = 0x0;

    FxosSetDeviceAddr(accelAddr);

    if (FxosInitialized == false) {
        FxosInitialized = true;

        FxosRead(WHO_AM_I_REG, &regVal);
        /*! Fixed Device ID Number = 0xC7 */
        if (regVal != kFXOS_WHO_AM_I_Device_ID) {
            PRINTF("ERROR: Device id register returned 0x%02x where as 0xC7 was expected!\r\n",
                    regVal);
            return FAIL;
        }

        FxosReset();

        /* wait for a bit */
        for (uint32_t i = 0; i < 0xFFFF; i++) {
            __asm("NOP");
        }

        /* Place FXOS in standby mode */
        FxosWrite(CTRL_REG1, STANDBY);

        /*! Magnetometer control register 1
         * [7]: m_acal=0: auto calibration disabled
         * [6]: m_rst=0: no one-shot magnetic reset
         * [5]: m_ost=0: no one-shot magnetic measurement
         * [4:2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
         * [1:0]: m_hms=11=3: select hybrid mode with accel and magnetometer active
         */
        FxosWrite(M_CTRL_REG1, (HYBRID_ACTIVE | (M_OSR_800_HZ)));

        /* Magnetometer control register 2
         * [7]: reserved
         * [6]: reserved
         * [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the accelerometer registers
         * [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
         * [3]: m_maxmin_dis_ths=0
         * [2]: m_maxmin_rst=0
         * [1:0]: m_rst_cnt=00 to enable magnetic reset each cycle
         */
        FxosWrite(M_CTRL_REG2, M_HYB_AUTOINC_MASK);

        /* XYZ data config register
         * [7]: reserved
         * [6]: reserved
         * [5]: reserved
         * [4]: hpf_out=0
         * [3]: reserved
         * [2]: reserved
         * [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB
         */
        FxosWrite(XYZ_DATA_CFG_REG, FULL_SCALE_4G);

        /* Accelerometer control register 1
         * [7:6]: aslp_rate=00
         * [5:3]: dr=001 for 200Hz data rate (when in hybrid mode)
         * [2]: lnoise=1 for low noise mode
         * [1]: f_read=0 for normal 16 bit reads
         * [0]: active=1 to take the part out of standby and enable sampling
         */
        FxosWrite(CTRL_REG1, (ASLP_RATE_20MS | DATA_RATE_200HZ | LNOISE_MASK | ACTIVE));
        FxosRead(CTRL_REG1, &regVal);
        /* Read Control register again to ensure we are in active mode */
        if ((regVal & ACTIVE_MASK) != ACTIVE_MASK) {
            PRINTF("Unable to move FXOS8700CQ to Active mode\n\r");
            return 1;
        }

    }
    return SUCCESS;
}

uint8_t FxosReset(void)
{
    // Reset the FXOS with CTRL_REG2
    if (FxosWrite(CTRL_REG2, RST_MASK) == SUCCESS) {
        return SUCCESS;
    }
    return FAIL;
}

uint8_t FxosReadSensorData(accel_sensor_data_t *sensorData)
{
    uint8_t data[12];
    uint8_t status;
    status = FxosReadBuffer(OUT_X_MSB_REG, data, 12u);

    // copy the 14 bit accelerometer byte data into 16 bit words
    sensorData->accelX = (int16_t)(((data[0] << 8) | data[1])) >> 2;
    sensorData->accelY = (int16_t)(((data[2] << 8) | data[3])) >> 2;
    sensorData->accelZ = (int16_t)(((data[4] << 8) | data[5])) >> 2;
    // copy the magnetometer byte data into 16 bit words
    sensorData->magX = (data[6] << 8) | data[7];
    sensorData->magY = (data[8] << 8) | data[9];
    sensorData->magZ = (data[10] << 8) | data[11];

    return status;
}

uint8_t FxosWrite(uint8_t addr, uint8_t data)
{
    return FxosWriteBuffer(addr, &data, 1);
}

uint8_t FxosWriteBuffer(uint8_t addr, uint8_t *data, uint8_t size)
{
    return I2cWriteBuffer(&I2c, I2cDeviceAddr, addr, data, size);
}

uint8_t FxosRead(uint8_t addr, uint8_t *data)
{
    return FxosReadBuffer(addr, data, 1);
}

uint8_t FxosReadBuffer(uint8_t addr, uint8_t *data, uint8_t size)
{
    return I2cReadBuffer(&I2c, I2cDeviceAddr, addr, data, size);
}

void FxosSetDeviceAddr(uint8_t addr)
{
    I2cDeviceAddr = addr;
}

uint8_t FxosGetDeviceAddr(void)
{
    return I2cDeviceAddr;
}
