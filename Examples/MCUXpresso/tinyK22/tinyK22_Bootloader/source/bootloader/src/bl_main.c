/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define exit exit_default
#include <stdbool.h>
#include "utilities/fsl_assert.h"
#include "bootloader/bl_context.h"
#include "bootloader/bl_peripheral.h"
#include "bootloader/bl_shutdown_cleanup.h"
#include "bootloader_common.h"
#include "bootloader/bootloader.h"
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
#include "fsl_flash.h"
#else
#include "flashiap_wrapper/fsl_flashiap_wrapper.h"
#endif
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#include "smc.h"
#include "microseconds.h"
#include "property/property.h"
#include "utilities/vector_table_info.h"
#include "utilities/fsl_rtos_abstraction.h"
#if BL_FEATURE_CRC_CHECK
#include "bootloader/bl_app_crc_check.h"
#endif
#if BL_FEATURE_QSPI_MODULE
#include "qspi.h"
#endif
#include "memory/memory.h"

#if BL_FEATURE_RELIABLE_UPDATE
#include "bootloader/bl_reliable_update.h"
#endif

//! @addtogroup bl_core
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
static const char *get_peripheral_name(uint32_t peripheralTypeMask);
#endif

#if !BL_FEATURE_TIMEOUT
static void get_user_application_entry(uint32_t *appEntry, uint32_t *appStack);
static void jump_to_application(uint32_t applicationAddress, uint32_t stackPointer);
static bool is_direct_boot(void);
#endif // !BL_FEATURE_TIMEOUT
static peripheral_descriptor_t const *get_active_peripheral(void);
static void bootloader_init(void);
static void bootloader_run(void);
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
static void bootloader_flash_init(void);
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if BL_FEATURE_QSPI_MODULE
static void configure_quadspi_as_needed(void);
#endif

int main(void);

// Not used, but needed to resolve reference in startup.s.
// uint32_t g_bootloaderTree;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
static const char *const kPeripheralNames[] = {
    "UART", // kPeripheralType_UART
    "I2C",  // kPeripheralType_I2CSlave
    "SPI",  // kPeripheralType_SPISlave
    "CAN",  // kPeripheralType_CAN
    "HID",  // kPeripheralType_USB_HID
    "CDC",  // kPeripheralType_USB_CDC
    "DFU",  // kPeripheralType_USB_DFU
    "MSD"   // kPeripheralType_USB_MSC
};
#endif // DEBUG

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
//! @brief Returns the name of a peripheral given its type mask.
const char *get_peripheral_name(uint32_t peripheralTypeMask)
{
    uint32_t i;
    for (i = 0; i < ARRAY_SIZE(kPeripheralNames); ++i)
    {
        if (peripheralTypeMask & (1 << i))
        {
            return kPeripheralNames[i];
        }
    }

    return "Unknown peripheral";
}
#endif // DEBUG

#if !BL_FEATURE_TIMEOUT
//! @brief Returns the user application address and stack pointer.
//!
//! For flash-resident and rom-resident target, gets the user application address
//! and stack pointer from the APP_VECTOR_TABLE.
//! Ram-resident version does not support jumping to application address.
static void get_user_application_entry(uint32_t *appEntry, uint32_t *appStack)
{
    assert(appEntry);
    assert(appStack);

#ifdef BL_TARGET_RAM
    *appEntry = 0;
    *appStack = 0;
#else
#if FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
    // Check if address of SP and PC is in an execute-only region.
    if (!is_in_execute_only_region(kDefaultVectorTableAddress, 8))
    {
        *appEntry = APP_VECTOR_TABLE[kInitialPC];
        *appStack = APP_VECTOR_TABLE[kInitialSP];
    }
    else
    {
        // Set to invalid value when vector table is in execute-only region,
        // as ROM doesn't support jumping to an application in such region so far.
        // The main purpose of below operation is to prevent ROM from inifinit loop
        // between NVIC_SystemReset() and fetching SP and PC frome execute-only region.
        *appEntry = 0;
        *appStack = 0;
    }
#else
    *appEntry = APP_VECTOR_TABLE[kInitialPC];
    *appStack = APP_VECTOR_TABLE[kInitialSP];
#endif //  FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
#endif // BL_TARGET_RAM
}
#endif // BL_FEATURE_TIMEOUT

#if !BL_FEATURE_TIMEOUT
bool is_direct_boot(void)
{
    bootloader_configuration_data_t *configurationData =
        &g_bootloaderContext.propertyInterface->store->configurationData;

    return (~configurationData->bootFlags) & kBootFlag_DirectBoot;
}
#endif // !BL_FEATURE_TIMEOUT

#if !BL_FEATURE_TIMEOUT
//! @brief Exits bootloader and jumps to the user application.
static void jump_to_application(uint32_t applicationAddress, uint32_t stackPointer)
{
#if BL_FEATURE_OTFAD_MODULE
    quadspi_cache_clear();
    oftfad_resume_as_needed();
#endif

    shutdown_cleanup(kShutdownType_Shutdown);

    // Create the function call to the user application.
    // Static variables are needed since changed the stack pointer out from under the compiler
    // we need to ensure the values we are using are not stored on the previous stack
    static uint32_t s_stackPointer = 0;
    s_stackPointer = stackPointer;
    static void (*farewellBootloader)(void) = 0;
    farewellBootloader = (void (*)(void))applicationAddress;

    // Set the VTOR to the application vector table address.
    SCB->VTOR = (uint32_t)APP_VECTOR_TABLE;

    // Set stack pointers to the application stack pointer.
    __set_MSP(s_stackPointer);
    __set_PSP(s_stackPointer);

    // Jump to the application.
    farewellBootloader();
    // Dummy fcuntion call, should never go to this fcuntion call
    shutdown_cleanup(kShutdownType_Shutdown);
}
#endif // !BL_FEATURE_TIMEOUT

//! A given jump address is considered valid if:
//! - Not 0x00000000
//! - Not 0xffffffff
//! - Not the reset handler entry point for the bootloader
//! - Is in flash or is in RAM or QuadSPI (if available)
//! @note this interface is also used by the configure_quadspi command
bool is_valid_application_location(uint32_t applicationAddress)
{
    const memory_map_entry_t *map;
    // Verify that the jumpLocation is non zero and then either within flash or RAM, both calculations are:
    // (jumpLocation >= startAddress) && (jumpLocation < (startAddress + size))
    if ((!applicationAddress) ||              // address is not null AND
        (applicationAddress == 0xffffffff) || // address is not blank Flash (0xff) AND
        (applicationAddress == (uint32_t)&Reset_Handler))
    {
        return false;
    }

    bool isValid = false;
    const uint32_t minThumb2InstructionSize = 2; // smallest thumb2 instruction size is 16-bit.
    // Check if the application address is in valid executable memory range
    status_t status = find_map_entry(applicationAddress, minThumb2InstructionSize, &map);
    if ((status == kStatus_Success) && (map->memoryProperty & kMemoryIsExecutable))
    {
        isValid = true;
    }

    return isValid;
}

bool is_valid_stackpointer_location(uint32_t stackpointerAddress)
{
    const memory_map_entry_t *map;
    bool isValid = false;

    map = &g_bootloaderContext.memoryMap[0];

    while (map->memoryInterface != NULL)
    {
        if ((map->memoryProperty & kMemoryIsExecutable) && (map->memoryProperty & kMemoryType_RAM))
        {
            if ((stackpointerAddress > map->startAddress) && (stackpointerAddress <= (map->endAddress + 1)))
            {
                isValid = true;
                break;
            }
        }

        ++map;
    }

    return isValid;
}

#if !BL_FEATURE_TIMEOUT
//! @brief Jump application is considered ready for executing if the location is valid and crc check is passed
static bool is_application_ready_for_executing(uint32_t applicationAddress)
{
    bool result = is_valid_application_location(applicationAddress);

#if BL_FEATURE_OTFAD_MODULE
    if (result && is_qspi_present())
    {
        quadspi_cache_clear();
        status_t status = otfad_init_as_needed();
        if (status != kStatus_Success)
        {
            result = false;
        }
        update_qspi_otfad_init_status(status);
    }
#endif

#if BL_FEATURE_CRC_CHECK
    // Validate application crc only if its location is valid
    if (result)
    {
        result = is_application_crc_check_pass();
    }

#if BL_FEATURE_OTFAD_MODULE
    otfad_bypass_as_needed();
#endif // BL_FEATURE_OTFAD_MODULE

#endif

    return result;
}
#endif // !BL_FEATURE_TIMEOUT

//! @brief Determines the active peripheral.
//!
//! This function has several stages:
//! - Init enabled peripherals.
//! - Compute timeout.
//! - Wait for peripheral activity with timeout.
//! - Shutdown inactive peripherals.
//!
//! If peripheral detection times out, then this function will call jump_to_application() to
//! directly enter the user application.
//!
//! The timeout value comes from the BCA if set, or the #BL_DEFAULT_PERIPHERAL_DETECT_TIMEOUT
//! configuration macro. If the boot pin is asserted, or if there is not a valid user application
//! in flash, then the timeout is disabled and peripheral detection will continue infinitely.
static peripheral_descriptor_t const *get_active_peripheral(void)
{
    peripheral_descriptor_t const *peripheral;
    peripheral_descriptor_t const *activePeripheral = NULL;
    bootloader_configuration_data_t *configurationData =
        &g_bootloaderContext.propertyInterface->store->configurationData;

    // Bring up all the peripherals
    for (peripheral = g_peripherals; peripheral->typeMask != 0; ++peripheral)
    {
        // Check that the peripheral is enabled in the user configuration data
        if (configurationData->enabledPeripherals & peripheral->typeMask)
        {
            assert(peripheral->controlInterface->init);

#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
            debug_printf("Initing %s\r\n", get_peripheral_name(peripheral->typeMask));
#endif
            peripheral->controlInterface->init(peripheral, peripheral->packetInterface->byteReceivedCallback);
        }
    }

#if !BL_FEATURE_TIMEOUT
#if BL_FEATURE_POWERDOWN
    bool shortTimeout = false;
#endif
    const uint64_t ticksPerMillisecond = microseconds_convert_to_ticks(1000);

    // Get the user application entry point and stack pointer.
    uint32_t applicationAddress, stackPointer;
    get_user_application_entry(&applicationAddress, &stackPointer);

    uint64_t lastTicks = 0;    // Value of our last recorded ticks second marker
    uint64_t timeoutTicks = 0; // The number of ticks we will wait for timeout, 0 means no timeout

    // If the boot to rom option is not set AND there is a valid jump application determine the timeout value
    if (!is_boot_pin_asserted() && is_application_ready_for_executing(applicationAddress))
    {
        if (is_direct_boot())
        {
            jump_to_application(applicationAddress, stackPointer);
        }

        // Calculate how many ticks we need to wait based on the bootloader config. Check to see if
        // there is a valid configuration data value for the timeout. If there's not, use the
        // default timeout value.
        uint32_t milliseconds;
        if (configurationData->peripheralDetectionTimeoutMs != 0xFFFF)
        {
            milliseconds = configurationData->peripheralDetectionTimeoutMs;
        }
        else
        {
            milliseconds = BL_DEFAULT_PERIPHERAL_DETECT_TIMEOUT;
        }
        timeoutTicks = milliseconds * ticksPerMillisecond;

        // save how many ticks we're currently at before the detection loop starts
        lastTicks = microseconds_get_ticks();
#if BL_FEATURE_POWERDOWN
        shortTimeout = true;
#endif
    }
#if BL_FEATURE_POWERDOWN
    else
    {
        timeoutTicks = BL_DEFAULT_POWERDOWN_TIMEOUT * ticksPerMillisecond;
        lastTicks = microseconds_get_ticks();
    }
#endif
#endif // !BL_FEATURE_TIMEOUT

    // Wait for a peripheral to become active
    while (activePeripheral == NULL)
    {
#if !BL_FEATURE_TIMEOUT
        // If timeout is enabled, check to see if we've exceeded it.
        if (timeoutTicks)
        {
            // Note that we assume that the tick counter won't overflow and wrap back to 0.
            // The timeout value is only up to 65536 milliseconds, and the tick count starts
            // at zero when when inited the microseconds driver just a few moments ago.
            uint64_t elapsedTicks = microseconds_get_ticks() - lastTicks;

            // Check if the elapsed time is longer than the timeout.
            if (elapsedTicks >= timeoutTicks)
            {
#if BL_FEATURE_POWERDOWN
                if (shortTimeout)
                {
#endif
                    // In the case of the typical peripheral timeout, jump to the user application.
                    jump_to_application(applicationAddress, stackPointer);
#if BL_FEATURE_POWERDOWN
                }
                else
                {
                    // Make sure a timeout value has been defined before shutting down.
                    if (BL_DEFAULT_POWERDOWN_TIMEOUT)
                    {
                        // Shut down the bootloader and return to reset-type state prior to low
                        // power entry
                        shutdown_cleanup(kShutdownType_Shutdown);

                        // Enter VLLS1 low power mode
                        enter_vlls1();
                    }
                }
#endif
            }
        }
#endif // !BL_FEATURE_TIMEOUT
        // Traverse through all the peripherals
        for (peripheral = g_peripherals; peripheral->typeMask != 0; ++peripheral)
        {
            // Check that the peripheral is enabled in the user configuration data
            if (configurationData->enabledPeripherals & peripheral->typeMask)
            {
                assert(peripheral->controlInterface->pollForActivity);

                if (peripheral->controlInterface->pollForActivity(peripheral))
                {
#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
                    debug_printf("%s is active\r\n", get_peripheral_name(peripheral->typeMask));
#endif
                    activePeripheral = peripheral;
                    break;
                }
            }
        }
    }

    // Shut down all non active peripherals
    for (peripheral = g_peripherals; peripheral->typeMask != 0; ++peripheral)
    {
        // Check that the peripheral is enabled in the user configuration data
        if (configurationData->enabledPeripherals & peripheral->typeMask)
        {
            if (activePeripheral != peripheral)
            {
#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
                debug_printf("Shutting down %s\r\n", get_peripheral_name(peripheral->typeMask));
#endif
                assert(peripheral->controlInterface->shutdown);
                peripheral->controlInterface->shutdown(peripheral);
            }
        }
    }

    return activePeripheral;
}

#if BL_FEATURE_QSPI_MODULE
static void configure_quadspi_as_needed(void)
{
    // Start the lifetime counter
    microseconds_init();
    if (qspi_need_configure())
    {
        status_t qspiOtfadInitStatus = kStatus_QspiNotConfigured;
        // Try to configure QuadSPI module based on on qspi_config_block_pointer in BCA first,
        // If bootloader cannot get qspi config block from internal flash, try to configure QSPI
        // based on default place (start address of QuadSPI memory).
        uint32_t qspi_config_block_base =
            g_bootloaderContext.propertyInterface->store->configurationData.qspi_config_block_pointer;

        // Get the start address and flash size
        // Note: Basically BCA is always stored in Main flash memory
        uint32_t flashStart;
        g_bootloaderContext.flashDriverInterface->flash_get_property(
            g_bootloaderContext.allFlashState, kFLASH_PropertyPflash0BlockBaseAddr, &flashStart);
        uint32_t flashSize;
        g_bootloaderContext.flashDriverInterface->flash_get_property(
            g_bootloaderContext.allFlashState, kFLASH_PropertyPflash0TotalSize, &flashSize);

        // Check if the pointer of qspi config block is valid.
        if ((qspi_config_block_base != 0xFFFFFFFF) && (qspi_config_block_base > flashStart) &&
            (qspi_config_block_base <= (flashStart + flashSize - sizeof(qspi_config_t))))
        {
#if FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
            if (!is_in_execute_only_region(qspi_config_block_base, sizeof(qspi_config_t)))
            {
                qspiOtfadInitStatus = quadspi_init((void *)qspi_config_block_base);
            }
#else
            qspiOtfadInitStatus = quadspi_init((void *)qspi_config_block_base);
#endif // FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
        }

        if (qspiOtfadInitStatus == kStatus_QspiNotConfigured)
        {
            qspiOtfadInitStatus = quadspi_init(NULL);
        }
        update_qspi_otfad_init_status(qspiOtfadInitStatus);
    }
    // Shutdown the lifetime counter before configuring clock.
    lock_acquire();
    microseconds_shutdown();
    lock_release();
}
#endif

#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
static void bootloader_flash_init(void)
{
    g_bootloaderContext.flashDriverInterface->flash_init(g_bootloaderContext.allFlashState);
#if !BL_DEVICE_IS_LPC_SERIES
    FTFx_CACHE_Init(g_bootloaderContext.allFlashCacheState);
#endif
#if BL_FEATURE_SUPPORT_DFLASH
    check_available_dFlash();
    if (g_bootloaderContext.dflashDriverInterface != NULL)
    {
        g_bootloaderContext.dflashDriverInterface->flash_init(g_bootloaderContext.dFlashState);
    }
#endif // BL_FEATURE_SUPPORT_DFLASH    
}
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH

//! @brief Initialize the bootloader and peripherals.
//!
//! This function initializes hardware and clocks, loads user configuration data, and initialzes
//! a number of drivers. It then enters the active peripheral detection phase by calling
//! get_active_peripheral(). Once the peripheral is detected, the packet and comand interfaces
//! are initialized.
//!
//! Note that this routine may not return if peripheral detection times out and the bootloader
//! jumps directly to the user application in flash.
static void bootloader_init(void)
{
    // Init the global irq lock
    lock_init();

    // Init pinmux and other hardware setup.
    init_hardware();

#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
    // Init flash driver.
    bootloader_flash_init();
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH

    // Load the user configuration data so that we can configure the clocks
    g_bootloaderContext.propertyInterface->load_user_config();

// Init QSPI module if needed
#if BL_FEATURE_QSPI_MODULE
    configure_quadspi_as_needed();
#endif // BL_FEATURE_QSPI_MODULE

    // Configure clocks.
    configure_clocks(kClockOption_EnterBootloader);

    // Start the lifetime counter
    microseconds_init();

#if BL_FEATURE_BYPASS_WATCHDOG
    bootloader_watchdog_init();
#endif // BL_FEATURE_BYPASS_WATCHDOG

    // Init address range of flash array, SRAM_L and SRAM U.
    g_bootloaderContext.memoryInterface->init();

    // Fully init the property store.
    g_bootloaderContext.propertyInterface->init();

#if BL_FEATURE_RELIABLE_UPDATE
    bootloader_reliable_update_as_requested(kReliableUpdateOption_Normal, 0);
#endif // BL_FEATURE_RELIABLE_UPDATE

    // Message so python instantiated debugger can tell the
    // bootloader application is running on the target.
    debug_printf("\r\n\r\nRunning bootloader...\r\n");

#if defined(DEBUG) && !defined(DEBUG_PRINT_DISABLE)
    standard_version_t version = g_bootloaderContext.propertyInterface->store->bootloaderVersion;
    debug_printf("Bootloader version %c%d.%d.%d\r\n", version.name, version.major, version.minor, version.bugfix);
#endif

    //    generate_key_blob_test();

    // Wait for a peripheral to become active.
    g_bootloaderContext.activePeripheral = get_active_peripheral();
    assert(g_bootloaderContext.activePeripheral);

    // Validate required active peripheral interfaces.
    assert(g_bootloaderContext.activePeripheral->controlInterface);

#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
    // Fully configure the pinmux
    if (g_bootloaderContext.activePeripheral->pinmuxConfig)
    {
        g_bootloaderContext.activePeripheral->pinmuxConfig(g_bootloaderContext.activePeripheral->instance,
                                                           kPinmuxType_Peripheral);
    }
#endif // BL_FEATURE_6PINS_PERIPHERAL

    // Init the active peripheral.
    if (g_bootloaderContext.activePeripheral->byteInterface &&
        g_bootloaderContext.activePeripheral->byteInterface->init)
    {
        g_bootloaderContext.activePeripheral->byteInterface->init(g_bootloaderContext.activePeripheral);
    }
    if (g_bootloaderContext.activePeripheral->packetInterface &&
        g_bootloaderContext.activePeripheral->packetInterface->init)
    {
        g_bootloaderContext.activePeripheral->packetInterface->init(g_bootloaderContext.activePeripheral);
    }

    // Initialize the command processor component.
    g_bootloaderContext.commandInterface->init();
}

//! @brief Bootloader outer loop.
//!
//! Infinitely calls the command interface and active peripheral control interface pump routines.
static void bootloader_run(void)
{
    const peripheral_descriptor_t *activePeripheral = g_bootloaderContext.activePeripheral;

    assert(g_bootloaderContext.commandInterface->pump);

    // Read and execute commands.
    while (1)
    {
        g_bootloaderContext.commandInterface->pump();

        // Pump the active peripheral.
        if (activePeripheral->controlInterface->pump)
        {
            activePeripheral->controlInterface->pump(activePeripheral);
        }
    }
}

//! @brief Entry point for the bootloader.
int main(void)
{
    bootloader_init();
    bootloader_run();

    // Should never end up here.
    debug_printf("Warning: reached end of main()\r\n");
    return 0;
}

//! Since we never exit this gets rid of the C standard functions that cause
//! extra ROM size usage.
#undef exit
void exit(int arg)
{
}

#if defined(__CC_ARM)
#define ITM_Port8(n) (*((volatile unsigned char *)(0xE0000000 + 4 * n)))
#define ITM_Port16(n) (*((volatile unsigned short *)(0xE0000000 + 4 * n)))
#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000 + 4 * n)))

#define DEMCR (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA 0x01000000

struct __FILE
{
    int handle; /* Add whatever needed */
};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
    if (DEMCR & TRCENA)
    {
        while (ITM_Port32(0) == 0)
            ;
        ITM_Port8(0) = ch;
    }
    return (ch);
}
#endif

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
