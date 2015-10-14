#ifndef __FRDM_S401_H_
#define __FRDM_S401_H_
/*^^^^^^^^^^^^^^^^      LCD HARDWARE CONECTION ^^^^^^^^^^^^^^^^^^^^^^^^*/
#define  _LCDFRONTPLANES   (8)                             // # of frontPlanes
#define  _LCDBACKPLANES    (4)                              // # of backplanes

/*
   LCD logical organization definition
    This section indicate how the LCD is distributed  how many characteres of (7-seg, 14,seg, 16 seg, or colums in case of Dot Matrix) does it contain
   First character is forced only one can be written

*/
// HARDWARE_CONFIG Changing LCD pins Allows to verify all LCD pins easily
// if HARDWARE_CONFIG  == 0 FRDM-KL46 RevB 
// if HARDWARE_CONFIG  == 1 FRDM-KL46 RevA
#include "Cpu.h"

#ifdef FRDM_REVA
#define HARDWARE_CONFIG 1
#else
#define HARDWARE_CONFIG 0
#endif

#define _CHARNUM     (4)  //number of chars that can be written
#define _CHAR_SIZE   (2)  // Used only when Dot Matrix is used
#define _LCDTYPE     (2)  //indicate how many LCD_WF are required to write a single Character / or Column in case of DOT matrix LCD

/*
  Following definitions indicate how characters are associated to waveform
*/
/* Hardware configuration  */
#if HARDWARE_CONFIG == 0
#undef DOT_MATRIX

// LCD PIN1 to LCDWF0  Rev B
#define   CHAR1a    37 // LCD Pin 5
#define   CHAR1b    17 // LCD Pin 6
#define   CHAR2a    7 // LCD Pin 7
#define   CHAR2b    8 // LCD Pin 8
#define   CHAR3a    53 // LCD Pin 9
#define   CHAR3b    38 // LCD Pin 10
#define   CHAR4a    10 // LCD Pin 11
#define   CHAR4b    11 // LCD Pin 12
#define   CHARCOM0    40 // LCD Pin 1
#define   CHARCOM1    52 // LCD Pin 2
#define   CHARCOM2    19 // LCD Pin 3
#define   CHARCOM3    18 // LCD Pin 4

/*Special Symbols */
#define SPECIAL_SYMBOL_COUNT   4

#define   _LCD_DP1_ON()      SymbolON(17,0)
#define   _LCD_DP2_ON()      SymbolON(8,0)
#define   _LCD_DP3_ON()      SymbolON(38,0)
#define   _LCD_COL_ON()      SymbolON(11,0)

#define   _LCD_DP1_OFF()      SymbolOFF(17,0)
#define   _LCD_DP2_OFF()      SymbolOFF(8,0)
#define   _LCD_DP3_OFF()      SymbolOFF(38,0)
#define   _LCD_COL_OFF()      SymbolOFF(11,0)

// LCD PIN1 to LCDWF2   for FRDM-KL46Z
#elif HARDWARE_CONFIG == 1
#define   CHAR1a    37 // LCD Pin 5
#define   CHAR1b    17 // LCD Pin 6
#define   CHAR2a    7 // LCD Pin 7
#define   CHAR2b    8 // LCD Pin 8
#define   CHAR3a    12 // LCD Pin 9
#define   CHAR3b    26 // LCD Pin 10
#define   CHAR4a    10 // LCD Pin 11
#define   CHAR4b    11 // LCD Pin 12
#define   CHARCOM0    51 // LCD Pin 1
#define   CHARCOM1    52 // LCD Pin 2
#define   CHARCOM2    19 // LCD Pin 3
#define   CHARCOM3    16 // LCD Pin 4

#define SPECIAL_SYMBOL_COUNT   4


#define   _LCD_DP1_ON()      SymbolON(17,0)
#define   _LCD_DP2_ON()      SymbolON(8,0)
#define   _LCD_DP3_ON()      SymbolON(26,0)
#define   _LCD_COL_ON()      SymbolON(11,0)

#define   _LCD_DP1_OFF()      SymbolOFF(17,0)
#define   _LCD_DP2_OFF()      SymbolOFF(8,0)
#define   _LCD_DP3_OFF()      SymbolOFF(26,0)
#define   _LCD_COL_OFF()      SymbolOFF(11,0)



#endif


/*Ascii Codification table information */
#define ASCCI_TABLE_START '0'   // indicates which is the first Ascii character in the table
#define ASCCI_TABLE_END   'Z'   // indicates which is the first Ascii character in the table
#define BLANK_CHARACTER   '>'  // Indicate which ASCII character is a blank character (depends on ASCII table)

#define _ALLON 0xFF     // Used for ALL_on function 

#define SEGDP 0x01
#define SEGC  0x02
#define SEGB  0x04
#define SEGA  0x08

#define SEGD  0x01
#define SEGE  0x02
#define SEGG  0x04
#define SEGF  0x08


/* Fault detect initial limits */

/* Fault detect initial parameters and limits */
#define FAULTD_FP_FDPRS  FDPRS_32
#define FAULTD_FP_FDSWW  FDSWW_128
#define FAULTD_BP_FDPRS  FDPRS_64
#define FAULTD_BP_FDSWW  FDSWW_128

#define FAULTD_FP_HI  127
#define FAULTD_FP_LO  110
#define FAULTD_BP_HI  127
#define FAULTD_BP_LO  110
#define FAULTD_TIME   6

extern const uint8  WF_ORDERING_TABLE[];              //   Logical Front plane N to LCD_WFx
extern const char  ASCII_TO_WF_CODIFICATION_TABLE[]; //   ASCII to 7x5 Dot Matrix

#endif /* __FRDM_S401_H_ */
