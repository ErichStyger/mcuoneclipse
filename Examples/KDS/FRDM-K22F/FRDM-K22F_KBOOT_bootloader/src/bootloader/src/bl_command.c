/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "bootloader_common.h"
#include "bootloader/bootloader.h"
#include "memory/memory.h"
#include "sbloader/sbloader.h"
#include "property/property.h"
#include "utilities/fsl_assert.h"
#include "utilities/fsl_rtos_abstraction.h"
#include <string.h>
#include <stdint.h>

#if !defined(BOOTLOADER_HOST)
#include "flash/fsl_flash.h"
#include "fsl_device_registers.h"
#if BL_FEATURE_QSPI_MODULE
#include "qspi/qspi.h"
#endif // #if BL_FEATURE_QSPI_MODULE
#if BL_FEATURE_OTFAD_MODULE
#include "otfad/fsl_otfad_driver.h"
#endif // #if BL_FEATURE_OTFAD_MODULE
#endif

#if BL_FEATURE_RELIABLE_UPDATE
#include "bootloader/bl_reliable_update.h"
#endif

//! @addtogroup command
//! @{

//! @name State machine
//@{
static status_t handle_command(uint8_t *packet, uint32_t packetLength);
static status_t handle_data(bool *hasMoreData);
//@}

//! @name Command handlers
//@{
void handle_reset(uint8_t *packet, uint32_t packetLength);
void handle_flash_erase_all(uint8_t *packet, uint32_t packetLength);
void handle_flash_erase_all_unsecure(uint8_t *packet, uint32_t packetLength);
void handle_flash_erase_region(uint8_t *packet, uint32_t packetLength);
void handle_receive_sb_file(uint8_t *packet, uint32_t packetLength);
void handle_read_memory(uint8_t *packet, uint32_t packetLength);
void handle_fill_memory(uint8_t *packet, uint32_t packetLength);
void handle_set_property(uint8_t *packet, uint32_t packetLength);
void handle_get_property(uint8_t *packet, uint32_t packetLength);
void handle_write_memory(uint8_t *packet, uint32_t packetLength);
void handle_execute(uint8_t *packet, uint32_t packetLength);
void handle_call(uint8_t *packet, uint32_t packetLength);
void handle_flash_security_disable(uint8_t *packet, uint32_t packetLength);
void handle_flash_program_once(uint8_t *packet, uint32_t length);
void handle_flash_read_once(uint8_t *packet, uint32_t length);
void handle_flash_read_resource(uint8_t *packet, uint32_t length);
void handle_configure_quadspi(uint8_t *packet, uint32_t packetLength);
void handle_reliable_update(uint8_t *packet, uint32_t packetLength);
//@}

//! @name Command responses
//@{
void send_read_memory_response(uint32_t commandStatus, uint32_t length);
void send_generic_response(uint32_t commandStatus, uint32_t commandTag);
void send_get_property_response(uint32_t commandStatus, uint32_t *value, uint32_t numValues);
void send_flash_read_once_response(uint32_t commandStatus, uint32_t *value, uint32_t byteCount);
void send_flash_read_resource_response(uint32_t commandStatus, uint32_t length);
//@}

//! @name Data phase
//@{
static void reset_data_phase(void);
void finalize_data_phase(status_t status);
status_t handle_data_producer(bool *hasMoreData);
status_t handle_data_consumer(bool *hasMoreData);
//@}

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//#define TEST_SENDER_ABORT
//#define TEST_RECEIVER_ABORT

enum _secure_commands
{
    //! @brief Bitmask of commands allowed when flash security is enabled.
    //!
    //! This bitmask uses the same format as the AvailableCommands property. This is,
    //! the bit number for a given command is the command's tag value minus one.
    kCommandsAllowedWhenSecure = (HAS_CMD(kCommandTag_FlashSecurityDisable) | HAS_CMD(kCommandTag_GetProperty) |
                                  HAS_CMD(kCommandTag_Reset) | HAS_CMD(kCommandTag_SetProperty) |
                                  HAS_CMD(kCommandTag_FlashEraseAllUnsecure) | HAS_CMD(kCommandTag_ReceiveSbFile))
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Command handler table.
const command_handler_entry_t g_commandHandlerTable[] = {
// cmd handler              // data handler or NULL
#if !BL_FEATURE_MIN_PROFILE
    { handle_flash_erase_all, NULL },              // kCommandTag_FlashEraseAll = 0x01
    { handle_flash_erase_region, NULL },           // kCommandTag_FlashEraseRegion = 0x02
    { handle_read_memory, handle_data_producer },  // kCommandTag_ReadMemory = 0x03
    { handle_write_memory, handle_data_consumer }, // kCommandTag_WriteMemory = 0x04
    { handle_fill_memory, NULL },                  // kCommandTag_FillMemory = 0x05
#if BL_FEATURE_FLASH_SECURITY
    { handle_flash_security_disable, NULL }, // kCommandTag_FlashSecurityDisable = 0x06
#else
    { 0 },
#endif                                                // BL_FEATURE_FLASH_SECURITY
    { handle_get_property, NULL },                    // kCommandTag_GetProperty = 0x07
    { handle_receive_sb_file, handle_data_consumer }, // kCommandTag_ReceiveSbFile = 0x08
    { handle_execute, NULL },                         // kCommandTag_Execute = 0x09
    { handle_call, NULL },                            // kCommandTag_Call = 0x0a
    { handle_reset, NULL },                           // kCommandTag_Reset = 0x0b
    { handle_set_property, NULL },                    // kCommandTag_SetProperty = 0x0c
#if BL_FEATURE_ERASEALL_UNSECURE
    { handle_flash_erase_all_unsecure, NULL }, // kCommandTag_FlashEraseAllUnsecure = 0x0d
#else  // BL_FEATURE_ERASEALL_UNSECURE
    { 0 }, // kCommandTag_FlashEraseAllUnsecure = 0x0d
#endif // BL_FEATURE_ERASEALL_UNSECURE
    { handle_flash_program_once, NULL },                  // kCommandTag_ProgramOnce = 0x0e
    { handle_flash_read_once, NULL },                     // kCommandTag_ReadOnce = 0x0f
    { handle_flash_read_resource, handle_data_producer }, // kCommandTag_ReadResource = 0x10
#if BL_FEATURE_QSPI_MODULE
    { handle_configure_quadspi, NULL }, // kCommandTag_ConfigureQuadSpi = 0x11
#else                                   // BL_FEATURE_QSPI_MODULE
    { 0 }, // kCommandTag_ConfigureQuadSpi = 0x11
#endif                                  // BL_FEATURE_QSPI_MODULE
#if BL_FEATURE_RELIABLE_UPDATE
    { handle_reliable_update, NULL }, // kCommandTag_ReliableUpdate = 0x12
#else
    { 0 }, // kCommandTag_ReliableUpdate = 0x12
#endif // BL_FEATURE_RELIABLE_UPDATE

#else // BL_FEATURE_MIN_PROFILE
    { handle_flash_erase_all, NULL },    // kCommandTag_FlashEraseAll = 0x01
    { handle_flash_erase_region, NULL }, // kCommandTag_FlashEraseRegion = 0x02
#if BL_FEATURE_READ_MEMORY
    { handle_read_memory, handle_data_producer }, // kCommandTag_ReadMemory = 0x03
#else // BL_FEATURE_READ_MEMORY
    { 0 }, // kCommandTag_ReadMemory = 0x03
#endif
    { handle_write_memory, handle_data_consumer }, // kCommandTag_WriteMemory = 0x04
#if BL_FEATURE_FILL_MEMORY
    { handle_fill_memory, NULL }, // kCommandTag_FillMemory = 0x05
#else
    { 0 },
#endif // BL_FEATURE_FILL_MEMORY
#if BL_FEATURE_FLASH_SECURITY
    { handle_flash_security_disable, NULL }, // kCommandTag_FlashSecurityDisable = 0x06
#else
    { 0 },
#endif // BL_FEATURE_FLASH_SECURITY
    { handle_get_property, NULL },             // kCommandTag_GetProperty = 0x07
    { 0 },                                     // kCommandTag_ReceiveSbFile = 0x08
    { handle_execute, NULL },                  // kCommandTag_Execute = 0x09
    { 0 },                                     // kCommandTag_Call = 0x0a
    { handle_reset, NULL },                    // kCommandTag_Reset = 0x0b
    { handle_set_property, NULL },             // kCommandTag_SetProperty = 0x0c
#if BL_FEATURE_ERASEALL_UNSECURE
    { handle_flash_erase_all_unsecure, NULL }, // kCommandTag_FlashEraseAllUnsecure = 0x0d
#else  // BL_FEATURE_ERASEALL_UNSECURE
    { 0 }, // kCommandTag_FlashEraseAllUnsecure = 0x0d
#endif // BL_FEATURE_ERASEALL_UNSECURE
    { 0 },                                     // kCommandTag_ProgramOnce = 0x0e
    { 0 },                                     // kCommandTag_ReadOnce = 0x0f
    { 0 },                                     // kCommandTag_ReadResource = 0x10
    { 0 },                                     // kCommandTag_ConfigureQuadSpi = 0x11
    { 0 },                                     // kCommandTag_ReliableUpdate = 0x12
#endif // BL_FEATURE_MIN_PROFILE
};

//! @brief Command processor state data.
command_processor_data_t g_commandData;

// See bl_command.h for documentation on this interface.
command_interface_t g_commandInterface = { bootloader_command_init, bootloader_command_pump,
                                           (command_handler_entry_t *)&g_commandHandlerTable, &g_commandData };

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bl_command.h for documentation on this function.
status_t bootloader_command_init()
{
    command_processor_data_t *data = g_bootloaderContext.commandInterface->stateData;

    data->state = kCommandState_CommandPhase;
    return kStatus_Success;
}

// See bl_command.h for documentation on this function.
status_t bootloader_command_pump()
{
    status_t status = kStatus_Success;
    bool hasMoreData = false;

    if (g_bootloaderContext.activePeripheral->packetInterface)
    {
        switch (g_bootloaderContext.commandInterface->stateData->state)
        {
            default:
            case kCommandState_CommandPhase:
                status = g_bootloaderContext.activePeripheral->packetInterface->readPacket(
                    g_bootloaderContext.activePeripheral, &g_bootloaderContext.commandInterface->stateData->packet,
                    &g_bootloaderContext.commandInterface->stateData->packetLength, kPacketType_Command);
                if ((status != kStatus_Success) && (status != kStatus_AbortDataPhase) && (status != kStatus_Ping))
                {
                    debug_printf("Error: readPacket returned status 0x%x\r\n", status);
                    break;
                }
                if (g_bootloaderContext.commandInterface->stateData->packetLength == 0)
                {
                    // No command packet is available. Return success.
                    break;
                }
                status = handle_command(g_bootloaderContext.commandInterface->stateData->packet,
                                        g_bootloaderContext.commandInterface->stateData->packetLength);
                if (status != kStatus_Success)
                {
                    debug_printf("Error: handle_command returned status 0x%x\r\n", status);
                    break;
                }
                g_bootloaderContext.commandInterface->stateData->state = kCommandState_DataPhase;
                break;

            case kCommandState_DataPhase:
                status = handle_data(&hasMoreData);
                if (status != kStatus_Success)
                {
                    debug_printf("Error: handle_data returned status 0x%x\r\n", status);
                    g_bootloaderContext.commandInterface->stateData->state = kCommandState_CommandPhase;
                    break;
                }
                g_bootloaderContext.commandInterface->stateData->state =
                    hasMoreData ? kCommandState_DataPhase : kCommandState_CommandPhase;
                break;
        }
    }

    return status;
}

//! @brief Find command handler entry.
//!
//! @retval NULL if no entry found.
static const command_handler_entry_t *find_entry(uint8_t tag)
{
    if (tag < kFirstCommandTag || tag > kLastCommandTag)
    {
        return 0; // invalid command
    }
    const command_handler_entry_t *entry =
        &g_bootloaderContext.commandInterface->handlerTable[(tag - kFirstCommandTag)];

    return entry;
}

//! @brief Handle a command transaction.
static status_t handle_command(uint8_t *packet, uint32_t packetLength)
{
    command_packet_t *commandPacket = (command_packet_t *)packet;
    uint8_t commandTag = commandPacket->commandTag;
    status_t status = kStatus_Success;

    // Look up the handler entry and save it for the data phaase.
    g_bootloaderContext.commandInterface->stateData->handlerEntry = find_entry(commandTag);

    if (g_bootloaderContext.commandInterface->stateData->handlerEntry &&
        g_bootloaderContext.commandInterface->stateData->handlerEntry->handleCommand)
    {
#if !BOOTLOADER_HOST
        // Get flash security state.
        flash_security_state_t securityState;
        status = g_bootloaderContext.flashDriverInterface->flash_get_security_state(&g_bootloaderContext.flashState,
                                                                                    &securityState);

        if (status == kStatus_Success)
        {
            // If flash security is enabled, make sure the command is one that is allowed. If
            // it's not, then we return an error response.
            if ((securityState != kFLASH_SecurityStateNotSecure) &&
                !IS_CMD_AVAILABLE(kCommandsAllowedWhenSecure, commandTag))
            {
                // Security is enabled and the command is not one of the few that can be
                // run, so return a security violation error.
                debug_printf("Error: command 0x%x not available due to flash security\r\n", commandPacket->commandTag);
                status = kStatus_SecurityViolation;
            }
            else
            {
#endif // BOOTLOADER_HOST
                // Process the command normally.
                g_bootloaderContext.commandInterface->stateData->handlerEntry->handleCommand(packet, packetLength);
                return kStatus_Success;
#if !BOOTLOADER_HOST
            }
        }
#endif // BOOTLOADER_HOST
    }
    else
    {
        // We don't recognize this command, so return an error response.
        debug_printf("unknown command 0x%x\r\n", commandPacket->commandTag);
        status = kStatus_UnknownCommand;
    }

    // Should only get to this point if an error occurred before running the command handler.
    send_generic_response(status, commandTag);
    return status;
}

//! @brief Handle a data transaction.
static status_t handle_data(bool *hasMoreData)
{
    if (g_bootloaderContext.commandInterface->stateData->handlerEntry)
    {
        // Run data phase if present, otherwise just return success.
        *hasMoreData = 0;
        return g_bootloaderContext.commandInterface->stateData->handlerEntry->handleData ?
                   g_bootloaderContext.commandInterface->stateData->handlerEntry->handleData(hasMoreData) :
                   kStatus_Success;
    }

    debug_printf("Error: no handler entry for data phase\r\n");
    return kStatus_Success;
}

////////////////////////////////////////////////////////////////////////////////
// Command Handlers
////////////////////////////////////////////////////////////////////////////////

//! @brief Reset command handler.
void handle_reset(uint8_t *packet, uint32_t packetLength)
{
    command_packet_t *commandPacket = (command_packet_t *)packet;
    send_generic_response(kStatus_Success, commandPacket->commandTag);

#if !defined(BOOTLOADER_HOST)
    // Wait for the ack from the host to the generic response
    g_bootloaderContext.activePeripheral->packetInterface->finalize(g_bootloaderContext.activePeripheral);

    // Prepare for shutdown.
    shutdown_cleanup(kShutdownType_Reset);

    NVIC_SystemReset();
    // Does not get here.
    assert(0);
#endif // BOOTLOADER_HOST
}

#if BL_FEATURE_RELIABLE_UPDATE
//! @brief Reliable Update command handler.
void handle_reliable_update(uint8_t *packet, uint32_t packetLength)
{
    command_packet_t *commandPacket = (command_packet_t *)packet;
    status_t status = kStatus_Success;

#if !defined(BOOTLOADER_HOST)
    reliable_update_packet_t *command = (reliable_update_packet_t *)packet;
    uint32_t address = command->address;

    // Call reliable update implementation..
    bootloader_reliable_update_as_requested(kReliableUpdateOption_Swap, address);

    status = g_bootloaderContext.propertyInterface->store->reliableUpdateStatus;
    send_generic_response(status, commandPacket->commandTag);

    if (status == kStatus_ReliableUpdateSuccess)
    {
        // Wait for the ack from the host to the generic response
        g_bootloaderContext.activePeripheral->packetInterface->finalize(g_bootloaderContext.activePeripheral);

        // Prepare for shutdown.
        shutdown_cleanup(kShutdownType_Reset);

        NVIC_SystemReset();
        // Does not get here.
        assert(0);
    }
#else
    send_generic_response(status, commandPacket->commandTag);
#endif // BOOTLOADER_HOST
}
#endif // BL_FEATURE_RELIABLE_UPDATE

//! @brief Reset data phase variables.
static void reset_data_phase()
{
    memset(&g_bootloaderContext.commandInterface->stateData->dataPhase, 0,
           sizeof(g_bootloaderContext.commandInterface->stateData->dataPhase));
}

//! @brief Flash Erase All command handler.
void handle_flash_erase_all(uint8_t *packet, uint32_t packetLength)
{
    flash_erase_all_packet_t *commandPacket = (flash_erase_all_packet_t *)packet;
    status_t status = kStatus_Success;

// Call flash erase all implementation.
#ifdef BOOTLOADER_HOST
    host_flash_erase_all();
#else
                                               // For target without QSPI module, ignore the memory identifier
#if ((!BL_FEATURE_QSPI_MODULE) && (!BL_FEATURE_FAC_ERASE))
    status = flash_mem_erase_all();
#else
    switch (commandPacket->memoryId)
    {
#if BL_FEATURE_FAC_ERASE
        case kFlashMemInternal:
            status = flash_mem_erase_all(kFlashEraseAllOption_Blocks);
            break;
        case kFlashMemExecuteOnly:
            status = flash_mem_erase_all(kFlashEraseAllOption_ExecuteOnlySegments);
            break;
#else
        case kFlashMemInternal:
            status = flash_mem_erase_all();
            break;
#endif
#if BL_FEATURE_QSPI_MODULE
        case kFlashMemQuadSpi0:
            status = qspi_mem_erase_all();
            break;
#endif
        default:
            status = kStatus_InvalidArgument;
            break;
    }
#endif // #if (!BL_FEATURE_QSPI_MODULE)
#endif // #ifdef BOOTLOADER_HOST

    send_generic_response(status, commandPacket->commandPacket.commandTag);
}

//! @brief Flash Erase All Unsecure command handler.
void handle_flash_erase_all_unsecure(uint8_t *packet, uint32_t packetLength)
{
    command_packet_t *commandPacket = (command_packet_t *)packet;
    status_t status = kStatus_Success;

// Call flash erase all unsecure implementation.
#ifdef BOOTLOADER_HOST
    host_flash_erase_all_unsecure();
#else
    status = flash_mem_erase_all_unsecure();
#endif

    send_generic_response(status, commandPacket->commandTag);
}

//! @brief Flash Erase Region command handler.
void handle_flash_erase_region(uint8_t *packet, uint32_t packetLength)
{
    flash_erase_region_packet_t *command = (flash_erase_region_packet_t *)packet;
    status_t status = kStatus_Success;

// Call flash erase region implementation.
#ifdef BOOTLOADER_HOST
    host_flash_erase_region(command->startAddress, command->byteCount);
#else
    status = g_bootloaderContext.memoryInterface->erase(command->startAddress, command->byteCount);
#endif

    send_generic_response(status, command->commandPacket.commandTag);
}

//! @brief Receive SB File command handler.
void handle_receive_sb_file(uint8_t *packet, uint32_t packetLength)
{
    receive_sb_file_packet_t *command = (receive_sb_file_packet_t *)packet;

    // Start the data phase.
    reset_data_phase();
    g_bootloaderContext.commandInterface->stateData->dataPhase.count = command->byteCount;
    g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag = kCommandTag_ReceiveSbFile;
    send_generic_response(kStatus_Success, command->commandPacket.commandTag);

    // Initialize the SB file loader state machine
    sbloader_init();
}

//! @brief Get Property command handler.
void handle_get_property(uint8_t *packet, uint32_t packetLength)
{
    get_property_packet_t *command = (get_property_packet_t *)packet;

    uint32_t *value = NULL;
    uint32_t valueSize = 0;
    status_t status = g_bootloaderContext.propertyInterface->get(command->propertyTag, command->memoryId,
                                                                 (const void **)&value, &valueSize);

    // Make sure the property's size is no more than the size of the max number of return parameters.
    assert(valueSize <= (kMaxPropertyReturnValues * sizeof(uint32_t)));

    // Currently there are no property responses that contain a data phase.
    g_bootloaderContext.commandInterface->stateData->dataPhase.count = 0;
    send_get_property_response(status, value, (valueSize / sizeof(uint32_t)));
}

//! @brief Set Property command handler.
void handle_set_property(uint8_t *packet, uint32_t packetLength)
{
    set_property_packet_t *command = (set_property_packet_t *)packet;

    status_t status = g_bootloaderContext.propertyInterface->set_uint32(command->propertyTag, command->propertyValue);

    send_generic_response(status, command->commandPacket.commandTag);
}

#if BL_FEATURE_QSPI_MODULE
//! @brief Configure QuadSpi command handler.
void handle_configure_quadspi(uint8_t *packet, uint32_t packetLength)
{
    configure_quadspi_packet_t *command = (configure_quadspi_packet_t *)packet;
    status_t status = kStatus_Success;

    uint32_t startAddr = command->configBlockAddress;
    uint32_t endAddr = startAddr + sizeof(qspi_config_t) - 1;

    // Validate parameters.
    if ((command->flashMemId != kFlashMemQuadSpi0) || (!is_valid_application_location(startAddr)) ||
        (!is_valid_application_location(endAddr)))
    {
        status = kStatus_InvalidArgument;
    }

    // Call configure quadspi implementation.
    if (status == kStatus_Success)
    {
#ifdef BOOTLOADER_HOST
#else
        status = quadspi_init((void *)startAddr);
        if (status == kStatus_Success)
        {
            // Re-init memory interface to intialize qspi memory interface
            g_bootloaderContext.memoryInterface->init();
        }
        g_bootloaderContext.propertyInterface->store->qspiInitStatus = status;
#endif
    }

    send_generic_response(status, command->commandPacket.commandTag);
}
#endif // BL_FEATURE_QSPI_MODULE

//! @brief Write Memory command handler.
void handle_write_memory(uint8_t *packet, uint32_t packetLength)
{
    write_memory_packet_t *command = (write_memory_packet_t *)packet;

    // Start the data phase.
    reset_data_phase();
    g_bootloaderContext.commandInterface->stateData->dataPhase.count = command->byteCount;
    g_bootloaderContext.commandInterface->stateData->dataPhase.address = command->startAddress;
    g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag = kCommandTag_WriteMemory;
    send_generic_response(kStatus_Success, command->commandPacket.commandTag);
}

//! @brief Read Memory command handler.
void handle_read_memory(uint8_t *packet, uint32_t packetLength)
{
    read_memory_packet_t *command = (read_memory_packet_t *)packet;

    // Start the data phase.
    reset_data_phase();
    g_bootloaderContext.commandInterface->stateData->dataPhase.count = command->byteCount;
    g_bootloaderContext.commandInterface->stateData->dataPhase.address = command->startAddress;
    g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag = kCommandTag_ReadMemory;
    send_read_memory_response(kStatus_Success, command->byteCount);
}

//! @brief Complete the data phase, optionally send a response.
void finalize_data_phase(status_t status)
{
    g_bootloaderContext.commandInterface->stateData->dataPhase.address = 0;
    g_bootloaderContext.commandInterface->stateData->dataPhase.count = 0;

    // Force to write cached data to target memory
    if (g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag == kCommandTag_WriteMemory)
    {
        assert(g_bootloaderContext.memoryInterface->flush);
        status_t flushStatus = g_bootloaderContext.memoryInterface->flush();

        // Update status only if the last operation result is successfull in order to reflect
        // real result of the write operation.
        if (status == kStatus_Success)
        {
            status = flushStatus;
        }
    }

    // Send final response packet.
    send_generic_response(status, g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag);

#if !BL_FEATURE_MIN_PROFILE
    if ((status == kStatus_AbortDataPhase) &&
        g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag == kCommandTag_ReceiveSbFile)
    {
        // Aborting due to sb loader jump or reset command.
        // If jump or reset successful, this will not return.
        // In the current architecture there is no way to handle an error return from sbloader_finalize()
        // because we already sent the "abort" status above to indicate that a jump command was encountered.
        sbloader_finalize();
    }
#endif // !BL_FEATURE_MIN_PROFILE
}

//! @brief Handle data phase with data consumer (read from host).
status_t handle_data_consumer(bool *hasMoreData)
{
    if (g_bootloaderContext.commandInterface->stateData->dataPhase.count == 0)
    {
        // No data phase.
        *hasMoreData = false;
        finalize_data_phase(kStatus_Success);
        return kStatus_Success;
    }

    *hasMoreData = true;
    uint32_t remaining = g_bootloaderContext.commandInterface->stateData->dataPhase.count;
    uint32_t dataAddress = g_bootloaderContext.commandInterface->stateData->dataPhase.address;
    uint8_t *packet;
    uint32_t packetLength = 0;
    status_t status;

    // Read the data packet.
    status = g_bootloaderContext.activePeripheral->packetInterface->readPacket(
        g_bootloaderContext.activePeripheral, &packet, &packetLength, kPacketType_Data);
    if (status != kStatus_Success)
    {
        // Abort data phase due to error.
        debug_printf("consumer abort data phase due to status 0x%x\r\n", status);
        g_bootloaderContext.activePeripheral->packetInterface->abortDataPhase(g_bootloaderContext.activePeripheral);
        finalize_data_phase(status);
        *hasMoreData = false;
        return kStatus_Success;
    }
    if (packetLength == 0)
    {
        // Sender requested data phase abort.
        debug_printf("Data phase aborted by sender\r\n");
        finalize_data_phase(kStatus_AbortDataPhase);
        *hasMoreData = false;
        return kStatus_Success;
    }

    //
    // Write the data to the destination address.
    //

    packetLength = MIN(packetLength, remaining);

#if !BL_FEATURE_MIN_PROFILE
    if (g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag == kCommandTag_ReceiveSbFile)
    {
        // Consumer is sb loader state machine
        g_bootloaderContext.commandInterface->stateData->dataPhase.data = packet;
        g_bootloaderContext.commandInterface->stateData->dataPhase.dataBytesAvailable = packetLength;

        status = sbloader_pump(packet, packetLength);

        // kStatusRomLdrDataUnderrun means need more data
        // kStatusRomLdrSectionOverrun means we reached the end of the sb file processing
        // either of these are OK
        if ((status == kStatusRomLdrDataUnderrun) || (status == kStatusRomLdrSectionOverrun))
        {
            status = kStatus_Success;
        }
    }
    else
#endif // !BL_FEATURE_MIN_PROFILE
    {
        // Consumer is memory interface.
        status = g_bootloaderContext.memoryInterface->write(dataAddress, packetLength, packet);
        dataAddress += packetLength;
    }

    remaining -= packetLength;

#ifdef TEST_RECEIVER_ABORT
    status = kStatus_Fail;
#endif

    if (remaining == 0)
    {
        finalize_data_phase(status);
        *hasMoreData = false;
    }
    else if (status != kStatus_Success)
    {
        // Abort data phase due to error.
        debug_printf("Data phase error 0x%x, aborting\r\n", status);
        g_bootloaderContext.activePeripheral->packetInterface->abortDataPhase(g_bootloaderContext.activePeripheral);
        finalize_data_phase(status);
        *hasMoreData = false;
    }
    else
    {
        g_bootloaderContext.commandInterface->stateData->dataPhase.count = remaining;
        g_bootloaderContext.commandInterface->stateData->dataPhase.address = dataAddress;
    }

    return kStatus_Success;
}

//! @brief Handle data phase with data producer (send to host).
status_t handle_data_producer(bool *hasMoreData)
{
    if (g_bootloaderContext.commandInterface->stateData->dataPhase.count == 0)
    {
        // No data phase.
        *hasMoreData = false;
        finalize_data_phase(kStatus_Success);
        return kStatus_Success;
    }

    *hasMoreData = true;
    uint32_t remaining = g_bootloaderContext.commandInterface->stateData->dataPhase.count;
    uint32_t dataAddress = g_bootloaderContext.commandInterface->stateData->dataPhase.address;
    uint8_t *data = g_bootloaderContext.commandInterface->stateData->dataPhase.data;
    uint8_t commandTag = g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag;
    status_t status = kStatus_Success;

    // Initialize the data packet to send.
    uint32_t packetSize;
    uint8_t packet[kMinPacketBufferSize];

    // Copy the data into the data packet.
    packetSize = MIN(kMinPacketBufferSize, remaining);
    if (data)
    {
        // Copy data using compiler-generated memcpy.
        memcpy(packet, data, packetSize);
        data += packetSize;
        status = kStatus_Success;
    }
    else
    {
        if (commandTag == kCommandTag_ReadMemory)
        {
            // Copy data using memory interface.
            status = g_bootloaderContext.memoryInterface->read(dataAddress, packetSize, packet);
        }
        else if (commandTag == kCommandTag_FlashReadResource)
        {
// Read data from special-purpose flash memory
#if !defined(BOOTLOADER_HOST)
            flash_read_resource_option_t option =
                (flash_read_resource_option_t)g_bootloaderContext.commandInterface->stateData->dataPhase.option;
            lock_acquire();
            status = g_bootloaderContext.flashDriverInterface->flash_read_resource(
                &g_bootloaderContext.flashState, dataAddress, (uint32_t *)packet, packetSize, option);
            lock_release();
#endif // BOOTLOADER_HOST
        }
        dataAddress += packetSize;
    }
    if (status != kStatus_Success)
    {
        debug_printf("Error: %s returned status 0x%x, abort data phase\r\n",
                     (commandTag == kCommandTag_ReadMemory) ? "read memory" : "flash read resource", status);
        // Send zero length packet to tell host we are aborting data phase
        g_bootloaderContext.activePeripheral->packetInterface->writePacket(
            g_bootloaderContext.activePeripheral, (const uint8_t *)packet, 0, kPacketType_Data);
        finalize_data_phase(status);
        *hasMoreData = false;
        return kStatus_Success;
    }
    remaining -= packetSize;

#ifdef TEST_SENDER_ABORT
#ifndef WIN32
// Disble IAR "statement is unreachable" error
#pragma diag_suppress = Pe111
#endif // WIN32
    // Send zero length packet to abort data phase.
    g_bootloaderContext.activePeripheral->packetInterface->writePacket(g_bootloaderContext.activePeripheral,
                                                                       (const uint8_t *)packet, 0, kPacketType_Data);
    finalize_data_phase(kStatus_AbortDataPhase);
    *hasMoreData = false;
    return kStatus_Success;
#endif // TEST_SENDER_ABORT;

    status = g_bootloaderContext.activePeripheral->packetInterface->writePacket(
        g_bootloaderContext.activePeripheral, (const uint8_t *)packet, packetSize, kPacketType_Data);

    if (remaining == 0)
    {
        finalize_data_phase(status);
        *hasMoreData = false;
    }
    else if (status != kStatus_Success)
    {
        debug_printf("writePacket aborted due to status 0x%x\r\n", status);
        finalize_data_phase(status);
        *hasMoreData = false;
    }
    else
    {
        g_bootloaderContext.commandInterface->stateData->dataPhase.count = remaining;
        g_bootloaderContext.commandInterface->stateData->dataPhase.address = dataAddress;
    }

    return kStatus_Success;
}

//! @brief Fill Memory command handler.
void handle_fill_memory(uint8_t *packet, uint32_t packetLength)
{
    fill_memory_packet_t *command = (fill_memory_packet_t *)packet;

    status_t status =
        g_bootloaderContext.memoryInterface->fill(command->startAddress, command->byteCount, command->patternWord);

    send_generic_response(status, command->commandPacket.commandTag);
}

//! @brief Execute command handler.
void handle_execute(uint8_t *packet, uint32_t packetLength)
{
    execute_call_packet_t *command = (execute_call_packet_t *)packet;

#if !defined(BOOTLOADER_HOST)
    static uint32_t s_addr = 0;
    uint32_t call_address = command->callAddress;
    uint32_t argument_word = command->argumentWord;
    s_addr = command->stackpointer;
    status_t responseStatus = kStatus_Success;

    // Get RAM address ranges
    const memory_map_entry_t *map = &g_bootloaderContext.memoryMap[kIndexSRAM];

    // Validate stack pointer address. It must either be 0 or within the RAM range.
    if (!((s_addr == 0) || ((s_addr >= map->startAddress) && (s_addr <= map->endAddress + 1))))
    {
        // Invalid stack pointer value, respond with kStatus_InvalidArgument.
        responseStatus = kStatus_InvalidArgument;
    }

    // Validate call address.
    if (!is_valid_application_location(call_address))
    {
        // Invalid address, respond with kStatus_InvalidArgument.
        responseStatus = kStatus_InvalidArgument;
    }

#if BL_FEATURE_OTFAD_MODULE
    if (is_qspi_present())
    {
        quadspi_cache_clear();
        status_t status = otfad_init_as_needed();
        if (status != kStatus_Success)
        {
            responseStatus = kStatus_OtfadInvalidKeyBlob;
        }
        update_qspi_otfad_init_status(status);
    }
#endif

    // Send response immediately since call may not return
    send_generic_response(responseStatus, command->commandPacket.commandTag);

    if (responseStatus == kStatus_Success)
    {
        static call_function_t s_callFunction = 0;
        s_callFunction = (call_function_t)call_address;

        // Prepare for shutdown.
        shutdown_cleanup(kShutdownType_Shutdown);

        // Static variables are needed since we are changing the stack pointer out from under the compiler
        // we need to ensure the values we are using are not stored on the previous stack
        static uint32_t s_argument = 0;
        s_argument = argument_word;

        if (s_addr)
        {
            // Set main stack pointer and process stack pointer
            __set_MSP(s_addr);
            __set_PSP(s_addr);
        }

        s_callFunction(s_argument);
        // Dummy fcuntion call, should never go to this fcuntion call
        shutdown_cleanup(kShutdownType_Shutdown);
    }
#else
    // Just send a successful response.
    send_generic_response(kStatus_Success, command->commandPacket.commandTag);
#endif // BOOTLOADER_HOST
}

//! @brief Call command handler.
void handle_call(uint8_t *packet, uint32_t packetLength)
{
    execute_call_packet_t *command = (execute_call_packet_t *)packet;
    status_t responseStatus = kStatus_Success;

#if !defined(BOOTLOADER_HOST)
    // Validate call address.
    if (!is_valid_application_location(command->callAddress))
    {
        // Invalid address, respond with kStatus_InvalidArgument.
        responseStatus = kStatus_InvalidArgument;
    }
    else
    {
        call_function_t callFunction = (call_function_t)command->callAddress;
        shutdown_cleanup(kShutdownType_Cleanup);
        responseStatus = callFunction(command->argumentWord);
    }
#endif // BOOTLOADER_HOST

    send_generic_response(responseStatus, command->commandPacket.commandTag);
}

//! @brief Flash Security Disable command handler.
void handle_flash_security_disable(uint8_t *packet, uint32_t packetLength)
{
    flash_security_disable_packet_t *command = (flash_security_disable_packet_t *)packet;

    status_t status = kStatus_Success;
#if !defined(BOOTLOADER_HOST)
    // Flash interface wants little endian, so just send two uint32s.
    status = g_bootloaderContext.flashDriverInterface->flash_security_bypass(&g_bootloaderContext.flashState,
                                                                             (uint8_t *)&command->keyLow);
#endif // BOOTLOADER_HOST

    send_generic_response(status, command->commandPacket.commandTag);
}

//! @brief  Flash Program Once command handler
void handle_flash_program_once(uint8_t *packet, uint32_t length)
{
    flash_program_once_packet_t *command = (flash_program_once_packet_t *)packet;

    status_t status = kStatus_Success;

#if !defined(BOOTLOADER_HOST)
    lock_acquire();
    status = g_bootloaderContext.flashDriverInterface->flash_program_once(
        &g_bootloaderContext.flashState, command->index, &command->data[0], command->byteCount);
    lock_release();
#endif // BOOTLOADER_HOST

    send_generic_response(status, command->commandPacket.commandTag);
}

//! @brief  Flash Read Once command handler
void handle_flash_read_once(uint8_t *packet, uint32_t length)
{
    flash_read_once_packet_t *command = (flash_read_once_packet_t *)packet;

    uint32_t readOnceItemData[2] = { 0 };

    status_t status = kStatus_Success;

#if !defined(BOOTLOADER_HOST)
    lock_acquire();
    status = g_bootloaderContext.flashDriverInterface->flash_read_once(&g_bootloaderContext.flashState, command->index,
                                                                       &readOnceItemData[0], command->byteCount);
    lock_release();
#endif // BOOTLOADER_HOST

    send_flash_read_once_response(status, readOnceItemData, command->byteCount);
}

//! @brief  Flash Read Resource command handler
void handle_flash_read_resource(uint8_t *packet, uint32_t length)
{
    flash_read_resource_packet_t *command = (flash_read_resource_packet_t *)packet;

    // Start the data phase.
    reset_data_phase();
    g_bootloaderContext.commandInterface->stateData->dataPhase.count = command->byteCount;
    g_bootloaderContext.commandInterface->stateData->dataPhase.address = command->startAddress;
    g_bootloaderContext.commandInterface->stateData->dataPhase.commandTag = kCommandTag_FlashReadResource;
    g_bootloaderContext.commandInterface->stateData->dataPhase.option = (uint8_t)command->option;
    send_flash_read_resource_response(kStatus_Success, command->byteCount);
}

//! @brief Send a generic response packet.
void send_generic_response(uint32_t commandStatus, uint32_t commandTag)
{
    generic_response_packet_t responsePacket;
    responsePacket.commandPacket.commandTag = kCommandTag_GenericResponse;
    responsePacket.commandPacket.flags = 0;
    responsePacket.commandPacket.reserved = 0;
    responsePacket.commandPacket.parameterCount = 2;
    responsePacket.status = commandStatus;
    responsePacket.commandTag = commandTag;

    status_t status = g_bootloaderContext.activePeripheral->packetInterface->writePacket(
        g_bootloaderContext.activePeripheral, (const uint8_t *)&responsePacket, sizeof(responsePacket),
        kPacketType_Command);
    if (status != kStatus_Success)
    {
        debug_printf("Error: writePacket returned status 0x%x\r\n", status);
    }
}

//! @brief Send a get property response packet.
void send_get_property_response(uint32_t commandStatus, uint32_t *value, uint32_t numValues)
{
    get_property_response_packet_t responsePacket;
    responsePacket.commandPacket.commandTag = kCommandTag_GetPropertyResponse;
    responsePacket.commandPacket.flags = 0;
    responsePacket.commandPacket.reserved = 0;
    responsePacket.commandPacket.parameterCount = 1 + numValues; // status + value words
    responsePacket.status = commandStatus;

    for (uint32_t i = 0; i < numValues; ++i)
    {
        responsePacket.propertyValue[i] = value[i];
    }

    uint32_t packetSize =
        sizeof(responsePacket.commandPacket) + (responsePacket.commandPacket.parameterCount * sizeof(uint32_t));

    status_t status = g_bootloaderContext.activePeripheral->packetInterface->writePacket(
        g_bootloaderContext.activePeripheral, (const uint8_t *)&responsePacket, packetSize, kPacketType_Command);
    if (status != kStatus_Success)
    {
        debug_printf("Error: writePacket returned status 0x%x\r\n", status);
    }
}

//! @brief Send a read memory response packet.
void send_read_memory_response(uint32_t commandStatus, uint32_t length)
{
    read_memory_response_packet_t responsePacket;
    responsePacket.commandPacket.commandTag = kCommandTag_ReadMemoryResponse;
    responsePacket.commandPacket.flags = kCommandFlag_HasDataPhase;
    responsePacket.commandPacket.reserved = 0;
    responsePacket.commandPacket.parameterCount = 2;
    responsePacket.status = commandStatus;
    responsePacket.dataByteCount = length;

    status_t status = g_bootloaderContext.activePeripheral->packetInterface->writePacket(
        g_bootloaderContext.activePeripheral, (const uint8_t *)&responsePacket, sizeof(responsePacket),
        kPacketType_Command);
    if (status != kStatus_Success)
    {
        debug_printf("Error: writePacket returned status 0x%x\r\n", status);
    }
}

//! @brief Send a flash read once resposne packet.
void send_flash_read_once_response(uint32_t commandStatus, uint32_t *value, uint32_t byteCount)
{
    flash_read_once_response_packet_t responsePacket;
    responsePacket.commandPacket.commandTag = kCommandTag_FlashReadOnceResponse;
    responsePacket.commandPacket.flags = 0;
    responsePacket.commandPacket.reserved = 0;
    responsePacket.commandPacket.parameterCount = 2; // always includes two parameters: status and byte count
    responsePacket.status = commandStatus;

    if (commandStatus == kStatus_Success)
    {
        responsePacket.commandPacket.parameterCount += byteCount / sizeof(uint32_t); // add parameter: data
        responsePacket.byteCount = byteCount;
        memcpy(responsePacket.data, value, byteCount);
    }
    else
    {
        responsePacket.byteCount = 0;
    }

    uint32_t packetSize =
        sizeof(responsePacket.commandPacket) + (responsePacket.commandPacket.parameterCount * sizeof(uint32_t));

    status_t status = g_bootloaderContext.activePeripheral->packetInterface->writePacket(
        g_bootloaderContext.activePeripheral, (const uint8_t *)&responsePacket, packetSize, kPacketType_Command);
    if (status != kStatus_Success)
    {
        debug_printf("Error: writePacket returned status 0x%x\r\n", status);
    }
}

//! @brief Send a flash read resource memory response packet.
void send_flash_read_resource_response(uint32_t commandStatus, uint32_t length)
{
    flash_read_resource_response_packet_t responsePacket;
    responsePacket.commandPacket.commandTag = kCommandTag_FlashReadResourceResponse;
    responsePacket.commandPacket.flags = kCommandFlag_HasDataPhase;
    responsePacket.commandPacket.reserved = 0;
    responsePacket.commandPacket.parameterCount = 2;
    responsePacket.status = commandStatus;
    responsePacket.dataByteCount = length;

    status_t status = g_bootloaderContext.activePeripheral->packetInterface->writePacket(
        g_bootloaderContext.activePeripheral, (const uint8_t *)&responsePacket, sizeof(responsePacket),
        kPacketType_Command);
    if (status != kStatus_Success)
    {
        debug_printf("Error: writePacket returned status 0x%x\r\n", status);
    }
}

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
