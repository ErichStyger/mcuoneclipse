/*
 * commandParser.h
 *
 * Created on: 31 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef COMMAND_PARSER_H_
#define COMMAND_PARSER_H_

#define RTT_CMD_BUF_SIZE (100)

void init_commandParser(void);
void commandParser_checkInputParse(void);

#endif /* COMMAND_PARSER_H_ */
