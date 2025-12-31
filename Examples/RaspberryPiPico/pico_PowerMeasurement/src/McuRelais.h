#ifndef __McuRelais_H__
#define __McuRelais_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "McuRelais_config.h"

/**
 * \file McuRelais.h
 * \brief API for controlling a relais (relay) on the target board.
 *
 * This header provides functions to initialize and de-initialize the relais
 * driver as well as to switch the relais on and off. When the optional
 * shell command support is enabled via \c McuRelais_CONFIG_PARSE_COMMAND_ENABLED,
 * a shell command parser is provided to operate the relais from a command
 * shell.
 */

#if McuRelais_CONFIG_PARSE_COMMAND_ENABLED
#include "McuShell.h"

/**
 * \brief Handle shell commands for the relais module.
 *
 * Recognizes relais-related commands and executes them. Typical commands are
 * "relais on", "relais off", "relais status" (implementation-specific).
 *
 * \param cmd Pointer to a NUL-terminated command string to parse.
 * \param handled Pointer to a boolean that will be set to true if the command
 *        was recognized and handled by this function. If not recognized, the
 *        function must set \p handled to false so other parsers can try.
 * \param io Pointer to an I/O interface used for printing responses and
 *        requesting input. May be NULL if no output is required.
 * \return Error code: ERR_OK (0) on success, or an error code on failure.
 */
uint8_t McuRelais_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/**
 * \brief Switch the relais on.
 *
 * Turns the relais output to the logical ON state. The exact electrical
 * behaviour (active-high/active-low) is defined by the board-specific
 * configuration in the implementation.
 *
 * \return Error code: ERR_OK on success, or an error code on failure.
 */
uint8_t McuRelais_On(void);

/**
 * \brief Switch the relais off.
 *
 * Turns the relais output to the logical OFF state.
 *
 * \return Error code: ERR_OK on success, or an error code on failure.
 */
uint8_t McuRelais_Off(void);

/**
 * \brief Query the current relais state.
 *
 * \return \c true if the relais is currently ON, \c false otherwise.
 */
bool McuRelais_IsOn(void);

/**
 * \brief Initialize the relais driver.
 *
 * Call this function once before using any other \c McuRelais API. It will
 * configure the GPIO or hardware required to control the relais according to
 * the board-specific configuration.
 */
void McuRelais_Init(void);

/**
 * \brief De-initialize the relais driver.
 *
 * Restores any resources allocated by \c McuRelais_Init and puts the relais
 * into a safe default state.
 */
void McuRelais_Deinit(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __McuRelais_H__ */
