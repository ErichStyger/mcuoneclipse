/**
 * \file
 * \brief Key/switch driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 04.03.2011
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "Platform.h"

#if PL_HAS_KEYBOARD
/*! \todo Implement following interface. Does not have to be with functions. Consider macros for efficiency. */
#if 0
uint8_t KEY1_Get(void);
uint8_t KEY2_Get(void);
uint8_t KEY3_Get(void);
uint8_t KEY4_Get(void);
#endif

#if PL_IS_SRB_BOARD
  #include "KB1.h"

  #define KEY1_Get()  (!(KB1_GetVal()&(1<<0))) 
    /*!< Macro which returns TRUE if key 1 is pressed */
  #define KEY2_Get()  (!(KB1_GetVal()&(1<<1))) 
    /*!< Macro which returns TRUE if key 2 is pressed */
  #define KEY3_Get()  (!(KB1_GetVal()&(1<<2))) 
    /*!< Macro which returns TRUE if key 3 is pressed */
  #define KEY4_Get()  (!(KB1_GetVal()&(1<<3))) 
    /*!< Macro which returns TRUE if key 4 is pressed */
#elif PL_IS_TOWER_BOARD
  #include "SW1.h"
  #include "SW3.h"

  #define KEY1_Get()  (!(SW1_GetVal())) 
    /*!< Macro which returns TRUE if key 1 is pressed */
  #define KEY2_Get()  (!(SW3_GetVal())) 
    /*!< Macro which returns TRUE if key 2 is pressed */
  #define KEY3_Get()  0 
    /*!< No key */
  #define KEY4_Get()  0 
    /*!< No key */
#endif

#if PL_IS_SRB_BOARD
/*! 
 * \brief Function called from a keyboard interrupt (if supported).
 */
void KEY_OnInterrupt(void);
#endif

/*!
 * \brief Scans the keys and generates the events.
 */
void KEY_Scan(void);

#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t KEY_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*! \brief Key driver initialization */
void KEY_Init(void);

#endif /* PL_HAS_KEYBOARD */

#endif /* KEYS_H_ */
