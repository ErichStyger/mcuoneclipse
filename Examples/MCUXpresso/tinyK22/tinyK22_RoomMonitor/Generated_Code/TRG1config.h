/**
 * \file
 * \brief Application configuration file for Trigger module
 *
 * This header file is a configuration header file to configure the module TRG1.
 * You can configure the defines directly in this file or with the compiler -D option.
 */

#ifndef __TRG1_CONFIG_H
#define __TRG1_CONFIG_H

/* no configuration supported yet */
/*! Definition of triggers */
#define TRG1_KEY1_PRESS /* key pressed, used by the KEY bean. Format is '<triggerName>_<keyName>_PRESS' */ 0
#define TRG1_EXAMPLE  /* example trigger */ 1

#define TRG1_CONFIG_TICK_PERIOD_MS \
  10                                    /* Period in milliseconds as defined in component properties, at which TRG1._AddTick() is called */

#endif /* __TRG1_CONFIG_H */
