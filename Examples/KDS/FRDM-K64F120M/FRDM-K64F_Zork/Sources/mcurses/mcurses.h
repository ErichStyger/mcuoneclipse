/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses.h - include file for mcurses lib
 *
 * Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de
 *
 * Revision History:
 * V1.0 2015 xx xx Frank Meyer, original version
 * V1.1 2017 01 13 ChrisMicro, addepted as Arduino library, MCU specific functions removed
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C"
{
	#endif

	#ifndef __MCURSES__
	#define __MCURSES__
	
#include <stdint.h>
#include <string.h>

#include "mcurses-config.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * some constants
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define LINES                   MCURSES_LINES
#define COLS                    MCURSES_COLS

#ifndef TRUE
#define TRUE                    (1)                                                 // true
#define FALSE                   (0)                                                 // false
#endif

#define OK                      (0)                                                 // yet not used
#define ERR                     (255)                                               // yet not used

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * attributes, may be ORed
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define A_NORMAL                0x0000                                              // normal
#define A_UNDERLINE             0x0001                                              // underline
#define A_REVERSE               0x0002                                              // reverse
#define A_BLINK                 0x0004                                              // blink
#define A_BOLD                  0x0008                                              // bold
#define A_DIM                   0x0010                                              // dim
#define A_STANDOUT              A_BOLD                                              // standout (same as bold)

#define F_BLACK                 0x0100                                              // foreground black
#define F_RED                   0x0200                                              // foreground red
#define F_GREEN                 0x0300                                              // foreground green
#define F_BROWN                 0x0400                                              // foreground brown
#define F_BLUE                  0x0500                                              // foreground blue
#define F_MAGENTA               0x0600                                              // foreground magenta
#define F_CYAN                  0x0700                                              // foreground cyan
#define F_WHITE                 0x0800                                              // foreground white
#define F_YELLOW                F_BROWN                                             // some terminals show brown as yellow (with A_BOLD)
#define F_COLOR                 0x0F00                                              // foreground mask

#define B_BLACK                 0x1000                                              // background black
#define B_RED                   0x2000                                              // background red
#define B_GREEN                 0x3000                                              // background green
#define B_BROWN                 0x4000                                              // background brown
#define B_BLUE                  0x5000                                              // background blue
#define B_MAGENTA               0x6000                                              // background magenta
#define B_CYAN                  0x7000                                              // background cyan
#define B_WHITE                 0x8000                                              // background white
#define B_YELLOW                B_BROWN                                             // some terminals show brown as yellow (with A_BOLD)
#define B_COLOR                 0xF000                                              // background mask

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses variables
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
extern uint_fast8_t             mcurses_is_up;                                      // flag: mcurses is up
extern uint_fast8_t             mcurses_cury;                                       // do not use, use getyx() instead!
extern uint_fast8_t             mcurses_curx;                                       // do not use, use getyx() instead!

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses functions
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void                     setFunction_putchar(void (*functionPoitner)(uint8_t ch));
void                     setFunction_getchar(char (*functionPoitner)(void));
uint_fast8_t             initscr (void);                                     // initialize mcurses
void                     move (uint_fast8_t, uint_fast8_t);                  // move cursor to line, column (home = 0, 0)
void                     attrset (uint_fast16_t);                            // set attribute(s)
void                     addch (uint_fast8_t);                               // add a character
void                     addstr (const char *);                              // add a string
void                     addstr_P (const char *);                            // add a string (PROGMEM)
void                     getnstr (char * str, uint_fast8_t maxlen);          // read a string (with mini editor functionality)
void                     setscrreg (uint_fast8_t, uint_fast8_t);             // set scrolling region
void                     deleteln (void);                                    // delete line at current line position
void                     insertln (void);                                    // insert a line at current line position
void                     scroll (void);                                      // scroll line up
void                     clear (void);                                       // clear total screen
void                     clrtobot (void);                                    // clear screen from current line to bottom
void                     clrtoeol (void);                                    // clear from current column to end of line
void                     delch (void);                                       // delete character at current position
void                     insch (uint_fast8_t);                               // insert character at current position
void                     nodelay (uint_fast8_t);                             // set/reset nodelay
void                     halfdelay (uint_fast8_t);                           // set/reset halfdelay
uint_fast8_t             getch (void);                                       // read key
void                     curs_set(uint_fast8_t);                             // set cursor to: 0=invisible 1=normal 2=very visible
void                     refresh (void);                                     // flush output
void                     endwin (void);                                      // end mcurses

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses macros
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define erase()                 clear()                                             // clear total screen, same as clear()
#define mvaddch(y,x,c)          move((y),(x)), addch((c))                           // move cursor, then add character
#define mvaddstr(y,x,s)         move((y),(x)), addstr((s))                          // move cursor, then add string
#define mvaddstr_P(y,x,s)       move((y),(x)), addstr_P((s))                        // move cursor, then add string (PROGMEM)



#define mvinsch(y,x,c)          move((y),(x)), insch((c))                           // move cursor, then insert character
#define mvdelch(y,x)            move((y),(x)), delch()                              // move cursor, then delete character
#define mvgetnstr(y,x,s,n)      move((y),(x)), getnstr(s,n)                         // move cursor, then get string
#define getyx(y,x)              y = mcurses_cury, x = mcurses_curx                  // get cursor coordinates

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses keys
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define KEY_TAB                 '\t'                                                // TAB key
#define KEY_CR                  '\r'                                                // RETURN key
#define KEY_BACKSPACE           '\b'                                                // Backspace key
#define KEY_ESCAPE              0x1B                                                // ESCAPE (pressed twice)

#define KEY_DOWN                0x80                                                // Down arrow key
#define KEY_UP                  0x81                                                // Up arrow key
#define KEY_LEFT                0x82                                                // Left arrow key
#define KEY_RIGHT               0x83                                                // Right arrow key
#define KEY_HOME                0x84                                                // Home key
#define KEY_DC                  0x85                                                // Delete character key
#define KEY_IC                  0x86                                                // Ins char/toggle ins mode key
#define KEY_NPAGE               0x87                                                // Next-page key
#define KEY_PPAGE               0x88                                                // Previous-page key
#define KEY_END                 0x89                                                // End key
#define KEY_BTAB                0x8A                                                // Back tab key
#define KEY_F1                  0x8B                                                // Function key F1
#define KEY_F(n)                (KEY_F1+(n)-1)                                      // Space for additional 12 function keys

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * graphics: draw boxes
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define ACS_LRCORNER            0x8a                                                // DEC graphic 0x6a: lower right corner
#define ACS_URCORNER            0x8b                                                // DEC graphic 0x6b: upper right corner
#define ACS_ULCORNER            0x8c                                                // DEC graphic 0x6c: upper left corner
#define ACS_LLCORNER            0x8d                                                // DEC graphic 0x6d: lower left corner
#define ACS_PLUS                0x8e                                                // DEC graphic 0x6e: crossing lines
#define ACS_HLINE               0x91                                                // DEC graphic 0x71: horizontal line
#define ACS_LTEE                0x94                                                // DEC graphic 0x74: left tee
#define ACS_RTEE                0x95                                                // DEC graphic 0x75: right tee
#define ACS_BTEE                0x96                                                // DEC graphic 0x76: bottom tee
#define ACS_TTEE                0x97                                                // DEC graphic 0x77: top tee
#define ACS_VLINE               0x98                                                // DEC graphic 0x78: vertical line

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * graphics: other symbols
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define ACS_DIAMOND             0x80                                                // DEC graphic 0x60: diamond
#define ACS_CKBOARD             0x81                                                // DEC graphic 0x61: checker board
#define ACS_DEGREE              0x86                                                // DEC graphic 0x66: degree symbol
#define ACS_PLMINUS             0x87                                                // DEC graphic 0x66: plus/minus

#define ACS_S1                  0x8f                                                // DEC graphic 0x6f: scan line 1
#define ACS_S3                  0x90                                                // DEC graphic 0x70: scan line 3
#define ACS_S5                  0x91                                                // DEC graphic 0x71: scan line 5
#define ACS_S7                  0x92                                                // DEC graphic 0x72: scan line 7
#define ACS_S9                  0x93                                                // DEC graphic 0x73: scan line 9
#define ACS_LEQUAL              0x99                                                // DEC graphic 0x79: less/equal
#define ACS_GEQUAL              0x9a                                                // DEC graphic 0x7a: greater/equal
#define ACS_PI                  0x9b                                                // DEC graphic 0x7b: Pi
#define ACS_NEQUAL              0x9c                                                // DEC graphic 0x7c: not equal
#define ACS_STERLING            0x9d                                                // DEC graphic 0x7d: uk pound sign
#define ACS_BULLET              0x9e                                                // DEC graphic 0x7e: bullet



	
	#endif // __MCURSES__

	#ifdef __cplusplus
}
#endif
