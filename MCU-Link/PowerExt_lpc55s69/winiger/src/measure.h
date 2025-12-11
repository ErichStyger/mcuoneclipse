/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 #ifndef MEASURE_H_
 #define MCP3MEASURE_H_561_H_
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 #include "McuShell.h"
 #include "McuGPIO.h"
/*!
 * \brief Shell command line parser
 * \param cmd Pointer to the command string
 * \param handled If command has been recognized and handled
 * \param io I/O hander used for output
 * \return Error code, ERR_OK if everything is fine
 */
uint8_t Measure_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
int32_t muxAndMeasureDUT_CurrentRaw(void);
int32_t convertRawVoltageToMilliVolt(int32_t);
int32_t Measure_Offset(int, int32_t*);
int32_t measure(int);

 /*!
  * \brief Module de-initialization
  */
 void Meaure_Deinit(void);
 
 /*!
  * \brief Module Initialization
  */
 void Measure_Init(void);
 extern McuGPIO_Handle_t ctrl_high_current;
 
 #ifdef __cplusplus
 }  /* extern "C" */
 #endif
 
#endif /* MEASURE_H_ */