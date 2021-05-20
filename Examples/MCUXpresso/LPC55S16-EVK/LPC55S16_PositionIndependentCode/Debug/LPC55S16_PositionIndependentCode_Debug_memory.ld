/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2021
 * Generated linker script file for LPC55S16
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.3.0 [Build 5222] [2021-01-11] on May 19, 2021 7:17:36 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x38000 /* 224K bytes (alias Flash) */  
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x10000 /* 64K bytes (alias RAM) */  
  USB_RAM (rwx) : ORIGIN = 0x20010000, LENGTH = 0x4000 /* 16K bytes (alias RAM2) */  
  SRAMX (rwx) : ORIGIN = 0x4000000, LENGTH = 0x4000 /* 16K bytes (alias RAM3) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x38000 ; /* 224K bytes */  
  __top_Flash = 0x0 + 0x38000 ; /* 224K bytes */  
  __base_SRAM = 0x20000000  ; /* SRAM */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM = 0x20000000 + 0x10000 ; /* 64K bytes */  
  __top_RAM = 0x20000000 + 0x10000 ; /* 64K bytes */  
  __base_USB_RAM = 0x20010000  ; /* USB_RAM */  
  __base_RAM2 = 0x20010000 ; /* RAM2 */  
  __top_USB_RAM = 0x20010000 + 0x4000 ; /* 16K bytes */  
  __top_RAM2 = 0x20010000 + 0x4000 ; /* 16K bytes */  
  __base_SRAMX = 0x4000000  ; /* SRAMX */  
  __base_RAM3 = 0x4000000 ; /* RAM3 */  
  __top_SRAMX = 0x4000000 + 0x4000 ; /* 16K bytes */  
  __top_RAM3 = 0x4000000 + 0x4000 ; /* 16K bytes */  
