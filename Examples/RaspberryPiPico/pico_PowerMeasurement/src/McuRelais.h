#ifndef __McuRelais_H__
#define __McuRelais_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "McuRelais_config.h"

#if McuRelais_CONFIG_PARSE_COMMAND_ENABLED
#include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
uint8_t McuRelais_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif/* McuRelais */

/*!
 * \brief Module initialization, call it to initialize the driver
 */
void McuRelais_Init(void);
/*!
 * \brief Module de-initialization, call it to de-initialize the driver
 */
void McuRelais_Deinit(void);

/* On and Off */
uint8_t McuRelais_On(void);
uint8_t McuRelais_Off(void);


bool McuRelais_IsOn(void);

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif /* __McuRelais_H__ */
