#include "platform.h"
#if PL_CONFIG_USE_USB_HOST_INFO
/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/* Host example will get device descriptors of attached devices and print it out via device cdc as follows:
 *    Device 1: ID 046d:c52f SN 11223344
      Device Descriptor:
        bLength             18
        bDescriptorType     1
        bcdUSB              0200
        bDeviceClass        0
        bDeviceSubClass     0
        bDeviceProtocol     0
        bMaxPacketSize0     8
        idVendor            0x046d
        idProduct           0xc52f
        bcdDevice           2200
        iManufacturer       1     Logitech
        iProduct            2     USB Receiver
        iSerialNumber       0
        bNumConfigurations  1
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

#include "pio_usb.h"

//#include "bsp/board_api.h"
#include "tusb.h"

#include "hardware/timer.h" /* << EST: needed for CMSIS-DAP debugging */

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+
// Language ID: English
#define LANGUAGE_ID 0x0409

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

static bool is_print[CFG_TUH_DEVICE_MAX+1] = { 0 };

static void print_utf16(uint16_t *temp_buf, size_t buf_len);
void led_blinking_task(void);
void cdc_task(void);

/*------------- MAIN -------------*/
#if 0 /* original code */
int main(void) {
  board_init();

  printf("TinyUSB Host Information -> Device CDC Example\r\n");

  // init device and host stack on configured roothub port
  tusb_rhport_init_t dev_init = {
    .role = TUSB_ROLE_DEVICE,
    .speed = TUSB_SPEED_AUTO
  };
  tusb_init(BOARD_TUD_RHPORT, &dev_init);

  tusb_rhport_init_t host_init = {
    .role = TUSB_ROLE_HOST,
    .speed = TUSB_SPEED_AUTO
  };
  tusb_init(BOARD_TUH_RHPORT, &host_init);

  if (board_init_after_tusb) {
    board_init_after_tusb();
  }

  while (1) {
    tud_task(); // tinyusb device task
    tuh_task(); // tinyusb host task
    cdc_task();
    led_blinking_task();
  }

  return 0;
}
#else

// core1: handle host events
void core1_main(void) {
  sleep_ms(10);

  // Use tuh_configure() to pass pio configuration to the host stack
  // Note: tuh_configure() must be called before
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_cfg);

  // To run USB SOF interrupt in core1, init host stack for pio_usb (roothub
  // port1) on core1
  tuh_init(1);
  while (true) {
    tuh_task(); // tinyusb host task
  }
}

#include "McuLib.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "usbHost.h"
#include "leds.h"

// core0: handle device events
int main(void) {
  // default 125MHz is not appropreate. Sysclock should be multiple of 12MHz.
  set_sys_clock_khz(120000, true);

#if 1 /* workaround for CMSIS-DAP, see https://github.com/raspberrypi/pico-sdk/issues/1152 */
//  timer_hw->dbgpause = 0;
#endif

  /* initialize McuLib parts: */
  McuLib_Init();
  McuGPIO_Init();
  #if PL_CONFIG_USE_LEDS
  McuLED_Init();
  Leds_Init();
  #endif
  UsbHost_Init();
  UsbHost_PowerEnable(true);

  sleep_ms(10);
#if 1
  multicore_reset_core1();
  // all USB task run in core1
  multicore_launch_core1(core1_main);
#endif
  // init device stack on native usb (roothub port0)
  tud_init(0);
 
  uint32_t cntr = 0;
  while (true) {
    tud_task(); // tinyusb device task
    cntr++;
    if((cntr%100000)==0) {
      //tud_cdc_write_str("a\n");
      #if PL_CONFIG_USE_LEDS
      Leds_Neg(LEDS_ONBOARD);
      #endif
    }
    tud_cdc_write_flush();
  }
  return 0;
}
#endif

//--------------------------------------------------------------------+
// Device CDC
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) {
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
  blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
}

#if 1
#define cdc_printf(...)                          \
  do {                                           \
    char _tempbuf[256];                          \
    int count = sprintf(_tempbuf, __VA_ARGS__);  \
    tud_cdc_write(_tempbuf, (uint32_t) count);   \
    tud_cdc_write_flush();                       \
    tud_task();                                  \
  } while(0)
#endif

//#define cdc_printf printf

void print_device_info(uint8_t daddr) {
  tusb_desc_device_t desc_device;
  uint8_t xfer_result = tuh_descriptor_get_device_sync(daddr, &desc_device, 18);
  if (XFER_RESULT_SUCCESS != xfer_result) {
    tud_cdc_write_str("Failed to get device descriptor\r\n");
    return;
  }

  // Get String descriptor using Sync API
  uint16_t serial[64];
  uint16_t buf[128];

  cdc_printf("Device %u: ID %04x:%04x SN ", daddr, desc_device.idVendor, desc_device.idProduct);
  xfer_result = tuh_descriptor_get_serial_string_sync(daddr, LANGUAGE_ID, serial, sizeof(serial));
  if (XFER_RESULT_SUCCESS != xfer_result) {
    serial[0] = 'n';
    serial[1] = '/';
    serial[2] = 'a';
    serial[3] = 0;
  }
  print_utf16(serial, TU_ARRAY_SIZE(serial));
  tud_cdc_write_str("\r\n");

  cdc_printf("Device Descriptor:\r\n");
  cdc_printf("  bLength             %u\r\n"     , desc_device.bLength);
  cdc_printf("  bDescriptorType     %u\r\n"     , desc_device.bDescriptorType);
  cdc_printf("  bcdUSB              %04x\r\n"   , desc_device.bcdUSB);
  cdc_printf("  bDeviceClass        %u\r\n"     , desc_device.bDeviceClass);
  cdc_printf("  bDeviceSubClass     %u\r\n"     , desc_device.bDeviceSubClass);
  cdc_printf("  bDeviceProtocol     %u\r\n"     , desc_device.bDeviceProtocol);
  cdc_printf("  bMaxPacketSize0     %u\r\n"     , desc_device.bMaxPacketSize0);
  cdc_printf("  idVendor            0x%04x\r\n" , desc_device.idVendor);
  cdc_printf("  idProduct           0x%04x\r\n" , desc_device.idProduct);
  cdc_printf("  bcdDevice           %04x\r\n"   , desc_device.bcdDevice);

  cdc_printf("  iManufacturer       %u     "     , desc_device.iManufacturer);
  xfer_result = tuh_descriptor_get_manufacturer_string_sync(daddr, LANGUAGE_ID, buf, sizeof(buf));
  if (XFER_RESULT_SUCCESS == xfer_result ) {
    print_utf16(buf, TU_ARRAY_SIZE(buf));
  }
  tud_cdc_write_str("\r\n");

  cdc_printf("  iProduct            %u     "     , desc_device.iProduct);
  xfer_result = tuh_descriptor_get_product_string_sync(daddr, LANGUAGE_ID, buf, sizeof(buf));
  if (XFER_RESULT_SUCCESS == xfer_result) {
    print_utf16(buf, TU_ARRAY_SIZE(buf));
  }
  tud_cdc_write_str("\r\n");

  cdc_printf("  iSerialNumber       %u     "     , desc_device.iSerialNumber);
  tud_cdc_write_str((char*)serial); // serial is already to UTF-8
  tud_cdc_write_str("\r\n");

  cdc_printf("  bNumConfigurations  %u\r\n"     , desc_device.bNumConfigurations);
}

void cdc_task(void) {
  if (tud_cdc_connected()) {
    for (uint8_t daddr = 1; daddr <= CFG_TUH_DEVICE_MAX; daddr++) {
      if (tuh_mounted(daddr)) {
        if (is_print[daddr]) {
          is_print[daddr] = false;
          print_device_info(daddr);
          tud_cdc_write_flush();
        }
      }
    }
  }
}

//--------------------------------------------------------------------+
// Host Get device information
//--------------------------------------------------------------------+
void tuh_mount_cb(uint8_t daddr) {
  printf("mounted device %u\r\n", daddr);
  is_print[daddr] = true;
}

void tuh_umount_cb(uint8_t daddr) {
  printf("unmounted device %u\r\n", daddr);
  is_print[daddr] = false;
}

#if 0
//--------------------------------------------------------------------+
// Blinking Task
//--------------------------------------------------------------------+
void led_blinking_task(void) {
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // Blink every interval ms
  if (board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}
#endif

//--------------------------------------------------------------------+
// String Descriptor Helper
//--------------------------------------------------------------------+

static void _convert_utf16le_to_utf8(const uint16_t *utf16, size_t utf16_len, uint8_t *utf8, size_t utf8_len) {
  // TODO: Check for runover.
  (void)utf8_len;
  // Get the UTF-16 length out of the data itself.

  for (size_t i = 0; i < utf16_len; i++) {
    uint16_t chr = utf16[i];
    if (chr < 0x80) {
      *utf8++ = chr & 0xffu;
    } else if (chr < 0x800) {
      *utf8++ = (uint8_t)(0xC0 | (chr >> 6 & 0x1F));
      *utf8++ = (uint8_t)(0x80 | (chr >> 0 & 0x3F));
    } else {
      // TODO: Verify surrogate.
      *utf8++ = (uint8_t)(0xE0 | (chr >> 12 & 0x0F));
      *utf8++ = (uint8_t)(0x80 | (chr >> 6 & 0x3F));
      *utf8++ = (uint8_t)(0x80 | (chr >> 0 & 0x3F));
    }
    // TODO: Handle UTF-16 code points that take two entries.
  }
}

// Count how many bytes a utf-16-le encoded string will take in utf-8.
static int _count_utf8_bytes(const uint16_t *buf, size_t len) {
  size_t total_bytes = 0;
  for (size_t i = 0; i < len; i++) {
    uint16_t chr = buf[i];
    if (chr < 0x80) {
      total_bytes += 1;
    } else if (chr < 0x800) {
      total_bytes += 2;
    } else {
      total_bytes += 3;
    }
    // TODO: Handle UTF-16 code points that take two entries.
  }
  return (int) total_bytes;
}

static void print_utf16(uint16_t *temp_buf, size_t buf_len) {
  if ((temp_buf[0] & 0xff) == 0) return;  // empty
  size_t utf16_len = ((temp_buf[0] & 0xff) - 2) / sizeof(uint16_t);
  size_t utf8_len = (size_t) _count_utf8_bytes(temp_buf + 1, utf16_len);
  _convert_utf16le_to_utf8(temp_buf + 1, utf16_len, (uint8_t *) temp_buf, sizeof(uint16_t) * buf_len);
  ((uint8_t*) temp_buf)[utf8_len] = '\0';

  tud_cdc_write(temp_buf, utf8_len);
  tud_cdc_write_flush();
  tud_task();
}

// Invoked when received report from device via interrupt endpoint
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) len;
  #if 0
  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  switch(itf_protocol)
  {
    case HID_ITF_PROTOCOL_KEYBOARD:
      process_kbd_report(dev_addr, (hid_keyboard_report_t const*) report );
      break;

    case HID_ITF_PROTOCOL_MOUSE:
      process_mouse_report(dev_addr, (hid_mouse_report_t const*) report );
      break;

    default: break;
  }
#endif
  // continue to request to receive report
  if ( !tuh_hid_receive_report(dev_addr, instance) )
  {
    tud_cdc_write_str("Error: cannot request report\r\n");
  }
}

// Invoked when device with hid interface is mounted
// Report descriptor is also available for use. tuh_hid_parse_report_descriptor()
// can be used to parse common/simple enough descriptor.
// Note: if report descriptor length > CFG_TUH_ENUMERATION_BUFSIZE, it will be skipped
// therefore report_desc = NULL, desc_len = 0
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
{
  (void)desc_report;
  (void)desc_len;
#if 0
  // Interface protocol (hid_interface_protocol_enum_t)
  const char* protocol_str[] = { "None", "Keyboard", "Mouse" };
  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  uint16_t vid, pid;
  tuh_vid_pid_get(dev_addr, &vid, &pid);

  char tempbuf[256];
  int count = sprintf(tempbuf, "[%04x:%04x][%u] HID Interface%u, Protocol = %s\r\n", vid, pid, dev_addr, instance, protocol_str[itf_protocol]);

  tud_cdc_write(tempbuf, count);
  tud_cdc_write_flush();

  // Receive report from boot keyboard & mouse only
  // tuh_hid_report_received_cb() will be invoked when report is available
  if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD || itf_protocol == HID_ITF_PROTOCOL_MOUSE)
  {
    if ( !tuh_hid_receive_report(dev_addr, instance) )
    {
      tud_cdc_write_str("Error: cannot request report\r\n");
    }
  }
  #endif
}

#endif /* PL_CONFIG_USE_USB_HOST_INFO */