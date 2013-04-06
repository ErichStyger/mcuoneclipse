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
 * @file usb_dciapi.h
 *
 * @author 
 *
 * @version 
 *
 * @date Jun-05-2009
 *
 * @brief The file contains DCI api function definetions .
 *
 *****************************************************************************/

#ifndef _USB_DCIAPI_H
#define _USB_DCIAPI_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_devapi.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define MAX_SUPPORTED_ENDPOINTS (USB_SERVICE_MAX_EP + 1)
                                           /* Maximum endpoints supported */
#define MIN_SUPPORTED_ENDPOINTS (1)        /* Minimum endpoints supported */
#define DOUBLE_BUFFERED_ENPOINT_NUMBER (0) /* First double buffered endpoint */

/******************************************************************************
 * Types - None
 *****************************************************************************/
 
 /*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_DCI_Init(
    uint_8    controller_ID,
    uint_8    bVregEn
);

extern uint_8 USB_DCI_DeInit(void);

extern uint_8 USB_DCI_Init_EndPoint(
    uint_8              controller_ID, 
    USB_EP_STRUCT_PTR   ep_ptr,        
    boolean             double_buffered
);

extern uint_8 USB_DCI_Init_EndPoint(
    uint_8               controller_ID,            
    USB_EP_STRUCT_PTR    ep_ptr,       
    boolean              flag          
);

extern uint_8 USB_DCI_Cancel_Transfer(
    uint_8    controller_ID,   
    uint_8    ep_num,          
    uint_8    direction        
);
   
extern uint_8 USB_DCI_Deinit_EndPoint(
    uint_8    controller_ID,  
    uint_8    ep_num,         
    uint_8    direction       
);

extern void USB_DCI_Stall_EndPoint(
    uint_8    controller_ID, 
    uint_8    ep_num,        
    uint_8    direction      
);

extern void USB_DCI_Unstall_EndPoint(
    uint_8    controller_ID, 
    uint_8    ep_num,        
    uint_8    direction      
);

extern void USB_DCI_Get_Setup_Data( 
    uint_8       controller_ID, 
    uint_8       ep_num,        
    uchar_ptr    buff_ptr       
);

extern uint_8 USB_DCI_Get_Transfer_Status(
    uint_8    controller_ID, 
    uint_8    ep_num,        
    uint_8    direction      
);

extern void USB_DCI_Clear_DATA0_Endpoint(
	uint_8		controller_ID,
	uint_8		ep_num,
	uint_8		direction
);

extern uint_8 USB_DCI_Recv_Data(
    uint_8           controller_ID, 
    uint_8           ep_num,        
    uchar_ptr        buff_ptr,      
    USB_PACKET_SIZE  size           
);

extern uint_8 USB_DCI_Send_Data(
    uint_8           controller_ID, 
    uint_8           ep_num,        
    uchar_ptr        buff_ptr,      
    USB_PACKET_SIZE  size           
);

extern void  USB_DCI_Set_Address(
    uint_8    controller_ID,
    uint_8    address       
);

extern void USB_DCI_Shutdown(
    uint_8    controller_ID 
);

extern void USB_DCI_Assert_Resume(
    uint_8    controller_ID 
);

extern void Clear_Mem(uint_8* start_addr,uint_32 count, uint_8 val);

#define USB_DCI_Cancel_Transfer _usb_device_cancel_transfer  

#define USB_DCI_Recv_Data _usb_device_recv_data  

#define USB_DCI_Send_Data _usb_device_send_data    

#define USB_DCI_Shutdown _usb_device_shutdown  

#define USB_DCI_Stall_EndPoint _usb_device_stall_endpoint  

#define USB_DCI_Unstall_EndPoint _usb_device_unstall_endpoint  

#define USB_DCI_Get_Transfer_Status _usb_device_get_transfer_status

#define USB_DCI_Clear_DATA0_Endpoint _usb_device_clear_data0_endpoint

#define USB_DCI_Get_Setup_Data _usb_device_read_setup_data 

#define USB_DCI_Set_Address _usb_device_set_address  

#define USB_DCI_Assert_Resume _usb_device_assert_resume  

#endif


