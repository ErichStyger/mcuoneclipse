/**
 * \file
 * \brief This is the interface for a key matrix.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 *
 * This module implements a driver for a keyboard matrix (e.g. 4x4 keyboard).
 */

#include "KeyMatrix.h"

#include "Row0.h"
#include "Row1.h"
#include "Row2.h"
#include "Row3.h"
#include "Column0.h"
#include "Column1.h"
#include "Column2.h"
#include "Column3.h"
/*
 * Pins:
 * Row   : Pin0-3 (Rows   => output pins)
 * Column: Pin0-3 (Columns => input pins)
 */
#define KEY_MAX_ROWS  3 /* maximum number of rows */
#define KEY_MAX_COLS  3 /* maximum number of columns */
#define KEY_NO_ROWS   0xE /* special value for 'no' */
#define KEY_ALL_ROWS  0xF /* special value for 'all' */

/*!
 * \brief Selects a row (putting the row pin to HIGH), all other row pins to LOW.
 * \param row Row number. Use KEY_ALL_ROWS to select all rows.
 */
static void KeySelRow(int row) {
  switch(row) {
    case 0: 
      Row0_SetVal(); 
      Row1_ClrVal(); 
      Row2_ClrVal(); 
      Row3_ClrVal(); 
      break;
    case 1: 
      Row0_ClrVal(); 
      Row1_SetVal(); 
      Row2_ClrVal(); 
      Row3_ClrVal(); 
      break;
    case 2: 
      Row0_ClrVal(); 
      Row1_ClrVal(); 
      Row2_SetVal(); 
      Row3_ClrVal(); 
      break;
    case 3: 
      Row0_ClrVal(); 
      Row1_ClrVal(); 
      Row2_ClrVal(); 
      Row3_SetVal(); 
      break;    
    case KEY_NO_ROWS:
      Row0_ClrVal();
      Row1_ClrVal();
      Row2_ClrVal();
      Row3_ClrVal();
      break;
    case KEY_ALL_ROWS:
      Row0_SetVal();
      Row1_SetVal();
      Row2_SetVal();
      Row3_SetVal();
      break;
  } /* switch */
}

/*!
 * \brief Returns the column number of the currently pressed key.
 * \return Column number.
 */
static int KeyGetCol(void) {
  int val; /* bit not zero: key pressed */
  
  val = 0;
  if (Column0_GetVal()==0) {
    val |= (1<<0);
  }
  if (Column1_GetVal()==0) {
    val |= (1<<1);
  }
  if (Column2_GetVal()==0) {
    val |= (1<<2);
  }
  if (Column3_GetVal()==0) {
    val |= (1<<3);
  }
  return (val<<(KEY_MAX_COLS+1)); /* column bits in the upper nibble! */
}

/*!
 * \brief Calculates the key scan code.
 * \return
 */
int KeyDecode(void) {
  int column, row, col_id;
  int msk = (1<<(KEY_MAX_COLS+1)); /* high nibble bit set! */
  bool done;
  
  row = 0;
  column = KeyGetCol();  /* column is stored in upper nibble */
  done = FALSE;
  /* find out in which row the key is pressed */
  while (row<KEY_MAX_ROWS && !done) {
    KeySelRow(row); /* select row */
    if(KeyGetCol()!=0) { /* pressed in this row? */
      row++; /* no, go to next row */
    } else {
      done = TRUE; /* row found! */      
    }
  }
  /* find the column */
  KeySelRow(KEY_ALL_ROWS);  /* power again all rows */
  done = FALSE;
  col_id = 0;
  while (col_id<KEY_MAX_COLS && !done) {  /* search all columns */
    if(column&msk) {  /* key in column? */
      done = TRUE;  /* yes, found it! */
    } else {
      col_id++;   /* select next column */
      msk = msk<<1; /* shift column bit */
    }  
  }
  KeySelRow(KEY_NO_ROWS); /* set it back for next iteration */
  return ((row*(KEY_MAX_COLS+1))+col_id);  /* return scan code */
}

/*!
 * \brief Determines if a key is pressed
 * \return Key scan code, KM_NO_KEY otherwise
 */
static int KeyIsKeyPressed(void) {
  if (KeyGetCol()!=0) {  /* is there a key pressed? */
    return KeyDecode();  /* yes, return scan code */
  } else {
    return KM_NO_KEY;  /* no key pressed */
  }
}

int KM_ScanTask(void) { 
  static int keyOld = KM_NO_KEY;  /* old key scan code */
  int keycode, keyNew;

  keycode = KeyIsKeyPressed();                                   
  if(keycode>=0 && keyOld==KM_NO_KEY) {
    /* start debouncing */
    keyOld = keycode;
    keycode = KM_NO_KEY;
  } else if(keyOld>=0) {
    keyNew = keycode;
    if(keyOld==keyNew) {  /* still same scan code? */
      keycode = keyNew;  /* yes, return that code */
    } else {  /* scan code not stable, restart debouncing */
      keycode= KM_NO_KEY;
      keyOld = KM_NO_KEY;
    }
  }
  return keycode;
}

void KM_Init(void) {
  /* make sure that the Row pins are configured as OUTPUT pins,
   * and the Column pins are configured as INPUT pins.
   * The input pins needs to have PULL-UPs to Vdd.
   */
  KeySelRow(KEY_NO_ROWS);
}

