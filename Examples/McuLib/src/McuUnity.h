/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_UNITY_H_
#define MCU_UNITY_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void McuUnity_putc(int c);
void McuUnity_flush(void);
void McuUnity_start(void);
void McuUnity_complete(void);

/*!
  \brief Get memory mapped argument number.
*/
uint32_t McuUnity_GetArgument(void);


/*!
 * \brief Callback of function pointer to read a terminal character.
 * \return The character or EOF.
 */
typedef int (*McuUnity_GetArgsCharFct)(void);

/*!
  \brief Get arguments passed from the test runner
  \param buffer Pointer to memory where to store the argument string
  \param bufSize Size of buffer in bytes
  \param readFct Callback to read from the input
  \return Number of bytes in buffer
*/
int McuUnity_GetArgs(unsigned char *buffer, size_t bufSize, McuUnity_GetArgsCharFct readFct);

/*!
 \brief Callback of function pointer to read a terminal character. Returns '\0' for now character present.
 */
typedef void (*McuUnity_ReadCharFct)(uint8_t *); /* Callback for an I/O input function. */

/*!
  \brief Get UART arguments passed
  \param buffer Pointer to memory where to store the argument string
  \param bufSize Size of buffer in bytes
  \param io Standard I/O descriptor
  \return Number of bytes in buffer
*/
int McuUnity_UART_GetArgs(unsigned char *buffer, size_t bufSize, McuUnity_ReadCharFct readFct);

/*!
  \brief Get J-Run arguments passed with RTT and --args
  \param buffer Pointer to memory where to store the argument string
  \param bufSize Size of buffer in bytes
  \return Number of bytes in buffer
*/
int McuUnity_RTT_GetArgs(unsigned char *buffer, size_t bufSize);

/*!
  \brief Get Semihosting arguments passed to application
  \param buffer Pointer to memory where to store the argument string
  \param bufSize Size of buffer in bytes
  \return Number of bytes in buffer
*/
int McuUnity_Semihost_GetArgs(unsigned char *buffer, size_t bufSize);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCU_UNITY_H_ */
