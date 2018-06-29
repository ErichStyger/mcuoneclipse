/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#if !defined(CLOCK_MANAGER_H)
#define CLOCK_MANAGER_H

#include "device_registers.h"
#include "status.h"

/*
 * Include the cpu specific clock API header files.
 */
#if (defined(S32K14x_SERIES))
    /* S32K144 Clock System Level API header file */
    #include "../src/clock/S32K1xx/clock_S32K1xx.h"
#elif (defined(S32V234_SERIES))
    /* S32V234 Clock System Level API header file */
    #include "../src/clock/S32V234/clock_S32V234.h"
#elif (defined(MPC574x_SERIES))
    /* MPC5748G Clock System Level API header file */
    #include "../src/clock/MPC57xx/clock_MPC57xx.h"
#elif (defined(S32S247_SERIES))
    /* S32S247 Clock System Level API header file */
    #include "../src/clock/S32Sxx/clock_S32Sxx.h"
#elif (defined(SJA1110_SERIES))
    /* SJA1110 Clock System Level API header file */
    #include "../src/clock/S32Sxx/clock_S32Sxx.h"
#else
    #error "No valid CPU defined!"
#endif


/*!
 * @file clock_manager.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, Global typedef not referenced.
 * Although all symbols from clock_manager.h are referenced in clock_manager.c,
 * these symbols are not referenced in other drivers;
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * This is required to implement enumeration entries as macro.
 * Enumeration entries (macros) are referenced from application code.
 */

/*! @addtogroup clock_manager*/
/*! @{*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief The clock notification type.
 * Implements clock_manager_notify_t_Class
 */
typedef enum
{
    CLOCK_MANAGER_NOTIFY_RECOVER = 0x00U,  /*!< Notify IP to recover to previous work state.      */
    CLOCK_MANAGER_NOTIFY_BEFORE  = 0x01U,  /*!< Notify IP that system will change clock setting.  */
    CLOCK_MANAGER_NOTIFY_AFTER   = 0x02U,  /*!< Notify IP that have changed to new clock setting. */
} clock_manager_notify_t;

/*!
 * @brief The callback type, indicates what kinds of notification this callback handles.
 * Implements clock_manager_callback_type_t_Class
 */
typedef enum
{
    CLOCK_MANAGER_CALLBACK_BEFORE       = 0x01U, /*!< Callback handles BEFORE notification.          */
    CLOCK_MANAGER_CALLBACK_AFTER        = 0x02U, /*!< Callback handles AFTER notification.           */
    CLOCK_MANAGER_CALLBACK_BEFORE_AFTER = 0x03U  /*!< Callback handles BEFORE and AFTER notification */
} clock_manager_callback_type_t;

/*!
 * @brief Clock transition policy.
 * Implements clock_manager_policy_t_Class
 */
typedef enum
{
    CLOCK_MANAGER_POLICY_AGREEMENT,  /*!< Clock transfers gracefully. */
    CLOCK_MANAGER_POLICY_FORCIBLE    /*!< Clock transfers forcefully. */
} clock_manager_policy_t;

/*!
 * @brief Clock notification structure passed to clock callback function.
 * Implements clock_notify_struct_t_Class
 */
typedef struct
{
    uint8_t targetClockConfigIndex;    /*!< Target clock configuration index. */
    clock_manager_policy_t policy;     /*!< Clock transition policy.          */
    clock_manager_notify_t notifyType; /*!< Clock notification type.          */
} clock_notify_struct_t;

/*!
 * @brief Type of clock callback functions.
 */
typedef status_t (*clock_manager_callback_t)(clock_notify_struct_t *notify,
                                             void* callbackData);

/*!
 * @brief Structure for callback function and its parameter.
 * Implements clock_manager_callback_user_config_t_Class
 */
typedef struct
{
    clock_manager_callback_t      callback;      /*!< Entry of callback function.     */
    clock_manager_callback_type_t callbackType;  /*!< Callback type.                  */
    void* callbackData;                          /*!< Parameter of callback function. */
} clock_manager_callback_user_config_t;

/*!
 * @brief Clock manager state structure.
 * Implements clock_manager_state_t_Class
 */
typedef struct
{
    clock_manager_user_config_t const **configTable;/*!< Pointer to clock configure table.*/
    uint8_t clockConfigNum;                         /*!< Number of clock configurations.  */
    uint8_t curConfigIndex;                         /*!< Index of current configuration.  */
    clock_manager_callback_user_config_t **callbackConfig; /*!< Pointer to callback table.*/
    uint8_t callbackNum;                            /*!< Number of clock callbacks.       */
    uint8_t errorCallbackIndex;                     /*!< Index of callback returns error. */
} clock_manager_state_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @name Dynamic clock setting
 * @{
 */

/*!
 * @brief Install pre-defined clock configurations.
 *
 * This function installs the pre-defined clock configuration table to
 * clock manager.
 *
 * @param[in] clockConfigsPtr Pointer to the clock configuration table.
 * @param[in] configsNumber Number of clock configurations in table.
 * @param[in] callbacksPtr Pointer to the callback configuration table.
 * @param[in] callbacksNumber Number of callback configurations in table.
 *
 * @return Error code.
 */
status_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                        uint8_t configsNumber,
                        clock_manager_callback_user_config_t **callbacksPtr,
                        uint8_t callbacksNumber);

/*!
 * @brief Set system clock configuration according to pre-defined structure.
 *
 * This function sets system to target clock configuration; before transition,
 * clock manager will send notifications to all drivers registered to the
 * callback table.  When graceful policy is used, if some drivers are not ready
 * to change, clock transition will not occur, all drivers still work in
 * previous configuration and error is returned. When forceful policy is used,
 * all drivers should stop work and system changes to new clock configuration.
 *
 * @param[in] targetConfigIndex Index of the clock configuration.
 * @param[in] policy Transaction policy, graceful or forceful.
 *
 * @return Error code.
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup
 * EREFS/HGO correctly and make sure OSCINIT is set.
 */
status_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                       clock_manager_policy_t policy);

/*!
 * @brief Set system clock configuration.
 *
 * This function sets the system to target configuration, it only sets the
 * clock modules registers for clock mode change, but not send notifications
 * to drivers. This function is different by different SoCs.
 *
 * @param[in] config Target configuration.
 *
 * @return Error code.
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup
 * EREFS/HGO correctly and make sure OSCINIT is set.
 */
status_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const * config);

/*!
 * @brief Get current system clock configuration.
 *
 * @return Current clock configuration index.
 */
uint8_t CLOCK_SYS_GetCurrentConfiguration(void);

/*!
 * @brief Get the callback which returns error in last clock switch.
 *
 * When graceful policy is used, if some IP is not ready to change clock
 * setting, the callback will return error and system stay in current
 * configuration. Applications can use this function to check which
 * IP callback returns error.
 *
 * @return Pointer to the callback which returns error.
 */
clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void);


/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_names_t.
 * The SCG must be properly configured before using this function. See the
 * reference manual for supported clock names for different chip families.
 * The returned value is in Hertz. If it cannot find the clock name
 * or the name is not supported for a specific chip family, it returns an
 * STATUS_UNSUPPORTED. If frequency is required for a peripheral and the
 * module is not clocked, then STATUS_MCU_GATED_OFF status is returned.
 * Frequency is returned if a valid address is provided. If frequency is
 * required for a peripheral that doesn't support functional clock, the zero
 * value is provided.
 *
 * @param[in] clockName Clock names defined in clock_names_t
 * @param[out] frequency Returned clock frequency value in Hertz
 * @return status   Error code defined in status_t
 */
status_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                           uint32_t *frequency);

/* @} */


#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_MANAGER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/

