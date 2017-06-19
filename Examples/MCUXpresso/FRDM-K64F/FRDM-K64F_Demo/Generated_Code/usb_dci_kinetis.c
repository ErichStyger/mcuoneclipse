/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2012 Freescale Semiconductor, Inc.
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
 * @file usb_dci_kinetis.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains Kinetis USB stack controller layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>
#include "usb_dciapi.h" /* USB DCI API Header File */
#include "usb_devapi.h" /* USB Device API Header File */
#include "usb_dci_kinetis.h"    /* USB DCI Header File */
#include "usb_bdt_kinetis.h"    /* USB BDT Structure Header File */
#include "wdt_kinetis.h"
#include "usb_class.h"

/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/
/****************************************************************************
 * Global Variables
 ****************************************************************************/
#ifdef USE_FEEDBACK_ENDPOINT
	extern uint_32 feedback_data;
	extern uint_32 gNrSamples;
#endif

/* location for BDT Table and buff */
#if (defined(__CWCC__)||defined(__GNUC__))
	__attribute__((__aligned__(512)))
#elif defined(__IAR_SYSTEMS_ICC__)
	#pragma data_alignment = 512
#endif

#if !HIGH_SPEED_DEVICE
	#if defined __CC_ARM
	  __align(512) uint_8 g_Mem[BYTES_1024];
	#else
#if 0 
		static uint_8 g_Mem[BYTES_1024];
#else
		uint_8 g_Mem[BYTES_1024];
#endif
	#endif
	/* Pointer to BDT Map Structure */
	BDTMAP *g_bdtmap = NULL;
	/* per endpoint per direction bdt index structure */
	static BDT_ELEM  g_bdt_elem[MAX_BDT_INDEX >> 1];
#endif
/* stores Controller ID */
static uint_8 g_dci_controller_Id = 0;
#if HIGH_SPEED_DEVICE
static uint_8 g_dci_address_state = 0;
#endif /* HIGH_SPEED_DEVICE */

#if !HIGH_SPEED_DEVICE
/* Start BDT buffer Address */
static uint_32 g_bdt_address;
#endif /* HIGH_SPEED_DEVICE */
/* Transfer direction */
static uint_8 g_trf_direction = USB_TRF_UNKNOWN;


// HIGH_SPEED_DEVICE
#if HIGH_SPEED_DEVICE
	#define MAX_DTDS_PER_EP     5	// maximum number of transfer descriptors
	#define DTD_FREE            0
	#define DTD_BUSY            1
	#define MAX_ENDPOINT_NUMBER 4

	// QH structures are 64-byte aligned
	#define TOTAL_QHD_SIZE (SIZE_OF_QHD * (MAX_ENDPOINT_NUMBER * 2))
	// TD structures are 64-byte aligned
	#define TOTAL_QTD_SIZE ((SIZE_OF_DTD0) * (MAX_ENDPOINT_NUMBER * 2) * MAX_DTDS_PER_EP)

	#ifdef __CWCC__
		#pragma define_section usb_dqh ".usb_dqh" RW
		__declspec(usb_dqh) uint_8 g_usbd_qh_buf[TOTAL_QHD_SIZE];	// 512
		#pragma define_section usb_dtd ".usb_dtd" RW
		__declspec(usb_dtd) uint_8 g_usbd_td_buf[TOTAL_QTD_SIZE];	// 1280
	#else
		#pragma data_alignment=(0x1000)
		uint_8 g_usbd_qh_buf[TOTAL_QHD_SIZE];	// 512
		#pragma data_alignment=(0x800)
		uint_8 g_usbd_td_buf[TOTAL_QTD_SIZE];	// 1280
	#endif


	/* flag status for td */
	static struct _td_status
	{
		uint_8  status;                 // DTD_BUSY or DTD_FREE
		unsigned int total_bytes;       // Original total bytes to transfer (not used by EP0)
		volatile struct dtd_setup_t *phys_td;   // Pointer to physical TD (not used by EP0)
	} g_usbd_td_flag[MAX_ENDPOINT_NUMBER * 2][MAX_DTDS_PER_EP];
	static struct dtd_setup_t *g_usbd_qh_tail[MAX_ENDPOINT_NUMBER * 2];
#endif // HIGH_SPEED_DEVICE

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_Bus_Reset_Handler(void);
#if !HIGH_SPEED_DEVICE
static uint_8 USB_DCI_Get_BDT_Index(uint_8 ep_num,
                                    uint_8 direction,
                                    boolean odd);
static uint_8 USB_DCI_Validate_Param(uint_8 ep_num,
                                    uint_8 direction,
                                    boolean odd);
#ifdef LONG_SEND_TRANSACTION
static void USB_DCI_Prepare_Send_Data(P_BUFF_DSC buffer_dsc,
                                    P_BDT_ELEM bdt_elem);
#endif /* LONG_SEND_TRANSACTION */
static void USB_Bus_Token_Cpl_Handler(uint_8 stat,
                                    USB_DEV_EVENT_STRUCT* event);
#endif /* HIGH_SPEED_DEVICE */

// HIGH_SPEED_DEVICE
#if HIGH_SPEED_DEVICE
static uint_8 K70_ULPI_SetDeviceMode(uint_8 controller_ID);
static void usbd_ep_qh_init(uint_8 controller_ID,
		unsigned char endpt_number, unsigned char direction,
		unsigned int max_pkt_len,
		unsigned int zlt, unsigned char mult, uint_32 next_dtd);
static void usbd_setup_qhead(struct dqh_t *qhead);
static void usbd_setup_td(struct dtd_t *td);
static unsigned int usbd_get_dqh(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction);
static void usbd_ep_setup(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned char ep_type);
static void usbd_ep_complete_handler(
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
);
static void usbd_setup_packet_handler(
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
);
static void usbd_read_setup_packet(uint_8 controller_ID, unsigned char *setup_packet);
static void usbd_port_change(
		USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
);
static void usbd_ep0_complete(USB_DEV_EVENT_STRUCT* event);
static void usbd_dtd_complete(USB_DEV_EVENT_STRUCT* event);
static usb_status_t usbd_receive_data_ep0out(uint_8 controller_ID, unsigned int ep0_data_buffer, unsigned int sz);
static usb_status_t usbd_receive_data_epxout(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz);
static void usbd_add_td(uint_8 controller_ID, unsigned char ep_num, unsigned char direction, struct dtd_t *td);
static void usbd_prime_ep(uint_8 controller_ID, unsigned char ep_num, unsigned char direction, struct dtd_t *td);
static usb_status_t usbd_send_data_epxin(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz);
static usb_status_t usbd_send_data_ep0in(uint_8 controller_ID,
                                         unsigned int ep0_data_buffer, unsigned int sz,
                                         unsigned char zlt_enable);

#endif
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
#if !HIGH_SPEED_DEVICE
	USB0_ERRSTAT = ERR_STAT_CLEAR_ALL;  /* clear USB error flag */
	USB0_CTL |= USB_CTL_ODDRST_MASK;                /* Reset to Even buffer */
	USB0_ADDR = 0;                       /* reset to default address */
	/* Select System Clock and Disable Weak Pull Downs */
	USB0_USBCTRL = 0x00;

	/* Clear bdt elem structure */
	Clear_Mem((uint_8_ptr)(g_bdt_elem),
			(sizeof(BDT_ELEM) * (MAX_BDT_INDEX >> 1)),
			(uint_8)UNINITIALISED_VAL);

	/* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap,(uint_32) BYTES_1024, (uint_8)0);

	/* Initialize BDT buffer address */
	g_bdt_address = ((uint_32)g_bdtmap + BYTES_512);

	g_trf_direction = USB_TRF_UNKNOWN;

	USB0_CTL &= ~USB_CTL_ODDRST_MASK;
	USB0_USBTRC0 |= 0x40;             /* attach CFv1 core to USB bus */

	USB0_ERREN = ERR_ENB_ENABLE_ALL;   /* Enable All Error Interrupts */
	USB0_INTEN = INTENB_BUS_RESET_VAL; /* Enable All Interrupts except RESUME */
	USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;

#else
	uint_32 reg;

	//Clear the device address
	USBHS_DEVICEADDR &= ~USBHS_DEVICEADDR_USBADR_MASK;

	// 1. Clear all setup token semaphores
	reg = USBHS_EPSETUPSR;
	USBHS_EPSETUPSR = reg;

	// 2. Clear all the endpoint complete status bits
	reg = USBHS_EPCOMPLETE;
	USBHS_EPCOMPLETE = reg;

	// 3. Cancel all primed status
	while(USBHS_EPPRIME);
	USBHS_EPFLUSH = 0xffffffff;

	// 4. If reset bit is not cleared at this point force reset device
	if(!(USBHS_PORTSC1 & USBHS_PORTSC1_PR_MASK)){
		USBHS_USBCMD |= USBHS_USBCMD_RST_MASK;
	}

	// 5. Free(reset) all allocated dTDs
	memset(g_usbd_td_buf, 0, TOTAL_QTD_SIZE);
	memset(g_usbd_td_flag,
			0,
			MAX_ENDPOINT_NUMBER * 2 * MAX_DTDS_PER_EP * sizeof(g_usbd_td_flag)/sizeof(*g_usbd_td_flag)
			);

	g_trf_direction = USB_TRF_UNKNOWN;
    UNUSED(g_trf_direction);
#endif
}

#if !HIGH_SPEED_DEVICE
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
 *         INVALID_BDT_INDEX : In case of error
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
#endif /* HIGH_SPEED_DEVICE */

#ifdef LONG_SEND_TRANSACTION
#if !HIGH_SPEED_DEVICE
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
#endif /* HIGH_SPEED_DEVICE */
#endif /* LONG_SEND_TRANSACTION */

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
#if !HIGH_SPEED_DEVICE
#if USB_USER_CONFIG_USE_STACK_INIT
	/* Select System Clock and Disable Weak Pull Downs */
	USB0_USBCTRL = 0x00;
#endif
	
	/* save the controller_ID for future use */
    g_dci_controller_Id = controller_ID;

    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)(g_bdt_elem),
       (sizeof(BDT_ELEM) * (MAX_BDT_INDEX >> 1)),
       (uint_8)UNINITIALISED_VAL);
    g_bdtmap = (BDTMAP *)((uint_32)g_Mem);

    /* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap,(uint_32) BYTES_1024, (uint_8)0);

    #ifndef OTG_BUILD
    #if 1   /* hardware bug workaround */ /* << EST: need to keep this workaround for FRDM-KL25Z */
    /* Hard Reset to the USB Module */
    USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;

    /* loop till the Reset bit clears  */
    while((USB0_USBTRC0 & USB_USBTRC0_USBRESET_MASK))
    {
    };
    #if !USB_USER_CONFIG_USE_STACK_INIT
    {
      /* need to re-init USB, as the hard reset above has reset the whole module! */
      void USB0_Init(void); /* prototype */
      USB0_Init(); /* call Processor Expert Init_USB_OTG Init() */
    }
    #endif

    #endif
    #endif

    g_trf_direction = USB_TRF_UNKNOWN;

#if USB_USER_CONFIG_USE_STACK_INIT
    /* Asynchronous Resume Interrupt Enable */
    USB0_USBTRC0 |= 0x40; /* undocumented bit???? */
#endif
    if(bVregEn)
    {
    	SIM_SOPT1 |= SIM_SOPT1_USBREGEN_MASK;	// enable usb voltage regulator
    }
    else
    {
    	SIM_SOPT1 &= ~SIM_SOPT1_USBREGEN_MASK;	// disable usb voltage regulator
    }

    /* Set the BDT Table address, Need to be on 512 byte boundary */
    /* D8 Bit is masked in BDT_PAGE_01 */
    USB0_BDTPAGE1 = (uint_8)(((uint_32)g_bdtmap >> 8)& 0xFE);
    USB0_BDTPAGE2 = (uint_8)((uint_32)g_bdtmap >> 16);
    USB0_BDTPAGE3 = (uint_8)((uint_32)g_bdtmap >> 24);

    /* Initialized BDT buffer address */
    g_bdt_address = ((uint_32)g_bdtmap + BYTES_512);

#if USB_USER_CONFIG_USE_STACK_INIT
    #ifndef OTG_BUILD
     /* Pull Up configuration */
    USB0_CONTROL = USB_CONTROL_DPPULLUPNONOTG_MASK;
    #endif
#endif
    USB0_CTL = USB_CTL_USBENSOFEN_MASK; 	/* Enable USB module */
    USB0_ISTAT = INT_STAT_CLEAR_ALL;      	/* Clear USB interrupts*/

    /* Remove suspend state */
    USB0_USBCTRL &= ~USB_USBCTRL_SUSP_MASK;

#if USB_USER_CONFIG_USE_STACK_INIT
    /* Enable USB RESET Interrupt */
    USB0_INTEN |= USB_INTEN_USBRSTEN_MASK;

    /* Enable USB Sleep Interrupt */
    USB0_INTEN |= USB_INTEN_SLEEPEN_MASK;

    USB0_OTGCTL = USB_OTGCTL_DPHIGH_MASK | USB_OTGCTL_OTGEN_MASK;
#endif /* USB_USER_CONFIG_USE_STACK_INIT */
#else	// HIGH_SPEED_DEVICE
    /* save the controller_ID for future use */
    g_dci_controller_Id = controller_ID;
    memset(g_usbd_qh_buf, 0, TOTAL_QHD_SIZE);
    memset(g_usbd_td_buf, 0, TOTAL_QTD_SIZE);

    // initialize module in device mode
    uint_8 status;
    status = K70_ULPI_SetDeviceMode(controller_ID);
    if (status != USB_OK)
    	return status;

    // initialize endpoint 0
    usbd_ep_qh_init(controller_ID, EP0, IN, 64, 0, 0, 1);
    usbd_ep_qh_init(controller_ID, EP0, OUT, 64, 0, 0, 1);

    // setup interrupts
    USBHS_USBINTR = USBHS_USBINTR_UE_MASK	// USB interrupt
    		| USBHS_USBINTR_UEE_MASK		// USB error
    		| USBHS_USBINTR_PCE_MASK		// Port change
    		| USBHS_USBINTR_URE_MASK		// Reset enable
    		| USBHS_USBINTR_SRE_MASK		// SOF received
    		| USBHS_USBINTR_SLE_MASK		// suspend received
    		| USBHS_USBINTR_SEE_MASK;		// System error

    // enable pullup on DP and initiate attach event
    USBHS_USBCMD |= USBHS_USBCMD_RS_MASK;
#endif
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
#if !HIGH_SPEED_DEVICE

#ifdef MCU_MK70F12
#if 0 /* hardware bug workaround */
	// Reset module
	USB0_USBTRC0 |= USB_USBTRC0_USBRESET_MASK;

	// Wait for reset to complete
	while((USB0_USBTRC0 & USB_USBTRC0_USBRESET_MASK));
#endif
	
#else
	/* Detach CFv1 core to USB bus*/
	USB0_USBTRC0 &= ~0x40;
#endif


	/* Clear USB interrupts*/
	USB0_ISTAT = INT_STAT_CLEAR_ALL;

	/* Disable USB RESET Interrupt */
	USB0_INTEN &= ~USB_INTEN_USBRSTEN_MASK;

    /* Disable USB module */
	USB0_CTL &= ~USB_CTL_USBENSOFEN_MASK;

    USB0_OTGCTL &= ~(USB_OTGCTL_DPHIGH_MASK | USB_OTGCTL_OTGEN_MASK);
#else	// HIGH_SPEED_DEVICE

#endif
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
#if !HIGH_SPEED_DEVICE
    uint_8 bdtmap_index;
    uint_8 bdtelem_index;
    uint_8 ep_num = ep_ptr->ep_num;
    uint_8 direction = ep_ptr->direction;
    uint_32 ep_ctrl[2] = {EP_OUT, EP_IN};
    P_BUFF_DSC temp;
    P_BDT_ELEM bdt_elem;
    UNUSED(controller_ID);

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
    temp = &g_bdtmap->ep_dsc[(uint8_t)((bdt_elem->bdtmap_index) ^ 1)];

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
    *((&USB0_ENDPT0) + (4 * ep_num)) |= ep_ctrl[direction];
#else	/* HIGH_SPEED_DEVICE */
    unsigned char mult;

    /* No need to initialize EP0 */
    if (ep_ptr->ep_num == CONTROL_ENDPOINT)
    	return USB_OK;

    switch (ep_ptr->type & 0x3) {
		case EP_TRANSFER_TYPE_CONTROL:
		case EP_TRANSFER_TYPE_BULK:
		case EP_TRANSFER_TYPE_INTERRUPT:
			mult = 0;
			break;
		case EP_TRANSFER_TYPE_ISOCHRONOUS:
			/* Calculate the ISO transfer High-Bandwidth Pipe Multiplier
			 * The ISO endpoints, must set Mult 1, 2, 3 for high speed
			 * and only 1 for full speed
			 */
#ifdef ULPI_FORCE_FULLSPEED
			mult = 1;
#else
			mult = (unsigned char)(1 + (((ep_ptr->size) >> 11) & 0x03));
#endif
    }

    /* setup dQH */
    usbd_ep_qh_init(controller_ID, ep_ptr->ep_num, ep_ptr->direction, ep_ptr->size, flag, mult, 0xDEAD0001);

    /* enable endpoint */
    usbd_ep_setup(controller_ID, ep_ptr->ep_num, ep_ptr->direction, ep_ptr->type);
#endif /* HIGH_SPEED_DEVICE */
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
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number */
    uint_8                direction           /* [IN] Endpoint direction */
)
{
#if !HIGH_SPEED_DEVICE
#ifdef LONG_TRANSACTION
    uint_8 status= USBERR_UNKNOWN_ERROR;

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);
    uint_8 bdtelem_index = (uint_8)TRANSFER_INDEX(bdt_index);
    UNUSED(handle);

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
#else	// HIGH_SPEED_DEVICE
#ifdef USART_DEBUG
    printf("%s\n", __func__);
#endif
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
#if !HIGH_SPEED_DEVICE
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (ep_num, direction,
        USB_RAM_EVEN_BUFFER);
    uint_8 bdtelem_index = (uint_8)TRANSFER_INDEX(bdt_index);

    /* in case the bdt_index is invalid*/
    if(bdt_index  == INVALID_BDT_INDEX)
    {
        return USBERR_EP_DEINIT_FAILED;
    }
    USB_DCI_Cancel_Transfer(&controller_ID, ep_num, direction);
    /* delete buffer space for both even and odd buffers */
    g_bdt_address -= (g_bdt_elem[bdtelem_index].len);

    /* Disable endpoint */
    *((&USB0_ENDPT0) + (4 * ep_num)) = EP_DISABLE;

    /* un-initialize the bdt_elem structure for this endpoint */
    g_bdt_elem[bdtelem_index].len = (uint_16)UNINITIALISED_VAL;
    g_bdt_elem[bdtelem_index].addr = (uint_32)UNINITIALISED_VAL;
#else	// HIGH SPEED
    uint_32 reg;

    if(ep_num<1)
    	return USB_INVALID;

    // clear qhd
    dqh_setup_t *dqh_word = (dqh_setup_t*)usbd_get_dqh(controller_ID, ep_num, direction);
    memset((void *)dqh_word, 0, SIZE_OF_QHD);

    // clear endpoint register
    reg = USBHS_EPCR(ep_num-1);
    USBHS_EPCR(ep_num-1) &= ~reg;

    // flush endpoint Tx(IN) buffer
    if(direction)
    	USBHS_EPFLUSH |= USBHS_EPFLUSH_FETB(ep_num-1);
    // flush endpoint Rx(OUT) buffer
    else
    	USBHS_EPFLUSH |= USBHS_EPFLUSH_FERB(ep_num-1);
#endif
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
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number to stall */
    uint_8                direction           /* [IN] Direction to stall */
)
{
#if !HIGH_SPEED_DEVICE
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
#else	// HIGH SPEED
	// check if it is control endpoint
	if(endpoint_number == 0){
		// stall both directions
		USBHS_EPCR0 |= USBHS_EPCR0_TXS_MASK|USBHS_EPCR0_RXS_MASK;
	}else{

		USBHS_EPCR(endpoint_number-1) |= direction?USBHS_EPCR0_TXS_MASK:USBHS_EPCR0_RXS_MASK;
	}
#endif
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
    _usb_device_handle     handle,             /* [IN] USB Device handle */
    uint_8                 endpoint_number,    /* [IN] Endpoint number to unstall */
    uint_8                 direction           /* [IN] Direction to unstall */
)
{
#if !HIGH_SPEED_DEVICE
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];

    bdt_index = bdt_elem->bdtmap_index;

    /* Check for valid bdt index */
	if(bdt_index != INVALID_BDT_INDEX)
	{
        ENDPT0STR *endpoint = (ENDPT0STR*)(&USB0_ENDPT0 + (4 * endpoint_number));

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
#else
	// todo:
	// This function unstalls the endpoint by clearing Endpoint Control Register
	// and QH
	if(endpoint_number == 0){
			// unstall both directions
			USBHS_EPCR0 &= ~(direction ? USBHS_EPCR0_TXS_MASK:USBHS_EPCR0_RXS_MASK);
		}else{
			USBHS_EPCR(endpoint_number-1) &= ~(direction?USBHS_EPCR_TXS_MASK:USBHS_EPCR_RXS_MASK);
		}
#ifdef USART_DEBUG
	printf("%s\n", __func__);
#endif
#endif
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
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number for the transaction */
    uint_8_ptr            buffer_ptr          /* [IN] Pointer to the buffer into which to read data */
)
{

#if !HIGH_SPEED_DEVICE
	uint_8_ptr addr;
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_RECV,
        USB_RAM_EVEN_BUFFER);

    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];
    UNUSED(handle);
    bdt_index = bdt_elem->bdtmap_index;

    /* address correponding to the endpoint */
    addr = (uint_8_ptr)SWAP32(g_bdtmap->ep_dsc[bdt_index].addr);

    /* copy bdt buffer to application buffer */
    (void)memcpy(buffer_ptr, addr, USB_SETUP_PKT_SIZE);
    return;
#else	// HIGH SPEED
#if USART_DEBUG
    printf("%s\n", __func__);
#endif /* USART_DEBUG */
#endif
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
 *         USBERR_TR_FAILED                : When unsuccessful
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
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number */
    uint_8                direction           /* [IN] Endpoint direction */
)
{
    uint_8 status = USB_STATUS_DISABLED;

#if !HIGH_SPEED_DEVICE
    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, direction,
        USB_RAM_EVEN_BUFFER);
    UNUSED(handle);

    /* Check for valid bdt index */
	if(bdt_index != INVALID_BDT_INDEX)
    {
        uint_8 ep_control = (uint_8)(*((&USB0_ENDPT0)+4*endpoint_number));

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
#else
#if USART_DEBUG
    printf("%s, ep_num is %d\n", __func__, endpoint_number);
#endif /* USART_DEBUG */
    status = USB_OK;
#endif /* HIGH_SPEED_DEVICE */
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
    uint_8                endpoint_number,    /* [IN] Endpoint number */
    uint_8                direction           /* [IN] Endpoint direction */
)
{
	
#if !HIGH_SPEED_DEVICE
	
	uint_8 bdt_index = USB_DCI_Validate_Param(endpoint_number, direction, USB_RAM_EVEN_BUFFER);	
	P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];
		
	bdt_index = bdt_elem->bdtmap_index;
	
	/*Check for a valid bdt index */
	if (bdt_index != INVALID_BDT_INDEX)
	{
		//ENDPT0STR *endpoint = (ENDPT0STR*)(&USB0_ENDPT0 + (4 * endpoint_number)); /* << EST not used */
		g_bdtmap->ep_dsc[bdt_index].Stat._byte = _DATA0;
	}
    return;
#else	// HIGH SPEED
#ifdef USART_DEBUG
    printf("%s\n", __func__);
#endif
#endif
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
 *         USB_OK                          : When successful
 *         USBERR_RX_FAILED                : When unsuccessful
 ******************************************************************************
 * This function retrieves data received data on a RECV endpoint by copying it
 * from USB RAM to application buffer
 *****************************************************************************/
uint_8 USB_DCI_Recv_Data (
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number for the transaction */
    uchar_ptr             buffer_ptr,         /* [OUT] Pointer to the buffer into which to receive data */
    uint_32               size                /* [IN] Number of bytes to receive */
)
{
    uint_8 status = USBERR_RX_FAILED;
#if !HIGH_SPEED_DEVICE

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_RECV, USB_RAM_EVEN_BUFFER);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];

	UNUSED(handle);

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
                bdt_elem->app_len = size;
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
#else
    if (endpoint_number != 0)
    {
    	status = usbd_receive_data_epxout(0, (unsigned int)buffer_ptr, endpoint_number, size);
    }
    else
    	status = usbd_receive_data_ep0out(0, (unsigned int)buffer_ptr, size);

    if (status != USB_SUCCESS)
    {
    	return USBERR_RX_FAILED;
    }
    else
    {
    	return USB_OK;
    }
#endif
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
 * This function configures Controller to send data on a SEND endpoint by
 * setting the BDT to send data.
 *****************************************************************************/
uint_8 USB_DCI_Send_Data (
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number */
    uchar_ptr             buffer_ptr,         /* [IN] Application buffer pointer */
    uint_32               size                /* [IN] Size of the buffer */
)
{
#if !HIGH_SPEED_DEVICE
    uint_8 status = USBERR_TX_FAILED;
    P_BUFF_DSC buffer_dsc;

    /* validate params and get the bdt index */
    uint_8 bdt_index = USB_DCI_Validate_Param (endpoint_number, USB_SEND, USB_RAM_EVEN_BUFFER);
    P_BDT_ELEM bdt_elem = &g_bdt_elem[TRANSFER_INDEX(bdt_index)];

	UNUSED(handle);

    if(bdt_index == INVALID_BDT_INDEX)
        return USBERR_TX_FAILED;

    /* Send Data After Toggling Buffer */
    bdt_index = (uint_8)bdt_elem->bdtmap_index;

    buffer_dsc = &g_bdtmap->ep_dsc[bdt_index];

    /* Does MCU owns it and it is not stalled */
    if(!((buffer_dsc->Stat.SieCtlBit.own) ||/* For MCU: own is 0 */
       (*(&USB0_ENDPT0 + (endpoint_number * 4)) & ENDPT_EP_STALL_MASK)))
    {
        /* Now configure buffer_dsc->addr and buffer_dsc->cnt */
#ifdef LONG_SEND_TRANSACTION
        /* Initialize transfer */
        bdt_elem->app_len = size;
        bdt_elem->app_buffer = buffer_ptr;
        bdt_elem->curr_offset = 0;

        /* Prepare for send */
        USB_DCI_Prepare_Send_Data(buffer_dsc, bdt_elem);
#else
        buffer_dsc->addr = SWAP32(buffer_ptr);

        /* Adjust size based on the input at the init endpoint */
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
#else	// HIGH SPEED
    usb_status_t status;

    if (endpoint_number != 0) {
    	status = usbd_send_data_epxin(0, (unsigned int)buffer_ptr, endpoint_number, size);
    }

    /* Send descriptor - Data Phase */
    //zlt is false=>not zero length packet, send dev descriptor to host.
    else
    	status = usbd_send_data_ep0in(0, (unsigned int)buffer_ptr, size, 0);

    if (status != USB_SUCCESS)
    	return USBERR_TX_FAILED;

    return USB_OK;
#endif
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

	UNUSED(handle);

	/* set the address */
#if !HIGH_SPEED_DEVICE
    USB0_ADDR = address;
#else
    USBHS_DEVICEADDR = USBHS_DEVICEADDR_USBADR(address);
#endif

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
	UNUSED(handle);
#if !HIGH_SPEED_DEVICE
    /* Reset the Control Register */
	USB0_CTL = 0;
    /* Initiate Reset in the USB Control0 Register */
  #ifndef OTG_BUILD

	USB0_USBTRC0 = _USBRESET;
  #endif

	_usb_device_set_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
        USB_STATE_UNKNOWN);
    return;
#else
#if USART_DEBUG
    printf("%s\n", __func__);
#endif /* USART_DEBUG */
#endif
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
#if !HIGH_SPEED_DEVICE
    uint_16 delay_count;

    /* Clear SUSP Bit from USB_CTRL */
    USB0_USBCTRL &= ~USB_USBCTRL_SUSP_MASK;

    (void)handle;

    /* Reset Low Power RESUME enable */
    USB0_USBTRC0 &= ~USB_USBTRC0_USBRESMEN_MASK;

    USB_DCI_WAKEUP

    USB0_CTL |= USB_CTL_RESUME_MASK;   /* Start RESUME signaling and make SUSPEND bit 0*/

    delay_count = ASSERT_RESUME_DELAY_COUNT; /* Set RESUME line for 1-15 ms*/

    do
    {
       delay_count--;
       Watchdog_Reset();    /* Reset the COP */
    }while(delay_count);

    USB0_CTL &= ~USB_CTL_RESUME_MASK;          /* Stop RESUME signalling */

    return;
#else
#ifdef USART_DEBUG
    printf("%s\n", __func__);
#endif /* USART_DEBUG */
#endif
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
#if !HIGH_SPEED_DEVICE
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
                USB_DCI_Cancel_Transfer(&(event->controller_ID), (uint_8)CONTROL_ENDPOINT,
                  (uint_8)USB_RECV);
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
                 (((uint_8)event->len == bdt_elem->len) && (bdt_elem->flag == TRUE))
               )
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
                USB_DCI_Cancel_Transfer(&(event->controller_ID), (uint_8)CONTROL_ENDPOINT,
                (uint_8)USB_SEND);
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
                 (!(bdt_elem->app_len % bdt_elem->len)) &&
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
                    buffer_dsc_alt->addr = SWAP32((uint_32)(bdt_elem->app_buffer + bdt_elem->curr_offset));
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
#endif	// HIGH_SPEED_DEVICE

#if HIGH_SPEED_DEVICE
/**************************************************************************//*!
 * */
uint_32 sof_counter = 0;
static uint_32 micro_sof_counter = 0;
void USBHS_ISR(void){
	uint_32 usbsts;
    uint_32 reg;
	USB_DEV_EVENT_STRUCT event;

	// get interrupt status
    reg = USBHS_USBINTR;
	usbsts = USBHS_USBSTS & reg;

	// clear interrupt status
	USBHS_USBSTS |= usbsts;

	// initialize event structure
	event.controller_ID = g_dci_controller_Id;
	event.setup = FALSE;
	event.buffer_ptr = NULL;
	event.len = 0;
	event.direction = USB_RECV;
	event.errors = NO_ERRORS;
	event.ep_num = (uint_8)UNINITIALISED_VAL;

	// handle SOF
	if(usbsts & USBHS_USBSTS_SRI_MASK){
		//USBHS_USBSTS |= USBHS_USBSTS_SRI_MASK;
#ifdef ULPI_FORCE_FULLSPEED
		sof_counter++;
#else
		if (++micro_sof_counter == 8){
			//sof_counter++;
			//micro_sof_counter = 0;
		}
#endif
	}

	// handle Suspend
	if (usbsts & USBHS_USBSTS_SLI_MASK){
		USB_Device_Call_Service(USB_SERVICE_SUSPEND, &event);
		return;
	}

	// handle Bus Reset
	if (usbsts & USBHS_USBSTS_URI_MASK){
		// handle reset
		USB_Bus_Reset_Handler();

		// notify device layer
		USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);
		return;
	}

	// handle Transaction Complete
	if (usbsts & USBHS_USBSTS_UI_MASK){
		if (!USBHS_EPSETUPSR && !USBHS_EPCOMPLETE){
#ifdef USART_DEBUG
			printf("Warning: unexpected UI interrupt\n");
#endif /* USART_DEBUG */
		}

		// Handle dTD complete interrupt.
		// Must process EP complete events first, because setup complete events
		// trigger stack to re-prime endpoints.
		if(USBHS_EPCOMPLETE)
			usbd_ep_complete_handler(&event);

		// Handle setup compete packet interrupt
		if(USBHS_EPSETUPSR & USBHS_EPSETUPSR_EPSETUPSTAT(1))
			usbd_setup_packet_handler(&event);

		//
		if( (USBHS_EPSETUPSR & USBHS_EPSETUPSR_EPSETUPSTAT(2))||
				(USBHS_EPSETUPSR & USBHS_EPSETUPSR_EPSETUPSTAT(4))||
				(USBHS_EPSETUPSR & USBHS_EPSETUPSR_EPSETUPSTAT(8))){
#if USART_DEBUG
			printf("");
#endif /* USART_DEBUG */
		}
	}

	// handle Port Change
	if (usbsts & USBHS_USBSTS_PCI_MASK){
		usbd_port_change(&event);
	}

	// handle USB Error
	if (usbsts & USBHS_USBSTS_UEI_MASK){
#ifdef USART_DEBUG
		printf("USBHS: Error\n");
#endif
		// Notify Device Layer of ERROR Event to error service
		(void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
	}

	// handle USB System Error
	if (usbsts & USBHS_USBSTS_SEI_MASK){
#ifdef USART_DEBUG
		printf("USBHS: System Error\n");
#endif
		// Notify Device Layer of ERROR Event to error service
		(void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);
	}

}
#endif	// HIGH_SPEED_DEVICE

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
#if !HIGH_SPEED_DEVICE
void USB_ISR(void)
{
    /* Which interrupt occured and also was enabled */
	uint_8 v1 = USB0_ISTAT;
	uint_8 v2 = USB0_INTEN;
    uint_8 intr_stat = (uint_8)(v1 & v2);
    uint_8 stat = (uint_8)USB0_STAT;
    USB_DEV_EVENT_STRUCT event;
    uint_8 dev_state = USB_STATUS_UNKNOWN;

    /* initialize event structure */
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
    if((USB0_USBTRC0 & USB_USBTRC0_USB_RESUME_INT_MASK) && (dev_state == USB_STATE_SUSPEND))
    {
        /* Clear SUSP Bit from USB_CTRL */
    	USB0_USBCTRL &= ~USB_USBCTRL_SUSP_MASK;

        /* Reset Low Power RESUME enable */
        USB0_USBTRC0 &= ~USB_USBTRC0_USBRESMEN_MASK;
    }

    /* SOF received */
    if(SOF_TOKEN_FLAG(intr_stat))
    {
        uint_16 sof_count;
		uint_16 tmp1, tmp2, tmp3;
		tmp1 = USB0_FRMNUMH;
		tmp2 = FRAME_HIGH_BYTE_SHIFT;
		tmp3 = USB0_FRMNUML;
        /* Clear SOF Interrupt */
        USB0_ISTAT = USB_ISTAT_SOFTOK_MASK;
        sof_count = (uint_16)((tmp1 << tmp2) | tmp3);
        /*address of Lower byte of Frame number*/
        event.buffer_ptr = (uint_8_ptr)(&sof_count);
        /* Notify Device Layer of SOF Event */
        (void)USB_Device_Call_Service(USB_SERVICE_SOF, &event);

#ifdef USE_FEEDBACK_ENDPOINT
        // set feedback rate info number
        if(gNrSamples!=0)
        	feedback_data = gNrSamples;
        gNrSamples = 0;
#endif
    }

    if(BUS_RESET_FLAG(intr_stat))
    {
        /* Clear Reset Flag */
    	USB0_ISTAT = USB_ISTAT_USBRST_MASK;

        /* Handle RESET Interrupt */
        USB_Bus_Reset_Handler();

        /* Notify Device Layer of RESET Event */
        (void)USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;

        /* No need to process other interrupts */
        return;
    }

    if(TOKEN_COMPL_FLAG(intr_stat))
    {
        /* Clear TOKEN Interrupt */
    	USB0_ISTAT = USB_ISTAT_TOKDNE_MASK;

        event.ep_num = (uint_8)((stat & ENDPOINT_NUMBER_MASK) >>
            ENDPOINT_NUMBER_SHIFT);

        USB_Bus_Token_Cpl_Handler(stat, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
    }

    if(ERROR_FLAG(intr_stat))
    {
        /* Clear ERROR Interrupt */
    	USB0_ISTAT = USB_ISTAT_ERROR_MASK;

		v1 = USB0_ERRSTAT;
		v2 = USB0_ERREN;
        event.errors = (uint_8)(v1 & v2);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);

       USB0_ERRSTAT = ERR_STAT_CLEAR_ALL;  /*clear all errors*/
        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
       USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
    }

    if(SLEEP_FLAG(intr_stat))
    {
        /* Clear RESUME Interrupt if Pending */
    	USB0_ISTAT = USB_ISTAT_RESUME_MASK;

        /* Clear SLEEP Interrupt */
    	USB0_ISTAT = USB_ISTAT_SLEEP_MASK;

        /* Notify Device Layer of SLEEP Event */
        (void)USB_Device_Call_Service(USB_SERVICE_SLEEP, &event);

        /* Set Low Power RESUME enable */
        USB0_USBTRC0 |= USB_USBTRC0_USBRESMEN_MASK;

        /* Set SUSP Bit in USB_CTRL */
        USB0_USBCTRL |= USB_USBCTRL_SUSP_MASK;

        /* Enable RESUME Interrupt */
        USB0_INTEN |= USB_INTEN_RESUMEEN_MASK;
#ifdef USB_LOWPOWERMODE
        /* Enter Stop3 Mode*/
        Enter_StopMode(STOP_MODE3);
#endif
    }

    if(RESUME_FLAG(intr_stat))
    {
        /* Clear RESUME Interrupt */
    	USB0_ISTAT = USB_ISTAT_RESUME_MASK;

        /* Notify Device Layer of RESUME Event */
        (void)USB_Device_Call_Service(USB_SERVICE_RESUME, &event);

        /* Disable RESUME Interrupt */
        USB0_INTEN &= ~USB_INTEN_RESUMEEN_MASK;
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
        USB0_ISTAT = USB_ISTAT_STALL_MASK;

        /* Notify Device Layer of STALL Event */
        (void)USB_Device_Call_Service(USB_SERVICE_STALL, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        USB0_CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
    }
    return;
}
#endif // HIGH_SPEED_DEVICE

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


/* HIGH_SPEED_DEVICE */
#if HIGH_SPEED_DEVICE

extern void delay(int delayloop);

static uint_8 K70_ULPI_SetDeviceMode(uint_8 controller_ID){
	// device init
	unsigned int count = 10000;
	unsigned int reg;

	// reset usb controller
	reg = USBHS_USBCMD;
	reg |= USBHS_USBCMD_RST_MASK;
	USBHS_USBCMD = reg;
	// check if reset done, port is enabled
	while (USBHS_USBCMD & USBHS_USBCMD_RST_MASK);

	// enable USB work in device mode
	reg = USBHS_USBMODE;
	reg &= ~0x3;
	reg |= 0x2;	// device mode

	// Disable Setup Lockout by writing '1' to SLOM in USBMODE
	reg &= ~(USBHS_USBMODE_SDIS_MASK);
	// Setup Lockouts Off
	reg |= USBHS_USBMODE_SLOM_MASK;
	// this register can only be written once after reset
	USBHS_USBMODE = reg;

	// wait for mode to be set
	while (((USBHS_USBMODE & 0x3) != 0x2) && (--count)) ;

	if (count == 0)
		return USBERR_INIT_FAILED;	//timeout

#ifdef ULPI_FORCE_FULLSPEED
	reg = USBHS_PORTSC1;
	reg |= USBHS_PORTSC1_PFSC_MASK;
	USBHS_PORTSC1 = reg; /* force full speed */
#endif

	// Configure ENDPOINTLISTADDR Pointer
	USBHS_EPLISTADDR = (unsigned int)g_usbd_qh_buf & 0xfffff800;

	// Set OTG termination, controls the pulldown on DM
	reg = USBHS_OTGSC;
	reg |= (0x1 << 3);
	USBHS_OTGSC = reg;

	// clear the usb intr status
	USBHS_USBSTS = 0xffffffff;

	return USB_OK;
}

/*!
 * Initialize the USB device endpoint queue head structure
 */
static void usbd_ep_qh_init(uint_8 controller_ID,
		unsigned char endpt_number, unsigned char direction, unsigned int max_pkt_len,
		unsigned int zlt, unsigned char mult, uint_32 next_dtd)
{
	struct dqh_t qhead;
	unsigned int total_bytes;

	memset((void*)&qhead, 0, sizeof(qhead));

	// Initialize device queue head in system memory
	if(endpt_number == CONTROL_ENDPOINT)
		total_bytes = 8;  // 8 bytes for the 1st setup packet
	else
		total_bytes = max_pkt_len;
	qhead.dqh_base = usbd_get_dqh(controller_ID, endpt_number, direction);
	qhead.next_link_ptr = next_dtd;
	qhead.zlt = zlt;
	qhead.mps = max_pkt_len;
	qhead.ios = IOS_SET;
	// todo: check
	qhead.terminate = TERMINATE;
	qhead.total_bytes = total_bytes;
	qhead.ioc = IOC_SET;
	qhead.status = NO_STATUS;
	qhead.mult = mult;
	qhead.buffer_ptr0 = 0;
	qhead.current_offset = 0;
	qhead.buffer_ptr1 = 0;
	qhead.buffer_ptr2 = 0;
	qhead.buffer_ptr3 = 0;
	qhead.buffer_ptr4 = 0;

	/* Set Device Queue Head */
	usbd_setup_qhead(&qhead);
	// Initialize TD list to empty
	g_usbd_qh_tail[(endpt_number * 2) + direction] = NULL;
}

/*!
 * Setup the queue head for the USB device
 *
 * @param    qhead    The queue head data structure that contains the necessary configuration data
 */
static void usbd_setup_qhead(struct dqh_t *qhead)
{
	volatile struct dqh_setup_t *dqh_word = (volatile struct dqh_setup_t *)qhead->dqh_base;

	// 0x0
    // Bit31:30 Mult; Bit29 zlt; Bit26:16 mps; Bit15 ios
	dqh_word->dqh_word0 =
			(((uint_32)((qhead->zlt) << 29)) |
			((uint_32)((qhead->mps) << 16)) |
			(((uint_32)(qhead->ios) <<15)) |
			(uint_32)((qhead->mult) << 30));

    // 0x4
    // Current dTD Pointer => for hw use, not modified by DCD software
	dqh_word->dqh_word1 = 0x0;

    // 0x8
    // Next dTD Pointer
	dqh_word->dqh_word2 = (((qhead->next_link_ptr) & 0xFFFFFFE0) | qhead->terminate);

	// 0xC
	// Bit30:16 total_bytes; Bit15 ioc; Bit11:10 MultO; Bit7:0 status
	dqh_word->dqh_word3 =
			((((uint_32)(qhead->total_bytes) & 0x7FFF) << 16) |
			((uint_32)(qhead->ioc) << 15) |
			(qhead->status));

	// 0x10
	// Bit31:12 Buffer Pointer (Page 0)
	dqh_word->dqh_word4 =
			((qhead->buffer_ptr0 & 0xFFFFF000) |
			(qhead->current_offset & 0xFFF));

	// 0x14
	// Bit31:12 Buffer Pointer (Page 1)
	dqh_word->dqh_word5 = (qhead->buffer_ptr1 & 0xFFFFF000);

	// 0x18
	// Bit31:12 Buffer Pointer (Page 2)
	dqh_word->dqh_word6 = (qhead->buffer_ptr2 & 0xFFFFF000);

	// 0x1C
	// Bit31:12 Buffer Pointer (Page 3)
	dqh_word->dqh_word7 = (qhead->buffer_ptr3 & 0xFFFFF000);

	// 0x20
	// Bit31:12 Buffer Pointer (Page 4)
	dqh_word->dqh_word8 = (qhead->buffer_ptr4 & 0xFFFFF000);

	// 0x24
	// Reserved
	dqh_word->dqh_word9 = 0;

	// 0x28
	// Setup Buffer 0
	dqh_word->dqh_word10 = 0;

	// 0x2C
	// Setup Buffer 1
	dqh_word->dqh_word11 = 0;
}

/*!
 * Setup the transfer descriptor
 *
 * @param    td    The TD data sturcture that contains the necessary configuration data
 */
static void usbd_setup_td(struct dtd_t *td)
{
	volatile struct dtd_setup_t *dtd_word = (volatile struct dtd_setup_t *)td->dtd_base;

	/* Bit31:5 Next Link Pointer ; Bit0 terminate */
	dtd_word->dtd_word0 = ((td->next_link_ptr & 0xFFFFFFE0) | td->terminate);

	/* Bit30:16 total_bytes, Bit15 ioc, Bit7:0 status */
	dtd_word->dtd_word1 = ((unsigned int)td->total_bytes & 0x7FFF) << 16;
	dtd_word->dtd_word1 |= ((unsigned int)td->ioc << 15) | (td->status);

	/* Bit31:12 Buffer Pointer Page 0 ; Bit11:0 Current Offset */
	dtd_word->dtd_word2 = ((td->buffer_ptr0 & 0xFFFFF000) | (td->current_offset & 0xFFF));

	/* Bit31:12 Buffer Pointer Page 1 ; Bit10:0 Frame Number */
	dtd_word->dtd_word3 = (td->buffer_ptr1 & 0xFFFFF000);

	/* Bit31:12 Buffer Pointer Page 2 ; */
	dtd_word->dtd_word4 = (td->buffer_ptr2 & 0xFFFFF000);

	/* Bit31:12 Buffer Pointer Page 3 ; */
	dtd_word->dtd_word5 = (td->buffer_ptr3 & 0xFFFFF000);

	/* Bit31:12 Buffer Pointer Page 4 ; */
	dtd_word->dtd_word6 = (td->buffer_ptr4 & 0xFFFFF000);

}
/*!
 * Get the offset of DQH from the QH buffer base
 *
 * @param    endpt_number    The end point number, start from 0
 * @param    direction       The In or Out endpoint
 *
 * @return   The relative offset of DQH
 * @return   0 if can't find a free DTD
 */
static unsigned int usbd_get_dqh(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction)
{

	unsigned char *qh_buf = g_usbd_qh_buf;

	/* direction OUT = 0 and IN = 1 */
	return (unsigned int)(qh_buf + (SIZE_OF_QHD * (endpt_number * 2 + direction)));
}

/*!
 * Get the offset of DTD from the TD buffer base
 *
 * @param    endpt_number    The end point number, start from 0
 * @param    direction       The In or Out endpoint
 *
 * @return   The relative offset of DTD
 */
static unsigned int usbd_get_dtd(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned int sz)
{
	/* If Maximum EPs supported in n then EPno will range from 0 to (n-1) */
	unsigned int i;
	unsigned char *td_buf = g_usbd_td_buf;

	int td_index = (endpt_number * 2) + direction;

	for (i = 0; i < MAX_DTDS_PER_EP; i++) {

		if (g_usbd_td_flag[td_index][i].status == DTD_FREE ||
				g_usbd_td_flag[td_index][i].total_bytes == 0) {
			g_usbd_td_flag[td_index][i].status = DTD_BUSY;
			//            printf("ep%d direction%d alloc = %d\n", endpt_number, direction, i);
			g_usbd_td_flag[td_index][i].phys_td = (volatile struct dtd_setup_t *)
						((unsigned int) td_buf +
								(SIZE_OF_DTD0) *(td_index) * MAX_DTDS_PER_EP +
								i * (SIZE_OF_DTD0));
			g_usbd_td_flag[td_index][i].total_bytes = sz;
#if USART_DEBUG
			if(endpt_number == 1){
			   	printf("usbd_get_dtd ep1\n");
			}
			if(endpt_number == 2){
				printf("usbd_get_dtd ep2\n");
			}
			if(endpt_number == 3){
				printf("usbd_get_dtd ep3\n");
			}
#endif /* USART_DEBUG */
			return (unsigned int)g_usbd_td_flag[td_index][i].phys_td ;
		}
	}
	// todo: clear dtd and g_usbd_td_flag and point to first item
#ifdef USART_DEBUG
	printf("Cannot get dTD!\n");
#endif
	return 0;
}

static void usbd_ep_setup(uint_8 controller_ID, unsigned char endpt_number, unsigned char direction, unsigned char ep_type)
{
	if(endpt_number == CONTROL_ENDPOINT){
		return;
	}

	unsigned int temp = 0;

	if (direction) {
		//if (endpt_number)
			temp |= USBHS_EPCR_TXR_MASK;
		temp |= USBHS_EPCR_TXE_MASK;
		temp |= ((unsigned int)(ep_type) << USBHS_EPCR_TXT_SHIFT);
		/* configure RX endpoint as bulk(see K70 RM) */
		temp |= ((unsigned int)(2) << USBHS_EPCR_RXT_SHIFT);
	} else {
//		/if (endpt_number)
			temp |= USBHS_EPCR_RXR_MASK;
		temp |= USBHS_EPCR_RXE_MASK;
		temp |= ((unsigned int)(ep_type) << USBHS_EPCR_RXT_SHIFT);
		/* configure TX endpoint as bulk(see K70 RM) */
		temp |= ((unsigned int)(2) << USBHS_EPCR_TXT_SHIFT);
	}

	// Initialize endpoints 1-3
	USBHS_EPCR(endpt_number-1) = temp;
}

/**************************************************************************//*!
 *
 * @name  usbd_setup_packet_handler
 *
 * @brief The function handles Token Complete USB interrupts on the bus.
 *
 * @param event : Pointer to USB EVENT Structure
 *
 * @return None
 ******************************************************************************
 * This function handles Token Complete USB interrupts on the bus.
 *****************************************************************************/
static void usbd_setup_packet_handler(
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
)
{
    unsigned char setup_packet[8];

    // Clear setup complete register
    USBHS_EPSETUPSR = USBHS_EPSETUPSR;

    // Read setup packet
    usbd_read_setup_packet(event->controller_ID, setup_packet);

    // Assume EP0
    event->ep_num = CONTROL_ENDPOINT;

    // Direction of setup complete is always Receive
    event->direction = USB_RECV;
    event->buffer_ptr = setup_packet;
    event->len = sizeof(setup_packet);
    event->setup = TRUE;

    /* Transfer direction of next packet */
    g_trf_direction = (uint_8)((uint_8)
        (event->buffer_ptr[0]) >> 7);

    /* Notify Device Layer of Data Received or Sent Event */
    (void)USB_Device_Call_Service(event->ep_num, event);
}

// Read in setup packet. Assumes EP0.
static void usbd_read_setup_packet(uint_8 controller_ID, unsigned char *setup_packet)
{
    dqh_setup_t *dqh_word;
    uint_32 dqh_address;
    uint_32 reg;
    uint_32 count = 10000;
    int i;
    usb_standard_device_request_t *setup_struct;

    // a. Clear setup complete register
    reg = USBHS_EPSETUPSR;
    USBHS_EPSETUPSR = reg;

    /* Get the Device Queue Head Address for EP0 OUT   */
    dqh_address = usbd_get_dqh(controller_ID, EP0, OUT);
    dqh_word = (dqh_setup_t *) dqh_address;

    do {
        // b. Setup tripwire bit
        USBHS_USBCMD |= USBHS_USBCMD_SUTW_MASK;

        // c. Copy the SetupBuffer into local software byte array
        reg = (dqh_word->dqh_word10);

        /* This is due to the simulator bug for word variant access on EMI but actually design has word invariant access */
        for (i = 0; i < 4; i++) {
            setup_packet[i] = (unsigned int)((reg >> (8 * i)) & 0xFF);
        }
        reg = (dqh_word->dqh_word11);
        for (i = 0; i < 4; i++) {
            setup_packet[i + 4] = (unsigned int)((reg >> (8 * i)) & 0xFF);
        }

        //todo change to processor speed independent count
        // d. Read USBCMD[SUTW] bit (if set, continue, else goto step b)
    } while (!(USBHS_USBCMD & USBHS_USBCMD_SUTW_MASK) && (--count));

    if (!count){
#ifdef USART_DEBUG
        printf("error getting setup buffer\n");
#endif /* USART_DEBUG */
    }

    // e. Clear USBCMD[SUTW] bit
    USBHS_USBCMD &= ~USBHS_USBCMD_SUTW_MASK;

    setup_struct = (usb_standard_device_request_t *)setup_packet;
   	if (setup_struct->bRequest == SET_ADDRESS) {
		g_dci_address_state = 1;
	}
}


static void usbd_port_change(
		USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
){
}


/**************************************************************************//*!
 *
 * @name  usbd_dtd_handler
 *
 * @brief The function handles Token Complete USB interrupts on the bus.
 *
 * @param event : Pointer to USB EVENT Structure
 *
 * @return None
 ******************************************************************************
 * This function handles Token Complete USB interrupts on the bus.
 *****************************************************************************/
static void usbd_ep_complete_handler(
    USB_DEV_EVENT_STRUCT* event /* [IN] Pointer to USB EVENT Structure */
)
{
    int i;
    unsigned int ep_complete;

    // todo: check
#if USART_DEBUG
	if(USBHS_EPCOMPLETE&USBHS_EPCOMPLETE_ERCE(2)){
		printf("ep1: RECV\n");
	}
	if(USBHS_EPCOMPLETE&USBHS_EPCOMPLETE_ERCE(4)){
		printf("ep2: RECV\n");
	}
	if(USBHS_EPCOMPLETE&USBHS_EPCOMPLETE_ERCE(8)){
		printf("ep3: RECV\n");
	}
	if(USBHS_EPCOMPLETE&USBHS_EPCOMPLETE_ETCE(2)){
		printf("ep1: SEND\n");
	}
	if(USBHS_EPCOMPLETE&USBHS_EPCOMPLETE_ETCE(4)){
		printf("ep2: SEND\n");
	}
	if(USBHS_EPCOMPLETE&USBHS_EPCOMPLETE_ETCE(8)){
		printf("ep3: SEND\n");
	}
#endif /* USART_DEBUG */
    // Get and clear endpoint complete register
    ep_complete = USBHS_EPCOMPLETE;
    USBHS_EPCOMPLETE = ep_complete;

    // Handle all ep bits set in ep complete register
    for (i = 0; i < 16; i++)
    {
        // Determine bit position in ep complete register
        // (skip over the reserved bits)
        unsigned int ep_bit = (i < 8) ? i : (i + 8);

        if (ep_complete & (1 << ep_bit))
        {
            if (ep_bit < 8)
            {
                // Endpoint Receive Complete Event
                event->direction = USB_RECV;
                event->ep_num = i;
            }
            else
            {
                // Endpoint Transmit Complete Event
                event->direction = USB_SEND;
                event->ep_num = ep_bit - 16;
            }

            if (event->ep_num == CONTROL_ENDPOINT)
            {
                // Control endpoint handling
                usbd_ep0_complete(event);
            }
            else
            {
                // Non-control endpoint handling
                usbd_dtd_complete(event);
            }
        }
    }
}

// Control endpoint complete handling
static void usbd_ep0_complete(USB_DEV_EVENT_STRUCT* event)
{
	volatile struct dtd_setup_t *dtd_word;
    unsigned int i;
    unsigned int endpt_number = event->ep_num;
    unsigned int direction = event->direction;

    // Walk the TD status array to find the next completed TD
    for (i = 0; i < MAX_DTDS_PER_EP; i++)
    {
        unsigned int td_index = (endpt_number * 2) + direction;

        // Get dTD associated with this endpoint and direction
        dtd_word = g_usbd_td_flag[td_index][i].phys_td;

        // Determine if dTD is busy (not free) and completed (not active)
        if ((g_usbd_td_flag[td_index][i].status == DTD_BUSY) && ((dtd_word->dtd_word1 & 0x80) != 0x80))
        {
            // Mark dTD as free
            g_usbd_td_flag[td_index][i].status = DTD_FREE;

            if (g_dci_address_state ==1) {
                event->ep_num = CONTROL_ENDPOINT;
                event->buffer_ptr = 0;
                event->len = 0;
                g_dci_address_state =0;
            }

            /* Notify Device Layer of Data Received or Sent Event */
            (void)USB_Device_Call_Service(event->ep_num, event);
        }
    }
}

// Handle endpoint dTD complete
static void usbd_dtd_complete(USB_DEV_EVENT_STRUCT* event)
{
    volatile struct dtd_setup_t *dtd_word;
    unsigned int i;
    unsigned int endpt_number = event->ep_num;
    unsigned int direction = event->direction;

    // todo: check
#if USART_DEBUG
    if(event->ep_num == 1){
    	printf("usbd_dtd_complete ep1\n");
    }
    if(event->ep_num == 2){
    	printf("usbd_dtd_complete ep2\n");
    }
    if(event->ep_num == 3){
    	printf("usbd_dtd_complete ep3\n");
    }
#endif /*USART_DEBUG */
    // Walk the TD status array to find the next completed TD
    for (i = 0; i < MAX_DTDS_PER_EP; i++)
    {
        unsigned int td_index = (endpt_number * 2) + direction;

        // Get dTD associated with this endpoint and direction
        dtd_word = g_usbd_td_flag[td_index][i].phys_td;

        // Determine if dTD is busy (not free) and completed (not active)
        if ((g_usbd_td_flag[td_index][i].status == DTD_BUSY) && ((dtd_word->dtd_word1 & 0x80) != 0x80))
        {
            // Get original number of bytes to transfer
            unsigned int total_bytes = g_usbd_td_flag[td_index][i].total_bytes;
            // Subtract number of remaining bytes not transferred
            event->len = total_bytes - (dtd_word->dtd_word1 >> 16) & 0x7FFF;
            event->buffer_ptr = (uint_8 *)dtd_word->dtd_word2 - event->len;

            // Mark dTD as free
            g_usbd_td_flag[td_index][i].status = DTD_FREE;

            // If this was the tail, mark list as empty
            if (dtd_word == g_usbd_qh_tail[td_index])
                g_usbd_qh_tail[td_index] = NULL;

            /* Notify Device Layer of Data Received or Sent Event */
            (void)USB_Device_Call_Service(event->ep_num, event);
//           break;
        }
    }
}

/*!
 * Receive data through EPx
 *
 * @param    epx_data_buffer    EPx receive buffer
 * @param    sz                 Number of bytes to receive
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_receive_data_epxout(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address;
    unsigned int direction = OUT;

    /* Get Device Transfer Descriptor of the requested endpoint */
	dtd_address = usbd_get_dtd(controller_ID, ep_num, direction, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get the total bytes to be received   */
    total_bytes = sz;

#if USART_DEBUG
	if (total_bytes > 20 * 1024)
	    printf("Error!!! %s, size is %d\n", __func__, sz);
#endif /* USART_DEBUG */

    td.dtd_base = dtd_address;
   	td.next_link_ptr = 0;

    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = epx_data_buffer;
    td.current_offset = (epx_data_buffer & 0xFFF);
    td.buffer_ptr1 = (epx_data_buffer & 0xFFFFF000) + 0x1000;
    td.buffer_ptr2 = (epx_data_buffer & 0xFFFFF000) + 0x2000;
    td.buffer_ptr3 = (epx_data_buffer & 0xFFFFF000) + 0x3000;
    td.buffer_ptr4 = (epx_data_buffer & 0xFFFFF000) + 0x4000;

    /* Set the Transfer Descriptor  */
    usbd_setup_td(&td);

    // Add TD to TD list for this endpoint + direction
    usbd_add_td(controller_ID, ep_num, direction, &td);

    return USB_SUCCESS;
}

/*!
 * Receive data through EP0
 *
 * @param    ep0_data_buffer    EP0 receive buffer
 * @param    sz                 Number of bytes to receive
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_receive_data_ep0out(uint_8 controller_ID, unsigned int ep0_data_buffer, unsigned int sz)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address;
    unsigned int dqh_address;
    unsigned int temp;

//    printf_info("%s, size is %d\n", __func__, sz);

    // Yi if (ep0_data_buffer != NULL)
    //  memset((void *)ep0_data_buffer, 0x0, 256);  //todo hard-coded size

    /* Get Device Device Queue Head of the requested endpoint */
    dqh_address = usbd_get_dqh(controller_ID, EP0, OUT);

    /* Get Device Transfer Descriptor of the requested endpoint */
	dtd_address = usbd_get_dtd(controller_ID, EP0, OUT, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get the total bytes to be received   */
    total_bytes = sz;

    td.dtd_base = dtd_address;
   	td.next_link_ptr = dtd_address + 0x20;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = ep0_data_buffer;
    td.current_offset = (ep0_data_buffer & 0xFFF);
    td.buffer_ptr1 = 0;
    td.buffer_ptr2 = 0;
    td.buffer_ptr3 = 0;
    td.buffer_ptr4 = 0;

    /* Set the Transfer Descriptor  */
    usbd_setup_td(&td);

	//Yi
    //(*(volatile unsigned int *)(dqh_address)) &= ~0x20000000;

    /* 1. write dQH next ptr and dQH terminate bit to 0 */
    *(volatile unsigned int *)(dqh_address + 0x8) = dtd_address;

    /* 2. clear active & halt bit in dQH */
    *(volatile unsigned int *)(dqh_address + 0xC) &= ~0xFF;

    /* 3. prime endpoint by writing '1' in ENDPTPRIME */
    temp = USBHS_EPPRIME;
    temp |= EPOUT_PRIME;
    USBHS_EPPRIME = temp;
    while (USBHS_EPPRIME & EPOUT_PRIME) ;  //wait prime end

    return USB_SUCCESS;
}

// Prime endpoint
static void usbd_prime_ep(uint_8 controller_ID, unsigned char ep_num, unsigned char direction, struct dtd_t *td)
{
    unsigned int temp;

    unsigned int ep_mask = (direction == OUT ? EPOUT_PRIME : EPIN_PRIME);
    // Get Device Device Queue Head of the requested endpoint
    unsigned int dqh_address = usbd_get_dqh(controller_ID, ep_num, direction);

    /* Enable ZLT when data size is in multiple of Maximum Packet Size  */
    /* set ZLT enable */
    if (direction == IN)
    {
        (*(volatile unsigned int *)(dqh_address)) &= ~0x20000000;
    }

    /* 1. write dQH next ptr and dQH terminate bit to 0 */
    *(volatile unsigned int *)(dqh_address + 0x8) = td->dtd_base;

    /* 2. clear active & halt bit in dQH */
    *(volatile unsigned int *)(dqh_address + 0xC) &= ~0xFF;

    /* 3. prime endpoint by writing '1' in ENDPTPRIME */
    temp = USBHS_EPPRIME;
    temp |= ep_mask << ep_num;
    USBHS_EPPRIME = temp;
}

// Add TD to TD list and prime endpoint based on this algorithm:
// Appendix
// 5.5.3 Executing A Transfer Descriptor
// To safely add a dTD, the DCD must be follow this procedure which will handle the event where the device
// controller reaches the end of the dTD list at the same time a new dTD is being added to the end of the list.
// Determine whether the link list is empty:
// Check DCD driver to see if pipe is empty (internal representation of linked-list should indicate if any packets
// are outstanding).
// Case 1: Link list is empty
// 1. Write dQH next pointer AND dQH terminate bit to 0 as a single DWord operation.
// 2. Clear active & halt bit in dQH (in case set from a previous error).
// 3. Prime endpoint by writing '1' to correct bit position in ENDPTPRIME.
// Case 2: Link list is not empty
// 1. Add dTD to end of linked list.
// 2. Read correct prime bit in ENDPTPRIME - if '1' DONE.
// 3. Set ATDTW bit in USBCMD register to '1'.
// 4. Read correct status bit in ENDPTPRIME. (store in tmp. variable for later) [[this should be ENDPTSTATUS, not ENDPTPRIME]}
// 5. Read ATDTW bit in USBCMD register.
// If '0' goto 3.
// If '1' continue to 6.
// 6. Write ATDTW bit in USBCMD register to '0'.
// 7. If status bit read in (4) is '1' DONE.
// 8. If status bit read in (4) is '0' then Goto Case 1: Step 1.
//
static void usbd_add_td(uint_8 controller_ID, unsigned char ep_num, unsigned char direction, struct dtd_t *td)
{
    // Get the index into the TD list for this endpoint + direction
    int td_index = (ep_num * 2) + direction;

    if (g_usbd_qh_tail[td_index] == NULL)
    {
        // Case 1: Link list is empty

        usbd_prime_ep(controller_ID, ep_num, direction, td);
    }
    else
    {
        // Case 2: Link list is not empty

        unsigned int ep_mask = (direction == OUT ? EPOUT_PRIME : EPIN_PRIME);

        // Add TD to tail next_link_ptr
        // Clear Terminate bit to indicate pointer is valid
        g_usbd_qh_tail[td_index]->dtd_word0 = td->dtd_base & 0xFFFFFFE0;

        // If EP is already primed, we are done
        if (!(USBHS_EPPRIME & (ep_mask << ep_num)))
        {
            // EP not primed, check if it is active
            unsigned int ep_status = 0;
            unsigned int temp;

            // Use Add dTD Tripwire to properly read endpoint status register
            do
            {
                /* write '1' to Add Tripwire (ATDTW) in USBCMD register */
                temp = USBHS_USBCMD;
                temp |= (0x1 << USBHS_USBCMD_ATDTW_SHIFT);
                USBHS_USBCMD = temp;

                // Read endpoint status
                ep_status = USBHS_EPSR & (ep_mask << ep_num);

            } while (!USBHS_USBCMD & (0x1 << USBHS_USBCMD_ATDTW_SHIFT));

            /* write '0' to Add Tripwire (ATDTW) in USBCMD register */
            temp = USBHS_USBCMD;
            temp &= ~(0x1 << USBHS_USBCMD_ATDTW_SHIFT);
            USBHS_USBCMD = temp;

            if (!ep_status)
            {
                // Status is inactive, so need to prime EP
                usbd_prime_ep(controller_ID, ep_num, direction, td);
            }
        }
    }

    // Make this TD the tail
    g_usbd_qh_tail[td_index] = (struct dtd_setup_t *)td->dtd_base;
}

/*!
 * Send data through endpoint x
 *
 * @param    epx_data_buffer    EPx send buffer
 * @param    sz                 Number of bytes to send
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_send_data_epxin(uint_8 controller_ID, unsigned int epx_data_buffer, uint_8 ep_num, unsigned int sz)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address;
    unsigned int direction = IN;

    /* verify Endpoint Number and address */
    /* Get Device Transfer Descriptor of the requested endpoint */
    dtd_address = usbd_get_dtd(controller_ID, ep_num, direction, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get Total Bytes to Be received */
    total_bytes = sz;

    td.dtd_base = dtd_address;
    td.next_link_ptr = 0;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = epx_data_buffer;
    td.current_offset = (epx_data_buffer & 0xFFF);
    td.buffer_ptr1 = (epx_data_buffer & 0xFFFFF000) + 0x1000;
    td.buffer_ptr2 = (epx_data_buffer & 0xFFFFF000) + 0x2000;
    td.buffer_ptr3 = (epx_data_buffer & 0xFFFFF000) + 0x3000;
    td.buffer_ptr4 = (epx_data_buffer & 0xFFFFF000) + 0x4000;

    /* Set the transfer descriptor */
    usbd_setup_td(&td);

    // Add TD to TD list for this endpoint + direction
    usbd_add_td(controller_ID, ep_num, direction, &td);

    return USB_SUCCESS;
}

/*!
 * Send data through endpoint 0
 *
 * @param    ep0_data_buffer    EP0 send buffer
 * @param    sz                 Number of bytes to send
 * @param    zlt_enable         If ZLT is enabled
 *
 * @return   SUCCESS on success, otherwise FAIL when timeout
 */
static usb_status_t usbd_send_data_ep0in(uint_8 controller_ID,
                                         unsigned int ep0_data_buffer, unsigned int sz,
                                         unsigned char zlt_enable)
{
    struct dtd_t td;
    unsigned int total_bytes;
    unsigned int dtd_address, dqh_address;

    /* varify Endpoint Number and address */
    /* Get Device Transfer Descriptor of the requested endpoint */
    dtd_address = usbd_get_dtd(controller_ID, EP0, IN, sz);
    if (!dtd_address)
    {
        return USB_FAILURE;
    }

    /* Get Device Queue head of the requested endpoint */
    dqh_address = usbd_get_dqh(controller_ID, EP0, IN);

    /* Get Total Bytes to Be received */
    total_bytes = sz;

    td.dtd_base = dtd_address;
    td.next_link_ptr = 0;
    td.terminate = TERMINATE;
    td.total_bytes = total_bytes;
    td.ioc = IOC_SET;
    td.status = ACTIVE;
    td.buffer_ptr0 = ep0_data_buffer;
    td.current_offset = (ep0_data_buffer & 0xFFF);
    td.buffer_ptr1 = 0;
    td.buffer_ptr2 = 0;
    td.buffer_ptr3 = 0;
    td.buffer_ptr4 = 0;

    /* Set the transfer descriptor */
    usbd_setup_td(&td);

    /* Enable ZLT when data size is in multiple of Maximum Packet Size  */
    /* set ZLT enable */
    (*(volatile unsigned int *)(dqh_address)) &= ~0x20000000;

    /* 1. write dQH next ptr and dQH terminate bit to 0  */
    *(volatile unsigned int *)(dqh_address + 0x8) = (dtd_address);

    /* 2. clear active & halt bit in dQH */
    *(volatile unsigned int *)(dqh_address + 0xC) &= ~0xFF;

    USBHS_EPPRIME |= EPIN_PRIME;

    /* 4. wait for prime complete */
    while (USBHS_EPPRIME & EPIN_PRIME);

    return USB_SUCCESS;
}
#endif	/* HIGH_SPEED_DEVICE */
