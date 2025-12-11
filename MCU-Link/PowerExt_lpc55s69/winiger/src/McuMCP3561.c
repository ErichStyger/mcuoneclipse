/* This driver is base on https://github.com/fhnw-ise-qcrypt/mcp3564
* @version 0.1
* @date    2021-12-25
* @license Apache 2.0
* @author  Simon Burkhardt
*
*          FHNW University of Applied Sciences and Arts Northwestern Switzerland
*          https://www.fhnw.ch/ise/
*          https://github.com/fhnw-ise-qcrypt/mcp3564
*
*          GAP Quantum Technologies University of Geneva
*          https://www.unige.ch/gap/qic/qtech/
*
* @see     https://www.microchip.com/en-us/product/MCP3561
************************************************************************************
 */

#include "McuMCP3561.h"
#include "McuMCP3561config.h"
#include "McuSPI.h"
#include "McuLog.h"
#include "McuUtility.h"
#include "spibus.h"

#define MCP3561_DEVICE_ADDRESS_MASK  (MCP3561_CONFIG_DEVICE_ADDRESS<<6)
#define MCP3561_COMMAND_ADDR_POS    (2)

// USEFUL MASKS FOR ADC COMMUNICATION
#define MCP3561_DATA_READY_SMASK   (0x04) // 0b00000100 // Tells us whether data is ready from an SPI transaction
#define MCP3561_ADDRESS_MASK       (0x38) // 0b00111000
#define MCP3561_WRITE_COMMAND_MASK (0x02) // 0b00000010
#define MCP3561_WRITE_COMMAND      (MCP3561_WRITE_COMMAND_MASK | MCP3561_DEVICE_ADDRESS_MASK)
#define MCP3561_IREAD_COMMAND_MASK (0x03) // 0b00000011 // Incremental read command
#define MCP3561_IREAD_COMMAND      (MCP3561_IREAD_COMMAND_MASK | MCP3561_DEVICE_ADDRESS_MASK)
#define MCP3561_SREAD_COMMAND_MASK (0x01) // 0b1 // Static read command
#define MCP3561_SREAD_DATA_COMMAND (MCP3561_SREAD_COMMAND_MASK | MCP3561_DEVICE_ADDRESS_MASK)

#define MCP3561_CONFIG0_ADDR             (0x01)
#define MCP3561_CONFIG0_WRITE            (MCP3561_CONFIG0_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG0_SREAD            (MCP3561_CONFIG0_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG0_IREAD            (MCP3561_CONFIG0_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define MCP3561_CONFIG0_CLK_SEL_MASK     (0x30) // 0b00110000
#define _MCP3561_CONFIG0_VREF_SEL_POS    (7)
#define MCP3561_CONFIG0_VREF_SEL_INT     (0x01 << _MCP3561_CONFIG0_VREF_SEL_POS)  // 0b01 << _CONFIG0_CLK_VREF_POS
#define MCP3561_CONFIG0_VREF_SEL_EXT     (0x00 << _MCP3561_CONFIG0_VREF_SEL_POS)  // 0b00 << _CONFIG0_CLK_VREF_POS
#define _MCP3561_CONFIG0_CLK_SEL_POS     (4)
#define MCP3561_CONFIG0_CLK_SEL_INT      (0x03 << _MCP3561_CONFIG0_CLK_SEL_POS)  // 0b11 << _CONFIG0_CLK_SEL_POS
#define MCP3561_CONFIG0_CLK_SEL_EXT      (0x00 << _MCP3561_CONFIG0_CLK_SEL_POS)  // 0b00 << _CONFIG0_CLK_SEL_POS
#define _MCP3561_CONFIG0_CS_SEL_POS      (2)
#define MCP3561_CONFIG0_CS_SEL_15uA      (0x03 << _MCP3561_CONFIG0_CS_SEL_POS)
#define MCP3561_CONFIG0_CS_SEL_3_7uA     (0x02 << _MCP3561_CONFIG0_CS_SEL_POS)
#define MCP3561_CONFIG0_CS_SEL_0_9uA     (0x01 << _MCP3561_CONFIG0_CS_SEL_POS)
#define MCP3561_CONFIG0_CS_SEL_NONE      (0x00 << _MCP3561_CONFIG0_CS_SEL_POS)
#define _MCP3561_CONFIG0_ADC_MODE_POS    (0)
#define MCP3561_CONFIG0_ADC_MODE_CONV    (0x03 << _MCP3561_CONFIG0_ADC_MODE_POS) // 0b11 << _CONFIG0_ADC_MODE_POS
#define MCP3561_CONFIG0_ADC_MODE_STANDBY (0x02 << _MCP3561_CONFIG0_ADC_MODE_POS)
#define MCP3561_CONFIG0_ADC_MODE_OFF     (0x00 << _MCP3561_CONFIG0_ADC_MODE_POS)

#define MCP3561_CONFIG1_ADDR       (0x02)
#define MCP3561_CONFIG1_WRITE      (MCP3561_CONFIG1_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG1_SREAD      (MCP3561_CONFIG1_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG1_IREAD      (MCP3561_CONFIG1_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_CONFIG1_AMCLK_POS (6)
#define MCP3561_CONFIG1_AMCLK_DIV8 (0x03 << _MCP3561_CONFIG1_AMCLK_POS)
#define MCP3561_CONFIG1_AMCLK_DIV4 (0x02 << _MCP3561_CONFIG1_AMCLK_POS)
#define MCP3561_CONFIG1_AMCLK_DIV2 (0x01 << _MCP3561_CONFIG1_AMCLK_POS)
#define MCP3561_CONFIG1_AMCLK_DIV0 (0x00 << _MCP3561_CONFIG1_AMCLK_POS)
#define _MCP3561_CONFIG1_OSR_POS   (2)
#define MCP3561_CONFIG1_OSR_32     (0x00 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_64     (0x01 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_128    (0x02 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_256    (0x03 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_512    (0x04 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_1024   (0x05 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_2048   (0x06 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_4096   (0x07 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_8192   (0x08 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_16384  (0x09 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_20480  (0x0A << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_24576  (0x0B << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_40960  (0x0C << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_49152  (0x0D << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_81920  (0x0E << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_98304  (0x0F << _MCP3561_CONFIG1_OSR_POS)

#define MCP3561_CONFIG2_ADDR        (0x03)
#define MCP3561_CONFIG2_WRITE       (MCP3561_CONFIG2_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG2_SREAD       (MCP3561_CONFIG2_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG2_IREAD       (MCP3561_CONFIG2_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_CONFIG2_BOOST_POS  (6)
#define MCP3561_CONFIG2_BOOST_x2    (0x03 << _MCP3561_CONFIG2_BOOST_POS)
#define MCP3561_CONFIG2_BOOST_x1    (0x02 << _MCP3561_CONFIG2_BOOST_POS)
#define MCP3561_CONFIG2_BOOST_2DIV3 (0x01 << _MCP3561_CONFIG2_BOOST_POS)
#define MCP3561_CONFIG2_BOOST_DIV2  (0x00 << _MCP3561_CONFIG2_BOOST_POS)
#define _MCP3561_CONFIG2_GAIN_POS   (3)
#define MCP3561_CONFIG2_GAIN_x64    (0x07 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x32    (0x06 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x16    (0x05 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x8     (0x04 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x4     (0x03 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x2     (0x02 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x1     (0x01 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_DIV3   (0x00 << _MCP3561_CONFIG2_GAIN_POS)
#define _MCP3561_CONFIG2_AZ_MUX_POS (2)
#define MCP3561_CONFIG2_AZ_MUX_ON   (0x01 << _MCP3561_CONFIG2_AZ_MUX_POS)
#define MCP3561_CONFIG2_AZ_MUX_OFF  (0x00 << _MCP3561_CONFIG2_AZ_MUX_POS)
#define _MCP3561_CONFIG2_AZ_REF_POS (1)
#define MCP3561_CONFIG2_AZ_REF_ON   (0x01 << _MCP3561_CONFIG2_AZ_REF_POS)
#define MCP3561_CONFIG2_AZ_REF_OFF  (0x00 << _MCP3561_CONFIG2_AZ_REF_POS)

#define MCP3561_CONFIG3_ADDR                       (0x04)
#define MCP3561_CONFIG3_WRITE                      (MCP3561_CONFIG3_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG3_SREAD                      (MCP3561_CONFIG3_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG3_IREAD                      (MCP3561_CONFIG3_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_CONFIG3_CONV_MODE_POS             (6)
#define MCP3561_CONFIG3_CONV_MODE_CONTINUOUS       (0x03 << _MCP3561_CONFIG3_CONV_MODE_POS) // 0b11 << _CONFIG3_CONV_MODE_POS
#define MCP3561_CONFIG3_CONV_MODE_ONE_SHOT_STANDBY (0x02 << _MCP3561_CONFIG3_CONV_MODE_POS)
#define MCP3561_CONFIG3_CONV_MODE_ONE_SHOT_OFF     (0x00 << _MCP3561_CONFIG3_CONV_MODE_POS)
#define _MCP3561_CONFIG3_DATA_FORMAT_POS           (4)
#define MCP3561_CONFIG3_DATA_FORMAT_32BIT_CHID_SGN (0x03 << _MCP3561_CONFIG3_DATA_FORMAT_POS) // right justified data + channel ID + sign extension
#define MCP3561_CONFIG3_DATA_FORMAT_32BIT_SGN      (0x02 << _MCP3561_CONFIG3_DATA_FORMAT_POS) // right justified data + sign extension
#define MCP3561_CONFIG3_DATA_FORMAT_32BIT          (0x01 << _MCP3561_CONFIG3_DATA_FORMAT_POS) // left justified data
#define MCP3561_CONFIG3_DATA_FORMAT_24BIT          (0x00 << _MCP3561_CONFIG3_DATA_FORMAT_POS)
#define _MCP3561_CONFIG3_CRC_POS                   (3)
#define MCP3561_CONFIG3_CRC_FORMAT_32              (1 << _MCP3561_CONFIG3_CRC_POS)
#define MCP3561_CONFIG3_CRC_FORMAT_16              (0 << _MCP3561_CONFIG3_CRC_POS)
#define _MCP3561_CONFIG3_CRCCOM_POS                (2)
#define MCP3561_CONFIG3_CRCCOM_ON                  (1 << _MCP3561_CONFIG3_CRCCOM_POS)
#define MCP3561_CONFIG3_CRCCOM_OFF                 (0 << _MCP3561_CONFIG3_CRCCOM_POS)
#define _MCP3561_CONFIG3_OFFCAL_POS                (1)
#define MCP3561_CONFIG3_OFFCAL_ON                  (1 << _MCP3561_CONFIG3_OFFCAL_POS)
#define MCP3561_CONFIG3_OFFCAL_OFF                 (0 << _MCP3561_CONFIG3_OFFCAL_POS)
#define _MCP3561_CONFIG3_GAINCAL_POS               (0)
#define MCP3561_CONFIG3_GAINCAL_ON                 (1 << _MCP3561_CONFIG3_GAINCAL_POS)
#define MCP3561_CONFIG3_GAINCAL_OFF                (0 << _MCP3561_CONFIG3_GAINCAL_POS)

#define MCP3561_IRQ_ADDR            (0x05)
#define MCP3561_IRQ_WRITE           (MCP3561_IRQ_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_IRQ_SREAD           (MCP3561_IRQ_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_IRQ_IREAD           (MCP3561_IRQ_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_IRQ_DR_POS         (6)
#define _MCP3561_IRQ_CRCCFG_POS     (5)
#define _MCP3561_IRQ_POR_POS        (4)
#define _MCP3561_IRQ_MODE_POS       (2)
#define MCP3561_IRQ_MODE_MDAT_HIGHZ (2 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_MODE_MDAT_HIGH  (3 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_MODE_IRQ_HIGHZ  (0 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_MODE_IRQ_HIGH   (1 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_FASTCMD_ON      (1 << 1)
#define MCP3561_IRQ_FASTCMD_OFF     (0 << 1)
#define MCP3561_IRQ_STP_ON          (1 << 0)
#define MCP3561_IRQ_STP_OFF         (0 << 0)

#define MCP3561_MUX_ADDR         (0x06)
#define MCP3561_MUX_WRITE        (MCP3561_MUX_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_MUX_SREAD        (MCP3561_MUX_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_MUX_IREAD        (MCP3561_MUX_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define MCP3561_MUX_CH_IntVcm    (0xf)
#define MCP3561_MUX_CH_IntTemp_M (0xe)
#define MCP3561_MUX_CH_IntTemp_P (0xd)
#define MCP3561_MUX_CH_REFIN_n   (0xc)
#define MCP3561_MUX_CH_REFIN_p   (0xb)
#define MCP3561_MUX_CH_AVDD      (0x9)
#define MCP3561_MUX_CH_AGND      (0x8)
#define MCP3561_MUX_CH7          (0x7)
#define MCP3561_MUX_CH6          (0x6)
#define MCP3561_MUX_CH5          (0x5)
#define MCP3561_MUX_CH4          (0x4)
#define MCP3561_MUX_CH3          (0x3)
#define MCP3561_MUX_CH2          (0x2)
#define MCP3561_MUX_CH1          (0x1)
#define MCP3561_MUX_CH0          (0x0)
#define _MCP3561_MUX_VIN_P_POS   (4)
#define _MCP3561_MUX_VIN_N_POS   (0)

#define MCP3561_SCAN_CH_Offset    (1 << 0xF)
#define MCP3561_SCAN_CH_IntVcm    (1 << 0xE)
#define MCP3561_SCAN_CH_AVDD      (1 << 0xD)
#define MCP3561_SCAN_CH_TEMP      (1 << 0xC)
#define MCP3561_SCAN_CH_DIFF_D    (1 << 0xB)
#define MCP3561_SCAN_CH_DIFF_C    (1 << 0xA)
#define MCP3561_SCAN_CH_DIFF_B    (1 << 0x9)
#define MCP3561_SCAN_CH_DIFF_A    (1 << 0x8)
#define MCP3561_SCAN_CH7          (1 << 0x7)
#define MCP3561_SCAN_CH6          (1 << 0x6)
#define MCP3561_SCAN_CH5          (1 << 0x5)
#define MCP3561_SCAN_CH4          (1 << 0x4)
#define MCP3561_SCAN_CH3          (1 << 0x3)
#define MCP3561_SCAN_CH2          (1 << 0x2)
#define MCP3561_SCAN_CH1          (1 << 0x1)
#define MCP3561_SCAN_CH0          (1 << 0x0)

#define MCP3561_SCAN_ADDR      (0x07)
#define MCP3561_SCAN_WRITE     (MCP3561_SCAN_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_SCAN_SREAD     (MCP3561_SCAN_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_SCAN_IREAD     (MCP3561_SCAN_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_SCAN_DLY_POS  (21)
#define MCP3561_SCAN_DLY_512   (0x07 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_256   (0x06 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_128   (0x05 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_64    (0x04 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_32    (0x03 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_16    (0x02 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_8     (0x01 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_NONE  (0x00 << _MCP3561_SCAN_DLY_POS)

#define MCP3561_TIMER_ADDR      (0x08)
#define MCP3561_TIMER_WRITE     (MCP3561_TIMER_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_TIMER_SREAD     (MCP3561_TIMER_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_TIMER_IREAD     (MCP3561_TIMER_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_OFFSETCAL_ADDR  (0x09)
#define MCP3561_OFFSETCAL_WRITE (MCP3561_OFFSETCAL_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_OFFSETCAL_SREAD (MCP3561_OFFSETCAL_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_OFFSETCAL_IREAD (MCP3561_OFFSETCAL_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_GAINCAL_ADDR    (0x0A)
#define MCP3561_GAINCAL_WRITE   (MCP3561_GAINCAL_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_GAINCAL_SREAD   (MCP3561_GAINCAL_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_GAINCAL_IREAD   (MCP3561_GAINCAL_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_RSVD_ADDR       (0x0B)
#define MCP3561_RSVD_WRITE      (MCP3561_RSVD_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_RSVD_SREAD      (MCP3561_RSVD_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_RSVD_IREAD      (MCP3561_RSVD_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_LOCK_ADDR       (0x0D)
#define MCP3561_LOCK_WRITE      (MCP3561_LOCK_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_LOCK_SREAD      (MCP3561_LOCK_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_LOCK_IREAD      (MCP3561_LOCK_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_CRCCFG_ADDR     (0x0F)
#define MCP3561_CRCCFG_WRITE    (MCP3561_CRCCFG_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CRCCFG_SREAD    (MCP3561_CRCCFG_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CRCCFG_IREAD    (MCP3561_CRCCFG_ADDR << MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

// USEFUL FAST COMMANDS AND OTHER COMMANDS
#define MCP3561_FAST_COMMAND 0b00
//Device address[7:6], Fast Command[5:2], Command type[1:0]
// Resets the device registers to their default  values

// MCP3561_DEVICE_ADDRESS_BYTE | 0b111000
#define DEVICE_RESET_COMMAND                (0xE << MCP3561_COMMAND_ADDR_POS) | MCP3561_FAST_COMMAND
// Start/Restart an ADC conversion
#define DEVICE_ADC_START_RESTART_COMMAND    (0xA << MCP3561_COMMAND_ADDR_POS) | MCP3561_FAST_COMMAND
// Sets the ADC in Standby mode
#define DEVICE_ADC_STANDBY_COMMAND          (0xB << MCP3561_COMMAND_ADDR_POS) | MCP3561_FAST_COMMAND
// Sets the ADC in Shutdown mode
#define DEVICE_ADC_SHUTDOWN_COMMAND         (0xC << MCP3561_COMMAND_ADDR_POS) | MCP3561_FAST_COMMAND
// Sets the ADC in Full Shutdown mode
#define DEVICE_ADC_FULL_SHUTDOWN_COMMAND    (0xD << MCP3561_COMMAND_ADDR_POS) | MCP3561_FAST_COMMAND

uint8_t MCP3561_PollStatusByte(void) {
  uint8_t cmd[2] = {0,0};
  uint8_t rx[2] = {0,0};

	cmd[0] = MCP3561_MUX_SREAD;
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Lock();
	#endif
	SpiBus_Assert();
  McuSPI_SendReceiveBlock(cmd, rx, 1);
	SpiBus_Deassert();
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Unlock();
	#endif
	return rx[0];
}

void MCP3561_write(uint8_t data[4], uint16_t size){
  uint8_t dummyRx[4];
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Lock();
	#endif
	SpiBus_Assert();
  McuSPI_SendReceiveBlock(data, dummyRx, size);
	SpiBus_Deassert();
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Unlock();
	#endif
}

uint8_t MCP3561_sread(uint8_t cmd[2]){
	uint8_t reg8[2];
	
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Lock();
	#endif
	SpiBus_Assert();
  McuSPI_SendReceiveBlock(cmd, reg8, 2);
	SpiBus_Deassert();
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Unlock();
	#endif
	return reg8[1];
}

int32_t MCP3561_ReadADCData_24Bit(void) {
	uint8_t val[4] = {0,0,0,0};
	uint8_t cmd[4] = {0,0,0,0};
	cmd[0] = MCP3561_SREAD_DATA_COMMAND;
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Lock();
	#endif
	SpiBus_Assert();
	McuSPI_SendReceiveBlock(cmd, val, sizeof(cmd));
	SpiBus_Deassert();
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Unlock();
	#endif
	int32_t value = (((val[1] & 0x80) >> 7 ) << 31) | ( (val[1] & 0x7F) << 16) | (val[2] << 8) | val[3];
	return value;
}

int32_t MCP3561_ReadADCData_32Bit(void) {
	uint8_t val[5] = {0,0,0,0,0};
	uint8_t cmd[5] = {0,0,0,0,0};
	cmd[0] = MCP3561_SREAD_DATA_COMMAND;
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Lock();
	#endif
	SpiBus_Assert();
	McuSPI_SendReceiveBlock(cmd, val, sizeof(cmd));
	SpiBus_Deassert();
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Unlock();
	#endif
	int32_t value = ((val[1] & 0x01) << 31) | (val[2] << 16) | (val[3] << 8) | val[4];
	return value;
}

static uint32_t sRead24Bit(uint8_t reg) {
	uint8_t cmd[4] = {0,0,0,0};
	uint8_t val[4] = {0,0,0,0};

	cmd[0] = reg;
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Lock();
	#endif
	SpiBus_Assert();
	McuSPI_SendReceiveBlock(cmd, val, sizeof(cmd));
	SpiBus_Deassert();
	#if SpiBus_CONFIG_USE_MUTEX
	SpiBus_Unlock();
	#endif
	return (uint32_t)val[1] << 16 | (uint32_t)val[2] << 8 | val[3];	
}

uint32_t MCP3561_ReadScan(void) {
	return sRead24Bit(MCP3561_SCAN_SREAD);
}

uint32_t MCP3561_ReadTimer(void) {
	return sRead24Bit(MCP3561_TIMER_SREAD);
}

uint32_t MCP3561_ReadOffsetCal(void) {
	return sRead24Bit(MCP3561_OFFSETCAL_SREAD);
}

uint32_t MCP3561_ReadGainCal(void) {
	return sRead24Bit(MCP3561_GAINCAL_SREAD);
}

#if 0
int32_t MCP3561_ReadADCData_32Bit_Scan(void) {
	uint8_t val[5] = {0,0,0,0,0};
	uint8_t cmd[5] = {0,0,0,0,0};
	cmd[0] = MCP3561_SREAD_DATA_COMMAND;
	SpiBus_Lock();
	McuSPI_SendReceiveBlock(cmd, val, sizeof(cmd));
	SpiBus_Unlock();
	int32_t value[3] = { val[0] ,
			( (val[1] & 0xF0) >> 4 ) ,
			( (val[1] & 0x01) << 31) | (val[2] << 16) | (val[3] << 8) | val[4]};
	int32_t * ptr = &value[0];
	return ptr; /* !!!!! */
}
#endif

void MCP3561_Configure(void) {
	uint8_t cmd[4] = {0,0,0,0};
	
	/* Following the MCP3561 Errata Sheet recommendation (section 3) when internal oscillator is selected */
	uint32_t reg_val = 0x900F00;
	cmd[0]  = MCP3561_RSVD_WRITE;
	cmd[1] = (uint8_t)((reg_val >> 16) & 0xff);
	cmd[2] = (uint8_t)((reg_val >>  8) & 0xff);
	cmd[3] = (uint8_t)((reg_val)       & 0xff);
	MCP3561_write(cmd, 4);

	/* 8-bit CONFIG registers */
	cmd[0]  = MCP3561_CONFIG0_WRITE;
	cmd[1]  = MCP3561_USERCONF_REG0;
	MCP3561_write(cmd, 2);

	cmd[0]  = MCP3561_CONFIG1_WRITE;
	cmd[1]  = MCP3561_USERCONF_REG1;
	MCP3561_write(cmd, 2);

	cmd[0]  = MCP3561_CONFIG2_WRITE;
	cmd[1]  = MCP3561_USERCONF_REG2;
	cmd[1] += 3; /* last two bits must always be '11' */
	MCP3561_write(cmd, 2);

	cmd[0]  = MCP3561_CONFIG3_WRITE;
	cmd[1]  = MCP3561_USERCONF_REG3;
	MCP3561_write(cmd, 2);

	cmd[0]  = MCP3561_IRQ_WRITE;
	cmd[1]  = MCP3561_USERCONF_IRQ_REG;
	MCP3561_write(cmd, 2);

	McuMCP3561_MuxSingleEnded_RefInPlus(); 
}

void McuMCP3561_MuxSingleEnded_RefInPlus(void) {
	uint8_t cmd[4];
  cmd[0]  = MCP3561_MUX_WRITE;
	cmd[1]  = (MCP3561_MUX_CH_REFIN_p << 4) | MCP3561_MUX_CH_AGND;   // [7..4] VIN+ / [3..0] VIN-
	MCP3561_write(cmd, 2);
}

void McuMCP3561_MuxSingleEnded_Ch0(void) {
	uint8_t cmd[4];
  cmd[0]  = MCP3561_MUX_WRITE;
	cmd[1]  = (MCP3561_MUX_CH0 << 4) | MCP3561_MUX_CH_AGND;   // [7..4] VIN+ / [3..0] VIN-
	MCP3561_write(cmd, 2);
}

void McuMCP3561_MuxSingleEnded_Ch1(void) {
	uint8_t cmd[4];
  cmd[0]  = MCP3561_MUX_WRITE;
	cmd[1]  = (MCP3561_MUX_CH1 << 4) | MCP3561_MUX_CH_AGND;   // [7..4] VIN+ / [3..0] VIN-
	MCP3561_write(cmd, 2);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[96];

  McuShell_SendStatusStr((unsigned char*)"McuMCP3561", (unsigned char*)"McuMCP3561 ADC status\r\n", io->stdOut);
	uint8_t reg8 = 0;
	uint8_t cmd[5] = {0,0,0,0,0};

	cmd[0] = MCP3561_CONFIG0_SREAD;
	reg8 = MCP3561_sread(cmd);
  McuUtility_strcpy((unsigned char*)buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), reg8);
	switch((reg8>>4)&0x3) {
		case 0b00:
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CLK_SEL:ext");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CLK_SEL:intNoOutput");
		  break;
		case 0b11:
		McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CLK_SEL:intAMCLK");
		  break;
	}
	switch((reg8>>2)&0x3) {
		case 0b00:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CS_SEL:none");
			break;
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CS_SEL:0.9uA");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CS_SEL:3.7uA");
		  break;
		case 0b11:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CS_SEL:15uA");
		  break;
	}
	switch(reg8&0x3) {
		case 0b00:
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ADC_MODE:shutdown");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ADC_MODE:standby");
		  break;
		case 0b11:
		McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ADC_MODE:conversion");
		  break;
	}
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  CONFIG0", buf, io->stdOut);

  cmd[0] = MCP3561_CONFIG1_SREAD;
	reg8 = MCP3561_sread(cmd);
  McuUtility_strcpy((unsigned char*)buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), reg8);
	switch((reg8>>6)&0x3) {
		case 0b00:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" PRE:MCLK");
			break;
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" PRE:MCLK/2");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" PRE:MCLK/4");
		  break;
		case 0b11:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" PRE:MCLK/8");
		  break;
	}
	switch((reg8>>2)&0xF) {
		case 0b0000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:32");
			break;
		case 0b0001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:64");
			break;
		case 0b0010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:128");
			break;
		case 0b0011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:256");
			break;
		case 0b0100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:512");
			break;
		case 0b0101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:1024");
			break;
		case 0b0110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:2048");
			break;
		case 0b0111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:4096");
			break;
		case 0b1000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:8192");
			break;
		case 0b1001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:16384");
			break;
		case 0b1010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:20480");
			break;
		case 0b1011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:24576");
			break;
		case 0b1100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:40906");
			break;
		case 0b1101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:49152");
			break;
		case 0b1110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:81920");
			break;
		case 0b1111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OSR:98304");
			break;
	}
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  CONFIG1", buf, io->stdOut);

  cmd[0] = MCP3561_CONFIG2_SREAD;
	reg8 = MCP3561_sread(cmd);
  McuUtility_strcpy((unsigned char*)buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), reg8);
	switch((reg8>>6)&0x3) {
		case 0b00:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BOOST:0.5");
			break;
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BOOST:0.66");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BOOST:1");
		  break;
		case 0b11:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" BOOST:2");
		  break;
	}
	switch((reg8>>3)&0x7) {
		case 0b000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:1/3");
			break;
		case 0b001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:1");
			break;
		case 0b010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:2");
		  break;
		case 0b011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:4");
		  break;
		case 0b100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:8");
			break;
		case 0b101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:16");
		  break;
		case 0b110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:32");
		  break;
		case 0b111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAIN:64");
		  break;
	}
	switch((reg8>>2)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" AZ_MUX:dis");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" AZ_MUX:en");
			break;
	}
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  CONFIG2", buf, io->stdOut);

  cmd[0] = MCP3561_CONFIG3_SREAD;
	reg8 = MCP3561_sread(cmd);
  McuUtility_strcpy((unsigned char*)buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), reg8);
	switch((reg8>>6)&0x3) {
		case 0b00:
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CONV_MODE:1shot/off");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CONV_MODE:1shot/standby");
		  break;
		case 0b11:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CONV_MODE:cont");
		  break;
	}
	switch((reg8>>4)&0x3) {
		case 0b00:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" DATA:24bit");
			break;
		case 0b01:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" DATA:32bit/24l");
			break;
		case 0b10:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" DATA:32bit/s+24r");
		  break;
		case 0b11:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" DATA:32bit/24r+s");
		  break;
	}
	switch((reg8>>3)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CRC:16");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CRC:32");
			break;
	}
	switch((reg8>>2)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CRCCOMM:dis");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CRCCOMM:en");
			break;
	}
	switch((reg8>>1)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OFFCAL:dis");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" OFFCAL:en");
			break;
	}
	switch(reg8&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAINCAL:dis");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" GAINCAL:en");
			break;
	}
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  CONFIG3", buf, io->stdOut);

	cmd[0] = MCP3561_IRQ_SREAD;
	reg8 = MCP3561_sread(cmd);
  McuUtility_strcpy((unsigned char*)buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), reg8);
	switch((reg8>>6)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" DR:yes");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" DR:no");
			break;
	}
	switch((reg8>>5)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CRC:Error>");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" CRC:noErr");
			break;
	}
	switch((reg8>>4)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" POR:yes");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" POR:no");
			break;
	}
	switch((reg8>>3)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" MODE1:IRQ");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" MODE1:MDAT");
			break;
	}
	switch((reg8>>2)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" MODE0:highZ");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" MODE0:inactiveHigh");
			break;
	}
	switch((reg8>>1)&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" FASTCMD:dis");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" FASTCMD:en");
			break;
	}
	switch(reg8&0x1) {
		case 0b0:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" STP:dis");
			break;
		case 0b1:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" STP:en");
			break;
	}
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  IRQ", buf, io->stdOut);

	cmd[0] = MCP3561_MUX_SREAD;
	reg8 = MCP3561_sread(cmd);
  McuUtility_strcpy((unsigned char*)buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), reg8);
	switch((reg8>>4)&0xF) {
		case 0b0000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH0");
			break;
		case 0b0001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH1");
			break;
		case 0b0010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH2");
			break;
		case 0b0011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH3");
			break;
		case 0b0100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH4");
			break;
		case 0b0101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH5");
			break;
		case 0b0110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH6");
			break;
		case 0b0111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:CH7");
			break;
		case 0b1000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:AGND");
			break;
		case 0b1001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:AVDD");
			break;
		case 0b1010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:Reserved");
			break;
		case 0b1011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:REFIN+");
			break;
		case 0b1100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:REFIN-");
			break;
		case 0b1101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:TempP");
			break;
		case 0b1110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:TempM");
			break;
		case 0b1111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN+:VCM");
			break;
	}
	switch(reg8&0xF) {
		case 0b0000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH0");
			break;
		case 0b0001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH1");
			break;
		case 0b0010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH2");
			break;
		case 0b0011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH3");
			break;
		case 0b0100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH4");
			break;
		case 0b0101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH5");
			break;
		case 0b0110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH6");
			break;
		case 0b0111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:CH7");
			break;
		case 0b1000:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:AGND");
			break;
		case 0b1001:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:AVDD");
			break;
		case 0b1010:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:Reserved");
			break;
		case 0b1011:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:REFIN+");
			break;
		case 0b1100:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:REFIN-");
			break;
		case 0b1101:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:TempP");
			break;
		case 0b1110:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:TempM");
			break;
		case 0b1111:
			McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VIN-:VCM");
			break;
	}
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  MUX", buf, io->stdOut);

	McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
	McuUtility_strcatNum24Hex(buf, sizeof(buf), MCP3561_ReadScan());
	McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  SCAN", buf, io->stdOut);

	McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
	McuUtility_strcatNum24Hex(buf, sizeof(buf), MCP3561_ReadTimer());
	McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  TIMER", buf, io->stdOut);

	McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
	McuUtility_strcatNum24Hex(buf, sizeof(buf), MCP3561_ReadOffsetCal());
	McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  OFFSETCAL", buf, io->stdOut);

	McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
	McuUtility_strcatNum24Hex(buf, sizeof(buf), MCP3561_ReadGainCal());
	McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  GAINCAL", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuMCP3561", (unsigned char*)"Group of McuMCP3561 ADC commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
	McuShell_SendHelpStr((unsigned char*)"  mux refin+", (unsigned char*)"Mux REFIN+ (single ended)\r\n", io->stdOut);
	McuShell_SendHelpStr((unsigned char*)"  mux ch0", (unsigned char*)"Mux channel 0 (CH0) (single ended)\r\n", io->stdOut);
	McuShell_SendHelpStr((unsigned char*)"  mux ch1", (unsigned char*)"Mux channel 1 (CH1) (single ended)\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuMCP3561_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
	if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0 || McuUtility_strcmp((char*)cmd, "McuMCP3561 help")==0) {
    *handled = true;
    return PrintHelp(io);
	} else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuMCP3561 status")==0)){
	  *handled = true;
	  return PrintStatus(io);
	} else if (McuUtility_strcmp((char*)cmd, "McuMCP3561 mux refin+")==0){
	  *handled = true;
		McuMCP3561_MuxSingleEnded_RefInPlus();
	  return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "McuMCP3561 mux ch0")==0){
	  *handled = true;
		McuMCP3561_MuxSingleEnded_Ch0();
	  return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "McuMCP3561 mux ch1")==0){
	  *handled = true;
		McuMCP3561_MuxSingleEnded_Ch1();
	  return ERR_OK;
	}
	return ERR_OK;
}

void McuMCP3561_Deinit(void) {
}

void McuMCP3561_Init(void) {
}