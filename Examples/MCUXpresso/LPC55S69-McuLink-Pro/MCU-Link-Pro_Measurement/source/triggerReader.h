/*
 * triggerReader.h
 *
 * Created on: 23 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

/* This file currently has no use
 * It is a relic of trying to implement an UART-like soft-interface
 * This would have been the command processing logic
 * to be used in the MCU-Link Pro Device
 */
typedef enum
{
    TRIGGER_READY,
    TRIGGER_PROCESSING,
    TRIGGER_DONE
} trigger_reader_t;

void enable_PinInterrupt(void);