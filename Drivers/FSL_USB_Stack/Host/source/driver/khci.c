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
* $FileName: khci.c$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains KHCI-specific implementations of USB interfaces
*
*END************************************************************************/
#include "khci.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usbmsgq.h"
#include "usbevent.h"
#include "usb_host_hub.h"
#include "rtc.h"
#include "hidef.h"

#ifdef USE_POLL
#include "poll.h"
#endif

#include "usb_classes.h"

#include "derivative.h"
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
#include "usb_lock.h"
#endif
/* Global variables */
#pragma define_section usb_bdt ".usb_bdt" RW
__declspec(usb_bdt) static uint_8 bdt[512] = { 1 };

#define MCF522X_USBOTG_BD_BC(n)                 ((n & 0x3ff) << 16)
#define MCF522X_USBOTG_ADDR_ADDR(x)             (((x)&0x7F)<<0)
#define MCF522X_USBOTG_BD_OWN                   0x80
#define MCF522X_USBOTG_BD_DATA01(n)             ((n & 1) << 6)
#define MCF522X_USBOTG_TOKEN_TOKEN_ENDPT(x)     (((x)&0xF)<<0)
#define _int_enable() USB_unlock()
#define HWTICKS_PER_MSEC     12500
#define HWTICKS_PER_TICK     62500
#define BDT_BASE              ((uint_32*)(bdt))
#define BD_PTR(ep, rxtx, odd)      (((uint_32)BDT_BASE) & 0xfffffe00 | ((ep & 0x0f) << 5) | ((rxtx & 1) << 4) | ((odd & 1) << 3))
/* FIXME: actually, only endpoint_data[0] is used in atom transaction */
static EP_STRUCT endpoint_data[16];
static USB_HOST_STATE_STRUCT_PTR _usb_host_ptr;
static USB_EVENT_STRUCT khci_event;
/* Transaction que */
USBMSGQ_STRUCT tr_que;
static PIPE_DESCRIPTOR_STRUCT_PTR last_to_pipe = NULL;
extern USB_HOST_STATE_STRUCT_PTR usb_host_state_struct_ptr;
uint_8 endpoint_stalled = FALSE;

static TR_INT_QUE_ITM_STRUCT TR_INT_QUE[USBCFG_KHCI_MAX_INT_TR];

//      static uint_32 HWTICKS_CONST_FS_ADD;
//      static uint_32 HWTICKS_CONST_FS_MUL;
//      static uint_32 HWTICKS_CONST_LS_ADD;
//      static uint_32 HWTICKS_CONST_LS_MUL;

/* Function prototypes */
static void   _usb_khci_process_tr_complete(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr, PIPE_TR_STRUCT_PTR pipe_tr_ptr, uint_32 remain, int_32 err);
static int_32 _usb_khci_get_hot_int_tr(TR_MSG_STRUCT *msg);
static int_32 _usb_khci_atom_tr(uint_32 type, uint_32 host_speed, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr, uint_8 *buf, uint_16 len);
USB_STATUS _usb_khci_init(_usb_host_handle handle);
USB_STATUS _usb_khci_shutdown(_usb_host_handle handle);
USB_STATUS    _usb_khci_send(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr, PIPE_TR_STRUCT_PTR pipe_tr_ptr);
USB_STATUS    _usb_khci_send_setup(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr, PIPE_TR_STRUCT_PTR pipe_tr_ptr);
USB_STATUS    _usb_khci_recv(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr, PIPE_TR_STRUCT_PTR pipe_tr_ptr);
USB_STATUS    _usb_khci_cancel(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr, PIPE_TR_STRUCT_PTR pipe_tr_ptr);
USB_STATUS _usb_khci_bus_control(_usb_host_handle handle, uint_8 bus_control);
uint_32 _usb_khci_get_frame_number(_usb_host_handle handle);
USB_STATUS    _usb_khci_host_open_pipe(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr);
USB_STATUS    _usb_khci_host_close_pipe(_usb_host_handle handle, PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr);
#ifndef OTG_BUILD
void interrupt VectorNumber_Vusb USB_ISR_HOST(void);
#endif
const USB_HOST_CALLBACK_FUNCTIONS_STRUCT _bsp_usb_host_callback_table =
{
/* The Host/Device init function */
_usb_khci_init,
/* The function to shutdown the host/device */
_usb_khci_shutdown,
/* The function to send data */
_usb_khci_send,
/* The function to send setup data */
_usb_khci_send_setup,
/* The function to receive data */
_usb_khci_recv,
/* The function to cancel the transfer */
_usb_khci_cancel,
/* The function for USB bus control */
   _usb_khci_bus_control,
   NULL,
/* The function to close pipe */
_usb_khci_host_close_pipe,
/* Get frame number function */
_usb_khci_get_frame_number,
/* Get microframe number function - not applicable on FS */
NULL,
/* Open pipe function */
   _usb_khci_host_open_pipe,
   NULL,   
   NULL
};
asm uint_32 mcf5xxx_byterev(uint_32 val);

__declspec(register_abi) asm uint_32 mcf5xxx_byterev(uint_32 val)
{
#if __STDABI__ == 1
	move.l 4(sp), d0
#endif 
	byterev.l d0
	rts
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_init_int_tr
 *  Returned Value : None
 *  Comments       :
 *        Initialize interrupt transaction que
 *END*-----------------------------------------------------------------*/
static void _usb_khci_init_int_tr(void)
{
	uint_32 i;
	TR_INT_QUE_ITM_STRUCT_PTR tr = TR_INT_QUE;
	for (i = 0; i < USBCFG_KHCI_MAX_INT_TR; i++, tr++)
	{
		tr->msg.type = TR_MSG_UNKNOWN;
	}
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_add_int_tr
 *  Returned Value : -1 que is full
 *  Comments       :
 *        Add new interrupt transaction to que
 *END*-----------------------------------_------------------------------*/
static int_32 _usb_khci_add_int_tr
(    
/* [IN] Pointer to message */
TR_MSG_STRUCT *msg,
/* Not use */
uint_32 period)
{
	int_32 i = 0;
	TR_INT_QUE_ITM_STRUCT_PTR tr = TR_INT_QUE;

	UNUSED(period)
	/* Find free position */
	for (i = 0; i < USBCFG_KHCI_MAX_INT_TR; i++, tr++)
	{
		if (tr->msg.type == TR_MSG_UNKNOWN)
		{
			memcpy(&tr->msg, msg, sizeof(TR_MSG_STRUCT));
			break;
		}
	}
	return (i < USBCFG_KHCI_MAX_INT_TR) ? i : -1;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_atom_tr
 *  Returned Value :  
 *  Comments       :
 *        
 *END*------------------------------------------------------------------*/
static int_32 _usb_khci_atom_tr
(    
/* [IN] Transfer type */
uint_32 type,
/* [IN] host speed */
uint_32 host_speed,
/* [IN] pipe descriptor pointer */
PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr,
/* [IN] buffer pointer */
uint_8 *buf,
/* [IN] length */
    uint_16 len
) 
{
	EP_STRUCT_PTR ep_ptr;
	uint_32 bd;
	int_32 res;
	int_32 retry, old_len;
	int_32 delay_const = 10;
    uint_32 event_wait_ticks_count; 
	last_to_pipe = NULL; /* At the beginning, consider that there was not timeout */
	old_len = len;
	len = (uint_16) ((len > pipe_desc_ptr->MAX_PACKET_SIZE) ? pipe_desc_ptr->MAX_PACKET_SIZE : len);
	ep_ptr = &endpoint_data[0];
	/* ADDR must be written before ENDPT0 (undocumented behavior) for to generate PRE packet */
	ADDR = (uint_8) ((pipe_desc_ptr->SPEED == USB_SPEED_FULL) ? MCF522X_USBOTG_ADDR_ADDR(pipe_desc_ptr->DEVICE_ADDRESS)
					: ADDR_LS_EN_MASK | MCF522X_USBOTG_ADDR_ADDR(pipe_desc_ptr->DEVICE_ADDRESS));

	if (pipe_desc_ptr->PIPETYPE != USB_ISOCHRONOUS_PIPE)
	{
		ENDPT0 = (uint_8) (host_speed == USB_SPEED_LOW ? ENDPT0_HOST_WO_HUB_MASK : 0) 
                        | ENDPT0_RETRY_DIS_MASK | ENDPT0_EP_TX_EN_MASK
                        | ENDPT0_EP_RX_EN_MASK | ENDPT0_EP_HSHK_MASK;
	}
	else
	{
		ENDPT0 = (uint_8) (host_speed == USB_SPEED_LOW ? ENDPT0_HOST_WO_HUB_MASK : 0) 
                        | ENDPT0_RETRY_DIS_MASK | ENDPT0_EP_TX_EN_MASK
                        | ENDPT0_EP_RX_EN_MASK;
	}

	switch (pipe_desc_ptr->PIPETYPE)
	{
	case USB_INTERRUPT_PIPE:
	case USB_ISOCHRONOUS_PIPE:
		retry = 0;
		break;
	default:
		retry = pipe_desc_ptr->NAK_COUNT;
		break;
	}

	do
	{
		res = 0;
		/*  Wait for USB ready, but with timeout */
		event_wait_ticks_count = 0;
		while (CTL & CTL_TXSUSPEND_TOKENBUSY_MASK)
		{
			delay(1);
			event_wait_ticks_count++;
            if (USB_EVENT_SET == _usb_event_wait_ticks(&khci_event, KHCI_EVENT_MASK, FALSE, 1) == USB_OK) 
			{
				break;
			}
			else if (50 == event_wait_ticks_count)
			{
				res = KHCI_ATOM_TR_RESET;
				break;
			}
		}
		if (!res)
		{
			/* All is ok, do transaction */
#if defined(KHCICFG_BASIC_SCHEDULING)
			INT_STAT |= INT_STAT_SOF_TOK_MASK; /* Clear SOF */
			while (!(INT_STAT & INT_STAT_SOF_TOK_MASK))
			/* wait for next SOF */
			SOF_THLD = 0;
#else
			/* Reserve enough time to ensure worst case transaction completes */
			if (pipe_desc_ptr->SPEED == USB_SPEED_FULL)
				SOF_THLD = len * 7 / 6 + KHCICFG_THSLD_DELAY;
			else
				SOF_THLD = len * 12 * 7 / 6 + KHCICFG_THSLD_DELAY;
#endif           
			INT_STAT |= INT_STAT_SOF_TOK_MASK; /* clear SOF */
			ERR_STAT = 0xFF; /* clear error status */
			switch (type)
			{
			case TR_CTRL:
				pipe_desc_ptr->bd_ptr = (uint_32*) BD_PTR(0, 1, ep_ptr->tx_bd);
				*((uint_32*) BD_PTR(0, 1, ep_ptr->tx_bd) + 1) = mcf5xxx_byterev((uint_32) buf);
				*((uint_32*) BD_PTR(0, 1, ep_ptr->tx_bd)) = mcf5xxx_byterev((uint_32) MCF522X_USBOTG_BD_BC(len) | 
				        (0x80));			     				
				TOKEN = (uint_8) (MCF522X_USBOTG_TOKEN_TOKEN_ENDPT((uint_8)pipe_desc_ptr->ENDPOINT_NUMBER) | (0xD0));				
				ep_ptr->tx_bd ^= 1;
				break;
			case TR_IN:
				pipe_desc_ptr->bd_ptr = (uint_32*) BD_PTR(0, 0, ep_ptr->rx_bd);
				*((uint_32*) BD_PTR(0, 0, ep_ptr->rx_bd) + 1) = mcf5xxx_byterev((uint_32) buf);
				*((uint_32*) BD_PTR(0, 0, ep_ptr->rx_bd)) = mcf5xxx_byterev((uint_32) MCF522X_USBOTG_BD_BC(len) | 
				        0x80 | MCF522X_USBOTG_BD_DATA01(pipe_desc_ptr->NEXTDATA01));
				TOKEN = (uint_8) (MCF522X_USBOTG_TOKEN_TOKEN_ENDPT((uint_8)pipe_desc_ptr->ENDPOINT_NUMBER) | (0x90));
				ep_ptr->rx_bd ^= 1;
				break;
			case TR_OUT:
				pipe_desc_ptr->bd_ptr = (uint_32*) BD_PTR(0, 1, ep_ptr->tx_bd);
				*((uint_32*) BD_PTR(0, 1, ep_ptr->tx_bd) + 1) = mcf5xxx_byterev((uint_32) buf);
				*((uint_32*) BD_PTR(0, 1, ep_ptr->tx_bd)) = mcf5xxx_byterev((uint_32) MCF522X_USBOTG_BD_BC(len) | 
				        0x80 | MCF522X_USBOTG_BD_DATA01(pipe_desc_ptr->NEXTDATA01));
				TOKEN = (uint_8) (MCF522X_USBOTG_TOKEN_TOKEN_ENDPT((uint_8)pipe_desc_ptr->ENDPOINT_NUMBER) | (0x10));
				ep_ptr->tx_bd ^= 1;
				break;
			default:
				pipe_desc_ptr->bd_ptr = NULL;
			}

			event_wait_ticks_count = 0;
			while (USB_EVENT_NOT_SET == _usb_event_wait_ticks(&khci_event, KHCI_EVENT_MASK, FALSE, 100))
			{
				delay(1);				
				event_wait_ticks_count++;
				if (1000 == event_wait_ticks_count)
				{
					res = KHCI_ATOM_TR_TO;
					last_to_pipe = pipe_desc_ptr;
					break;
				}
			}
		}
		try_again:
		/* check for reset event (detach)*/
		if (khci_event.VALUE & KHCI_EVENT_RESET)
		{
			res = KHCI_ATOM_TR_RESET;
			break;
		}
		if ((pipe_desc_ptr->bd_ptr != NULL) && (khci_event.VALUE & KHCI_EVENT_TOK_DONE))
		{
			/* transaction finished */
			_usb_event_clear(&khci_event, KHCI_EVENT_TOK_DONE);
			/* check result*/
			bd = mcf5xxx_byterev(*pipe_desc_ptr->bd_ptr);

			if (ERR_STAT & (
			        ERR_STAT_PID_ERR_MASK   | 
			        ERR_STAT_CRC16_MASK     |
#if defined (KHCICFG_BASIC_SCHEDULING)                   
					ERR_STAT_CRC5_EOF_MASK  |
#endif
					ERR_STAT_DFN8_MASK      |
					//ERR_STAT_DMA_ERR_MASK |
					//ERR_STAT_BTO_ERR_MASK |		// 
					ERR_STAT_BTS_ERR_MASK))
			{
#if defined (KHCICFG_BASIC_SCHEDULING)
				if (ERR_STAT & ERR_STAT_CRC5_EOF_MASK)
				    retry = 0;
#endif                
				res = -ERR_STAT;
				break;
			}
			else
			{
				switch (bd >> 2 & 0xf)
				{
				case 0x03: /* DATA0 */
				case 0x0b: /* DATA1 */
				case 0x02: /* ACK */
					retry = 0;
					res = (int_32) ((bd >> 16) & 0x3ff);
					pipe_desc_ptr->NEXTDATA01 ^= 1; /* switch data toggle */
					break;
				case 0x0e: /* STALL */
					res = KHCI_ATOM_TR_STALL;
					retry = 0;
					break;
				case 0x0a: /* NAK */
					res = KHCI_ATOM_TR_NAK;
					if (retry)
                            time_delay(delay_const * (pipe_desc_ptr->NAK_COUNT - retry));
					break;
				case 0x00: /* bus timeout */
					/* wait a bit, but not too much, perhaps some error occurs on the bus */
					if (pipe_desc_ptr->PIPETYPE != USB_ISOCHRONOUS_PIPE)
					{
						/* wait a bit, but not too much, perhaps some error occurs on the bus */
						event_wait_ticks_count = 0;
						while (USB_EVENT_NOT_SET == _usb_event_wait_ticks(&khci_event, KHCI_EVENT_MASK, FALSE, (uint_16) delay_const))
						{
							delay(1);							
							event_wait_ticks_count++;
							if (500 == event_wait_ticks_count)
							{
								res = KHCI_ATOM_TR_TO;
								last_to_pipe = pipe_desc_ptr; /* remember this pipe as it had timeout last time */
								if (retry)
									time_delay(delay_const * (pipe_desc_ptr->NAK_COUNT - retry));
								break;
							}
						}
						if (500 != event_wait_ticks_count)						
							goto try_again;						
					}
					else
					{
						retry = 0;
						res = (int_32) ((bd >> 16) & 0x3ff);
						pipe_desc_ptr->NEXTDATA01 ^= 1; /* switch data toggle */
					}
					break;

				case 0x0f: /* data error */
					/* if this event happens during enumeration, then return means not finished enumeration */
					res = KHCI_ATOM_TR_DATA_ERROR;
					time_delay(delay_const * (pipe_desc_ptr->NAK_COUNT - retry));
					break;
				default:
					break;
				}
			}
		}
	} while (retry--);
	return res;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_process_tr_complete
 *  Returned Value : none
 *  Comments       :
 *        Transaction complete
 *END*-----------------------------------------------------------------*/
static void _usb_khci_process_tr_complete
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] pipe descritor pointer */
PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr,
/* [IN] Pipe transfer pointer */
PIPE_TR_STRUCT_PTR pipe_tr_ptr,
/* [IN] remaining bytes */
uint_32 remaining_bytes,
/* [IN] error */
    int_32 err
) 
{
	USB_HOST_STATE_STRUCT_PTR usb_host_ptr = (USB_HOST_STATE_STRUCT_PTR) handle;

	uchar_ptr buffer_ptr = NULL;
	uint_32 total_req_bytes = 0;
	uint_32 status = 0;

	if (err == KHCI_ATOM_TR_STALL)
	{
		status = USBERR_ENDPOINT_STALLED;
		endpoint_stalled = TRUE;
	}
	else if ((err == KHCI_ATOM_TR_NAK) || (err >= 0))
	{
		status = USB_OK;
		if ((remaining_bytes > 0) || (err == KHCI_ATOM_TR_NAK)) /* remaining bytes */
			status = USBERR_TR_FAILED;

		if (pipe_desc_ptr->PIPETYPE == USB_CONTROL_PIPE)
		{
			if (pipe_tr_ptr->SEND_PHASE)
			{
				total_req_bytes = pipe_tr_ptr->TX_LENGTH;
				buffer_ptr = pipe_tr_ptr->TX_BUFFER;
				pipe_tr_ptr->SEND_PHASE = FALSE;
			}
			else
			{
				total_req_bytes = pipe_tr_ptr->RX_LENGTH;
				buffer_ptr = pipe_tr_ptr->RX_BUFFER;
			}
		}
            else {
			if (pipe_desc_ptr->DIRECTION)
			{
				total_req_bytes = pipe_tr_ptr->TX_LENGTH;
				buffer_ptr = pipe_tr_ptr->TX_BUFFER;
			}
			else
			{
				total_req_bytes = pipe_tr_ptr->RX_LENGTH;
				buffer_ptr = pipe_tr_ptr->RX_BUFFER;
			}
		}
	}
	else if (err < 0)
		status = USBERR_TR_FAILED;

	pipe_tr_ptr->status = USB_STATUS_IDLE;
	pipe_tr_ptr->TR_INDEX = 0;
	if (pipe_tr_ptr->status == USB_STATUS_IDLE)
	{
		/* Transfer done. Call the callback function for this
		 ** transaction if there is one (usually true). 
		 */
		if (pipe_tr_ptr->CALLBACK != NULL)
		{
                pipe_tr_ptr->CALLBACK((pointer)pipe_desc_ptr, pipe_tr_ptr->CALLBACK_PARAM,
                    buffer_ptr, (total_req_bytes - remaining_bytes), status);
			/* If the application enqueued another request on this pipe 
			 ** in this callback context then it will be at the end of the list
			 */
		}
	}
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_rm_int_tr
 *  Returned Value : 0 successful
 *  Comments       :
 *        Remove interrupt transaction from que
 *END*-----------------------------------------------------------------*/
static int _usb_khci_rm_int_tr
(    
/* [IN] Pointer to message */
    TR_MSG_STRUCT *msg
) 
{
	int_32 i = 0, res = -1;
	static uint_32 countrm_int_tr = 0;
	TR_INT_QUE_ITM_STRUCT_PTR tr = TR_INT_QUE;

    /* find record */
    for (i = 0; i < USBCFG_KHCI_MAX_INT_TR; i++, tr++)
    {
        if ((tr->msg.pipe_desc == msg->pipe_desc) && (tr->msg.pipe_tr == msg->pipe_tr))
        {
          tr->msg.type = TR_MSG_UNKNOWN;
          return 0;
        }
    }
    return -1;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_init
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        Initialize the kirin HCI controller
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_init
(
/* [IN] the USB Host state structure */
    _usb_host_handle handle
)
{
	USB_STATUS status = USB_OK;
    static const uint_32  msg_size_in_max_type = 1 + (sizeof(TR_MSG_STRUCT) - 1) / sizeof(uint_32);

	UNUSED(handle)
    if (_usb_msgq_init(USBCFG_KHCI_TR_QUE_MSG_CNT, sizeof(TR_MSG_STRUCT)/sizeof(uint_32)) != USB_MSGQ_OK) 
	{
		/* usb_msgq_init failed */
		return USBERR_INIT_FAILED;
	}
	_usb_event_init(&khci_event);
	INT_STAT = 0xff;
	/* Enable weak pull-downs, useful for detecting detach, set clock source */
#ifdef _MCF51JM128_H 
	USB_CTRL = USB_CTRL_PDE_MASK | USB_CTRL_CLK_SRC_MASK;
#else
	USB_CTRL = USB_CTRL_CLK_SRC0_MASK;
#endif
	/* Remove suspend state */
	USB_CTRL &= ~USB_CTRL_SUSP_MASK;

	CTL |= CTL_ODD_RST_MASK;

	memset(&endpoint_data, 0, sizeof(endpoint_data));
	BDT_PAGE_01 = (uint_8) ((uint_32) BDT_BASE >> 8);
	BDT_PAGE_02 = (uint_8) ((uint_32) BDT_BASE >> 16);
	BDT_PAGE_03 = (uint_8) ((uint_32) BDT_BASE >> 24);

	/* Set SOF threshold */
	SOF_THLD = 1;

	/* Enable Host Mode */
	CTL = CTL_HOST_MODE_EN_MASK;

	/* Enable the ATTACH interrupt */
	INT_ENB = INT_ENB_ATTACH_EN_MASK;

	/* Following is for OTG control instead of internal bus control */
	//OTG_CTRL = OTG_CTRL_DM_LOW_MASK | OTG_CTRL_DP_LOW_MASK | OTG_CTRL_OTG_EN_MASK;    

	_usb_khci_init_int_tr();

#ifdef USE_POLL
	/* Register polling function */
	POLL_register((POLL_POINTER) _usb_khci_task);
#endif

	return status;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_shutdown - NOT IMPLEMENT YET
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function to shutdown the host
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_shutdown
(
/* [IN] the USB Host state structure */
    _usb_host_handle handle
) 
{
	UNUSED(handle)
	INT_ENB = 0;
	CTL = 0;
	INT_STAT = 0xff;

	return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_send
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function to send data
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_send
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] pipe descriptor pointer */
PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr,
/* [IN] Pipe transfer pointer */
    PIPE_TR_STRUCT_PTR pipe_tr_ptr
) 
{
	USB_STATUS status = USB_OK;
	TR_MSG_STRUCT msg;

	UNUSED(handle)

	msg.type = TR_MSG_SEND;
	msg.pipe_desc = pipe_desc_ptr;
	msg.pipe_tr = pipe_tr_ptr;
	_usb_msgq_send((int*) &msg);
	return status;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_cancel
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function to cancel the transfer
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_cancel
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] pipe descriptor pointer */
PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr,
/* [IN] pipe transfer pointer */
    PIPE_TR_STRUCT_PTR pipe_tr_ptr
) 
{
	TR_MSG_STRUCT msg;

	UNUSED(handle)
	UNUSED(pipe_desc_ptr)
	UNUSED(pipe_tr_ptr)

	/* remove messages from KHCI msg que */
	while (_usb_msgq_receive((int*) &msg) == USB_MSGQ_OK)
		/* void */;
	return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_recv
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function to receive data
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_recv
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] pipe descriptor pointer */
PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr,
/* [IN] pipe transfer pointer */
    PIPE_TR_STRUCT_PTR pipe_tr_ptr
) 
{
	USB_STATUS status = USB_OK;
	TR_MSG_STRUCT msg;

	UNUSED(handle)

	msg.type = TR_MSG_RECV;
	msg.pipe_desc = pipe_desc_ptr;
	msg.pipe_tr = pipe_tr_ptr;
	_usb_msgq_send((int*) &msg);
	return status;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_bus_control
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function for USB bus control
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_bus_control
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] bus control */
    uint_8 bus_control
) 
{
	UNUSED(handle)
	UNUSED(bus_control)
	return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_get_frame_number
 *  Returned Value : frame number
 *  Comments       :
 *        The function to get frame number
 *END*-----------------------------------------------------------------*/
uint_32 _usb_khci_get_frame_number
(
/* [IN] the USB Host state structure */
    _usb_host_handle handle
) 
{
	UNUSED(handle)
	return (uint_32) (FRM_NUMH << 8 | FRM_NUML);
}
/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_attach
 *  Returned Value : none
 *  Comments       :
 *        KHCI attach event
 *END*-----------------------------------------------------------------*/
static void _usb_khci_attach(void)
{
	/* device attached */
	ADDR = 0;
#ifdef OTG_BUILD
	time_delay(1);
#else
	time_delay(100);
#endif

	/* Speed check, set */
	usb_host_state_struct_ptr->speed
			= (uint_8) ((CTL & (0x80)) ? USB_SPEED_FULL : USB_SPEED_LOW);
	if (usb_host_state_struct_ptr->speed == USB_SPEED_FULL)
	{
		/* Clear low speed bit */
		ADDR &= ~ADDR_LS_EN_MASK;
	}
	INT_STAT = 0xff; /* clean each int flags */
	INT_ENB = INT_ENB_TOK_DNE_EN_MASK | INT_ENB_USB_RST_EN_MASK;

	/* Bus reset */
	CTL |= CTL_RESET_MASK;
	time_delay(100);
	/* End reset */
	CTL &= ~CTL_RESET_MASK;

	/* Enable SOF sending */
	CTL |= CTL_USB_EN_SOF_EN_MASK;
	time_delay(100);

	INT_ENB = INT_ENB_TOK_DNE_EN_MASK | INT_ENB_USB_RST_EN_MASK;
	usb_dev_list_attach_device((pointer) usb_host_state_struct_ptr,
			(uint_8) (usb_host_state_struct_ptr->speed), 0, 0);
	_usb_event_clear(&khci_event, KHCI_EVENT_ATTACH);
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_reset
 *  Returned Value : none
 *  Comments       :
 *        KHCI reset event
 *END*-----------------------------------------------------------------*/
static void _usb_khci_reset(void)
{
	/* Clear attach flag */
	INT_STAT |= INT_STAT_ATTACH_MASK;

	/* Test the presence of USB devices */
	if (INT_STAT & INT_STAT_ATTACH_MASK)
	{
		/* Device attached, normal reset was performed */
		ADDR = 0;
		ENDPT0 |= ENDPT0_HOST_WO_HUB_MASK;
	}
	else
	{
		_usb_event_set(&khci_event, KHCI_EVENT_DETACH);
	}
	_usb_event_clear(&khci_event, KHCI_EVENT_RESET | KHCI_EVENT_TOK_DONE);
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_detach
 *  Returned Value : none
 *  Comments       :
 *        KHCI detach event
 *END*-----------------------------------------------------------------*/
static void _usb_khci_detach(void)
{
	/* Device detached, notify detach */
	usb_dev_list_detach_device((pointer) usb_host_state_struct_ptr, 0, 0);
	/* Cleaning interrupt transaction queue from device is done
	 ** by calling _usb_khci_host_close_pipe from upper layer
	 */

	/* Disable bus control for any events, disable SOFs,
	 ** prepare for attach in host mode. 
	 */
	CTL = CTL_HOST_MODE_EN_MASK;
	/* Clear all pending interrupts */
	INT_STAT = 0xFF;
	/* Enable interrupt for usb attach */
	INT_ENB = INT_ENB_ATTACH_EN_MASK;

	_usb_event_clear(&khci_event, KHCI_EVENT_DETACH);
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_task
 *  Returned Value : none
 *  Comments       :
 *        KHCI task
 *END*-----------------------------------------------------------------*/
void _usb_khci_task(void)
{
	static uint_32 seq_ints = 10;
	static uint_32 wait_on = 0;
	static TR_MSG_STRUCT msg;
	static uint_32 remain = 0;
	static int_32 res;
	static uint_8 *buf;

	if (usb_host_state_struct_ptr->DEVICE_LIST_PTR)
	{
		msg.type = TR_MSG_UNKNOWN;
		/* look for interrupt transaction */
		if ((_usb_khci_get_hot_int_tr(&msg) != 0) || (!seq_ints--))
		{
			seq_ints = 10;
			if (_usb_msgq_receive((int *) &msg) == USB_MSGQ_OK)
				if (msg.pipe_desc->PIPETYPE == USB_INTERRUPT_PIPE)
					_usb_khci_add_int_tr(&msg, msg.pipe_desc->INTERVAL);
		}
		if (msg.type != TR_MSG_UNKNOWN)
		{
			/* evaluate message */
			switch (msg.type)
			{
			case TR_MSG_SETUP:
                    _usb_khci_atom_tr(TR_CTRL, usb_host_state_struct_ptr->speed, msg.pipe_desc, (void*)&msg.pipe_tr->setup_packet, 8);
				/* send next token */
				if (msg.pipe_tr->RX_LENGTH)
				{
					buf = msg.pipe_tr->RX_BUFFER;
					remain = msg.pipe_tr->RX_LENGTH;
                        while (remain > 0) {
                            res = _usb_khci_atom_tr(TR_IN, usb_host_state_struct_ptr->speed, msg.pipe_desc, buf, (uint_16)remain); 
						if (res < 0)
							break;
						buf += res;
						remain -= res;
					}
					msg.pipe_desc->NEXTDATA01 = 1;
                        res = _usb_khci_atom_tr(TR_OUT, usb_host_state_struct_ptr->speed, msg.pipe_desc, 0, 0);
				}
				else if (msg.pipe_tr->TX_LENGTH)
				{
					buf = msg.pipe_tr->TX_BUFFER;
					remain = msg.pipe_tr->TX_LENGTH;
					while (remain > 0)
					{
                            res = _usb_khci_atom_tr(TR_OUT, usb_host_state_struct_ptr->speed, msg.pipe_desc, buf, (uint_16)remain);
						if (res < 0)
							break;
						buf += res;
						remain -= res;
					}
					msg.pipe_desc->NEXTDATA01 = 1;
                        res = _usb_khci_atom_tr(TR_IN, usb_host_state_struct_ptr->speed, msg.pipe_desc, 0, 0);
				}
				else
				{
					msg.pipe_desc->NEXTDATA01 = 1;
                        res = _usb_khci_atom_tr(TR_IN, usb_host_state_struct_ptr->speed, msg.pipe_desc, 0, 0);
					remain = 0;
				}
				break;

			case TR_MSG_RECV:
				buf = msg.pipe_tr->RX_BUFFER;
				remain = msg.pipe_tr->RX_LENGTH;
                    do {
                        res = _usb_khci_atom_tr(TR_IN, usb_host_state_struct_ptr->speed, msg.pipe_desc, buf, (uint_16)remain);
					if (res < 0)
						break;
					buf += res;
					remain -= res;
					if ((remain == 0) || (res < msg.pipe_desc->MAX_PACKET_SIZE))
					{
						res = (int_32) remain;
						break;
					}
				} while (1);
				break;
			case TR_MSG_SEND:
				buf = msg.pipe_tr->TX_BUFFER;
				remain = msg.pipe_tr->TX_LENGTH;
                    do {
                        res = _usb_khci_atom_tr(TR_OUT, usb_host_state_struct_ptr->speed, msg.pipe_desc, buf, (uint_16)remain);
					if (res < 0)
						break;
					buf += res;
					remain -= res;
					if ((remain == 0) || (res < msg.pipe_desc->MAX_PACKET_SIZE))
					{
						res = (int_32) remain;
						break;
					}
				} while (1);
				break;
			default:
				break;
			}
			
            if (msg.pipe_desc->PIPETYPE == USB_INTERRUPT_PIPE)
            {
                if ((res >= 0) || (res != KHCI_ATOM_TR_NAK))
                {
                    _usb_khci_process_tr_complete((pointer)usb_host_state_struct_ptr, msg.pipe_desc, msg.pipe_tr, remain, res);
                    _usb_khci_rm_int_tr(&msg);
                }
            }
            else
            {
                _usb_khci_process_tr_complete((pointer)usb_host_state_struct_ptr, msg.pipe_desc, msg.pipe_tr, remain, res);
            }			
		}
	}
	if ((khci_event.VALUE & KHCI_EVENT_MASK))
	{
		if (khci_event.VALUE & KHCI_EVENT_ATTACH)
			_usb_khci_attach();

		if (khci_event.VALUE & KHCI_EVENT_RESET)
			_usb_khci_reset();

		if (khci_event.VALUE & KHCI_EVENT_DETACH)
			_usb_khci_detach();
	}

	/* todo AI: transaction complete */

	return;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_send_setup
 *  Returned Value :  
 *  Comments       : Send setup packet  
 *        
 *END*------------------------------------------------------------------*/
USB_STATUS _usb_khci_send_setup
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] pipe descriptor pointer */
PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr,
/* [IN] pipe transfer pointer */
    PIPE_TR_STRUCT_PTR pipe_tr_ptr
)
{
	USB_STATUS status = USB_OK;
	TR_MSG_STRUCT msg;

	UNUSED(handle)

	msg.type = TR_MSG_SETUP;
	msg.pipe_desc = pipe_desc_ptr;
	msg.pipe_tr = pipe_tr_ptr;
	status = _usb_msgq_send((int*) &msg);
	return status;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : USB_ISR
 *  Returned Value :  
 *  Comments       : Service interrupt in usb hardware. 
 *        
 *END*------------------------------------------------------------------*/
#ifndef OTG_BUILD
void interrupt VectorNumber_Vusb USB_ISR_HOST(void)
#else
void USB_ISR_HOST(void)
#endif
{
	uchar status;
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
	if(usb_int_disable)
	{
		usb_int_en_copy = INT_ENB;
		INT_ENB = 0;
		return;
	}
#endif 
	while (1)
	{
		status = (uint_8)(INT_STAT & INT_ENB);
		if (!status)
		break;
		INT_STAT = status;
		if (status & INT_STAT_ATTACH_MASK)
		{
			/* usb device attached */
			INT_ENB &= ~INT_ENB_ATTACH_EN_MASK;
			_usb_event_set(&khci_event, KHCI_EVENT_ATTACH);
		}
		if (status & INT_STAT_TOK_DNE_MASK)
		{
			/* atom transaction done - token done */
			_usb_event_set(&khci_event, KHCI_EVENT_TOK_DONE);
		}
		if (status & INT_STAT_USB_RST_MASK)
		{
			/* usb reset */
			_usb_event_set(&khci_event, KHCI_EVENT_RESET);
		}
	};
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_host_open_pipe
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function to open pipe
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_host_open_pipe
(
/* [IN] the USB Host state structure */
_usb_host_handle handle,
/* [IN] pipe descriptor pointer */
    PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr
) 
{
	uint_32 *ep = ((uint_32 *) &ENDPT0) + pipe_desc_ptr->ENDPOINT_NUMBER;

	UNUSED(handle)

    switch (pipe_desc_ptr->PIPETYPE) {
	case USB_CONTROL_PIPE:
		*(uint_8*) ep |= ENDPT0_EP_TX_EN_MASK | ENDPT0_EP_RX_EN_MASK;
		pipe_desc_ptr->ep_ptr = ep;
		break;
	case USB_BULK_PIPE:
		break;
	case USB_INTERRUPT_PIPE:
		*(uint_8*) ep = ENDPT0_EP_RX_EN_MASK;
		pipe_desc_ptr->ep_ptr = ep;
		break;
	case USB_ISOCHRONOUS_PIPE:
		break;
	default:
		return USBERR_OPEN_PIPE_FAILED;
	}
	return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_host_close_pipe
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        The function to close pipe
 *END*-----------------------------------------------------------------*/
USB_STATUS _usb_khci_host_close_pipe
(
/* [IN] the USB Host state structure */
_usb_host_handle,
/* [IN] pipe descriptor pointer */
    PIPE_DESCRIPTOR_STRUCT_PTR pipe_desc_ptr
) 
{
	if (pipe_desc_ptr->PIPETYPE == USB_INTERRUPT_PIPE)
	{
		uint_16 i;
		TR_INT_QUE_ITM_STRUCT_PTR tr = TR_INT_QUE;
		/* find record */
		for (i = 0; i < USBCFG_KHCI_MAX_INT_TR; i++, tr++)
		{
			if (tr->msg.pipe_desc == pipe_desc_ptr)
				tr->msg.type = TR_MSG_UNKNOWN;
		}
	}
	return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_get_hot_int_tr
 *  Returned Value : 0 successful
 *  Comments       :
 *        Make a message copy for transaction which need evaluation
 *END*-----------------------------------------------------------------*/
static int_32 _usb_khci_get_hot_int_tr
(
/* [IN] pointer to message */
    TR_MSG_STRUCT *msg
) 
{
	int_32 i, res = -1;
	TR_INT_QUE_ITM_STRUCT_PTR tr = TR_INT_QUE;
	TR_INT_QUE_ITM_STRUCT_PTR hot_tr = NULL;
	/* find hottest transaction */
	for (i = 0; i < USBCFG_KHCI_MAX_INT_TR; i++, tr++)
	{
		if (tr->msg.type != TR_MSG_UNKNOWN)
		{
			hot_tr = tr;
		}
	}
	if (hot_tr)
	{
		/* test if hottest transaction was not the last one with timeout 
		 - if yes, don't allow to block USB transfers with timeouts */
		if (last_to_pipe == hot_tr->msg.pipe_desc)
		{
			last_to_pipe = NULL; /* it is allowed to perform this interupt next time */
			return res;
		}
		memcpy(msg, &hot_tr->msg, sizeof(TR_MSG_STRUCT));
		res = 0;
	}
	return res;
}

