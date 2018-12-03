/*
 * editor.h
 *
 * Created: 19.01.2017 11:01:08
 *  Author: ChrisMicro
 */ 

#ifdef __cplusplus
extern "C"
{
	#endif

	#ifndef EDITOR_H_
	#define EDITOR_H_

	#include "mcurses.h"
	
	void editLine (char * str, uint8_t lineLength );
	int16_t editInt16(int16_t initialNumber);

	#endif /* EDITOR_H_ */

	#ifdef __cplusplus
}
#endif