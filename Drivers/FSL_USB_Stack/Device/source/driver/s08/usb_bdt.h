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
 * @file usb_bdt.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains definitions of Buffer Descriptor Table.
 *
 *****************************************************************************/

#ifndef _USBBDT_H
#define _USBBDT_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"  /* User Defined Data Types */

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* Buffer Descriptor Status Register Initialization Parameters */
#define _BDTSTALL      (0x04)                /* Buffer Stall enable */
#define _DATA0         (0x00)                /* DATA0 packet expected next */
#define _DATA1         (0x40)                /* DATA1 packet expected next */
#define _DTS           (0x08)                /* DTS Mask */
#define _SIE           (0x80)                /* SIE owns buffer */
#define _CPU           (0x00)                /* CPU owns buffer */

#if 0 /* << EST */
#if (defined(_MC9S08MM128_H) || defined(_MC9S08JE128_H))
#define USB_RAM_BASE_ADDRESS (0x1920) /* USB Register Base Address */
#else
#define USB_RAM_BASE_ADDRESS (0x1860) /* USB Register Base Address */
#endif
#else
/* device is %CPUDevice << EST */
%if (CPUDevice="MC9S08MM128") | (CPUDevice="MC9S08JE128")
#define USB_RAM_BASE_ADDRESS (0x1920) /* USB Register Base Address */
%else
#define USB_RAM_BASE_ADDRESS (0x1860) /* USB Register Base Address */
%endif
#endif

#define BD_SHIFT             (2)

/* calculate offset to put in bdt from endpoint buffer address */
#define CAL_BD_OFFSET(address)   ((uint_8)(((address) - USB_RAM_BASE_ADDRESS) \
                                            >> BD_SHIFT))

/* calculate address to from offset in the bdt */
#define CAL_USB_RAM_ADDR(offset) (((uint_16)(offset) << BD_SHIFT) + \
                                            USB_RAM_BASE_ADDRESS)

#ifdef DOUBLE_BUFFERING_USED
#define MAX_BDT_INDEX (10)          /* Maximum BDT Indexes */
#else
#define MAX_BDT_INDEX (6)           /* Maximum BDT Indexes */
#endif

/******************************************************************************
 * Types
 *****************************************************************************/
 /* This structure is an exact replica of the BDT MAP in the USB RAM
    The BDT_STAT defines the stat byte of the buffer descriptor vector.
    McuCtlBit structure defines the bits that have a meaning from CPU
    point of view.SieCtlBit structure defines the bits that have a
    meaning from USB controller point of view.
 */
typedef union _BD_STAT
{
    uint_8 _byte;
    struct{
        unsigned :1;
        unsigned :1;
        unsigned bdtstall:1;            /* Buffer Stall Enable */
        unsigned dts:1;                 /* Data Toggle Synch Enable */
        unsigned :1;                    /* Address Increment Disable */
        unsigned :1;                    /* BD Keep Enable */
        unsigned data:1;                /* Data Toggle Synch Value */
        unsigned own:1;                 /* USB Ownership */
    }McuCtlBit;
    struct{
        unsigned :1;
        unsigned :1;
        unsigned pid0:1;                /* Packet Identifier bit 0 */
        unsigned pid1:1;                /* Packet Identifier bit 1 */
        unsigned pid2:1;                /* Packet Identifier bit 2 */
        unsigned pid3:1;                /* Packet Identifier bit 3 */
        unsigned :1;
        unsigned own:1;
    }SieCtlBit;
    struct{
        unsigned    :2;
        unsigned pid:4;                 /* Packet Identifier */
        unsigned    :2;
    }RecPid;
} BD_STAT;                              /* Buffer Descriptor Status Register */

typedef struct _BUFF_DSC
{
        BD_STAT Stat;                   /* BD_STAT Structure*/
        uint_8 cnt;                    /* Count of bytes received or sent */
        uint_8 addr;                   /* Buffer Address */
} BUFF_DSC, *P_BUFF_DSC;               /* Buffer Descriptor Table */

typedef struct _g_bdtmap {

  BUFF_DSC ep_dsc[MAX_BDT_INDEX];      /* Endpoint Descriptor */
  uint_16 Reserved;
}BDTMAP;

/******************************************************************************
 * Global Functions - None
 *****************************************************************************/

#endif