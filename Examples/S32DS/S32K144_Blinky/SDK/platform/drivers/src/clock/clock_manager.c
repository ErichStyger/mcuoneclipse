/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2107 NXP
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

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 1.3, There shall be no occurrence of
 * undefined or critical unspecified behaviour.
 * The addresses of the stack variables are only used at local scope.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * Function is defined for usage by application code.
 *
 */

#include <stddef.h>
#include "device_registers.h"
#include "clock_manager.h"
#include "interrupt_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static clock_manager_state_t g_clockState;


/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_Init
 * Description   : Install pre-defined clock configurations.
 * This function installs the pre-defined clock configuration table to the
 * clock manager.
 *
 * Implements CLOCK_SYS_Init_Activity
 *END**************************************************************************/
status_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                              uint8_t configsNumber,
                              clock_manager_callback_user_config_t **callbacksPtr,
                              uint8_t callbacksNumber)
{
    DEV_ASSERT(clockConfigsPtr != NULL);
    DEV_ASSERT(callbacksPtr != NULL);

    g_clockState.configTable     = clockConfigsPtr;
    g_clockState.clockConfigNum  = configsNumber;
    g_clockState.callbackConfig  = callbacksPtr;
    g_clockState.callbackNum     = callbacksNumber;

    /*
     * errorCallbackIndex is the index of the callback which returns error
     * during clock mode switch. If all callbacks return success, then the
     * errorCallbackIndex is callbacksNumber.
     */
    g_clockState.errorCallbackIndex = callbacksNumber;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_UpdateConfiguration
 * Description   : Send notification and change system clock configuration.
 * This function sends the notification to all callback functions, if all
 * callbacks return OK or forceful policy is used, this function will change
 * system clock configuration.
 *
 * Implements CLOCK_SYS_UpdateConfiguration_Activity
 *END**************************************************************************/
status_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                                   clock_manager_policy_t policy)
{
    uint8_t callbackIdx;
    bool successfulSetConfig;           /* SetConfiguraiton status */
    status_t ret = STATUS_SUCCESS;
    const clock_manager_callback_user_config_t * callbackConfig;
    clock_notify_struct_t notifyStruct;

    DEV_ASSERT(targetConfigIndex < g_clockState.clockConfigNum);       /* Clock configuration index is out of range. */

    notifyStruct.targetClockConfigIndex = targetConfigIndex;
    notifyStruct.policy                 = policy;

    /* Disable interrupts */
    INT_SYS_DisableIRQGlobal();
    /* Set errorcallbackindex as callbackNum, which means no callback error now.*/
    g_clockState.errorCallbackIndex = g_clockState.callbackNum;

    /* First step: Send "BEFORE" notification. */
    notifyStruct.notifyType = CLOCK_MANAGER_NOTIFY_BEFORE;

    /* Send notification to all callback. */
    for (callbackIdx=0; callbackIdx<g_clockState.callbackNum; callbackIdx++)
    {
        callbackConfig = g_clockState.callbackConfig[callbackIdx];
        if ((callbackConfig) &&
            (callbackConfig->callbackType != CLOCK_MANAGER_CALLBACK_AFTER))
        {
            if (STATUS_SUCCESS !=
                    (*callbackConfig->callback)(&notifyStruct,
                        callbackConfig->callbackData))
            {
                g_clockState.errorCallbackIndex = callbackIdx;
                /* Save the error callback index. */
                ret = STATUS_MCU_NOTIFY_BEFORE_ERROR;

                if (CLOCK_MANAGER_POLICY_AGREEMENT == policy)
                {
                    break;
                }
            }
        }
    }

    /* If all callback success or forceful policy is used. */
    if ((STATUS_SUCCESS == ret) ||
        (policy == CLOCK_MANAGER_POLICY_FORCIBLE))
    {
        /* clock mode switch. */
        ret = CLOCK_SYS_SetConfiguration(g_clockState.configTable[targetConfigIndex]);
        successfulSetConfig = (STATUS_SUCCESS == ret);

        g_clockState.curConfigIndex = targetConfigIndex;
    }
    else
    {
        /* Unsuccessful setConfiguration */
        successfulSetConfig = false;
    }

    if(successfulSetConfig){
        notifyStruct.notifyType = CLOCK_MANAGER_NOTIFY_AFTER;

        for (callbackIdx=0; callbackIdx<g_clockState.callbackNum; callbackIdx++)
        {
            callbackConfig = g_clockState.callbackConfig[callbackIdx];
            if ((callbackConfig) &&
                (callbackConfig->callbackType != CLOCK_MANAGER_CALLBACK_BEFORE))
            {
                if (STATUS_SUCCESS !=
                        (*callbackConfig->callback)(&notifyStruct,
                            callbackConfig->callbackData))
                {
                    g_clockState.errorCallbackIndex = callbackIdx;
                    /* Save the error callback index. */
                    ret = STATUS_MCU_NOTIFY_AFTER_ERROR;

                    if (CLOCK_MANAGER_POLICY_AGREEMENT == policy)
                    {
                        break;
                    }
                }
            }
        }
    }
    else /* Error occurs, need to send "RECOVER" notification. */
    {
        notifyStruct.notifyType = CLOCK_MANAGER_NOTIFY_RECOVER;
        for(;;)
        {
            callbackConfig = g_clockState.callbackConfig[callbackIdx];
            if (callbackConfig != NULL)
            {
                (void)(*callbackConfig->callback)(&notifyStruct,
                        callbackConfig->callbackData);
            }
            if(callbackIdx == 0U)
            {
                break;
            }
            callbackIdx--;
        }
    }

    /* Enable interrupts */
    INT_SYS_EnableIRQGlobal();

    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCurrentConfiguration
 * Description   : Get current clock configuration index.
 *
 * Implements CLOCK_SYS_GetCurrentConfiguration_Activity
 *END**************************************************************************/
uint8_t CLOCK_SYS_GetCurrentConfiguration(void)
{
    return g_clockState.curConfigIndex;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetErrorCallback
 * Description   : Get the callback which returns error in last clock switch.
 *
 * Implements CLOCK_SYS_GetErrorCallback_Activity
 *END**************************************************************************/
clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void)
{
    clock_manager_callback_user_config_t *retValue;

    /* If all callbacks return success. */
    if (g_clockState.errorCallbackIndex >= g_clockState.clockConfigNum)
    {
        retValue = NULL;
    }
    else
    {
        retValue = g_clockState.callbackConfig[g_clockState.errorCallbackIndex];
    }
    return retValue;
}


/*******************************************************************************
 * EOF
 ******************************************************************************/

