/*
 * runtime_configuration file for Embedded ARM
 */


/* copy ROM to RAM locations.  Set to 0 for more aggressive dead stripping */
#ifndef SUPPORT_ROM_TO_RAM
#define SUPPORT_ROM_TO_RAM   1
#endif

#ifndef SUPPORT_SEMIHOST_ARGC_ARGV
#define SUPPORT_SEMIHOST_ARGC_ARGV 0
#endif


