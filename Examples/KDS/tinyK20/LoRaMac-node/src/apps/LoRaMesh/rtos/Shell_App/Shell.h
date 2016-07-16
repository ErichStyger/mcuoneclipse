/**
 * \file Shell.h
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
#ifndef SHELL_H_
#define SHELL_H_

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#define SHELL_DASH_LINE "--------------------------------------------------------------"
/* predefined commands */
#define SHELL_CMD_HELP   "help"
#define SHELL_CMD_STATUS "status"

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
/**/
typedef unsigned char byte;

/* Callback for an output or error I/O function */
typedef void (*StdIO_OutErrFunction_t)( byte );

/* Callback for an I/O input function. */
typedef void (*StdIO_InFunction_t)( byte * );

/* Callback which returns true if a key has been pressed */
typedef bool (*StdIO_KeyPressedFunction_t)( void );

/* Record containing input, output and error callback (stdin, stdout, stderr). */
typedef struct {
    StdIO_InFunction_t stdIn; /* standard input */
    StdIO_OutErrFunction_t stdOut; /* standard output */
    StdIO_OutErrFunction_t stdErr; /* standard error */
    StdIO_KeyPressedFunction_t keyPressed; /* key pressed callback */
} Shell_StdIO_t;

/* constant StdIOType */
typedef const Shell_StdIO_t Shell_ConstStdIO_t;

/* Callback for parsing a shell command */
typedef byte (*Shell_ParseCommandCallback_t)( const byte *cmd, bool *handled,
        const Shell_StdIO_t *io );

/* Callback for parsing a shell command */
typedef const Shell_ParseCommandCallback_t Shell_ConstParseCommandCallback_t;

/*******************************************************************************
 * MODULE FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
void Shell_Init( void );

void Shell_SendHelpStr( const byte *strCmd, const byte *strHelp,
        StdIO_OutErrFunction_t io );

void Shell_SendStatusStr( const byte *strItem, const byte *strStatus,
        StdIO_OutErrFunction_t io );

void Shell_SendStr( const byte *str, StdIO_OutErrFunction_t io );

byte Shell_ParseCommand( const unsigned char *cmd, bool *handled,
        Shell_ConstStdIO_t *io );

byte Shell_ParseWithCommandTable( const unsigned char *cmd, Shell_ConstStdIO_t *io,
        Shell_ConstParseCommandCallback_t *parseCallback );

byte Shell_ReadAndParseWithCommandTable( byte *cmdBuf, size_t cmdBufSize,
        Shell_ConstStdIO_t *io, Shell_ConstParseCommandCallback_t *parseCallback );

Shell_ConstStdIO_t *Shell_GetStdio( void );

uint8_t Shell_SetStdio( Shell_ConstStdIO_t *stdio );

void Shell_ReadChar( byte *ch );

void Shell_SendChar( byte ch );

bool Shell_KeyPressed( void );

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#endif /* SHELL_H_ */
