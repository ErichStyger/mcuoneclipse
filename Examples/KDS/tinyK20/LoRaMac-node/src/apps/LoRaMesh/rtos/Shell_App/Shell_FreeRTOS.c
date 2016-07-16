/**
 * \file Shell_FreeRTOS.c
 * \author tawinige
 * \date 09.02.2016
 * \version 1.0
 *
 * \brief
 *
 *******************************************************************************
 *  Change log:
 *      [1.0]   09.02.2016      	tawinige
 *          - created
 *******************************************************************************
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "Shell_FreeRTOS.h"
#include "task.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
/*! \brief Print task list */
static uint8_t PrintTaskList( Shell_ConstStdIO_t *io );

/*! \brief Print status */
static uint8_t PrintStatus( Shell_ConstStdIO_t *io );

/*! \brief Print help */
static uint8_t PrintHelp( Shell_ConstStdIO_t *io );

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
uint8_t FreeRTOS_ParseCommand( const unsigned char *cmd, bool *handled, Shell_ConstStdIO_t *io )
{
    if ( strcmp((char*) cmd, SHELL_CMD_HELP) == 0 || strcmp((char*) cmd, "rtos help") == 0 ) {
        *handled = TRUE;
        return PrintHelp(io);
    } else if ( (strcmp((char*) cmd, SHELL_CMD_STATUS) == 0)
            || (strcmp((char*) cmd, "rtos status") == 0) ) {
        *handled = TRUE;
        return PrintStatus(io);
#if configFRTOS_MEMORY_SCHEME != 1 /* this scheme does not allow deallocation of memory */
    } else if ( strcmp((char*) cmd, "rtos tasklist") == 0 ) {
        *handled = TRUE;
        return PrintTaskList(io);
#endif
    }
    return ERR_OK;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
#if configFRTOS_MEMORY_SCHEME!=1 /* this scheme does not allow deallocation of memory */
static uint8_t PrintTaskList( Shell_ConstStdIO_t *io )
{
    UBaseType_t nofTasks, nof, i;
    TaskStatus_t *pxTaskStatusArray;
    uint8_t buf[32], tmpBuf[16], res;

    res = ERR_OK;
    nofTasks = uxTaskGetNumberOfTasks();
    pxTaskStatusArray = pvPortMalloc(nofTasks * sizeof(TaskStatus_t));
    if ( pxTaskStatusArray != NULL ) {
        nof = uxTaskGetSystemState(pxTaskStatusArray, nofTasks, NULL);
        if ( nof != nofTasks ) { /* error, array was to small? */
            Shell_SendStr((unsigned char*) "***GetSystemState failed!\r\n", io->stdErr);
            res = ERR_FAILED; /* out of memory */
        } else {
#define PAD_STAT_TASK_TCB         5
#define PAD_STAT_TASK_HANDLE      11
#define PAD_STAT_TASK_NAME        (configMAX_TASK_NAME_LEN+1)
#define PAD_STAT_TASK_STATE       10
#define PAD_STAT_TASK_PRIO        8
#define PAD_STAT_TASK_RUNTIME     11
#define PAD_STAT_TASK_STACK_MARK  11
            /* header */
            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "TCB#", ' ',
            PAD_STAT_TASK_TCB);
            Shell_SendStr(buf, io->stdOut);

            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "Handle", ' ',
            PAD_STAT_TASK_HANDLE);
            Shell_SendStr(buf, io->stdOut);

            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "Name", ' ',
            PAD_STAT_TASK_NAME);
            Shell_SendStr(buf, io->stdOut);

            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "State", ' ',
            PAD_STAT_TASK_STATE);
            Shell_SendStr(buf, io->stdOut);

            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "Prio", ' ',
            PAD_STAT_TASK_PRIO);
            Shell_SendStr(buf, io->stdOut);

            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "Runtime", ' ',
            PAD_STAT_TASK_RUNTIME);
            Shell_SendStr(buf, io->stdOut);

            buf[0] = '\0';
            strcatPad(buf, sizeof(buf), (const unsigned char*) "Stack", ' ',
            PAD_STAT_TASK_STACK_MARK);
            Shell_SendStr(buf, io->stdOut);

            Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
            for ( i = 0; i < nof; i++ ) {
                /* TCB */
                tmpBuf[0] = '\0';
                strcatNum32u(tmpBuf, sizeof(tmpBuf), (uint32_t) pxTaskStatusArray[i].xTaskNumber);
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), tmpBuf, ' ', PAD_STAT_TASK_TCB);
                Shell_SendStr(buf, io->stdOut);
                /* task handle */
                tmpBuf[0] = '\0';
                custom_strcat(tmpBuf, sizeof(tmpBuf), (unsigned char*) "0x");
                strcatNum32Hex(tmpBuf, sizeof(tmpBuf), (uint32_t) pxTaskStatusArray[i].xHandle);
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), tmpBuf, ' ', PAD_STAT_TASK_HANDLE);
                Shell_SendStr(buf, io->stdOut);

                /* task name */
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), (const unsigned char*) pxTaskStatusArray[i].pcTaskName,
                        ' ', PAD_STAT_TASK_NAME);
                Shell_SendStr(buf, io->stdOut);

                /* state */
                switch ( pxTaskStatusArray[i].eCurrentState ) {
                    case eRunning:
                        custom_strcpy(tmpBuf, sizeof(tmpBuf), (unsigned char*) "Running");
                        break;
                    case eReady:
                        custom_strcpy(tmpBuf, sizeof(tmpBuf), (unsigned char*) "Ready");
                        break;
                    case eSuspended:
                        custom_strcpy(tmpBuf, sizeof(tmpBuf), (unsigned char*) "Suspended");
                        break;
                    case eBlocked:
                        custom_strcpy(tmpBuf, sizeof(tmpBuf), (unsigned char*) "Blocked");
                        break;
                    default:
                        custom_strcpy(tmpBuf, sizeof(tmpBuf), (unsigned char*) "UNKNOWN!");
                        break;
                }
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), tmpBuf, ' ', PAD_STAT_TASK_STATE);
                Shell_SendStr(buf, io->stdOut);

                /* (baseprio,currprio) */
                tmpBuf[0] = '\0';
                chcat(tmpBuf, sizeof(tmpBuf), '(');
                strcatNum32s(tmpBuf, sizeof(tmpBuf), pxTaskStatusArray[i].uxBasePriority);
                chcat(tmpBuf, sizeof(tmpBuf), ',');
                strcatNum32s(tmpBuf, sizeof(tmpBuf), pxTaskStatusArray[i].uxCurrentPriority);
                chcat(tmpBuf, sizeof(tmpBuf), ')');
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), tmpBuf, ' ', PAD_STAT_TASK_PRIO);
                Shell_SendStr(buf, io->stdOut);

                /* runtime */
                tmpBuf[0] = '\0';
                custom_strcat(tmpBuf, sizeof(tmpBuf), (unsigned char*) "0x");
                strcatNum32Hex(tmpBuf, sizeof(tmpBuf), pxTaskStatusArray[i].ulRunTimeCounter);
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), tmpBuf, ' ', PAD_STAT_TASK_RUNTIME);
                Shell_SendStr(buf, io->stdOut);

                /* stack high water mark */
                tmpBuf[0] = '\0';
                strcatNum16u(tmpBuf, sizeof(tmpBuf), pxTaskStatusArray[i].usStackHighWaterMark);
                buf[0] = '\0';
                strcatPad(buf, sizeof(buf), tmpBuf, ' ', PAD_STAT_TASK_STACK_MARK);
                Shell_SendStr(buf, io->stdOut);

                Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
            }
        }
    } else {
        Shell_SendStr((unsigned char*) "***alloc failed!\r\n", io->stdErr);
        res = ERR_FAILED; /* out of memory */
    }
    if ( pxTaskStatusArray != NULL ) { /* free memory */
        vPortFree(pxTaskStatusArray);
    }
    return res;
}
#endif /* configFRTOS_MEMORY_SCHEME!=1 */

static uint8_t PrintStatus( Shell_ConstStdIO_t *io )
{
#if configUSE_TRACE_FACILITY || configGENERATE_RUN_TIME_STATS /* FreeRTOS trace feature enabled */
#if configFRTOS_MEMORY_SCHEME==1 /* this scheme does not allow deallocation of memory */
    static unsigned char *taskListBufferP=NULL; /* allocated only once, never deallocated! */
#else
    unsigned char *taskListBufferP;
#endif
    size_t bufSize;
#endif
    uint8_t buf[16];

    Shell_SendStatusStr((unsigned char*) "rtos", (unsigned char*) "\r\n", io->stdOut);
#if 0 && configUSE_TRACE_FACILITY /* FreeRTOS trace feature enabled */
    Shell_SendStr((unsigned char*)"TASK LIST:\r\n", io->stdOut);
    buf[0] = '\0';
    strcatPad(buf, sizeof(buf), (const unsigned char*)"Name", ' ', configMAX_TASK_NAME_LEN);
    Shell_SendStr(buf, io->stdOut);
    Shell_SendStr((unsigned char*)"\tState\tPrio\tStack\tTCB#\r\n", io->stdOut);
    Shell_SendStr((unsigned char*)CLS1_DASH_LINE, io->stdOut);
    Shell_SendStr((unsigned char*)"\r\n", io->stdOut);
    /* task list and status */
    bufSize = 40*uxTaskGetNumberOfTasks(); /* about 40 bytes for a task should be enough */
#if configFRTOS_MEMORY_SCHEME==1 /* this scheme does not allow deallocation of memory */
    if (taskListBufferP==NULL) { /* only if not allocated yet */
        taskListBufferP = FRTOS1_pvPortMalloc(bufSize); /* about 40 bytes for a task should be enough */
    }
#else
    taskListBufferP = FRTOS1_pvPortMalloc(bufSize); /* about 40 bytes for a task should be enough */
#endif
    if (taskListBufferP != NULL) {
        vTaskList((char*)taskListBufferP, bufSize);
        Shell_SendStr(taskListBufferP, io->stdOut);
#if configFRTOS_MEMORY_SCHEME!=1 /* this scheme does not allow deallocation of memory */
        vPortFree(taskListBufferP);
#endif
    } else {
        Shell_SendStr((unsigned char*)"\r\n*** out of heap! ***\r\n", io->stdErr);
    }
#endif
#if ((configGENERATE_RUN_TIME_STATS==1) && (configUSE_STATS_FORMATTING_FUNCTIONS==1))
    Shell_SendStr((unsigned char*)CLS1_DASH_LINE, io->stdOut);
    Shell_SendStr((unsigned char*)"\r\nRTOS RUN-TIME STATISTICS:\r\n", io->stdOut);
    buf[0] = '\0';
    custom_strcatPad(buf, sizeof(buf), (const unsigned char*)"Name", ' ', configMAX_TASK_NAME_LEN);
    Shell_SendStr(buf, io->stdOut);
    Shell_SendStr((unsigned char*)"\tTime\t\t%Time\r\n", io->stdOut);
    Shell_SendStr((unsigned char*)CLS1_DASH_LINE, io->stdOut);
    Shell_SendStr((unsigned char*)"\r\n", io->stdOut);
    /* task list and status */
    bufSize = 40*uxTaskGetNumberOfTasks(); /* about 40 bytes for a task should be enough */
#if configFRTOS_MEMORY_SCHEME==1 /* this scheme does not allow deallocation of memory */
    if (taskListBufferP==NULL) { /* only if not allocated yet */
        taskListBufferP = FRTOS1_pvPortMalloc(bufSize);
    }
#else
    taskListBufferP = FRTOS1_pvPortMalloc(bufSize);
#endif
    if (taskListBufferP != NULL) {
        FRTOS1_vTaskGetRunTimeStats((char*)taskListBufferP, bufSize);
        Shell_SendStr(taskListBufferP, io->stdOut);
#if configFRTOS_MEMORY_SCHEME!=1 /* this scheme does not allow deallocation of memory */
        FRTOS1_vPortFree(taskListBufferP);
#endif
    } else {
        Shell_SendStr((unsigned char*)"\r\n*** out of heap! ***\r\n", io->stdErr);
    }
#endif
    Shell_SendStatusStr((unsigned char*) "  RTOS ticks", (const unsigned char*) "", io->stdOut);
    num16sToStr(buf, sizeof(buf), configTICK_RATE_HZ);
    Shell_SendStr(buf, io->stdOut);
    Shell_SendStr((unsigned char*) " Hz, ", io->stdOut);
    num16sToStr(buf, sizeof(buf), 1000 / configTICK_RATE_HZ);
    Shell_SendStr(buf, io->stdOut);
    Shell_SendStr((unsigned char*) " ms\r\n", io->stdOut);
#if configFRTOS_MEMORY_SCHEME!=3 /* wrapper to malloc() does not have xPortGetFreeHeapSize() */
    Shell_SendStatusStr((unsigned char*) "  Free heap", (const unsigned char*) "", io->stdOut);
    num32uToStr(buf, sizeof(buf), xPortGetFreeHeapSize());
    Shell_SendStr(buf, io->stdOut);
    Shell_SendStr((unsigned char*) " bytes\r\n", io->stdOut);
#endif
    return ERR_OK;
}

static uint8_t PrintHelp( Shell_ConstStdIO_t *io )
{
    Shell_SendHelpStr((unsigned char*) "rtos", (unsigned char*) "Group of rtos commands\r\n",
            io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  help|status",
            (unsigned char*) "Print help or status information\r\n", io->stdOut);
#if configFRTOS_MEMORY_SCHEME!=1 /* this scheme does not allow deallocation of memory */
    Shell_SendHelpStr((unsigned char*) "  tasklist", (unsigned char*) "Print tasklist\r\n",
            io->stdOut);
#endif
    return ERR_OK;
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
