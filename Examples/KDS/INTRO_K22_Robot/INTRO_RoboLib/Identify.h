/**
 * \file
 * \brief Module to identify different devices based on their unique ID.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * With this module individual devices are identified based on their unique ID.
 */

#ifndef __IDENTIFY_H_
#define __IDENTIFY_H_

#include "Platform.h"

#if PL_CONFIG_HAS_IDENTIFY
  #if PL_CONFIG_HAS_SHELL
    #include "CLS1.h"
    /*!
     * \brief Parses a command
     * \param cmd Command string to be parsed
     * \param handled Sets this variable to TRUE if command was handled
     * \param io I/O stream to be used for input/output
     * \return Error code, ERR_OK if everything was fine
     */
    uint8_t ID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
  #endif /* PL_CONFIG_HAS_SHELL */

  typedef enum {
    ID_DEVICE_ROBO_V1_L1,  /* Lab 1 robot V1 */
    ID_DEVICE_ROBO_V1_L2,  /* Lab 2 robot V1 */
    ID_DEVICE_ROBO_V1_L3,  /* Lab 3 robot V1 */
    ID_DEVICE_ROBO_V1_L4,  /* Lab 4 robot V1 */
    ID_DEVICE_ROBO_V2_L5,  /* Lab 4 robot V2 */
    ID_DEVICE_ROBO_V1_L7,  /* Lab 7 robot V1, white wheels */
    ID_DEVICE_ROBO_V1_L8,  /* Lab 8 robot V1 */ /* instructor 'black' robot */
    ID_DEVICE_ROBO_V2_L12, /* Lab 12 robot V2 2016 with white wheels */
    ID_DEVICE_ROBO_V2_L13, /* Lab 13 robot V2 2016 with black wheels */
    ID_DEVICE_ROBO_V2_L14, /* Lab 14 robot V2 2016 with white wheels */
    ID_DEVICE_ROBO_V2_L20, /* Lab 20 robot V2 2016 with black wheels */
    ID_DEVICE_ROBO_V2_L21, /* Lab 21 robot V2 2016 with white wheels */
    ID_DEVICE_ROBO_V2_L22, /* Lab 22 robot V2 2016 with white wheels */
    ID_DEVICE_ROBO_V2_L23, /* Lab 23 robot V2 2016 with white wheels, second one built for MINT */
    ID_DEVICE_UNKNOWN, /* unknown robot, unknown ID */
    ID_DEVICE_NONE /* initialization value, used internally */
  } ID_Devices;

  ID_Devices ID_WhichDevice(void);
  void ID_Deinit(void);
  void ID_Init(void);
#endif /* PL_CONFIG_HAS_IDENTIFY */

#endif /* __IDENTIFY_H_ */
