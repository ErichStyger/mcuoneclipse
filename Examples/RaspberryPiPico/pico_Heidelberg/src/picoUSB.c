/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "McuUtility.h"

/* ----------------------------------------------------------------------------------------------------------- */
/* https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/pico_stdio_usb/stdio_usb_descriptors.c
 * SDK 1.4: around line 147
 * change call of pico_get_unique_board_id_string() to the following:  */
#if 0
  #if 1 /* << EST */
      extern void pico_usb_get_unique_board_id_string(char *id_out, uint len);
      pico_usb_get_unique_board_id_string(usbd_serial_str, sizeof(usbd_serial_str));
  #else
        pico_get_unique_board_id_string(usbd_serial_str, sizeof(usbd_serial_str));
  #endif
#endif

void pico_usb_get_unique_board_id_string(char *id_out, uint len) {
#if 0 /* original version */
  pico_get_unique_board_id_string(id_out, len); /* default */
#else /* use same USB serial number for all boards, so sharing the same COM interface */
  McuUtility_strcpy(id_out, len, "Pico");
#endif
}
/* ----------------------------------------------------------------------------------------------------------- */


