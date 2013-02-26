/*
 * host.c
 *
 *  Created on: Feb 23, 2013
 *      Author: Erich Styger
 */

#include "host.h"
#include "WAIT1.h"
#include "host_common.h"
#include "usb.h"
#include "msd_commands.h"
#include "host_main.h"
#include "usb_host_hub_sm.h"
#include "usb_host_msd_bo.h"
#include "mem_util.h"
#include "poll.h"
#include "CLS1.h"
#include "FRTOS1.h"

/* the following is the mass storage class driver object structure. This is
used to send commands down to  the class driver. See the Class API document
for details */
COMMAND_OBJECT_STRUCT pCmd;
volatile DEVICE_STRUCT       mass_device = { 0 };   /* mass storage device struct */

const USB_HOST_DRIVER_INFO DriverInfoTable[] = {
   /* Floppy drive */
   {
      {0x00,0x00},                  /* Vendor ID per USB-IF             */
      {0x00,0x00},                  /* Product ID per manufacturer      */
      USB_CLASS_MASS_STORAGE,       /* Class code                       */
      USB_SUBCLASS_MASS_UFI,        /* Sub-Class code                   */
      USB_PROTOCOL_MASS_BULK,       /* Protocol                         */
      0,                            /* Reserved                         */
      usb_host_mass_device_event    /* Application call back function   */
   },

   /* USB 2.0 hard drive */
   {

      {0x49,0x0D},                  /* Vendor ID per USB-IF             */
      {0x00,0x30},                  /* Product ID per manufacturer      */
      USB_CLASS_MASS_STORAGE,       /* Class code                       */
      USB_SUBCLASS_MASS_SCSI,       /* Sub-Class code                   */
      USB_PROTOCOL_MASS_BULK,       /* Protocol                         */
      0,                            /* Reserved                         */
      usb_host_mass_device_event    /* Application call back function   */
   },

   /* USB 1.1 hub */
   {

      {0x00,0x00},                  /* Vendor ID per USB-IF             */
      {0x00,0x00},                  /* Product ID per manufacturer      */
      USB_CLASS_HUB,                /* Class code                       */
      USB_SUBCLASS_HUB_NONE,        /* Sub-Class code                   */
      USB_PROTOCOL_HUB_LS,          /* Protocol                         */
      0,                            /* Reserved                         */
      usb_host_hub_device_event     /* Application call back function   */
   },

   {
      {0x00,0x00},                  /* All-zero entry terminates        */
      {0x00,0x00},                  /*    driver info list.             */
      0,
      0,
      0,
      0,
      NULL
   }
};

static void print(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}


void Main_Task (void)
{ /* Body */
   //USB_STATUS   status = USB_OK;
   static uint_8 bootloader_task = 0;

   /*----------------------------------------------------**
   ** Infinite loop, waiting for events requiring action **
   **----------------------------------------------------*/
   switch (mass_device.dev_state)
   {
       case USB_DEVICE_IDLE:
           break;

       case USB_DEVICE_ATTACHED:
           print((unsigned char*)"Mass Storage Device Attached\n" );
           mass_device.dev_state = USB_DEVICE_SET_INTERFACE_STARTED;
           /*status = */_usb_hostdev_select_interface(mass_device.dev_handle,
           mass_device.intf_handle, (pointer)&mass_device.class_intf);
           /* Can run bootloader_task task */
           bootloader_task = 1;
           break;

       case USB_DEVICE_SET_INTERFACE_STARTED:
           break;

       case USB_DEVICE_INTERFACED:
#if MSD_TEST_MODE /* << EST */
         usb_host_mass_test_storage();
#else /* MSD_BOOTLOADER_MODE */
           //mass_device.dev_state = USB_DEVICE_OTHER;
           if(bootloader_task==1)
           {
               /* USB attached, call bootloader function */
//              BootLoader();
           }
           /* Disable flag to run bootloader_task */
           bootloader_task = 0;
#endif
           break;

       case USB_DEVICE_DETACHED:
           print((unsigned char*)"\nMass Storage Device Detached\n" );
           mass_device.dev_state = USB_DEVICE_IDLE;
           break;

       case USB_DEVICE_OTHER:
           break;

       default:
           print ((unsigned char*)"Unknown Mass Storage Device State = %d\n" /*, (int)mass_device.dev_state*/ );
           break;
   } /* Endswitch */
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_host_mass_device_event
* Returned Value : None
* Comments       :
*     called when mass storage device has been attached, detached, etc.
*END*--------------------------------------------------------------------*/
void usb_host_mass_device_event
   (
      /* [IN] pointer to device instance */
      _usb_device_instance_handle      dev_handle,

      /* [IN] pointer to interface descriptor */
      _usb_interface_descriptor_handle intf_handle,

      /* [IN] code number for event causing callback */
      uint_32           event_code
   )
{ /* Body */
//   INTERFACE_DESCRIPTOR_PTR   intf_ptr =      (INTERFACE_DESCRIPTOR_PTR)intf_handle;

   switch (event_code)
   {
      case USB_CONFIG_EVENT:
         /* Drop through into attach, same processing */
      case USB_ATTACH_EVENT:
         if (mass_device.dev_state == USB_DEVICE_IDLE)
         {
            mass_device.dev_handle = dev_handle;
            mass_device.intf_handle = intf_handle;
            mass_device.dev_state = USB_DEVICE_ATTACHED;
         }
         else
         {
            print((unsigned char*)"Mass Storage Device Is Already Attached\n");
         } /* EndIf */
         break;

      case USB_INTF_EVENT:
         mass_device.dev_state = USB_DEVICE_INTERFACED;
         break;

      case USB_DETACH_EVENT:
         //test = 0;
         if (mass_device.dev_state != USB_DEVICE_IDLE)
         {
            mass_device.dev_handle = NULL;
            mass_device.intf_handle = NULL;
            mass_device.dev_state = USB_DEVICE_DETACHED;
         }
         else
         {
           print((unsigned char*)"Mass Storage Device Is Not Attached\n");
         } /* EndIf */
         break;

      default:
         mass_device.dev_state = USB_DEVICE_IDLE;
         break;
   } /* EndSwitch */
} /* Endbody */

static void host_init(void) {
  USB_STATUS           status = USB_OK;
  _usb_host_handle     host_handle;

  /* Initialize the current platform. Call for the _bsp_platform_init which is specific to each processor family */
  /* Init polling global variable */
  POLL_init();

  //DisableInterrupts;
  #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
  usb_int_dis();
  #endif
  status = _usb_host_init
    (HOST_CONTROLLER_NUMBER,    /* Use value in header file */
     MAX_FRAME_SIZE,            /* Frame size per USB spec  */
     &host_handle);             /* Returned pointer */

  if (status != USB_OK)
  {
    print((unsigned char*)"\nUSB Host Initialization failed. STATUS: 0x%x"/*, (unsigned int) status*/);
  } /* Endif */

   /*
   ** Since we are going to act as the host driver, register
   ** the driver information for wanted class/subclass/protocols
   */
  status = _usb_host_driver_info_register(host_handle, (void *)DriverInfoTable);
  if (status != USB_OK)
  {
     print((unsigned char*)"\nDriver Registration failed. STATUS: 0x%x"/*, (unsigned int)status*/);
  }

  //EnableInterrupts;
  #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
  usb_int_en();
  #endif

  pCmd.CBW_PTR = (CBW_STRUCT_PTR)USB_mem_alloc_word_aligned(sizeof(CBW_STRUCT));
  if (pCmd.CBW_PTR == NULL)
  {
     print ((unsigned char*)"\nUnable to allocate Command Block Wrapper!");
  }
  memset(pCmd.CBW_PTR, 0, sizeof(CBW_STRUCT));

  pCmd.CSW_PTR = (CSW_STRUCT_PTR)USB_mem_alloc_word_aligned(sizeof(CSW_STRUCT));
  if (pCmd.CSW_PTR == NULL)
  {
     print ((unsigned char*)"\nUnable to allocate Command Status Wrapper!");
  }
  memset(pCmd.CSW_PTR, 0, sizeof(CSW_STRUCT));

  print((unsigned char*)"\nUSB MSD Application.\nWaiting for USB mass storage to be attached...\n");
}

void time_delay(uint_32 delay) {
  WAIT1_Waitms(delay);
}

int_32 _bsp_usb_host_init(pointer param) {
  return 0;
}

static portTASK_FUNCTION(HostTask, pvParameters) {
  (void)pvParameters; /* not used */
  host_init();
  for(;;) {
    Main_Task();
    Poll();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void HOST_Init(void) {
  host_init();
  for(;;) {
    Main_Task();
    Poll();
  }
  if (FRTOS1_xTaskCreate(HostTask, (signed portCHAR *)"Host", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

