/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : BitIoLdd2.c
**     Project     : FRDM-K22F_USB_CDC_FreeRTOS_PEx
**     Processor   : MK22FN512VDC12
**     Component   : BitIO_LDD
**     Version     : Component 01.033, Driver 01.03, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2022-05-05, 14:58, # CodeGen: 9
**     Abstract    :
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : BitIoLdd2
**          Pin for I/O                                    : PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO
**          Direction                                      : Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 0
**            Auto initialization                          : yes
**          Safe mode                                      : yes
**     Contents    :
**         Init   - LDD_TDeviceData* BitIoLdd2_Init(LDD_TUserData *UserDataPtr);
**         GetVal - bool BitIoLdd2_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         ClrVal - void BitIoLdd2_ClrVal(LDD_TDeviceData *DeviceDataPtr);
**         SetVal - void BitIoLdd2_SetVal(LDD_TDeviceData *DeviceDataPtr);
**         NegVal - void BitIoLdd2_NegVal(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file BitIoLdd2.c
** @version 01.03
** @brief
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup BitIoLdd2_module BitIoLdd2 module documentation
**  @{
*/         

/* MODULE BitIoLdd2. */

#include "FreeRTOS.h" /* FreeRTOS interface */
#include "BitIoLdd2.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserDataPtr;          /* Pointer to user data */
} BitIoLdd2_TDeviceData;               /* Device data structure type */

typedef BitIoLdd2_TDeviceData *BitIoLdd2_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {FreeRTOS RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static BitIoLdd2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/*
** ===================================================================
**     Method      :  BitIoLdd2_Init (component BitIO_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* BitIoLdd2_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  BitIoLdd2_TDeviceDataPtr DeviceDataPrv;

  /* {FreeRTOS RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Enable device clock gate */
  /* SIM_SCGC5: PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* Configure pin as output */
  /* GPIOA_PDDR: PDD|=4 */
  GPIOA_PDDR |= GPIO_PDDR_PDD(0x04);
  /* Set initialization value */
  /* GPIOA_PDOR: PDO&=~4 */
  GPIOA_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x04));
  /* Initialization of pin routing */
  /* PORTA_PCR2: ISF=0,MUX=1 */
  PORTA_PCR2 = (uint32_t)((PORTA_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_BitIoLdd2_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}
/*
** ===================================================================
**     Method      :  BitIoLdd2_GetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Returns the input/output value. If the direction is [input]
**         then the input value of the pin is read and returned. If the
**         direction is [output] then the last written value is read
**         and returned (see <Safe mode> property for limitations).
**         This method cannot be disabled if direction is [input].
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Input or output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
bool BitIoLdd2_GetVal(LDD_TDeviceData *DeviceDataPtr)
{
  uint32_t PortData;                   /* Port data masked according to the bit used */

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PortData = GPIO_PDD_GetPortDataOutput(BitIoLdd2_MODULE_BASE_ADDRESS) & BitIoLdd2_PORT_MASK;
  return (PortData != 0U) ? (bool)TRUE : (bool)FALSE;
}

/*
** ===================================================================
**     Method      :  BitIoLdd2_ClrVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Clears (set to zero) the output value. It is equivalent to
**         the [PutVal(FALSE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void BitIoLdd2_ClrVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_ClearPortDataOutputMask(BitIoLdd2_MODULE_BASE_ADDRESS, BitIoLdd2_PORT_MASK);
}

/*
** ===================================================================
**     Method      :  BitIoLdd2_SetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Sets (to one) the output value. It is equivalent to the
**         [PutVal(TRUE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void BitIoLdd2_SetVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_SetPortDataOutputMask(BitIoLdd2_MODULE_BASE_ADDRESS, BitIoLdd2_PORT_MASK);
}

/*
** ===================================================================
**     Method      :  BitIoLdd2_NegVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Negates (inverts) the output value. It is equivalent to the
**         [PutVal(!GetVal())]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void BitIoLdd2_NegVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_TogglePortDataOutputMask(BitIoLdd2_MODULE_BASE_ADDRESS, BitIoLdd2_PORT_MASK);
}

/* END BitIoLdd2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
