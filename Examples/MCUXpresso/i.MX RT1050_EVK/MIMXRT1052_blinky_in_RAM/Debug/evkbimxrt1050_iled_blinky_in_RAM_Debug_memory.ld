/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008 - 2013 Code Red Technologies Ltd, 
 * Copyright 2015, 2018 NXP
 * (c) NXP Semiconductors 2013-2019
 * Generated linker script file for MIMXRT1052xxxxB
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.3.0 [Build 2200] [2018-12-03] on Jan 22, 2019 9:03:48 PM
 */

MEMORY
{
  /* Define each memory region */
  SRAM_ITC (rwx) : ORIGIN = 0x2000, LENGTH = 0x1d000 /* 116K bytes (alias RAM) */  
  SRAM_DTC (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 /* 128K bytes (alias RAM2) */  
  SRAM_OC (rwx) : ORIGIN = 0x20200000, LENGTH = 0x40000 /* 256K bytes (alias RAM3) */  
  BOARD_FLASH (rx) : ORIGIN = 0x60000000, LENGTH = 0x4000000 /* 64M bytes (alias Flash) */  
  BOARD_SDRAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x2000000 /* 32M bytes (alias RAM4) */  
  SRAM_ITC_reserved (rwx) : ORIGIN = 0x0, LENGTH = 0x2000 /* 8K bytes (alias RAM5) */  
}

  /* Define a symbol for the top of each memory region */
  __base_SRAM_ITC = 0x2000  ; /* SRAM_ITC */  
  __base_RAM = 0x2000 ; /* RAM */  
  __top_SRAM_ITC = 0x2000 + 0x1d000 ; /* 116K bytes */  
  __top_RAM = 0x2000 + 0x1d000 ; /* 116K bytes */  
  __base_SRAM_DTC = 0x20000000  ; /* SRAM_DTC */  
  __base_RAM2 = 0x20000000 ; /* RAM2 */  
  __top_SRAM_DTC = 0x20000000 + 0x20000 ; /* 128K bytes */  
  __top_RAM2 = 0x20000000 + 0x20000 ; /* 128K bytes */  
  __base_SRAM_OC = 0x20200000  ; /* SRAM_OC */  
  __base_RAM3 = 0x20200000 ; /* RAM3 */  
  __top_SRAM_OC = 0x20200000 + 0x40000 ; /* 256K bytes */  
  __top_RAM3 = 0x20200000 + 0x40000 ; /* 256K bytes */  
  __base_BOARD_FLASH = 0x60000000  ; /* BOARD_FLASH */  
  __base_Flash = 0x60000000 ; /* Flash */  
  __top_BOARD_FLASH = 0x60000000 + 0x4000000 ; /* 64M bytes */  
  __top_Flash = 0x60000000 + 0x4000000 ; /* 64M bytes */  
  __base_BOARD_SDRAM = 0x80000000  ; /* BOARD_SDRAM */  
  __base_RAM4 = 0x80000000 ; /* RAM4 */  
  __top_BOARD_SDRAM = 0x80000000 + 0x2000000 ; /* 32M bytes */  
  __top_RAM4 = 0x80000000 + 0x2000000 ; /* 32M bytes */  
  __base_SRAM_ITC_reserved = 0x0  ; /* SRAM_ITC_reserved */  
  __base_RAM5 = 0x0 ; /* RAM5 */  
  __top_SRAM_ITC_reserved = 0x0 + 0x2000 ; /* 8K bytes */  
  __top_RAM5 = 0x0 + 0x2000 ; /* 8K bytes */  
