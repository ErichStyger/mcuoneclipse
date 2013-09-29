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
 * @file usb_dci_cfv2.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains CFV2 USB stack controller layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string.h>
#include "usb_dciapi_cfv2.h" /* USB DCI API Header File */
#include "usb_devapi.h"      /* USB Device API Header File */
#include "usb_dci_cfv2.h"    /* USB DCI Header File */
#include "usb_bdt_cfv2.h"    /* USB BDT Structure Header File */
#include "exceptions_cfv2.h"
#include "wdt_cfv2.h"

#if 1 /* << EST: for Processor expert */
typedef volatile unsigned char vuint8;
/*********************************************************************
*
* Universal Serial Bus - OTG Controller (USB_OTG)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_USB_OTG_PER_ID                   (*(vuint8 *)(0x401C0000))
#define MCF_USB_OTG_ID_COMP                  (*(vuint8 *)(0x401C0004))
#define MCF_USB_OTG_REV                      (*(vuint8 *)(0x401C0008))
#define MCF_USB_OTG_ADD_INFO                 (*(vuint8 *)(0x401C000C))
#define MCF_USB_OTG_OTG_INT_STAT             (*(vuint8 *)(0x401C0010))
#define MCF_USB_OTG_OTG_INT_EN               (*(vuint8 *)(0x401C0014))
#define MCF_USB_OTG_OTG_STAT                 (*(vuint8 *)(0x401C0018))
#define MCF_USB_OTG_OTG_CTRL                 (*(vuint8 *)(0x401C001C))
#define MCF_USB_OTG_INT_STAT                 (*(vuint8 *)(0x401C0080))
#define MCF_USB_OTG_INT_ENB                  (*(vuint8 *)(0x401C0084))
#define MCF_USB_OTG_ERR_STAT                 (*(vuint8 *)(0x401C0088))
#define MCF_USB_OTG_ERR_ENB                  (*(vuint8 *)(0x401C008C))
#define MCF_USB_OTG_STAT                     (*(vuint8 *)(0x401C0090))
#define MCF_USB_OTG_CTL                      (*(vuint8 *)(0x401C0094))
#define MCF_USB_OTG_ADDR                     (*(vuint8 *)(0x401C0098))
#define MCF_USB_OTG_BDT_PAGE_01              (*(vuint8 *)(0x401C009C))
#define MCF_USB_OTG_FRM_NUML                 (*(vuint8 *)(0x401C00A0))
#define MCF_USB_OTG_FRM_NUMH                 (*(vuint8 *)(0x401C00A4))
#define MCF_USB_OTG_TOKEN                    (*(vuint8 *)(0x401C00A8))
#define MCF_USB_OTG_SOF_THLD                 (*(vuint8 *)(0x401C00AC))
#define MCF_USB_OTG_BDT_PAGE_02              (*(vuint8 *)(0x401C00B0))
#define MCF_USB_OTG_BDT_PAGE_03              (*(vuint8 *)(0x401C00B4))
#define MCF_USB_OTG_ENDPT0                   (*(vuint8 *)(0x401C00C0))
#define MCF_USB_OTG_ENDPT1                   (*(vuint8 *)(0x401C00C4))
#define MCF_USB_OTG_ENDPT2                   (*(vuint8 *)(0x401C00C8))
#define MCF_USB_OTG_ENDPT3                   (*(vuint8 *)(0x401C00CC))
#define MCF_USB_OTG_ENDPT4                   (*(vuint8 *)(0x401C00D0))
#define MCF_USB_OTG_ENDPT5                   (*(vuint8 *)(0x401C00D4))
#define MCF_USB_OTG_ENDPT6                   (*(vuint8 *)(0x401C00D8))
#define MCF_USB_OTG_ENDPT7                   (*(vuint8 *)(0x401C00DC))
#define MCF_USB_OTG_ENDPT8                   (*(vuint8 *)(0x401C00E0))
#define MCF_USB_OTG_ENDPT9                   (*(vuint8 *)(0x401C00E4))
#define MCF_USB_OTG_ENDPT10                  (*(vuint8 *)(0x401C00E8))
#define MCF_USB_OTG_ENDPT11                  (*(vuint8 *)(0x401C00EC))
#define MCF_USB_OTG_ENDPT12                  (*(vuint8 *)(0x401C00F0))
#define MCF_USB_OTG_ENDPT13                  (*(vuint8 *)(0x401C00F4))
#define MCF_USB_OTG_ENDPT14                  (*(vuint8 *)(0x401C00F8))
#define MCF_USB_OTG_ENDPT15                  (*(vuint8 *)(0x401C00FC))
#define MCF_USB_OTG_USB_CTRL                 (*(vuint8 *)(0x401C0100))
#define MCF_USB_OTG_USB_OTG_OBSERVE          (*(vuint8 *)(0x401C0104))
#define MCF_USB_OTG_USB_OTG_CONTROL          (*(vuint8 *)(0x401C0108))
#define MCF_USB_OTG_ENDPT(x)                 (*(vuint8 *)(0x401C00C0 + ((x)*0x4)))

/* Other macros */
#define MCF_USB_OTG_FRM_NUM                  (MCF_USB_OTG_INT_STAT=MCF_USB_OTG_INT_STAT_SOF_TOK ,MCF_USB_OTG_FRM_NUML | (((vuint16)MCF_USB_OTG_FRM_NUMH)<<8))


/* Bit definitions and macros for MCF_USB_OTG_PER_ID */
#define MCF_USB_OTG_PER_ID_ID(x)             (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF_USB_OTG_ID_COMP */
#define MCF_USB_OTG_ID_COMP_NID(x)           (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF_USB_OTG_REV */
#define MCF_USB_OTG_REV_REV(x)               (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_USB_OTG_ADD_INFO */
#define MCF_USB_OTG_ADD_INFO_IEHOST          (0x1)
#define MCF_USB_OTG_ADD_INFO_IRQ_NUM(x)      (((x)&0x1F)<<0x3)

/* Bit definitions and macros for MCF_USB_OTG_OTG_INT_STAT */
#define MCF_USB_OTG_OTG_INT_STAT_A_VBUS_CHG  (0x1)
#define MCF_USB_OTG_OTG_INT_STAT_B_SESS_CHG  (0x4)
#define MCF_USB_OTG_OTG_INT_STAT_SESS_VLD_CHG (0x8)
#define MCF_USB_OTG_OTG_INT_STAT_LINE_STATE_CHG (0x20)
#define MCF_USB_OTG_OTG_INT_STAT_1_MSEC      (0x40)
#define MCF_USB_OTG_OTG_INT_STAT_ID_CHG      (0x80)

/* Bit definitions and macros for MCF_USB_OTG_OTG_INT_EN */
#define MCF_USB_OTG_OTG_INT_EN_A_VBUS_EN     (0x1)
#define MCF_USB_OTG_OTG_INT_EN_B_SESS_EN     (0x4)
#define MCF_USB_OTG_OTG_INT_EN_SESS_VLD_EN   (0x8)
#define MCF_USB_OTG_OTG_INT_EN_LINE_STATE_EN (0x20)
#define MCF_USB_OTG_OTG_INT_EN_1_MSEC_EN     (0x40)
#define MCF_USB_OTG_OTG_INT_EN_ID_EN         (0x80)

/* Bit definitions and macros for MCF_USB_OTG_OTG_STAT */
#define MCF_USB_OTG_OTG_STAT_A_VBUS_VLD      (0x1)
#define MCF_USB_OTG_OTG_STAT_B_SESS_END      (0x4)
#define MCF_USB_OTG_OTG_STAT_SESS_VLD        (0x8)
#define MCF_USB_OTG_OTG_STAT_LINE_STATE_STABLE (0x20)
#define MCF_USB_OTG_OTG_STAT_1_MSEC_EN       (0x40)
#define MCF_USB_OTG_OTG_STAT_ID              (0x80)

/* Bit definitions and macros for MCF_USB_OTG_OTG_CTRL */
#define MCF_USB_OTG_OTG_CTRL_VBUS_DSCHG      (0x1)
#define MCF_USB_OTG_OTG_CTRL_VBUS_CHG        (0x2)
#define MCF_USB_OTG_OTG_CTRL_OTG_EN          (0x4)
#define MCF_USB_OTG_OTG_CTRL_VBUS_ON         (0x8)
#define MCF_USB_OTG_OTG_CTRL_DM_LOW          (0x10)
#define MCF_USB_OTG_OTG_CTRL_DP_LOW          (0x20)
#define MCF_USB_OTG_OTG_CTRL_DP_HIGH         (0x80)

/* Bit definitions and macros for MCF_USB_OTG_INT_STAT */
#define MCF_USB_OTG_INT_STAT_USB_RST         (0x1)
#define MCF_USB_OTG_INT_STAT_ERROR           (0x2)
#define MCF_USB_OTG_INT_STAT_SOF_TOK         (0x4)
#define MCF_USB_OTG_INT_STAT_TOK_DNE         (0x8)
#define MCF_USB_OTG_INT_STAT_SLEEP           (0x10)
#define MCF_USB_OTG_INT_STAT_RESUME          (0x20)
#define MCF_USB_OTG_INT_STAT_ATTACH          (0x40)
#define MCF_USB_OTG_INT_STAT_STALL           (0x80)

/* Bit definitions and macros for MCF_USB_OTG_INT_ENB */
#define MCF_USB_OTG_INT_ENB_USB_RST_EN       (0x1)
#define MCF_USB_OTG_INT_ENB_ERROR_EN         (0x2)
#define MCF_USB_OTG_INT_ENB_SOF_TOK_EN       (0x4)
#define MCF_USB_OTG_INT_ENB_TOK_DNE_EN       (0x8)
#define MCF_USB_OTG_INT_ENB_SLEEP_EN         (0x10)
#define MCF_USB_OTG_INT_ENB_RESUME_EN        (0x20)
#define MCF_USB_OTG_INT_ENB_ATTACH_EN        (0x40)
#define MCF_USB_OTG_INT_ENB_STALL_EN         (0x80)

/* Bit definitions and macros for MCF_USB_OTG_ERR_STAT */
#define MCF_USB_OTG_ERR_STAT_PID_ERR         (0x1)
#define MCF_USB_OTG_ERR_STAT_CRC5_EOF        (0x2)
#define MCF_USB_OTG_ERR_STAT_CRC16           (0x4)
#define MCF_USB_OTG_ERR_STAT_DFN8            (0x8)
#define MCF_USB_OTG_ERR_STAT_BTO_ERR         (0x10)
#define MCF_USB_OTG_ERR_STAT_DMA_ERR         (0x20)
#define MCF_USB_OTG_ERR_STAT_BTS_ERR         (0x80)

/* Bit definitions and macros for MCF_USB_OTG_ERR_ENB */
#define MCF_USB_OTG_ERR_ENB_PID_ERR_EN       (0x1)
#define MCF_USB_OTG_ERR_ENB_CRC5_EOF_EN      (0x2)
#define MCF_USB_OTG_ERR_ENB_CRC16_EN         (0x4)
#define MCF_USB_OTG_ERR_ENB_DFN8_EN          (0x8)
#define MCF_USB_OTG_ERR_ENB_BTO_ERR_EN       (0x10)
#define MCF_USB_OTG_ERR_ENB_DMA_ERR_EN       (0x20)
#define MCF_USB_OTG_ERR_ENB_BTS_ERR_EN       (0x80)

/* Bit definitions and macros for MCF_USB_OTG_STAT */
#define MCF_USB_OTG_STAT_ODD                 (0x4)
#define MCF_USB_OTG_STAT_TX                  (0x8)
#define MCF_USB_OTG_STAT_ENDP(x)             (((x)&0xF)<<0x4)

/* Bit definitions and macros for MCF_USB_OTG_CTL */
#define MCF_USB_OTG_CTL_USB_EN_SOF_EN        (0x1)
#define MCF_USB_OTG_CTL_ODD_RST              (0x2)
#define MCF_USB_OTG_CTL_RESUME               (0x4)
#define MCF_USB_OTG_CTL_HOST_MODE_EN         (0x8)
#define MCF_USB_OTG_CTL_RESET                (0x10)
#define MCF_USB_OTG_CTL_TXSUSPEND_TOKENBUSY  (0x20)
#define MCF_USB_OTG_CTL_SE0                  (0x40)
#define MCF_USB_OTG_CTL_JSTATE               (0x80)

/* Bit definitions and macros for MCF_USB_OTG_ADDR */
#define MCF_USB_OTG_ADDR_ADDR(x)             (((x)&0x7F)<<0)
#define MCF_USB_OTG_ADDR_LS_EN               (0x80)

/* Bit definitions and macros for MCF_USB_OTG_BDT_PAGE_01 */
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA9      (0x2)
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA10     (0x4)
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA11     (0x8)
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA12     (0x10)
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA13     (0x20)
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA14     (0x40)
#define MCF_USB_OTG_BDT_PAGE_01_BDT_BA15     (0x80)

/* Bit definitions and macros for MCF_USB_OTG_FRM_NUML */
#define MCF_USB_OTG_FRM_NUML_FRM0            (0x1)
#define MCF_USB_OTG_FRM_NUML_FRM1            (0x2)
#define MCF_USB_OTG_FRM_NUML_FRM2            (0x4)
#define MCF_USB_OTG_FRM_NUML_FRM3            (0x8)
#define MCF_USB_OTG_FRM_NUML_FRM4            (0x10)
#define MCF_USB_OTG_FRM_NUML_FRM5            (0x20)
#define MCF_USB_OTG_FRM_NUML_FRM6            (0x40)
#define MCF_USB_OTG_FRM_NUML_FRM7            (0x80)

/* Bit definitions and macros for MCF_USB_OTG_FRM_NUMH */
#define MCF_USB_OTG_FRM_NUMH_FRM8            (0x1)
#define MCF_USB_OTG_FRM_NUMH_FRM9            (0x2)
#define MCF_USB_OTG_FRM_NUMH_FRM10           (0x4)

/* Bit definitions and macros for MCF_USB_OTG_TOKEN */
#define MCF_USB_OTG_TOKEN_TOKEN_ENDPT(x)     (((x)&0xF)<<0)
#define MCF_USB_OTG_TOKEN_TOKEN_PID(x)       (((x)&0xF)<<0x4)
#define MCF_USB_OTG_TOKEN_TOKEN_PID_OUT      (0x10)
#define MCF_USB_OTG_TOKEN_TOKEN_PID_IN       (0x90)
#define MCF_USB_OTG_TOKEN_TOKEN_PID_SETUP    (0xD0)

/* Bit definitions and macros for MCF_USB_OTG_SOF_THLD */
#define MCF_USB_OTG_SOF_THLD_CNT0            (0x1)
#define MCF_USB_OTG_SOF_THLD_CNT1            (0x2)
#define MCF_USB_OTG_SOF_THLD_CNT2            (0x4)
#define MCF_USB_OTG_SOF_THLD_CNT3            (0x8)
#define MCF_USB_OTG_SOF_THLD_CNT4            (0x10)
#define MCF_USB_OTG_SOF_THLD_CNT5            (0x20)
#define MCF_USB_OTG_SOF_THLD_CNT6            (0x40)
#define MCF_USB_OTG_SOF_THLD_CNT7            (0x80)

/* Bit definitions and macros for MCF_USB_OTG_BDT_PAGE_02 */
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA16     (0x1)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA17     (0x2)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA18     (0x4)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA19     (0x8)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA20     (0x10)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA21     (0x20)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA22     (0x40)
#define MCF_USB_OTG_BDT_PAGE_02_BDT_BA23     (0x80)

/* Bit definitions and macros for MCF_USB_OTG_BDT_PAGE_03 */
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA24     (0x1)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA25     (0x2)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA26     (0x4)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA27     (0x8)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA28     (0x10)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA29     (0x20)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA30     (0x40)
#define MCF_USB_OTG_BDT_PAGE_03_BDT_BA31     (0x80)

/* Bit definitions and macros for MCF_USB_OTG_ENDPT */
#define MCF_USB_OTG_ENDPT_EP_HSHK            (0x1)
#define MCF_USB_OTG_ENDPT_EP_STALL           (0x2)
#define MCF_USB_OTG_ENDPT_EP_TX_EN           (0x4)
#define MCF_USB_OTG_ENDPT_EP_RX_EN           (0x8)
#define MCF_USB_OTG_ENDPT_EP_CTL_DIS         (0x10)
#define MCF_USB_OTG_ENDPT_RETRY_DIS          (0x40)
#define MCF_USB_OTG_ENDPT_HOST_WO_HUB        (0x80)

/* Bit definitions and macros for MCF_USB_OTG_USB_CTRL */
#define MCF_USB_OTG_USB_CTRL_CLK_SRC(x)      (((x)&0x3)<<0)
#define MCF_USB_OTG_USB_CTRL_CLK_SRC_ALTCLK  (0)
#define MCF_USB_OTG_USB_CTRL_CLK_SRC_OSCCLK  (0x1)
#define MCF_USB_OTG_USB_CTRL_CLK_SRC_SYSCLK  (0x3)
#define MCF_USB_OTG_USB_CTRL_PDE             (0x40)
#define MCF_USB_OTG_USB_CTRL_SUSP            (0x80)

/* Bit definitions and macros for MCF_USB_OTG_USB_OTG_OBSERVE */
#define MCF_USB_OTG_USB_OTG_OBSERVE_DM_PD    (0x10)
#define MCF_USB_OTG_USB_OTG_OBSERVE_DP_PD    (0x40)
#define MCF_USB_OTG_USB_OTG_OBSERVE_DP_PU    (0x80)

/* Bit definitions and macros for MCF_USB_OTG_USB_OTG_CONTROL */
#define MCF_USB_OTG_USB_OTG_CONTROL_SESSEND  (0x1)
#define MCF_USB_OTG_USB_OTG_CONTROL_SESSVLD  (0x2)
#define MCF_USB_OTG_USB_OTG_CONTROL_VBUSVLD  (0x4)
#define MCF_USB_OTG_USB_OTG_CONTROL_ID       (0x8)
#define MCF_USB_OTG_USB_OTG_CONTROL_DPPULLUP_NONOTG (0x10)

#endif

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
    MCF_USB_OTG_ERR_STAT = ERR_STAT_CLEAR_ALL;  	/* clear USB error flag */
    MCF_USB_OTG_CTL |= MCF_USB_OTG_CTL_ODD_RST;     /* Reset to Even buffer */
    MCF_USB_OTG_ADDR = 0;                       /* reset to default address */
    
    /* Select clock source and Disable Weak Pull Downs */
    
    /* OSCCLK = 48MHz */
    MCF_USB_OTG_USB_CTRL = MCF_USB_OTG_USB_CTRL_CLK_SRC_OSCCLK;  

    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)(g_bdt_elem),
        (sizeof(BDT_ELEM) * (MAX_BDT_INDEX >> 1)),
        (uint_8)UNINITIALISED_VAL);
    
    /* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap, BYTES_1024, (uint_8)NULL);
    
    /* Initialize BDT buffer address */
    g_bdt_address = ((uint_32)g_bdtmap + BYTES_512);
    
    g_trf_direction = USB_TRF_UNKNOWN;
    
    MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_ODD_RST;
   
    MCF_USB_OTG_ERR_ENB = ERR_ENB_ENABLE_ALL;   /* Enable All Error Interrupts */
    MCF_USB_OTG_INT_ENB = INTENB_BUS_RESET_VAL; /* Enable All Interrupts except RESUME */

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

    MCF_USB_OTG_USB_CTRL = MCF_USB_OTG_USB_CTRL_CLK_SRC_OSCCLK;        /* Select System Clock and 
                                           Disable Weak Pull Downs */

    g_dci_controller_Id = controller_ID; /* save the controller_ID 
                                           for future use*/

    UNUSED(bVregEn);
    
    /* Clear bdt elem structure */
    Clear_Mem((uint_8_ptr)(g_bdt_elem),
       (sizeof(BDT_ELEM) * (MAX_BDT_INDEX >> 1)), 
       (uint_8)UNINITIALISED_VAL);
    g_bdtmap = (BDTMAP *)((uint_32)g_Mem);
    
    /* Clear Memory for BDT and buffer Data */
    Clear_Mem((uint_8_ptr)g_bdtmap, BYTES_1024, (uint_8)NULL);

    g_trf_direction = USB_TRF_UNKNOWN;

    /* Set the BDT Table address, Need to be on 512 byte boundry */
    /* D8 Bit is masked in BDT_PAGE_01 */
    MCF_USB_OTG_BDT_PAGE_01 = (uint_8)(((uint_32)g_bdtmap >> 8) & 0xFE);
    MCF_USB_OTG_BDT_PAGE_02 = (uint_8)((uint_32)g_bdtmap >> 16);
    MCF_USB_OTG_BDT_PAGE_03 = (uint_8)((uint_32)g_bdtmap >> 24);

    /* Initialized BDT buffer address */
    g_bdt_address = ((uint_32)g_bdtmap + BYTES_512);

    /* Pull Up configuration */
    #if defined(__MCF52259_H__) || 1 /* << EST */
    	MCF_USB_OTG_USB_OTG_CONTROL |= MCF_USB_OTG_USB_OTG_CONTROL_DPPULLUP_NONOTG;
	#endif
	#ifdef __MCF52221_H__
    	MCF_USB_OTG_USB_OTG_CONTROL |= MCF_USB_OTG_USB_OTG_CONTROL_VBUSD;	
	#endif
    
    /* Clear USB interrupts*/
    MCF_USB_OTG_INT_STAT = INT_STAT_CLEAR_ALL;
    /* Enable USB RESET Interrupt */
    MCF_USB_OTG_INT_ENB  = MCF_USB_OTG_INT_ENB_USB_RST_EN;
    /* Enable USB Sleep Interrupt */
    MCF_USB_OTG_INT_ENB |= MCF_USB_OTG_INT_ENB_SLEEP_EN;
    /* Enable USB module */
    MCF_USB_OTG_CTL |= MCF_USB_OTG_CTL_USB_EN_SOF_EN;    

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
	 MCF_USB_OTG_INT_STAT = INT_STAT_CLEAR_ALL; 
	                
	 /* Disable USB RESET Interrupt */
	 MCF_USB_OTG_INT_ENB  &= ~MCF_USB_OTG_INT_ENB_USB_RST_EN;   
	 
     /* Disable USB module */ 
     MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_USB_EN_SOF_EN;   
           
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
 * This function initializes an endpoint and the Buffer Descriptor Table
 * entry associated with it. In case the input parameters are invalid it will
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
    *((&MCF_USB_OTG_ENDPT0) + (4 * ep_num)) |= ep_ctrl[direction];

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
    _usb_device_handle    handle,           /* [IN] Controller ID */
    uint_8                endpoint_number,  /* [IN] Endpoint number */
    uint_8                direction         /* [IN] Endpoint direction */
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
    (void)/*<<EST*/USB_DCI_Cancel_Transfer(&controller_ID, ep_num, direction); 
    /* delete buffer space for both even and odd buffers */
    g_bdt_address -= (g_bdt_elem[bdtelem_index].len);

    /* Disable endpoint */
    *((&MCF_USB_OTG_ENDPT0) + (4 * ep_num)) = EP_DISABLE; 

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
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number to stall */
    uint_8                direction           /* [IN] Direction to stall */
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
    _usb_device_handle    handle,           /* [IN] USB Device handle */
    uint_8                endpoint_number,  /* [IN] Endpoint number to unstall */
    uint_8                direction         /* [IN] Direction to unstall */
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
        vuint8 *endpoint = (vuint8*)(&MCF_USB_OTG_ENDPT0 + (4 * endpoint_number));
	    
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
            *endpoint |= endpt;	
        }
        /* Clear Endpoint Stall bit is endpoint control register */        
        *endpoint &= ~MCF_USB_OTG_ENDPT_EP_STALL;
        
        
	    /* Unstall endpoint by clearing stall bit in BDT  */
	    g_bdtmap->ep_dsc[bdt_index].Stat._byte &= ~(_SIE | _BDTSTALL); 
        /* We Require DATA0 PID to be zero on unstall */
        g_bdtmap->ep_dsc[bdt_index].Stat._byte = _DATA0;
	    if(direction == USB_RECV)
	    {
	        /* Initiate Next receive Transfer */
	      (void)/*<<EST*/USB_DCI_Recv_Data(handle, endpoint_number, NULL, 0);   
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
    _usb_device_handle    handle,           /* [IN] USB Device handle */
    uint_8                endpoint_number,  /* [IN] Endpoint number for the transaction */
    uint_8_ptr            buffer_ptr        /* [IN] Pointer to the buffer into which to read data */
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
    _usb_device_handle    handle,            /* [IN] USB Device handle */
    uint_8                endpoint_number,   /* [IN] Endpoint number */
    uint_8                direction          /* [IN] Endpoint direction */
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
        uint_8 ep_control = (uint_8)(*((&MCF_USB_OTG_ENDPT0)+4*endpoint_number));

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
		vuint8 *endpoint = (vuint8*)(&MCF_USB_OTG_ENDPT0 + (4 * endpoint_number));
		g_bdtmap->ep_dsc[bdt_index].Stat._byte = _DATA0;
	}
    return;
#else	// HIGH SPEED
    printf("%%s\n", __func__);
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
 *         USB_OK                          : When successfull
 *         USBERR_RX_FAILED                : When unsuccessfull
 ******************************************************************************
 * This function retrieves data received data on a RECV endpoint by copying it
 * from USB RAM to application buffer
 *****************************************************************************/
uint_8 USB_DCI_Recv_Data (
    _usb_device_handle    handle,           /* [IN] Controller ID */
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
                bdt_elem->app_len = ( USB_PACKET_SIZE)size;
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
    _usb_device_handle    handle,            /* [IN] USB Device handle */
    uint_8                endpoint_number,   /* [IN] Endpoint number of the transaction */
    uchar_ptr             buffer_ptr,        /* [IN] Pointer to the buffer to send */
    uint_32               size               /* [IN] Number of bytes to send */
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
       (*(&MCF_USB_OTG_ENDPT0 + (endpoint_number * 4)) & ENDPT_EP_STALL_MASK)))
    {
        /* Now configure buffer_dsc->addr and buffer_dsc->cnt */
#ifdef LONG_SEND_TRANSACTION
        /* Initialise transfer */
        bdt_elem->app_len = (USB_PACKET_SIZE)size;
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
    MCF_USB_OTG_ADDR = address;

    (void)/*<<EST*/_usb_device_set_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
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
    MCF_USB_OTG_CTL = 0;

    (void)/*<<EST*/_usb_device_set_status(&g_dci_controller_Id, USB_STATUS_DEVICE_STATE,
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
    MCF_USB_OTG_USB_CTRL &= ~MCF_USB_OTG_USB_CTRL_SUSP;

    USB_DCI_WAKEUP

    MCF_USB_OTG_CTL |= MCF_USB_OTG_CTL_RESUME;   /* Start RESUME signaling and make SUSPEND bit 0*/

    delay_count = ASSERT_RESUME_DELAY_COUNT; /* Set RESUME line for 1-15 ms*/
     
    do
    {
       delay_count--;
       Watchdog_Reset();    /* Reset the COP */
    }while(delay_count);

    MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_RESUME;          /* Stop RESUME signalling */

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
                (void)/*<<EST*/USB_DCI_Cancel_Transfer(&(event->controller_ID), CONTROL_ENDPOINT,
                  USB_RECV);
                /* We Require DATA0 PID for Setup Token */
                buffer_dsc_alt->Stat._byte = _DATA0;
                /* Prepare for Next SETUP PACKET Receive */
                (void)/*<<EST*/USB_DCI_Recv_Data(&(event->controller_ID),
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
                (void)/*<<EST*/USB_DCI_Cancel_Transfer(&(event->controller_ID), CONTROL_ENDPOINT,
                  USB_SEND);
                /* We Require DATA0 PID for Setup Token */
                buffer_dsc_alt->Stat._byte = _DATA0;
                /* Prepare for Next SETUP PACKET Receive */
                (void)/*<<EST*/USB_DCI_Recv_Data(&(event->controller_ID),
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

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
extern volatile uint_8 usb_int_disable;
extern volatile uint_8 usb_int_en_copy;
#endif
#ifdef OTG_BUILD
void USB_ISR(void)
#else
void __declspec(interrupt) USB_ISR(void)
#endif
{

    /* Which interrupt occured and also was enabled */
    uint_8 intr_stat = (uint_8)(MCF_USB_OTG_INT_STAT & MCF_USB_OTG_INT_ENB);
    uint_8 stat = (uint_8)MCF_USB_OTG_STAT;

    USB_DEV_EVENT_STRUCT event;
    uint_8 dev_state = USB_STATUS_UNKNOWN;
    
    #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
    
     if(usb_int_disable)
     {
       usb_int_en_copy = MCF_USB_OTG_INT_ENB;
       MCF_USB_OTG_INT_ENB = 0;
       return;
     }
     
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
    if(dev_state == USB_STATE_SUSPEND)
    {
        /* Clear SUSP Bit from USB_CTRL */
        MCF_USB_OTG_USB_CTRL &= ~MCF_USB_OTG_USB_CTRL_SUSP;
    }

    if(SOF_TOKEN_FLAG(intr_stat))
    {
        uint_16 sof_count;
        /* Clear SOF Interrupt */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_ENB_SOF_TOK_EN;
        sof_count = (uint_16)((MCF_USB_OTG_FRM_NUMH << FRAME_HIGH_BYTE_SHIFT) | MCF_USB_OTG_FRM_NUML);
        /*address of Lower byte of Frame number*/
        event.buffer_ptr = (uint_8_ptr)(&sof_count);
        /* Notify Device Layer of SOF Event */
        (void)USB_Device_Call_Service(USB_SERVICE_SOF, &event);
    }

    if(BUS_RESET_FLAG(intr_stat))
    {
        /* Clear Reset Flag */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_USB_RST;   

        /* Handle RESET Interrupt */
        USB_Bus_Reset_Handler();

        /* Notify Device Layer of RESET Event */
        (void)USB_Device_Call_Service(USB_SERVICE_BUS_RESET, &event);
 
        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_TXSUSPEND_TOKENBUSY;
        
        /* No need to process other interrupts */
        return;
    }

    if(TOKEN_COMPL_FLAG(intr_stat))
    {
        /* Clear TOKEN Interrupt */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_TOK_DNE;

        event.ep_num = (uint_8)((stat & ENDPOINT_NUMBER_MASK) >>
            ENDPOINT_NUMBER_SHIFT);
        USB_Bus_Token_Cpl_Handler(stat, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_TXSUSPEND_TOKENBUSY;
    }

    if(ERROR_FLAG(intr_stat))
    {
        /* Clear ERROR Interrupt */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_ERROR;

        event.errors = (uint_8)(MCF_USB_OTG_ERR_STAT & MCF_USB_OTG_ERR_ENB);

        /* Notify Device Layer of ERROR Event to error service */
       (void)USB_Device_Call_Service(USB_SERVICE_ERROR, &event);

        MCF_USB_OTG_ERR_STAT = ERR_STAT_CLEAR_ALL; /*clear all errors*/
        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_TXSUSPEND_TOKENBUSY;
    }

    if(SLEEP_FLAG(intr_stat))
    {
        /* Clear RESUME Interrupt if Pending */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_RESUME;
        
        /* Clear SLEEP Interrupt */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_SLEEP;

        /* Notify Device Layer of SLEEP Event */
        (void)USB_Device_Call_Service(USB_SERVICE_SLEEP, &event);

        /* Set SUSP Bit in USB_CTRL */
        MCF_USB_OTG_USB_CTRL |= MCF_USB_OTG_USB_CTRL_SUSP;        
        
        /* Enable RESUME Interrupt */
        MCF_USB_OTG_INT_ENB |= MCF_USB_OTG_INT_ENB_RESUME_EN;
#ifdef USB_LOWPOWERMODE
        /* Enter Stop3 Mode*/
        Enter_StopMode(STOP_MODE3);
#endif
    }

    if(RESUME_FLAG(intr_stat))
    {
        /* Clear RESUME Interrupt */
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_RESUME;

        /* Notify Device Layer of RESUME Event */
        (void)USB_Device_Call_Service(USB_SERVICE_RESUME, &event);

        /* Disable RESUME Interrupt */
        MCF_USB_OTG_INT_ENB &= ~ MCF_USB_OTG_INT_ENB_RESUME_EN;
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
        MCF_USB_OTG_INT_STAT = MCF_USB_OTG_INT_STAT_STALL;

        /* Notify Device Layer of STALL Event */
        (void)USB_Device_Call_Service(USB_SERVICE_STALL, &event);

        /* Clearing this bit allows the SIE to continue token processing
           and clear suspend condition */
        MCF_USB_OTG_CTL &= ~MCF_USB_OTG_CTL_TXSUSPEND_TOKENBUSY;
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
