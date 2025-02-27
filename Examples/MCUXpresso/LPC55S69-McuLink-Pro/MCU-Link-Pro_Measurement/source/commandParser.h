/*
 * commandParser.h
 *
 * Created on: 31 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef COMMAND_PARSER

#define RTT_CMD_BUF_SIZE (100)

void init_commandParser(void);
void commandParser_checkInputParse(void);

#define COMMAND_PARSER
#endif
