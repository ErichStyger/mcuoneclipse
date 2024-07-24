/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses.c - mcurses lib
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __AVR__
	#include <avr/pgmspace.h>
#else
	#define PROGMEM
	#define PSTR(x)                                 (x)
	#define pgm_read_byte(s)                        (*s)
#endif 

#include "mcurses/mcurses.h"

#define SEQ_CSI                                 PSTR("\033[")                   // code introducer
#define SEQ_CLEAR                               PSTR("\033[2J")                 // clear screen
#define SEQ_CLRTOBOT                            PSTR("\033[J")                  // clear to bottom
#define SEQ_CLRTOEOL                            PSTR("\033[K")                  // clear to end of line
#define SEQ_DELCH                               PSTR("\033[P")                  // delete character
#define SEQ_NEXTLINE                            PSTR("\033E")                   // goto next line (scroll up at end of scrolling region)
#define SEQ_INSERTLINE                          PSTR("\033[L")                  // insert line
#define SEQ_DELETELINE                          PSTR("\033[M")                  // delete line
#define SEQ_ATTRSET                             PSTR("\033[0")                  // set attributes, e.g. "\033[0;7;1m"
#define SEQ_ATTRSET_REVERSE                     PSTR(";7")                      // reverse
#define SEQ_ATTRSET_UNDERLINE                   PSTR(";4")                      // underline
#define SEQ_ATTRSET_BLINK                       PSTR(";5")                      // blink
#define SEQ_ATTRSET_BOLD                        PSTR(";1")                      // bold
#define SEQ_ATTRSET_DIM                         PSTR(";2")                      // dim
#define SEQ_ATTRSET_FCOLOR                      PSTR(";3")                      // forground color
#define SEQ_ATTRSET_BCOLOR                      PSTR(";4")                      // background color
#define SEQ_INSERT_MODE                         PSTR("\033[4h")                 // set insert mode
#define SEQ_REPLACE_MODE                        PSTR("\033[4l")                 // set replace mode
#define SEQ_RESET_SCRREG                        PSTR("\033[r")                  // reset scrolling region
#define SEQ_LOAD_G1                             PSTR("\033)0")                  // load G1 character set
#define SEQ_CURSOR_VIS                          PSTR("\033[?25")                // set cursor visible/not visible

static uint_fast8_t                             mcurses_scrl_start = 0;         // start of scrolling region, default is 0
static uint_fast8_t                             mcurses_scrl_end = LINES - 1;   // end of scrolling region, default is last line
static uint_fast8_t                             mcurses_nodelay;                // nodelay flag
static uint_fast8_t                             mcurses_halfdelay;              // halfdelay value, in tenths of a second

uint_fast8_t                                    mcurses_is_up = 0;              // flag: mcurses is up
uint_fast8_t                                    mcurses_cury = 0xff;            // current y position of cursor, public (getyx())
uint_fast8_t                                    mcurses_curx = 0xff;            // current x position of cursor, public (getyx())

static void                                     mcurses_puts_P (const char *);

char (*FunctionPointer_getchar)(void);
void  (*FunctionPointer_putchar)(uint_fast8_t ch);

void setFunction_getchar(char (*functionPoitner)(void))
{
	FunctionPointer_getchar = functionPoitner;
}

void setFunction_putchar(void (*functionPoitner)(uint8_t ch))
{
	FunctionPointer_putchar = functionPoitner;
}

static uint_fast8_t mcurses_phyio_init (void)
{
  return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * PHYIO: done (AVR)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void mcurses_phyio_done (void)
{
	
}

static void mcurses_phyio_putc (uint_fast8_t ch)
{
	if(FunctionPointer_putchar!=0)	FunctionPointer_putchar(ch);
}

static uint_fast8_t mcurses_phyio_getc (void)
{
	if(FunctionPointer_getchar!=0)	return FunctionPointer_getchar();
	else return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * PHYIO: set/reset nodelay (AVR)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void mcurses_phyio_nodelay (uint_fast8_t flag)
{
    mcurses_nodelay = flag;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * PHYIO: set/reset halfdelay (AVR)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void mcurses_phyio_halfdelay (uint_fast8_t tenths)
{
    mcurses_halfdelay = tenths;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * PHYIO: flush output (AVR)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void mcurses_phyio_flush_output ()
{
	
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * INTERN: put a character (raw)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void
mcurses_putc (uint_fast8_t ch)
{
    mcurses_phyio_putc (ch);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * INTERN: put a string from flash (raw)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void
mcurses_puts_P (const char * str)
{
    uint_fast8_t ch;

    while ((ch = pgm_read_byte(str)) != '\0')
    {
        mcurses_putc (ch);
        str++;
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * INTERN: put a 3/2/1 digit integer number (raw)
 *
 * Here we don't want to use sprintf (too big on AVR/Z80) or itoa (not available on Z80)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void
mcurses_puti (uint_fast8_t i)
{
    uint_fast8_t ii;

    if (i >= 10)
    {
        if (i >= 100)
        {
            ii = i / 100;
            mcurses_putc (ii + '0');
            i -= 100 * ii;
        }

        ii = i / 10;
        mcurses_putc (ii + '0');
        i -= 10 * ii;
    }

    mcurses_putc (i + '0');
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * INTERN: addch or insch a character
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define CHARSET_G0      0
#define CHARSET_G1      1

static void
mcurses_addch_or_insch (uint_fast8_t ch, uint_fast8_t insert)
{
    static uint_fast8_t  charset = 0xff;
    static uint_fast8_t  insert_mode = FALSE;

    if (ch >= 0x80 && ch <= 0x9F)
    {
        if (charset != CHARSET_G1)
        {
            mcurses_putc ('\016');                                              // switch to G1 set
            charset = CHARSET_G1;
        }
        ch -= 0x20;                                                             // subtract offset to G1 characters
    }
    else
    {
        if (charset != CHARSET_G0)
        {
            mcurses_putc ('\017');                                              // switch to G0 set
            charset = CHARSET_G0;
        }
    }

    if (insert)
    {
        if (! insert_mode)
        {
            mcurses_puts_P (SEQ_INSERT_MODE);
            insert_mode = TRUE;
        }
    }
    else
    {
        if (insert_mode)
        {
            mcurses_puts_P (SEQ_REPLACE_MODE);
            insert_mode = FALSE;
        }
    }

    mcurses_putc (ch);
    mcurses_curx++;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * INTERN: set scrolling region (raw)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void
mysetscrreg (uint_fast8_t top, uint_fast8_t bottom)
{
    if (top == bottom)
    {
        mcurses_puts_P (SEQ_RESET_SCRREG);                                      // reset scrolling region
    }
    else
    {
        mcurses_puts_P (SEQ_CSI);
        mcurses_puti (top + 1);
        mcurses_putc (';');
        mcurses_puti (bottom + 1);
        mcurses_putc ('r');
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * move cursor (raw)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
static void
mymove (uint_fast8_t y, uint_fast8_t x)
{
    mcurses_puts_P (SEQ_CSI);
    mcurses_puti (y + 1);
    mcurses_putc (';');
    mcurses_puti (x + 1);
    mcurses_putc ('H');
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: initialize
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
uint_fast8_t
initscr (void)
{
    uint_fast8_t rtc;

    if (mcurses_phyio_init ())
    {
        mcurses_puts_P (SEQ_LOAD_G1);                                               // load graphic charset into G1
        attrset (A_NORMAL);
        clear ();
        move (0, 0);
        mcurses_is_up = 1;
        rtc = OK;
    }
    else
    {
        rtc = ERR;
    }
    return rtc;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: add character
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
addch (uint_fast8_t ch)
{
    mcurses_addch_or_insch (ch, FALSE);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: add string
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
addstr (const char * str)
{
    while (*str)
    {
        mcurses_addch_or_insch (*str++, FALSE);
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: add string
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
addstr_P (const char * str)
{
    uint_fast8_t ch;

    while ((ch = pgm_read_byte(str)) != '\0')
    {
        mcurses_addch_or_insch (ch, FALSE);
        str++;
    }
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: set attribute(s)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
attrset (uint_fast16_t attr)
{
    static uint_fast8_t mcurses_attr = 0xff;                    // current attributes
    uint_fast8_t        idx;

    if (attr != mcurses_attr)
    {
        mcurses_puts_P (SEQ_ATTRSET);

        idx = (attr & F_COLOR) >> 8;

        if (idx >= 1 && idx <= 8)
        {
            mcurses_puts_P (SEQ_ATTRSET_FCOLOR);
            mcurses_putc (idx - 1 + '0');
        }

        idx = (attr & B_COLOR) >> 12;

        if (idx >= 1 && idx <= 8)
        {
            mcurses_puts_P (SEQ_ATTRSET_BCOLOR);
            mcurses_putc (idx - 1 + '0');
        }

        if (attr & A_REVERSE)
        {
            mcurses_puts_P (SEQ_ATTRSET_REVERSE);
        }
        if (attr & A_UNDERLINE)
        {
            mcurses_puts_P (SEQ_ATTRSET_UNDERLINE);
        }
        if (attr & A_BLINK)
        {
            mcurses_puts_P (SEQ_ATTRSET_BLINK);
        }
        if (attr & A_BOLD)
        {
            mcurses_puts_P (SEQ_ATTRSET_BOLD);
        }
        if (attr & A_DIM)
        {
            mcurses_puts_P (SEQ_ATTRSET_DIM);
        }
        mcurses_putc ('m');
        mcurses_attr = attr;
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: move cursor
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
move (uint_fast8_t y, uint_fast8_t x)
{
    if (mcurses_cury != y || mcurses_curx != x)
    {
        mcurses_cury = y;
        mcurses_curx = x;
        mymove (y, x);
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: delete line
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
deleteln (void)
{
    mysetscrreg (mcurses_scrl_start, mcurses_scrl_end);                         // set scrolling region
    mymove (mcurses_cury, 0);                                                   // goto to current line
    mcurses_puts_P (SEQ_DELETELINE);                                            // delete line
    mysetscrreg (0, 0);                                                         // reset scrolling region
    mymove (mcurses_cury, mcurses_curx);                                        // restore position
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: insert line
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
insertln (void)
{
    mysetscrreg (mcurses_cury, mcurses_scrl_end);                               // set scrolling region
    mymove (mcurses_cury, 0);                                                   // goto to current line
    mcurses_puts_P (SEQ_INSERTLINE);                                            // insert line
    mysetscrreg (0, 0);                                                         // reset scrolling region
    mymove (mcurses_cury, mcurses_curx);                                        // restore position
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: scroll
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
scroll (void)
{
    mysetscrreg (mcurses_scrl_start, mcurses_scrl_end);                         // set scrolling region
    mymove (mcurses_scrl_end, 0);                                               // goto to last line of scrolling region
    mcurses_puts_P (SEQ_NEXTLINE);                                              // next line
    mysetscrreg (0, 0);                                                         // reset scrolling region
    mymove (mcurses_cury, mcurses_curx);                                        // restore position
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: clear
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
clear (void)
{
    mcurses_puts_P (SEQ_CLEAR);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: clear to bottom of screen
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
clrtobot (void)
{
    mcurses_puts_P (SEQ_CLRTOBOT);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: clear to end of line
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
clrtoeol (void)
{
    mcurses_puts_P (SEQ_CLRTOEOL);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: delete character at cursor position
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
delch (void)
{
    mcurses_puts_P (SEQ_DELCH);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: insert character
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
insch (uint_fast8_t ch)
{
    mcurses_addch_or_insch (ch, TRUE);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: set scrolling region
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
setscrreg (uint_fast8_t t, uint_fast8_t b)
{
    mcurses_scrl_start = t;
    mcurses_scrl_end = b;
}

void
curs_set (uint_fast8_t visibility)
{
    mcurses_puts_P (SEQ_CURSOR_VIS);

    if (visibility == 0)
    {
        mcurses_putc ('l');
    }
    else
    {
        mcurses_putc ('h');
    }
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: refresh: flush output
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
refresh (void)
{
    mcurses_phyio_flush_output ();
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: set/reset nodelay
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
nodelay (uint_fast8_t flag)
{
    if (mcurses_nodelay != flag)
    {
        mcurses_phyio_nodelay (flag);
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: set/reset halfdelay
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
halfdelay (uint_fast8_t tenths)
{
    mcurses_phyio_halfdelay (tenths);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: read key
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#define MAX_KEYS                ((KEY_F1 + 12) - 0x80)

static const char * function_keys[MAX_KEYS] =
{
    "B",                        // KEY_DOWN                 0x80                // Down arrow key
    "A",                        // KEY_UP                   0x81                // Up arrow key
    "D",                        // KEY_LEFT                 0x82                // Left arrow key
    "C",                        // KEY_RIGHT                0x83                // Right arrow key
    "1~",                       // KEY_HOME                 0x84                // Home key
    "3~",                       // KEY_DC                   0x85                // Delete character key
    "2~",                       // KEY_IC                   0x86                // Ins char/toggle ins mode key
    "6~",                       // KEY_NPAGE                0x87                // Next-page key
    "5~",                       // KEY_PPAGE                0x88                // Previous-page key
    "4~",                       // KEY_END                  0x89                // End key
    "Z",                        // KEY_BTAB                 0x8A                // Back tab key
#if 0 // VT400:
    "11~",                      // KEY_F(1)                 0x8B                // Function key F1
    "12~",                      // KEY_F(2)                 0x8C                // Function key F2
    "13~",                      // KEY_F(3)                 0x8D                // Function key F3
    "14~",                      // KEY_F(4)                 0x8E                // Function key F4
    "15~",                      // KEY_F(5)                 0x8F                // Function key F5
#else // Linux console
    "[A",                       // KEY_F(1)                 0x8B                // Function key F1
    "[B",                       // KEY_F(2)                 0x8C                // Function key F2
    "[C",                       // KEY_F(3)                 0x8D                // Function key F3
    "[D",                       // KEY_F(4)                 0x8E                // Function key F4
    "[E",                       // KEY_F(5)                 0x8F                // Function key F5
#endif
    "17~",                      // KEY_F(6)                 0x90                // Function key F6
    "18~",                      // KEY_F(7)                 0x91                // Function key F7
    "19~",                      // KEY_F(8)                 0x92                // Function key F8
    "20~",                      // KEY_F(9)                 0x93                // Function key F9
    "21~",                      // KEY_F(10)                0x94                // Function key F10
    "23~",                      // KEY_F(11)                0x95                // Function key F11
    "24~"                       // KEY_F(12)                0x96                // Function key F12
};

uint_fast8_t
getch (void)
{
    char    buf[4];
    uint_fast8_t ch;
    uint_fast8_t idx;

    refresh ();
    ch = mcurses_phyio_getc ();

    if (ch == 0x7F)                                                             // BACKSPACE on VT200 sends DEL char
    {
        ch = KEY_BACKSPACE;                                                     // map it to '\b'
    }
    else if (ch == '\033')                                                      // ESCAPE
    {
        while ((ch = mcurses_phyio_getc ()) == ERR)
        {
            ;
        }

        if (ch == '\033')                                                       // 2 x ESCAPE
        {
            return KEY_ESCAPE;
        }
        else if (ch == '[')
        {
            for (idx = 0; idx < 3; idx++)
            {
                while ((ch = mcurses_phyio_getc ()) == ERR)
                {
                    ;
                }

                buf[idx] = ch;

                if ((ch >= 'A' && ch <= 'Z') || ch == '~')
                {
                    idx++;
                    break;
                }
            }

            buf[idx] = '\0';

            for (idx = 0; idx < MAX_KEYS; idx++)
            {
                if (! strcmp (buf, function_keys[idx]))
                {
                    ch = idx + 0x80;
                    break;
                }
            }

            if (idx == MAX_KEYS)
            {
                ch = ERR;
            }
        }
        else
        {
            ch = ERR;
        }
    }

    return ch;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: read string (with mini editor built-in)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
getnstr (char * str, uint_fast8_t maxlen)
{
    uint_fast8_t ch;
    uint_fast8_t curlen = 0;
    uint_fast8_t curpos = 0;
    uint_fast8_t starty;
    uint_fast8_t startx;
    uint_fast8_t i;

    maxlen--;                               // reserve one byte in order to store '\0' in last position
    getyx (starty, startx);                 // get current cursor position

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
                    delch();
                }
                break;

            case KEY_DC:
                if (curlen > 0)
                {
                    curlen--;
                    for (i = curpos; i < curlen; i++)
                    {
                        str[i] = str[i + 1];
                    }
                    str[i] = '\0';
                    delch();
                }
                break;

            default:
                if (curlen < maxlen && (ch & 0x7F) >= 32 && (ch & 0x7F) < 127)      // printable ascii 7bit or printable 8bit ISO8859
                {
                    for (i = curlen; i > curpos; i--)
                    {
                        str[i] = str[i - 1];
                    }
                    insch (ch);
                    str[curpos] = ch;
                    curpos++;
                    curlen++;
                }
        }
        move (starty, startx + curpos);
    }
    str[curlen] = '\0';
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MCURSES: endwin
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
endwin (void)
{
    move (LINES - 1, 0);                                                        // move cursor to last line
    clrtoeol ();                                                                // clear this line
    mcurses_putc ('\017');                                                      // switch to G0 set
    curs_set (TRUE);                                                            // show cursor
    mcurses_puts_P(SEQ_REPLACE_MODE);                                           // reset insert mode
    refresh ();                                                                 // flush output
    mcurses_phyio_done ();                                                      // end of physical I/O
    mcurses_is_up = 0;
}
