/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022, Ha Thach (tinyusb.org)
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
 * This file is part of the TinyUSB stack.
 */

#include "platform.h"
#if PL_CONFIG_USE_USB_HOST_CDC

#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

#include "pio_usb.h"
#include "bsp/board.h"

#include "tusb.h"

//#include "bsp/board_api.h"

/*------------- MAIN -------------*/

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

#if 0
int board_getchar(void) {
  return 0; /* \todo */
}
#endif

size_t get_console_inputs(uint8_t* buf, size_t bufsize) {
  size_t count = 0;
  while (count < bufsize) {
    int ch = board_getchar();
    if (ch <= 0) break;

    buf[count] = (uint8_t) ch;
    count++;
  }
  return count;
}

void cdc_app_task(void) {
  uint8_t buf[64 + 1]; // +1 for extra null character
  uint32_t const bufsize = sizeof(buf) - 1;

  uint32_t count = get_console_inputs(buf, bufsize);
  buf[count] = 0;

  // loop over all mounted interfaces
  for (uint8_t idx = 0; idx < CFG_TUH_CDC; idx++) {
    if (tuh_cdc_mounted(idx)) {
      // console --> cdc interfaces
      if (count) {
        tuh_cdc_write(idx, buf, count);
        tuh_cdc_write_flush(idx);
      }
    }
  }
}

//--------------------------------------------------------------------+
// TinyUSB callbacks
//--------------------------------------------------------------------+

// Invoked when received new data
void tuh_cdc_rx_cb(uint8_t idx) {
  uint8_t buf[64 + 1]; // +1 for extra null character
  uint32_t const bufsize = sizeof(buf) - 1;

  // forward cdc interfaces -> console
  uint32_t count = tuh_cdc_read(idx, buf, bufsize);
  buf[count] = 0;

  printf("%s", (char*) buf);
}

void tuh_cdc_mount_cb(uint8_t idx)
{
  tuh_cdc_itf_info_t itf_info = { 0 };
  tuh_cdc_itf_get_info(idx, &itf_info);

  printf("CDC Interface is mounted: address = %u, itf_num = %u\r\n", itf_info.daddr, itf_info.bInterfaceNumber);

#ifdef CFG_TUH_CDC_LINE_CODING_ON_ENUM
  // CFG_TUH_CDC_LINE_CODING_ON_ENUM must be defined for line coding is set by tinyusb in enumeration
  // otherwise you need to call tuh_cdc_set_line_coding() first
  cdc_line_coding_t line_coding = { 0 };
  if ( tuh_cdc_get_local_line_coding(idx, &line_coding) )
  {
    printf("  Baudrate: %lu, Stop Bits : %u\r\n", line_coding.bit_rate, line_coding.stop_bits);
    printf("  Parity  : %u, Data Width: %u\r\n", line_coding.parity  , line_coding.data_bits);
  }
#endif
}

void tuh_cdc_umount_cb(uint8_t idx)
{
  tuh_cdc_itf_info_t itf_info = { 0 };
  tuh_cdc_itf_get_info(idx, &itf_info);

  printf("CDC Interface is unmounted: address = %u, itf_num = %u\r\n", itf_info.daddr, itf_info.bInterfaceNumber);
}


#endif /* PL_CONFIG_USE_USB_HOST_CDC */