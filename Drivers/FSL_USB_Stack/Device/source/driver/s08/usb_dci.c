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
 * @file usb_dci.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains S08 USB stack controller layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>
#include "usb_dciapi.h" /* USB DCI API Header File */
#include "usb_devapi.h" /* USB Device API Header File */
#include "usb_dci.h"    /* USB DCI Header File */
#include "usb_bdt.h"    /* USB BDT Structure Header File */
#include "USB_Config.h" /* USB Configuration Parameters Header File */

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
const uint_8 g_EP_sizes[16] =
{
    USB_EP0_SIZE,
    USB_EP1_SIZE,
    USB_EP2_SIZE,
    USB_EP3_SIZE,
    USB_EP4_SIZE,
    USB_EP5_SIZE,
    USB_EP6_SIZE,
    USB_EP7_SIZE,
    USB_EP8_SIZE,
    USB_EP9_SIZE,
    USB_EP10_SIZE,
    USB_EP11_SIZE,
    USB_EP12_SIZE,
    USB_EP13_SIZE,
    USB_EP14_SIZE,
    USB_EP15_SIZE,
};

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* Pointer to BDT Map Structure */
static BDTMAP * const g_bdtmap = (BDTMAP *)USB_RAM_BASE_ADDRESS;

static BDT_ELEM g_bdt_elem[MAX_BDT_INDEX];       /* per bdt index struc */
static uint_8 g_dci_controller_Id;               /* stores Controller ID */
static uint_8 g_bdt_address = EP_START_BUFFER_ADDR;/* Start BDT buffer Address */
static uint_8 g_trf_direction = USB_TRF_UNKNOWN;   /* Transfer direction */
volatile uint_8 gu8ProcessPendingFlag = 0;
volatile T_EP_BITFIELD gtUSBEPEventFlags = 0;

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/
/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void Clear_Mem(uint_8* startAdr, uint_8 count, uint_8 val);

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_Bus_Reset_Handler(void);
static void USB_DCI_Write_BDT(uint_8 index, uint_8 stat, BDT_ELEM* elem);
static uint_8 USB_DCI_Get_BDT_Index(uint_8 ep_num, uint_8 direction);

#ifdef LONG_SEND_TRANSACTION
static void USB_DCI_Prepare_Send_Data(P_BUFF_DSC buffer_dsc,
                               P_BDT_ELEM bdt_elem, uint_8_ptr addr);
#endif

static void USB_Bus_Token_Cpl_Handler (uint_8 stat, USB_DEV_EVENT_STRUCT* event);
#ifdef USB_LOWPOWERMODE
static void Enter_StopMode(STOP_MODE stop_mode);
#endif
/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/
static volatile T_EP_BITFIELD gtUSBEPDirFlags = 0;   
static volatile T_EP_BITFIELD gtUSBEPOddEvenFlags = 0;
static volatile uint_8 gu8ErrorFlags = 0;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
#if 0 /* << EST */
#if (defined(_MC9S08MM128_H) || defined(_MC9S08JE128_H))
#pragma CODE_SEG DEFAULT
#endif
#else
/* device is %CPUDevice << EST */
%if (CPUDevice="MC9S08MM128") | (CPUDevice="MC9S08JE128")
#pragma CODE_SEG DEFAULT
%endif
#endif
/**************************************************************************//*!
 *
 * @name  USB_DCI_Write_BDT
 *
 * @brief The function writes Buffer Descriptor to a BDT Index
 *
 * @param index     : BDT index
 * @param stat      : BDT stat byte
 * @param elem      : pointer to BDT_ELEM
 *
 * @return None
 *
 ******************************************************************************
 * This function writes BD to the USB Buffer Descriptor Table for a specified
 * index
 *****************************************************************************/
static void USB_DCI_Write_BDT (
    uint_8 index,           /* [IN] BDT Index */
    uint_8 stat,            /* [IN] BDT stat byte */
    BDT_ELEM* elem          /* [IN] pointer to BDT_ELEM */
)
{
    g_bdtmap->ep_dsc[index].Stat._byte = stat;
    g_bdtmap->ep_dsc[index].cnt = (uint_8)elem->len;
    g_bdtmap->ep_dsc[index].addr = elem->addr;
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_Bus_Reset_Handler
 *
 * @brief The function handles Bus Reset Interrupt
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************
 * This functions is called when USB Bus Reset event is received on USB Bus.
 * This function clears all the errors conditions and reinit Global data
 * structures. Also resets USB device controller.
 *****************************************************************************/
static void USB_Bus_Reset_Handler(void)
{

    ERRSTAT = ERRSTAT_CLEAR_ALL;    /* clear USB error flag     */
    INTSTAT = INTSTAT_USBRSTF_MASK; /* clear USB Bus Reset Flag */
    CTL_ODDRST = 1;                /* Reset to Even buffer */
    ADDR = 0;                       /* reset to default address */
    
    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)&(g_bdt_elem),
        (uint_8)(sizeof(BDT_ELEM) * MAX_BDT_INDEX), (uint_8)UNINITIALISED_VAL);

    /* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap, sizeof(BDTMAP), (uint_8)NULL);
    /* initialize variables */
    g_bdt_address = EP_START_BUFFER_ADDR;
    g_trf_direction = USB_TRF_UNKNOWN;

	CTL_ODDRST = 0;						/* Clear ODD Reset Flag 				*/
    CTL = CTL_RESET_VAL;            	/* reset CTL Register       			*/
    USBCTL0 = UCFG_VAL | _USBREGEN;     /* Attach JM60 to USB bus   			*/
    ERRENB = ERRENB_ENABLE_ALL;     	/* Enable All Error Interrupts         	*/
    INTENB = INTENB_BUS_RESET_VAL;  	/* Enable All Interrupts except RESUME 	*/
    CTL_USBEN = 1;                  	/* Enable module            			*/
    CTL_TSUSPEND = 0;
    
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Get_BDT_Index
 *
 * @brief The function maps endpoint number and direction to bdt index
 *
 * @param  ep_num    : Endpoint Number
 * @param  direction : Endpoint direction
 *
 * @return bdt index         : mapped bdt index
 *         INVALID_BDT_INDEX : incase of error
 *
 ******************************************************************************
 * This function returns BDT Index from Endpoint number and direction
 *****************************************************************************/
static uint_8 USB_DCI_Get_BDT_Index (
    uint_8 ep_num,          /* [IN] Endpoint Number */
    uint_8 direction        /* [IN] Endpoint direction */
)
{
    uint_8 bdt_index = 0;

    if(ep_num == CONTROL_ENDPOINT)
    {
        if(direction == USB_RECV)
        {   
            /*for Control endpoint RECV BDT index is 1 */
            bdt_index = 1;
        }
    }
    else if(ep_num < MAX_SUPPORTED_ENDPOINTS)
    {   
        /* Non double buffered index are one more than the endpoint number */
        bdt_index = (uint_8)(ep_num + 1);

        #ifdef DOUBLE_BUFFERING_USED
        if(ep_num == SECOND_DOUBLE_BUFFERED_EP_NUM)
        {
            /* 
               adjust bdt_index for second double buffer EP
               bdt_index is (ep_num+2) 
            */
            bdt_index += 1;
        }
        #endif
    }
    else
    {
        return INVALID_BDT_INDEX;
    }

    return bdt_index;

}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Validate_Param
 *
 * @brief This function validates endpoint number & direction parameters
 *        and returns bdt index.
 *
 * @param  ep_num    : Endpoint Number
 * @param  direction : Endpoint direction
 *
 * @return bdt index         : mapped bdt index
 *         INVALID_BDT_INDEX : incase of error
 *
 ******************************************************************************
 * This function validates endpoint number & direction parameters and returns
 * bdt index
 *****************************************************************************/
uint_8 USB_DCI_Validate_Param (
    uint_8 ep_num,          /* [IN] Endpoint Number */
    uint_8 direction        /* [IN] Endpoint direction */
)
{
    /* Get bdt index mapped to endpoint number-direction */
    uint_8 bdt_index = USB_DCI_Get_BDT_Index(ep_num,direction);


    if((bdt_index != INVALID_BDT_INDEX) &&
       (g_bdt_elem[bdt_index].len == (uint_8)UNINITIALISED_VAL))
    {   
        /* Inase len in bdt_elem is unitialised return invalid index */
        bdt_index = INVALID_BDT_INDEX;
    }

    return bdt_index;

}

#ifdef LONG_SEND_TRANSACTION
/**************************************************************************//*!
 *
 * @name  USB_DCI_Prepare_Send_Data
 *
 * @brief The function sets up the BDT for Send
 *
 * @param  buffer_dsc    : pointer to buffer descriptor element in USB_RAM
 * @param  bdt_elem      : pointer to per endpoint/direction structure
 * @param  addr          : address in bdt from where the data is written from
 *
 * @return None
 *
 ******************************************************************************
 * This functions copies application data to USB RAM buffer. Application Data
 * is copied from the current offset. Amount of data copied to USB RAM Buffer
 * is limited to the size of USB RAM Buffer.
 *****************************************************************************/
static void USB_DCI_Prepare_Send_Data (
    P_BUFF_DSC buffer_dsc,  /* [OUT] pointer to buffer descriptor element in
                                USB_RAM */
    P_BDT_ELEM bdt_elem,    /* [IN] pointer to per endpoint/direction
                                structure */
    uint_8_ptr addr         /* [OUT] address in bdt from where the data is
                                written from */
)
{

    uint_8_ptr buff_ptr = bdt_elem->app_buffer + bdt_elem->curr_offset;

    /* adjust size based on the input at the init endpoint */
    if((bdt_elem->app_len - bdt_elem->curr_offset) > bdt_elem->len)
    {
        buffer_dsc->cnt = bdt_elem->len;
    }
    else
    {
        buffer_dsc->cnt = (uint_8)(bdt_elem->app_len - bdt_elem->curr_offset);
    }

    /* loop and copy from application buffer to USB RAM  */
    (void)memcpy(addr, buff_ptr, buffer_dsc->cnt);
}
#endif

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_DCI_Init
 *
 * @brief The function initializes the Controller layer
 *
 * @param controller_ID: Controller ID
 *
 * @return USB_OK    : Always
 ******************************************************************************
 *
 *****************************************************************************/
uint_8 USB_DCI_Init (
    uint_8    controller_ID,	/* [IN] Controller ID */
    uint_8    bVregEn			/* Enables or disables internal regulator */
)
{

    /* save the controller_ID for future use*/
    g_dci_controller_Id = controller_ID;

    USBCTL0 = USB_RST;                    /* Reset the Controller */
    while(USBCTL0_USBRESET == 1)          /* loop till the Reset bit clears  */
    {
        __RESET_WATCHDOG();
    }

    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)&(g_bdt_elem),
        (uint_8)(sizeof(BDT_ELEM) * MAX_BDT_INDEX), (uint_8)UNINITIALISED_VAL);
    /* Write the bdt */
    g_bdt_address = EP_START_BUFFER_ADDR;
    g_trf_direction = USB_TRF_UNKNOWN;

    CTL = CTL_RESET_VAL;

    INTSTAT = INTSTAT_CLEAR_ALL;        /* clear USB interrupt*/
    INTENB = INTENB_DISABLE_ALL_VAL;    /* disable USB interrupt*/

    if(bVregEn == FALSE)
    {
        USBCTL0 = UCFG_VAL;                 /* attach JM60 to USB bus*/
    }
    else
    {
        USBCTL0 = UCFG_VAL | _USBREGEN;     /* attach JM60 to USB bus*/
    }

    CTL_USBEN = 1;                      /* Enable module */

    INTENB_USBRST = 1;                  /* Enable USB RESET Interrupt */    
    INTENB_SLEEP = 1;                   /* Enable USB Sleep Interrupt */

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_DeInit
 *
 * @brief The function de-initializes the Controller layer
 *
 * @param controller_ID : Controller ID
 *
 * @return status
 *         USB_OK    : Always
 ******************************************************************************
 * Initializes the USB controller
 *****************************************************************************/
uint_8 USB_DCI_DeInit(void)
{
   /* Clear USB interrupts*/ 
   INTSTAT = INTSTAT_CLEAR_ALL; 
	 
   /* Disable USB interrupt*/
   INTENB = INTENB_DISABLE_ALL_VAL; 
   
   /* Detach JM60 to USB bus*/
   USBCTL0 = ~(UCFG_VAL | _USBREGEN);                
	                
   /* Disable USB RESET Interrupt */
   INTENB_USBRST = 0;
	 
   /* Disable USB module */ 
   CTL_USBEN = 0; 
   
   /* Disable USB interrupt*/
   INTENB = INTENB_DISABLE_ALL_VAL;    
           
   return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Init_EndPoint
 *
 * @brief The function initializes an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_ptr        : Pointer to EndPoint Structure
 * @param flag          : Zero Termination Flag
 *
 * @return status
 *         USB_OK                    : When Successfull
 *         USBERR_EP_INIT_FAILED     : When Error
 ******************************************************************************
 *
 * This function initializes an endpoint and the Bufffer Descriptor Table
 * entry associated with it. Incase the input parameters are invalid it will
 * return USBERR_EP_INIT_FAILED error.
 *
 *****************************************************************************/
uint_8 USB_DCI_Init_EndPoint (
    uint_8               controller_ID,/* [IN] Controller ID */
    USB_EP_STRUCT_PTR    ep_ptr,       /* [IN] Pointer to EndPoint Structure */
    boolean              flag          /* [IN] Zero Termination */
)
{
    uint_8 bdtelem_index = 0,ep_num = ep_ptr->ep_num;
    uint_8 direction = ep_ptr->direction;
    uint_8 stat[2] = {_SIE | _DATA0 | _DTS, _CPU | _DATA1};
    uint_8 ep_ctrl[2] = {EP_OUT, EP_IN};
    uint_8 addr = g_bdt_address;
    UNUSED (controller_ID)
#ifdef DOUBLE_BUFFERING_USED
    if(DOUBLE_BUFFER_EP(ep_num))
    {
        stat[0] = _SIE | _DATA0; /* for even recv buffer */
        stat[1] = _CPU | _DATA0; /* for even send buffer */
    }
#endif
    /* if the max packet size is greater than
       the max buffer size so */
    if(ep_ptr->size > MAX_EP_BUFFER_SIZE)
    {
      ep_ptr->size = MAX_EP_BUFFER_SIZE;
    }

    /* update the buffer address for the next endpoint */
    g_bdt_address += (ep_ptr->size >> BDT_OFFSET_SHIFT) * 
        BDT_MIN_BUFFER_ADDR_INC;
    if(ep_ptr->size %% BDT_MIN_BUFFER_SIZE)
    {
        g_bdt_address += BDT_MIN_BUFFER_ADDR_INC;
    }

    /* Get the bdt index correspoding to the endpoint */
    bdtelem_index = USB_DCI_Get_BDT_Index(ep_num, direction);

    /* incase the bdt_index is invalid
      or already initialised return with an error*/
    if((bdtelem_index  == INVALID_BDT_INDEX) ||
      (g_bdt_elem[bdtelem_index].len != (uint_8)UNINITIALISED_VAL) ||
      (g_bdt_address >= MAX_USB_RAM_BUFFER_INDEX * BDT_MIN_BUFFER_ADDR_INC) ||
       (ep_ptr->type > USB_INTERRUPT_PIPE) ||
       (ep_ptr->direction > USB_SEND))
    {
        /* reassign g_bdt_index back to value before increment */
        g_bdt_address = addr;
        return USBERR_EP_INIT_FAILED;
    }

    /* Reset Handler resets bdtmap_index to UNINITIALISED_VAL */
    if(g_bdt_elem[bdtelem_index].bdtmap_index == (uint_8)UNINITIALISED_VAL) 
    {
        g_bdt_elem[bdtelem_index].bdtmap_index = 0;  
    }          
    g_bdt_elem[bdtelem_index].bdtmap_index |= bdtelem_index;
    
    g_bdt_elem[bdtelem_index].len = (uint_8)ep_ptr->size;
    g_bdt_elem[bdtelem_index].addr = addr;
    g_bdt_elem[bdtelem_index].flag = flag;
    
#ifdef LONG_TRANSACTION
    g_bdt_elem[bdtelem_index].app_buffer = NULL;
    g_bdt_elem[bdtelem_index].app_len = UNINITIALISED_VAL;
    g_bdt_elem[bdtelem_index].curr_offset = 0;
#endif

    /* Write the bdt */
    USB_DCI_Write_BDT(g_bdt_elem[bdtelem_index].bdtmap_index, stat[direction], 
        &g_bdt_elem[bdtelem_index]);

    /* initialize the other buffer for double buffer endpoint */
#ifdef DOUBLE_BUFFERING_USED
    if(DOUBLE_BUFFER_EP(ep_num))
    {
        stat[0] = _CPU | _DATA1; /* for odd recv buffer */
        stat[1] = _CPU | _DATA1; /* for odd send buffer */
        addr= g_bdt_address;

        /* update the buffer address for the next endpoint */
        g_bdt_address += (ep_ptr->size >> BDT_OFFSET_SHIFT)*
            BDT_MIN_BUFFER_ADDR_INC;
        if(ep_ptr->size %% BDT_MIN_BUFFER_SIZE)
        {
            g_bdt_address += BDT_MIN_BUFFER_ADDR_INC;
        }
        g_bdt_elem[bdtelem_index].addr = addr;

        /* Write the bdt for odd buffer */
        USB_DCI_Write_BDT((g_bdt_elem[bdtelem_index].bdtmap_index ^ 1),stat[direction],
            &g_bdt_elem[bdtelem_index]);            
    }
#endif
    /* enable handshake for Non-Isochronous Endpoints */
    ep_ctrl[direction] |= ((ep_ptr->type != USB_ISOCHRONOUS_PIPE) ?
        HSHK_EN : 0x00);
    /* set the EndPoint Control MCU Register*/
    *(((uint_8*)&EPCTL0) + ep_num) |= ep_ctrl[direction];

    return USB_OK;

}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Cancel_Transfer
 *
 * @brief The function cancels any pending Transfers which has not been sent
 *
 * @param handle           : USB Device handle
 * @param endpoint_number  : endpoint number
 * @param direction        : direction
 *
 * @return status
 *          USB_OK                  : When Successfull
 *          USBERR_UNKNOWN_ERROR    : When incorrect endpoint number
 *                                    and direction is supplied
 *          USBERR_NOT_SUPPORTED    : Always
 ******************************************************************************
 * This function just returns Error Code not supported
 *****************************************************************************/
uint_8 USB_DCI_Cancel_Transfer (
    _usb_device_handle   handle,             /* [IN] USB Device handle */
    uint_8               endpoint_number,    /* [IN] Endpoint number for the transfer */
    uint_8               direction           /* [IN] Direction of transfer */
)
{
#ifdef LONG_TRANSACTION
    uint_8 status= USBERR_UNKNOWN_ERROR;
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction);
#endif
    UNUSED (handle)
#ifdef LONG_TRANSACTION
    /* Check for valid bdt index */
    if(bdt_index != INVALID_BDT_INDEX)
    {
        P_BUFF_DSC buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];   
        buffer_dsc->Stat._byte &= ~_SIE; 
        g_bdt_elem[bdt_index].app_buffer = NULL;
        g_bdt_elem[bdt_index].app_len = UNINITIALISED_VAL;       

#ifdef DOUBLE_BUFFERING_USED  
        if(DOUBLE_BUFFER_EP(endpoint_number))
        {
            P_BUFF_DSC buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index ^ 1];        
            buffer_dsc_alt->Stat._byte &= ~_SIE; 
            g_bdt_elem[bdt_index ^ 1].app_buffer = NULL;
            g_bdt_elem[bdt_index ^ 1].app_len = UNINITIALISED_VAL;
    	}
#endif
        status = USB_OK;
    }

    return status;
#else
    return USBERR_NOT_SUPPORTED;
#endif
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Deinit_EndPoint
 *
 * @brief The function de-initializes an endpoint
 *
 * @param controller_ID: Controller ID
 * @param ep_num       : Endpoint number
 * @param direction    : direction
 *
 * @return status
 *         USB_OK                   : When successfull
 *         USBERR_EP_DEINIT_FAILED  : When unsuccessfull
 ******************************************************************************
 *
 * This function un intializes the endpoint by clearing the corresponding
 * endpoint control register and then clearing the bdt elem.
 *
 *****************************************************************************/
uint_8 USB_DCI_Deinit_EndPoint (
    uint_8    controller_ID,  /* [IN] Controller ID */
    uint_8    ep_num,         /* [IN] Endpoint number */
    uint_8    direction       /* [IN] Direction */
)
{
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (ep_num, direction);
    uint_8 subtract_size; 
    UNUSED (controller_ID)
    /* incase the bdt_index is invalid
      or already initialised return with an error*/
    if(bdt_index  == INVALID_BDT_INDEX)
    {
        return USBERR_EP_DEINIT_FAILED;
    }

    (void)USB_DCI_Cancel_Transfer(&controller_ID, ep_num, direction); 
    
    /* free the buffer address from this endpoint */
    subtract_size =  (g_bdt_elem[bdt_index].len >> 
        BDT_OFFSET_SHIFT) * BDT_MIN_BUFFER_ADDR_INC;
    if(g_bdt_elem[bdt_index].len %% BDT_MIN_BUFFER_SIZE)
    {
        subtract_size += BDT_MIN_BUFFER_ADDR_INC;
    }

#ifdef DOUBLE_BUFFERING_USED
    if(DOUBLE_BUFFER_EP(ep_num))
    {
        subtract_size *= 2;
	}
#endif

    g_bdt_address -= subtract_size;
    

    *(((uint_8*)&EPCTL0) + ep_num) = EP_DISABLE; /* disable endpoint */

    /* uninitialise the bdt_elem strucrure for this endpoint */
    g_bdt_elem[bdt_index].len = (uint_8)UNINITIALISED_VAL;

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Stall_EndPoint
 *
 * @brief The function stalls an endpoint
 *
 * @param handle           : USB Device handle
 * @param endpoint_number  : endpoint number
 * @param direction        : direction
 *
 * @return None
 *
 ******************************************************************************
 * This function stalls the endpoint by setting Endpoint Control Register
 * and BDT
 *****************************************************************************/
void USB_DCI_Stall_EndPoint (
    _usb_device_handle      handle,             /* [IN] USB Device handle */
    uint_8                  endpoint_number,    /* [IN] Endpoint number to stall */
    uint_8                  direction           /* [IN] Direction to stall */
)
{
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[bdt_index]; 
    UNUSED (handle)
    
    bdt_index = bdt_elem->bdtmap_index; 
    
    /* Check for valid bdt index */
    if(bdt_index != INVALID_BDT_INDEX)
    {
        (void)USB_DCI_Cancel_Transfer(handle, endpoint_number, direction);
        /* Stall endpoint */
        g_bdtmap->ep_dsc[bdt_index].Stat._byte = _SIE | _BDTSTALL;
        /* clear suspend condition */
        CTL_TSUSPEND = 0;
    }

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Unstall_EndPoint
 *
 * @brief The function unstalls an endpoint
 *
 * @param handle           : USB Device handle
 * @param endpoint_number  : Endpoint number
 * @param direction        : direction
 *
 * @return None
 *
 ******************************************************************************
 *
 * This function unstalls the endpoint by clearing Endpoint Control Register
 * and BDT
 *
 *****************************************************************************/
void USB_DCI_Unstall_EndPoint (
    _usb_device_handle  handle,             /* [IN] USB Device handle */
    uint_8              endpoint_number,    /* [IN] Endpoint number to unstall */
    uint_8              direction           /* [IN] Direction to unstall */
)
{
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[bdt_index]; 
    UNUSED (handle)

    bdt_index = bdt_elem->bdtmap_index; 

    /* Check for valid bdt index */
    if(bdt_index != INVALID_BDT_INDEX)
    {
        /* Write the bdt
        1. Set DATA PID to DATA0
        2. Enable Data Toggle Sequence
        3. Give Control to SIE for OUT Endpoints and CPU for IN Endpoints
        */

        if(endpoint_number != CONTROL_ENDPOINT)
        {
            if(direction == USB_SEND)
            {
                *(((uint_8*)&EPCTL0) + endpoint_number) = (HSHK_EN | EP_IN);
            }
            else
            {
                *(((uint_8*)&EPCTL0) + endpoint_number) = (HSHK_EN | EP_OUT);
            }
        }
	    /* Unstall endpoint by clearing stall bit in BDT  */
	    g_bdtmap->ep_dsc[bdt_index].Stat._byte &= ~(_SIE | _BDTSTALL); 
        /* We Require DATA0 PID to be zero on unstall for next transaction
           Therefore, below we are setting Data PID as _DATA1, because in our 
           implementation of send/recv it will get toggled*/
        g_bdtmap->ep_dsc[bdt_index].Stat._byte = _DATA1;  

#ifdef DOUBLE_BUFFERING_USED 
        if(DOUBLE_BUFFER_EP(endpoint_number))
        {                
            g_bdtmap->ep_dsc[bdt_index ^ 1].Stat._byte = _CPU | _DATA1 | _DTS;  
        }
#endif    

	    if(direction == USB_RECV)
	    {
	        /* Initiate Next receive Transfer */
	        (void)USB_DCI_Recv_Data(handle, endpoint_number, NULL, 0);   
	    } 	    

        /* clear suspend condition */
        CTL_TSUSPEND = 0;

    }

    return;

}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Get_Setup_Data
 *
 * @brief The function copies Setup Packet from USB RAM to application buffer
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : endpoint number
 * @param buffer_ptr      : application buffer pointer
 *
 * @return None
 *
 ******************************************************************************
 * Copies setup packet from USB RAM to Application Buffer
 *****************************************************************************/
void USB_DCI_Get_Setup_Data (
    _usb_device_handle  handle,             /* [IN] USB Device handle */
    uint_8              endpoint_number,    /* [IN] Endpoint number for the transaction */
    uchar_ptr           buffer_ptr          /* [OUT] Pointer to the buffer into which to read data */
)
{
    /* address correponding to the endpoint */
    uint_8_ptr addr = (uint_8_ptr)CAL_USB_RAM_ADDR(
        g_bdtmap->ep_dsc[endpoint_number + 1].addr);
    UNUSED (handle)

    /* copy bdt buffer to application buffer */
    (void)memcpy(buffer_ptr, addr, USB_SETUP_PKT_SIZE);

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Get_Transfer_Status
 *
 * @brief The function retrieves the Transfer status of an endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param direction       : direction
 *
 * @return status
 *         USB_STATUS_IDLE                 : No transfer on endpoint
 *         USB_STATUS_DISABLED             : endpoint is disabled
 *         USB_STATUS_STALLED              : endpoint is stalled
 *         USB_STATUS_TRANSFER_IN_PROGRESS : When SIE has control of BDT
 ******************************************************************************
 *
 * This function retrieves the transfer status of the endpoint by checking the
 * BDT as well as the endpoint control register
 *
 *****************************************************************************/
uint_8 USB_DCI_Get_Transfer_Status (
    _usb_device_handle  handle,             /* [IN] USB Device handle */
    uint_8              endpoint_number,    /* [IN] Endpoint number */
    uint_8              direction           /* [IN] direction */
)
{
    uint_8 status = USB_STATUS_DISABLED;
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param(endpoint_number, direction);
    UNUSED (handle)
    /* Check for valid bdt index */
    if(bdt_index != INVALID_BDT_INDEX)
    {
        uint_8 ep_control = *(((uint_8*)&EPCTL0) + endpoint_number);

        status = USB_STATUS_IDLE;

        /* Check for direction in endpoint control register */
        if((ep_control & (EP_IN | EP_OUT)) == EP_DISABLE)
        {
            status = USB_STATUS_DISABLED;
        }
        /* Check for stall bit in endpoint control register */
        else if ((ep_control &  EPCTL_STALL) == EPCTL_STALL)
        {
            status = USB_STATUS_STALLED;
        }
        /* Check whether SIE has control of BDT */
        else if (g_bdtmap->ep_dsc[bdt_index].Stat.SieCtlBit.own == 1)
        {
            status = USB_STATUS_TRANSFER_IN_PROGRESS;
        }
    }

    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Clear_DATA0_Endpoint
 *
 * @brief The function clear the DATA0/1 bit 
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param direction       : Endpoint direction
 *
 * @return None
 *
 ******************************************************************************
 * This function clear the DATA0/1 bit 
 *****************************************************************************/
void  USB_DCI_Clear_DATA0_Endpoint (
    _usb_device_handle    handle,    /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number */
    uint_8                direction           /* [IN] Endpoint direction */
)
{
	
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[bdt_index]; 
		
		UNUSED(handle);
	
	bdt_index = bdt_elem->bdtmap_index;
	
	/*Check for a valid bdt index */
	if (bdt_index != INVALID_BDT_INDEX)
	{
        /* We Require DATA0 PID to be zero on unstall for next transaction
           Therefore, below we are setting Data PID as _DATA1, because in our 
           implementation of send/recv it will get toggled*/
        g_bdtmap->ep_dsc[bdt_index].Stat._byte = _DATA1;  
	}
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Recv_Data
 *
 * @brief The function retrieves data received on RECV endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param buffer_ptr      : Buffer to receive data
 * @param size            : Length of the transfer
 *
 * @return status
 *         USB_OK                          : When successfull
 *         USBERR_RX_FAILED                : When unsuccessfull
 ******************************************************************************
 * This function retrieves data received data on a RECV endpoint by copying it
 * from USB RAM to application buffer
 *****************************************************************************/
uint_8 USB_DCI_Recv_Data (
    _usb_device_handle     handle,             /* [IN] USB Device handle */
    uint_8                 endpoint_number,    /* [IN] Endpoint number for the transaction */
    uint_8_ptr             buffer_ptr,         /* [OUT] Pointer to the buffer into which to receive data */
    uint_32                size                /* [IN] Number of bytes to receive */
)
{
    uint_8 status = USBERR_RX_FAILED;
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_RECV);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[bdt_index];
    UNUSED(handle)
    
#ifdef DOUBLE_BUFFERING_USED
    if(DOUBLE_BUFFER_EP(endpoint_number))
    {
        bdt_index = bdt_elem->bdtmap_index;/* For selecting even/odd buffer */
    }
#endif

    if(bdt_index != INVALID_BDT_INDEX)
    {
        P_BUFF_DSC buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];
        P_BUFF_DSC buffer_dsc_alt;
        
#ifdef DOUBLE_BUFFERING_USED
        if(DOUBLE_BUFFER_EP(endpoint_number))
        {
            /* fetch previous buffer_dsc */
            buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index ^ 1];
        }
        else
#endif
        {
            /* in absence of double buffering both buffer_dsc and buffer_dsc_alt are same */
            buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index];            
        }


        /* Check for valid bdt index */
        if(bdt_elem->len != (uint_8)UNINITIALISED_VAL)
        {
            /* Check MCU owns the endpoint BDT and it is not stalled */
            if (buffer_dsc->Stat.SieCtlBit.own == FALSE)
            {
                uint_8_ptr addr = (uint_8_ptr)CAL_USB_RAM_ADDR
                    (buffer_dsc_alt->addr);
                
                if(size == 0)
                {
#ifdef LONG_TRANSACTION
                    bdt_elem->app_len = 
                        (USB_PACKET_SIZE)UNINITIALISED_VAL;
                    bdt_elem->app_buffer = NULL;
#endif
                
                    /* Set the USB RAM buffer for next transaction */
                    buffer_dsc->cnt = bdt_elem->len;
    
                    buffer_dsc->Stat._byte = (uint_8)((
                        buffer_dsc_alt->Stat.McuCtlBit.data ? 
                        _DATA0 : _DATA1) | _SIE | _DTS);
                    return USB_OK;
                }
                
                #ifdef LONG_RECEIVE_TRANSACTION
                    /* Initialise transfer */
                    bdt_elem->app_len = (USB_PACKET_SIZE)size;
                    bdt_elem->app_buffer = buffer_ptr;
                #endif
                if(size > bdt_elem->len)
                {
                    size = bdt_elem->len;
                }
                #ifdef LONG_RECEIVE_TRANSACTION
                    bdt_elem->curr_offset = 0;
                #endif
                buffer_dsc->cnt = (uint_8)size;
                
                buffer_dsc->Stat._byte = (uint_8)((
                    buffer_dsc_alt->Stat.McuCtlBit.data ? _DATA0 : _DATA1)
                    | _SIE | _DTS);
                /* clear suspend condition */
                CTL_TSUSPEND = 0;
                status = USB_OK;
            }
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Send_Data
 *
 * @brief The function configures Controller to send data on SEND endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param buffer_ptr      : Buffer to send
 * @param size            : Length of the transfer
 *
 * @return status
 *         USB_OK                          : When successfull
 *         USBERR_TX_FAILED                : When unsuccessfull
 ******************************************************************************
 *
 * This function configures Controller to send data on an SEND endpoint by
 * copying data from application buffer to USB RAM and then setting the BDT to
 * send data.
 *
 *****************************************************************************/
uint_8 USB_DCI_Send_Data (
    _usb_device_handle  handle,             /* [IN] USB Device handle */
    uint_8              endpoint_number,    /* [IN] Endpoint number of the transaction */
    uint_8_ptr          buffer_ptr,         /* [IN] Pointer to the buffer to send */
    uint_32             size                /* [IN] Number of bytes to send */
)
{
    uint_8 status = USBERR_TX_FAILED;
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_SEND);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[bdt_index];
    UNUSED (handle)
#ifdef DOUBLE_BUFFERING_USED
    if(DOUBLE_BUFFER_EP(endpoint_number))
    {
       bdt_index = bdt_elem->bdtmap_index;/* For selecting even/odd buffer */
    }
#endif

    if(bdt_index != INVALID_BDT_INDEX)
    {
        /* Get BDT buffer addr for the endpoint */
        uint_8_ptr addr = NULL;
        P_BUFF_DSC buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];
        P_BUFF_DSC buffer_dsc_alt;
        
#ifdef DOUBLE_BUFFERING_USED
        if(DOUBLE_BUFFER_EP(endpoint_number))
        {
            /* fetch previous buffer_dsc */
            buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index ^ 1];
        }
        else
#endif
        {
            /* in absence of double buffering both buffer_dsc and buffer_dsc_alt are same */
            buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index];            
        }
        addr = (uint_8_ptr)CAL_USB_RAM_ADDR(buffer_dsc->addr);

        /* Does MCU owns it and it is not stalled */
        if(buffer_dsc->Stat.SieCtlBit.own == 0)
        {
#ifdef LONG_SEND_TRANSACTION
            /* Initialise transfer */
            bdt_elem->app_len = (USB_PACKET_SIZE)size;
            bdt_elem->app_buffer = buffer_ptr;
            bdt_elem->curr_offset = 0;

            /* prepare for send */
            USB_DCI_Prepare_Send_Data(buffer_dsc, bdt_elem, addr);
#else
            /* adjust size based on the input at the init endpoint */
            if((uint_8)size > bdt_elem->len)
            {
                buffer_dsc->cnt = bdt_elem->len;
            }
            else
            {
                buffer_dsc->cnt = (uint_8)size;
            }

            /* copy from application buffer to USB RAM  */
            (void)memcpy(addr, buff_ptr, buffer_dsc->cnt);
#endif

            if(endpoint_number != CONTROL_ENDPOINT)
            {
                /* Set the USB RAM buffer for next transaction */
                /* give the ownership to SIE */
                buffer_dsc->Stat._byte = (uint_8)
                    ((buffer_dsc_alt->Stat.McuCtlBit.data ?
                    _DATA0 : _DATA1) | _SIE | _DTS);
                status = USB_OK;
            }
            else /* CONTROL ENDPOINT */
            {
                /* Set up the control endpoint bdt for next packet */
                g_bdtmap->ep_dsc[SEND_CONTROL_ENDPOINT_BDT_INDEX].Stat._byte =
                    _SIE | _DATA1 | _DTS;
                if((g_bdtmap->ep_dsc[RECV_CONTROL_ENDPOINT_BDT_INDEX].
                    Stat.SieCtlBit.own == 0)
                        && (g_trf_direction != USB_TRF_UNKNOWN))
                {   
                    /* MCU owns RECV CONTROL endpoint */
                    uint_8 stat[2] = {_SIE | _DATA1 | _DTS, _SIE | _DTS};

                    /* set the for CONTROL ENDPOINT RECV direction */
                    g_bdtmap->ep_dsc[RECV_CONTROL_ENDPOINT_BDT_INDEX].cnt =
                    	USB_EP0_SIZE;

                    /* set the stat for CONTROL ENDPOINT RECV direction */
                    g_bdtmap->ep_dsc[RECV_CONTROL_ENDPOINT_BDT_INDEX].
                        Stat._byte = stat[g_trf_direction];

                    status = USB_OK;
                }
                /* clear suspend condition */
                CTL_TSUSPEND = 0;
            } /* CONTROL ENDPOINT */
        } /* Does MCU own IN BDT */
    } /* valid bdt index */
    return status;
}

uint_8 USB_DCI_Get_Send_Buffer (
    uint_8           controller_ID,	/* [IN] Controller ID */
    uint_8           ep_num,		/* [IN] Endpoint number */
    uint_8_ptr       *buff_ptr,		/* [OUT] Buffer for IN endpoint */
    USB_PACKET_SIZE  *size			/* [OUT] Size of IN endpoint */
)
{
    uint_8 status = USB_OK;
    uint_8 bdt_index = USB_DCI_Validate_Param (ep_num, USB_SEND);
    
    UNUSED(controller_ID);

    if(bdt_index != INVALID_BDT_INDEX)
    {
        /* Get BDT buffer addr for the endpoint */
        P_BUFF_DSC buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];
        
        /* Does MCU owns it */
        if(buffer_dsc->Stat.SieCtlBit.own == 0)
        {
            *buff_ptr = (uint_8_ptr)CAL_USB_RAM_ADDR(buffer_dsc->addr);
            *size = g_EP_sizes[ep_num];
        }
        else
        {
            status = USBERR_TRANSFER_IN_PROGRESS;
        }
    }
    
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Set_Address
 *
 * @brief The function configures Controller Device Address
 *
 * @param handle    : USB Device handle
 * @param address   : address to be configured in the Controller
 *
 * @return None
 *
 ******************************************************************************
 * Assigns the Address to the Controller
 *****************************************************************************/
void  USB_DCI_Set_Address (
    _usb_device_handle  handle,    /* [IN] USB Device handle */
    uint_8              address    /* [IN] Address of the USB device */
)
{
    UNUSED (handle)
    /* set the address */
    ADDR = address;

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Shutdown
 *
 * @brief The function shuts down the controller
 *
 * @param handle: USB Device handle
 *
 * @return None
 *
 ******************************************************************************
 * Resets USB Device Controller
 *****************************************************************************/
void USB_DCI_Shutdown (
     _usb_device_handle  handle  /* [IN] USB Device handle */
)
{
    UNUSED (handle)
    /* Reset the Control Register */
    CTL = 0;
    /* Initiate Reset in the USB Control0 Register */
    USBCTL0 = USB_RST;

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Assert_Resume
 *
 * @brief The function makes the Controller start USB RESUME signaling
 *
 * @param handle: USB Device handle
 *
 * @return None
 *
 ******************************************************************************
 *
 * This function starts RESUME signalling and then stops it after some delay.
 * In this delay make sure that COP is reset.
 *
 *****************************************************************************/
void USB_DCI_Assert_Resume (
     _usb_device_handle  handle  /* [IN] USB Device handle */
)
{
    uint_16 delay_count;
    UNUSED (handle)
    /* Reset Low Power RESUME enable */
    USBCTL0_USBRESMEN = 0;

    USB_DCI_WAKEUP

    CTL_CRESUME = 1;   /* Start RESUME signaling and make SUSPEND bit 0*/

    delay_count = ASSERT_RESUME_DELAY_COUNT; /* Set RESUME line for 1-15 ms*/
    do
    {
        delay_count--;
        __RESET_WATCHDOG();    /* Reset the COP */
    }while(delay_count);

    CTL_CRESUME = 0;          /* Stop RESUME signalling */

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_Bus_Token_Cpl_Handler
 *
 * @brief This function handles Token Complete USB interrupts on the bus.
 *
 * @param stat  : BDT stat byte
 * @param event : Pointer to USB EVENT Structure
 *
 * @return None
 *
 ******************************************************************************
 * This function handles Token Complete USB interrupts on the bus.
 *****************************************************************************/
static void USB_Bus_Token_Cpl_Handler (
    uint_8 stat,            /* [IN] Value of STAT register */
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
)
{
    uint_8 ep_num = event->ep_num;
    uint_8 bdt_index = 0 ;
    P_BDT_ELEM bdt_elem = NULL;
    boolean odd = FALSE;

    P_BUFF_DSC buffer_dsc = NULL;

#ifdef DOUBLE_BUFFERING_USED
    P_BUFF_DSC buffer_dsc_alt = NULL;/* stores data of alternate buffer --
                                       only for double buffer endpoints */
    if(DOUBLE_BUFFER_EP(ep_num))
    {
        odd = (boolean)((stat & STAT_ODD_MASK) >> STAT_ODD_SHIFT);
    }            
#endif

    /* Get the direction from STAT register */
    event->direction = ((stat & ENDPOINT_DIRECTION_MASK) >>
        ENDPOINT_DIRECTION_SHIFT);

    /* Get bdt index corresponding to endpoint number and direction */
    bdt_index = USB_DCI_Get_BDT_Index(event->ep_num,event->direction);

    bdt_index = bdt_index ^ odd; 

    buffer_dsc = &g_bdtmap->ep_dsc[bdt_index]; 
    /* We are not using 7 and 9 index of g_bdt_elem */
    bdt_elem = &g_bdt_elem[bdt_index ^ odd]; 

#ifdef DOUBLE_BUFFERING_USED
    if(DOUBLE_BUFFER_EP(ep_num))
    {
        buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index ^ 1];
        /* Toggle Data PID*/
        buffer_dsc_alt->Stat._byte = (uint_8)((buffer_dsc->Stat.McuCtlBit.data ^ 1) << 6);        
        /* Prepare for Next USB Transaction */
        bdt_elem->bdtmap_index ^= 1;
    }
#endif    


    /* Get address from BDT */
    event->buffer_ptr = (uint_8_ptr)CAL_USB_RAM_ADDR(buffer_dsc->addr);

    /* Get len from BDT */
    event->len = buffer_dsc->cnt;

    if(event->direction == USB_SEND)
    {
        if(event->ep_num == CONTROL_ENDPOINT)
        { /* for Control Endpoint */

            /* For Transfer Direction Host to Device */
            if(g_trf_direction == USB_RECV)
            {   /* make Transfer Direction UNKNOWN */
                g_trf_direction = USB_TRF_UNKNOWN;  
            }
#ifndef LONG_SEND_TRANSACTION
            else
            {
                /* Clear TOKEN Interrupt */
                INTSTAT = INTSTAT_TOKDNEF_MASK;
                return;
            }
#endif
        }  /* ep_num is CONTROL ENDPOINT */

#ifdef LONG_SEND_TRANSACTION

        if((g_trf_direction == USB_SEND) ||
             (event->ep_num != CONTROL_ENDPOINT))
        {
            /* update the request */
            bdt_elem->curr_offset += event->len;
            /* 
               Initiate next USB SEND if:
               1. More Data is still pending OR
               2. Send Data == Endpoint Size AND
               3. Zero Termination Flag is TRUE
            */
            if((bdt_elem->app_len > bdt_elem->curr_offset) ||
                ((uint_8)event->len == bdt_elem->len) &&
                (bdt_elem->flag == TRUE))
            {  
                /* send next Req */
#ifdef DOUBLE_BUFFERING_USED
                if(DOUBLE_BUFFER_EP(ep_num))
                {
                    uint_8_ptr addr = NULL;
                    /* prepare the other buffer to send data */
                    addr = (uint_8_ptr)CAL_USB_RAM_ADDR(buffer_dsc_alt->addr);
                    USB_DCI_Prepare_Send_Data(buffer_dsc_alt, bdt_elem, addr);
                    /* give the ownership to SIE and TOGGLE DATA BIT */
                    buffer_dsc_alt->Stat._byte = (uint_8)(
                        ((buffer_dsc_alt->Stat.McuCtlBit.data) << 6) | 
                        _SIE | _DTS);;                
                }
                else
#endif
                {
                    USB_DCI_Prepare_Send_Data(buffer_dsc, bdt_elem,
                        event->buffer_ptr);
                    buffer_dsc->Stat._byte = (uint_8)((
                        buffer_dsc->Stat.McuCtlBit.data ? _DATA0 : _DATA1)
                        | _SIE | _DTS);
                }

                /* Clear TOKEN Interrupt */
                INTSTAT = INTSTAT_TOKDNEF_MASK;

                return;

            }
            else
            {
                if(event->ep_num == CONTROL_ENDPOINT)
                {
                    g_trf_direction = USB_TRF_UNKNOWN;
                }
                event->buffer_ptr = bdt_elem->app_buffer;
                event->len = bdt_elem->curr_offset;

            }
        }
#endif
    }
    else /* direction IS USB_RECV */
    {
        if(event->ep_num == CONTROL_ENDPOINT)
        { /* for Control Endpoint */

            if((buffer_dsc->Stat.RecPid.pid == USB_SETUP_TOKEN)
                && (event->len != 0 ))
            {
                event->setup = TRUE; /* set setup phase */

                /***************************************
                * next 6 lines are for optimisation for
                * if((event->buffer_ptr[0] & USB_SETUP_DIRECTION)
                *                     == USB_SETUP_DIRECTION)
                *   g_trf_direction=USB_SEND;
                * else
                *   g_trf_direction=USB_RECV;
                ***************************************/

                /* Based on direction of Setup Packet set
                   Transfer direction of next packet */
                g_trf_direction = (uint_8)((uint_8)
					(event->buffer_ptr[0]) >> 7);

                g_bdtmap->ep_dsc[SEND_CONTROL_ENDPOINT_BDT_INDEX].
                    Stat._byte &= ~_SIE;
            }
            else if(g_trf_direction == USB_SEND)
            {
                /* make Transfer Direction UNKNOWN */
                g_trf_direction = USB_TRF_UNKNOWN;   
            }
        }  /* ep_num is CONTROL ENDPOINT */

#ifdef LONG_RECEIVE_TRANSACTION
        if(bdt_elem->app_len != (USB_PACKET_SIZE)UNINITIALISED_VAL)
        { /* on control endpoint the data is only 8 bytes */

            USB_PACKET_SIZE size = event->len;

            /* update the request */
            if((bdt_elem->app_len - bdt_elem->curr_offset)  < event->len)
            {   
				/* case when host sends more data then it commits */
                size = (bdt_elem->app_len - bdt_elem->curr_offset);
            }

            /* copy data to buffer  */
            (void)memcpy((uint_8_ptr)&bdt_elem->app_buffer
                [bdt_elem->curr_offset], event->buffer_ptr, size);
            bdt_elem->curr_offset += size;             

            /* 
               Initiate next USB RECV if:
               1. More Data is still pending OR
               2. Received Data == Endpoint Size AND
               3. Zero Termination Flag is TRUE
            */
            if(
               ( (size == bdt_elem->len) && 
                 (bdt_elem->app_len > bdt_elem->curr_offset)
               ) ||
               ( (bdt_elem->app_len)&&
                 (!(bdt_elem->app_len %% bdt_elem->len)) &&
                 (bdt_elem->flag == TRUE)
               )
              )
            {  
                /* send next IO */

                /* Clear TOKEN Interrupt */
                INTSTAT = INTSTAT_TOKDNEF_MASK;

#ifdef DOUBLE_BUFFERING_USED
                if(DOUBLE_BUFFER_EP(ep_num))
                {
                    /* give the ownership to SIE and Toggle DATA bit*/
                    buffer_dsc_alt->Stat._byte = (uint_8)((
                        (buffer_dsc_alt->Stat.McuCtlBit.data) << 6) | 
                        _SIE | _DTS);
                }
                else
#endif
                {
                    buffer_dsc->Stat._byte = (uint_8)((
                        buffer_dsc->Stat.McuCtlBit.data ? _DATA0 : _DATA1)
                        | _SIE | _DTS);
                }
                /* Clear TOKEN Interrupt */
                INTSTAT = INTSTAT_TOKDNEF_MASK;
                return;
            }
            else /* request completed */
            {   /* populate buffer structure */
                event->buffer_ptr = bdt_elem->app_buffer;
                event->len = bdt_elem->curr_offset;
                bdt_elem->app_len = UNINITIALISED_VAL;                                
            }
        }
#endif
    } /* Direction was RECV */

    /* Clear TOKEN Interrupt */
    //INTSTAT = INTSTAT_TOKDNEF_MASK;

    /* Notify Device Layer of Data Received or Sent Event */
    (void)USB_Device_Call_Service(event->ep_num, event);

    return;
}
/**************************************************************************//*!
 *
 * @name  USB_ISR
 *
 * @brief The function handles USB interrupts on the bus.
 *
 * @param None
 *
 * @return None
 *
 ******************************************************************************
 *
 * This function is hooked onto interrupt 7 and handles the USB interrupts.
 * After handling the interrupt it calls the Device Layer to notify it about
 * the event.
 *
 *****************************************************************************/
#if 0 /* << EST */
void USB_ISR(void);

#if (defined(_MC9S08MM128_H) || defined(_MC9S08JE128_H))
#pragma CODE_SEG NON_BANKED
#endif

void interrupt VectorNumber_Vusb USB_ISR_vector(void)
{
    USB_ISR();
}

#if (defined(_MC9S08MM128_H) || defined(_MC9S08JE128_H))
#pragma CODE_SEG DEFAULT
#endif

#else
/* device is %CPUDevice << EST */
%if (CPUDevice="MC9S08MM128") | (CPUDevice="MC9S08JE128")
static void USB_ISR_Banked(void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt USB_ISR(void)
{
    USB_ISR_Banked();
}

#pragma CODE_SEG DEFAULT

static void USB_ISR_Banked(void)
%else
void interrupt USB_ISR(void)
%endif
#endif
{
	/* Which interrupt occurred and also was enabled */
	uint_8 intr_stat = INTSTAT & INTENB;
	uint_8 stat = STAT;
	uint_8 u8EPMask;	
	uint_8 dev_state = USB_STATUS_UNKNOWN;

	/* Get the device state from the Device Layer */
	(void)_usb_device_get_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
			&dev_state);

	/* if current device state is SUSPEND and Low Power Resume Flag set */
	if((USBCTL0_LPRESF == 1) && (dev_state == USB_STATE_SUSPEND))
	{
		/* Reset Low Power RESUME enable */
		USBCTL0_USBRESMEN = 0;
	}

	if(SOF_TOKEN_FLAG(intr_stat))
	{
		/* Clear SOF Interrupt */
		INTSTAT = INTSTAT_SOFTOKF_MASK;

        SOF_TOKEN_FLAG_SET(gu8ProcessPendingFlag);
	}

	if(BUS_RESET_FLAG(intr_stat))
	{
		/* Clear USB Bus Reset Flag */
		INTSTAT = INTSTAT_USBRSTF_MASK;
		BUS_RESET_FLAG_SET(gu8ProcessPendingFlag);	
	}

	if(TOKEN_COMPL_FLAG(intr_stat))
	{
		/* Clear TOKEN Interrupt */
		INTSTAT = INTSTAT_TOKDNEF_MASK;

		TOKEN_COMPL_FLAG_SET(gu8ProcessPendingFlag);

		u8EPMask = 0x01<<((stat & ENDPOINT_NUMBER_MASK) >>
				ENDPOINT_NUMBER_SHIFT);

		gtUSBEPEventFlags |= u8EPMask;

		if((stat & 0x04) != 0)  /* Odd transaction */
		{
			gtUSBEPOddEvenFlags |= u8EPMask;
		}
		else
		{
			gtUSBEPOddEvenFlags &= ~u8EPMask;
		}

		if((stat & 0x08) != 0)  /* Out transaction */
		{
			gtUSBEPDirFlags |= u8EPMask;
		}
		else
		{
			gtUSBEPDirFlags &= ~u8EPMask;
		}
	}

	if(ERROR_FLAG(intr_stat))
	{
		gu8ErrorFlags = ERRSTAT & ERRENB;

		ERROR_FLAG_SET(gu8ProcessPendingFlag);

		ERRSTAT = ERRSTAT_CLEAR_ALL; /*clear all errors*/

		/* Clear ERROR Interrupt */
		INTSTAT = INTSTAT_ERRORF_MASK;
	}

	if(SLEEP_FLAG(intr_stat))
	{
		/* Clear RESUME Interrupt if pending */
		INTSTAT = INTSTAT_RESUMEF_MASK;

		/* Clear SLEEP Interrupt */
		INTSTAT = INTSTAT_SLEEPF_MASK;

		SLEEP_FLAG_SET(gu8ProcessPendingFlag);

		/* Set Low Power RESUME enable */
		USBCTL0_USBRESMEN = 1;

		/* Enable RESUME Interrupt */
		INTENB_RESUME = 1;
	}

	if(RESUME_FLAG(intr_stat))
	{
		/* Clear RESUME Interrupt */
		INTSTAT = INTSTAT_RESUMEF_MASK;

		RESUME_FLAG_SET(gu8ProcessPendingFlag);

		/* Disable RESUME Interrupt */
		INTENB_RESUME = 0;
	}

	if(STALL_FLAG(intr_stat))
	{
		/* Clear STALL Interrupt */
		INTSTAT = INTSTAT_STALLF_MASK;

		STALL_FLAG_SET(gu8ProcessPendingFlag);
	}
}

void USB_Engine(void)
{
    USB_DEV_EVENT_STRUCT event;

    /* Initialize the event structure */
    event.controller_ID = g_dci_controller_Id;
    event.setup = FALSE;
    event.buffer_ptr = NULL;
    event.len = 0;
    event.direction = USB_RECV;
    event.errors = NO_ERRORS;
    event.ep_num = (uint_8)UNINITIALISED_VAL;

    if(SOF_TOKEN_FLAG(gu8ProcessPendingFlag))
    {
    	/* Clear SOF Flag */
    	SOF_TOKEN_FLAG_CLR(gu8ProcessPendingFlag);

    	event.buffer_ptr = &FRMNUML;/*address of Lower byte of Frame number*/

    	/* Notify Device Layer of SOF Event */
    	(void)USB_Device_Call_Service(USB_SERVICE_SOF, &event);
    }
 
    if(BUS_RESET_FLAG(gu8ProcessPendingFlag))
    {
    	BUS_RESET_FLAG_CLR(gu8ProcessPendingFlag);

    	/* Handle RESET Interrupt */
    	USB_Bus_Reset_Handler();

    	/* Notify Device Layer of RESET Event */
    	(void)USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);

    	/* No need to process other interrupts */
    	return;
    }

    if(TOKEN_COMPL_FLAG(gu8ProcessPendingFlag) || (gtUSBEPEventFlags != 0))
    {
    	uint_8 u8Count;
    	uint_8 u8Mask;
    	uint_8 u8Stat;

    	TOKEN_COMPL_FLAG_CLR(gu8ProcessPendingFlag);

    	for(u8Count = 0, u8Mask = 0x01; u8Count < 6; u8Count++, u8Mask<<=1)
    	{
    		if((gtUSBEPEventFlags & u8Mask) != 0)
    		{
    			DisableInterrupts;
    			gtUSBEPEventFlags &= ~u8Mask;

    			EnableInterrupts;

    			event.ep_num = u8Count;
    			u8Stat = 0;

    			if((gtUSBEPDirFlags & u8Mask) != 0)
    			{
    				u8Stat |= 0x08;
    			}

    			if((gtUSBEPOddEvenFlags & u8Mask) != 0)
    			{
    				u8Stat |= 0x04;
    			}

    			USB_Bus_Token_Cpl_Handler(u8Stat, &event);

    		}
    	}
    }

    if(ERROR_FLAG(gu8ProcessPendingFlag))
    {
    	ERROR_FLAG_CLR(gu8ProcessPendingFlag);

    	event.errors = gu8ErrorFlags;

    	/* Notify Device Layer of ERROR Event to error service */
    	(void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
    }

    if(SLEEP_FLAG(gu8ProcessPendingFlag))
    {
    	SLEEP_FLAG_CLR(gu8ProcessPendingFlag);

    	/* Notify Device Layer of SLEEP Event */
    	(void)USB_Device_Call_Service(USB_SERVICE_SLEEP, &event);

#ifdef USB_LOWPOWERMODE
    	/* Enter Stop3 Mode*/
    	Enter_StopMode(3);
#endif
    }

    if(RESUME_FLAG(gu8ProcessPendingFlag))
    {
    	RESUME_FLAG_CLR(gu8ProcessPendingFlag);

    	/* Notify Device Layer of RESUME Event */
    	(void)USB_Device_Call_Service(USB_SERVICE_RESUME, &event);
    }

    if(STALL_FLAG(gu8ProcessPendingFlag))
    {
    	uint_8 endp_status;

    	STALL_FLAG_CLR(gu8ProcessPendingFlag);

    	event.ep_num = UNINITIALISED_VAL;

    	/* If Control Endpoint is stalled then unstall it.
            For other endpoints host issues clear endpoint feature request
            to unstall them */

    	/* Get Control Endpoint Status*/
    	(void)_usb_device_get_status(&(event.controller_ID),
    	            (USB_STATUS_ENDPOINT | CONTROL_ENDPOINT),
    	            &endp_status);
    	
    	if(endp_status == USB_STATUS_STALLED)
    	{
    		event.ep_num = CONTROL_ENDPOINT;
    		event.direction = USB_SEND;
    	}
    	/* Notify Device Layer of STALL Event */
    	(void)USB_Device_Call_Service(USB_SERVICE_STALL, &event);
    }
}

/**************************************************************************//*!
 *
 * @name  Clear_Mem
 *
 * @brief The function clears memory starting from start_addr till count bytes
 *
 * @param start_addr : Buffer Start address
 * @param count      : Count of Bytes
 * @param val        : Value to be set
 *
 * @return None
 ******************************************************************************
 * This function is an implementation of memset
 *****************************************************************************/
void Clear_Mem(
    uint_8* start_addr,     /* [OUT] Buffer Start address */
    uint_8 count,           /* [IN] Count of Bytes */
    uint_8 val              /* [IN] Value to be set */
)
{
    (void)memset(start_addr, val, count);
    return;
}

#ifdef USB_LOWPOWERMODE
/**************************************************************************//*!
 *
 * @name  Enter_StopMode
 *
 * @brief The function configures STOP Mode
 *
 * @param stop_mode : STOP MODE to be entered
 *
 * @return None
 ******************************************************************************
 * This function configures different STOP MODES defined by the controller.
 * Used to put controller into low power mode. Only STOP MODE 3 is implemented
 *****************************************************************************/
static void Enter_StopMode(STOP_MODE stop_mode)
{
    switch(stop_mode)
    {
        case STOP_MODE1:
#if 0 /* << EST */
#if (!(defined(_MC9S08JS16_H)|| defined(_MC9S08JM16_H) ||   \
    defined(_MC9S08JM60_H)))
            /* MC9S08JS16,  MC9S08JM16 and MC9S08JM60 does not support
               STOP MODE 1. We enter Default Stop Mode
            */
#endif
#else
          /* device is %CPUDevice << EST */
          %if (CPUDevice="MC9S08JS16") | (CPUDevice="MC9S08JM16") | (CPUDevice="MC9S08JM60")
          /* MC9S08JS16,  MC9S08JM16 and MC9S08JM60 does not support
             STOP MODE 1. We enter Default Stop Mode
          */
          %endif
#endif
            break;
        case STOP_MODE2:
            /* Save IO Pin Status in a global variable
                IO Pin Status is to be restored at POR.
                Check if PPDC
            */
            /* Set PPDC */
            break;
        case STOP_MODE3:
            /* Enable LVD */
            SPMSC1_LVDE = 1;
            SPMSC1_LVDSE = 1;
            /* Clear PPDC */
            SPMSC2_PPDC = 0;
            break;
    }
    /* Enter STOP Mode*/
    _Stop;
}

#endif
