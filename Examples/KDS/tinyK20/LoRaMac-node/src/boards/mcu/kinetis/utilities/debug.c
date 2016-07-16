/**
 * \file debug.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 13.11.2015
 * \brief Debug output helper
 *
 */

#if !defined(USE_KINETIS_SDK)
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "debug.h"
#include "print_scan.h"

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
static int debug_putc( int ch, void* stream );

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static Uart_t *dbg_stdio;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
uint8_t DbgConsole_Init( Uart_t *stdio )
{
    dbg_stdio = stdio;

    return ERR_OK;
}

#pragma weak _write
int _write( int handle, char *buffer, int size )
{
    if ( buffer == 0 ) {
        /* return -1 if error */
        return -1;
    }

    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ( (handle != 1) && (handle != 2) ) {
        return -1;
    }

    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }

    /* Send data.*/
    UartPutBuffer(dbg_stdio, (uint8_t *) buffer, size);
    return size;
}

#pragma weak _read
int _read( int handle, char *buffer, int size )
{
    /* This function only reads from "standard in", for all other file*/
    /* handles it returns failure.*/
    if ( handle != 0 ) {
        return -1;
    }

    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }

    /* Receive data.*/
    UartGetBuffer(dbg_stdio, (uint8_t *) buffer, size, (void*) NULL);

    return size;
}

/*************Code for debug_printf/scanf/assert*******************************/
int debug_printf( const char *fmt_s, ... )
{
    va_list ap;
    int result;
    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }
    va_start(ap, fmt_s);
    result = _doprint(NULL, debug_putc, -1, (char *) fmt_s, ap);
    va_end(ap);

    return result;
}

int debug_putchar( int ch )
{
    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }
    debug_putc(ch, NULL);

    return 1;
}

int debug_scanf( const char *fmt_ptr, ... )
{
    char temp_buf[IO_MAXLINE];
    va_list ap;
    uint32_t i;
    char result;

    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }
    va_start(ap, fmt_ptr);
    temp_buf[0] = '\0';

    for ( i = 0; i < IO_MAXLINE; i++ ) {
        temp_buf[i] = result = debug_getchar();

        if ( (result == '\r') || (result == '\n') ) {
            /* End of Line */
            if ( i == 0 ) {
                i = (uint32_t) - 1;
            } else {
                break;
            }
        }

        temp_buf[i + 1] = '\0';
    }

    result = scan_prv(temp_buf, (char *) fmt_ptr, ap);
    va_end(ap);

    return result;
}

int debug_getchar( void )
{
    unsigned char c;

    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }
    UartGetBuffer(dbg_stdio, &c, 1, (void*) NULL);

    return c;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
static int debug_putc( int ch, void* stream )
{
    const unsigned char c = (unsigned char) ch;
    /* Do nothing if the debug uart is not initialized.*/
    if ( dbg_stdio == NULL ) {
        return -1;
    }
#if defined(USE_CUSTOM_UART_HAL)
    UartPutBuffer(dbg_stdio, (uint8_t *) &c, 1);
#else
    UartPutChar(dbg_stdio, c);
#endif

    return 0;

}

void debug_assert( const char* file, int line )
{
    asm volatile("bkpt");
} /* end debug_assert */

#endif /* USE_KINETIS_SDK */
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
