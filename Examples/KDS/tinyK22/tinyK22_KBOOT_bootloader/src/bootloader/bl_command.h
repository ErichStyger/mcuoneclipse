/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#ifndef _command_h
#define _command_h

//! @addtogroup command
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Command state machine states.
enum _command_state
{
    kCommandState_CommandPhase,
    kCommandState_DataPhase
};

//! @brief Format of command handler entry.
typedef struct CommandHandlerEntry
{
    void (*handleCommand)(uint8_t *packet, uint32_t packetLength);
    status_t (*handleData)(bool *hasMoreData);
} command_handler_entry_t;

//! @brief Command processor data format.
typedef struct CommandProcessorData
{
    int32_t state;         //!< Current state machine state
    uint8_t *packet;       //!< Pointer to packet in process
    uint32_t packetLength; //!< Length of packet in process
    struct DataPhase
    {
        uint8_t *data;               //!< Data for data phase
        uint32_t count;              //!< Remaining count to produce/consume
        uint32_t address;            //!< Address for data phase
        uint32_t dataBytesAvailable; //!< Number of bytes available at data pointer
        uint8_t commandTag;          //!< Tag of command running data phase
        uint8_t option;              //!< option for special command

#if defined(__cplusplus)
        DataPhase()
            : data(NULL)
            , count(0)
            , address(0)
            , dataBytesAvailable(0)
            , commandTag(0)
            , option(0)
        {
        }
#endif
    } dataPhase;
    const command_handler_entry_t *handlerEntry; //! Pointer to handler table entry for packet in process
#if defined(__cplusplus)
    CommandProcessorData()
        : state(kCommandState_CommandPhase)
        , packet(NULL)
        , packetLength(0)
        , dataPhase()
    {
    }
#endif
} command_processor_data_t;

//! @brief Interface to command processor operations.
typedef struct CommandInterface
{
    status_t (*init)(void);
    status_t (*pump)(void);
    const command_handler_entry_t *handlerTable;
    command_processor_data_t *stateData;
} command_interface_t;

////////////////////////////////////////////////////////////////////////////////
// Externals
////////////////////////////////////////////////////////////////////////////////

//! @brief Default command interface.
extern command_interface_t g_commandInterface;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @brief Initialize the command processor component.
status_t bootloader_command_init(void);

//! @brief Pump the command state machine.
//!
//! Executes one command or data phase transaction.
status_t bootloader_command_pump(void);

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif // _bl_command.h_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
