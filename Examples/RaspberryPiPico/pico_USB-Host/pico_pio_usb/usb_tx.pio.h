// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

#define IRQ_TX_EOP 0

// ----------- //
// usb_tx_dpdm //
// ----------- //

#define usb_tx_dpdm_wrap_target 1
#define usb_tx_dpdm_wrap 4

static const uint16_t usb_tx_dpdm_program_instructions[] = {
    0xc700, //  0: irq    nowait 0        side 0 [7] 
            //     .wrap_target
    0x6ba2, //  1: out    pc, 2           side 1 [3] 
    0xeb80, //  2: set    pindirs, 0      side 1 [3] 
    0x73a2, //  3: out    pc, 2           side 2 [3] 
    0xe883, //  4: set    pindirs, 3      side 1     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program usb_tx_dpdm_program = {
    .instructions = usb_tx_dpdm_program_instructions,
    .length = 5,
    .origin = -1,
};

static inline pio_sm_config usb_tx_dpdm_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + usb_tx_dpdm_wrap_target, offset + usb_tx_dpdm_wrap);
    sm_config_set_sideset(&c, 2, false, false);
    return c;
}
#endif

// --------------- //
// usb_tx_pre_dpdm //
// --------------- //

#define usb_tx_pre_dpdm_wrap_target 1
#define usb_tx_pre_dpdm_wrap 4

static const uint16_t usb_tx_pre_dpdm_program_instructions[] = {
    0xcf00, //  0: irq    nowait 0        side 1 [7] 
            //     .wrap_target
    0x6ba2, //  1: out    pc, 2           side 1 [3] 
    0xeb80, //  2: set    pindirs, 0      side 1 [3] 
    0x73a2, //  3: out    pc, 2           side 2 [3] 
    0xe883, //  4: set    pindirs, 3      side 1     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program usb_tx_pre_dpdm_program = {
    .instructions = usb_tx_pre_dpdm_program_instructions,
    .length = 5,
    .origin = -1,
};

static inline pio_sm_config usb_tx_pre_dpdm_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + usb_tx_pre_dpdm_wrap_target, offset + usb_tx_pre_dpdm_wrap);
    sm_config_set_sideset(&c, 2, false, false);
    return c;
}
#endif

// ----------- //
// usb_tx_dmdp //
// ----------- //

#define usb_tx_dmdp_wrap_target 1
#define usb_tx_dmdp_wrap 4

static const uint16_t usb_tx_dmdp_program_instructions[] = {
    0xc700, //  0: irq    nowait 0        side 0 [7] 
            //     .wrap_target
    0x73a2, //  1: out    pc, 2           side 2 [3] 
    0xf380, //  2: set    pindirs, 0      side 2 [3] 
    0x6ba2, //  3: out    pc, 2           side 1 [3] 
    0xf083, //  4: set    pindirs, 3      side 2     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program usb_tx_dmdp_program = {
    .instructions = usb_tx_dmdp_program_instructions,
    .length = 5,
    .origin = -1,
};

static inline pio_sm_config usb_tx_dmdp_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + usb_tx_dmdp_wrap_target, offset + usb_tx_dmdp_wrap);
    sm_config_set_sideset(&c, 2, false, false);
    return c;
}
#endif

// --------------- //
// usb_tx_pre_dmdp //
// --------------- //

#define usb_tx_pre_dmdp_wrap_target 1
#define usb_tx_pre_dmdp_wrap 4

static const uint16_t usb_tx_pre_dmdp_program_instructions[] = {
    0xd700, //  0: irq    nowait 0        side 2 [7] 
            //     .wrap_target
    0x73a2, //  1: out    pc, 2           side 2 [3] 
    0xf380, //  2: set    pindirs, 0      side 2 [3] 
    0x6ba2, //  3: out    pc, 2           side 1 [3] 
    0xf083, //  4: set    pindirs, 3      side 2     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program usb_tx_pre_dmdp_program = {
    .instructions = usb_tx_pre_dmdp_program_instructions,
    .length = 5,
    .origin = -1,
};

static inline pio_sm_config usb_tx_pre_dmdp_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + usb_tx_pre_dmdp_wrap_target, offset + usb_tx_pre_dmdp_wrap);
    sm_config_set_sideset(&c, 2, false, false);
    return c;
}

#include "hardware/clocks.h"
  static void __no_inline_not_in_flash_func(usb_tx_configure_pins)(PIO pio, uint sm, uint pin_dp, uint pin_dm) {
    if (pin_dp < pin_dm) {
      pio_sm_set_out_pins(pio, sm, pin_dp, 2);
      pio_sm_set_set_pins(pio, sm, pin_dp, 2);
      pio_sm_set_sideset_pins(pio, sm, pin_dp);
    } else {
      pio_sm_set_out_pins(pio, sm, pin_dm, 2);
      pio_sm_set_set_pins(pio, sm, pin_dm, 2);
      pio_sm_set_sideset_pins(pio, sm, pin_dm);
    }
  }
  static inline void usb_tx_fs_program_init(PIO pio, uint sm, uint offset,
                                         uint pin_dp, uint pin_dm) {
    pio_sm_set_pins_with_mask(pio, sm, (1 << pin_dp), ((1 << pin_dp) | (1 << pin_dm)));
    gpio_pull_down(pin_dp);
    gpio_pull_down(pin_dm);
    pio_gpio_init(pio, pin_dp);
    pio_gpio_init(pio, pin_dm);
    pio_sm_config c = usb_tx_dpdm_program_get_default_config(offset);
    // shifts to left, autopull, 8bit
    sm_config_set_out_shift(&c, false, true, 8);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    // run at 48MHz
    // clk_sys should be multiply of 12MHz
    float div = (float)clock_get_hz(clk_sys) / (48000000UL);
    sm_config_set_clkdiv(&c, div);
    pio_sm_init(pio, sm, offset + 1, &c);
    usb_tx_configure_pins(pio, sm, pin_dp, pin_dm);
    pio_sm_set_enabled(pio, sm, true);
  }
  static inline void usb_tx_ls_program_init(PIO pio, uint sm, uint offset,
                                         uint pin_dp, uint pin_dm) {
    pio_sm_set_pins_with_mask(pio, sm, (1 << pin_dm), ((1 << pin_dp) | (1 << pin_dm)));
    gpio_pull_down(pin_dp);
    gpio_pull_down(pin_dm);
    pio_gpio_init(pio, pin_dp);
    pio_gpio_init(pio, pin_dm);
    pio_sm_config c = usb_tx_dmdp_program_get_default_config(offset);
    // shifts to left, autopull, 8bit
    sm_config_set_out_shift(&c, false, true, 8);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    // run at 6MHz
    // clk_sys should be multiply of 12MHz
    float div = (float)clock_get_hz(clk_sys) / (6000000UL);
    sm_config_set_clkdiv(&c, div);
    pio_sm_init(pio, sm, offset + 1, &c);
    usb_tx_configure_pins(pio, sm, pin_dp, pin_dm);
    pio_sm_set_enabled(pio, sm, true);
  }

#endif

