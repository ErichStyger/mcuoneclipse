/*
 * VS1053.h
 *
 *      Author: Erich Styger
 */

#ifndef VS1053_H_
#define VS1053_H_

/* VS1053 Registers */
#define VS_MODE         0x00
#define VS_STATUS       0x01
#define VS_BASS         0x02
#define VS_CLOCKF       0x03
#define VS_DECODE_TIME  0x04
#define VS_AUDATA       0x05
#define VS_WRAM         0x06
#define VS_WRAMADDR     0x07
#define VS_HDAT0        0x08
#define VS_HDAT1        0x09
#define VS_AIADDR       0x0A
#define VS_VOL          0x0B
#define VS_AICTRL0      0x0C
#define VS_AICTRL1      0x0D
#define VS_AICTRL2      0x0E
#define VS_AICTRL3      0x0F
#define VS_IO_DDR       0xC017
#define VS_IO_IDATA     0xC018
#define VS_IO_ODATA     0xC019

#include "CLS1.h" /* shell interface */
/*!
 * \brief Module command line parser
 * \param cmd Pointer to the command
 * \param handled Return value if the command has been handled by parser
 * \param io Shell standard I/O handle
 * \return Error code, ERR_OK if everything is OK
 */
uint8_t VS_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Event hook called before activating/accessing the SPI bus
 */
void VS_OnSPIActivate(void);

/*!
 * \brief Event hook called after activating/accessing the SPI bus
 */
void VS_OnSPIDeactivate(void);

/*!
 * \brief Event hook handler, called from an interrupt when we have received the MISO SPI data from the device.
 */
void VS_OnSPIBlockReceived(void);

/*!
 * \brief Plays a song file
 * \param fileName file name of the song
 * \param io Shell standard I/O for messages, NULL for no message printing
 * \return Error code, ERR_OK if everything is OK
 */
uint8_t VS_PlaySong(const uint8_t *fileName, const CLS1_StdIOType *io);

/*!
 * \brief Read a device register
 * \param reg Register address to read
 * \param value Pointer where to store the register value
 * \return Error code, ERR_OK if everything is OK
 */
uint8_t VS_ReadRegister(uint8_t reg, uint16_t *value);

/*!
 * \brief Write a device register
 * \param reg Register address to write
 * \param value VAlue to write to the register
 * \return Error code, ERR_OK if everything is OK
 */
uint8_t VS_WriteRegister(uint8_t reg, uint16_t value);

/*!
 * \brief Driver initialization.
 */
void VS_Init(void);

/*!
 * \brief Driver deinitalization
 */
void VS_Deinit(void);

#endif /* VS1053_H_ */
