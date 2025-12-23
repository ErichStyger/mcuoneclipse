#include "McuRelais.h"
#include "McuRelais_config.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuUtility.h"

static McuGPIO_Handle_t relaisSetPin = NULL;
static McuGPIO_Handle_t relaisResetPin = NULL;
static bool relaisIsOn = false;

/* Pulse set */
static void Relais_Pulse(McuGPIO_Handle_t hPin) {
  McuGPIO_SetHigh(hPin);
  McuWait_Waitms(McuRelais_CONFIG_PULSE_TIME_MS);
  McuGPIO_SetLow(hPin);
}

/* On = Set Relay */
uint8_t McuRelais_On(void) {
  if (relaisSetPin == NULL) {
    return ERR_FAILED;
  }
  Relais_Pulse(relaisSetPin);
  relaisIsOn = true;
  return ERR_OK;
}

/* Off = Reset Relay */
uint8_t McuRelais_Off(void) {
  if (relaisResetPin == NULL) {
    return ERR_FAILED;
  }
  Relais_Pulse(relaisResetPin);
  relaisIsOn = false;
  return ERR_OK;
}

bool McuRelais_IsOn(void) {
  return relaisIsOn;
}

void McuRelais_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false; /* we are going to use output pins */

  /* Set pin */
  config.hw.pin = McuRelais_CONFIG_PIN_SET;
  relaisSetPin = McuGPIO_InitGPIO(&config);
  if (relaisSetPin == NULL) {
    for(;;) {}
  }

  /* Reset pin */
  config.hw.pin = McuRelais_CONFIG_PIN_RESET;
  relaisResetPin = McuGPIO_InitGPIO(&config);
  if (relaisResetPin == NULL) {
    for(;;) {}
  }
  
  relaisIsOn = false;
}

void McuRelais_Deinit(void) {
  relaisSetPin = McuGPIO_DeinitGPIO(relaisSetPin);
  relaisResetPin = McuGPIO_DeinitGPIO(relaisResetPin);
}

#if McuRelais_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) { 
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"McuRelais", (unsigned char*)"Bistable relais status\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), relaisIsOn ? (unsigned char*)"ON\r\n" : (unsigned char*)"OFF\r\n");
  McuShell_SendStatusStr((unsigned char*)"  state", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"SET=");
  McuUtility_strcatNum8u(buf, sizeof(buf), McuRelais_CONFIG_PIN_SET);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", RESET=");
  McuUtility_strcatNum8u(buf, sizeof(buf), McuRelais_CONFIG_PIN_RESET);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  pins", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuRelais", (unsigned char*)"Group of relay commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  on", (unsigned char*)"Switch relay ON (SET pulse)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  off", (unsigned char*)"Switch relay OFF (RESET pulse)\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuRelais_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  if (   McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
      || McuUtility_strcmp((char*)cmd, "McuRelais help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS) == 0)
             || (McuUtility_strcmp((char*)cmd, "McuRelais status") == 0)
            )
  {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuRelais on") == 0) {
    *handled = true;
    return McuRelais_On();
  } else if (McuUtility_strcmp((char*)cmd, "McuRelais off") == 0) {
    *handled = true;
    return McuRelais_Off();
  }
  return ERR_OK;
}
#endif /* McuRelais_CONFIG_PARSE_COMMAND_ENABLED */
