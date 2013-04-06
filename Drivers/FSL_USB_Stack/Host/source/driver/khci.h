/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
* All Rights Reserved
*
*************************************************************************** 
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
**************************************************************************
*
* $FileName: khci.h$
* $Version : 3.0.4.0$
* $Date    : Jan-29-2009$
*
* Comments:
*
*   This file contains KHCI-specific implementations of USB interfaces
*
*END************************************************************************/

#ifndef __khci_h__
#define __khci_h__

#include "user_config.h"

#if !HIGH_SPEED_DEVICE
#include "usbprv_host.h"
/* KHCI event bits */
#define KHCI_EVENT_ATTACH       0x01
#define KHCI_EVENT_RESET        0x02
#define KHCI_EVENT_TOK_DONE     0x04
#define KHCI_EVENT_SOF_TOK      0x08
#define KHCI_EVENT_DETACH       0x10
#define KHCI_EVENT_MASK         0x1f

/* atom transaction error results */
#define KHCI_ATOM_TR_PID_ERROR  (-1)
#define KHCI_ATOM_TR_EOF_ERROR  (-2)
#define KHCI_ATOM_TR_CRC_ERROR  (-4)
#define KHCI_ATOM_TR_TO         (-16)
#define KHCI_ATOM_TR_DMA_ERROR  (-32)
#define KHCI_ATOM_TR_BTS_ERROR  (-128)
#define KHCI_ATOM_TR_NAK        (-256)
#define KHCI_ATOM_TR_DATA_ERROR (-512)
#define KHCI_ATOM_TR_STALL      (-1024)
#define KHCI_ATOM_TR_RESET      (-2048)
#define KHCI_ATOM_TR_SENSE_ERR  (-4096)

#define USBCFG_KHCI_TR_QUE_MSG_CNT              (10)
#define USBCFG_KHCI_MAX_INT_TR                  (10)

/* Basic scheduling packets algorithm, schedules next packet to the beginning of next frame
*/
//#define KHCICFG_BASIC_SCHEDULING

/* Scheduling based on internal "deadtime" register THSLD; you can choose additional value passed to the register
** Note that the register value depends on delay on line from host to device and is experimentally set to 0x65,
** which should be enough for the absolute majority of cases.
*/
#define KHCICFG_THSLD_DELAY 0x65

typedef enum 
{
    TR_MSG_UNKNOWN,     /* unknown - not used   */
    TR_MSG_SETUP,       /* setup transaction   */
    TR_MSG_SEND,        /* send trnasaction    */
    TR_MSG_RECV         /* receive transaction */
} TR_MSG_TYPE;

/* atom transaction message */
typedef struct 
{
    TR_MSG_TYPE type;                       /* transaction type */
#ifdef __GNUC__
   uchar       reserved[3];
#endif
    PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc;   /* pointer to pipe descriptor */
    PIPE_TR_STRUCT_PTR pipe_tr;             /* pointer to transaction */
} TR_MSG_STRUCT, _PTR_ TR_MSG_STRUCT_PTR;

/* interrupt transaction */
typedef struct tr_int_que_itm_struct 
{
    uint_32     period;         /* period in [ms] for interrupt endpoint */
    TR_MSG_STRUCT msg;          /* atom transaction message */
} TR_INT_QUE_ITM_STRUCT, _PTR_ TR_INT_QUE_ITM_STRUCT_PTR;

/* endpoint data structure */
typedef struct 
{
    uint_8 rx_bd;
    uint_8 tx_bd;
} EP_STRUCT, _PTR_ EP_STRUCT_PTR;

typedef struct usb_host_callback_functions_struct
{
   /* The Host/Device init function */
   USB_STATUS (_CODE_PTR_ HOST_INIT)(_usb_host_handle);

   /* The function to shutdown the host/device */
   USB_STATUS (_CODE_PTR_ HOST_SHUTDOWN)(_usb_host_handle);

   /* The function to send data */
   USB_STATUS (_CODE_PTR_ HOST_SEND)(_usb_host_handle, struct pipe_descriptor_struct _PTR_, struct pipe_tr_struct _PTR_);

   /* The function to send setup data */
   USB_STATUS (_CODE_PTR_ HOST_SEND_SETUP)(_usb_host_handle, struct pipe_descriptor_struct _PTR_, struct pipe_tr_struct _PTR_);

   /* The function to receive data */
   USB_STATUS (_CODE_PTR_ HOST_RECV)(_usb_host_handle, struct pipe_descriptor_struct _PTR_, struct pipe_tr_struct _PTR_);
   
   /* The function to cancel the transfer */
   USB_STATUS (_CODE_PTR_ HOST_CANCEL)(_usb_host_handle, struct pipe_descriptor_struct _PTR_, struct pipe_tr_struct _PTR_);
   
   /* The function for USB bus control */
   USB_STATUS (_CODE_PTR_ HOST_BUS_CONTROL)(_usb_host_handle, uint_8);

   uint_32 (_CODE_PTR_ HOST_ALLOC_BANDWIDTH)(_usb_host_handle, struct pipe_descriptor_struct _PTR_);

   USB_STATUS (_CODE_PTR_ HOST_FREE_CONTROLLER_RESOURCE)(_usb_host_handle, struct pipe_descriptor_struct _PTR_);
  
   uint_32 (_CODE_PTR_ HOST_EHCI_GET_FRAME_NUM)(_usb_host_handle);   
   
   uint_32 (_CODE_PTR_ HOST_EHCI_GET_MICRO_FRAME_NUM)(_usb_host_handle);   
   
   USB_STATUS (_CODE_PTR_ HOST_OPEN_PIPE)(_usb_host_handle, struct pipe_descriptor_struct _PTR_);
   
   USB_STATUS (_CODE_PTR_ HOST_UPDATE_MAX_PACKET_SIZE)(_usb_host_handle, struct pipe_descriptor_struct _PTR_);
   
   USB_STATUS (_CODE_PTR_ HOST_UPDATE_DEVICE_ADDRESS)(_usb_host_handle, struct pipe_descriptor_struct _PTR_);

} USB_HOST_CALLBACK_FUNCTIONS_STRUCT,  _PTR_ USB_HOST_CALLBACK_FUNCTIONS_STRUCT_PTR;

extern const USB_HOST_CALLBACK_FUNCTIONS_STRUCT _bsp_usb_host_callback_table;
extern void _usb_khci_task(void);

#ifdef OTG_BUILD
	void USB_ISR_HOST(void);
#endif

#endif // HIGH_SPEED_DEVICE
/* scheduling based on time and packet length, not just SOF synchronizing */
#endif