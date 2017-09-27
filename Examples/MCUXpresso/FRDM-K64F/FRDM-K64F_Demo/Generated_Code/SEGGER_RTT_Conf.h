/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co. KG                 *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 2014 - 2016  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* * This software may in its unmodified form be freely redistributed *
*   in source form.                                                  *
* * The source code may be modified, provided the source code        *
*   retains the above copyright notice, this list of conditions and  *
*   the following disclaimer.                                        *
* * Modified versions of this software in source or linkable form    *
*   may not be distributed without prior consent of SEGGER.          *
* * This software may only be used for communication with SEGGER     *
*   J-Link debug probes.                                             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       RTT version: 5.10u                                           *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File    : SEGGER_RTT_Conf.h
Purpose : Implementation of SEGGER real-time transfer (RTT) which 
          allows real-time communication on targets which support 
          debugger memory accesses while the CPU is running.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef SEGGER_RTT_CONF_H
#define SEGGER_RTT_CONF_H

#ifdef __ICCARM__
  #include <intrinsics.h>
#endif

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
/* << EST: Additional setting to check for FreeRTOS: need to use FreeRTOS with proper BASEPRI mask to create critical sections */
#define SEGGER_RTT_FREERTOS_PRESENT   1 /* 1: FreeRTOS enabled in project, 0: bare metal */
#if SEGGER_RTT_FREERTOS_PRESENT
  #include "portmacro.h" /* include FreeRTOS port header file for critical section handling */
#endif

/* Channel 0 settings from properties */ /* << EST */
#define SEGGER_RTT_CHANNEL_0_ENABLED              (1) /* 1: initialize channel; 0: do not initialize channel */
#define SEGGER_RTT_CHANNEL_0_NAME                 "Terminal"
#define SEGGER_RTT_CHANNEL_0_BUFFER_SIZE_UP       (512)
#define SEGGER_RTT_CHANNEL_0_BUFFER_SIZE_DOWN     (64)
#define SEGGER_RTT_CHANNEL_0_MODE_UP              SEGGER_RTT_MODE_NO_BLOCK_SKIP
#define SEGGER_RTT_CHANNEL_0_MODE_DOWN            SEGGER_RTT_MODE_NO_BLOCK_SKIP

#define SEGGER_RTT_MAX_NUM_UP_BUFFERS             (3)     // Max. number of up-buffers (T->H) available on this target    (Default: 2)
#define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS           (3)     // Max. number of down-buffers (H->T) available on this target  (Default: 2)

#define BUFFER_SIZE_UP                            (512)  // Size of the buffer for terminal output of target, up to host (Default: 1k)
#define BUFFER_SIZE_DOWN                          (64)    // Size of the buffer for terminal input to target from host (Usually keyboard input) (Default: 16)

#define SEGGER_RTT_PRINTF_BUFFER_SIZE             (64)    // Size of buffer for RTT printf to bulk-send chars via RTT     (Default: 64)
#define SEGGER_RTT_MODE_DEFAULT                   SEGGER_RTT_MODE_NO_BLOCK_SKIP // Mode for pre-initialized terminal channel (buffer 0)

//
// Target is not allowed to perform other RTT operations while string still has not been stored completely.
// Otherwise we would probably end up with a mixed string in the buffer.
// If using  RTT from within interrupts, multiple tasks or multi processors, define the SEGGER_RTT_LOCK() and SEGGER_RTT_UNLOCK() function here.
//
/*********************************************************************
*
*       RTT lock configuration for SEGGER Embedded Studio, 
*       Rowley CrossStudio and GCC
*/
#if (defined __SES_ARM) || (defined __CROSSWORKS_ARM) || (defined __GNUC__)
  #ifdef __ARM_ARCH_6M__
    #define SEGGER_RTT_LOCK() {                                                 \
                                    /*lint -save -e529 Symbol 'LockState' not subsequently referenced  */ \
                                    unsigned int LockState;                     \
                                  __asm volatile ("mrs   %0, primask  \n\t"     \
                                                  "mov   r1, $1     \n\t"       \
                                                  "msr   primask, r1  \n\t"     \
                                                  : "=r" (LockState)            \
                                                  :                             \
                                                  : "r1"                        \
                                                  );                            
    
    #define SEGGER_RTT_UNLOCK()   __asm volatile ("msr   primask, %0  \n\t"     \
                                                  :                             \
                                                  : "r" (LockState)             \
                                                  :                             \
                                                  );                            \
                                     /*lint -restore */                          \
                                 }                                             
                                  
  #elif (defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__))
    /* >> EST */
    #if SEGGER_RTT_FREERTOS_PRESENT
       #define SEGGER_RTT_BLOCKED_INTERRUPT_PRIORITY  configMAX_SYSCALL_INTERRUPT_PRIORITY /* Interrupts at this level and below will be blocked (valid values 1-15) */
    #else
      #define SEGGER_RTT_LOCK_INTERRUPT_LEVEL         3 /* Interrupts at this level and below will be blocked (valid values 1-15 for Kinetis) */
      #define SEGGER_RTT_PRIO_BITS                    4 /* NXP Kinetis M4(F) has 4 interrupt priority bits */
      #define SEGGER_RTT_BLOCKED_INTERRUPT_PRIORITY   (SEGGER_RTT_LOCK_INTERRUPT_LEVEL<<(8-SEGGER_RTT_PRIO_BITS))
    #endif
    /* >> EST */
    #define SEGGER_RTT_LOCK() {                                                 \
                                     /*lint -save -e529 Symbol 'LockState' not subsequently referenced  */ \
                                   unsigned int LockState;                     \
                                  __asm volatile ("mrs   %0, basepri  \n\t"     \
                                                  "mov   r1, %1     \n\t"     \
                                                  "msr   basepri, r1  \n\t"     \
                                                  : "=r" (LockState)            \
                                                  : "i"(SEGGER_RTT_BLOCKED_INTERRUPT_PRIORITY) /* input */\
                                                  : "r1"                        \
                                                  );                            
    
    #define SEGGER_RTT_UNLOCK()   __asm volatile ("msr   basepri, %0  \n\t"     \
                                                  :                             \
                                                  : "r" (LockState)             \
                                                  :                             \
                                                  );                            \
                                     /*lint -restore */                          \
                                 }
  #else
    #define SEGGER_RTT_LOCK()  
    #define SEGGER_RTT_UNLOCK()
  #endif
#endif

/*********************************************************************
*
*       RTT lock configuration for IAR EWARM
*/
#ifdef __ICCARM__
  #if (defined (__ARM6M__) && (__CORE__ == __ARM6M__))
    #define SEGGER_RTT_LOCK() {                                                 \
                                    unsigned int LockState;                     \
                                    LockState = __get_PRIMASK();                \
                                    __set_PRIMASK(1);                           
                                    
    #define SEGGER_RTT_UNLOCK() __set_PRIMASK(LockState);                       \
                                  }
  #elif ((defined (__ARM7EM__) && (__CORE__ == __ARM7EM__)) || (defined (__ARM7M__) && (__CORE__ == __ARM7M__)))
    #define SEGGER_RTT_LOCK() {                                                 \
                                    unsigned int LockState;                     \
                                    LockState = __get_BASEPRI();                \
                                    __set_BASEPRI(128);                           
                                    
    #define SEGGER_RTT_UNLOCK() __set_BASEPRI(LockState);                       \
                                  }  
  #endif
#endif
/*********************************************************************
*
*       RTT lock configuration fallback
*/
#ifndef   SEGGER_RTT_LOCK
  #define SEGGER_RTT_LOCK()                // Lock RTT (nestable)   (i.e. disable interrupts)
#endif

#ifndef   SEGGER_RTT_UNLOCK
  #define SEGGER_RTT_UNLOCK()              // Unlock RTT (nestable) (i.e. enable previous interrupt lock state)
#endif

#endif
/*************************** End of file ****************************/

