/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_OS_ABSTRACTION_BM_H__)
#define __FSL_OS_ABSTRACTION_BM_H__

#include "sw_timer.h"

/*!
 * @addtogroup os_abstraction_bm
 * @{
 */

/*******************************************************************************
 * Declarations
 ******************************************************************************/

/*! @brief Type for an synchronization object */
typedef struct
{
    volatile bool    isWaiting; /*!< Is any task waiting for a timeout on this object */
    volatile uint8_t semCount;  /*!< The count value of the object                    */
    uint8_t timerId;            /*!< The software timer channel this object bind to   */
}sync_object_t;

/*! @brief Type for a resource locking object */
typedef struct
{
    volatile bool    isWaiting;  /*!< Is any task waiting for a timeout on this lock  */
    volatile bool    isLocked;   /*!< Is the object locked or not                     */
    uint8_t timerId;             /*!< The software timer channel this lock bind to    */
}lock_object_t;

/*! @brief Type for an event flags group, bit 32 is reserved */
typedef uint32_t event_group_t;

/*! @brief Type for an event group object */
typedef struct
{
    volatile bool             isWaiting;   /*!< Is any task waiting for a timeout on this event  */
    uint8_t                   timerId;     /*!< The software timer channel this event bind to    */
    volatile event_group_t    flags;       /*!< The flags status                                 */
    event_clear_type          clearType;   /*!< Auto clear or manual clear                       */
}event_object_t;

/*! @brief Type for a task pointer */
typedef void (* task_t)(void* param);

/*! @brief Type for a task handler, returned by the task_create function */
typedef task_t task_handler_t;

/*! @brief Type for a task stack */
typedef uint32_t task_stack_t;

/*! @brief Type for a message queue declaration and creation */
typedef struct
{
#if (__FSL_RTOS_MSGQ_COPY_MSG__)
    uint32_t              *queueMem;      /*!< Points to the queue memory */
#else
    void                 **queueMem;      /*!< Points to the queue memory */
#endif
    uint16_t               number;        /*!< Stores the elements in the queue         */
    uint16_t               size;          /*!< Stores the size in words of each element */
    uint16_t               head;          /*!< Index of the next element to be read     */
    uint16_t               tail;          /*!< Index of the next place to write to      */
    sync_object_t          queueSync;     /*!< Sync object wakeup tasks waiting for msg */
    volatile bool          isEmpty;       /*!< Whether queue is empty */
}msg_queue_t;

/*! @brief Type for a message queue declaration and creation */
typedef msg_queue_t*  msg_queue_handler_t;

/*! @brief Type for a message queue item */
typedef void*         msg_queue_item_t;

/*! @brief Constant to pass as timeout value in order to wait indefinitely. */
#define kSyncWaitForever  kSwTimerMaxTimeout

/*! @brief Macro passed to the task_destroy function to destroy the current task */
#define FSL_RTOS_CURRENT_TASK   ((task_handler_t)0)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Synchronization
 * @{
 */

/*!
 * @brief Create the synchronization object. To be used instead of a standard
 *      declaration.
 *
 * @param obj The sync object to create.
 */
#define sync_object_declare(obj)    sync_object_t obj

/* @} */

/*!
 * @name Resource locking
 * @{
 */

/*!
 * @brief Create the locking object. To be used instead of a standard declaration.
 *
 * @param obj The lock object to create.
 */
#define lock_object_declare(obj)    lock_object_t obj

/* @} */

/*!
 * @name Thread management
 * @{
 */

/*!
 * @brief Define a task
 *
 * This macro is used to define resources for a task statically, then task_create will
 * create task based-on these resources.
 *
 * @param task The task function.
 * @param stackSize Number of elements in the stack for this task.
 * @param name String to assign to the task.
 * @param usesFloat Boolean that indicates whether the task uses the floating point unit.
 */
#define FSL_RTOS_TASK_DEFINE(task, stackSize, name, usesFloat)    \
    uint8_t fslTaskName_##task[] = name

/*!
 * @brief Creates and sets the task to active
 *
 * This macro is used with FSL_RTOS_TASK_DEFINE to create a task.
 * Here is an example demonstrating how to use:
   @code
   FSL_RTOS_TASK_DEFINE(task_func, stackSize, taskName, FALSE);

   void main(void)
   {
       task_handler_t handler;
       task_create(task_func, priority, param, &handler);
   }
   @endcode
 *
 * @param task The task function.
 * @param priority Initial priority of the task.
 * @param param Parameter to be passed to the task when it is created.
 * @param handler Returns the identifier to be used afterwards to destroy the task.
 * 
 * @retval kSuccess The task was successfully created.
 * @retval kError The task creation failed.
 */
#define task_create(task, priority, param, handler)                 \
    __task_create(task,                                             \
                  fslTaskName_##task,                               \
                  0,                                                \
                  NULL,                                             \
                  priority,                                         \
                  param,                                            \
                  false,                                            \
                  handler)

/* @} */

/*!
 * @name Message queues
 * @{
 */

/*!
 * @brief This macro statically reserves the memory required for the queue.
 *
 * @param name Identifier for the memory region.
 * @param number Number of elements in the queue. 
 * @param size Size of every element in words.
 */
#if (__FSL_RTOS_MSGQ_COPY_MSG__)
#define MSG_QUEUE_DECLARE(name, number, size) uint32_t queueMem##name[number * size]; \
                                              msg_queue_t name = {                    \
                                                  .queueMem = queueMem##name          \
                                              }
#else
#define MSG_QUEUE_DECLARE(name, number, size) void * queueMem##name[number];          \
                                              msg_queue_t name = {                    \
                                                  .queueMem = queueMem##name          \
                                              }
#endif

/* @} */

/*!
 * @name Critical Sections
 * @{
 */

/*! @brief Ensures the following code will not be preempted */
#define rtos_enter_critical    interrupt_disable_global

/*! @brief Allows preemption */
#define rtos_exit_critical     interrupt_enable_global

/* @} */

/*!
 * @name Task poll
 * @{
 */
/*! @brief Maximum number of functions called every time Poll function is invoked */
#define POLL_MAX_NUM  5

/*! @brief Poll function slot */
typedef struct {
	task_t p_func;  /*!< Task's entry */
	void*  param;   /*!< Task's parameter */
} POLL_SLOT_STRUCT;

/*! @brief Poll structure */
typedef struct {
	POLL_SLOT_STRUCT   p_slot[POLL_MAX_NUM]; /*!< polling function pointer array */
    uint32_t           registered_no;        /*!< number of registered function */
} POLL_STRUCT;

/*!
 * @brief Poll every function registered in the POLL_STRUCT.
 *
 * Every task function registered in the POLL_STRUCT will be called in turn.
 * This function should be used in a infinite loop in main.
 *
 * Here is an example demonstrating how to use:
   @code
   int main(void)
   {
       // System initialize functions.
       POLL_init();
       
       for(;;)
       {
           Poll();
       }
       return 0;
   }
   @endcode
 *
 */
void Poll(void);

/*!
 * @brief Initialize the POLL_STRUCT.
 *
 * The struct POLL_STRUCT must be initialized before task functions are
 * registered.
 */
void POLL_init(void);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_OS_ABSTRACTION_BM_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

