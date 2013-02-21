/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file usb_dci.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions needed by the DCI layer.
 *
 *****************************************************************************/

#ifndef _USB_DCI_H
#define _USB_DCI_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"          /* User Defined Data Types */
#include "derivative.h"     /* include peripheral declarations */
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#ifdef USB_LOWPOWERMODE
typedef enum _stopmode
{
    STOP_MODE1 = 1, /* STOP MODE 1 */
    STOP_MODE2 = 2, /* STOP MODE 2 */
    STOP_MODE3 = 3  /* STOP MODE 3 */
}STOP_MODE;
#endif

/* USBCTL0 Initialization Parameters */
#define _USBPHYEN           (0x01)       /* Use internal transceiver */
#define _USBPUEN            (0x40)       /* Use internal pull-up resistor */
#define _USBREGEN           (0x04)       /* Use the internal regulator */
#define _USBRESET           (0x80)

#define USB_RST             (_USBRESET)   			/* USB_RESET */
#define UCFG_VAL            (_USBPUEN|_USBPHYEN) 	/* Config value to
                                                       enable USB */

#define CTL_RESET_VAL (0)             /* value programmed to the CTL
                                         register in RESET */

#define EP_CTRL     (0x0C)            /* Cfg Control pipe for this endpoint */
#define EP_OUT      (0x08)            /* Cfg OUT only pipe for this endpoint*/
#define EP_IN       (0x04)            /* Cfg IN only pipe for this endpoint */
#define HSHK_EN     (0x01)            /* Enable handshake packet            */
                                      /* Handshake should be disable for
                                         isochorous transfer                */

#define EP_DISABLE  (0)

#define MAX_EP_BUFFER_SIZE  USB_MAX_EP_BUFFER_SIZE /*Max Endpoint Buffer Size*/

/* Macro's to check whether corresponding INTSTAT bit is set */
#define BUS_RESET_FLAG(x)               ((x) & 1)
#define ERROR_FLAG(x)                   ((x) & 2)
#define SOF_TOKEN_FLAG(x)               ((x) & 4)
#define TOKEN_COMPL_FLAG(x)             ((x) & 8)
#define SLEEP_FLAG(x)                   ((x) & 0x10)
#define RESUME_FLAG(x)                  ((x) & 0x20)
#define STALL_FLAG(x)                   ((x) & 0x80)

/* Macro's to set corresponding INTSTAT bit */
#define BUS_RESET_FLAG_SET(x)               ((x) |= 1)
#define ERROR_FLAG_SET(x)                   ((x) |= 2)
#define SOF_TOKEN_FLAG_SET(x)               ((x) |= 4)
#define TOKEN_COMPL_FLAG_SET(x)             ((x) |= 8)
#define SLEEP_FLAG_SET(x)                   ((x) |= 0x10)
#define RESUME_FLAG_SET(x)                  ((x) |= 0x20)
#define STALL_FLAG_SET(x)                   ((x) |= 0x80)

/* Macro's to clear corresponding INTSTAT bit */
#define BUS_RESET_FLAG_CLR(x)               ((x) &= ~1)
#define ERROR_FLAG_CLR(x)                   ((x) &= ~2)
#define SOF_TOKEN_FLAG_CLR(x)               ((x) &= ~4)
#define TOKEN_COMPL_FLAG_CLR(x)             ((x) &= ~8)
#define SLEEP_FLAG_CLR(x)                   ((x) &= ~0x10)
#define RESUME_FLAG_CLR(x)                  ((x) &= ~0x20)
#define STALL_FLAG_CLR(x)                   ((x) &= ~0x80)

/* Setup the controller for Remote Wakeup */
#define USB_DCI_WAKEUP              \
    {                               \
        INTSTAT_RESUMEF = 1;        \
        INTENB_RESUME = 0;          \
        CTL_TSUSPEND = 0;           \
    }
/* control endpoint transfer types */
#define USB_TRF_UNKNOWN      (0xff)

#define BDT_MIN_BUFFER_SIZE             (16)   /* space occupied by smallest
                                                              buffer in BDT */

#define BDT_MIN_BUFFER_ADDR_INC         (4)    /* min offset increment
                                                 correspoding to min buffer
                                                 size */

#define BDT_OFFSET_SHIFT                (4)    /* bdt offset shift */

#define INVALID_BDT_INDEX               (0xff) /* invalid bdt index */

#define ENDPOINT_NUMBER_SHIFT           (4)    /* endpoint shift & mask to  */
#define ENDPOINT_NUMBER_MASK            (0xf0) /* use in setting and getting
                                                  status */

#define ENDPOINT_DIRECTION_SHIFT        (3)    /* direction shift & mask to */
#define ENDPOINT_DIRECTION_MASK         (0x08) /* be used for STAT byte
                                                  in BDT */

#define SEND_CONTROL_ENDPOINT_BDT_INDEX (0)    /* BDT Index for Control
                                                  Endpoint SEND direction */
#define RECV_CONTROL_ENDPOINT_BDT_INDEX (1)    /* BDT Index for Control
                                                  Endpoint RECV direction */

#define EPCTL_STALL                     (0x02) /* Stall bit in Endpoint
                                                  Control Reg */

#define USB_SETUP_TOKEN                 (0x0d) /* Setup Token PID */
#define USB_SETUP_DIRECTION             (0x80) /* Data xfer direction
                                                  for Setup packet */

#define INTSTAT_CLEAR_ALL               (0xbf) /* Value to clear
                                                  all Interrupts */
#define ERRSTAT_CLEAR_ALL               (0xbf) /* Value to clear
                                                  all Errors */
#define ERRENB_ENABLE_ALL               (0xbf) /* Value to enable
                                                  all Error Interrupts */
#define INTENB_BUS_RESET_VAL            (0x9f) /* Value to enable
                                                  Interrupts in Bus Reset */
#define INTENB_DISABLE_ALL_VAL          (0x00) /* Value to disable all
                                                  Interrupts */

#define MAX_USB_RAM_BUFFER_INDEX        (14)   /* MAX possible RAM buffer
                                                  Index */

#define EP_START_BUFFER_ADDR            (0x08) /* First USB_RAM buffer offset*/

#define ASSERT_RESUME_DELAY_COUNT       (12000) /* Delay for assert resume */

#define NO_ERRORS                       (0)    /* Init value for error */

#define STAT_ODD_SHIFT                  (2)

/******************************************************************************
 * Types
 *****************************************************************************/
#if (defined(LONG_SEND_TRANSACTION) || defined (LONG_RECEIVE_TRANSACTION))
#define LONG_TRANSACTION
#endif

/* This structure holds endpoint parameters and transaction parameters
on the IO's happening on them */
typedef struct  _BDT_ELEM
{
    uint_8             len;         /* endpoint max buffer len */
    uint_8             addr;        /* endpoint buffer addr in USB_RAM */
#ifdef LONG_TRANSACTION
    uint_8_ptr         app_buffer;  /* application buffer pointer */
    USB_PACKET_SIZE    app_len;     /* application buffer len */
    USB_PACKET_SIZE    curr_offset; /* current offset for long transactions*/
#endif
    uint_8         flag;            /* zero termination flag */
    uint_8         bdtmap_index;    /* BDT MAP Index */
} BDT_ELEM, *P_BDT_ELEM;

 /*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Device_Call_Service(
    uint_8                  type,
    PTR_USB_DEV_EVENT_STRUCT    event
);


#endif
