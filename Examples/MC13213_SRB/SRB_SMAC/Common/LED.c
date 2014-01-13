/**
 * \file
 * \brief LED driver module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic LED driver, plus a test routine to verify functionality.
 * The module supports right now up to 5 LEDs, and the number of LEDs can be specified using
 * the ::PL_NOF_LED macro in the range of 0 to 5
 * The module has been verified to run both on the SRB and the TOWER platform.
 */

#include "Platform.h" /* interface to the platform */

#if PL_HAS_LED
#include "LED.h"
#include "UTIL1.h"

#define TEST_LED 0 
  /*!< if we perform tests */

#if TEST_LED
/*! 
 * \brief LED test routine.
 * This routine tests if 
 * - we can turn the LEDs properly on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 */
static void LED_Test(void) {
  LED1_On();
  LED2_On();
  LED3_On();
  LED4_On();
  LED5_On();
  
  LED1_Off();
  LED2_Off();
  LED3_Off();
  LED4_Off();
  LED5_Off();

  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  LED4_Neg();
  LED5_Neg();

  LED1_On();
  if (!LED1_Get()) {
    for(;;){}; /* error */ /*! \todo need a dedicated error routine */
  }
  LED1_Off();
  if (LED1_Get()) {
    for(;;){}; /* error */
  }
  LED1_Put(1);
  if (!LED1_Get()) {
    for(;;){}; /* error */
  }
}
#endif

#if PL_HAS_SHELL
/*! 
 * \brief Prints the status text to the console
 * \param io I/O channel to be used
 */
static void PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr("LED Status", "", io->stdOut);
#if PL_NOF_LED >= 1
  CLS1_SendStr("1:", io->stdOut);
  CLS1_SendStr(LED1_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_LED >= 2
  CLS1_SendStr("2:", io->stdOut);
  CLS1_SendStr(LED2_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_LED >= 3
  CLS1_SendStr("3:", io->stdOut);
  CLS1_SendStr(LED3_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_LED >= 4
  CLS1_SendStr("4:", io->stdOut);
  CLS1_SendStr(LED4_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_LED >= 5
  CLS1_SendStr("5:", io->stdOut);
  CLS1_SendStr(LED5_Get()!=0?"on ":"off ", io->stdOut);
#endif
  CLS1_SendStr("\r\n", io->stdOut);
}
#endif /* PL_HAS_SHELL */

#if PL_HAS_SHELL
typedef enum LED_Cmd {
  LED_ON_CMD, /*!< command for turning on an LED */
  LED_OFF_CMD, /*!< command for turning off an LED */
  LED_NEG_CMD /*!< command for negating/toggling an LED */
} LED_Cmd;

/*!
 * \brief Turns on an LED
 * \param[in] ledNo LED number, starting with 1
 * \param[in,out] handled Callee sets it to TRUE if command has been processed successfully
 */
static void LED_OnCmd(uint8_t ledNo, bool *handled) {
#if PL_NOF_LED >= 1
  if (ledNo==1) {
    LED1_On(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 2
  } else if (ledNo==2) {
    LED2_On(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 3
  } else if (ledNo==3) {
    LED3_On(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 4
  } else if (ledNo==4) {
    LED4_On(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 5
  } else if (ledNo==5) {
    LED5_On(); *handled=TRUE;
#endif
  }
}

/*!
 * \brief Turns off an LED
 * \param[in]     ledNo   LED number, starting with 1
 * \param[in,out] handled Callee sets it to TRUE if command has been processed successfully
 */
static void LED_OffCmd(uint8_t ledNo, bool *handled) {
#if PL_NOF_LED >= 1
  if (ledNo==1) {
    LED1_Off(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 2
  } else if (ledNo==2) {
    LED2_Off(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 3
  } else if (ledNo==3) {
    LED3_Off(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 4
  } else if (ledNo==4) {
    LED4_Off(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 5
  } else if (ledNo==5) {
    LED5_Off(); *handled=TRUE;
#endif
  }
}

/*!
 * \brief Negates an LED
 * \param[in]     ledNo   LED number, starting with 1
 * \param[in,out] handled Callee sets it to TRUE if command has been processed successfully
 */
static void LED_NegCmd(uint8_t ledNo, bool *handled) {
#if PL_NOF_LED >= 1
  if (ledNo==1) {
    LED1_Neg(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 2
  } else if (ledNo==2) {
    LED2_Neg(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 3
  } else if (ledNo==3) {
    LED3_Neg(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 4
  } else if (ledNo==4) {
    LED4_Neg(); *handled=TRUE;
#endif  
#if PL_NOF_LED >= 5
  } else if (ledNo==5) {
    LED5_Neg(); *handled=TRUE;
#endif
  }
}

/*!
 * \brief Processes a command on an LED
 * \param[in]     ledNo   LED number, starting with 1
 * \param[in]     cmd     Command ID to be processed
 * \param[in,out] handled Callee sets it to TRUE if command has been processed successfully
 */
static void LED_Command(uint8_t ledNo, LED_Cmd cmd, bool *handled) {
  switch(cmd) {
    case LED_ON_CMD:
      LED_OnCmd(ledNo, handled);
      break;
    case LED_OFF_CMD:
      LED_OffCmd(ledNo, handled);
      break;
    case LED_NEG_CMD:
      LED_NegCmd(ledNo, handled);
      break;
  }
}
#endif /* PL_HAS_SHELL */

#if PL_HAS_SHELL
/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const CLS1_StdIOType *io) {
  /* list your local help here */
  CLS1_SendHelpStr("led", "Group of led commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr("  on|off|neg <nr>", "Turns a led on, off or negates it\r\n", io->stdOut);
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t LED_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t ledNr;
  const char *p;
  
  if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "led status")==0) {
    PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "led help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp(cmd, "led on ", sizeof("led on ")-1)==0) {
    p = cmd+sizeof("led on ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &ledNr)==ERR_OK) {
      LED_Command(ledNr, LED_ON_CMD, handled);
    }
  } else if (UTIL1_strncmp(cmd, "led off ", sizeof("led off ")-1)==0) {
    p = cmd+sizeof("led off ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &ledNr)==ERR_OK) {
      LED_Command(ledNr, LED_OFF_CMD, handled);
    }
  } else if (UTIL1_strncmp(cmd, "led neg ", sizeof("led neg ")-1)==0) {
    p = cmd+sizeof("led neg ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &ledNr)==ERR_OK) {
      LED_Command(ledNr, LED_NEG_CMD, handled);
    }
  }
  return ERR_OK;
}
#endif /* PL_HAS_SHELL */

/*!
 * \brief LED driver initialization
 */
void LED_Init(void) {
  /*! \todo call your LED test routines here */
#if TEST_LED
  LED_Test();
#endif
#if PL_NOF_LED >= 1
  LED1_Off();
#endif
#if PL_NOF_LED >= 2
  LED2_Off();
#endif
#if PL_NOF_LED >= 3
  LED3_Off();
#endif
#if PL_NOF_LED >= 4
  LED4_Off();
#endif
#if PL_NOF_LED >= 5
  LED5_Off();
#endif
}
#endif /* PL_HAS_LED */
