/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if !defined(__FSL_RTOS_ABSTRACTION_H__)
#define __FSL_RTOS_ABSTRACTION_H__

#include <stdint.h>
#include <stdbool.h>

//! @addtogroup rtos_irq_sync
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////
typedef enum _osa_status_t
{
    kStatus_OSA_Success = 0U, /*!< Success */
    kStatus_OSA_Error = 1U,   /*!< Failed */
    kStatus_OSA_Timeout = 2U, /*!< Timeout occurs while waiting */
    kStatus_OSA_Idle = 3U     /*!< Used for bare metal only, the wait object is not ready
                                and timeout still not occur */
} osa_status_t;

typedef struct Semaphore
{
    volatile bool isWaiting;   /*!< Is any task waiting for a timeout on this object */
    volatile uint8_t semCount; /*!< The count value of the object                    */
    uint64_t tickStart;        /*!< The ticks to start timeout                       */
    uint32_t timeout;          /*!< Timeout to wait in milliseconds                  */
} semaphore_t;

//! @brief Type for an interrupt synchronization object.
typedef volatile int32_t sync_object_t;

//! @brief Type for an interrupt lock object.
typedef volatile uint32_t lock_object_t;

enum sync_timeouts
{
    //! @brief Constant to pass for the sync_wait() timeout in order to wait indefinitely.
    kSyncWaitForever = 0xffffffffU
};

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name Interrupt handler synchronization
//@{

/*!
 * @name Counting Semaphore
 * @{
 */

/*!
 * @brief Creates a semaphore with a given value.
 *
 * This function creates a semaphore and sets the value to the parameter
 * initValue.
 *
 * @param pSem      Pointer to the semaphore.
 * @param initValue Initial value the semaphore will be set to.
 *
 * @retval kStatus_OSA_Success The semaphore is created successfully.
 * @retval kStatus_OSA_Error   The semaphore can not be created.
 *
 * Example:
   @code
   semaphore_t mySem;
   OSA_SemaCreate(&mySem, 0);
   @endcode
 *
 */
osa_status_t OSA_SemaCreate(semaphore_t *pSem, uint8_t initValue);

/*!
 * @brief Pending a semaphore with timeout.
 *
 * This function checks the semaphore's counting value. If it is positive,
 * decreases it and returns kStatus_OSA_Success. Otherwise, a timeout is used
 * to wait.
 *
 * @param pSem    Pointer to the semaphore.
 * @param timeout The maximum number of milliseconds to wait if semaphore is not
 *                positive. Pass OSA_WAIT_FOREVER to wait indefinitely, pass 0
 *                will return kStatus_OSA_Timeout immediately.
 *
 * @retval kStatus_OSA_Success The semaphore is received.
 * @retval kStatus_OSA_Timeout The semaphore is not received within the specified 'timeout'.
 * @retval kStatus_OSA_Error   An incorrect parameter was passed.
 * @retval kStatus_OSA_Idle    The semaphore is not available and 'timeout' is not exhausted,
 *                             This is only for bare metal.
 *
 * @note With bare metal, a semaphore can not be waited by more than one task
 * at the same time.
 *
 * Example:
 * @code
   osa_status_t status;
   status = OSA_SemaWait(&mySem, 100);
   switch(status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_SemaWait(semaphore_t *pSem, uint32_t timeout);

/*!
 * @brief Signals for someone waiting on the semaphore to wake up.
 *
 * Wakes up one task that is waiting on the semaphore. If no task is waiting, increases
 * the semaphore's counting value.
 *
 * @param pSem Pointer to the semaphore to signal.
 *
 * @retval kStatus_OSA_Success The semaphore is successfully signaled.
 * @retval kStatus_OSA_Error   The object can not be signaled or invalid parameter.
 *
 * Example:
 * @code
   osa_status_t status;
   status = OSA_SemaPost(&mySem);
   switch(status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_SemaPost(semaphore_t *pSem);

/*!
 * @brief Destroys a previously created semaphore.
 *
 * @param pSem Pointer to the semaphore to destroy.
 *
 * @retval kStatus_OSA_Success The semaphore is successfully destroyed.
 * @retval kStatus_OSA_Error   The semaphore can not be destroyed.
 *
 * Example:
 * @code
   osa_status_t status;
   status = OSA_SemaDestroy(&mySem);
   switch(status)
   {
       //...
   }
   @endcode
 *
 */
osa_status_t OSA_SemaDestroy(semaphore_t *pSem);

/*!
 * @brief Delays execution for a number of milliseconds.
 *
 * @param delay The time in milliseconds to wait.
 */
void OSA_TimeDelay(uint32_t delay);

//@}

//! @}

//! @name Interrupt handler synchronization
//@{

/*!
 * @brief Initialize a synchronization object to a given state.
 *
 * @param obj The sync object to initialize.
 * @param state The initial state of the object. Pass true to make the sync object start
 *      out locked, or false to make it unlocked.
 */
void sync_init(sync_object_t *obj, bool state);

/*!
 * @brief Wait for a synchronization object to be signalled.
 *
 * @param obj The synchronization object.
 * @param timeout The maximum number of milliseconds to wait for the object to be signalled.
 *      Pass the #kSyncWaitForever constant to wait indefinitely for someone to signal the object.
 *      If 0 is passed for this timeout, then the function will return immediately if the object
 *      is locked.
 *
 * @retval true The object was signalled.
 * @retval false A timeout occurred.
 */
bool sync_wait(sync_object_t *obj, uint32_t timeout);

/*!
 * @brief Signal for someone waiting on the syncronization object to wake up.
 *
 * @param obj The synchronization object to signal.
 */
void sync_signal(sync_object_t *obj);

/*!
 * @brief Reset the synchronization object
 *
 * @param obj The synchronization object to signal.
 */
void sync_reset(sync_object_t *obj);

//@}

//! @addtogroup irq_lock
//! @{

//! @name Interrupt handler lock
//@{

//! @brief Initialize the lock object
void lock_init(void);

//! @brief Disable global irq and store previous state.
void lock_acquire(void);

//! @brief Restore previous state.
void lock_release(void);

//@}

//! @}

#if defined(__cplusplus)
}
#endif

#endif // __FSL_RTOS_ABSTRACTION_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
