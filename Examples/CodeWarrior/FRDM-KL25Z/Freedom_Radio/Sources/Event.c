/**
 * \file
 * \brief Event driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first
 * \todo Make this module reentrant and thread safe!
 */
#include "Platform.h"
#if PL_HAS_EVENTS
#include "Event.h"
#if PL_HAS_SHELL
  #include "Shell.h"
  #include "FSSH1.h"
#endif

typedef uint8_t EVNT_MemUnit; /* memory unit used to store events flags */
#define EVNT_MEM_UNIT_NOF_BITS  (sizeof(EVNT_MemUnit)*8) /* number of bits in memory unit */

static EVNT_MemUnit EVNT_Events[((EVNT_NOF_EVENTS-1)/EVNT_MEM_UNIT_NOF_BITS)+1]; /*!< Bit set of events */

#define SET_EVENT(event) \
  EVNT_Events[(event)/EVNT_MEM_UNIT_NOF_BITS] |= (1<<(EVNT_MEM_UNIT_NOF_BITS-1))>>((uint8_t)((event)%EVNT_MEM_UNIT_NOF_BITS)) /*!< Set the event */
#define CLR_EVENT(event) \
  EVNT_Events[(event)/EVNT_MEM_UNIT_NOF_BITS] &= ~((1<<(EVNT_MEM_UNIT_NOF_BITS-1))>>((uint8_t)((event)%EVNT_MEM_UNIT_NOF_BITS))) /*!< Clear the event */
#define GET_EVENT(event) \
  (bool)(EVNT_Events[(event)/EVNT_MEM_UNIT_NOF_BITS]&((1<<(EVNT_MEM_UNIT_NOF_BITS-1))>>((uint8_t)((event)%EVNT_MEM_UNIT_NOF_BITS)))) /*!< Return TRUE if event is set */


void EVNT_SetEvent(EVNT_Handle event) {
  EnterCritical();
  SET_EVENT(event);
  ExitCritical();
}

void EVNT_ClearEvent(EVNT_Handle event) {
  EnterCritical();
  CLR_EVENT(event);
  ExitCritical();
}

bool EVNT_EventIsSet(EVNT_Handle event) {
  bool isSet;

  EnterCritical();
  isSet = GET_EVENT(event);
  ExitCritical();
  return isSet;
}

void EVNT_HandleEvent(void (*callback)(EVNT_Handle)) {
  /* Handle the one with the highest priority. Zero is the event with the highest priority. */
   EVNT_Handle event;

   EnterCritical();
   for (event=(EVNT_Handle)0; event<EVNT_NOF_EVENTS; event++) { /* does a test on every event */
     if (GET_EVENT(event)) { /* event present? */
       CLR_EVENT(event); /* clear event */
       break; /* get out of loop */
     }
   }
   ExitCritical();
   if (event != EVNT_NOF_EVENTS) {
     callback(event);
   }
}

#if PL_HAS_SHELL
/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PrintHelp(const FSSH1_StdIOType *io) {
  /* list your local help here */
  FSSH1_SendHelpStr("event", "Group of event commands\r\n", io->stdOut);
  FSSH1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  FSSH1_SendHelpStr("  set <nr>", "Set an event\r\n", io->stdOut);
}

static void PrintStatus(const FSSH1_StdIOType *io) {
  EVNT_Handle i;

  FSSH1_SendStatusStr("Event Status", "", io->stdOut);
  for(i=(EVNT_Handle)0;i<EVNT_NOF_EVENTS;i++) {
    if (i>0 && i%8==0) {
      FSSH1_SendStr(" ", io->stdOut);
    }
    FSSH1_SendStr(EVNT_EventIsSet((EVNT_Handle)i)?"1":"0", io->stdOut);
  }
  FSSH1_SendStr("\r\n", io->stdOut);
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t EVNT_ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io) {
  uint8_t nr;
  const char *p;

  if (UTIL1_strcmp(cmd, FSSH1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "event status")==0) {
    PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, FSSH1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "event help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strncmp(cmd, "event set ", sizeof("event set ")-1)==0) {
    p = cmd+sizeof("event set ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &nr)==ERR_OK) {
      EVNT_SetEvent((EVNT_Handle)nr);
      *handled = TRUE;
    }
  }
  return ERR_OK;
}
#endif /* PL_HAS_SHELL */


/*! \brief Event module initialization */
void EVNT_Init(void) {
  uint8_t i;

  i = 0;
  do {
    EVNT_Events[i] = 0; /* initialize data structure */
    i++;
  } while(i<sizeof(EVNT_Events)/sizeof(EVNT_Events[0]));
  EVNT_SetEvent(EVNT_INIT);
}
#endif /* PL_HAS_EVENTS */
