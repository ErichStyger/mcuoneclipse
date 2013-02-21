/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: ehci_utl.c$
* $Version : 3.4.3.0$
* $Date    : Sep-10-2009$
*
* Comments:
*
*   This file contains the low-level Host API functions specific to the VUSB 
*   chip.
*
*END************************************************************************/
#include "hostapi.h"
#include "ehci_usbprv_host.h"
#include "ehci_utl.h"

#include "ehci_host.h"

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_hci_vusb20_bus_control
*  Returned Value : None
*  Comments       :
*        Bus control
*END*-----------------------------------------------------------------*/

USB_STATUS _usb_hci_vusb20_bus_control
   (
      /* [IN] the USB Host state structure */
      _usb_host_handle        handle,

      /* The operation to be performed on the bus */
      uint_8                  bControl
   )
{ /* Body */
   USB_HOST_STATE_STRUCT_PTR usb_host_ptr;
   
   usb_host_ptr = (USB_HOST_STATE_STRUCT_PTR)handle;
   
   switch(bControl) {
      case USB_ASSERT_BUS_RESET:
         break;
      case USB_ASSERT_RESUME:
         break;
      case USB_SUSPEND_SOF:
         _usb_ehci_bus_suspend(handle);
         break;
      case USB_DEASSERT_BUS_RESET:
      case USB_RESUME_SOF:
      case USB_DEASSERT_RESUME:
      default:
         break;
   } /* EndSwitch */
   
   return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_ehci_bus_suspend
*  Returned Value : None
*  Comments       :
*        Suspend the bus
*END*-----------------------------------------------------------------*/

void _usb_ehci_bus_suspend
   (
      /* [IN] the USB Host state structure */
      _usb_host_handle              handle
   )
{ /* Body */
   USB_HOST_STATE_STRUCT_PTR                    usb_host_ptr;
   VUSB20_REG_STRUCT_PTR                        dev_ptr;
   VUSB20_REG_STRUCT_PTR                        cap_dev_ptr;
   uint_8                                       i, total_port_numbers;
   uint_32                                      port_control;
   
   usb_host_ptr = (USB_HOST_STATE_STRUCT_PTR)handle;
   //cap_dev_ptr = (VUSB20_REG_STRUCT_PTR)
   //   _bsp_get_usb_capability_register_base(usb_host_ptr->DEV_NUM);
   cap_dev_ptr  = (VUSB20_REG_STRUCT_PTR)(&MCF_USB_OTG_CAPLENGTH);
      
   dev_ptr = (VUSB20_REG_STRUCT_PTR)usb_host_ptr->DEV_PTR;
   
   total_port_numbers = 
      (uint_8)((cap_dev_ptr->REGISTERS.CAPABILITY_REGISTERS.HCS_PARAMS & 
         EHCI_HCS_PARAMS_N_PORTS));
         
   USB_lock();
      

   /* Suspend all ports */
   for (i=0;i<total_port_numbers;i++) {
      port_control = dev_ptr->REGISTERS.OPERATIONAL_HOST_REGISTERS.PORTSCX[i];
      
      if (port_control & EHCI_PORTSCX_PORT_ENABLE) {
      
         port_control = dev_ptr->REGISTERS.OPERATIONAL_DEVICE_REGISTERS.PORTSCX[0];
         port_control &= ~EHCI_PORTSCX_W1C_BITS;
         
         dev_ptr->REGISTERS.OPERATIONAL_HOST_REGISTERS.PORTSCX[i] = 
            (port_control | EHCI_PORTSCX_PORT_SUSPEND);
      } /* Endif */
      
   } /* Endfor */
   
   /* Stop the controller 
   SGarg: This should not be done. If the controller is stopped, we will
   get no attach or detach interrupts and this will stop all operatings
   including the OTG state machine which is still running assuming that
   Host is alive.
   
   dev_ptr->REGISTERS.OPERATIONAL_HOST_REGISTERS.USB_CMD &= 
      ~EHCI_CMD_RUN_STOP;
   */   
      
   USB_unlock();
   
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_ehci_bus_resume
*  Returned Value : None
*  Comments       :
*        Resume the bus
*END*-----------------------------------------------------------------*/

void _usb_ehci_bus_resume
   (
      /* [IN] the USB Host state structure */
      _usb_host_handle              handle,

      /* The pipe descriptor to queue */            
      PIPE_DESCRIPTOR_STRUCT_PTR    pipe_descr_ptr
   )
{ /* Body */
   USB_HOST_STATE_STRUCT_PTR                    usb_host_ptr;
   VUSB20_REG_STRUCT_PTR                        dev_ptr;
   VUSB20_REG_STRUCT_PTR                        cap_dev_ptr;
   uint_8                                       i, total_port_numbers;
   uint_32                                      port_control;
   
   usb_host_ptr = (USB_HOST_STATE_STRUCT_PTR)handle;
   cap_dev_ptr = (VUSB20_REG_STRUCT_PTR)
      _bsp_get_usb_capability_register_base(usb_host_ptr->DEV_NUM);
   dev_ptr = (VUSB20_REG_STRUCT_PTR)usb_host_ptr->DEV_PTR;
   
   total_port_numbers = 
      (uint_8)(cap_dev_ptr->REGISTERS.CAPABILITY_REGISTERS.HCS_PARAMS & 
      EHCI_HCS_PARAMS_N_PORTS);

   USB_lock();
      

   /* Resume all ports */
   for (i=0;i<total_port_numbers;i++) {
      port_control = dev_ptr->REGISTERS.OPERATIONAL_HOST_REGISTERS.PORTSCX[i];
      
      if (port_control & EHCI_PORTSCX_PORT_ENABLE) {
         port_control &= ~EHCI_PORTSCX_W1C_BITS;
         dev_ptr->REGISTERS.OPERATIONAL_HOST_REGISTERS.PORTSCX[i] = 
            (port_control | EHCI_PORTSCX_PORT_FORCE_RESUME);
      } /* Endif */
      
   } /* Endfor */
   
   /* 
    S Garg: This should not be done. See comments in suspend.
      Restart the controller   
      dev_ptr->REGISTERS.OPERATIONAL_HOST_REGISTERS.USB_CMD |= 
      EHCI_CMD_RUN_STOP;
     */

   USB_unlock();
   
} /* EndBody */

/* EOF */
