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
 * @file usb_dci.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains CFV1 USB stack controller layer implementation.
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
/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/
/****************************************************************************
 * Global Variables
 ****************************************************************************/
#pragma define_section usb_bdt ".usb_bdt" RW
/* location for BDT Table and buff */
#if 0
__declspec (usb_bdt) static uint_8 g_Mem[BYTES_1024];
#else /* << EST */
__declspec (usb_bdt) uint_8 g_Mem[BYTES_1024];
#endif
/* Pointer to BDT Map Structure */
BDTMAP *g_bdtmap = NULL;
/* per endpoint per direction bdt index structure */
static BDT_ELEM  g_bdt_elem[MAX_BDT_INDEX >> 1];
/* stores Controller ID */
static uint_8 g_dci_controller_Id;
/* Start BDT buffer Address */
static uint_32 g_bdt_address;
/* Transfer direction */
static uint_8 g_trf_direction = USB_TRF_UNKNOWN;
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_Bus_Reset_Handler(void);
static uint_8 USB_DCI_Get_BDT_Index(uint_8 ep_num,
                                    uint_8 direction,
                                    boolean odd);
static uint_8 USB_DCI_Validate_Param(uint_8 ep_num,
                                    uint_8 direction,
                                    boolean odd);
#ifdef LONG_SEND_TRANSACTION
static void USB_DCI_Prepare_Send_Data(P_BUFF_DSC buffer_dsc,
                                    P_BDT_ELEM bdt_elem);
#endif
static void USB_Bus_Token_Cpl_Handler(uint_8 stat,
                                    USB_DEV_EVENT_STRUCT* event);
#ifdef USB_LOWPOWERMODE
static void Enter_StopMode(STOP_MODE stop_mode);
#endif
/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

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
static void USB_Bus_Reset_Handler (void)
{
    ERR_STAT = ERR_STAT_CLEAR_ALL;  /* clear USB error flag */
    CTL_ODD_RST = 1;                /* Reset to Even buffer */
    ADDR = 0;                       /* reset to default address */
    /* Select System Clock and Disable Weak Pull Downs */
    USB_CTRL = 0x03;

    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)(g_bdt_elem),
        (sizeof(BDT_ELEM) * (MAX_BDT_INDEX >> 1)),
        (uint_8)UNINITIALISED_VAL);

    /* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap, BYTES_1024, (uint_8)NULL);

    /* Initialize BDT buffer address */
    g_bdt_address = ((uint_32)g_bdtmap + BYTES_512);

    g_trf_direction = USB_TRF_UNKNOWN;

    CTL_ODD_RST = 0;
    USBTRC0 = UCFG_VAL;             /* attach CFv1 core to USB bus */

    ERR_ENB = ERR_ENB_ENABLE_ALL;   /* Enable All Error Interrupts */
    INT_ENB = INTENB_BUS_RESET_VAL; /* Enable All Interrupts except RESUME */

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Get_BDT_Index
 *
 * @brief The function maps endpoint number and direction to bdt index
 *
 * @param  ep_num   : Endpoint Number
 * @param  direction: Endpoint direction
 * @param  odd      : Odd or even buffer
 *
 * @return bdt index         : Mapped bdt index
 *         INVALID_BDT_INDEX : Incase of error
 *
 ******************************************************************************
 * This function returns BDT Index from Endpoint number, direction,
 * odd/even buffer
 *****************************************************************************/
static uint_8 USB_DCI_Get_BDT_Index (
    uint_8 ep_num,     /* [IN] Endpoint Number */
    uint_8 direction,  /* [IN] Endpoint direction */
    boolean odd        /* [IN] Odd or even buffer */
)
{
    uint_8 bdt_index = INVALID_BDT_INDEX;

    if(ep_num < MAX_SUPPORTED_ENDPOINTS)
    {
        /* per endpoint 4 bdt_index -- 2 for recv 2 for send */
        bdt_index=(uint_8)((ep_num * 4) + (uint_8)odd);

        if(direction == USB_SEND)
        {
            bdt_index += 2;
        }
    }
    return bdt_index;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Validate_Param
 *
 * @brief The function validates endpoint number & direction parameters
 *        and returns bdt index.
 *
 * @param  ep_num   : Endpoint Number
 * @param  direction: Endpoint direction
 * @param  odd      : odd or even buffer
 *
 * @return bdt index         : mapped bdt index
 *         INVALID_BDT_INDEX : incase of error
 *
 ******************************************************************************
 * This function validates endpoint parameters and returns bdt index
 *****************************************************************************/
static uint_8 USB_DCI_Validate_Param (
    uint_8 ep_num,     /* [IN] Endpoint Number */
    uint_8 direction,  /* [IN] Endpoint direction */
    boolean odd        /* [IN] Odd or even buffer */
)
{
    /* Get bdt index mapped to endpoint number-direction and odd/even buffer */
    uint_8 bdt_index = USB_DCI_Get_BDT_Index(ep_num, direction, odd);

    if((bdt_index  != INVALID_BDT_INDEX) &&
        (g_bdt_elem[TRANSFER_INDEX(bdt_index)].len ==
        (uint_16)UNINITIALISED_VAL))
    {
        /* Incase length in bdt_elem is uninitialised return invalid index */
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
 * @param  buffer_dsc   : Pointer to buffer descriptor element in USB_RAM
 * @param  bdt_elem     : Pointer to per endpoint/direction structure
 *
 * @return None
 *
 ******************************************************************************
 * This functions configures Buffer Descriptor (Address and Count)
 *****************************************************************************/
static void USB_DCI_Prepare_Send_Data (
    P_BUFF_DSC buffer_dsc,  /* [OUT] Pointer to buffer descriptor
                                element in USB_RAM */
    P_BDT_ELEM bdt_elem     /* [IN] Pointer to per endpoint/direction
                                structure */
)
{
    uint_8_ptr buff_ptr = bdt_elem->app_buffer + bdt_elem->curr_offset;
    uint_16 current_count = 0;

    /* adjust size based on the input at the init endpoint */
    if((bdt_elem->app_len - bdt_elem->curr_offset) > bdt_elem->len)
    {
        /* If size of packet is greater than endpoint buffer size */
        current_count = bdt_elem->len;
    }
    else
    {
        /* If size of packet is smaller than endpoint buffer size */
        current_count = (uint_16)(bdt_elem->app_len - bdt_elem->curr_offset);
    }

    buffer_dsc->cnt = SWAP16(current_count);

    buffer_dsc->addr = SWAP32((uint_32)buff_ptr);
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
 * @param controller_ID : Controller ID
 *
 * @return status
 *         USB_OK    : Always
 ******************************************************************************
 * Initializes the USB controller
 *****************************************************************************/
uint_8 USB_DCI_Init (
    uint_8    controller_ID,   /* [IN] Controller ID */
    uint_8    bVregEn         /* Enables or disables internal regulator */
)
{
    USB_CTRL = 0x03;                    /* Select System Clock and
                                           Disable Weak Pull Downs */

    g_dci_controller_Id = controller_ID; /* save the controller_ID
                                           for future use*/

    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)(g_bdt_elem),
       (sizeof(BDT_ELEM) * (MAX_BDT_INDEX >> 1)),
       (uint_8)UNINITIALISED_VAL);
    g_bdtmap = (BDTMAP *)((uint_32)g_Mem);

    /* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap, BYTES_1024, (uint_8)NULL);

    #ifndef OTG_BUILD

    USBTRC0 = _USBRESET;                /* Hard Reset to the USB Module */

    while(USBTRC0_USBRESET == 1)        /* loop till the Reset bit clears  */
    {
    };

    #endif

    g_trf_direction = USB_TRF_UNKNOWN;

    /* attach CFv1 core to USB bus*/
    if(bVregEn)
    	USBTRC0 = _USBPUEN|_USBREGEN;
    else
    	USBTRC0 = _USBPUEN;

    /* Set the BDT Table address, Need to be on 512 byte boundry */
    /* D8 Bit is masked in BDT_PAGE_01 */
    BDT_PAGE_01 = (uint_8)(((uint_32)g_bdtmap >> 8) & 0xFE);
    BDT_PAGE_02 = (uint_8)((uint_32)g_bdtmap >> 16);
    BDT_PAGE_03 = (uint_8)((uint_32)g_bdtmap >> 24);

    /* Initialized BDT buffer address */
    g_bdt_address = ((uint_32)g_bdtmap + BYTES_512);

    #ifndef OTG_BUILD
     /* Pull Up configuration */
     USB_OTG_CONTROL |= USB_OTG_CONTROL_DPPULLUP_NONOTG_MASK;
    #endif


    CTL_USB_EN_SOF_EN = 1;              /* Enable USB module */
    INT_STAT = INT_STAT_CLEAR_ALL;      /* Clear USB interrupts*/

    INT_ENB_USB_RST_EN = 1;             /* Enable USB RESET Interrupt */

    INT_ENB_SLEEP_EN = 1;               /* Enable USB Sleep Interrupt */

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
	 INT_STAT = INT_STAT_CLEAR_ALL;

	 /* Disable USB RESET Interrupt */
	 INT_ENB_USB_RST_EN = 0;

   /* Disable USB module */
   CTL_USB_EN_SOF_EN = 0;

	 return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Init_EndPoint
 *
 * @brief The function initializes an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_ptr        : Pointer to EndPoint Structures
 * @param flag          : Zero Termination
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
    USB_EP_STRUCT_PTR    ep_ptr,       /* [IN] Pointer to Endpoint structure,
                                               (endpoint number,
                                                endpoint type,
                                                endpoint direction,
                                                max packet size) */
    boolean              flag          /* [IN] Zero Termination */
)
{
    UNUSED(controller_ID)
    uint_8 bdtmap_index;
    uint_8 bdtelem_index;
    uint_8 ep_num = ep_ptr->ep_num;
    uint_8 direction = ep_ptr->direction;
    uint_32 ep_ctrl[2] = {EP_OUT, EP_IN};
    P_BUFF_DSC temp;
    P_BDT_ELEM bdt_elem;

    /* if the max packet size is greater than the max buffer size */
    if(ep_ptr->size > MAX_EP_BUFFER_SIZE)
    {
        ep_ptr->size = MAX_EP_BUFFER_SIZE;
    }

    /* Get the bdt index correspoding to the endpoint */
    bdtmap_index = USB_DCI_Get_BDT_Index(ep_num, direction,
        USB_RAM_EVEN_BUFFER);
    bdtelem_index = (uint_8)TRANSFER_INDEX(bdtmap_index);

    /*
       incase the bdtmap_index is invalid
       or already initialised return with an error
    */
    if((bdtmap_index  == INVALID_BDT_INDEX) ||
       (g_bdt_elem[bdtelem_index].len != (uint_16)UNINITIALISED_VAL) ||
       (g_bdt_address >= ((uint_32)g_Mem + BYTES_1024)) ||
       (ep_ptr->type > USB_INTERRUPT_PIPE) ||
       (ep_ptr->direction > USB_SEND))
    {
        return USBERR_EP_INIT_FAILED;
    }

    bdt_elem = &g_bdt_elem[bdtelem_index];
    /* Reset Handler resets bdtmap_index to UNINITIALISED_VAL */
    if(bdt_elem->bdtmap_index == (uint_8)UNINITIALISED_VAL)
    {
        bdt_elem->bdtmap_index = 0;
    }

   /* update bdt element structure */
    bdt_elem->len = (uint_16)ep_ptr->size;
    bdt_elem->flag = flag;
    /* preserving even/odd buffer bit */
    bdt_elem->bdtmap_index &= 0x01;
    bdt_elem->bdtmap_index |= ((direction << 1) | (ep_num << 2));
    bdt_elem->addr = g_bdt_address;
    bdt_elem->type = ep_ptr->type;
    bdt_elem->direction = direction;

    temp = &g_bdtmap->ep_dsc[bdt_elem->bdtmap_index];

    /* Update BDTMAP for endpoint's EVEN Buffer */
    temp->cnt = SWAP16((uint_16)ep_ptr->size);
    temp->addr = SWAP32(g_bdt_address);
    temp->Stat._byte = (_CPU | _DATA0 | _DTS);

    /* Update BDTMAP for endpoint's ODD Buffer */
    temp = &g_bdtmap->ep_dsc[bdt_elem->bdtmap_index ^ 1];

    temp->cnt = SWAP16((uint_16)ep_ptr->size);
    temp->addr = SWAP32(g_bdt_address);
    temp->Stat._byte = (_CPU | _DATA1 | _DTS);

    /* update the buffer address for the next endpoint */
    g_bdt_address += ep_ptr->size;

    if(direction == USB_RECV)
    {
        /*
           For Recv Endpoints
           Give SIE Control to DATA0
        */
        temp = &g_bdtmap->ep_dsc[bdt_elem->bdtmap_index];
        temp->Stat._byte |= _SIE;
    }

    /* enable handshake for Non-Isochronous Endpoints */
    ep_ctrl[direction] |= ((ep_ptr->type != USB_ISOCHRONOUS_PIPE) ?
        HSHK_EN:0x00);
    /* set the EndPoint Control MCU Register*/
    *((&ENDPT0) + (4 * ep_num)) |= ep_ctrl[direction];

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Cancel_Transfer
 *
 * @brief The function cancels any pending Transfers which ahve not been sent
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param direction       : Endpoint direction
 *
 * @return status
 *         USBERR_NOT_SUPPORTED : Always
 ******************************************************************************
 * This function just returns Error Code not supported
 *****************************************************************************/
uint_8 USB_DCI_Cancel_Transfer (
    _usb_device_handle  handle,           /* [IN] USB Device handle */
    uint_8              endpoint_number,  /* [IN] Endpoint number */
    uint_8              direction         /* [IN] Endpoint direction */
)
{
    UNUSED(handle)
#ifdef LONG_TRANSACTION
    uint_8 status= USBERR_UNKNOWN_ERROR;

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);
    uint_8 bdtelem_index = (uint_8)TRANSFER_INDEX(bdt_index);

    /* Check for valid bdt index */
    if(bdt_index != INVALID_BDT_INDEX)
    {
        P_BDT_ELEM bdt_elem = &g_bdt_elem[bdtelem_index];
        P_BUFF_DSC buffer_dsc = &g_bdtmap->ep_dsc[bdt_elem->bdtmap_index];
        P_BUFF_DSC buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_elem->bdtmap_index ^ 1];
        /* Clear SIE Control Bit for both buffers*/
        buffer_dsc->Stat._byte &= ~_SIE;
        buffer_dsc_alt->Stat._byte &= ~_SIE;
        bdt_elem->app_len = (USB_PACKET_SIZE)UNINITIALISED_VAL;

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
 * @brief The function de initializes an endpoint
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param direction     : Endpoint direction
 *
 * @return status
 *         USB_OK                   : When successfull
 *         USBERR_EP_DEINIT_FAILED  : When unsuccessfull
 ******************************************************************************
 *
 * This function un-intializes the endpoint by clearing the corresponding
 * endpoint control register and then clearing the bdt elem.
 *
 *****************************************************************************/
uint_8 USB_DCI_Deinit_EndPoint (
    uint_8    controller_ID,   /* [IN] Controller ID */
    uint_8    ep_num,          /* [IN] Endpoint number */
    uint_8    direction        /* [IN] Endpoint direction */
)
{
    UNUSED(controller_ID)

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (ep_num, direction,
        USB_RAM_EVEN_BUFFER);
    uint_8 bdtelem_index = (uint_8)TRANSFER_INDEX(bdt_index);

    /* incase the bdt_index is invalid*/
    if(bdt_index  == INVALID_BDT_INDEX)
    {
        return USBERR_EP_DEINIT_FAILED;
    }
    USB_DCI_Cancel_Transfer(&controller_ID, ep_num, direction);
    /* delete buffer space for both even and odd buffers */
    g_bdt_address -= (g_bdt_elem[bdtelem_index].len);

    /* Disable endpoint */
    *((&ENDPT0) + (4 * ep_num)) = EP_DISABLE;

    /* un-initialize the bdt_elem structure for this endpoint */
    g_bdt_elem[bdtelem_index].len = (uint_16)UNINITIALISED_VAL;
    g_bdt_elem[bdtelem_index].addr = (uint_32)UNINITIALISED_VAL;

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Stall_EndPoint
 *
 * @brief The function stalls an endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param direction       : Endpoint direction
 *
 * @return None
 *
 ******************************************************************************
 * This function stalls the endpoint by setting Endpoint BDT
 *****************************************************************************/
void USB_DCI_Stall_EndPoint (
    _usb_device_handle  handle,            /* [IN] USB Device handle */
    uint_8              endpoint_number,   /* [IN] Endpoint number to stall */
    uint_8              direction          /* [IN] Direction to stall */
)
{
    UNUSED(handle)
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];
    bdt_index = bdt_elem->bdtmap_index;

    /* Check for valid bdt index */
	if(bdt_index != INVALID_BDT_INDEX)
    {
        (void)USB_DCI_Cancel_Transfer(handle, endpoint_number, direction);

        /* Stall endpoint */
        g_bdtmap->ep_dsc[bdt_index].Stat._byte |= (_SIE | _BDTSTALL);
    }

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Unstall_EndPoint
 *
 * @brief The function unstalls an endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param direction       : Endpoint direction
 *
 * @return None
 *
 ******************************************************************************
 * This function unstalls the endpoint by clearing Endpoint Control Register
 * and BDT
 *****************************************************************************/
void USB_DCI_Unstall_EndPoint (
    _usb_device_handle  handle,           /* [IN] Controller ID */
    uint_8              endpoint_number,  /* [IN] Endpoint number */
    uint_8              direction         /* [IN] Endpoint direction */
)
{
    UNUSED(handle)
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];

    bdt_index = bdt_elem->bdtmap_index;

    /* Check for valid bdt index */
	if(bdt_index != INVALID_BDT_INDEX)
	{
        ENDPT0STR *endpoint = (ENDPT0STR*)(&_ENDPT0 + (4 * endpoint_number));

	    /* Enable ENDPTx for non control endpoints */
	    /* For Control Endpoint the default Value 0x0D */
        if(endpoint_number != CONTROL_ENDPOINT)
        {
            uint_8 endpt;
            /* Enable handshaking for non isochronous endpoint */
            endpt = (uint_8)((bdt_elem->type != USB_ISOCHRONOUS_PIPE) ?
                HSHK_EN:0);
            /*
               Enable the endpoint in the specified direction and disable
               control tranfers (valid only in case the endpoint is
               bidirectional)
            */
    	    endpt |= (uint_8)(EP_CTL_DIS |
                ((direction == USB_SEND)?EP_IN:EP_OUT));
            endpoint->Byte |= endpt;
        }
        /* Clear Endpoint Stall bit is endpoint control register */
        endpoint->Bits.EP_STALL = 0;

	    /* Unstall endpoint by clearing stall bit in BDT  */
	    g_bdtmap->ep_dsc[bdt_index].Stat._byte &= ~(_SIE | _BDTSTALL);
        /* We Require DATA0 PID to be zero on unstall */
        g_bdtmap->ep_dsc[bdt_index].Stat._byte = _DATA0;
	    if(direction == USB_RECV)
	    {
	        /* Initiate Next receive Transfer */
	        USB_DCI_Recv_Data(handle, endpoint_number, NULL, 0);
	    }
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
 * @param endpoint_number : Endpoint number
 * @param buffer_ptr      : Application buffer pointer
 *
 * @return None
 *
 ******************************************************************************
 * Copies setup packet from USB RAM to Application Buffer
 *****************************************************************************/
void USB_DCI_Get_Setup_Data (
    _usb_device_handle  handle,           /* [IN] USB Device handle */
    uint_8              endpoint_number,  /* [IN] Endpoint number for the transaction */
    uint_8_ptr          buffer_ptr        /* [IN] Pointer to the buffer into which to read data */
)
{
    UNUSED(handle)
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_RECV,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];
    bdt_index = bdt_elem->bdtmap_index;

    /* address correponding to the endpoint */
    uint_8_ptr addr = (uint_8_ptr)SWAP32(g_bdtmap->ep_dsc[bdt_index].addr);

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
 * @param direction       : Endpoint direction
 *
 * @return status
 *         USBERR_TR_FAILED                : When unsuccessfull
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
    _usb_device_handle  handle,           /* [IN] Controller ID */
    uint_8              endpoint_number,  /* [IN] Endpoint number */
    uint_8              direction         /* [IN] Endpoint direction */
)
{
    UNUSED(handle)
    uint_8 status = USB_STATUS_DISABLED;

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);

    /* Check for valid bdt index */
	if(bdt_index != INVALID_BDT_INDEX)
    {
        uint_8 ep_control = (uint_8)(*((&ENDPT0)+4*endpoint_number));

        status = USB_STATUS_IDLE;

        /* Check for direction in endpoint control register */
        if((ep_control & (EP_IN|EP_OUT)) == EP_DISABLE)
        {
            status = USB_STATUS_DISABLED;
        }
        /* Check for stall bit in endpoint control register */
        else if ((ep_control &  EPCTL_STALL) == EPCTL_STALL)
        {
            status = USB_STATUS_STALLED ;
        }
        /* Check whether SIE has control of BDT */
        else if ((g_bdtmap->ep_dsc[bdt_index].Stat.SieCtlBit.own == 1)
            || (g_bdtmap->ep_dsc[bdt_index ^ 1].Stat.SieCtlBit.own == 1))
        {
            status = USB_STATUS_TRANSFER_IN_PROGRESS;
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Recv_Data
 *
 * @brief The function retrieves data received on an RECV endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param buffer_ptr      : Application buffer pointer
 * @param size            : Size of the buffer
 *
 * @return status
 *         USB_OK                          : When successfull
 *         USBERR_RX_FAILED                : When unsuccessfull
 ******************************************************************************
 * This function retrieves data received data on a RECV endpoint by copying it
 * from USB RAM to application buffer
 *****************************************************************************/
uint_8 USB_DCI_Recv_Data (
    _usb_device_handle    handle,           /* [IN] USB Device handle */
    uint_8                endpoint_number,  /* [IN] Endpoint number */
    uchar_ptr             buffer_ptr,       /* [OUT] Application buffer pointer */
    uint_32               size              /* [IN] Size of the buffer */
)
{
    UNUSED(handle)
    uint_8 status = USBERR_RX_FAILED;
    uint_8_ptr addr = NULL;

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_RECV,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];
    /* For selecting even/odd buffer */
    bdt_index = bdt_elem->bdtmap_index;

    if(bdt_index != INVALID_BDT_INDEX)
    {
        P_BUFF_DSC buffer_dsc = &g_bdtmap->ep_dsc[bdt_index ^ 1];
        P_BUFF_DSC buffer_dsc_alt = NULL;

        /* Check for valid bdt index */
        if(bdt_elem->len != (uint_16)UNINITIALISED_VAL)
        {
            /* Does MCU owns it */
            if(buffer_dsc->Stat.SieCtlBit.own == FALSE)
            {
                if(size == 0)
                {
                    /*
                       Give control to the other buffer to recv the next
                       packet
                    */
                    buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index];
                    buffer_dsc_alt->cnt = SWAP16(bdt_elem->len);
                    buffer_dsc_alt->addr = SWAP32(bdt_elem->addr);

                    /* Give the ownership to SIE and TOGGLE DATA BIT */
                    buffer_dsc_alt->Stat._byte = (uint_8)(
                        (buffer_dsc_alt->Stat.McuCtlBit.data << 6) |
                        _SIE | _DTS);
                    return USB_OK;
                }
                /* adjust size based on the input at the init endpoint */
#ifdef LONG_RECEIVE_TRANSACTION
                /* Initialise transfer */
                bdt_elem->app_len = (uint_16)size;
                bdt_elem->app_buffer = buffer_ptr;
#endif
                if(size > bdt_elem->len)
                {
                    size = bdt_elem->len;
                }

#ifdef LONG_RECEIVE_TRANSACTION
                bdt_elem->curr_offset = 0;
#endif
                buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index];
                buffer_dsc_alt->cnt = SWAP16(size);
                buffer_dsc_alt->addr = SWAP32((uint_32)buffer_ptr);
                buffer_dsc_alt->Stat._byte = (uint_8)(
                    (buffer_dsc_alt->Stat.McuCtlBit.data << 6) |
                    _SIE | _DTS);
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
 * @brief The function configures Controller to send data on an SEND endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param buffer_ptr      : Application buffer pointer
 * @param size            : Size of the buffer
 *
 * @return status
 *         USB_OK           : When successfull
 *         USBERR_TX_FAILED : When unsuccessfull
 ******************************************************************************
 * This function configures Controller to send data on an SEND endpoint by
 * setting the BDT to send data.
 *****************************************************************************/
uint_8 USB_DCI_Send_Data (
    _usb_device_handle    handle,           /* [IN] USB Device handle */
    uint_8                endpoint_number,  /* [IN] Endpoint number of the transaction */
    uchar_ptr             buffer_ptr,       /* [IN] Pointer to the buffer to send */
    uint_32               size              /* [IN] Number of bytes to send */
)
{
    UNUSED(handle)
    uint_8 status = USBERR_TX_FAILED;
    P_BUFF_DSC buffer_dsc;

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_SEND,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];

    if(bdt_index == INVALID_BDT_INDEX)
        return USBERR_TX_FAILED;

    /* Send Data After Toggling Buffer */
    bdt_index = (uint_8)bdt_elem->bdtmap_index;

    buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];
    /* Does MCU owns it and it is not stalled */
    if(!((buffer_dsc->Stat.SieCtlBit.own) ||/* For MCU: own is 0 */
       (*(&ENDPT0 + (endpoint_number * 4)) & ENDPT_EP_STALL_MASK)))
    {
        /* Now configure buffer_dsc->addr and buffer_dsc->cnt */
#ifdef LONG_SEND_TRANSACTION
        /* Initialise transfer */
        bdt_elem->app_len = (uint_16)size;
        bdt_elem->app_buffer = buffer_ptr;
        bdt_elem->curr_offset = 0;

        /* prepare for send */
        USB_DCI_Prepare_Send_Data(buffer_dsc, bdt_elem);
#else
        buffer_dsc->addr = SWAP32(buff_ptr);

        /* adjust size based on the input at the init endpoint */
        if((uint_16)size > bdt_elem->len)
        {
            buffer_dsc->cnt = SWAP16(bdt_elem->len);
        }
        else
        {
            buffer_dsc->cnt = SWAP16((uint_16)size);
        }
#endif
        if(endpoint_number == CONTROL_ENDPOINT)
        {
            /* Set up the control endpoint bdt for next packet */
            buffer_dsc->Stat._byte = (_SIE | _DATA1 | _DTS);
        }
        else
        {
            buffer_dsc->Stat._byte = (uint_8)(
                (buffer_dsc->Stat.McuCtlBit.data << 6) |
                _SIE | _DTS);
        }

        status = USB_OK;
    } /* Does MCU own IN BDT */
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Set_Address
 *
 * @brief The function configures Controller to send data on an SEND endpoint
 *
 * @param handle  : USB Device handle
 * @param address : Controller Address
 *
 * @return None
 *
 ******************************************************************************
 * Assigns the Address to the Controller
 *****************************************************************************/
void  USB_DCI_Set_Address (
    _usb_device_handle    handle,    /* [IN] USB Device handle */
    uint_8                address    /* [IN] Address of the USB device */
)
{
    UNUSED(handle)
    /* set the address */
    ADDR = address;

    _usb_device_set_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
        USB_STATE_ADDRESS);
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Shutdown
 *
 * @brief The function shuts down the controller
 *
 * @param handle : USB Device handle
 *
 * @return None
 *
 ******************************************************************************
 * Resets USB Device Controller
 *****************************************************************************/
void USB_DCI_Shutdown (
    _usb_device_handle    handle    /* [IN] USB Device handle */
)
{
    UNUSED(handle)
    /* Reset the Control Register */
    CTL = 0;
    /* Initiate Reset in the USB Control0 Register */
  #ifndef OTG_BUILD

    USBTRC0 = _USBRESET;
  #endif

    _usb_device_set_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
        USB_STATE_UNKNOWN);
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_DCI_Assert_Resume
 *
 * @brief The function makes the Controller start USB RESUME signaling
 *
 * @param handle : USB Device handle
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
    _usb_device_handle    handle    /* [IN] USB Device handle */
)
{
    UNUSED(handle)
    uint_16 delay_count;

    /* Clear SUSP Bit from USB_CTRL */
    USB_CTRL_SUSP = 0;

    /* Reset Low Power RESUME enable */
    USBTRC0_USBRESMEN = 0;

    USB_DCI_WAKEUP

    CTL_RESUME = 1;   /* Start RESUME signaling and make SUSPEND bit 0*/

    delay_count = ASSERT_RESUME_DELAY_COUNT; /* Set RESUME line for 1-15 ms*/

    do
    {
       delay_count--;
       __RESET_WATCHDOG();    /* Reset the COP */
    }while(delay_count);

    CTL_RESUME = 0;          /* Stop RESUME signalling */

    return;
}

/**************************************************************************//*!
 *
 * @name  USB_Bus_Token_Cpl_Handler
 *
 * @brief The function handles Token Complete USB interrupts on the bus.
 *
 * @param stat  : BDT stat byte
 * @param event : Pointer to USB EVENT Structure
 *
 * @return None
 ******************************************************************************
 * This function handles Token Complete USB interrupts on the bus.
 *****************************************************************************/
void USB_Bus_Token_Cpl_Handler (
    uint_8 stat,            /* [IN] Value of STAT register */
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
)
{
    uint_8 bdt_index = 0 ;
    P_BUFF_DSC buffer_dsc = NULL;
    P_BUFF_DSC buffer_dsc_alt = NULL;/* stores data of alternate buffer */
    P_BDT_ELEM bdt_elem = NULL;
    boolean odd = (boolean)((stat & 0x04) >> 2);

    /* Get the direction from STAT register */
    event->direction = (uint_8)((stat & ENDPOINT_DIRECTION_MASK) >>
        ENDPOINT_DIRECTION_SHIFT);


    /* Get bdt index corresponding to endpoint number and direction */
    bdt_index = USB_DCI_Get_BDT_Index(event->ep_num,event->direction, odd);

    buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];
    buffer_dsc_alt = &g_bdtmap->ep_dsc[bdt_index ^ 1];

    bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];

    /* Get address from BDT */
    event->buffer_ptr = (uint_8_ptr)SWAP32(buffer_dsc->addr);

    /* Get len from BDT */
    event->len = SWAP16(buffer_dsc->cnt);

    /* Prepare for Next USB Transaction */
    bdt_index = (uint_8)(bdt_elem->bdtmap_index ^ 1);
    bdt_elem->bdtmap_index = bdt_index;

    /* Toggle Data PID*/
    buffer_dsc_alt->Stat._byte = (uint_8)((buffer_dsc->Stat.McuCtlBit.data ^ 1) << 6);

    if(event->direction == USB_SEND)
    {
        if(event->ep_num == CONTROL_ENDPOINT)
        {
            /* for Control Endpoint */
            /* For Transfer Direction Host to Device */
            if(g_trf_direction == USB_RECV)
            {
                /*
                   Enters here for first time after Set_Address TRANSFER
                   Completed
                */
                /* make Transfer Direction UNKNOWN */
                g_trf_direction = USB_TRF_UNKNOWN;
                /* Cancel any pending Transfers on RECV Control Endpoint*/
                USB_DCI_Cancel_Transfer(&(event->controller_ID), CONTROL_ENDPOINT,
                  USB_RECV);
                /* We Require DATA0 PID for Setup Token */
                buffer_dsc_alt->Stat._byte = _DATA0;
                /* Prepare for Next SETUP PACKET Receive */
                USB_DCI_Recv_Data(&(event->controller_ID),
                    CONTROL_ENDPOINT,
                    NULL,0);

            }
        }/* ep_num is CONTROL ENDPOINT */

#ifdef LONG_SEND_TRANSACTION
        if( (g_trf_direction == USB_SEND) ||
            (event->ep_num != CONTROL_ENDPOINT) )
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
                USB_DCI_Prepare_Send_Data(buffer_dsc_alt, bdt_elem);

                /* give the ownership to SIE and TOGGLE DATA BIT */
                buffer_dsc_alt->Stat._byte = (uint_8)(
                    ((buffer_dsc_alt->Stat.McuCtlBit.data) << 6) |
                    _SIE | _DTS);;
                return;
            }
            else
            {
                event->buffer_ptr = bdt_elem->app_buffer;
                event->len = bdt_elem->curr_offset;
            }
        }
#endif
    }/* End of SEND loop */
    else /* direction IS USB_RECV */
    {
        if(event->ep_num == CONTROL_ENDPOINT)
        {
            /* for Control Endpoint */
            if(buffer_dsc->Stat.RecPid.pid == USB_SETUP_TOKEN)
            {
                /* set setup phase */
                event->setup = TRUE;
                /* Transfer direction of next packet */
                g_trf_direction = (uint_8)((uint_8)
                    (event->buffer_ptr[0]) >> 7);
            }
            else if(g_trf_direction == USB_SEND)
            {
                /* make Transfer Direction UNKNOWN */
                g_trf_direction = USB_TRF_UNKNOWN;
                /* Cancel any pending Transfers on SEND Control Endpoint*/
                USB_DCI_Cancel_Transfer(&(event->controller_ID), CONTROL_ENDPOINT,
                  USB_SEND);
                /* We Require DATA0 PID for Setup Token */
                buffer_dsc_alt->Stat._byte = _DATA0;
                /* Prepare for Next SETUP PACKET Receive */
                USB_DCI_Recv_Data(&(event->controller_ID),
                    CONTROL_ENDPOINT,
                    NULL,0);
            }
        }   /* ep_num is CONTROL ENDPOINT */

#ifdef LONG_RECEIVE_TRANSACTION
        /* For NON CONTROL ENDPOINT only */
        if(bdt_elem->app_len != (USB_PACKET_SIZE)UNINITIALISED_VAL)
        {
            /* on control endpoint the data is only 8 bytes */
            USB_PACKET_SIZE size = event->len;
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
                uint_16 count;
                count = (uint_16)(((bdt_elem->app_len - bdt_elem->curr_offset)
                    > bdt_elem->len) ? bdt_elem->len :
                    (bdt_elem->app_len - bdt_elem->curr_offset));
				if(count == 0)
				{
            		/* For Zero byte Packet Receive */
					buffer_dsc_alt->addr = SWAP32(bdt_elem->addr);
				    buffer_dsc_alt->cnt = 0;
				}
				else
				{
                    buffer_dsc_alt->addr = SWAP32(
                        (uint_32)&bdt_elem->app_buffer[bdt_elem->curr_offset]);
				    buffer_dsc_alt->cnt = SWAP16(count);
				}

                /* give the ownership to SIE and Toggle DATA bit*/
                buffer_dsc_alt->Stat._byte = (uint_8)((
                    (buffer_dsc_alt->Stat.McuCtlBit.data) << 6) |
                    _SIE | _DTS);
                return;
            }
            else /* request completed */
            {
                /* populate buffer structure */
                event->buffer_ptr = bdt_elem->app_buffer;
                event->len = bdt_elem->curr_offset;
                bdt_elem->app_len = (USB_PACKET_SIZE)UNINITIALISED_VAL;
            }
        }
#endif
    } /* End of RECV loop */

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
 * This function is hooked onto interrupt 69 and handles the USB interrupts.
 * After handling the interrupt it calls the Device Layer to notify it about
 * the event.
 *****************************************************************************/

#if 0
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
extern volatile uint_8 usb_int_disable;
extern volatile uint_8 usb_int_en_copy;
#define Vector_Vusb 67
#endif
#else /* << EST */
%if (CPUDevice="MCF51MM256") | (CPUDevice="MCF51JE256")
#include "%'ModuleName'.h"
%endif
#endif

#if 0 /* << EST */
#ifndef OTG_BUILD
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
void interrupt Vector_Vusb USB_ISR(void)
#else
void interrupt VectorNumber_Vusb USB_ISR(void)
#endif
#else
void USB_ISR(void)
#endif
#else
__interrupt void USB_ISR(void)
#endif
{

    /* Which interrupt occured and also was enabled */
    uint_8 intr_stat = (uint_8)(INT_STAT & INT_ENB);
    uint_8 stat = (uint_8)STAT;

    USB_DEV_EVENT_STRUCT event;
    uint_8 dev_state = USB_STATUS_UNKNOWN;

#if 0
    #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)

     if(usb_int_disable)
     {
       usb_int_en_copy = INT_ENB;
       INT_ENB = 0;
       return;
     }

    #endif
#else /* << EST */
    /* device is %CPUDevice << EST */
    %if (CPUDevice="MCF51MM256") | (CPUDevice="MCF51JE256")
    if (%'ModuleName'%.usb_int_disable) {
      %'ModuleName'%.usb_int_en_copy = INT_ENB;
      INT_ENB = 0;
      return;
    }
    %endif
#endif
    /* initialise event structure */
    event.controller_ID = g_dci_controller_Id;
    event.setup = FALSE;
    event.buffer_ptr = NULL;
    event.len = 0;
    event.direction = USB_RECV;
    event.errors = NO_ERRORS;

    event.ep_num = (uint_8)UNINITIALISED_VAL;

    /* Get the device state from the Device Layer */
    (void)_usb_device_get_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
        &dev_state);

    /* if current device state is SUSPEND and Low Power Resume Flag set */
    if((USBTRC0_USB_RESUME_INT == 1) && (dev_state == USB_STATE_SUSPEND))
    {
        /* Clear SUSP Bit from USB_CTRL */
        USB_CTRL_SUSP = 0;

        /* Reset Low Power RESUME enable */
        USBTRC0_USBRESMEN = 0;
    }

    if(SOF_TOKEN_FLAG(intr_stat))
    {
        uint_16 sof_count;
        /* Clear SOF Interrupt */
        INT_STAT = INT_STAT_SOF_TOK_MASK;
        sof_count = (uint_16)((FRM_NUMH << FRAME_HIGH_BYTE_SHIFT) | FRM_NUML);
        /*address of Lower byte of Frame number*/
        event.buffer_ptr = (uint_8_ptr)(&sof_count);
        /* Notify Device Layer of SOF Event */
        (void)USB_Device_Call_Service(USB_SERVICE_SOF, &event);
    }

    if(BUS_RESET_FLAG(intr_stat))
    {
        /* Clear Reset Flag */
        INT_STAT = INT_STAT_USB_RST_MASK;

        /* Handle RESET Interrupt */
        USB_Bus_Reset_Handler();

        /* Notify Device Layer of RESET Event */
        (void)USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        CTL_TXSUSPEND_TOKENBUSY = 0;

        /* No need to process other interrupts */
        return;
    }

    if(TOKEN_COMPL_FLAG(intr_stat))
    {
        /* Clear TOKEN Interrupt */
        INT_STAT = INT_STAT_TOK_DNE_MASK;

        event.ep_num = (uint_8)((stat & ENDPOINT_NUMBER_MASK) >>
            ENDPOINT_NUMBER_SHIFT);
        USB_Bus_Token_Cpl_Handler(stat, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        CTL_TXSUSPEND_TOKENBUSY = 0;
    }

    if(ERROR_FLAG(intr_stat))
    {
        /* Clear ERROR Interrupt */
        INT_STAT = INT_STAT_ERROR_MASK;

        event.errors = (uint_8)(ERR_STAT & ERR_ENB);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);

        ERR_STAT = ERR_STAT_CLEAR_ALL; /*clear all errors*/
        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        CTL_TXSUSPEND_TOKENBUSY = 0;
    }

    if(SLEEP_FLAG(intr_stat))
    {
        /* Clear RESUME Interrupt if Pending */
        INT_STAT = INT_STAT_RESUME_MASK;

        /* Clear SLEEP Interrupt */
        INT_STAT = INT_STAT_SLEEP_MASK;

        /* Notify Device Layer of SLEEP Event */
        (void)USB_Device_Call_Service(USB_SERVICE_SLEEP, &event);

        /* Set Low Power RESUME enable */
        USBTRC0_USBRESMEN = 1;

        /* Set SUSP Bit in USB_CTRL */
        USB_CTRL_SUSP = 1;

        /* Enable RESUME Interrupt */
        INT_ENB_RESUME_EN = 1;
#ifdef USB_LOWPOWERMODE
        /* Enter Stop3 Mode*/
        Enter_StopMode(STOP_MODE3);
#endif
    }

    if(RESUME_FLAG(intr_stat))
    {
        /* Clear RESUME Interrupt */
        INT_STAT = INT_STAT_RESUME_MASK;

        /* Notify Device Layer of RESUME Event */
        (void)USB_Device_Call_Service(USB_SERVICE_RESUME, &event);

        /* Disable RESUME Interrupt */
        INT_ENB_RESUME_EN = 0;
    }

    if(STALL_FLAG(intr_stat))
    {
        uint_8 endp_status;
        event.ep_num = (uint_8)UNINITIALISED_VAL;

        /* If Control Endpoint is stalled then unstall it.
        For other endpoints host issues clear endpoint feature request
        to unstall them */

        /* Get Control Endpoint Status*/
        (void)_usb_device_get_status(&(event.controller_ID),
            (USB_STATUS_ENDPOINT|CONTROL_ENDPOINT),
            &endp_status);
        if(endp_status == USB_STATUS_STALLED)
        {
            event.ep_num = CONTROL_ENDPOINT;
            event.direction = USB_SEND;
        }

        /* Clear STALL Interrupt */
        INT_STAT = INT_STAT_STALL_MASK;

        /* Notify Device Layer of STALL Event */
        (void)USB_Device_Call_Service(USB_SERVICE_STALL, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        CTL_TXSUSPEND_TOKENBUSY = 0;
    }

    return;
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
void Clear_Mem (
    uint_8_ptr start_addr,  /* [OUT] Buffer Start address */
    uint_32 count,          /* [IN] Count of Bytes */
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
            /*
               We enter Default Stop Mode
            */
            break;
        case STOP_MODE2:
            /* Save IO Pin Status in a global variable
                IO Pin Status is to be restored at POR.
                Check if PPDC
            */
            /* Set PPDC */
            break;
        case STOP_MODE3:
            /* Clear PPDC */
            SPMSC2_PPDC = 0;
            /* Disable Low Voltage Detect */
            SPMSC1_LVDSE = 0;
            break;
        case STOP_MODE4:
            break;
    }
    /* Enter STOP Mode*/
    _Stop;
}

#endif
