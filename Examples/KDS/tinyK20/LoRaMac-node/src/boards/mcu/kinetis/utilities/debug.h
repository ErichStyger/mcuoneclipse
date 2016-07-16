/**
 * \file debug.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 13.11.2015
 * \brief Debug output helper
 *
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
/**
 * Define a global default log level (may be none), i.e. either
 * LOG_DEFAULT_LEVEL_TRACE, LOG_DEFAULT_LEVEL_DEBUG or LOG_DEFAULT_LEVEL_ERROR.
 *
 * Note:
 * In your application file, you may select a specific log level by defining
 * either LOG_LEVEL_TRACE, LOG_LEVEL_DEBUG or LOG_LEVEL_ERROR before including
 * this file.
 */
//#define LOG_DEFAULT_LEVEL_TRACE       // Everything gets printed
//#define LOG_DEFAULT_LEVEL_DEBUG       // Errors and debug data get printed
#define LOG_DEFAULT_LEVEL_ERROR       // Only errors get printed
//#define LOG_DEFAULT_LEVEL_NONE        // Nothing gets printed

/**
 * Undefine log enable flags
 */
#undef LOG_TRACE_IS_ENABLED
#undef LOG_DEBUG_IS_ENABLED
#undef LOG_ERROR_IS_ENABLED

/**
 * Color definitions
 */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define IO_MAXLINE  20

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/
/**
 * Determine applicable log level
 */
#if !defined(LOG_LEVEL_TRACE) && !defined(LOG_LEVEL_DEBUG) && !defined(LOG_LEVEL_ERROR)
// No log level is defined -> set default log level
#if defined(LOG_DEFAULT_LEVEL_TRACE)
#define LOG_TRACE_IS_ENABLED
#define LOG_DEBUG_IS_ENABLED
#define LOG_ERROR_IS_ENABLED
#elif defined(LOG_DEFAULT_LEVEL_DEBUG)
#define LOG_DEBUG_IS_ENABLED
#define LOG_ERROR_IS_ENABLED
#elif defined(LOG_DEFAULT_LEVEL_ERROR)
#define LOG_ERROR_IS_ENABLED
#endif
#else
// At least one log level is defined
#if defined(LOG_LEVEL_TRACE)
#define LOG_TRACE_IS_ENABLED
#define LOG_DEBUG_IS_ENABLED
#define LOG_ERROR_IS_ENABLED
#elif defined(LOG_LEVEL_DEBUG)
#define LOG_DEBUG_IS_ENABLED
#define LOG_ERROR_IS_ENABLED
#elif defined(LOG_LEVEL_ERROR)
#define LOG_ERROR_IS_ENABLED
#endif
#endif

/**
 * Define log functions.
 */
#if defined(LOG_TRACE_IS_ENABLED) && defined(DEBUG)
#define LOG_TRACE(fmt, ...)                 debug_printf("TRACE: " fmt "\r\n", ##__VA_ARGS__)
#define LOG_TRACE_BARE(fmt, ...)            debug_printf(fmt, ##__VA_ARGS__)
#define LOG_TRACE_IF(cond, fmt, ...)        if (cond) { debug_printf("TRACE: " fmt "\r\n", ##__VA_ARGS__); }
#define LOG_TRACE_BARE_IF(cond, fmt, ...)   if (cond) { debug_printf(fmt, ##__VA_ARGS__); }
#else
#define LOG_TRACE(fmt, ...)
#define LOG_TRACE_COLORED(fmt, ...)
#define LOG_TRACE_BARE(fmt, ...)
#define LOG_TRACE_IF(cond, fmt, ...)
#define LOG_TRACE_BARE_IF(cond, fmt, ...)
#endif

#if defined(LOG_DEBUG_IS_ENABLED) && defined(DEBUG)
#define LOG_DEBUG(fmt, ...)                 debug_printf("DEBUG: " fmt "\r\n", ##__VA_ARGS__)
#define LOG_DEBUG_BARE(fmt, ...)            debug_printf(fmt, ##__VA_ARGS__)
#define LOG_DEBUG_IF(cond, fmt, ...)        if (cond) { debug_printf("DEBUG: " fmt "\r\n", ##__VA_ARGS__); }
#define LOG_DEBUG_BARE_IF(cond, fmt, ...)   if (cond) { debug_printf(fmt, ##__VA_ARGS__); }
#else
#define LOG_DEBUG(fmt, ...)
#define LOG_DEBUG_BARE(fmt, ...)
#define LOG_DEBUG_IF(cond, fmt, ...)
#define LOG_DEBUG_BARE_IF(cond, fmt, ...)
#endif

#if defined(LOG_ERROR_IS_ENABLED) && defined(DEBUG)
#define LOG_ERROR(fmt, ...)                 debug_printf(KRED "ERROR: " fmt "\x1b[0m\r\n", ##__VA_ARGS__)
#define LOG_ERROR_BARE(fmt, ...)            debug_printf(fmt, ##__VA_ARGS__)
#define LOG_ERROR_IF(cond, fmt, ...)        if (cond) { debug_printf(KRED "ERROR: " fmt KNRM, ##__VA_ARGS__); }
#define LOG_ERROR_BARE_IF(cond, fmt, ...)   if (cond) { debug_printf(fmt, ##__VA_ARGS__); }
#else
#define LOG_ERROR(fmt, ...)
#define LOG_ERROR_BARE(fmt, ...)
#define LOG_ERROR_IF(cond, fmt, ...)
#define LOG_ERROR_BARE_IF(cond, fmt, ...)
#endif

/*******************************************************************************
 * MODULE FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
#if !defined(USE_KINETIS_SDK)
/*!
 * @brief Init the UART/LPUART used for debug messages.
 *
 * Call this function to enable debug log messages to be output via the specified UART/LPUART
 * base address and at the specified baud rate. Just initializes the UART/LPUART to the given baud
 * rate and 8N1. After this function has returned, stdout and stdin will be connected to the
 * selected UART/LPUART. The debug_printf() function also uses this UART/LPUART.
 *
 * @param uartInstance Which UART/LPUART instance is used to send debug messages.
 * @param baudRate The desired baud rate in bits per second.
 * @param device Low level device type for the debug console.
 * @return Whether initialization was successful or not.
 */
uint8_t DbgConsole_Init( Uart_t *stdio );

/*!
 * @brief   Prints formatted output to the standard output stream.
 *
 * Call this function to print formatted output to the standard output stream.
 *
 * @param   fmt_s   Format control string.
 * @return  Returns the number of characters printed, or a negative value if an error occurs.
 */
int debug_printf( const char *fmt_s, ... );

/*!
 * @brief   Writes a character to stdout.
 *
 * Call this function to write a character to stdout.
 *
 * @param   ch  Character to be written.
 * @return  Returns the character written.
 */
int debug_putchar( int ch );

/*!
 * @brief   Reads formatted data from the standard input stream.
 *
 * Call this function to read formatted data from the standard input stream.
 *
 * @param   fmt_ptr Format control string.
 * @return  Returns the number of fields successfully converted and assigned.
 */
int debug_scanf( const char *fmt_ptr, ... );

/*!
 * @brief   Reads a character from standard input.
 *
 * Call this function to read a character from standard input.
 *
 * @return  Returns the character read.
 */
int debug_getchar( void );

#endif /* USE_KINETIS_SDK */
#endif /* __DEBUG_H__ */
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
