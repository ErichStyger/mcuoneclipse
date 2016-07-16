/**
 * \file Shell.c
 * \author tawinige
 * \date 28.12.2015
 * \version 1.0
 *
 * \brief
 *
 *******************************************************************************
 *  Change log:
 *      [1.0]   28.12.2015      	tawinige
 *          - created
 *******************************************************************************
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "Shell.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/*! FIFO buffers size */
#define SHELL_FIFO_RX_SIZE                  128

/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static Shell_ConstStdIO_t Shell_stdio = { (StdIO_InFunction_t) Shell_ReadChar, /* stdin */
(StdIO_OutErrFunction_t) Shell_SendChar, /* stdout */
(StdIO_OutErrFunction_t) Shell_SendChar, /* stderr */
Shell_KeyPressed /* if input is not empty */
};

/**/
static Shell_ConstStdIO_t *Shell_currStdIO = &Shell_stdio;

/*! FIFO buffers */
uint8_t Shell_RxBuffer[SHELL_FIFO_RX_SIZE];

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
byte IterateTable( const unsigned char *cmd, bool *handled, Shell_ConstStdIO_t *io,
        Shell_ConstParseCommandCallback_t *parserTable );

void PrintPrompt( Shell_ConstStdIO_t *io );

uint8_t PrintStatus( Shell_ConstStdIO_t *io );

void PrintCommandFailed( const unsigned char *cmd, Shell_ConstStdIO_t *io );

bool ReadLine( byte *buf, size_t bufSize, Shell_ConstStdIO_t *io );

void SendSeparatedStrings( const byte *strA, const byte *strB, byte tabChar, byte tabPos,
        StdIO_OutErrFunction_t io );

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void Shell_Init( void )
{
    FifoInit(&Uart1.FifoRx, Shell_RxBuffer, SHELL_FIFO_RX_SIZE);
    UartInit(&Uart1, UART_1, UART1_TX, UART1_RX);
    UartConfig(&Uart1, RX_TX, 115200, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY,
            NO_FLOW_CTRL);
}

void Shell_SendHelpStr( const unsigned char *strCmd, const unsigned char *strHelp,
        StdIO_OutErrFunction_t io )
{
#define HELP_SEMICOLON_POS  26 /* position of the ';' after the command string */
    SendSeparatedStrings(strCmd, strHelp, ';', HELP_SEMICOLON_POS, io);
}

void Shell_SendStatusStr( const unsigned char *strItem, const unsigned char *strStatus,
        StdIO_OutErrFunction_t io )
{
#define STATUS_COLON_POS  13 /* position of the ':' after the item string */
    SendSeparatedStrings(strItem, strStatus, ':', STATUS_COLON_POS, io);
}

void Shell_SendStr( const unsigned char *str, StdIO_OutErrFunction_t io )
{
    while (*str != '\0') {
        io(*str++);
    }
}

uint8_t Shell_ParseCommand( const unsigned char *cmd, bool *handled,
        Shell_ConstStdIO_t *io )
{
    if ( strcmp((char*) cmd, SHELL_CMD_HELP) == 0
            || strcmp((char*) cmd, "Shell help") == 0 ) {
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        Shell_SendStr((unsigned char*) "LoRaMesh demo application", io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        Shell_SendHelpStr((unsigned char*) "Shell",
                (const unsigned char*) "Group of shell commands\r\n", io->stdOut);
        Shell_SendHelpStr((unsigned char*) "  help|status",
                (const unsigned char*) "Print help or status information\r\n",
                io->stdOut);
        *handled = true;
        return ERR_OK;
    } else if ( (strcmp((char*) cmd, SHELL_CMD_STATUS) == 0)
            || (strcmp((char*) cmd, "Shell status") == 0) ) {
        *handled = true;
        return PrintStatus(io);
    }
    return ERR_OK; /* no error */
}

byte Shell_ParseWithCommandTable( const unsigned char *cmd, Shell_ConstStdIO_t *io,
        Shell_ConstParseCommandCallback_t *parseCallback )
{
    uint8_t res = ERR_OK;
    bool handled;
    bool silent;

    if ( *cmd == '\0' ) { /* empty command */
        return ERR_OK;
    }
    /* parse first shell commands */
    handled = false;
    silent = (bool) (*cmd == '#');
    if ( silent ) {
        cmd++; /* skip '#' */
    }
    res = IterateTable(cmd, &handled, io, parseCallback); /* iterate through all parser functions in table */
    if ( !handled || res != ERR_OK ) { /* no handler has handled the command? */
        PrintCommandFailed(cmd, io);
        res = ERR_FAILED;
    }
    if ( !silent ) {
        PrintPrompt(io);
    }
    return res;
}

byte Shell_ReadAndParseWithCommandTable( unsigned char *cmdBuf, size_t cmdBufSize,
        Shell_ConstStdIO_t *io, Shell_ConstParseCommandCallback_t *parseCallback )
{
    uint8_t res = ERR_OK;
    size_t len;

    /* IMPORTANT NOTE: this function *appends* to the buffer, so the buffer needs to be initialized first! */
    len = strlen((const char*) cmdBuf);
    if ( ReadLine(cmdBuf + len, cmdBufSize - len, io) ) {
        len = strlen((const char*) cmdBuf); /* length of buffer string */
        if ( len == 0 ) { /* error case */
            return ERR_FAILED;
        } else if ( len == 1 && (cmdBuf[0] == '\n' || cmdBuf[0] == '\r') ) { /* eat preceding newline characters */
            cmdBuf[0] = '\0';
        }
        if ( len >= cmdBufSize - 1 ) { /* buffer overflow? Parse what we have, will be likely return an error */
            res = Shell_ParseWithCommandTable(cmdBuf, io, parseCallback);
            cmdBuf[0] = '\0'; /* start again */
            res = ERR_OVERFLOW;
        } else if ( cmdBuf[len - 1] == '\n' || cmdBuf[len - 1] == '\r' ) { /* line end: parse command */
            cmdBuf[len - 1] = '\0'; /* remove line end character for parser */
            res = Shell_ParseWithCommandTable(cmdBuf, io, parseCallback);
            cmdBuf[0] = '\0'; /* start again */
        } else {
            /* continue to append to buffer */
        }
    }
    return res;
}

Shell_ConstStdIO_t *Shell_GetStdio( void )
{
    return Shell_currStdIO;
}

uint8_t Shell_SetStdio( Shell_ConstStdIO_t *stdio )
{
    Shell_currStdIO = stdio;
    return ERR_OK;
}

void Shell_ReadChar( unsigned char *ch )
{
    if ( !Uart1.IsInitialized ) return;

    if ( UartGetChar(&Uart1, (uint8_t *) ch) == ERR_RXEMPTY ) {
        /* no character in buffer */
        *ch = '\0';
    }
}

void Shell_SendChar( unsigned char ch )
{
    if ( !Uart1.IsInitialized ) return;

    UartPutBuffer(&Uart1, (uint8_t *) &ch, 1);
}

bool Shell_KeyPressed( void )
{
    return !IsFifoEmpty(&Uart1.FifoRx);
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
uint8_t IterateTable( const unsigned char *cmd, bool *handled, Shell_ConstStdIO_t *io,
        Shell_ConstParseCommandCallback_t *parserTable )
{
    uint8_t res = ERR_OK;

    if ( parserTable == NULL ) { /* no table??? */
        return ERR_FAILED;
    }
    /* iterate through all parser functions in table */
    while (*parserTable != NULL) {
        if ( (*parserTable)(cmd, handled, io) != ERR_OK ) {
            res = ERR_FAILED;
        }
        parserTable++;
    }
    return res;
}

void PrintPrompt( Shell_ConstStdIO_t *io )
{
    Shell_SendStr((unsigned char*) "CMD> ", io->stdOut);
}

uint8_t PrintStatus( Shell_ConstStdIO_t *io )
{
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\nSYSTEM STATUS\r\n", io->stdOut);
    Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    Shell_SendStatusStr((const unsigned char*) "Firmware",
            (const unsigned char*) __DATE__, io->stdOut);
    Shell_SendStr((unsigned char*) " ", io->stdOut);
    Shell_SendStr((unsigned char*) __TIME__, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    return ERR_OK;
}

void PrintCommandFailed( const unsigned char *cmd, Shell_ConstStdIO_t *io )
{
    Shell_SendStr((unsigned char*) "*** Failed or unknown command: ", io->stdErr);
    Shell_SendStr(cmd, io->stdErr);
    Shell_SendStr((unsigned char*) "\r\n", io->stdErr);
    Shell_SendStr((unsigned char*) "*** Type ", io->stdErr);
    Shell_SendStr((unsigned char*) SHELL_CMD_HELP, io->stdErr);
    Shell_SendStr((unsigned char*) " to get a list of available commands\r\n",
            io->stdErr);
}

bool ReadLine( uint8_t *buf, size_t bufSize, Shell_ConstStdIO_t *io )
{
    unsigned char c;

    if ( io->keyPressed() ) {
        for ( ;; ) { /* while not '\r' or '\n' */
            c = '\0'; /* initialize character */
            io->stdIn(&c); /* read character */
            if ( c == '\0' ) { /* nothing in rx buffer? Something is wrong... */
                break; /* get out of loop */
            }
            *buf = (uint8_t) c; /* append character to the string */
            io->stdOut(c); /* console feedback */
            buf++;
            bufSize--;
            if ( (c == '\r') || (c == '\n') ) {
                break;
            }
            if ( bufSize <= 1 ) { /* buffer full */
                break;
            }
        } /* for */
        *buf = '\0'; /* zero terminate string */
        return true;
    } else {
        return false;
    }
}

void SendSeparatedStrings( const uint8_t *strA, const uint8_t *strB, uint8_t tabChar,
        uint8_t tabPos, StdIO_OutErrFunction_t io )
{
    /* write command part */
    while (*strA != '\0' && tabPos > 0) {
        io(*strA++);
        tabPos--;
    }
    /* fill up until ';' */
    while (tabPos > 0) {
        io(' ');
        tabPos--;
    }
    /* write separator */
    io(tabChar);
    io(' ');
    /* write help text */
    Shell_SendStr(strB, io);
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
