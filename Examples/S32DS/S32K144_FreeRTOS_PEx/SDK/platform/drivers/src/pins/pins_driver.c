/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
 * @file pins_driver.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * Function is defined for usage by application code.
 *
 */

#include "device_registers.h"
#include "pins_gpio_hw_access.h"
#if defined(FEATURE_PINS_DRIVER_USING_SIUL2)
#include "pins_siul2_hw_access.h"
#elif defined(FEATURE_PINS_DRIVER_USING_PORT)
#include "pins_port_hw_access.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_Init
 * Description   : This function configures the pins with the options provided
 * in the given structure.
 *
 * Implements    : PINS_DRV_Init_Activity
 *END**************************************************************************/
status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[])
{
    uint32_t i;
    status_t result = STATUS_SUCCESS;
    status_t pinInitStatus;
    for (i = 0U; i < pinCount; i++)
    {
        pinInitStatus = PINS_Init(&config[i]);
        if (STATUS_SUCCESS != pinInitStatus)
        {
            result = pinInitStatus;
        }
    }

    return result;
}

#if defined(FEATURE_PINS_DRIVER_USING_PORT)
#if FEATURE_PINS_HAS_PULL_SELECTION
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPullSel
 * Description   : This function configures the internal resistor.
 *
 * Implements    : PINS_DRV_SetPullSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetPullSel(PORT_Type * const base,
                         uint32_t pin,
                         port_pull_config_t pullConfig)
{
    PINS_SetPullSel(base, pin, pullConfig);
}

#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetMuxModeSel
 * Description   : This function configures the pin muxing.
 *
 * Implements    : PINS_DRV_SetMuxModeSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetMuxModeSel(PORT_Type * const base,
                            uint32_t pin,
                            port_mux_t mux)
{
    PINS_SetMuxModeSel(base, pin, mux);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPinIntSel
 * Description   : This function configures the port pin interrupt/DMA request.
 *
 * Implements    : PINS_DRV_SetPinIntSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetPinIntSel(PORT_Type * const base,
                           uint32_t pin,
                           port_interrupt_config_t intConfig)
{
    PINS_SetPinIntSel(base, pin, intConfig);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinIntSel
 * Description   : This function gets the current port pin interrupt/DMA request configuration.
 *
 * Implements    : PINS_DRV_GetPinIntSel_Activity
 *END**************************************************************************/
port_interrupt_config_t PINS_DRV_GetPinIntSel(const PORT_Type * const base,
                                              uint32_t pin)
{
    return PINS_GetPinIntSel(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPinIntFlagCmd
 * Description   : This function clears the individual pin-interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearPinIntFlagCmd_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPinIntFlagCmd(PORT_Type * const base,
                                 uint32_t pin)
{
    PINS_ClearPinIntFlagCmd(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_EnableDigitalFilter
 * Description   : This function enables digital filter feature for digital pin muxing.
 *
 * Implements    : PINS_DRV_EnableDigitalFilter_Activity
 *END**************************************************************************/
void PINS_DRV_EnableDigitalFilter(PORT_Type * const base,
                                  uint32_t pin)
{
    PINS_EnableDigitalFilter(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_DisableDigitalFilter
 * Description   : This function disables digital filter feature for digital
 * pin muxing.
 *
 * Implements    : PINS_DRV_DisableDigitalFilter_Activity
 *END**************************************************************************/
void PINS_DRV_DisableDigitalFilter(PORT_Type * const base,
                                   uint32_t pin)
{
    PINS_DisableDigitalFilter(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ConfigDigitalFilter
 * Description   : This function configures digital filter for port with
 * given configuration.
 *
 * Implements    : PINS_DRV_ConfigDigitalFilter_Activity
 *END**************************************************************************/
void PINS_DRV_ConfigDigitalFilter(PORT_Type * const base,
                                  const port_digital_filter_config_t * const config)
{
    PINS_ConfigDigitalFilter(base, config);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPortIntFlag
 * Description   : This function reads the entire port interrupt status flag.
 *
 * Implements    : PINS_DRV_GetPortIntFlag_Activity
 *END**************************************************************************/
uint32_t PINS_DRV_GetPortIntFlag(const PORT_Type * const base)
{
    return PINS_GetPortIntFlag(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPortIntFlagCmd
 * Description   : This function clears the entire port interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearPortIntFlagCmd_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPortIntFlagCmd(PORT_Type * const base)
{
    PINS_ClearPortIntFlagCmd(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinsDirection
 * Description   : This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * Implements    : PINS_DRV_GetPinsDirection_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPinsDirection(const GPIO_Type * const base)
{
    return PINS_GPIO_GetPinsDirection(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPinDirection
 * Description   : This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input).
 *
 * Implements    : PINS_DRV_SetPinDirection_Activity
 *END**************************************************************************/
void PINS_DRV_SetPinDirection(GPIO_Type * const base,
                              pins_channel_type_t pin,
                              pins_level_type_t direction)
{
    PINS_GPIO_SetPinDirection(base, pin, direction);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPinsDirection
 * Description   : This function sets the direction configuration for all pins
 * in a port. Pins corresponding to bits with value of '1' will be configured as
 * output and pins corresponding to bits with value of '0' will be configured as
 * input.
 *
 * Implements    : PINS_DRV_SetPinsDirection_Activity
 *END**************************************************************************/
void PINS_DRV_SetPinsDirection(GPIO_Type * const base,
                               pins_channel_type_t pins)
{
    PINS_GPIO_SetPinsDirection(base, pins);
}

#if FEATURE_PORT_HAS_INPUT_DISABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPortInputDisable
 * Description   : This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured
 * as input and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * Implements    : PINS_DRV_SetPortInputDisable_Activity
 *END**************************************************************************/
void PINS_DRV_SetPortInputDisable(GPIO_Type * const base,
                                  pins_channel_type_t pins)
{
    PINS_GPIO_SetPortInputDisable(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPortInputDisable
 * Description   : This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * Implements    : PINS_DRV_GetPortInputDisable_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPortInputDisable(const GPIO_Type * const base)
{
    return PINS_GPIO_GetPortInputDisable(base);
}
#endif /* FEATURE_PORT_HAS_INPUT_DISABLE */

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetGlobalPinControl
 * Description   : This function quickly configures multiple pins within the one port for
 * the same peripheral function with the same pin configuration. Supports up to 16 pins with
 * the lower or upper half of pin registers at the same port.
 *
 * Implements    : PINS_DRV_SetGlobalPinControl_Activity
 *END**************************************************************************/
void PINS_DRV_SetGlobalPinControl(PORT_Type * const base,
                                  uint16_t pins,
                                  uint16_t value,
                                  port_global_control_pins_t halfPort)
{
    PINS_SetGlobalPinControl(base, pins, value, halfPort);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetGlobalIntControl
 * Description   : This function quickly configures multiple pins within the one port for
 * the same peripheral function with the same interrupt configuration. Supports up to 16 pins with
 * the lower or upper half of pin registers at the same port.
 *
 * Implements    : PINS_DRV_SetGlobalIntControl_Activity
 *END**************************************************************************/
void PINS_DRV_SetGlobalIntControl(PORT_Type * const base,
                                  uint16_t pins,
                                  uint16_t value,
                                  port_global_control_pins_t halfPort)
{
    PINS_SetGlobalIntControl(base, pins, value, halfPort);
}

#if FEATURE_PINS_HAS_OVER_CURRENT
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetOverCurPortIntFlag
 * Description   : This function reads the entire over current port interrupt status flag.
 *
 * Implements    : PINS_DRV_GetOverCurPortIntFlag_Activity
 *END**************************************************************************/
uint32_t PINS_DRV_GetOverCurPortIntFlag(const PORT_Type * const base)
{
    return PINS_GetPortIntFlag(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearOverCurPortIntFlag
 * Description   : This function clears the entire over current port interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearOverCurPortIntFlag_Activity
 *END**************************************************************************/
void PINS_DRV_ClearOverCurPortIntFlag(PORT_Type * const base)
{
    PINS_ClearPortIntFlag(base);
}
#endif /* FEATURE_PINS_HAS_OVER_CURRENT */

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
#if FEATURE_PINS_HAS_PULL_SELECTION
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPullSel
 * Description   : This function configures the internal resistor.
 *
 * Implements    : PINS_DRV_SetPullSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetPullSel(PORT_Type * const base,
                         uint16_t pin,
                         port_pull_config_t pullConfig)
{
    PINS_SetPullSel(base, pin, pullConfig);
}

#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetOutputBuffer
 * Description   : This function configures the output buffer.
 *
 * Implements    : PINS_DRV_SetOutputBuffer_Activity
 *END**************************************************************************/
void PINS_DRV_SetOutputBuffer(PORT_Type * const base,
                              uint16_t pin,
                              bool enable,
                              port_mux_t mux)
{
    PINS_SetOutputBuffer(base, pin, enable, mux);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetInputBuffer
 * Description   : This function configures the input buffer.
 *
 * Implements    : PINS_DRV_SetInputBuffer_Activity
 *END**************************************************************************/
void PINS_DRV_SetInputBuffer(PORT_Type * const base,
                             uint16_t pin,
                             bool enable,
                             uint32_t inputMuxReg,
                             port_input_mux_t inputMux)
{
    PINS_SetInputBuffer(base, pin, enable, inputMuxReg, inputMux);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetExInt
 * Description   : This function configures the external interrupt.
 *
 * Implements    : PINS_DRV_SetExInt_Activity
 *END**************************************************************************/
void PINS_DRV_SetExInt(siul2_interrupt_config_t intConfig)
{
    PINS_SetExInt(intConfig);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPinExIntFlag
 * Description   : This function clears the individual pin external interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearPinExIntFlag_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPinExIntFlag(uint32_t eirqPinIdx)
{
    PINS_ClearPinExIntFlag(eirqPinIdx);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinExIntFlag
 * Description   : This function gets the individual pin external interrupt status flag.
 *
 * Implements    : PINS_DRV_GetPinExIntFlag_Activity
 *END**************************************************************************/
bool PINS_DRV_GetPinExIntFlag(uint32_t eirqPinIdx)
{
    return PINS_GetPinExIntFlag(eirqPinIdx);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearExIntFlag
 * Description   : This function clears the entire external interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearExIntFlag_Activity
 *END**************************************************************************/
void PINS_DRV_ClearExIntFlag(void)
{
    PINS_ClearExIntFlag();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetExIntFlag
 * Description   : This function reads the entire external interrupt status flag.
 *
 * Implements    : PINS_DRV_GetExIntFlag_Activity
 *END**************************************************************************/
uint32_t PINS_DRV_GetExIntFlag(void)
{
    return PINS_GetExIntFlag();
}

#endif /* FEATURE_PINS_DRIVER_USING_PORT */

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_WritePin
 * Description   : This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * Implements    : PINS_DRV_WritePin_Activity
 *END**************************************************************************/
void PINS_DRV_WritePin(GPIO_Type * const base,
                       pins_channel_type_t pin,
                       pins_level_type_t value)
{
    PINS_GPIO_WritePin(base, pin, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_WritePins
 * Description   : This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * Implements    : PINS_DRV_WritePins_Activity
 *END**************************************************************************/
void PINS_DRV_WritePins(GPIO_Type * const base,
                        pins_channel_type_t pins)
{
    PINS_GPIO_WritePins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinsOutput
 * Description   : This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * Implements    : PINS_DRV_GetPinsOutput_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPinsOutput(const GPIO_Type * const base)
{
    return PINS_GPIO_GetPinsOutput(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPins
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * Implements    : PINS_DRV_SetPins_Activity
 *END**************************************************************************/
void PINS_DRV_SetPins(GPIO_Type * const base,
                      pins_channel_type_t pins)
{
    PINS_GPIO_SetPins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPins
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * Implements    : PINS_DRV_ClearPins_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPins(GPIO_Type * const base,
                        pins_channel_type_t pins)
{
    PINS_GPIO_ClearPins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_TogglePins
 * Description   : This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * Implements    : PINS_DRV_TogglePins_Activity
 *END**************************************************************************/
void PINS_DRV_TogglePins(GPIO_Type * const base,
                         pins_channel_type_t pins)
{
    PINS_GPIO_TogglePins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ReadPins
 * Description   : This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * Implements    : PINS_DRV_ReadPins_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_ReadPins(const GPIO_Type * const base)
{
    return PINS_GPIO_ReadPins(base);
}

/******************************************************************************
 * EOF
 *****************************************************************************/
