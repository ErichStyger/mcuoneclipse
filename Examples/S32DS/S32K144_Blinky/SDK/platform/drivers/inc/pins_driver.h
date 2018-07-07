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

#ifndef PINS_DRIVER_H
#define PINS_DRIVER_H

#include <stddef.h>
#include "device_registers.h"
#include "status.h"

/*!
 * @defgroup pins_driver PINS Driver
 * @ingroup pins
 * @details This section describes the programming interface of the PINS driver.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
/*!
 * @brief Type of a GPIO channel representation
 * Implements : pins_channel_type_t_Class
 */
typedef uint32_t pins_channel_type_t;

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
/*!
 * @brief Type of a GPIO channel representation
 * Implements : pins_channel_type_t_Class
 */
typedef uint16_t pins_channel_type_t;

#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */

/*!
 * @brief Type of a port levels representation.
 * Implements : pins_level_type_t_Class
 */
typedef uint8_t pins_level_type_t;

/*!
 * @brief Configures the port data direction
 * Implements : port_data_direction_t_Class
 */
typedef enum
{
    GPIO_INPUT_DIRECTION       = 0x0U,  /*!< General purpose input direction.       */
    GPIO_OUTPUT_DIRECTION      = 0x1U,  /*!< General purpose output direction.      */
    GPIO_UNSPECIFIED_DIRECTION = 0x2U   /*!< General purpose unspecified direction. */
} port_data_direction_t;

#if FEATURE_PINS_HAS_PULL_SELECTION
/*!
 * @brief Internal resistor pull feature selection
 * Implements : port_pull_config_t_Class
 */
typedef enum
{
    PORT_INTERNAL_PULL_NOT_ENABLED   = 0U,  /*!< internal pull-down or pull-up resistor is not enabled.           */
    PORT_INTERNAL_PULL_DOWN_ENABLED  = 1U,  /*!< internal pull-down resistor is enabled. @internal gui name="Down"*/
    PORT_INTERNAL_PULL_UP_ENABLED    = 2U   /*!< internal pull-up resistor is enabled. @internal gui name="Up"    */
} port_pull_config_t;
#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

#if FEATURE_PINS_HAS_OPEN_DRAIN
/*!
 * @brief Configures the Open Drain Enable field.
 * Implements : port_open_drain_t_Class
 */
typedef enum
{
    PORT_OPEN_DRAIN_DISABLED  = 0U, /*!< Output is CMOS       */
    PORT_OPEN_DRAIN_ENABLED   = 1U  /*!< Output is open drain */
} port_open_drain_t;
#endif /* FEATURE_PINS_HAS_OPEN_DRAIN */

#if FEATURE_PINS_HAS_DRIVE_STRENGTH
/*!
 * @brief Configures the drive strength.
 * Implements : port_drive_strength_t_Class
 */
typedef enum
{
#if FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL
    PORT_STRENGTH_DISABLED      = 0U, /*!< Output driver disabled                                         */
    PORT_LOW_DRIVE_STRENGTH     = 1U, /*!< Low drive strength is configured. Resistor is set to 240 Ohm   */
    PORT_STR1_DRIVE_STRENGTH    = 1U, /*!< Resistor is set to 240 Ohm                                     */
    PORT_STR2_DRIVE_STRENGTH    = 2U, /*!< Resistor is set to 240 / 2 Ohm = 120 Ohm                       */
    PORT_STR3_DRIVE_STRENGTH    = 3U, /*!< Resistor is set to 240 / 3 Ohm = 80 Ohm                        */
    PORT_STR4_DRIVE_STRENGTH    = 4U, /*!< Resistor is set to 240 / 4 Ohm = 60 Ohm                        */
    PORT_STR5_DRIVE_STRENGTH    = 5U, /*!< Resistor is set to 240 / 5 Ohm = 48 Ohm                        */
    PORT_STR6_DRIVE_STRENGTH    = 6U, /*!< Resistor is set to 240 / 6 Ohm = 40 Ohm                        */
    PORT_STR7_DRIVE_STRENGTH    = 7U, /*!< Resistor is set to 240 / 7 Ohm = 34 Ohm                        */
    PORT_HIGH_DRIVE_STRENGTH    = 7U  /*!< High drive strength is configured. Resistor is set to 240 Ohm  */
#else /* if not FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL */
    PORT_LOW_DRIVE_STRENGTH     = 0U,    /*!< low drive strength is configured. @internal gui name="Low"  */
    PORT_HIGH_DRIVE_STRENGTH    = 1U     /*!< high drive strength is configured. @internal gui name="High"*/
#endif /* if FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL */
} port_drive_strength_t;
#endif /* FEATURE_PINS_HAS_DRIVE_STRENGTH */

#ifdef FEATURE_PINS_DRIVER_USING_PORT
/*!
 * @brief Configures the Pin mux selection
 * Implements : port_mux_t_Class
 */
typedef enum
{
    PORT_PIN_DISABLED = 0U,  /*!< corresponding pin is disabled, but is used as an analog pin.*/
    PORT_MUX_AS_GPIO  = 1U,  /*!< corresponding pin is configured as GPIO.                    */
    PORT_MUX_ALT2     = 2U,  /*!< chip-specific                                               */
    PORT_MUX_ALT3     = 3U,  /*!< chip-specific                                               */
    PORT_MUX_ALT4     = 4U,  /*!< chip-specific                                               */
    PORT_MUX_ALT5     = 5U,  /*!< chip-specific                                               */
    PORT_MUX_ALT6     = 6U,  /*!< chip-specific                                               */
    PORT_MUX_ALT7     = 7U   /*!< chip-specific                                               */
} port_mux_t;

/*!
 * @brief Configures the interrupt generation condition.
 * Implements : port_interrupt_config_t_Class
 */
typedef enum
{
    PORT_DMA_INT_DISABLED  = 0x0U,  /*!< Interrupt/DMA request is disabled.                   */
    PORT_DMA_RISING_EDGE   = 0x1U,  /*!< DMA request on rising edge.                          */
    PORT_DMA_FALLING_EDGE  = 0x2U,  /*!< DMA request on falling edge.                         */
    PORT_DMA_EITHER_EDGE   = 0x3U,  /*!< DMA request on either edge.                          */
#if FEATURE_PORT_HAS_FLAG_SET_ONLY
    PORT_FLAG_RISING_EDGE  = 0x5U,  /*!< Flag sets on rising edge, no interrupt is generated. */
    PORT_FLAG_FALLING_EDGE = 0x6U,  /*!< Flag sets on falling edge, no interrupt is generated.*/
    PORT_FLAG_EITHER_EDGE  = 0x7U,  /*!< Flag sets on either edge, no interrupt is generated. */
#endif /* FEATURE_PORT_HAS_FLAG_SET_ONLY */
    PORT_INT_LOGIC_ZERO    = 0x8U,  /*!< Interrupt when logic 0.                              */
    PORT_INT_RISING_EDGE   = 0x9U,  /*!< Interrupt on rising edge.                            */
    PORT_INT_FALLING_EDGE  = 0xAU,  /*!< Interrupt on falling edge.                           */
    PORT_INT_EITHER_EDGE   = 0xBU,  /*!< Interrupt on either edge.                            */
    PORT_INT_LOGIC_ONE     = 0xCU   /*!< Interrupt when logic 1.                              */
#if FEATURE_PORT_HAS_TRIGGER_OUT
    PORT_HIGH_TRIGGER_OUT  = 0xDU   /*!< Enable active high trigger output, flag is disabled. */
    PORT_LOW_TRIGGER_OUT   = 0xEU   /*!< Enable active low trigger output, flag is disabled.  */
#endif /* FEATURE_PORT_HAS_TRIGGER_OUT */
} port_interrupt_config_t;

#if FEATURE_PINS_HAS_SLEW_RATE
/*!
 * @brief Configures the Slew Rate field.
 * Implements : port_slew_rate_t_Class
 */
typedef enum
{
    PORT_FAST_SLEW_RATE     = 0U,   /*!< fast slew rate is configured. @internal gui name="Fast" */
    PORT_SLOW_SLEW_RATE     = 1U    /*!< slow slew rate is configured. @internal gui name="Slow" */
} port_slew_rate_t;
#endif /* FEATURE_PINS_HAS_SLEW_RATE */

/*!
 * @brief Clock source for the digital input filters
 * Implements : port_digital_filter_clock_t_Class
 */
typedef enum
{
    PORT_DIGITAL_FILTER_BUS_CLOCK  = 0U, /*!< Digital filters are clocked by the bus clock. @internal gui name="BUS" */
    PORT_DIGITAL_FILTER_LPO_CLOCK  = 1U  /*!< Digital filters are clocked by the LPO clock. @internal gui name="LPO" */
} port_digital_filter_clock_t;

/*!
 * @brief The digital filter configuration
 * Implements : port_digital_filter_config_t_Class
 */
typedef struct
{
    port_digital_filter_clock_t clock;  /*!< The digital filter clock for port */
    uint8_t                     width;  /*!< The digital filter width value */
} port_digital_filter_config_t;

/*!
 * @brief The port global pin/interuppt control registers
 * Implements : port_global_control_pins_t_Class
 */
typedef enum
{
    PORT_GLOBAL_CONTROL_LOWER_HALF_PINS = 0U, /*!< the lower of pins is configured. @internal gui name="Lower" */
    PORT_GLOBAL_CONTROL_UPPER_HALF_PINS = 1U  /*!< the upper of pins is configured. @internal gui name="Upper" */
} port_global_control_pins_t;

#if FEATURE_PINS_HAS_OVER_CURRENT
/*!
 * @brief Over-current detection feature
 * Implements : port_over_current_config_t_Class
 */
typedef enum
{
    PORT_OVER_CURRENT_DISABLED      = 0U,   /*!< Over-current feature pin is disabled.          */
    PORT_OVER_CURRENT_INT_DISABLED  = 1U,   /*!< Over-current is enabled, interrupt is disabled */
    PORT_OVER_CURRENT_INT_ENABLED   = 2U    /*!< Over-current is enabled, interrupt is enabled  */
} port_over_current_config_t;
#endif /* FEATURE_PINS_HAS_OVER_CURRENT */

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
#if FEATURE_SIUL2_HAS_DDR_PAD
/*!
 * @brief Configures the DDR type to:
 *      DDR3, DDR3L modes   - 00
 *      LPDDR2 mode         - 10
 * Implements : port_ddr_type_t_Class
 */
typedef enum
{
    DDR_DDR3_MODE       = 0x0U,  /*!< DDR3 / LPDDR3 mode  */
    DDR_LPDDR2_MODE     = 0x2U   /*!< LPDDR2 mode         */
} port_ddr_type_t;

/*!
 * @brief Configures the DDR trimming delay to:
 *      min delay           - 00
 *      +50ps delay         - 01
 *      +100ps delay        - 10
 *      +150ps delay        - 11
 * Implements : port_ddr_trim_delay_t_Class
 */
typedef enum
{
    DDR_MIN_DELAY       = 0x0U,  /*!< min delay     */
    DDR_50PS_DELAY      = 0x1U,  /*!< +50ps delay   */
    DDR_100PS_DELAY     = 0x2U,  /*!< +100ps delay  */
    DDR_150PS_DELAY     = 0x3U   /*!< +150ps delay  */
} port_ddr_trim_delay_t;

/*!
 * @brief Configures the DDR crosspoint adjusment of DDR CLK cell output signal to:
 *      No crosspoint change                    - 00
 *      Output crosspoint is +70mV higher       - 01
 *      Output crosspoint is -70mV lower        - 10
 *      Output crosspoint is +140mV higher      - 11
 * Implements : port_ddr_crpoint_t_Class
 */
typedef enum
{
    DDR_NO_CRPOINT      = 0x0U,  /*!< No crosspoint change               */
    DDR_MINUS_CRPOINT   = 0x1U,  /*!< Output crosspoint is +70mV higher  */
    DDR_PLUS_CRPOINT    = 0x2U,  /*!< Output crosspoint is -70mV lower   */
    DDR_DOUBLE_CRPOINT  = 0x3U   /*!< Output crosspoint is +140mV higher */
} port_ddr_crpoint_t;

/*!
 * @brief Configures the DDR output signal duty cycle adjustment to:
 *      No duty cycle change            - 00
 *      Left side input pulse shrink    - 01
 *      Right side input pulse shrink   - 10
 *      Right side input pulse shrink   - 11
 * Implements : port_ddr_trim_t_Class
 */
typedef enum
{
    DDR_NO_TRIM         = 0x0U,  /*!< No duty cycle change             */
    DDR_LEFT_TRIM       = 0x1U,  /*!< Left side input pulse shrink     */
    DDR_RIGHT_TRIM      = 0x2U   /*!< Right side input pulse shrink    */
} port_ddr_trim_t;

/*!
 * @brief Configures DDR input to select differential or CMOS input receiver mode.
 * Implements : port_ddr_input_t_Class
 */
typedef enum
{
    PORT_DDR_INPUT_CMOS          = 0U, /*!< CMOS input receiver mode             */
    PORT_DDR_INPUT_DIFFERENTIAL  = 1U  /*!< differential DDR input receiver mode */
} port_ddr_input_t;

/*!
 * @brief Configures the On die Termination to select ODT strength in DDR3 mode.
 * Implements : port_on_die_termination_t_Class
 */
typedef enum
{
    PORT_STR0_ON_DIE_TERMINATION    = 0U, /*!< Not applicable                         */
    PORT_STR1_ON_DIE_TERMINATION    = 1U, /*!< Termination resistor is set to 120 Ohm */
    PORT_STR2_ON_DIE_TERMINATION    = 2U, /*!< Termination resistor is set to 60 Ohm  */
    PORT_STR3_ON_DIE_TERMINATION    = 3U, /*!< Termination resistor is set to 40 Ohm  */
    PORT_STR4_ON_DIE_TERMINATION    = 4U, /*!< Termination resistor is set to 30 Ohm  */
    PORT_STR5_ON_DIE_TERMINATION    = 5U, /*!< Termination resistor is set to 24 Ohm  */
    PORT_STR6_ON_DIE_TERMINATION    = 6U, /*!< Termination resistor is set to 20 Ohm  */
    PORT_STR7_ON_DIE_TERMINATION    = 7U  /*!< Termination resistor is set to 17 Ohm  */
} port_on_die_termination_t;

/*!
 * @brief Defines the DDR configuration
 *
 * This structure is used to configure the pins for the DDR controller
 * Implements : pin_ddr_config_t_Class
 */
typedef struct
{
    port_ddr_type_t         ddrSelection;           /*!< DDR type                   */
    port_ddr_trim_delay_t   trimmingDelay;          /*!< DDR trimming delay value   */
    port_ddr_crpoint_t      crosspointAdjustment;   /*!< Crosspoint adjusment       */
    port_ddr_trim_t         trimmingAdjustment;     /*!< DDR trimming type          */
} pin_ddr_config_t;

#endif /* FEATURE_SIUL2_HAS_DDR_PAD */

/*!
 * @brief Configures the Pin mux selection
 * Implements : port_mux_t_Class
 */
typedef enum
{
    PORT_MUX_AS_GPIO    = 0U,   /*!< corresponding pin is configured as GPIO */
    PORT_MUX_ALT1       = 1U,   /*!< chip-specific                           */
    PORT_MUX_ALT2       = 2U,   /*!< chip-specific                           */
    PORT_MUX_ALT3       = 3U,   /*!< chip-specific                           */
    PORT_MUX_ALT4       = 4U,   /*!< chip-specific                           */
    PORT_MUX_ALT5       = 5U,   /*!< chip-specific                           */
    PORT_MUX_ALT6       = 6U,   /*!< chip-specific                           */
    PORT_MUX_ALT7       = 7U,   /*!< chip-specific                           */
    PORT_MUX_ALT8       = 8U,   /*!< chip-specific                           */
    PORT_MUX_ALT9       = 9U,   /*!< chip-specific                           */
    PORT_MUX_ALT10      = 10U,  /*!< chip-specific                           */
    PORT_MUX_ALT11      = 11U,  /*!< chip-specific                           */
    PORT_MUX_ALT12      = 12U,  /*!< chip-specific                           */
    PORT_MUX_ALT13      = 13U,  /*!< chip-specific                           */
    PORT_MUX_ALT14      = 14U,  /*!< chip-specific                           */
    PORT_MUX_ALT15      = 15U   /*!< chip-specific                           */
} port_mux_t;

/*!
 * @brief Configures the interrupt generation condition.
 * Implements : siul2_interrupt_type_t_Class
 */
typedef enum
{
    SIUL2_INT_DISABLE       = 0x0U,  /*!< Interrupt disable.         */
    SIUL2_INT_RISING_EDGE   = 0x1U,  /*!< Interrupt on rising edge.  */
    SIUL2_INT_FALLING_EDGE  = 0x2U,  /*!< Interrupt on falling edge. */
    SIUL2_INT_EITHER_EDGE   = 0x3U   /*!< Interrupt on either edge.  */
} siul2_interrupt_type_t;

#if FEATURE_SIUL2_EXTERNAL_INT_SUPPORT_DMA
/*!
 * @brief Configures the interrupt DMA select.
 * Implements : siul2_interrupt_dma_select_t_Class
 */
typedef enum
{
    SIUL2_INT_USING_INTERUPT = 0x0U, /*!< Executived by an interrupt request */
    SIUL2_INT_USING_DMA      = 0x1U  /*!< Executived by an DMA request       */
} siul2_interrupt_dma_select_t;
#endif /* FEATURE_SIUL2_EXTERNAL_INT_SUPPORT_DMA */

/*!
 * @brief Interrupt configuration structure.
 * Implements : siul2_interrupt_config_t_Class
 */
typedef struct
{
    uint8_t eirqPinIdx;
    siul2_interrupt_type_t intEdgeSel;
#if FEATURE_SIUL2_EXTERNAL_INT_SUPPORT_DMA
    siul2_interrupt_dma_select_t intExeSel;
#endif
} siul2_interrupt_config_t;

/*!
 * @brief Configures the Output Buffer Enable field.
 * Implements : port_output_buffer_t_Class
 */
typedef enum
{
    PORT_OUTPUT_BUFFER_DISABLED     = 0U, /*!< Output buffer disabled */
    PORT_OUTPUT_BUFFER_ENABLED      = 1U  /*!< Output buffer enabled  */
} port_output_buffer_t;

/*!
 * @brief Configures the Input Buffer Enable field.
 * Implements : port_input_buffer_t_Class
 */
typedef enum
{
    PORT_INPUT_BUFFER_DISABLED     = 0U, /*!< Input buffer disabled */
    PORT_INPUT_BUFFER_ENABLED      = 1U  /*!< Input buffer enabled  */
} port_input_buffer_t;

#if FEATURE_SIUL2_HAS_HYSTERESIS
/*!
 * @brief Configures the Hysteresis Enable field.
 * Implements : port_hysteresis_t_Class
 */
typedef enum
{
    PORT_HYSTERESYS_CMOS        = 0U, /*!< CMOS Input            */
    PORT_HYSTERESYS_SCHMITT     = 1U, /*!< Schmitt trigger input */
    PORT_HYSTERESYS_DISABLED    = 0U, /*!< DISABLED              */
    PORT_HYSTERESYS_ENABLED     = 1U  /*!< ENABLED               */
} port_hysteresis_t;
#endif /* FEATURE_SIUL2_HAS_HYSTERESIS */

#if FEATURE_SIUL2_HAS_INVERT_DATA_OUTPUT
/*!
 * @brief Configures the Invert Data Output field.
 * Implements : port_invert_output_t_Class
 */
typedef enum
{
    PORT_INVERT_OUTPUT_DISABLED  = 0U, /*!< Invert Data Output disabled */
    PORT_INVERT_OUTPUT_ENABLED   = 1U  /*!< Invert Data Output enabled  */
} port_invert_output_t;
#endif /* FEATURE_SIUL2_HAS_INVERT_DATA_OUTPUT */

#if FEATURE_SIUL2_HAS_INVERT_DATA_INPUT
/*!
 * @brief Configures the Invert Data Input field.
 * Implements : port_invert_input_t_Class
 */
typedef enum
{
    PORT_INVERT_INPUT_DISABLED   = 0U, /*!< Invert Data Input disabled  */
    PORT_INVERT_INPUT_ENABLED    = 1U  /*!< Invert Data Input enabled   */
} port_invert_input_t;
#endif /* FEATURE_SIUL2_HAS_INVERT_DATA_INPUT */

#if FEATURE_SIUL2_HAS_PULL_KEEPER
/*!
 * @brief Configures the Pull / Keep Enable field.
 * Implements : port_pull_keep_t_Class
 */
typedef enum
{
    PORT_PULL_KEEP_DISABLED  = 0U, /*!< Pull/Keeper Disabled  */
    PORT_PULL_KEEP_ENABLED   = 1U  /*!< Pull/Keeper Enabled   */
} port_pull_keep_t;

/*!
 * @brief Configures the Pull / Keep Select Field (PUE).
 * Implements : port_pull_keeper_select_t_Class
 */
typedef enum
{
    PORT_KEEPER_ENABLED      = 0U, /*!< Keeper enable                       */
    PORT_PULL_ENABLED        = 1U  /*!< Pullup or pulldown resistors enable */
} port_pull_keeper_select_t;

/*!
 * @brief Configures the Pull Up / Down Config Field.
 * Implements : port_pull_up_down_t_Class
 */
typedef enum
{
    PORT_PULL_DOWN_ENABLED   = 0U,  /*!< 100 kOhm pulldown */
    PORT_PULL_UP_MEDIUM      = 1U,  /*!< 50 kOhm pullup    */
    PORT_PULL_UP_HIGH        = 2U,  /*!< 100 kOhm pullup   */
    PORT_PULL_UP_LOW         = 3U   /*!< 33 kOhm pullup    */
} port_pull_up_down_t;

#endif /* FEATURE_SIUL2_HAS_PULL_KEEPER */

#if FEATURE_SIUL2_HAS_ANALOG_PAD
/*!
 * @brief Configures the Analog Pad Control.
 * Implements : port_analog_pad_t_Class
 */
typedef enum
{
    PORT_ANALOG_PAD_CONTROL_DISABLED = 0U, /*!< Disable (the switch is off)                                 */
    PORT_ANALOG_PAD_CONTROL_ENABLED  = 1U  /*!< Enable (another module can control the state of the switch) */
} port_analog_pad_t;
#endif /* FEATURE_SIUL2_HAS_ANALOG_PAD */

/*!
 * @brief Configures the DAISY (on CPU_S32V234) or SSS (on CPU_MPC5748G) bitfield in the IMCR register.
 * Implements : port_input_mux_t_Class
 */
typedef enum
{
    PORT_INPUT_MUX_ALT0      = 0U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT1      = 1U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT2      = 2U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT3      = 3U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT4      = 4U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT5      = 5U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT6      = 6U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT7      = 7U,   /*!< Chip-specific     */
#if (FEATURE_SIUL2_INPUT_SOURCE_SELECT_WIDTH >= 4U)
    PORT_INPUT_MUX_ALT8      = 8U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT9      = 9U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT10     = 10U,  /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT11     = 11U,  /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT12     = 12U,  /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT13     = 13U,  /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT14     = 14U,  /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT15     = 15U,  /*!< Chip-specific     */
#endif
    PORT_INPUT_MUX_NO_INIT           /*!< No initialization */
} port_input_mux_t;

/*!
 * @brief Configures the Safe Mode Control.
 * Implements : port_safe_mode_t_Class
 */
typedef enum
{
    PORT_SAFE_MODE_DISABLED     = 0U, /*!< To drive pad in hi-z state using OBE = 0, when FCCU in fault state.
                                       * The OBE will be driven by IP/SIUL when FCCU leaves the fault state. */
    PORT_SAFE_MODE_ENABLED      = 1U  /*!< No effect on IP/SIUL driven OBE value */
} port_safe_mode_t;

#if FEATURE_SIUL2_HAS_SLEW_RATE_CONTROL
/*!
 * @brief Configures the slew rate control.
 * Implements : port_slew_rate_control_t_Class
 */
typedef enum
{
    HALF_STRENGTH_WITH_SLEWRATE_CONTROL     = 0u, /*!< Half Strength with Slewrate Control     */
    FULL_STRENGTH_WITH_SLEWRATE_CONTROL     = 1u, /*!< Full Strength with Slewrate Control     */
    HALF_STRENGTH_WITHOUT_SLEWRATE_CONTROL  = 2u, /*!< Half Strength without Slewrate Control  */
    FULL_STRENGTH_WITHOUT_SLEWRATE_CONTROL  = 3u  /*!< Full Strength without Slewrate Control  */
} port_slew_rate_control_t;
#endif /* FEATURE_SIUL2_HAS_SLEW_RATE_CONTROL  */

#if FEATURE_PINS_HAS_SLEW_RATE
/*!
 * @brief Configures the Slew Rate field.
 * Implements : port_slew_rate_t_Class
 */
typedef enum
{
    PORT_LOW_SLEW_RATE      = 0U,   /*!< Low    frequency slew rate (50 Mhz) */
    PORT_MEDIUM_SLEW_RATE   = 1U,   /*!< Medium frequency slew rate (100Mhz) */
    PORT_MEDIUM_SLEW_RATE2  = 2U,   /*!< Medium frequency slew rate (100Mhz) */
    PORT_HIGH_SLEW_RATE     = 3U    /*!< High   frequency slew rate (200Mhz) */
} port_slew_rate_t;
#endif

#endif /* FEATURE_PINS_DRIVER_USING_SIUL2 */

/*!
 * @brief Defines the converter configuration
 *
 * This structure is used to configure the pins
 * Implements : pin_settings_config_t_Class
 */
typedef struct
{
#ifdef FEATURE_PINS_DRIVER_USING_PORT
    PORT_Type         *         base;              /*!< Port base pointer.                        */
#elif defined FEATURE_PINS_DRIVER_USING_SIUL2
    SIUL2_Type        *         base;              /*!< SIUL2 base pointer.                       */
#endif
    uint32_t                    pinPortIdx;        /*!< Port pin number.                          */
#if FEATURE_PINS_HAS_PULL_SELECTION
    port_pull_config_t          pullConfig;        /*!< Internal resistor pull feature selection. */
#endif
#if FEATURE_PINS_HAS_SLEW_RATE
    port_slew_rate_t            rateSelect;        /*!< Slew rate selection.                      */
#endif
#if FEATURE_PORT_HAS_PASSIVE_FILTER
    bool                        passiveFilter;     /*!< Passive filter configuration.             */
#endif
#if FEATURE_PINS_HAS_OPEN_DRAIN
    port_open_drain_t           openDrain;         /*!< Configures open drain.                    */
#endif
#if FEATURE_PINS_HAS_DRIVE_STRENGTH
    port_drive_strength_t       driveSelect;       /*!< @brief Configures the drive strength.     */
#endif
    port_mux_t                  mux;               /*!< @brief Pin (C55: Out) mux selection.      */
#if FEATURE_PORT_HAS_PIN_CONTROL_LOCK
    bool                        pinLock;           /*!< Lock pin control register or not.         */
#endif
#ifdef FEATURE_PINS_DRIVER_USING_PORT
    port_interrupt_config_t     intConfig;         /*!< Interrupt generation condition.           */
    bool                        clearIntFlag;      /*!< Clears the interrupt status flag.         */
#if FEATURE_PINS_HAS_OVER_CURRENT
    port_over_current_config_t  overCurConfig;     /*!< Over-current detection feature.           */
#endif
#endif
    GPIO_Type         *         gpioBase;          /*!< GPIO base pointer.                        */
    port_data_direction_t       direction;         /*!< Configures the port data direction.       */
    bool                        digitalFilter;     /*!< Enables digital filter.                   */
#ifdef FEATURE_PINS_DRIVER_USING_SIUL2
    port_input_mux_t inputMux[FEATURE_SIUL2_INPUT_MUX_WIDTH];   /*!< Configures the input muxing selection */
    uint32_t         inputMuxReg[FEATURE_SIUL2_INPUT_MUX_WIDTH];/*!< Configures the input muxing register  */
    port_output_buffer_t        outputBuffer;      /*!< Configures the Output Buffer Enable.      */
    port_input_buffer_t         inputBuffer;       /*!< Configures the Input Buffer Enable.       */
    siul2_interrupt_config_t    intConfig;         /*!< Interrupt generation condition.           */
#if FEATURE_SIUL2_HAS_SAFE_MODE_CONTROL
    port_safe_mode_t            safeMode;          /*!< Configures the Safe Mode Control.         */
#endif /* FEATURE_SIUL2_HAS_SAFE_MODE_CONTROL */
#if FEATURE_SIUL2_HAS_SLEW_RATE_CONTROL
    port_slew_rate_control_t    slewRateCtrlSel;   /*!< Configures the Slew Rate Control field.   */
#endif /* FEATURE_SIUL2_HAS_SLEW_RATE_CONTROL */
#if FEATURE_SIUL2_HAS_HYSTERESIS
    port_hysteresis_t           hysteresisSelect;  /*!< Configures the Hysteresis Enable.         */
#endif /* FEATURE_SIUL2_HAS_HYSTERESIS */
#if FEATURE_SIUL2_HAS_DDR_PAD
    pin_ddr_config_t            ddrConfiguration;  /*!< Structure that configures the DDR         */
    port_ddr_input_t            inputMode;         /*!< Configures DDR input receiver mode.       */
    port_on_die_termination_t   odtSelect;         /*!< Configures the ODT to select strength.    */
#endif /* FEATURE_SIUL2_HAS_DDR_PAD */
#if FEATURE_SIUL2_HAS_INVERT_DATA_OUTPUT
    port_invert_output_t        invertOutput;      /*!< Configures the Invert Data Output.        */
#endif /* FEATURE_SIUL2_HAS_INVERT_DATA_OUTPUT */
#if FEATURE_SIUL2_HAS_INVERT_DATA_INPUT
    port_invert_input_t         invertInput;       /*!< Configures the Invert Data Input.         */
#endif /* FEATURE_SIUL2_HAS_INVERT_DATA_INPUT */
#if FEATURE_SIUL2_HAS_PULL_KEEPER
    port_pull_keep_t            pullKeepEnable;    /*!< Configures the Pull / Keep Enable.        */
    port_pull_keeper_select_t   pullKeepSelect;    /*!< Configures the Pull / Keep Select.        */
    port_pull_up_down_t         pullSelect;        /*!< Configures the Pull Up / Down Config.     */
#endif /* FEATURE_SIUL2_HAS_PULL_KEEPER */
#if FEATURE_SIUL2_HAS_ANALOG_PAD
    port_analog_pad_t           analogPadCtrlSel;  /*!< Configures the Analog Pad Control         */
#endif /* FEATURE_SIUL2_HAS_ANALOG_PAD */
#endif /* FEATURE_PINS_DRIVER_USING_SIUL2 */
    pins_level_type_t           initValue;         /*!< Initial value                             */
} pin_settings_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name PINS DRIVER API.
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] pinCount The number of configured pins in structure
 * @param[in] config The configuration structure
 * @return The status of the operation
 */
status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[]);

#ifdef FEATURE_PINS_DRIVER_USING_PORT
#if FEATURE_PINS_HAS_PULL_SELECTION
/*!
 * @brief Configures the internal resistor.
 *
 * This function configures the internal resistor.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] pullConfig The pull configuration
 */
void PINS_DRV_SetPullSel(PORT_Type * const base,
                         uint32_t pin,
                         port_pull_config_t pullConfig);

#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

/*!
 * @brief Configures the pin muxing.
 *
 * This function configures the pin muxing.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] mux Pin muxing slot selection
 */
void PINS_DRV_SetMuxModeSel(PORT_Type * const base,
                            uint32_t pin,
                            port_mux_t mux);

/*!
 * @brief Configures the port pin interrupt/DMA request.
 *
 * This function configures the port pin interrupt/DMA request.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] intConfig  Interrupt configuration
 */
void PINS_DRV_SetPinIntSel(PORT_Type * const base,
                           uint32_t pin,
                           port_interrupt_config_t intConfig);

/*!
 * @brief Gets the current port pin interrupt/DMA request configuration.
 *
 * This function gets the current port pin interrupt/DMA request configuration.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @return Interrupt configuration
 */
port_interrupt_config_t PINS_DRV_GetPinIntSel(const PORT_Type * const base,
                                              uint32_t pin);

/*!
 * @brief Clears the individual pin-interrupt status flag.
 *
 * This function clears the individual pin-interrupt status flag.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 */
void PINS_DRV_ClearPinIntFlagCmd(PORT_Type * const base,
                                 uint32_t pin);

/*!
 * @brief Enables digital filter for digital pin muxing
 *
 * This function enables digital filter feature for digital pin muxing
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 */
void PINS_DRV_EnableDigitalFilter(PORT_Type * const base,
                                  uint32_t pin);

/*!
 * @brief Disables digital filter for digital pin muxing
 *
 * This function disables digital filter feature for digital pin muxing
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 */
void PINS_DRV_DisableDigitalFilter(PORT_Type * const base,
                                   uint32_t pin);

/*!
 * @brief Configures digital filter for port with given configuration
 *
 * This function configures digital filter for port with given configuration
 *
 * Note: Updating the filter configuration must be done only after all filters are disabled.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] config the digital filter configuration struct
 */
void PINS_DRV_ConfigDigitalFilter(PORT_Type * const base,
                                  const port_digital_filter_config_t * const config);

/*!
 * @brief Reads the entire port interrupt status flag
 *
 * This function reads the entire port interrupt status flag.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @return All 32 pin interrupt status flags
 */
uint32_t PINS_DRV_GetPortIntFlag(const PORT_Type * const base);

/*!
 * @brief Clears the entire port interrupt status flag.
 *
 * This function clears the entire port interrupt status flag.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 */
void PINS_DRV_ClearPortIntFlagCmd(PORT_Type * const base);

/*!
 * @brief Quickly configures multiple pins with the same pin configuration.
 *
 * This function quickly configures multiple pins within the one port for the same peripheral
 * function with the same pin configuration. Supports up to 16 pins with the lower or upper
 * half of pin registers at the same port.
 *
 * Note: The set global interrupt control function (PINS_DRV_SetGlobalIntControl) cannot be
 * configured if you ever used this function at the same port
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pins Pin mask where each bit represents one pin. For each bit:
 *        - 0: pins corresponding to bits with value of '1' is updated with the value input
 *        - 1: pins corresponding to bits with value of '0' is not updated with the value input
 * @param[in] value the config value will be updated for the pins are set to '1'
 * @param[in] halfPort the lower or upper half of pin registers at the same port
 */
void PINS_DRV_SetGlobalPinControl(PORT_Type * const base,
                                  uint16_t pins,
                                  uint16_t value,
                                  port_global_control_pins_t halfPort);

/*!
 * @brief Quickly configures multiple pins with the same interrupt configuration.
 *
 * This function quickly configures multiple pins within the one port for the same peripheral
 * function with the same interrupt configuration. Supports up to 16 pins with the lower or
 * upper half of pin registers at the same port.
 *
 * Note: The set global pin control function (PINS_DRV_SetGlobalPinControl) cannot be
 * configured if you ever used this function at the same port
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pins Pin mask where each bit represents one pin. For each bit:
 *        - 0: pins corresponding to bits with value of '1' is updated with the value input
 *        - 1: pins corresponding to bits with value of '0' is not updated with the value input
 * @param[in] value the config value will be updated for the pins are set to '1'
 * @param[in] halfPort the lower or upper half of pin registers at the same port
 */
void PINS_DRV_SetGlobalIntControl(PORT_Type * const base,
                                  uint16_t pins,
                                  uint16_t value,
                                  port_global_control_pins_t halfPort);

#if FEATURE_PINS_HAS_OVER_CURRENT
/*!
 * @brief Reads the entire over current port interrupt status flag
 *
 * This function reads the entire over current port interrupt status flag.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @return All 32 pin interrupt status flags
 */
uint32_t PINS_DRV_GetOverCurPortIntFlag(const PORT_Type * const base);

/*!
 * @brief Clears the entire over current port interrupt status flag.
 *
 * This function clears the entire over current port interrupt status flag.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 */
void PINS_DRV_ClearOverCurPortIntFlag(PORT_Type * const base);
#endif /* FEATURE_PINS_HAS_OVER_CURRENT */

/*!
 * @brief Get the pins directions configuration for a port
 *
 * This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO directions. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
pins_channel_type_t PINS_DRV_GetPinsDirection(const GPIO_Type * const base);

/*!
 * @brief Configure the direction for a certain pin from a port
 *
 * This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input)
 *
 * Note: With some platforms when you want to set a pin as output only and disable
 * input completely, it is required to call PINS_DRV_SetPortInputDisable if platform
 * has this feature.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pin The pin number for which to configure the direction
 * @param[in] direction The pin direction:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
void PINS_DRV_SetPinDirection(GPIO_Type * const base,
                              pins_channel_type_t pin,
                              pins_level_type_t direction);

/*!
 * @brief Set the pins directions configuration for a port
 *
 * This function sets the direction configuration for all pins
 * in a port. Pins corresponding to bits with value of '1' will be configured as
 * output and pins corresponding to bits with value of '0' will be configured as
 * input.
 *
 * Note: With some platforms when you want to set a pin as output only and disable
 * input completely, it is required to call PINS_DRV_SetPortInputDisable if platform
 * has this feature.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pins Pin mask where each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
void PINS_DRV_SetPinsDirection(GPIO_Type * const base,
                               pins_channel_type_t pins);

#if FEATURE_PORT_HAS_INPUT_DISABLE
/*!
 * @brief Set the pins input disable state for a port
 *
 * This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured
 * as input and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pins Pin mask where each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
void PINS_DRV_SetPortInputDisable(GPIO_Type * const base,
                                  pins_channel_type_t pins);

/*!
 * @brief Get the pins input disable state for a port
 *
 * This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO input state. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
pins_channel_type_t PINS_DRV_GetPortInputDisable(const GPIO_Type * const base);
#endif /* FEATURE_PORT_HAS_INPUT_DISABLE */

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
#if FEATURE_PINS_HAS_PULL_SELECTION
/*!
 * @brief Configures the internal resistor.
 *
 * This function configures the internal resistor.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] pullConfig The pull configuration
 */
void PINS_DRV_SetPullSel(PORT_Type * const base,
                         uint16_t pin,
                         port_pull_config_t pullConfig);

#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

/*!
 * @brief Configures the output buffer.
 *
 * This function configures the output buffer.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] enable Enable output buffer
 * @param[in] mux Pin muxing slot selection
 */
void PINS_DRV_SetOutputBuffer(PORT_Type * const base,
                              uint16_t pin,
                              bool enable,
                              port_mux_t mux);

/*!
 * @brief Configures the input buffer.
 *
 * This function configures the input buffer.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] enable Enable input buffer
 * @param[in] inputMuxReg Pin muxing register slot selection
 * @param[in] inputMux Pin muxing slot selection
 */
void PINS_DRV_SetInputBuffer(PORT_Type * const base,
                             uint16_t pin,
                             bool enable,
                             uint32_t inputMuxReg,
                             port_input_mux_t inputMux);

/*!
 * @brief Configures the external interrupt.
 *
 * This function configures the external interrupt.
 *
 * @param[in] intConfig Configuration edge for interrupt
 */
void PINS_DRV_SetExInt(siul2_interrupt_config_t intConfig);

/*!
 * @brief Clears the individual pin external interrupt status flag.
 *
 * This function clears the individual pin external interrupt status flag.
 *
 * @param[in] eirqPinIdx IRQ pin
 */
void PINS_DRV_ClearPinExIntFlag(uint32_t eirqPinIdx);

/*!
 * @brief Gets the individual pin external interrupt status flag.
 *
 * This function gets the individual pin external interrupt status flag.
 *
 * @param[in] eirqPinIdx IRQ pin
 * @return Pin external status flag
 */
bool PINS_DRV_GetPinExIntFlag(uint32_t eirqPinIdx);

/*!
 * @brief Clears the entire external interrupt status flag.
 *
 * This function clears the entire external interrupt status flag.
 */
void PINS_DRV_ClearExIntFlag(void);

/*!
 * @brief Reads the entire external interrupt status flag
 *
 * This function reads the entire external interrupt status flag.
 *
 * @return All 32 IRQ pins
 */
uint32_t PINS_DRV_GetExIntFlag(void);

#endif /* FEATURE_PINS_DRIVER_USING_PORT */

/*!
 * @brief Write a pin of a port with a given value
 *
 * This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pin Pin number to be written
 * @param[in] value Pin value to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_WritePin(GPIO_Type * const base,
                       pins_channel_type_t pin,
                       pins_level_type_t value);

/*!
 * @brief Write all pins of a port
 *
 * This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pins Pin mask to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_WritePins(GPIO_Type * const base,
                        pins_channel_type_t pins);

/*!
 * @brief Get the current output from a port
 *
 * This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO outputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
pins_channel_type_t PINS_DRV_GetPinsOutput(const GPIO_Type * const base);

/*!
 * @brief Write pins with 'Set' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pins Pin mask of bits to be set. Each bit represents one pin (LSB is
 * pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_SetPins(GPIO_Type * const base,
                      pins_channel_type_t pins);

/*!
 * @brief Write pins to 'Clear' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pins Pin mask of bits to be cleared. Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is cleared(set to LOW)
 */
void PINS_DRV_ClearPins(GPIO_Type * const base,
                        pins_channel_type_t pins);

/*!
 * @brief Toggle pins value
 *
 * This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pins Pin mask of bits to be toggled.  Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is toggled
 */
void PINS_DRV_TogglePins(GPIO_Type * const base,
                         pins_channel_type_t pins);

/*!
 * @brief Read input pins
 *
 * This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO inputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is read as LOW
 *        - 1: corresponding pin is read as HIGH
 */
pins_channel_type_t PINS_DRV_ReadPins(const GPIO_Type * const base);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* PINS_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
