/*-----------------------------------------------------------------------------------------------------------------

   line editor 

   Revision History:
   V1.0 2017 01 18 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

  ---------------------------------------------------------------------------------------------------------------*/

#include "mcurses.h"
#include <stdlib.h>     // strtol 

/*-----------------------------------------------------------------------------------------------------------------

 string line editor editor

 input: string buffer: the content of the buffer will be displayed and you can edit it
        lineLength   : maximum number of characters the line can have and can be edited

  output: *str       : edited string


 This function is a modified and extended version of  

 void getnstr (char * str, uint_fast8_t maxlen)

 which allows predefined strings.

 getnstr was written by  Frank Meyer - frank(at)fli4l.de
 
------------------------------------------------------------------------------------------------------------------*/
 
void editLine (char * str, uint8_t lineLength )
{
    uint_fast8_t ch;
    uint_fast8_t curlen = 0;
    uint_fast8_t curpos = 0;
    uint_fast8_t starty;
    uint_fast8_t startx;
    uint_fast8_t i;

	curlen=strlen(str);
	curpos=curlen;

    getyx (starty, startx);           // get current cursor position	
	for (i=0;i<lineLength;i++)addch(' '); // clear region

	attrset(A_REVERSE);
		
	move(starty,startx);
	addstr (str);    // show text

	move (starty, startx+curpos);

    while ((ch = getch ()) != KEY_CR)
    {
        switch (ch)
        {
            case KEY_LEFT:
                if (curpos > 0)
                {
                    curpos--;
                }
                break;
            case KEY_RIGHT:
                if (curpos < curlen)
                {
                    curpos++;
                }
                break;
            case KEY_HOME:
                curpos = 0;
                break;
            case KEY_END:
                curpos = curlen;
                break;
            case KEY_BACKSPACE:
                if (curpos > 0)
                {
                    curpos--;
                    curlen--;
                    move (starty, startx + curpos);

                    for (i = curpos; i < curlen; i++)
                    {
                        str[i] = str[i + 1];
                    }
                    str[i] = '\0';
										
					for(i=curpos;i<curlen;i++)addch(str[i]);
					attrset(A_REVERSE);
					attrset(A_NORMAL);
					addch(' ');
					attrset(A_REVERSE);
                }
                break;

            case KEY_DC: // delete-key
                if (curlen > 0)
                {
                    curlen--;
                    for (i = curpos; i < curlen; i++)
                    {
                        str[i] = str[i + 1];
                    }
                    str[i] = '\0';

                    for(i=curpos;i<curlen;i++)addch(str[i]);
					attrset(A_REVERSE);
					attrset(A_NORMAL);
					addch(' ');
					attrset(A_REVERSE);
                }
                break;

            default:
                if (curlen < lineLength && (ch & 0x7F) >= 32 && (ch & 0x7F) < 127)      // printable ASCII 7bit or printable 8bit ISO8859
                {
                    for (i = curlen; i > curpos; i--)
                    {
                        str[i] = str[i - 1];
                    }
                    str[curpos] = ch;
                    curlen++;
                    for(i=curpos;i<curlen;i++)addch(str[i]);
					curpos++;					
                }
        }
        move (starty, startx + curpos);
    }
    str[curlen] = '\0';
	
	// redraw the string with normal attribute
	attrset(A_REVERSE);
	attrset(A_NORMAL);
	move(starty,startx);
	addstr (str);    // show text
}

/*-----------------------------------------------------------------------------------------------------------------

 edit a given number

 input: number: initial number. It will be displayed

 output: edited number
 
-----------------------------------------------------------------------------------------------------------------*/

int16_t editInt16(int16_t initialNumber)
{
	  char text[10];
      uint8_t starty;
      uint8_t startx;
	      
      getyx (starty, startx);   // get current cursor position

	  itoa(initialNumber,text,10);
	  editLine (text,6);
	  
	  int16_t number = strtol(text, 0, 10);

	  itoa(number,text,10);
	  move (starty, startx);    // set cursor position from the beginning
	  addstr (text);            // show text
	  return number;
}
