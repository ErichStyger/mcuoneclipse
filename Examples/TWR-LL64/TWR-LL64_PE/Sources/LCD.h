/*
 * LCD.h
 *
 *  Created on: 07.05.2010
 *      Author: Erich Styger
 */

#ifndef LCD_H_
#define LCD_H_

#include "PE_Types.h"

/* do not change the order of the symbols, as they are used as index into an array */
typedef enum LCD_SymbolKind {
  LCD_SYMBOL_MONDAY,
  LCD_SYMBOL_TUESDAY,
  LCD_SYMBOL_WEDNESDAY,
  LCD_SYMBOL_THURSDAY,
  LCD_SYMBOL_FRIDAY,
  LCD_SYMBOL_SATURDAY,
  LCD_SYMBOL_SUNDAY,
  LCD_SYMBOL_HEAT,
  LCD_SYMBOL_COOL,
  LCD_SYMBOL_BATTERY_OUTLINE,
  LCD_SYMBOL_BATTERY_P1,
  LCD_SYMBOL_BATTERY_P2,
  LCD_SYMBOL_BATTERY_P3,
  LCD_SYMBOL_BATTERY_P4,
  LCD_SYMBOL_AM,
  LCD_SYMBOL_PM,
  LCD_SYMBOL_FLTR,
  LCD_SYMBOL_HOLD,
  LCD_SYMBOL_T1,
  LCD_SYMBOL_COLON,
  LCD_SYMBOL_LAST /* must be last! */
} LCD_SymbolKind;

void LCD_SymbolOn(LCD_SymbolKind sy);

void LCD_SymbolOff(LCD_SymbolKind sy);

void LCD_ShowTime(void);

void LCD_PrintAlphaNum(byte pos, byte ch);

void LCD_Test(void);

#endif /* LCD_H_ */
