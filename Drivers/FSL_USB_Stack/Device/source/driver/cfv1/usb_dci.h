/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
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
 * @date
 *
 * @brief The file contains Macro's and functions needed by the DCI layer.
 *
 *****************************************************************************/

#ifndef _USB_DCI_H
#define _USB_DCI_H
/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "derivative.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define BYTES_1024              (1024)
#define BYTES_512               (512)
#define ENDPT_EP_STALL_MASK     (0x02)
#define FRAME_HIGH_BYTE_SHIFT    (8)

#ifdef USB_LOWPOWERMODE
typedef enum _stopmode
{
    STOP_MODE1 = 1, /* STOP MODE 1 */
    STOP_MODE2 = 2, /* STOP MODE 2 */
    STOP_MODE3 = 3, /* STOP MODE 3 */
    STOP_MODE4 = 4  /* STOP MODE 4 */
}STOP_MODE;
#endif

/* USBTRC0 Initialization Parameters */
#define _USBPHYEN           (0x01)       /* Use internal transceiver */
#define _USBPUEN            (0x40)       /* Use internal pull-up resistor */
#define _USBREGEN           (0x04)       /* Use the internal regulator */
#define _USBRESET           (0x80)

#define UCFG_VAL            (_USBPUEN|_USBREGEN) 

#define CTL_RESET_VAL (0)             /* value programmed to the CTL 
                                         register in RESET */

#define EP_CTRL     (0x0C)            /* Cfg Control pipe for this endpoint */
#define EP_OUT      (0x08)            /* Cfg OUT only pipe for this endpoint*/
#define EP_IN       (0x04)            /* Cfg IN only pipe for this endpoint */
#define HSHK_EN     (0x01)            /* Enable handshake packet            */
                                      /* Handshake should be disable for
                                         isochorous transfer                */
#define EP_CTL_DIS  (0x10)

#define EP_DISABLE  (0)                                         
                                 
#define TRANSFER_INDEX(x)  (x>>1)                                       

#define MAX_EP_BUFFER_SIZE  USB_MAX_EP_BUFFER_SIZE /*Max Endpoint Buffer Size*/

/* Macro's to check whether corresponding INT_STAT bit is set */
#define BUS_RESET_FLAG(x)               ((x) & 1)  
#define ERROR_FLAG(x)                   ((x) & 2)
#define SOF_TOKEN_FLAG(x)               ((x) & 4)
#define SLEEP_FLAG(x)                   ((x) & 0x10)
#define RESUME_FLAG(x)                  ((x) & 0x20)
#define STALL_FLAG(x)                   ((x) & 0x80)
#define TOKEN_COMPL_FLAG(x)             ((x) & 8)

/* Setup the controller for Remote Wakeup */
#define USB_DCI_WAKEUP				\
{									\
	INT_STAT_RESUME = 1; 			\
	INT_ENB_RESUME_EN = 0; 			\
	CTL_TXSUSPEND_TOKENBUSY = 0;	\
}

/* control endpoint transfer types */
#define USB_TRF_UNKNOWN      			(0xFF)


#define BDT_MIN_BUFFER_SIZE             (16)  /* space occupied by smallest 
                                                           buffer in BDT */
                                                              
#define BDT_MIN_BUFFER_ADDR_INC         (4)   /* min offset increment  
                                                 correspoding to min buffer 
                                                 size */
                                                 
#define BDT_OFFSET_SHIFT                (4)   /* bdt offset shift */

#define INVALID_BDT_INDEX               (0xff)/* invalid bdt index */  

#define ENDPOINT_NUMBER_SHIFT           (4)   /* endpoint shift & mask to  */
#define ENDPOINT_NUMBER_MASK            (0xf0)/* use in setting and getting 
                                                 status */

#define ENDPOINT_DIRECTION_SHIFT        (3)   /* direction shift & mask to */
#define ENDPOINT_DIRECTION_MASK         (0x08)/* be used for STAT byte 
                                                 in BDT */

#define SEND_CONTROL_ENDPOINT_BDT_INDEX (2)   /* BDT Index for Control Endpoint 
                                                 SEND direction */
#define RECV_CONTROL_ENDPOINT_BDT_INDEX (0)   /* BDT Index for Control Endpoint
                                                 RECV direction */
                               
#define EPCTL_STALL                     (0x02)/* Stall bit in Endpoint 
                                                  Control Reg */
                                 
#define USB_SETUP_TOKEN                 (0x0d)/* Setup Token PID */
#define USB_SETUP_DIRECTION             (0x80)/* Data xfer direction 
                                                 for Setup packet */

#define INT_STAT_CLEAR_ALL              (0xbf)/* Value to clear 
                                                 all Interrupts */
#define ERR_STAT_CLEAR_ALL              (0xbf)/* Value to clear 
                                                 all Errors */
#define ERR_ENB_ENABLE_ALL              (0xbf)/* Value to enable 
                                                 all Error Interrupts */
#define INTENB_BUS_RESET_VAL            (0x9f)/* Value to enable 
                                                 Interrupts in Bus Reset */
#define INTENB_DISABLE_ALL_VAL          (0x00)/* Value to disable all 
                                                 Interrupts */

#define MAX_USB_RAM_BUFFER_INDEX        (14)  /* MAX possible RAM buffer  
                                                 Index */

#define EP_START_BUFFER_ADDR            (0x08)/* First USB_RAM buffer offset*/


#define ASSERT_RESUME_DELAY_COUNT       (20000)/* Delay for assert resume */

#define NO_ERRORS                       (0)   /* Init value for error */

#define USB_RAM_EVEN_BUFFER             (0)
#define USB_RAM_ODD_BUFFER              (1)

#define SWAP16(val)                                                 \
    (uint_16)((((uint_16)(val) >> 0x8) & 0xFF) |                    \
    (((uint_16)(val) & 0xFF) << 0x8))

#define SWAP32(val)                                                 \
    (uint_32)((SWAP16((uint_32)(val) & (uint_32)0xFFFF) << 0x10) |  \
    (SWAP16((uint_32)((val) >> 0x10))))

/******************************************************************************
 * Types
 *****************************************************************************/
#ifdef LONG_SEND_TRANSACTION
  #define LONG_TRANSACTION
#endif 

#ifdef LONG_RECEIVE_TRANSACTION
  #define LONG_TRANSACTION
#endif 

#pragma pack(1)
/* This structure is used to hold endpoint paramaetes and the 
   transaction parameters on the IO's happening on them */
typedef struct  _BDT_ELEM 
{
	uint_16            len;             /* endpoint max buffer len */
	uint_32            addr;            /* endpoint buffer addr in USB_RAM */
#ifdef LONG_TRANSACTION
    uint_8_ptr         app_buffer;      /* application buffer pointer */
    USB_PACKET_SIZE    app_len;         /* application buffer len */
    USB_PACKET_SIZE    curr_offset;     /* current offset for long transactions */
#endif  
    uint_8         flag;                /* zero termination flag */
    uint_8         bdtmap_index;        /* Corresponding to the buffer */
    uint_8         direction;           /* Direction (Send/Receive) */  
    uint_8         type;                /* Type of Endpoint */
} BDT_ELEM, *P_BDT_ELEM;
#pragma options align=reset

 /*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Device_Call_Service(
    uint_8                    type, 
    PTR_USB_DEV_EVENT_STRUCT  event 
);

#if 0 /* << EST */
#ifndef OTG_BUILD
void interrupt VectorNumber_Vusb USB_ISR(void);
#else
void USB_ISR(void);
#endif
#else
void USB_ISR(void);
#endif

#endif