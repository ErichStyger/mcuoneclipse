/*
  Following table indicate how LCD_WF are logically organized to Chars(columns in the LCD)
  Char1 (LCD physical position)   to LCD_WF (offset)
   This table is used by  WriteChar function to write the character/column to appropriate place
Char1  is Defined in LCDHDW.h

Following Table is used 
1) indicate how WF are organized with 
2) LCD_Px  in this table will be enabled
3) LCD_Px  after _LCDFRONTPLANES will be configured as backplanes and initialized as 0x01, 0x02, etc.
*/

#include "LCDConfig.h" 

const uint8 WF_ORDERING_TABLE[ ] =
{
   CHAR1a,   // LCD81 --- Pin:5  LCDnAddress=51
   CHAR1b,   // LCD82 --- Pin:6  LCDnAddress=52
   CHAR2a,   // LCD83 --- Pin:7  LCDnAddress=53
   CHAR2b,   // LCD84 --- Pin:8  LCDnAddress=54
   CHAR3a,   // LCD85 --- Pin:9  LCDnAddress=55
   CHAR3b,   // LCD86 --- Pin:10  LCDnAddress=56
   CHAR4a,   // LCD87 --- Pin:11  LCDnAddress=57
   CHAR4b,   // LCD88 --- Pin:12  LCDnAddress=58
   CHARCOM0,   // LCD77 --- Pin:1  LCDnAddress=4D
   CHARCOM1,   // LCD78 --- Pin:2  LCDnAddress=4E
   CHARCOM2,   // LCD79 --- Pin:3  LCDnAddress=4F
   CHARCOM3,   // LCD80 --- Pin:4  LCDnAddress=50
};

/*
   Ascii to 8x6 dot matrix decodification table
*/
const char ASCII_TO_WF_CODIFICATION_TABLE [ ] =
{
( SEGD+ SEGE+ SEGF+!SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = 0,   offset=0
(!SEGD+!SEGE+!SEGF+!SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = 1,   offset=4
( SEGD+ SEGE+!SEGF+ SEGG) , (!SEGC+ SEGB+ SEGA) ,//Char = 2,   offset=8
( SEGD+!SEGE+!SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = 3,   offset=12
(!SEGD+!SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = 4,   offset=16
( SEGD+!SEGE+ SEGF+ SEGG) , ( SEGC+!SEGB+ SEGA) ,//Char = 5,   offset=20
( SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+!SEGB+ SEGA) ,//Char = 6,   offset=24
(!SEGD+!SEGE+!SEGF+!SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = 7,   offset=28
( SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = 8,   offset=32
( SEGD+!SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = 9,   offset=36
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = :,   offset=40
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = ;,   offset=44
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = <,   offset=48
( SEGD+!SEGE+!SEGF+ SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = =,   offset=52
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = >,   offset=56
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = ?,   offset=60
( SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = @,   offset=64
(!SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = A,   offset=68
( SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+!SEGB+!SEGA) ,//Char = B,   offset=72
( SEGD+ SEGE+ SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = C,   offset=76
( SEGD+ SEGE+!SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = D,   offset=80
( SEGD+ SEGE+ SEGF+ SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = E,   offset=84
(!SEGD+ SEGE+ SEGF+ SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = F,   offset=88
( SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+!SEGB+ SEGA) ,//Char = G,   offset=92
(!SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = H,   offset=96
(!SEGD+!SEGE+!SEGF+!SEGG) , ( SEGC+!SEGB+!SEGA) ,//Char = I,   offset=100
( SEGD+ SEGE+!SEGF+!SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = J,   offset=104
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = K,   offset=108
( SEGD+ SEGE+ SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = L,   offset=112
(!SEGD+ SEGE+ SEGF+!SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = M,   offset=116
(!SEGD+ SEGE+!SEGF+ SEGG) , ( SEGC+!SEGB+!SEGA) ,//Char = N,   offset=120
( SEGD+ SEGE+!SEGF+ SEGG) , ( SEGC+!SEGB+!SEGA) ,//Char = O,   offset=124
(!SEGD+ SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = P,   offset=128
( SEGD+!SEGE+ SEGF+ SEGG) , ( SEGC+ SEGB+ SEGA) ,//Char = Q,   offset=132
(!SEGD+ SEGE+ SEGF+ SEGG) , (!SEGC+ SEGB+ SEGA) ,//Char = R,   offset=136
( SEGD+!SEGE+ SEGF+ SEGG) , ( SEGC+!SEGB+ SEGA) ,//Char = S,   offset=140
( SEGD+ SEGE+ SEGF+ SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = T,   offset=144
( SEGD+ SEGE+ SEGF+!SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = U,   offset=148
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = V,   offset=152
(!SEGD+ SEGE+ SEGF+!SEGG) , ( SEGC+ SEGB+!SEGA) ,//Char = W,   offset=156
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = X,   offset=160
(!SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+!SEGA) ,//Char = Y,   offset=164
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = Z,   offset=168
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = [,   offset=172
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = \,   offset=176
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = ],   offset=180
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = ^,   offset=184
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = _,   offset=188
( SEGD+!SEGE+!SEGF+!SEGG) , (!SEGC+!SEGB+ SEGA) ,//Char = `,   offset=192
};
