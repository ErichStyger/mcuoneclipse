/* Based on CPU DB MC9S08LL16_64, version 3.00.030 (RegistersPrg V2.32) */
/*
** ###################################################################
**     Filename  : mc9s08ll16.h
**     Processor : MC9S08LL16CLH
**     FileFormat: V2.32
**     DataSheet : MC9S08LL16RM Rev. 4 10/2008
**     Compiler  : CodeWarrior compiler
**     Date/Time : 5.10.2010, 13:53
**     Abstract  :
**         This header implements the mapping of I/O devices.
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
**
**     CPU Registers Revisions:
**               - none
**
**     File-Format-Revisions:
**      - 19.07.2007, V2.18 :
**               - Improved number of blanked lines inside register structures
**      - 06.08.2007, V2.19 :
**               - CPUDB revisions generated ahead of the file-format revisions.
**      - 11.09.2007, V2.20 :
**               - Added comment about initialization of unbonded pins.
**      - 02.01.2008, V2.21 :
**               - Changes have not affected this file (because they are related to another family)
**      - 13.02.2008, V2.22 :
**               - Changes have not affected this file (because they are related to another family)
**      - 20.02.2008, V2.23 :
**               - Changes have not affected this file (because they are related to another family)
**      - 03.07.2008, V2.24 :
**               - Added support for bits with name starting with number (like "1HZ")
**      - 28.11.2008, V2.25 :
**               - StandBy RAM array declaration for ANSI-C added
**      - 1.12.2008, V2.26 :
**               - Duplication of bit (or bit-group) name with register name is not marked as a problem, if register is internal only and it is not displayed in I/O map.
**      - 17.3.2009, V2.27 :
**               - Merged bit-group is not generated, if the name matches with another bit name in the register
**      - 6.4.2009, V2.28 :
**               - Fixed generation of merged bits for bit-groups with a digit at the end, if group-name is defined in CPUDB
**      - 3.8.2009, V2.29 :
**               - If there is just one bits group matching register name, single bits are not generated
**      - 10.9.2009, V2.30 :
**               - Fixed generation of registers arrays.
**      - 15.10.2009, V2.31 :
**               - HCS08 family: Bits and bit-groups are published for 16-bit registers: 8-bit overlay registers are required.
**      - 18.05.2010, V2.32 :
**               - MISRA compliance: U/UL suffixes added to all numbers (_MASK,_BITNUM and addresses)
**
**     Not all general-purpose I/O pins are available on all packages or on all mask sets of a specific
**     derivative device. To avoid extra current drain from floating input pins, the user’s reset
**     initialization routine in the application program must either enable on-chip pull-up devices
**     or change the direction of unconnected pins to outputs so the pins do not float.
** ###################################################################
*/

#ifndef _MC9S08LL16_H
#define _MC9S08LL16_H

/*lint -save  -e950 -esym(960,18.4) -e46 -esym(961,19.7) Disable MISRA rule (1.1,18.4,6.4,19.7) checking. */
/* Types definition */
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;
typedef unsigned long dlong[2];

/* Watchdog reset macro */
#ifndef __RESET_WATCHDOG
#ifdef _lint
  #define __RESET_WATCHDOG()  /* empty */
#else
  #define __RESET_WATCHDOG() {asm sta SRS;}
#endif
#endif /* __RESET_WATCHDOG */

#define REG_BASE 0x0000                /* Base address for the I/O register block */


#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */

/**************** interrupt vector numbers ****************/
#define VectorNumber_Vtod               19U
#define VectorNumber_Vacmp              18U
#define VectorNumber_Vadc               17U
#define VectorNumber_Vkeyboard          16U
#define VectorNumber_Viic               15U
#define VectorNumber_Vscitx             14U
#define VectorNumber_Vscirx             13U
#define VectorNumber_Vscierr            12U
#define VectorNumber_Vspi               11U
#define VectorNumber_Vlcd               10U
#define VectorNumber_Vtpm2ovf           9U
#define VectorNumber_Vtpm2ch1           8U
#define VectorNumber_Vtpm2ch0           7U
#define VectorNumber_Vtpm1ovf           6U
#define VectorNumber_Vtpm1ch1           5U
#define VectorNumber_Vtpm1ch0           4U
#define VectorNumber_Vlvd               3U
#define VectorNumber_Virq               2U
#define VectorNumber_Vswi               1U
#define VectorNumber_Vreset             0U

/**************** interrupt vector table ****************/
#define Vtod                            0xFFD8U
#define Vacmp                           0xFFDAU
#define Vadc                            0xFFDCU
#define Vkeyboard                       0xFFDEU
#define Viic                            0xFFE0U
#define Vscitx                          0xFFE2U
#define Vscirx                          0xFFE4U
#define Vscierr                         0xFFE6U
#define Vspi                            0xFFE8U
#define Vlcd                            0xFFEAU
#define Vtpm2ovf                        0xFFECU
#define Vtpm2ch1                        0xFFEEU
#define Vtpm2ch0                        0xFFF0U
#define Vtpm1ovf                        0xFFF2U
#define Vtpm1ch1                        0xFFF4U
#define Vtpm1ch0                        0xFFF6U
#define Vlvd                            0xFFF8U
#define Virq                            0xFFFAU
#define Vswi                            0xFFFCU
#define Vreset                          0xFFFEU

/**************** registers I/O map ****************/

/*** PTAD - Port A Data Register; 0x00000000 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAD0       :1;                                       /* Port A Data Register Bit 0 */
    byte PTAD1       :1;                                       /* Port A Data Register Bit 1 */
    byte PTAD2       :1;                                       /* Port A Data Register Bit 2 */
    byte PTAD3       :1;                                       /* Port A Data Register Bit 3 */
    byte PTAD4       :1;                                       /* Port A Data Register Bit 4 */
    byte PTAD5       :1;                                       /* Port A Data Register Bit 5 */
    byte PTAD6       :1;                                       /* Port A Data Register Bit 6 */
    byte PTAD7       :1;                                       /* Port A Data Register Bit 7 */
  } Bits;
} PTADSTR;
extern volatile PTADSTR _PTAD @0x00000000;
#define PTAD                            _PTAD.Byte
#define PTAD_PTAD0                      _PTAD.Bits.PTAD0
#define PTAD_PTAD1                      _PTAD.Bits.PTAD1
#define PTAD_PTAD2                      _PTAD.Bits.PTAD2
#define PTAD_PTAD3                      _PTAD.Bits.PTAD3
#define PTAD_PTAD4                      _PTAD.Bits.PTAD4
#define PTAD_PTAD5                      _PTAD.Bits.PTAD5
#define PTAD_PTAD6                      _PTAD.Bits.PTAD6
#define PTAD_PTAD7                      _PTAD.Bits.PTAD7

#define PTAD_PTAD0_MASK                 1U
#define PTAD_PTAD1_MASK                 2U
#define PTAD_PTAD2_MASK                 4U
#define PTAD_PTAD3_MASK                 8U
#define PTAD_PTAD4_MASK                 16U
#define PTAD_PTAD5_MASK                 32U
#define PTAD_PTAD6_MASK                 64U
#define PTAD_PTAD7_MASK                 128U


/*** PTADD - Port A Data Direction Register; 0x00000001 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADD0      :1;                                       /* Data Direction for Port A Bit 0 */
    byte PTADD1      :1;                                       /* Data Direction for Port A Bit 1 */
    byte PTADD2      :1;                                       /* Data Direction for Port A Bit 2 */
    byte PTADD3      :1;                                       /* Data Direction for Port A Bit 3 */
    byte PTADD4      :1;                                       /* Data Direction for Port A Bit 4 */
    byte PTADD5      :1;                                       /* Data Direction for Port A Bit 5 */
    byte PTADD6      :1;                                       /* Data Direction for Port A Bit 6 */
    byte PTADD7      :1;                                       /* Data Direction for Port A Bit 7 */
  } Bits;
} PTADDSTR;
extern volatile PTADDSTR _PTADD @0x00000001;
#define PTADD                           _PTADD.Byte
#define PTADD_PTADD0                    _PTADD.Bits.PTADD0
#define PTADD_PTADD1                    _PTADD.Bits.PTADD1
#define PTADD_PTADD2                    _PTADD.Bits.PTADD2
#define PTADD_PTADD3                    _PTADD.Bits.PTADD3
#define PTADD_PTADD4                    _PTADD.Bits.PTADD4
#define PTADD_PTADD5                    _PTADD.Bits.PTADD5
#define PTADD_PTADD6                    _PTADD.Bits.PTADD6
#define PTADD_PTADD7                    _PTADD.Bits.PTADD7

#define PTADD_PTADD0_MASK               1U
#define PTADD_PTADD1_MASK               2U
#define PTADD_PTADD2_MASK               4U
#define PTADD_PTADD3_MASK               8U
#define PTADD_PTADD4_MASK               16U
#define PTADD_PTADD5_MASK               32U
#define PTADD_PTADD6_MASK               64U
#define PTADD_PTADD7_MASK               128U


/*** PTBD - Port B Data Register; 0x00000002 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBD0       :1;                                       /* Port B Data Register Bit 0 */
    byte PTBD1       :1;                                       /* Port B Data Register Bit 1 */
    byte PTBD2       :1;                                       /* Port B Data Register Bit 2 */
    byte PTBD3       :1;                                       /* Port B Data Register Bit 3 */
    byte PTBD4       :1;                                       /* Port B Data Register Bit 4 */
    byte PTBD5       :1;                                       /* Port B Data Register Bit 5 */
    byte PTBD6       :1;                                       /* Port B Data Register Bit 6 */
    byte PTBD7       :1;                                       /* Port B Data Register Bit 7 */
  } Bits;
} PTBDSTR;
extern volatile PTBDSTR _PTBD @0x00000002;
#define PTBD                            _PTBD.Byte
#define PTBD_PTBD0                      _PTBD.Bits.PTBD0
#define PTBD_PTBD1                      _PTBD.Bits.PTBD1
#define PTBD_PTBD2                      _PTBD.Bits.PTBD2
#define PTBD_PTBD3                      _PTBD.Bits.PTBD3
#define PTBD_PTBD4                      _PTBD.Bits.PTBD4
#define PTBD_PTBD5                      _PTBD.Bits.PTBD5
#define PTBD_PTBD6                      _PTBD.Bits.PTBD6
#define PTBD_PTBD7                      _PTBD.Bits.PTBD7

#define PTBD_PTBD0_MASK                 1U
#define PTBD_PTBD1_MASK                 2U
#define PTBD_PTBD2_MASK                 4U
#define PTBD_PTBD3_MASK                 8U
#define PTBD_PTBD4_MASK                 16U
#define PTBD_PTBD5_MASK                 32U
#define PTBD_PTBD6_MASK                 64U
#define PTBD_PTBD7_MASK                 128U


/*** PTBDD - Port B Data Direction Register; 0x00000003 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDD0      :1;                                       /* Data Direction for Port B Bit 0 */
    byte PTBDD1      :1;                                       /* Data Direction for Port B Bit 1 */
    byte PTBDD2      :1;                                       /* Data Direction for Port B Bit 2 */
    byte PTBDD3      :1;                                       /* Data Direction for Port B Bit 3 */
    byte PTBDD4      :1;                                       /* Data Direction for Port B Bit 4 */
    byte PTBDD5      :1;                                       /* Data Direction for Port B Bit 5 */
    byte PTBDD6      :1;                                       /* Data Direction for Port B Bit 6 */
    byte PTBDD7      :1;                                       /* Data Direction for Port B Bit 7 */
  } Bits;
} PTBDDSTR;
extern volatile PTBDDSTR _PTBDD @0x00000003;
#define PTBDD                           _PTBDD.Byte
#define PTBDD_PTBDD0                    _PTBDD.Bits.PTBDD0
#define PTBDD_PTBDD1                    _PTBDD.Bits.PTBDD1
#define PTBDD_PTBDD2                    _PTBDD.Bits.PTBDD2
#define PTBDD_PTBDD3                    _PTBDD.Bits.PTBDD3
#define PTBDD_PTBDD4                    _PTBDD.Bits.PTBDD4
#define PTBDD_PTBDD5                    _PTBDD.Bits.PTBDD5
#define PTBDD_PTBDD6                    _PTBDD.Bits.PTBDD6
#define PTBDD_PTBDD7                    _PTBDD.Bits.PTBDD7

#define PTBDD_PTBDD0_MASK               1U
#define PTBDD_PTBDD1_MASK               2U
#define PTBDD_PTBDD2_MASK               4U
#define PTBDD_PTBDD3_MASK               8U
#define PTBDD_PTBDD4_MASK               16U
#define PTBDD_PTBDD5_MASK               32U
#define PTBDD_PTBDD6_MASK               64U
#define PTBDD_PTBDD7_MASK               128U


/*** PTCD - Port C Data Register; 0x00000004 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCD0       :1;                                       /* Port C Data Register Bit 0 */
    byte PTCD1       :1;                                       /* Port C Data Register Bit 1 */
    byte PTCD2       :1;                                       /* Port C Data Register Bit 2 */
    byte PTCD3       :1;                                       /* Port C Data Register Bit 3 */
    byte PTCD4       :1;                                       /* Port C Data Register Bit 4 */
    byte PTCD5       :1;                                       /* Port C Data Register Bit 5 */
    byte PTCD6       :1;                                       /* Port C Data Register Bit 6 */
    byte PTCD7       :1;                                       /* Port C Data Register Bit 7 */
  } Bits;
} PTCDSTR;
extern volatile PTCDSTR _PTCD @0x00000004;
#define PTCD                            _PTCD.Byte
#define PTCD_PTCD0                      _PTCD.Bits.PTCD0
#define PTCD_PTCD1                      _PTCD.Bits.PTCD1
#define PTCD_PTCD2                      _PTCD.Bits.PTCD2
#define PTCD_PTCD3                      _PTCD.Bits.PTCD3
#define PTCD_PTCD4                      _PTCD.Bits.PTCD4
#define PTCD_PTCD5                      _PTCD.Bits.PTCD5
#define PTCD_PTCD6                      _PTCD.Bits.PTCD6
#define PTCD_PTCD7                      _PTCD.Bits.PTCD7

#define PTCD_PTCD0_MASK                 1U
#define PTCD_PTCD1_MASK                 2U
#define PTCD_PTCD2_MASK                 4U
#define PTCD_PTCD3_MASK                 8U
#define PTCD_PTCD4_MASK                 16U
#define PTCD_PTCD5_MASK                 32U
#define PTCD_PTCD6_MASK                 64U
#define PTCD_PTCD7_MASK                 128U


/*** PTCDD - Port C Data Direction Register; 0x00000005 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDD0      :1;                                       /* Data Direction for Port C Bit 0 */
    byte PTCDD1      :1;                                       /* Data Direction for Port C Bit 1 */
    byte PTCDD2      :1;                                       /* Data Direction for Port C Bit 2 */
    byte PTCDD3      :1;                                       /* Data Direction for Port C Bit 3 */
    byte PTCDD4      :1;                                       /* Data Direction for Port C Bit 4 */
    byte PTCDD5      :1;                                       /* Data Direction for Port C Bit 5 */
    byte PTCDD6      :1;                                       /* Data Direction for Port C Bit 6 */
    byte PTCDD7      :1;                                       /* Data Direction for Port C Bit 7 */
  } Bits;
} PTCDDSTR;
extern volatile PTCDDSTR _PTCDD @0x00000005;
#define PTCDD                           _PTCDD.Byte
#define PTCDD_PTCDD0                    _PTCDD.Bits.PTCDD0
#define PTCDD_PTCDD1                    _PTCDD.Bits.PTCDD1
#define PTCDD_PTCDD2                    _PTCDD.Bits.PTCDD2
#define PTCDD_PTCDD3                    _PTCDD.Bits.PTCDD3
#define PTCDD_PTCDD4                    _PTCDD.Bits.PTCDD4
#define PTCDD_PTCDD5                    _PTCDD.Bits.PTCDD5
#define PTCDD_PTCDD6                    _PTCDD.Bits.PTCDD6
#define PTCDD_PTCDD7                    _PTCDD.Bits.PTCDD7

#define PTCDD_PTCDD0_MASK               1U
#define PTCDD_PTCDD1_MASK               2U
#define PTCDD_PTCDD2_MASK               4U
#define PTCDD_PTCDD3_MASK               8U
#define PTCDD_PTCDD4_MASK               16U
#define PTCDD_PTCDD5_MASK               32U
#define PTCDD_PTCDD6_MASK               64U
#define PTCDD_PTCDD7_MASK               128U


/*** PTDD - Port D Data Register; 0x00000006 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDD0       :1;                                       /* Port D Data Register Bit 0 */
    byte PTDD1       :1;                                       /* Port D Data Register Bit 1 */
    byte PTDD2       :1;                                       /* Port D Data Register Bit 2 */
    byte PTDD3       :1;                                       /* Port D Data Register Bit 3 */
    byte PTDD4       :1;                                       /* Port D Data Register Bit 4 */
    byte PTDD5       :1;                                       /* Port D Data Register Bit 5 */
    byte PTDD6       :1;                                       /* Port D Data Register Bit 6 */
    byte PTDD7       :1;                                       /* Port D Data Register Bit 7 */
  } Bits;
} PTDDSTR;
extern volatile PTDDSTR _PTDD @0x00000006;
#define PTDD                            _PTDD.Byte
#define PTDD_PTDD0                      _PTDD.Bits.PTDD0
#define PTDD_PTDD1                      _PTDD.Bits.PTDD1
#define PTDD_PTDD2                      _PTDD.Bits.PTDD2
#define PTDD_PTDD3                      _PTDD.Bits.PTDD3
#define PTDD_PTDD4                      _PTDD.Bits.PTDD4
#define PTDD_PTDD5                      _PTDD.Bits.PTDD5
#define PTDD_PTDD6                      _PTDD.Bits.PTDD6
#define PTDD_PTDD7                      _PTDD.Bits.PTDD7

#define PTDD_PTDD0_MASK                 1U
#define PTDD_PTDD1_MASK                 2U
#define PTDD_PTDD2_MASK                 4U
#define PTDD_PTDD3_MASK                 8U
#define PTDD_PTDD4_MASK                 16U
#define PTDD_PTDD5_MASK                 32U
#define PTDD_PTDD6_MASK                 64U
#define PTDD_PTDD7_MASK                 128U


/*** PTDDD - Port D Data Direction Register; 0x00000007 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDD0      :1;                                       /* Data Direction for Port D Bit 0 */
    byte PTDDD1      :1;                                       /* Data Direction for Port D Bit 1 */
    byte PTDDD2      :1;                                       /* Data Direction for Port D Bit 2 */
    byte PTDDD3      :1;                                       /* Data Direction for Port D Bit 3 */
    byte PTDDD4      :1;                                       /* Data Direction for Port D Bit 4 */
    byte PTDDD5      :1;                                       /* Data Direction for Port D Bit 5 */
    byte PTDDD6      :1;                                       /* Data Direction for Port D Bit 6 */
    byte PTDDD7      :1;                                       /* Data Direction for Port D Bit 7 */
  } Bits;
} PTDDDSTR;
extern volatile PTDDDSTR _PTDDD @0x00000007;
#define PTDDD                           _PTDDD.Byte
#define PTDDD_PTDDD0                    _PTDDD.Bits.PTDDD0
#define PTDDD_PTDDD1                    _PTDDD.Bits.PTDDD1
#define PTDDD_PTDDD2                    _PTDDD.Bits.PTDDD2
#define PTDDD_PTDDD3                    _PTDDD.Bits.PTDDD3
#define PTDDD_PTDDD4                    _PTDDD.Bits.PTDDD4
#define PTDDD_PTDDD5                    _PTDDD.Bits.PTDDD5
#define PTDDD_PTDDD6                    _PTDDD.Bits.PTDDD6
#define PTDDD_PTDDD7                    _PTDDD.Bits.PTDDD7

#define PTDDD_PTDDD0_MASK               1U
#define PTDDD_PTDDD1_MASK               2U
#define PTDDD_PTDDD2_MASK               4U
#define PTDDD_PTDDD3_MASK               8U
#define PTDDD_PTDDD4_MASK               16U
#define PTDDD_PTDDD5_MASK               32U
#define PTDDD_PTDDD6_MASK               64U
#define PTDDD_PTDDD7_MASK               128U


/*** PTED - Port E Data Register; 0x00000008 ***/
typedef union {
  byte Byte;
  struct {
    byte PTED0       :1;                                       /* Port E Data Register Bit 0 */
    byte PTED1       :1;                                       /* Port E Data Register Bit 1 */
    byte PTED2       :1;                                       /* Port E Data Register Bit 2 */
    byte PTED3       :1;                                       /* Port E Data Register Bit 3 */
    byte PTED4       :1;                                       /* Port E Data Register Bit 4 */
    byte PTED5       :1;                                       /* Port E Data Register Bit 5 */
    byte PTED6       :1;                                       /* Port E Data Register Bit 6 */
    byte PTED7       :1;                                       /* Port E Data Register Bit 7 */
  } Bits;
} PTEDSTR;
extern volatile PTEDSTR _PTED @0x00000008;
#define PTED                            _PTED.Byte
#define PTED_PTED0                      _PTED.Bits.PTED0
#define PTED_PTED1                      _PTED.Bits.PTED1
#define PTED_PTED2                      _PTED.Bits.PTED2
#define PTED_PTED3                      _PTED.Bits.PTED3
#define PTED_PTED4                      _PTED.Bits.PTED4
#define PTED_PTED5                      _PTED.Bits.PTED5
#define PTED_PTED6                      _PTED.Bits.PTED6
#define PTED_PTED7                      _PTED.Bits.PTED7

#define PTED_PTED0_MASK                 1U
#define PTED_PTED1_MASK                 2U
#define PTED_PTED2_MASK                 4U
#define PTED_PTED3_MASK                 8U
#define PTED_PTED4_MASK                 16U
#define PTED_PTED5_MASK                 32U
#define PTED_PTED6_MASK                 64U
#define PTED_PTED7_MASK                 128U


/*** PTEDD - Port E Data Direction Register; 0x00000009 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDD0      :1;                                       /* Data Direction for Port E Bit 0 */
    byte PTEDD1      :1;                                       /* Data Direction for Port E Bit 1 */
    byte PTEDD2      :1;                                       /* Data Direction for Port E Bit 2 */
    byte PTEDD3      :1;                                       /* Data Direction for Port E Bit 3 */
    byte PTEDD4      :1;                                       /* Data Direction for Port E Bit 4 */
    byte PTEDD5      :1;                                       /* Data Direction for Port E Bit 5 */
    byte PTEDD6      :1;                                       /* Data Direction for Port E Bit 6 */
    byte PTEDD7      :1;                                       /* Data Direction for Port E Bit 7 */
  } Bits;
} PTEDDSTR;
extern volatile PTEDDSTR _PTEDD @0x00000009;
#define PTEDD                           _PTEDD.Byte
#define PTEDD_PTEDD0                    _PTEDD.Bits.PTEDD0
#define PTEDD_PTEDD1                    _PTEDD.Bits.PTEDD1
#define PTEDD_PTEDD2                    _PTEDD.Bits.PTEDD2
#define PTEDD_PTEDD3                    _PTEDD.Bits.PTEDD3
#define PTEDD_PTEDD4                    _PTEDD.Bits.PTEDD4
#define PTEDD_PTEDD5                    _PTEDD.Bits.PTEDD5
#define PTEDD_PTEDD6                    _PTEDD.Bits.PTEDD6
#define PTEDD_PTEDD7                    _PTEDD.Bits.PTEDD7

#define PTEDD_PTEDD0_MASK               1U
#define PTEDD_PTEDD1_MASK               2U
#define PTEDD_PTEDD2_MASK               4U
#define PTEDD_PTEDD3_MASK               8U
#define PTEDD_PTEDD4_MASK               16U
#define PTEDD_PTEDD5_MASK               32U
#define PTEDD_PTEDD6_MASK               64U
#define PTEDD_PTEDD7_MASK               128U


/*** KBISC - KBI Status and Control Register; 0x0000000C ***/
typedef union {
  byte Byte;
  struct {
    byte KBIMOD      :1;                                       /* Keyboard Detection Mode */
    byte KBIE        :1;                                       /* Keyboard Interrupt Enable */
    byte KBACK       :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KBF         :1;                                       /* Keyboard Interrupt Flag */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} KBISCSTR;
extern volatile KBISCSTR _KBISC @0x0000000C;
#define KBISC                           _KBISC.Byte
#define KBISC_KBIMOD                    _KBISC.Bits.KBIMOD
#define KBISC_KBIE                      _KBISC.Bits.KBIE
#define KBISC_KBACK                     _KBISC.Bits.KBACK
#define KBISC_KBF                       _KBISC.Bits.KBF

#define KBISC_KBIMOD_MASK               1U
#define KBISC_KBIE_MASK                 2U
#define KBISC_KBACK_MASK                4U
#define KBISC_KBF_MASK                  8U


/*** KBIPE - KBI Pin Enable Register; 0x0000000D ***/
typedef union {
  byte Byte;
  struct {
    byte KBIPE0      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 0 */
    byte KBIPE1      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 1 */
    byte KBIPE2      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 2 */
    byte KBIPE3      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 3 */
    byte KBIPE4      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 4 */
    byte KBIPE5      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 5 */
    byte KBIPE6      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 6 */
    byte KBIPE7      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 7 */
  } Bits;
} KBIPESTR;
extern volatile KBIPESTR _KBIPE @0x0000000D;
#define KBIPE                           _KBIPE.Byte
#define KBIPE_KBIPE0                    _KBIPE.Bits.KBIPE0
#define KBIPE_KBIPE1                    _KBIPE.Bits.KBIPE1
#define KBIPE_KBIPE2                    _KBIPE.Bits.KBIPE2
#define KBIPE_KBIPE3                    _KBIPE.Bits.KBIPE3
#define KBIPE_KBIPE4                    _KBIPE.Bits.KBIPE4
#define KBIPE_KBIPE5                    _KBIPE.Bits.KBIPE5
#define KBIPE_KBIPE6                    _KBIPE.Bits.KBIPE6
#define KBIPE_KBIPE7                    _KBIPE.Bits.KBIPE7

#define KBIPE_KBIPE0_MASK               1U
#define KBIPE_KBIPE1_MASK               2U
#define KBIPE_KBIPE2_MASK               4U
#define KBIPE_KBIPE3_MASK               8U
#define KBIPE_KBIPE4_MASK               16U
#define KBIPE_KBIPE5_MASK               32U
#define KBIPE_KBIPE6_MASK               64U
#define KBIPE_KBIPE7_MASK               128U


/*** KBIES - KBI Edge Select Register; 0x0000000E ***/
typedef union {
  byte Byte;
  struct {
    byte KBEDG0      :1;                                       /* Keyboard Edge Select Bit 0 */
    byte KBEDG1      :1;                                       /* Keyboard Edge Select Bit 1 */
    byte KBEDG2      :1;                                       /* Keyboard Edge Select Bit 2 */
    byte KBEDG3      :1;                                       /* Keyboard Edge Select Bit 3 */
    byte KBEDG4      :1;                                       /* Keyboard Edge Select Bit 4 */
    byte KBEDG5      :1;                                       /* Keyboard Edge Select Bit 5 */
    byte KBEDG6      :1;                                       /* Keyboard Edge Select Bit 6 */
    byte KBEDG7      :1;                                       /* Keyboard Edge Select Bit 7 */
  } Bits;
} KBIESSTR;
extern volatile KBIESSTR _KBIES @0x0000000E;
#define KBIES                           _KBIES.Byte
#define KBIES_KBEDG0                    _KBIES.Bits.KBEDG0
#define KBIES_KBEDG1                    _KBIES.Bits.KBEDG1
#define KBIES_KBEDG2                    _KBIES.Bits.KBEDG2
#define KBIES_KBEDG3                    _KBIES.Bits.KBEDG3
#define KBIES_KBEDG4                    _KBIES.Bits.KBEDG4
#define KBIES_KBEDG5                    _KBIES.Bits.KBEDG5
#define KBIES_KBEDG6                    _KBIES.Bits.KBEDG6
#define KBIES_KBEDG7                    _KBIES.Bits.KBEDG7

#define KBIES_KBEDG0_MASK               1U
#define KBIES_KBEDG1_MASK               2U
#define KBIES_KBEDG2_MASK               4U
#define KBIES_KBEDG3_MASK               8U
#define KBIES_KBEDG4_MASK               16U
#define KBIES_KBEDG5_MASK               32U
#define KBIES_KBEDG6_MASK               64U
#define KBIES_KBEDG7_MASK               128U


/*** IRQSC - Interrupt request status and control register; 0x0000000F ***/
typedef union {
  byte Byte;
  struct {
    byte IRQMOD      :1;                                       /* IRQ Detection Mode */
    byte IRQIE       :1;                                       /* IRQ Interrupt Enable */
    byte IRQACK      :1;                                       /* IRQ Acknowledge */
    byte IRQF        :1;                                       /* IRQ Flag */
    byte IRQPE       :1;                                       /* IRQ Pin Enable */
    byte IRQEDG      :1;                                       /* IRQ Edge Select */
    byte IRQPDD      :1;                                       /* IRQ Pull Device Disable */
    byte             :1; 
  } Bits;
} IRQSCSTR;
extern volatile IRQSCSTR _IRQSC @0x0000000F;
#define IRQSC                           _IRQSC.Byte
#define IRQSC_IRQMOD                    _IRQSC.Bits.IRQMOD
#define IRQSC_IRQIE                     _IRQSC.Bits.IRQIE
#define IRQSC_IRQACK                    _IRQSC.Bits.IRQACK
#define IRQSC_IRQF                      _IRQSC.Bits.IRQF
#define IRQSC_IRQPE                     _IRQSC.Bits.IRQPE
#define IRQSC_IRQEDG                    _IRQSC.Bits.IRQEDG
#define IRQSC_IRQPDD                    _IRQSC.Bits.IRQPDD

#define IRQSC_IRQMOD_MASK               1U
#define IRQSC_IRQIE_MASK                2U
#define IRQSC_IRQACK_MASK               4U
#define IRQSC_IRQF_MASK                 8U
#define IRQSC_IRQPE_MASK                16U
#define IRQSC_IRQEDG_MASK               32U
#define IRQSC_IRQPDD_MASK               64U


/*** ADCSC1 - Status and Control Register 1; 0x00000010 ***/
typedef union {
  byte Byte;
  struct {
    byte ADCH0       :1;                                       /* Input Channel Select Bit 0 */
    byte ADCH1       :1;                                       /* Input Channel Select Bit 1 */
    byte ADCH2       :1;                                       /* Input Channel Select Bit 2 */
    byte ADCH3       :1;                                       /* Input Channel Select Bit 3 */
    byte ADCH4       :1;                                       /* Input Channel Select Bit 4 */
    byte ADCO        :1;                                       /* Continuous Conversion Enable - ADCO is used to enable continuous conversions */
    byte AIEN        :1;                                       /* Interrupt Enable - AIEN is used to enable conversion complete interrupts. When COCO becomes set while AIEN is high, an interrupt is asserted */
    byte COCO        :1;                                       /* Conversion Complete Flag */
  } Bits;
  struct {
    byte grpADCH :5;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ADCSC1STR;
extern volatile ADCSC1STR _ADCSC1 @0x00000010;
#define ADCSC1                          _ADCSC1.Byte
#define ADCSC1_ADCH0                    _ADCSC1.Bits.ADCH0
#define ADCSC1_ADCH1                    _ADCSC1.Bits.ADCH1
#define ADCSC1_ADCH2                    _ADCSC1.Bits.ADCH2
#define ADCSC1_ADCH3                    _ADCSC1.Bits.ADCH3
#define ADCSC1_ADCH4                    _ADCSC1.Bits.ADCH4
#define ADCSC1_ADCO                     _ADCSC1.Bits.ADCO
#define ADCSC1_AIEN                     _ADCSC1.Bits.AIEN
#define ADCSC1_COCO                     _ADCSC1.Bits.COCO
#define ADCSC1_ADCH                     _ADCSC1.MergedBits.grpADCH

#define ADCSC1_ADCH0_MASK               1U
#define ADCSC1_ADCH1_MASK               2U
#define ADCSC1_ADCH2_MASK               4U
#define ADCSC1_ADCH3_MASK               8U
#define ADCSC1_ADCH4_MASK               16U
#define ADCSC1_ADCO_MASK                32U
#define ADCSC1_AIEN_MASK                64U
#define ADCSC1_COCO_MASK                128U
#define ADCSC1_ADCH_MASK                31U
#define ADCSC1_ADCH_BITNUM              0U


/*** ADCSC2 - Status and Control Register 2; 0x00000011 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ACFGT       :1;                                       /* Compare Function Greater Than Enable */
    byte ACFE        :1;                                       /* Compare Function Enable - ACFE is used to enable the compare function */
    byte ADTRG       :1;                                       /* Conversion Trigger Select-ADTRG is used to select the type of trigger to be used for initiating a conversion */
    byte ADACT       :1;                                       /* Conversion Active - ADACT indicates that a conversion is in progress. ADACT is set when a conversion is initiated and cleared when a conversion is completed or aborted */
  } Bits;
} ADCSC2STR;
extern volatile ADCSC2STR _ADCSC2 @0x00000011;
#define ADCSC2                          _ADCSC2.Byte
#define ADCSC2_ACFGT                    _ADCSC2.Bits.ACFGT
#define ADCSC2_ACFE                     _ADCSC2.Bits.ACFE
#define ADCSC2_ADTRG                    _ADCSC2.Bits.ADTRG
#define ADCSC2_ADACT                    _ADCSC2.Bits.ADACT

#define ADCSC2_ACFGT_MASK               16U
#define ADCSC2_ACFE_MASK                32U
#define ADCSC2_ADTRG_MASK               64U
#define ADCSC2_ADACT_MASK               128U


/*** ADCR - Data Result Register; 0x00000012 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADCRH - Data Result High Register; 0x00000012 ***/
    union {
      byte Byte;
      struct {
        byte ADR8        :1;                                       /* ADC Result Data Bit 8 */
        byte ADR9        :1;                                       /* ADC Result Data Bit 9 */
        byte ADR10       :1;                                       /* ADC Result Data Bit 10 */
        byte ADR11       :1;                                       /* ADC Result Data Bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpADR_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADCRHSTR;
    #define ADCRH                       _ADCR.Overlap_STR.ADCRHSTR.Byte
    #define ADCRH_ADR8                  _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR8
    #define ADCRH_ADR9                  _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR9
    #define ADCRH_ADR10                 _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR10
    #define ADCRH_ADR11                 _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR11
    #define ADCRH_ADR_8                 _ADCR.Overlap_STR.ADCRHSTR.MergedBits.grpADR_8
    #define ADCRH_ADR                   ADCRH_ADR_8
    
    #define ADCRH_ADR8_MASK             1U
    #define ADCRH_ADR9_MASK             2U
    #define ADCRH_ADR10_MASK            4U
    #define ADCRH_ADR11_MASK            8U
    #define ADCRH_ADR_8_MASK            15U
    #define ADCRH_ADR_8_BITNUM          0U
    

    /*** ADCRL - Data Result Low Register; 0x00000013 ***/
    union {
      byte Byte;
      struct {
        byte ADR0        :1;                                       /* ADC Result Data Bit 0 */
        byte ADR1        :1;                                       /* ADC Result Data Bit 1 */
        byte ADR2        :1;                                       /* ADC Result Data Bit 2 */
        byte ADR3        :1;                                       /* ADC Result Data Bit 3 */
        byte ADR4        :1;                                       /* ADC Result Data Bit 4 */
        byte ADR5        :1;                                       /* ADC Result Data Bit 5 */
        byte ADR6        :1;                                       /* ADC Result Data Bit 6 */
        byte ADR7        :1;                                       /* ADC Result Data Bit 7 */
      } Bits;
    } ADCRLSTR;
    #define ADCRL                       _ADCR.Overlap_STR.ADCRLSTR.Byte
    #define ADCRL_ADR0                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR0
    #define ADCRL_ADR1                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR1
    #define ADCRL_ADR2                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR2
    #define ADCRL_ADR3                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR3
    #define ADCRL_ADR4                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR4
    #define ADCRL_ADR5                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR5
    #define ADCRL_ADR6                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR6
    #define ADCRL_ADR7                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR7
    
    #define ADCRL_ADR0_MASK             1U
    #define ADCRL_ADR1_MASK             2U
    #define ADCRL_ADR2_MASK             4U
    #define ADCRL_ADR3_MASK             8U
    #define ADCRL_ADR4_MASK             16U
    #define ADCRL_ADR5_MASK             32U
    #define ADCRL_ADR6_MASK             64U
    #define ADCRL_ADR7_MASK             128U
    
  } Overlap_STR;

} ADCRSTR;
extern volatile ADCRSTR _ADCR @0x00000012;
#define ADCR                            _ADCR.Word


/*** ADCCV - Compare Value Register; 0x00000014 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADCCVH - Compare Value High Register; 0x00000014 ***/
    union {
      byte Byte;
      struct {
        byte ADCV8       :1;                                       /* Compare Function Value 8 */
        byte ADCV9       :1;                                       /* Compare Function Value 9 */
        byte ADCV10      :1;                                       /* Compare Function Value 10 */
        byte ADCV11      :1;                                       /* Compare Function Value 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpADCV_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADCCVHSTR;
    #define ADCCVH                      _ADCCV.Overlap_STR.ADCCVHSTR.Byte
    #define ADCCVH_ADCV8                _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV8
    #define ADCCVH_ADCV9                _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV9
    #define ADCCVH_ADCV10               _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV10
    #define ADCCVH_ADCV11               _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV11
    #define ADCCVH_ADCV_8               _ADCCV.Overlap_STR.ADCCVHSTR.MergedBits.grpADCV_8
    #define ADCCVH_ADCV                 ADCCVH_ADCV_8
    
    #define ADCCVH_ADCV8_MASK           1U
    #define ADCCVH_ADCV9_MASK           2U
    #define ADCCVH_ADCV10_MASK          4U
    #define ADCCVH_ADCV11_MASK          8U
    #define ADCCVH_ADCV_8_MASK          15U
    #define ADCCVH_ADCV_8_BITNUM        0U
    

    /*** ADCCVL - Compare Value Low Register; 0x00000015 ***/
    union {
      byte Byte;
      struct {
        byte ADCV0       :1;                                       /* Compare Function Value 0 */
        byte ADCV1       :1;                                       /* Compare Function Value 1 */
        byte ADCV2       :1;                                       /* Compare Function Value 2 */
        byte ADCV3       :1;                                       /* Compare Function Value 3 */
        byte ADCV4       :1;                                       /* Compare Function Value 4 */
        byte ADCV5       :1;                                       /* Compare Function Value 5 */
        byte ADCV6       :1;                                       /* Compare Function Value 6 */
        byte ADCV7       :1;                                       /* Compare Function Value 7 */
      } Bits;
    } ADCCVLSTR;
    #define ADCCVL                      _ADCCV.Overlap_STR.ADCCVLSTR.Byte
    #define ADCCVL_ADCV0                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV0
    #define ADCCVL_ADCV1                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV1
    #define ADCCVL_ADCV2                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV2
    #define ADCCVL_ADCV3                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV3
    #define ADCCVL_ADCV4                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV4
    #define ADCCVL_ADCV5                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV5
    #define ADCCVL_ADCV6                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV6
    #define ADCCVL_ADCV7                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV7
    
    #define ADCCVL_ADCV0_MASK           1U
    #define ADCCVL_ADCV1_MASK           2U
    #define ADCCVL_ADCV2_MASK           4U
    #define ADCCVL_ADCV3_MASK           8U
    #define ADCCVL_ADCV4_MASK           16U
    #define ADCCVL_ADCV5_MASK           32U
    #define ADCCVL_ADCV6_MASK           64U
    #define ADCCVL_ADCV7_MASK           128U
    
  } Overlap_STR;

} ADCCVSTR;
extern volatile ADCCVSTR _ADCCV @0x00000014;
#define ADCCV                           _ADCCV.Word


/*** ADCCFG - Configuration Register; 0x00000016 ***/
typedef union {
  byte Byte;
  struct {
    byte ADICLK0     :1;                                       /* Input Clock Select Bit 0 */
    byte ADICLK1     :1;                                       /* Input Clock Select Bit 1 */
    byte MODE0       :1;                                       /* Conversion Mode Selection Bit 0 */
    byte MODE1       :1;                                       /* Conversion Mode Selection Bit 1 */
    byte ADLSMP      :1;                                       /* Long Sample Time Configuration */
    byte ADIV0       :1;                                       /* Clock Divide Select Bit 0 */
    byte ADIV1       :1;                                       /* Clock Divide Select Bit 1 */
    byte ADLPC       :1;                                       /* Low Power Configuration */
  } Bits;
  struct {
    byte grpADICLK :2;
    byte grpMODE :2;
    byte         :1;
    byte grpADIV :2;
    byte         :1;
  } MergedBits;
} ADCCFGSTR;
extern volatile ADCCFGSTR _ADCCFG @0x00000016;
#define ADCCFG                          _ADCCFG.Byte
#define ADCCFG_ADICLK0                  _ADCCFG.Bits.ADICLK0
#define ADCCFG_ADICLK1                  _ADCCFG.Bits.ADICLK1
#define ADCCFG_MODE0                    _ADCCFG.Bits.MODE0
#define ADCCFG_MODE1                    _ADCCFG.Bits.MODE1
#define ADCCFG_ADLSMP                   _ADCCFG.Bits.ADLSMP
#define ADCCFG_ADIV0                    _ADCCFG.Bits.ADIV0
#define ADCCFG_ADIV1                    _ADCCFG.Bits.ADIV1
#define ADCCFG_ADLPC                    _ADCCFG.Bits.ADLPC
#define ADCCFG_ADICLK                   _ADCCFG.MergedBits.grpADICLK
#define ADCCFG_MODE                     _ADCCFG.MergedBits.grpMODE
#define ADCCFG_ADIV                     _ADCCFG.MergedBits.grpADIV

#define ADCCFG_ADICLK0_MASK             1U
#define ADCCFG_ADICLK1_MASK             2U
#define ADCCFG_MODE0_MASK               4U
#define ADCCFG_MODE1_MASK               8U
#define ADCCFG_ADLSMP_MASK              16U
#define ADCCFG_ADIV0_MASK               32U
#define ADCCFG_ADIV1_MASK               64U
#define ADCCFG_ADLPC_MASK               128U
#define ADCCFG_ADICLK_MASK              3U
#define ADCCFG_ADICLK_BITNUM            0U
#define ADCCFG_MODE_MASK                12U
#define ADCCFG_MODE_BITNUM              2U
#define ADCCFG_ADIV_MASK                96U
#define ADCCFG_ADIV_BITNUM              5U


/*** APCTL1 - Pin Control 1 Register; 0x00000017 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC0       :1;                                       /* ADC Pin Control 0 - ADPC0 is used to control the pin associated with channel AD0 */
    byte ADPC1       :1;                                       /* ADC Pin Control 1 - ADPC1 is used to control the pin associated with channel AD1 */
    byte ADPC2       :1;                                       /* ADC Pin Control 2 - ADPC2 is used to control the pin associated with channel AD2 */
    byte ADPC3       :1;                                       /* ADC Pin Control 3 - ADPC3 is used to control the pin associated with channel AD3 */
    byte ADPC4       :1;                                       /* ADC Pin Control 4 - ADPC4 is used to control the pin associated with channel AD4 */
    byte ADPC5       :1;                                       /* ADC Pin Control 5 - ADPC5 is used to control the pin associated with channel AD5 */
    byte ADPC6       :1;                                       /* ADC Pin Control 6 - ADPC6 is used to control the pin associated with channel AD6 */
    byte ADPC7       :1;                                       /* ADC Pin Control 7 - ADPC7 is used to control the pin associated with channel AD7 */
  } Bits;
} APCTL1STR;
extern volatile APCTL1STR _APCTL1 @0x00000017;
#define APCTL1                          _APCTL1.Byte
#define APCTL1_ADPC0                    _APCTL1.Bits.ADPC0
#define APCTL1_ADPC1                    _APCTL1.Bits.ADPC1
#define APCTL1_ADPC2                    _APCTL1.Bits.ADPC2
#define APCTL1_ADPC3                    _APCTL1.Bits.ADPC3
#define APCTL1_ADPC4                    _APCTL1.Bits.ADPC4
#define APCTL1_ADPC5                    _APCTL1.Bits.ADPC5
#define APCTL1_ADPC6                    _APCTL1.Bits.ADPC6
#define APCTL1_ADPC7                    _APCTL1.Bits.ADPC7

#define APCTL1_ADPC0_MASK               1U
#define APCTL1_ADPC1_MASK               2U
#define APCTL1_ADPC2_MASK               4U
#define APCTL1_ADPC3_MASK               8U
#define APCTL1_ADPC4_MASK               16U
#define APCTL1_ADPC5_MASK               32U
#define APCTL1_ADPC6_MASK               64U
#define APCTL1_ADPC7_MASK               128U


/*** LCDC0 - LCD Control Register 0; 0x00000018 ***/
typedef union {
  byte Byte;
  struct {
    byte DUTY0       :1;                                       /* LCD Duty Select Bit 0 */
    byte DUTY1       :1;                                       /* LCD Duty Select Bit 1 */
    byte DUTY2       :1;                                       /* LCD Duty Select Bit 2 */
    byte LCLK0       :1;                                       /* LCD Clock Prescaler Bit 0 */
    byte LCLK1       :1;                                       /* LCD Clock Prescaler Bit 1 */
    byte LCLK2       :1;                                       /* LCD Clock Prescaler Bit 2 */
    byte SOURCE      :1;                                       /* LCD Clock Source Select */
    byte LCDEN       :1;                                       /* LCD Driver Enable */
  } Bits;
  struct {
    byte grpDUTY :3;
    byte grpLCLK :3;
    byte         :1;
    byte         :1;
  } MergedBits;
} LCDC0STR;
extern volatile LCDC0STR _LCDC0 @0x00000018;
#define LCDC0                           _LCDC0.Byte
#define LCDC0_DUTY0                     _LCDC0.Bits.DUTY0
#define LCDC0_DUTY1                     _LCDC0.Bits.DUTY1
#define LCDC0_DUTY2                     _LCDC0.Bits.DUTY2
#define LCDC0_LCLK0                     _LCDC0.Bits.LCLK0
#define LCDC0_LCLK1                     _LCDC0.Bits.LCLK1
#define LCDC0_LCLK2                     _LCDC0.Bits.LCLK2
#define LCDC0_SOURCE                    _LCDC0.Bits.SOURCE
#define LCDC0_LCDEN                     _LCDC0.Bits.LCDEN
/* LCDC_ARR: Access 2 LCDCx registers in an array */
#define LCDC_ARR                        ((volatile byte * __far) &LCDC0)
#define LCDC0_DUTY                      _LCDC0.MergedBits.grpDUTY
#define LCDC0_LCLK                      _LCDC0.MergedBits.grpLCLK

#define LCDC0_DUTY0_MASK                1U
#define LCDC0_DUTY1_MASK                2U
#define LCDC0_DUTY2_MASK                4U
#define LCDC0_LCLK0_MASK                8U
#define LCDC0_LCLK1_MASK                16U
#define LCDC0_LCLK2_MASK                32U
#define LCDC0_SOURCE_MASK               64U
#define LCDC0_LCDEN_MASK                128U
#define LCDC0_DUTY_MASK                 7U
#define LCDC0_DUTY_BITNUM               0U
#define LCDC0_LCLK_MASK                 56U
#define LCDC0_LCLK_BITNUM               3U


/*** LCDC1 - LCD Control Register 1; 0x00000019 ***/
typedef union {
  byte Byte;
  struct {
    byte LCDSTP      :1;                                       /* LCD Module Driver and Charge Pump Stop While in Stop2 or Stop3 Mode */
    byte LCDWAI      :1;                                       /* LCD Module Driver and Charge Pump Stop While in Wait Mode */
    byte FCDEN       :1;                                       /* Full Complementary Drive Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte LCDIEN      :1;                                       /* LCD Module Frame Frequency Interrupt Enable */
  } Bits;
} LCDC1STR;
extern volatile LCDC1STR _LCDC1 @0x00000019;
#define LCDC1                           _LCDC1.Byte
#define LCDC1_LCDSTP                    _LCDC1.Bits.LCDSTP
#define LCDC1_LCDWAI                    _LCDC1.Bits.LCDWAI
#define LCDC1_FCDEN                     _LCDC1.Bits.FCDEN
#define LCDC1_LCDIEN                    _LCDC1.Bits.LCDIEN

#define LCDC1_LCDSTP_MASK               1U
#define LCDC1_LCDWAI_MASK               2U
#define LCDC1_FCDEN_MASK                4U
#define LCDC1_LCDIEN_MASK               128U


/*** LCDSUPPLY - LCD Voltage Supply Register; 0x0000001A ***/
typedef union {
  byte Byte;
  struct {
    byte VSUPPLY0    :1;                                       /* Voltage Supply Control Bit 0 */
    byte VSUPPLY1    :1;                                       /* Voltage Supply Control Bit 1 */
    byte BBYPASS     :1;                                       /* Op Amp Control */
    byte             :1; 
    byte LADJ0       :1;                                       /* LCD Module Load Adjust Bit 0 */
    byte LADJ1       :1;                                       /* LCD Module Load Adjust Bit 1 */
    byte HREFSEL     :1;                                       /* High Reference Select */
    byte CPSEL       :1;                                       /* Charge Pump or Resistor Bias Select */
  } Bits;
  struct {
    byte grpVSUPPLY :2;
    byte         :1;
    byte         :1;
    byte grpLADJ :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} LCDSUPPLYSTR;
extern volatile LCDSUPPLYSTR _LCDSUPPLY @0x0000001A;
#define LCDSUPPLY                       _LCDSUPPLY.Byte
#define LCDSUPPLY_VSUPPLY0              _LCDSUPPLY.Bits.VSUPPLY0
#define LCDSUPPLY_VSUPPLY1              _LCDSUPPLY.Bits.VSUPPLY1
#define LCDSUPPLY_BBYPASS               _LCDSUPPLY.Bits.BBYPASS
#define LCDSUPPLY_LADJ0                 _LCDSUPPLY.Bits.LADJ0
#define LCDSUPPLY_LADJ1                 _LCDSUPPLY.Bits.LADJ1
#define LCDSUPPLY_HREFSEL               _LCDSUPPLY.Bits.HREFSEL
#define LCDSUPPLY_CPSEL                 _LCDSUPPLY.Bits.CPSEL
#define LCDSUPPLY_VSUPPLY               _LCDSUPPLY.MergedBits.grpVSUPPLY
#define LCDSUPPLY_LADJ                  _LCDSUPPLY.MergedBits.grpLADJ

#define LCDSUPPLY_VSUPPLY0_MASK         1U
#define LCDSUPPLY_VSUPPLY1_MASK         2U
#define LCDSUPPLY_BBYPASS_MASK          4U
#define LCDSUPPLY_LADJ0_MASK            16U
#define LCDSUPPLY_LADJ1_MASK            32U
#define LCDSUPPLY_HREFSEL_MASK          64U
#define LCDSUPPLY_CPSEL_MASK            128U
#define LCDSUPPLY_VSUPPLY_MASK          3U
#define LCDSUPPLY_VSUPPLY_BITNUM        0U
#define LCDSUPPLY_LADJ_MASK             48U
#define LCDSUPPLY_LADJ_BITNUM           4U


/*** LCDRVC - LCD Regulated Voltage Control Register; 0x0000001B ***/
typedef union {
  byte Byte;
  struct {
    byte RVTRIM0     :1;                                       /* Regulated Voltage Trim Bit 0 */
    byte RVTRIM1     :1;                                       /* Regulated Voltage Trim Bit 1 */
    byte RVTRIM2     :1;                                       /* Regulated Voltage Trim Bit 2 */
    byte RVTRIM3     :1;                                       /* Regulated Voltage Trim Bit 3 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte RVEN        :1;                                       /* Regulated Voltage Enable */
  } Bits;
  struct {
    byte grpRVTRIM :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} LCDRVCSTR;
extern volatile LCDRVCSTR _LCDRVC @0x0000001B;
#define LCDRVC                          _LCDRVC.Byte
#define LCDRVC_RVTRIM0                  _LCDRVC.Bits.RVTRIM0
#define LCDRVC_RVTRIM1                  _LCDRVC.Bits.RVTRIM1
#define LCDRVC_RVTRIM2                  _LCDRVC.Bits.RVTRIM2
#define LCDRVC_RVTRIM3                  _LCDRVC.Bits.RVTRIM3
#define LCDRVC_RVEN                     _LCDRVC.Bits.RVEN
#define LCDRVC_RVTRIM                   _LCDRVC.MergedBits.grpRVTRIM

#define LCDRVC_RVTRIM0_MASK             1U
#define LCDRVC_RVTRIM1_MASK             2U
#define LCDRVC_RVTRIM2_MASK             4U
#define LCDRVC_RVTRIM3_MASK             8U
#define LCDRVC_RVEN_MASK                128U
#define LCDRVC_RVTRIM_MASK              15U
#define LCDRVC_RVTRIM_BITNUM            0U


/*** LCDBCTL - LCD Blink Control Register; 0x0000001C ***/
typedef union {
  byte Byte;
  struct {
    byte BRATE0      :1;                                       /* Blink-Rate Configuration Bit 0 */
    byte BRATE1      :1;                                       /* Blink-Rate Configuration Bit 1 */
    byte BRATE2      :1;                                       /* Blink-Rate Configuration Bit 2 */
    byte BMODE       :1;                                       /* Blink Mode */
    byte             :1; 
    byte BLANK       :1;                                       /* Blank Display Mode */
    byte ALT         :1;                                       /* Alternate Display Mode */
    byte BLINK       :1;                                       /* Blink Command */
  } Bits;
  struct {
    byte grpBRATE :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} LCDBCTLSTR;
extern volatile LCDBCTLSTR _LCDBCTL @0x0000001C;
#define LCDBCTL                         _LCDBCTL.Byte
#define LCDBCTL_BRATE0                  _LCDBCTL.Bits.BRATE0
#define LCDBCTL_BRATE1                  _LCDBCTL.Bits.BRATE1
#define LCDBCTL_BRATE2                  _LCDBCTL.Bits.BRATE2
#define LCDBCTL_BMODE                   _LCDBCTL.Bits.BMODE
#define LCDBCTL_BLANK                   _LCDBCTL.Bits.BLANK
#define LCDBCTL_ALT                     _LCDBCTL.Bits.ALT
#define LCDBCTL_BLINK                   _LCDBCTL.Bits.BLINK
#define LCDBCTL_BRATE                   _LCDBCTL.MergedBits.grpBRATE

#define LCDBCTL_BRATE0_MASK             1U
#define LCDBCTL_BRATE1_MASK             2U
#define LCDBCTL_BRATE2_MASK             4U
#define LCDBCTL_BMODE_MASK              8U
#define LCDBCTL_BLANK_MASK              32U
#define LCDBCTL_ALT_MASK                64U
#define LCDBCTL_BLINK_MASK              128U
#define LCDBCTL_BRATE_MASK              7U
#define LCDBCTL_BRATE_BITNUM            0U


/*** LCDS - LCD Status Register; 0x0000001D ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte LCDIF       :1;                                       /* LCD Interrupt Flag */
  } Bits;
} LCDSSTR;
extern volatile LCDSSTR _LCDS @0x0000001D;
#define LCDS                            _LCDS.Byte
#define LCDS_LCDIF                      _LCDS.Bits.LCDIF

#define LCDS_LCDIF_MASK                 128U


/*** ACMPSC - ACMP Status and Control Register; 0x0000001F ***/
typedef union {
  byte Byte;
  struct {
    byte ACMOD0      :1;                                       /* Analog Comparator Mode Bit 0 */
    byte ACMOD1      :1;                                       /* Analog Comparator Mode Bit 1 */
    byte ACOPE       :1;                                       /* Analog Comparator Output Pin Enable */
    byte ACO         :1;                                       /* Analog Comparator Output */
    byte ACIE        :1;                                       /* Analog Comparator Interrupt Enable */
    byte ACF         :1;                                       /* Analog Comparator Flag */
    byte ACBGS       :1;                                       /* Analog Comparator Bandgap Select */
    byte ACME        :1;                                       /* Analog Comparator Module Enable */
  } Bits;
  struct {
    byte grpACMOD :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ACMPSCSTR;
extern volatile ACMPSCSTR _ACMPSC @0x0000001F;
#define ACMPSC                          _ACMPSC.Byte
#define ACMPSC_ACMOD0                   _ACMPSC.Bits.ACMOD0
#define ACMPSC_ACMOD1                   _ACMPSC.Bits.ACMOD1
#define ACMPSC_ACOPE                    _ACMPSC.Bits.ACOPE
#define ACMPSC_ACO                      _ACMPSC.Bits.ACO
#define ACMPSC_ACIE                     _ACMPSC.Bits.ACIE
#define ACMPSC_ACF                      _ACMPSC.Bits.ACF
#define ACMPSC_ACBGS                    _ACMPSC.Bits.ACBGS
#define ACMPSC_ACME                     _ACMPSC.Bits.ACME
#define ACMPSC_ACMOD                    _ACMPSC.MergedBits.grpACMOD

#define ACMPSC_ACMOD0_MASK              1U
#define ACMPSC_ACMOD1_MASK              2U
#define ACMPSC_ACOPE_MASK               4U
#define ACMPSC_ACO_MASK                 8U
#define ACMPSC_ACIE_MASK                16U
#define ACMPSC_ACF_MASK                 32U
#define ACMPSC_ACBGS_MASK               64U
#define ACMPSC_ACME_MASK                128U
#define ACMPSC_ACMOD_MASK               3U
#define ACMPSC_ACMOD_BITNUM             0U


/*** SCIBD - SCI Baud Rate Register; 0x00000020 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCIBDH - SCI Baud Rate Register High; 0x00000020 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
        byte LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCIBDHSTR;
    #define SCIBDH                      _SCIBD.Overlap_STR.SCIBDHSTR.Byte
    #define SCIBDH_SBR8                 _SCIBD.Overlap_STR.SCIBDHSTR.Bits.SBR8
    #define SCIBDH_SBR9                 _SCIBD.Overlap_STR.SCIBDHSTR.Bits.SBR9
    #define SCIBDH_SBR10                _SCIBD.Overlap_STR.SCIBDHSTR.Bits.SBR10
    #define SCIBDH_SBR11                _SCIBD.Overlap_STR.SCIBDHSTR.Bits.SBR11
    #define SCIBDH_SBR12                _SCIBD.Overlap_STR.SCIBDHSTR.Bits.SBR12
    #define SCIBDH_RXEDGIE              _SCIBD.Overlap_STR.SCIBDHSTR.Bits.RXEDGIE
    #define SCIBDH_LBKDIE               _SCIBD.Overlap_STR.SCIBDHSTR.Bits.LBKDIE
    #define SCIBDH_SBR_8                _SCIBD.Overlap_STR.SCIBDHSTR.MergedBits.grpSBR_8
    #define SCIBDH_SBR                  SCIBDH_SBR_8
    
    #define SCIBDH_SBR8_MASK            1U
    #define SCIBDH_SBR9_MASK            2U
    #define SCIBDH_SBR10_MASK           4U
    #define SCIBDH_SBR11_MASK           8U
    #define SCIBDH_SBR12_MASK           16U
    #define SCIBDH_RXEDGIE_MASK         64U
    #define SCIBDH_LBKDIE_MASK          128U
    #define SCIBDH_SBR_8_MASK           31U
    #define SCIBDH_SBR_8_BITNUM         0U
    

    /*** SCIBDL - SCI Baud Rate Register Low; 0x00000021 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCIBDLSTR;
    #define SCIBDL                      _SCIBD.Overlap_STR.SCIBDLSTR.Byte
    #define SCIBDL_SBR0                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR0
    #define SCIBDL_SBR1                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR1
    #define SCIBDL_SBR2                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR2
    #define SCIBDL_SBR3                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR3
    #define SCIBDL_SBR4                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR4
    #define SCIBDL_SBR5                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR5
    #define SCIBDL_SBR6                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR6
    #define SCIBDL_SBR7                 _SCIBD.Overlap_STR.SCIBDLSTR.Bits.SBR7
    
    #define SCIBDL_SBR0_MASK            1U
    #define SCIBDL_SBR1_MASK            2U
    #define SCIBDL_SBR2_MASK            4U
    #define SCIBDL_SBR3_MASK            8U
    #define SCIBDL_SBR4_MASK            16U
    #define SCIBDL_SBR5_MASK            32U
    #define SCIBDL_SBR6_MASK            64U
    #define SCIBDL_SBR7_MASK            128U
    
  } Overlap_STR;

} SCIBDSTR;
extern volatile SCIBDSTR _SCIBD @0x00000020;
#define SCIBD                           _SCIBD.Word


/*** SCIC1 - SCI Control Register 1; 0x00000022 ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCIC1STR;
extern volatile SCIC1STR _SCIC1 @0x00000022;
#define SCIC1                           _SCIC1.Byte
#define SCIC1_PT                        _SCIC1.Bits.PT
#define SCIC1_PE                        _SCIC1.Bits.PE
#define SCIC1_ILT                       _SCIC1.Bits.ILT
#define SCIC1_WAKE                      _SCIC1.Bits.WAKE
#define SCIC1_M                         _SCIC1.Bits.M
#define SCIC1_RSRC                      _SCIC1.Bits.RSRC
#define SCIC1_SCISWAI                   _SCIC1.Bits.SCISWAI
#define SCIC1_LOOPS                     _SCIC1.Bits.LOOPS

#define SCIC1_PT_MASK                   1U
#define SCIC1_PE_MASK                   2U
#define SCIC1_ILT_MASK                  4U
#define SCIC1_WAKE_MASK                 8U
#define SCIC1_M_MASK                    16U
#define SCIC1_RSRC_MASK                 32U
#define SCIC1_SCISWAI_MASK              64U
#define SCIC1_LOOPS_MASK                128U


/*** SCIC2 - SCI Control Register 2; 0x00000023 ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCIC2STR;
extern volatile SCIC2STR _SCIC2 @0x00000023;
#define SCIC2                           _SCIC2.Byte
#define SCIC2_SBK                       _SCIC2.Bits.SBK
#define SCIC2_RWU                       _SCIC2.Bits.RWU
#define SCIC2_RE                        _SCIC2.Bits.RE
#define SCIC2_TE                        _SCIC2.Bits.TE
#define SCIC2_ILIE                      _SCIC2.Bits.ILIE
#define SCIC2_RIE                       _SCIC2.Bits.RIE
#define SCIC2_TCIE                      _SCIC2.Bits.TCIE
#define SCIC2_TIE                       _SCIC2.Bits.TIE

#define SCIC2_SBK_MASK                  1U
#define SCIC2_RWU_MASK                  2U
#define SCIC2_RE_MASK                   4U
#define SCIC2_TE_MASK                   8U
#define SCIC2_ILIE_MASK                 16U
#define SCIC2_RIE_MASK                  32U
#define SCIC2_TCIE_MASK                 64U
#define SCIC2_TIE_MASK                  128U


/*** SCIS1 - SCI Status Register 1; 0x00000024 ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCIS1STR;
extern volatile SCIS1STR _SCIS1 @0x00000024;
#define SCIS1                           _SCIS1.Byte
#define SCIS1_PF                        _SCIS1.Bits.PF
#define SCIS1_FE                        _SCIS1.Bits.FE
#define SCIS1_NF                        _SCIS1.Bits.NF
#define SCIS1_OR                        _SCIS1.Bits.OR
#define SCIS1_IDLE                      _SCIS1.Bits.IDLE
#define SCIS1_RDRF                      _SCIS1.Bits.RDRF
#define SCIS1_TC                        _SCIS1.Bits.TC
#define SCIS1_TDRE                      _SCIS1.Bits.TDRE

#define SCIS1_PF_MASK                   1U
#define SCIS1_FE_MASK                   2U
#define SCIS1_NF_MASK                   4U
#define SCIS1_OR_MASK                   8U
#define SCIS1_IDLE_MASK                 16U
#define SCIS1_RDRF_MASK                 32U
#define SCIS1_TC_MASK                   64U
#define SCIS1_TDRE_MASK                 128U


/*** SCIS2 - SCI Status Register 2; 0x00000025 ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte LBKDE       :1;                                       /* LIN Break Detection Enable */
    byte BRK13       :1;                                       /* Break Character Generation Length */
    byte RWUID       :1;                                       /* Receive Wake Up Idle Detect */
    byte RXINV       :1;                                       /* Receive Data Inversion */
    byte             :1; 
    byte RXEDGIF     :1;                                       /* RxD Pin Active Edge Interrupt Flag */
    byte LBKDIF      :1;                                       /* LIN Break Detect Interrupt Flag */
  } Bits;
} SCIS2STR;
extern volatile SCIS2STR _SCIS2 @0x00000025;
#define SCIS2                           _SCIS2.Byte
#define SCIS2_RAF                       _SCIS2.Bits.RAF
#define SCIS2_LBKDE                     _SCIS2.Bits.LBKDE
#define SCIS2_BRK13                     _SCIS2.Bits.BRK13
#define SCIS2_RWUID                     _SCIS2.Bits.RWUID
#define SCIS2_RXINV                     _SCIS2.Bits.RXINV
#define SCIS2_RXEDGIF                   _SCIS2.Bits.RXEDGIF
#define SCIS2_LBKDIF                    _SCIS2.Bits.LBKDIF

#define SCIS2_RAF_MASK                  1U
#define SCIS2_LBKDE_MASK                2U
#define SCIS2_BRK13_MASK                4U
#define SCIS2_RWUID_MASK                8U
#define SCIS2_RXINV_MASK                16U
#define SCIS2_RXEDGIF_MASK              64U
#define SCIS2_LBKDIF_MASK               128U


/*** SCIC3 - SCI Control Register 3; 0x00000026 ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCIC3STR;
extern volatile SCIC3STR _SCIC3 @0x00000026;
#define SCIC3                           _SCIC3.Byte
#define SCIC3_PEIE                      _SCIC3.Bits.PEIE
#define SCIC3_FEIE                      _SCIC3.Bits.FEIE
#define SCIC3_NEIE                      _SCIC3.Bits.NEIE
#define SCIC3_ORIE                      _SCIC3.Bits.ORIE
#define SCIC3_TXINV                     _SCIC3.Bits.TXINV
#define SCIC3_TXDIR                     _SCIC3.Bits.TXDIR
#define SCIC3_T8                        _SCIC3.Bits.T8
#define SCIC3_R8                        _SCIC3.Bits.R8

#define SCIC3_PEIE_MASK                 1U
#define SCIC3_FEIE_MASK                 2U
#define SCIC3_NEIE_MASK                 4U
#define SCIC3_ORIE_MASK                 8U
#define SCIC3_TXINV_MASK                16U
#define SCIC3_TXDIR_MASK                32U
#define SCIC3_T8_MASK                   64U
#define SCIC3_R8_MASK                   128U


/*** SCID - SCI Data Register; 0x00000027 ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCIDSTR;
extern volatile SCIDSTR _SCID @0x00000027;
#define SCID                            _SCID.Byte
#define SCID_R0_T0                      _SCID.Bits.R0_T0
#define SCID_R1_T1                      _SCID.Bits.R1_T1
#define SCID_R2_T2                      _SCID.Bits.R2_T2
#define SCID_R3_T3                      _SCID.Bits.R3_T3
#define SCID_R4_T4                      _SCID.Bits.R4_T4
#define SCID_R5_T5                      _SCID.Bits.R5_T5
#define SCID_R6_T6                      _SCID.Bits.R6_T6
#define SCID_R7_T7                      _SCID.Bits.R7_T7

#define SCID_R0_T0_MASK                 1U
#define SCID_R1_T1_MASK                 2U
#define SCID_R2_T2_MASK                 4U
#define SCID_R3_T3_MASK                 8U
#define SCID_R4_T4_MASK                 16U
#define SCID_R5_T5_MASK                 32U
#define SCID_R6_T6_MASK                 64U
#define SCID_R7_T7_MASK                 128U


/*** SPIC1 - SPI Control Register 1; 0x00000028 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (Shifter Direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI System Enable */
    byte SPIE        :1;                                       /* SPI Interrupt Enable (for SPRF and MODF) */
  } Bits;
} SPIC1STR;
extern volatile SPIC1STR _SPIC1 @0x00000028;
#define SPIC1                           _SPIC1.Byte
#define SPIC1_LSBFE                     _SPIC1.Bits.LSBFE
#define SPIC1_SSOE                      _SPIC1.Bits.SSOE
#define SPIC1_CPHA                      _SPIC1.Bits.CPHA
#define SPIC1_CPOL                      _SPIC1.Bits.CPOL
#define SPIC1_MSTR                      _SPIC1.Bits.MSTR
#define SPIC1_SPTIE                     _SPIC1.Bits.SPTIE
#define SPIC1_SPE                       _SPIC1.Bits.SPE
#define SPIC1_SPIE                      _SPIC1.Bits.SPIE

#define SPIC1_LSBFE_MASK                1U
#define SPIC1_SSOE_MASK                 2U
#define SPIC1_CPHA_MASK                 4U
#define SPIC1_CPOL_MASK                 8U
#define SPIC1_MSTR_MASK                 16U
#define SPIC1_SPTIE_MASK                32U
#define SPIC1_SPE_MASK                  64U
#define SPIC1_SPIE_MASK                 128U


/*** SPIC2 - SPI Control Register 2; 0x00000029 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI Stop in Wait Mode */
    byte             :1; 
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SPIC2STR;
extern volatile SPIC2STR _SPIC2 @0x00000029;
#define SPIC2                           _SPIC2.Byte
#define SPIC2_SPC0                      _SPIC2.Bits.SPC0
#define SPIC2_SPISWAI                   _SPIC2.Bits.SPISWAI
#define SPIC2_BIDIROE                   _SPIC2.Bits.BIDIROE
#define SPIC2_MODFEN                    _SPIC2.Bits.MODFEN

#define SPIC2_SPC0_MASK                 1U
#define SPIC2_SPISWAI_MASK              2U
#define SPIC2_BIDIROE_MASK              8U
#define SPIC2_MODFEN_MASK               16U


/*** SPIBR - SPI Baud Rate Register; 0x0000002A ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI Baud Rate Divisor Bit 2 */
    byte             :1; 
    byte SPPR0       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpSPR  :3;
    byte         :1;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPIBRSTR;
extern volatile SPIBRSTR _SPIBR @0x0000002A;
#define SPIBR                           _SPIBR.Byte
#define SPIBR_SPR0                      _SPIBR.Bits.SPR0
#define SPIBR_SPR1                      _SPIBR.Bits.SPR1
#define SPIBR_SPR2                      _SPIBR.Bits.SPR2
#define SPIBR_SPPR0                     _SPIBR.Bits.SPPR0
#define SPIBR_SPPR1                     _SPIBR.Bits.SPPR1
#define SPIBR_SPPR2                     _SPIBR.Bits.SPPR2
#define SPIBR_SPR                       _SPIBR.MergedBits.grpSPR
#define SPIBR_SPPR                      _SPIBR.MergedBits.grpSPPR

#define SPIBR_SPR0_MASK                 1U
#define SPIBR_SPR1_MASK                 2U
#define SPIBR_SPR2_MASK                 4U
#define SPIBR_SPPR0_MASK                16U
#define SPIBR_SPPR1_MASK                32U
#define SPIBR_SPPR2_MASK                64U
#define SPIBR_SPR_MASK                  7U
#define SPIBR_SPR_BITNUM                0U
#define SPIBR_SPPR_MASK                 112U
#define SPIBR_SPPR_BITNUM               4U


/*** SPIS - SPI Status Register; 0x0000002B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI Transmit Buffer Empty Flag */
    byte             :1; 
    byte SPRF        :1;                                       /* SPI Read Buffer Full Flag */
  } Bits;
} SPISSTR;
extern volatile SPISSTR _SPIS @0x0000002B;
#define SPIS                            _SPIS.Byte
#define SPIS_MODF                       _SPIS.Bits.MODF
#define SPIS_SPTEF                      _SPIS.Bits.SPTEF
#define SPIS_SPRF                       _SPIS.Bits.SPRF

#define SPIS_MODF_MASK                  16U
#define SPIS_SPTEF_MASK                 32U
#define SPIS_SPRF_MASK                  128U


/*** SPID - SPI Data Register; 0x0000002D ***/
typedef union {
  byte Byte;
} SPIDSTR;
extern volatile SPIDSTR _SPID @0x0000002D;
#define SPID                            _SPID.Byte


/*** IICA - IIC Address Register; 0x00000030 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte AD1         :1;                                       /* Slave Address Bit 1 */
    byte AD2         :1;                                       /* Slave Address Bit 2 */
    byte AD3         :1;                                       /* Slave Address Bit 3 */
    byte AD4         :1;                                       /* Slave Address Bit 4 */
    byte AD5         :1;                                       /* Slave Address Bit 5 */
    byte AD6         :1;                                       /* Slave Address Bit 6 */
    byte AD7         :1;                                       /* Slave Address Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpAD_1 :7;
  } MergedBits;
} IICASTR;
extern volatile IICASTR _IICA @0x00000030;
#define IICA                            _IICA.Byte
#define IICA_AD1                        _IICA.Bits.AD1
#define IICA_AD2                        _IICA.Bits.AD2
#define IICA_AD3                        _IICA.Bits.AD3
#define IICA_AD4                        _IICA.Bits.AD4
#define IICA_AD5                        _IICA.Bits.AD5
#define IICA_AD6                        _IICA.Bits.AD6
#define IICA_AD7                        _IICA.Bits.AD7
#define IICA_AD_1                       _IICA.MergedBits.grpAD_1
#define IICA_AD                         IICA_AD_1

#define IICA_AD1_MASK                   2U
#define IICA_AD2_MASK                   4U
#define IICA_AD3_MASK                   8U
#define IICA_AD4_MASK                   16U
#define IICA_AD5_MASK                   32U
#define IICA_AD6_MASK                   64U
#define IICA_AD7_MASK                   128U
#define IICA_AD_1_MASK                  254U
#define IICA_AD_1_BITNUM                1U


/*** IICF - IIC Frequency Divider Register; 0x00000031 ***/
typedef union {
  byte Byte;
  struct {
    byte ICR0        :1;                                       /* IIC Clock Rate Bit 0 */
    byte ICR1        :1;                                       /* IIC Clock Rate Bit 1 */
    byte ICR2        :1;                                       /* IIC Clock Rate Bit 2 */
    byte ICR3        :1;                                       /* IIC Clock Rate Bit 3 */
    byte ICR4        :1;                                       /* IIC Clock Rate Bit 4 */
    byte ICR5        :1;                                       /* IIC Clock Rate Bit 5 */
    byte MULT0       :1;                                       /* Multiplier Factor Bit 0 */
    byte MULT1       :1;                                       /* Multiplier Factor Bit 1 */
  } Bits;
  struct {
    byte grpICR  :6;
    byte grpMULT :2;
  } MergedBits;
} IICFSTR;
extern volatile IICFSTR _IICF @0x00000031;
#define IICF                            _IICF.Byte
#define IICF_ICR0                       _IICF.Bits.ICR0
#define IICF_ICR1                       _IICF.Bits.ICR1
#define IICF_ICR2                       _IICF.Bits.ICR2
#define IICF_ICR3                       _IICF.Bits.ICR3
#define IICF_ICR4                       _IICF.Bits.ICR4
#define IICF_ICR5                       _IICF.Bits.ICR5
#define IICF_MULT0                      _IICF.Bits.MULT0
#define IICF_MULT1                      _IICF.Bits.MULT1
#define IICF_ICR                        _IICF.MergedBits.grpICR
#define IICF_MULT                       _IICF.MergedBits.grpMULT

#define IICF_ICR0_MASK                  1U
#define IICF_ICR1_MASK                  2U
#define IICF_ICR2_MASK                  4U
#define IICF_ICR3_MASK                  8U
#define IICF_ICR4_MASK                  16U
#define IICF_ICR5_MASK                  32U
#define IICF_MULT0_MASK                 64U
#define IICF_MULT1_MASK                 128U
#define IICF_ICR_MASK                   63U
#define IICF_ICR_BITNUM                 0U
#define IICF_MULT_MASK                  192U
#define IICF_MULT_BITNUM                6U


/*** IICC1 - IIC Control Register 1; 0x00000032 ***/
typedef union {
  byte Byte;
  union { /* Several registers at the same address */
    /*** IICC1 - IIC Control Register 1; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IICC1STR;
    #define IICC1                       _IICC1.Byte
    #define IICC1_RSTA                  _IICC1.SameAddr_STR.IICC1STR.Bits.RSTA
    #define IICC1_TXAK                  _IICC1.SameAddr_STR.IICC1STR.Bits.TXAK
    #define IICC1_TX                    _IICC1.SameAddr_STR.IICC1STR.Bits.TX
    #define IICC1_MST                   _IICC1.SameAddr_STR.IICC1STR.Bits.MST
    #define IICC1_IICIE                 _IICC1.SameAddr_STR.IICC1STR.Bits.IICIE
    #define IICC1_IICEN                 _IICC1.SameAddr_STR.IICC1STR.Bits.IICEN
    
    #define IICC1_RSTA_MASK             4U
    #define IICC1_TXAK_MASK             8U
    #define IICC1_TX_MASK               16U
    #define IICC1_MST_MASK              32U
    #define IICC1_IICIE_MASK            64U
    #define IICC1_IICEN_MASK            128U
    
    /*** IICC - IIC Control Register; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IICCSTR;
    #define IICC                        _IICC1.Byte
    #define IICC_RSTA                   _IICC1.SameAddr_STR.IICCSTR.Bits.RSTA
    #define IICC_TXAK                   _IICC1.SameAddr_STR.IICCSTR.Bits.TXAK
    #define IICC_TX                     _IICC1.SameAddr_STR.IICCSTR.Bits.TX
    #define IICC_MST                    _IICC1.SameAddr_STR.IICCSTR.Bits.MST
    #define IICC_IICIE                  _IICC1.SameAddr_STR.IICCSTR.Bits.IICIE
    #define IICC_IICEN                  _IICC1.SameAddr_STR.IICCSTR.Bits.IICEN
    
    #define IICC_RSTA_MASK              4U
    #define IICC_TXAK_MASK              8U
    #define IICC_TX_MASK                16U
    #define IICC_MST_MASK               32U
    #define IICC_IICIE_MASK             64U
    #define IICC_IICEN_MASK             128U
    
  } SameAddr_STR; /*Several registers at the same address */

} IICC1STR;
extern volatile IICC1STR _IICC1 @0x00000032;


/*** IICS - IIC Status Register; 0x00000033 ***/
typedef union {
  byte Byte;
  struct {
    byte RXAK        :1;                                       /* Receive Acknowledge */
    byte IICIF       :1;                                       /* IIC Interrupt Flag */
    byte SRW         :1;                                       /* Slave Read/Write */
    byte             :1; 
    byte ARBL        :1;                                       /* Arbitration Lost */
    byte BUSY        :1;                                       /* Bus Busy */
    byte IAAS        :1;                                       /* Addressed as a Slave */
    byte TCF         :1;                                       /* Transfer Complete Flag */
  } Bits;
} IICSSTR;
extern volatile IICSSTR _IICS @0x00000033;
#define IICS                            _IICS.Byte
#define IICS_RXAK                       _IICS.Bits.RXAK
#define IICS_IICIF                      _IICS.Bits.IICIF
#define IICS_SRW                        _IICS.Bits.SRW
#define IICS_ARBL                       _IICS.Bits.ARBL
#define IICS_BUSY                       _IICS.Bits.BUSY
#define IICS_IAAS                       _IICS.Bits.IAAS
#define IICS_TCF                        _IICS.Bits.TCF

#define IICS_RXAK_MASK                  1U
#define IICS_IICIF_MASK                 2U
#define IICS_SRW_MASK                   4U
#define IICS_ARBL_MASK                  16U
#define IICS_BUSY_MASK                  32U
#define IICS_IAAS_MASK                  64U
#define IICS_TCF_MASK                   128U


/*** IICD - IIC Data I/O Register; 0x00000034 ***/
typedef union {
  byte Byte;
  struct {
    byte DATA0       :1;                                       /* IIC Data Bit 0 */
    byte DATA1       :1;                                       /* IIC Data Bit 1 */
    byte DATA2       :1;                                       /* IIC Data Bit 2 */
    byte DATA3       :1;                                       /* IIC Data Bit 3 */
    byte DATA4       :1;                                       /* IIC Data Bit 4 */
    byte DATA5       :1;                                       /* IIC Data Bit 5 */
    byte DATA6       :1;                                       /* IIC Data Bit 6 */
    byte DATA7       :1;                                       /* IIC Data Bit 7 */
  } Bits;
} IICDSTR;
extern volatile IICDSTR _IICD @0x00000034;
#define IICD                            _IICD.Byte
#define IICD_DATA0                      _IICD.Bits.DATA0
#define IICD_DATA1                      _IICD.Bits.DATA1
#define IICD_DATA2                      _IICD.Bits.DATA2
#define IICD_DATA3                      _IICD.Bits.DATA3
#define IICD_DATA4                      _IICD.Bits.DATA4
#define IICD_DATA5                      _IICD.Bits.DATA5
#define IICD_DATA6                      _IICD.Bits.DATA6
#define IICD_DATA7                      _IICD.Bits.DATA7

#define IICD_DATA0_MASK                 1U
#define IICD_DATA1_MASK                 2U
#define IICD_DATA2_MASK                 4U
#define IICD_DATA3_MASK                 8U
#define IICD_DATA4_MASK                 16U
#define IICD_DATA5_MASK                 32U
#define IICD_DATA6_MASK                 64U
#define IICD_DATA7_MASK                 128U


/*** IICC2 - IIC Control Register 2; 0x00000035 ***/
typedef union {
  byte Byte;
  struct {
    byte AD8         :1;                                       /* Slave Address Bit 8 */
    byte AD9         :1;                                       /* Slave Address Bit 9 */
    byte AD10        :1;                                       /* Slave Address Bit 10 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ADEXT       :1;                                       /* Address Extension */
    byte GCAEN       :1;                                       /* General Call Address Enable */
  } Bits;
  struct {
    byte grpAD_8 :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} IICC2STR;
extern volatile IICC2STR _IICC2 @0x00000035;
#define IICC2                           _IICC2.Byte
#define IICC2_AD8                       _IICC2.Bits.AD8
#define IICC2_AD9                       _IICC2.Bits.AD9
#define IICC2_AD10                      _IICC2.Bits.AD10
#define IICC2_ADEXT                     _IICC2.Bits.ADEXT
#define IICC2_GCAEN                     _IICC2.Bits.GCAEN
#define IICC2_AD_8                      _IICC2.MergedBits.grpAD_8
#define IICC2_AD                        IICC2_AD_8

#define IICC2_AD8_MASK                  1U
#define IICC2_AD9_MASK                  2U
#define IICC2_AD10_MASK                 4U
#define IICC2_ADEXT_MASK                64U
#define IICC2_GCAEN_MASK                128U
#define IICC2_AD_8_MASK                 7U
#define IICC2_AD_8_BITNUM               0U


/*** ICSC1 - ICS Control Register 1; 0x00000038 ***/
typedef union {
  byte Byte;
  struct {
    byte IREFSTEN    :1;                                       /* Internal Reference Stop Enable */
    byte IRCLKEN     :1;                                       /* Internal Reference Clock Enable */
    byte IREFS       :1;                                       /* Internal Reference Select */
    byte RDIV0       :1;                                       /* Reference Divider, bit 0 */
    byte RDIV1       :1;                                       /* Reference Divider, bit 1 */
    byte RDIV2       :1;                                       /* Reference Divider, bit 2 */
    byte CLKS0       :1;                                       /* Clock Source Select, bit 0 */
    byte CLKS1       :1;                                       /* Clock Source Select, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpRDIV :3;
    byte grpCLKS :2;
  } MergedBits;
} ICSC1STR;
extern volatile ICSC1STR _ICSC1 @0x00000038;
#define ICSC1                           _ICSC1.Byte
#define ICSC1_IREFSTEN                  _ICSC1.Bits.IREFSTEN
#define ICSC1_IRCLKEN                   _ICSC1.Bits.IRCLKEN
#define ICSC1_IREFS                     _ICSC1.Bits.IREFS
#define ICSC1_RDIV0                     _ICSC1.Bits.RDIV0
#define ICSC1_RDIV1                     _ICSC1.Bits.RDIV1
#define ICSC1_RDIV2                     _ICSC1.Bits.RDIV2
#define ICSC1_CLKS0                     _ICSC1.Bits.CLKS0
#define ICSC1_CLKS1                     _ICSC1.Bits.CLKS1
#define ICSC1_RDIV                      _ICSC1.MergedBits.grpRDIV
#define ICSC1_CLKS                      _ICSC1.MergedBits.grpCLKS

#define ICSC1_IREFSTEN_MASK             1U
#define ICSC1_IRCLKEN_MASK              2U
#define ICSC1_IREFS_MASK                4U
#define ICSC1_RDIV0_MASK                8U
#define ICSC1_RDIV1_MASK                16U
#define ICSC1_RDIV2_MASK                32U
#define ICSC1_CLKS0_MASK                64U
#define ICSC1_CLKS1_MASK                128U
#define ICSC1_RDIV_MASK                 56U
#define ICSC1_RDIV_BITNUM               3U
#define ICSC1_CLKS_MASK                 192U
#define ICSC1_CLKS_BITNUM               6U


/*** ICSC2 - ICS Control Register 2; 0x00000039 ***/
typedef union {
  byte Byte;
  struct {
    byte EREFSTEN    :1;                                       /* External Reference Stop Enable */
    byte ERCLKEN     :1;                                       /* External Reference Enable */
    byte EREFS       :1;                                       /* External Reference Select */
    byte LP          :1;                                       /* Low Power Select */
    byte HGO         :1;                                       /* High Gain Oscillator Select */
    byte RANGE       :1;                                       /* Frequency Range Select */
    byte BDIV0       :1;                                       /* Bus Frequency Divider, bit 0 */
    byte BDIV1       :1;                                       /* Bus Frequency Divider, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpBDIV :2;
  } MergedBits;
} ICSC2STR;
extern volatile ICSC2STR _ICSC2 @0x00000039;
#define ICSC2                           _ICSC2.Byte
#define ICSC2_EREFSTEN                  _ICSC2.Bits.EREFSTEN
#define ICSC2_ERCLKEN                   _ICSC2.Bits.ERCLKEN
#define ICSC2_EREFS                     _ICSC2.Bits.EREFS
#define ICSC2_LP                        _ICSC2.Bits.LP
#define ICSC2_HGO                       _ICSC2.Bits.HGO
#define ICSC2_RANGE                     _ICSC2.Bits.RANGE
#define ICSC2_BDIV0                     _ICSC2.Bits.BDIV0
#define ICSC2_BDIV1                     _ICSC2.Bits.BDIV1
#define ICSC2_BDIV                      _ICSC2.MergedBits.grpBDIV

#define ICSC2_EREFSTEN_MASK             1U
#define ICSC2_ERCLKEN_MASK              2U
#define ICSC2_EREFS_MASK                4U
#define ICSC2_LP_MASK                   8U
#define ICSC2_HGO_MASK                  16U
#define ICSC2_RANGE_MASK                32U
#define ICSC2_BDIV0_MASK                64U
#define ICSC2_BDIV1_MASK                128U
#define ICSC2_BDIV_MASK                 192U
#define ICSC2_BDIV_BITNUM               6U


/*** ICSTRM - ICS Trim Register; 0x0000003A ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* ICS Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* ICS Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* ICS Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* ICS Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* ICS Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* ICS Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* ICS Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* ICS Trim Setting, bit 7 */
  } Bits;
} ICSTRMSTR;
extern volatile ICSTRMSTR _ICSTRM @0x0000003A;
#define ICSTRM                          _ICSTRM.Byte
#define ICSTRM_TRIM0                    _ICSTRM.Bits.TRIM0
#define ICSTRM_TRIM1                    _ICSTRM.Bits.TRIM1
#define ICSTRM_TRIM2                    _ICSTRM.Bits.TRIM2
#define ICSTRM_TRIM3                    _ICSTRM.Bits.TRIM3
#define ICSTRM_TRIM4                    _ICSTRM.Bits.TRIM4
#define ICSTRM_TRIM5                    _ICSTRM.Bits.TRIM5
#define ICSTRM_TRIM6                    _ICSTRM.Bits.TRIM6
#define ICSTRM_TRIM7                    _ICSTRM.Bits.TRIM7

#define ICSTRM_TRIM0_MASK               1U
#define ICSTRM_TRIM1_MASK               2U
#define ICSTRM_TRIM2_MASK               4U
#define ICSTRM_TRIM3_MASK               8U
#define ICSTRM_TRIM4_MASK               16U
#define ICSTRM_TRIM5_MASK               32U
#define ICSTRM_TRIM6_MASK               64U
#define ICSTRM_TRIM7_MASK               128U


/*** ICSSC - ICS Status and Control Register; 0x0000003B ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* ICS Fine Trim */
    byte OSCINIT     :1;                                       /* OSC Initialization */
    byte CLKST0      :1;                                       /* Clock Mode Status, bit 0 */
    byte CLKST1      :1;                                       /* Clock Mode Status, bit 1 */
    byte IREFST      :1;                                       /* Internal Reference Status */
    byte DMX32       :1;                                       /* DCO Maximum frequency with 32.768 kHz reference */
    byte DRST_DRS0   :1;                                       /* DCO Range Status/Range Select, bit 0 */
    byte DRST_DRS1   :1;                                       /* DCO Range Status/Range Select, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpCLKST :2;
    byte         :1;
    byte grpDMX_32 :1;
    byte grpDRST_DRS :2;
  } MergedBits;
} ICSSCSTR;
extern volatile ICSSCSTR _ICSSC @0x0000003B;
#define ICSSC                           _ICSSC.Byte
#define ICSSC_FTRIM                     _ICSSC.Bits.FTRIM
#define ICSSC_OSCINIT                   _ICSSC.Bits.OSCINIT
#define ICSSC_CLKST0                    _ICSSC.Bits.CLKST0
#define ICSSC_CLKST1                    _ICSSC.Bits.CLKST1
#define ICSSC_IREFST                    _ICSSC.Bits.IREFST
#define ICSSC_DMX32                     _ICSSC.Bits.DMX32
#define ICSSC_DRST_DRS0                 _ICSSC.Bits.DRST_DRS0
#define ICSSC_DRST_DRS1                 _ICSSC.Bits.DRST_DRS1
#define ICSSC_CLKST                     _ICSSC.MergedBits.grpCLKST
#define ICSSC_DRST_DRS                  _ICSSC.MergedBits.grpDRST_DRS

#define ICSSC_FTRIM_MASK                1U
#define ICSSC_OSCINIT_MASK              2U
#define ICSSC_CLKST0_MASK               4U
#define ICSSC_CLKST1_MASK               8U
#define ICSSC_IREFST_MASK               16U
#define ICSSC_DMX32_MASK                32U
#define ICSSC_DRST_DRS0_MASK            64U
#define ICSSC_DRST_DRS1_MASK            128U
#define ICSSC_CLKST_MASK                12U
#define ICSSC_CLKST_BITNUM              2U
#define ICSSC_DRST_DRS_MASK             192U
#define ICSSC_DRST_DRS_BITNUM           6U


/*** TPM1SC - TPM1 Status and Control Register; 0x00000040 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1SCSTR;
extern volatile TPM1SCSTR _TPM1SC @0x00000040;
#define TPM1SC                          _TPM1SC.Byte
#define TPM1SC_PS0                      _TPM1SC.Bits.PS0
#define TPM1SC_PS1                      _TPM1SC.Bits.PS1
#define TPM1SC_PS2                      _TPM1SC.Bits.PS2
#define TPM1SC_CLKSA                    _TPM1SC.Bits.CLKSA
#define TPM1SC_CLKSB                    _TPM1SC.Bits.CLKSB
#define TPM1SC_CPWMS                    _TPM1SC.Bits.CPWMS
#define TPM1SC_TOIE                     _TPM1SC.Bits.TOIE
#define TPM1SC_TOF                      _TPM1SC.Bits.TOF
#define TPM1SC_PS                       _TPM1SC.MergedBits.grpPS
#define TPM1SC_CLKSx                    _TPM1SC.MergedBits.grpCLKSx

#define TPM1SC_PS0_MASK                 1U
#define TPM1SC_PS1_MASK                 2U
#define TPM1SC_PS2_MASK                 4U
#define TPM1SC_CLKSA_MASK               8U
#define TPM1SC_CLKSB_MASK               16U
#define TPM1SC_CPWMS_MASK               32U
#define TPM1SC_TOIE_MASK                64U
#define TPM1SC_TOF_MASK                 128U
#define TPM1SC_PS_MASK                  7U
#define TPM1SC_PS_BITNUM                0U
#define TPM1SC_CLKSx_MASK               24U
#define TPM1SC_CLKSx_BITNUM             3U


/*** TPM1CNT - TPM1 Timer Counter Register; 0x00000041 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1CNTH - TPM1 Timer Counter Register High; 0x00000041 ***/
    union {
      byte Byte;
    } TPM1CNTHSTR;
    #define TPM1CNTH                    _TPM1CNT.Overlap_STR.TPM1CNTHSTR.Byte
    

    /*** TPM1CNTL - TPM1 Timer Counter Register Low; 0x00000042 ***/
    union {
      byte Byte;
    } TPM1CNTLSTR;
    #define TPM1CNTL                    _TPM1CNT.Overlap_STR.TPM1CNTLSTR.Byte
    
  } Overlap_STR;

} TPM1CNTSTR;
extern volatile TPM1CNTSTR _TPM1CNT @0x00000041;
#define TPM1CNT                         _TPM1CNT.Word


/*** TPM1MOD - TPM1 Timer Counter Modulo Register; 0x00000043 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1MODH - TPM1 Timer Counter Modulo Register High; 0x00000043 ***/
    union {
      byte Byte;
    } TPM1MODHSTR;
    #define TPM1MODH                    _TPM1MOD.Overlap_STR.TPM1MODHSTR.Byte
    

    /*** TPM1MODL - TPM1 Timer Counter Modulo Register Low; 0x00000044 ***/
    union {
      byte Byte;
    } TPM1MODLSTR;
    #define TPM1MODL                    _TPM1MOD.Overlap_STR.TPM1MODLSTR.Byte
    
  } Overlap_STR;

} TPM1MODSTR;
extern volatile TPM1MODSTR _TPM1MOD @0x00000043;
#define TPM1MOD                         _TPM1MOD.Word


/*** TPM1C0SC - TPM1 Timer Channel 0 Status and Control Register; 0x00000045 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C0SCSTR;
extern volatile TPM1C0SCSTR _TPM1C0SC @0x00000045;
#define TPM1C0SC                        _TPM1C0SC.Byte
#define TPM1C0SC_ELS0A                  _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELS0B                  _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MS0A                   _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MS0B                   _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CH0IE                  _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CH0F                   _TPM1C0SC.Bits.CH0F
#define TPM1C0SC_ELS0x                  _TPM1C0SC.MergedBits.grpELS0x
#define TPM1C0SC_MS0x                   _TPM1C0SC.MergedBits.grpMS0x

#define TPM1C0SC_ELS0A_MASK             4U
#define TPM1C0SC_ELS0B_MASK             8U
#define TPM1C0SC_MS0A_MASK              16U
#define TPM1C0SC_MS0B_MASK              32U
#define TPM1C0SC_CH0IE_MASK             64U
#define TPM1C0SC_CH0F_MASK              128U
#define TPM1C0SC_ELS0x_MASK             12U
#define TPM1C0SC_ELS0x_BITNUM           2U
#define TPM1C0SC_MS0x_MASK              48U
#define TPM1C0SC_MS0x_BITNUM            4U


/*** TPM1C0V - TPM1 Timer Channel 0 Value Register; 0x00000046 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C0VH - TPM1 Timer Channel 0 Value Register High; 0x00000046 ***/
    union {
      byte Byte;
    } TPM1C0VHSTR;
    #define TPM1C0VH                    _TPM1C0V.Overlap_STR.TPM1C0VHSTR.Byte
    

    /*** TPM1C0VL - TPM1 Timer Channel 0 Value Register Low; 0x00000047 ***/
    union {
      byte Byte;
    } TPM1C0VLSTR;
    #define TPM1C0VL                    _TPM1C0V.Overlap_STR.TPM1C0VLSTR.Byte
    
  } Overlap_STR;

} TPM1C0VSTR;
extern volatile TPM1C0VSTR _TPM1C0V @0x00000046;
#define TPM1C0V                         _TPM1C0V.Word


/*** TPM1C1SC - TPM1 Timer Channel 1 Status and Control Register; 0x00000048 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C1SCSTR;
extern volatile TPM1C1SCSTR _TPM1C1SC @0x00000048;
#define TPM1C1SC                        _TPM1C1SC.Byte
#define TPM1C1SC_ELS1A                  _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELS1B                  _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MS1A                   _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MS1B                   _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CH1IE                  _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CH1F                   _TPM1C1SC.Bits.CH1F
#define TPM1C1SC_ELS1x                  _TPM1C1SC.MergedBits.grpELS1x
#define TPM1C1SC_MS1x                   _TPM1C1SC.MergedBits.grpMS1x

#define TPM1C1SC_ELS1A_MASK             4U
#define TPM1C1SC_ELS1B_MASK             8U
#define TPM1C1SC_MS1A_MASK              16U
#define TPM1C1SC_MS1B_MASK              32U
#define TPM1C1SC_CH1IE_MASK             64U
#define TPM1C1SC_CH1F_MASK              128U
#define TPM1C1SC_ELS1x_MASK             12U
#define TPM1C1SC_ELS1x_BITNUM           2U
#define TPM1C1SC_MS1x_MASK              48U
#define TPM1C1SC_MS1x_BITNUM            4U


/*** TPM1C1V - TPM1 Timer Channel 1 Value Register; 0x00000049 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C1VH - TPM1 Timer Channel 1 Value Register High; 0x00000049 ***/
    union {
      byte Byte;
    } TPM1C1VHSTR;
    #define TPM1C1VH                    _TPM1C1V.Overlap_STR.TPM1C1VHSTR.Byte
    

    /*** TPM1C1VL - TPM1 Timer Channel 1 Value Register Low; 0x0000004A ***/
    union {
      byte Byte;
    } TPM1C1VLSTR;
    #define TPM1C1VL                    _TPM1C1V.Overlap_STR.TPM1C1VLSTR.Byte
    
  } Overlap_STR;

} TPM1C1VSTR;
extern volatile TPM1C1VSTR _TPM1C1V @0x00000049;
#define TPM1C1V                         _TPM1C1V.Word


/*** TPM2SC - TPM2 Status and Control Register; 0x00000050 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2SCSTR;
extern volatile TPM2SCSTR _TPM2SC @0x00000050;
#define TPM2SC                          _TPM2SC.Byte
#define TPM2SC_PS0                      _TPM2SC.Bits.PS0
#define TPM2SC_PS1                      _TPM2SC.Bits.PS1
#define TPM2SC_PS2                      _TPM2SC.Bits.PS2
#define TPM2SC_CLKSA                    _TPM2SC.Bits.CLKSA
#define TPM2SC_CLKSB                    _TPM2SC.Bits.CLKSB
#define TPM2SC_CPWMS                    _TPM2SC.Bits.CPWMS
#define TPM2SC_TOIE                     _TPM2SC.Bits.TOIE
#define TPM2SC_TOF                      _TPM2SC.Bits.TOF
#define TPM2SC_PS                       _TPM2SC.MergedBits.grpPS
#define TPM2SC_CLKSx                    _TPM2SC.MergedBits.grpCLKSx

#define TPM2SC_PS0_MASK                 1U
#define TPM2SC_PS1_MASK                 2U
#define TPM2SC_PS2_MASK                 4U
#define TPM2SC_CLKSA_MASK               8U
#define TPM2SC_CLKSB_MASK               16U
#define TPM2SC_CPWMS_MASK               32U
#define TPM2SC_TOIE_MASK                64U
#define TPM2SC_TOF_MASK                 128U
#define TPM2SC_PS_MASK                  7U
#define TPM2SC_PS_BITNUM                0U
#define TPM2SC_CLKSx_MASK               24U
#define TPM2SC_CLKSx_BITNUM             3U


/*** TPM2CNT - TPM2 Timer Counter Register; 0x00000051 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2CNTH - TPM2 Timer Counter Register High; 0x00000051 ***/
    union {
      byte Byte;
    } TPM2CNTHSTR;
    #define TPM2CNTH                    _TPM2CNT.Overlap_STR.TPM2CNTHSTR.Byte
    

    /*** TPM2CNTL - TPM2 Timer Counter Register Low; 0x00000052 ***/
    union {
      byte Byte;
    } TPM2CNTLSTR;
    #define TPM2CNTL                    _TPM2CNT.Overlap_STR.TPM2CNTLSTR.Byte
    
  } Overlap_STR;

} TPM2CNTSTR;
extern volatile TPM2CNTSTR _TPM2CNT @0x00000051;
#define TPM2CNT                         _TPM2CNT.Word


/*** TPM2MOD - TPM2 Timer Counter Modulo Register; 0x00000053 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2MODH - TPM2 Timer Counter Modulo Register High; 0x00000053 ***/
    union {
      byte Byte;
    } TPM2MODHSTR;
    #define TPM2MODH                    _TPM2MOD.Overlap_STR.TPM2MODHSTR.Byte
    

    /*** TPM2MODL - TPM2 Timer Counter Modulo Register Low; 0x00000054 ***/
    union {
      byte Byte;
    } TPM2MODLSTR;
    #define TPM2MODL                    _TPM2MOD.Overlap_STR.TPM2MODLSTR.Byte
    
  } Overlap_STR;

} TPM2MODSTR;
extern volatile TPM2MODSTR _TPM2MOD @0x00000053;
#define TPM2MOD                         _TPM2MOD.Word


/*** TPM2C0SC - TPM2 Timer Channel 0 Status and Control Register; 0x00000055 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C0SCSTR;
extern volatile TPM2C0SCSTR _TPM2C0SC @0x00000055;
#define TPM2C0SC                        _TPM2C0SC.Byte
#define TPM2C0SC_ELS0A                  _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELS0B                  _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MS0A                   _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MS0B                   _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CH0IE                  _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CH0F                   _TPM2C0SC.Bits.CH0F
#define TPM2C0SC_ELS0x                  _TPM2C0SC.MergedBits.grpELS0x
#define TPM2C0SC_MS0x                   _TPM2C0SC.MergedBits.grpMS0x

#define TPM2C0SC_ELS0A_MASK             4U
#define TPM2C0SC_ELS0B_MASK             8U
#define TPM2C0SC_MS0A_MASK              16U
#define TPM2C0SC_MS0B_MASK              32U
#define TPM2C0SC_CH0IE_MASK             64U
#define TPM2C0SC_CH0F_MASK              128U
#define TPM2C0SC_ELS0x_MASK             12U
#define TPM2C0SC_ELS0x_BITNUM           2U
#define TPM2C0SC_MS0x_MASK              48U
#define TPM2C0SC_MS0x_BITNUM            4U


/*** TPM2C0V - TPM2 Timer Channel 0 Value Register; 0x00000056 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C0VH - TPM2 Timer Channel 0 Value Register High; 0x00000056 ***/
    union {
      byte Byte;
    } TPM2C0VHSTR;
    #define TPM2C0VH                    _TPM2C0V.Overlap_STR.TPM2C0VHSTR.Byte
    

    /*** TPM2C0VL - TPM2 Timer Channel 0 Value Register Low; 0x00000057 ***/
    union {
      byte Byte;
    } TPM2C0VLSTR;
    #define TPM2C0VL                    _TPM2C0V.Overlap_STR.TPM2C0VLSTR.Byte
    
  } Overlap_STR;

} TPM2C0VSTR;
extern volatile TPM2C0VSTR _TPM2C0V @0x00000056;
#define TPM2C0V                         _TPM2C0V.Word


/*** TPM2C1SC - TPM2 Timer Channel 1 Status and Control Register; 0x00000058 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C1SCSTR;
extern volatile TPM2C1SCSTR _TPM2C1SC @0x00000058;
#define TPM2C1SC                        _TPM2C1SC.Byte
#define TPM2C1SC_ELS1A                  _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELS1B                  _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MS1A                   _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MS1B                   _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CH1IE                  _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CH1F                   _TPM2C1SC.Bits.CH1F
#define TPM2C1SC_ELS1x                  _TPM2C1SC.MergedBits.grpELS1x
#define TPM2C1SC_MS1x                   _TPM2C1SC.MergedBits.grpMS1x

#define TPM2C1SC_ELS1A_MASK             4U
#define TPM2C1SC_ELS1B_MASK             8U
#define TPM2C1SC_MS1A_MASK              16U
#define TPM2C1SC_MS1B_MASK              32U
#define TPM2C1SC_CH1IE_MASK             64U
#define TPM2C1SC_CH1F_MASK              128U
#define TPM2C1SC_ELS1x_MASK             12U
#define TPM2C1SC_ELS1x_BITNUM           2U
#define TPM2C1SC_MS1x_MASK              48U
#define TPM2C1SC_MS1x_BITNUM            4U


/*** TPM2C1V - TPM2 Timer Channel 1 Value Register; 0x00000059 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C1VH - TPM2 Timer Channel 1 Value Register High; 0x00000059 ***/
    union {
      byte Byte;
    } TPM2C1VHSTR;
    #define TPM2C1VH                    _TPM2C1V.Overlap_STR.TPM2C1VHSTR.Byte
    

    /*** TPM2C1VL - TPM2 Timer Channel 1 Value Register Low; 0x0000005A ***/
    union {
      byte Byte;
    } TPM2C1VLSTR;
    #define TPM2C1VL                    _TPM2C1V.Overlap_STR.TPM2C1VLSTR.Byte
    
  } Overlap_STR;

} TPM2C1VSTR;
extern volatile TPM2C1VSTR _TPM2C1V @0x00000059;
#define TPM2C1V                         _TPM2C1V.Word


/*** LCDPEN0 - LCD Pin Enable Register 0; 0x00000880 ***/
typedef union {
  byte Byte;
  struct {
    byte PEN0        :1;                                       /* Enable LCD pin 0 for LCD operation */
    byte PEN1        :1;                                       /* Enable LCD pin 1 for LCD operation */
    byte PEN2        :1;                                       /* Enable LCD pin 2 for LCD operation */
    byte PEN3        :1;                                       /* Enable LCD pin 3 for LCD operation */
    byte PEN4        :1;                                       /* Enable LCD pin 4 for LCD operation */
    byte PEN5        :1;                                       /* Enable LCD pin 5 for LCD operation */
    byte PEN6        :1;                                       /* Enable LCD pin 6 for LCD operation */
    byte PEN7        :1;                                       /* Enable LCD pin 7 for LCD operation */
  } Bits;
} LCDPEN0STR;
extern volatile LCDPEN0STR _LCDPEN0 @0x00000880;
#define LCDPEN0                         _LCDPEN0.Byte
#define LCDPEN0_PEN0                    _LCDPEN0.Bits.PEN0
#define LCDPEN0_PEN1                    _LCDPEN0.Bits.PEN1
#define LCDPEN0_PEN2                    _LCDPEN0.Bits.PEN2
#define LCDPEN0_PEN3                    _LCDPEN0.Bits.PEN3
#define LCDPEN0_PEN4                    _LCDPEN0.Bits.PEN4
#define LCDPEN0_PEN5                    _LCDPEN0.Bits.PEN5
#define LCDPEN0_PEN6                    _LCDPEN0.Bits.PEN6
#define LCDPEN0_PEN7                    _LCDPEN0.Bits.PEN7
/* LCDPEN_ARR: Access 4 LCDPENx registers in an array */
#define LCDPEN_ARR                      ((volatile byte * __far) &LCDPEN0)

#define LCDPEN0_PEN0_MASK               1U
#define LCDPEN0_PEN1_MASK               2U
#define LCDPEN0_PEN2_MASK               4U
#define LCDPEN0_PEN3_MASK               8U
#define LCDPEN0_PEN4_MASK               16U
#define LCDPEN0_PEN5_MASK               32U
#define LCDPEN0_PEN6_MASK               64U
#define LCDPEN0_PEN7_MASK               128U


/*** LCDPEN1 - LCD Pin Enable Register 1; 0x00000881 ***/
typedef union {
  byte Byte;
  struct {
    byte PEN8        :1;                                       /* Enable LCD pin 8 for LCD operation */
    byte PEN9        :1;                                       /* Enable LCD pin 9 for LCD operation */
    byte PEN10       :1;                                       /* Enable LCD pin 10 for LCD operation */
    byte PEN11       :1;                                       /* Enable LCD pin 11 for LCD operation */
    byte PEN12       :1;                                       /* Enable LCD pin 12 for LCD operation */
    byte PEN13       :1;                                       /* Enable LCD pin 13 for LCD operation */
    byte PEN14       :1;                                       /* Enable LCD pin 14 for LCD operation */
    byte PEN15       :1;                                       /* Enable LCD pin 15 for LCD operation */
  } Bits;
} LCDPEN1STR;
extern volatile LCDPEN1STR _LCDPEN1 @0x00000881;
#define LCDPEN1                         _LCDPEN1.Byte
#define LCDPEN1_PEN8                    _LCDPEN1.Bits.PEN8
#define LCDPEN1_PEN9                    _LCDPEN1.Bits.PEN9
#define LCDPEN1_PEN10                   _LCDPEN1.Bits.PEN10
#define LCDPEN1_PEN11                   _LCDPEN1.Bits.PEN11
#define LCDPEN1_PEN12                   _LCDPEN1.Bits.PEN12
#define LCDPEN1_PEN13                   _LCDPEN1.Bits.PEN13
#define LCDPEN1_PEN14                   _LCDPEN1.Bits.PEN14
#define LCDPEN1_PEN15                   _LCDPEN1.Bits.PEN15

#define LCDPEN1_PEN8_MASK               1U
#define LCDPEN1_PEN9_MASK               2U
#define LCDPEN1_PEN10_MASK              4U
#define LCDPEN1_PEN11_MASK              8U
#define LCDPEN1_PEN12_MASK              16U
#define LCDPEN1_PEN13_MASK              32U
#define LCDPEN1_PEN14_MASK              64U
#define LCDPEN1_PEN15_MASK              128U


/*** LCDPEN2 - LCD Pin Enable Register 2; 0x00000882 ***/
typedef union {
  byte Byte;
  struct {
    byte PEN16       :1;                                       /* Enable LCD pin 16 for LCD operation */
    byte PEN17       :1;                                       /* Enable LCD pin 17 for LCD operation */
    byte PEN18       :1;                                       /* Enable LCD pin 18 for LCD operation */
    byte PEN19       :1;                                       /* Enable LCD pin 19 for LCD operation */
    byte PEN20       :1;                                       /* Enable LCD pin 20 for LCD operation */
    byte PEN21       :1;                                       /* Enable LCD pin 21 for LCD operation */
    byte PEN22       :1;                                       /* Enable LCD pin 22 for LCD operation */
    byte PEN23       :1;                                       /* Enable LCD pin 23 for LCD operation */
  } Bits;
} LCDPEN2STR;
extern volatile LCDPEN2STR _LCDPEN2 @0x00000882;
#define LCDPEN2                         _LCDPEN2.Byte
#define LCDPEN2_PEN16                   _LCDPEN2.Bits.PEN16
#define LCDPEN2_PEN17                   _LCDPEN2.Bits.PEN17
#define LCDPEN2_PEN18                   _LCDPEN2.Bits.PEN18
#define LCDPEN2_PEN19                   _LCDPEN2.Bits.PEN19
#define LCDPEN2_PEN20                   _LCDPEN2.Bits.PEN20
#define LCDPEN2_PEN21                   _LCDPEN2.Bits.PEN21
#define LCDPEN2_PEN22                   _LCDPEN2.Bits.PEN22
#define LCDPEN2_PEN23                   _LCDPEN2.Bits.PEN23

#define LCDPEN2_PEN16_MASK              1U
#define LCDPEN2_PEN17_MASK              2U
#define LCDPEN2_PEN18_MASK              4U
#define LCDPEN2_PEN19_MASK              8U
#define LCDPEN2_PEN20_MASK              16U
#define LCDPEN2_PEN21_MASK              32U
#define LCDPEN2_PEN22_MASK              64U
#define LCDPEN2_PEN23_MASK              128U


/*** LCDPEN3 - LCD Pin Enable Register 3; 0x00000883 ***/
typedef union {
  byte Byte;
  struct {
    byte PEN24       :1;                                       /* Enable LCD pin 24 for LCD operation */
    byte PEN25       :1;                                       /* Enable LCD pin 25 for LCD operation */
    byte PEN26       :1;                                       /* Enable LCD pin 26 for LCD operation */
    byte PEN27       :1;                                       /* Enable LCD pin 27 for LCD operation */
    byte PEN28       :1;                                       /* Enable LCD pin 28 for LCD operation */
    byte PEN29       :1;                                       /* Enable LCD pin 29 for LCD operation */
    byte PEN30       :1;                                       /* Enable LCD pin 30 for LCD operation */
    byte PEN31       :1;                                       /* Enable LCD pin 31 for LCD operation */
  } Bits;
} LCDPEN3STR;
extern volatile LCDPEN3STR _LCDPEN3 @0x00000883;
#define LCDPEN3                         _LCDPEN3.Byte
#define LCDPEN3_PEN24                   _LCDPEN3.Bits.PEN24
#define LCDPEN3_PEN25                   _LCDPEN3.Bits.PEN25
#define LCDPEN3_PEN26                   _LCDPEN3.Bits.PEN26
#define LCDPEN3_PEN27                   _LCDPEN3.Bits.PEN27
#define LCDPEN3_PEN28                   _LCDPEN3.Bits.PEN28
#define LCDPEN3_PEN29                   _LCDPEN3.Bits.PEN29
#define LCDPEN3_PEN30                   _LCDPEN3.Bits.PEN30
#define LCDPEN3_PEN31                   _LCDPEN3.Bits.PEN31

#define LCDPEN3_PEN24_MASK              1U
#define LCDPEN3_PEN25_MASK              2U
#define LCDPEN3_PEN26_MASK              4U
#define LCDPEN3_PEN27_MASK              8U
#define LCDPEN3_PEN28_MASK              16U
#define LCDPEN3_PEN29_MASK              32U
#define LCDPEN3_PEN30_MASK              64U
#define LCDPEN3_PEN31_MASK              128U


/*** LCDBPEN0 - LCD Backplane Enable Register 0; 0x00000888 ***/
typedef union {
  byte Byte;
  struct {
    byte BPEN0       :1;                                       /* Enable LCD pin 0 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN1       :1;                                       /* Enable LCD pin 1 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN2       :1;                                       /* Enable LCD pin 2 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN3       :1;                                       /* Enable LCD pin 3 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN4       :1;                                       /* Enable LCD pin 4 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN5       :1;                                       /* Enable LCD pin 5 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN6       :1;                                       /* Enable LCD pin 6 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN7       :1;                                       /* Enable LCD pin 7 to operate as an LCD backplane or an LCD frontplane */
  } Bits;
} LCDBPEN0STR;
extern volatile LCDBPEN0STR _LCDBPEN0 @0x00000888;
#define LCDBPEN0                        _LCDBPEN0.Byte
#define LCDBPEN0_BPEN0                  _LCDBPEN0.Bits.BPEN0
#define LCDBPEN0_BPEN1                  _LCDBPEN0.Bits.BPEN1
#define LCDBPEN0_BPEN2                  _LCDBPEN0.Bits.BPEN2
#define LCDBPEN0_BPEN3                  _LCDBPEN0.Bits.BPEN3
#define LCDBPEN0_BPEN4                  _LCDBPEN0.Bits.BPEN4
#define LCDBPEN0_BPEN5                  _LCDBPEN0.Bits.BPEN5
#define LCDBPEN0_BPEN6                  _LCDBPEN0.Bits.BPEN6
#define LCDBPEN0_BPEN7                  _LCDBPEN0.Bits.BPEN7
/* LCDBPEN_ARR: Access 4 LCDBPENx registers in an array */
#define LCDBPEN_ARR                     ((volatile byte * __far) &LCDBPEN0)

#define LCDBPEN0_BPEN0_MASK             1U
#define LCDBPEN0_BPEN1_MASK             2U
#define LCDBPEN0_BPEN2_MASK             4U
#define LCDBPEN0_BPEN3_MASK             8U
#define LCDBPEN0_BPEN4_MASK             16U
#define LCDBPEN0_BPEN5_MASK             32U
#define LCDBPEN0_BPEN6_MASK             64U
#define LCDBPEN0_BPEN7_MASK             128U


/*** LCDBPEN1 - LCD Backplane Enable Register 1; 0x00000889 ***/
typedef union {
  byte Byte;
  struct {
    byte BPEN8       :1;                                       /* Enable LCD pin 8 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN9       :1;                                       /* Enable LCD pin 9 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN10      :1;                                       /* Enable LCD pin 10 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN11      :1;                                       /* Enable LCD pin 11 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN12      :1;                                       /* Enable LCD pin 12 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN13      :1;                                       /* Enable LCD pin 13 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN14      :1;                                       /* Enable LCD pin 14 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN15      :1;                                       /* Enable LCD pin 15 to operate as an LCD backplane or an LCD frontplane */
  } Bits;
} LCDBPEN1STR;
extern volatile LCDBPEN1STR _LCDBPEN1 @0x00000889;
#define LCDBPEN1                        _LCDBPEN1.Byte
#define LCDBPEN1_BPEN8                  _LCDBPEN1.Bits.BPEN8
#define LCDBPEN1_BPEN9                  _LCDBPEN1.Bits.BPEN9
#define LCDBPEN1_BPEN10                 _LCDBPEN1.Bits.BPEN10
#define LCDBPEN1_BPEN11                 _LCDBPEN1.Bits.BPEN11
#define LCDBPEN1_BPEN12                 _LCDBPEN1.Bits.BPEN12
#define LCDBPEN1_BPEN13                 _LCDBPEN1.Bits.BPEN13
#define LCDBPEN1_BPEN14                 _LCDBPEN1.Bits.BPEN14
#define LCDBPEN1_BPEN15                 _LCDBPEN1.Bits.BPEN15

#define LCDBPEN1_BPEN8_MASK             1U
#define LCDBPEN1_BPEN9_MASK             2U
#define LCDBPEN1_BPEN10_MASK            4U
#define LCDBPEN1_BPEN11_MASK            8U
#define LCDBPEN1_BPEN12_MASK            16U
#define LCDBPEN1_BPEN13_MASK            32U
#define LCDBPEN1_BPEN14_MASK            64U
#define LCDBPEN1_BPEN15_MASK            128U


/*** LCDBPEN2 - LCD Backplane Enable Register 2; 0x0000088A ***/
typedef union {
  byte Byte;
  struct {
    byte BPEN16      :1;                                       /* Enable LCD pin 16 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN17      :1;                                       /* Enable LCD pin 17 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN18      :1;                                       /* Enable LCD pin 18 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN19      :1;                                       /* Enable LCD pin 19 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN20      :1;                                       /* Enable LCD pin 20 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN21      :1;                                       /* Enable LCD pin 21 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN22      :1;                                       /* Enable LCD pin 22 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN23      :1;                                       /* Enable LCD pin 23 to operate as an LCD backplane or an LCD frontplane */
  } Bits;
} LCDBPEN2STR;
extern volatile LCDBPEN2STR _LCDBPEN2 @0x0000088A;
#define LCDBPEN2                        _LCDBPEN2.Byte
#define LCDBPEN2_BPEN16                 _LCDBPEN2.Bits.BPEN16
#define LCDBPEN2_BPEN17                 _LCDBPEN2.Bits.BPEN17
#define LCDBPEN2_BPEN18                 _LCDBPEN2.Bits.BPEN18
#define LCDBPEN2_BPEN19                 _LCDBPEN2.Bits.BPEN19
#define LCDBPEN2_BPEN20                 _LCDBPEN2.Bits.BPEN20
#define LCDBPEN2_BPEN21                 _LCDBPEN2.Bits.BPEN21
#define LCDBPEN2_BPEN22                 _LCDBPEN2.Bits.BPEN22
#define LCDBPEN2_BPEN23                 _LCDBPEN2.Bits.BPEN23

#define LCDBPEN2_BPEN16_MASK            1U
#define LCDBPEN2_BPEN17_MASK            2U
#define LCDBPEN2_BPEN18_MASK            4U
#define LCDBPEN2_BPEN19_MASK            8U
#define LCDBPEN2_BPEN20_MASK            16U
#define LCDBPEN2_BPEN21_MASK            32U
#define LCDBPEN2_BPEN22_MASK            64U
#define LCDBPEN2_BPEN23_MASK            128U


/*** LCDBPEN3 - LCD Backplane Enable Register 3; 0x0000088B ***/
typedef union {
  byte Byte;
  struct {
    byte BPEN24      :1;                                       /* Enable LCD pin 24 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN25      :1;                                       /* Enable LCD pin 25 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN26      :1;                                       /* Enable LCD pin 26 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN27      :1;                                       /* Enable LCD pin 27 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN28      :1;                                       /* Enable LCD pin 28 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN29      :1;                                       /* Enable LCD pin 29 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN30      :1;                                       /* Enable LCD pin 30 to operate as an LCD backplane or an LCD frontplane */
    byte BPEN31      :1;                                       /* Enable LCD pin 31 to operate as an LCD backplane or an LCD frontplane */
  } Bits;
} LCDBPEN3STR;
extern volatile LCDBPEN3STR _LCDBPEN3 @0x0000088B;
#define LCDBPEN3                        _LCDBPEN3.Byte
#define LCDBPEN3_BPEN24                 _LCDBPEN3.Bits.BPEN24
#define LCDBPEN3_BPEN25                 _LCDBPEN3.Bits.BPEN25
#define LCDBPEN3_BPEN26                 _LCDBPEN3.Bits.BPEN26
#define LCDBPEN3_BPEN27                 _LCDBPEN3.Bits.BPEN27
#define LCDBPEN3_BPEN28                 _LCDBPEN3.Bits.BPEN28
#define LCDBPEN3_BPEN29                 _LCDBPEN3.Bits.BPEN29
#define LCDBPEN3_BPEN30                 _LCDBPEN3.Bits.BPEN30
#define LCDBPEN3_BPEN31                 _LCDBPEN3.Bits.BPEN31

#define LCDBPEN3_BPEN24_MASK            1U
#define LCDBPEN3_BPEN25_MASK            2U
#define LCDBPEN3_BPEN26_MASK            4U
#define LCDBPEN3_BPEN27_MASK            8U
#define LCDBPEN3_BPEN28_MASK            16U
#define LCDBPEN3_BPEN29_MASK            32U
#define LCDBPEN3_BPEN30_MASK            64U
#define LCDBPEN3_BPEN31_MASK            128U


/*** LCDWF0 - LCD Waveform Register 0; 0x00000890 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD0     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF0STR;
extern volatile LCDWF0STR _LCDWF0 @0x00000890;
#define LCDWF0                          _LCDWF0.Byte
#define LCDWF0_BPALCD0                  _LCDWF0.Bits.BPALCD0
#define LCDWF0_BPBLCD0                  _LCDWF0.Bits.BPBLCD0
#define LCDWF0_BPCLCD0                  _LCDWF0.Bits.BPCLCD0
#define LCDWF0_BPDLCD0                  _LCDWF0.Bits.BPDLCD0
#define LCDWF0_BPELCD0                  _LCDWF0.Bits.BPELCD0
#define LCDWF0_BPFLCD0                  _LCDWF0.Bits.BPFLCD0
#define LCDWF0_BPGLCD0                  _LCDWF0.Bits.BPGLCD0
#define LCDWF0_BPHLCD0                  _LCDWF0.Bits.BPHLCD0
/* LCDWF_ARR: Access 32 LCDWFx registers in an array */
#define LCDWF_ARR                       ((volatile byte * __far) &LCDWF0)

#define LCDWF0_BPALCD0_MASK             1U
#define LCDWF0_BPBLCD0_MASK             2U
#define LCDWF0_BPCLCD0_MASK             4U
#define LCDWF0_BPDLCD0_MASK             8U
#define LCDWF0_BPELCD0_MASK             16U
#define LCDWF0_BPFLCD0_MASK             32U
#define LCDWF0_BPGLCD0_MASK             64U
#define LCDWF0_BPHLCD0_MASK             128U


/*** LCDWF1 - LCD Waveform Register 1; 0x00000891 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD1     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF1STR;
extern volatile LCDWF1STR _LCDWF1 @0x00000891;
#define LCDWF1                          _LCDWF1.Byte
#define LCDWF1_BPALCD1                  _LCDWF1.Bits.BPALCD1
#define LCDWF1_BPBLCD1                  _LCDWF1.Bits.BPBLCD1
#define LCDWF1_BPCLCD1                  _LCDWF1.Bits.BPCLCD1
#define LCDWF1_BPDLCD1                  _LCDWF1.Bits.BPDLCD1
#define LCDWF1_BPELCD1                  _LCDWF1.Bits.BPELCD1
#define LCDWF1_BPFLCD1                  _LCDWF1.Bits.BPFLCD1
#define LCDWF1_BPGLCD1                  _LCDWF1.Bits.BPGLCD1
#define LCDWF1_BPHLCD1                  _LCDWF1.Bits.BPHLCD1

#define LCDWF1_BPALCD1_MASK             1U
#define LCDWF1_BPBLCD1_MASK             2U
#define LCDWF1_BPCLCD1_MASK             4U
#define LCDWF1_BPDLCD1_MASK             8U
#define LCDWF1_BPELCD1_MASK             16U
#define LCDWF1_BPFLCD1_MASK             32U
#define LCDWF1_BPGLCD1_MASK             64U
#define LCDWF1_BPHLCD1_MASK             128U


/*** LCDWF2 - LCD Waveform Register 2; 0x00000892 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD2     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF2STR;
extern volatile LCDWF2STR _LCDWF2 @0x00000892;
#define LCDWF2                          _LCDWF2.Byte
#define LCDWF2_BPALCD2                  _LCDWF2.Bits.BPALCD2
#define LCDWF2_BPBLCD2                  _LCDWF2.Bits.BPBLCD2
#define LCDWF2_BPCLCD2                  _LCDWF2.Bits.BPCLCD2
#define LCDWF2_BPDLCD2                  _LCDWF2.Bits.BPDLCD2
#define LCDWF2_BPELCD2                  _LCDWF2.Bits.BPELCD2
#define LCDWF2_BPFLCD2                  _LCDWF2.Bits.BPFLCD2
#define LCDWF2_BPGLCD2                  _LCDWF2.Bits.BPGLCD2
#define LCDWF2_BPHLCD2                  _LCDWF2.Bits.BPHLCD2

#define LCDWF2_BPALCD2_MASK             1U
#define LCDWF2_BPBLCD2_MASK             2U
#define LCDWF2_BPCLCD2_MASK             4U
#define LCDWF2_BPDLCD2_MASK             8U
#define LCDWF2_BPELCD2_MASK             16U
#define LCDWF2_BPFLCD2_MASK             32U
#define LCDWF2_BPGLCD2_MASK             64U
#define LCDWF2_BPHLCD2_MASK             128U


/*** LCDWF3 - LCD Waveform Register 3; 0x00000893 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD3     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF3STR;
extern volatile LCDWF3STR _LCDWF3 @0x00000893;
#define LCDWF3                          _LCDWF3.Byte
#define LCDWF3_BPALCD3                  _LCDWF3.Bits.BPALCD3
#define LCDWF3_BPBLCD3                  _LCDWF3.Bits.BPBLCD3
#define LCDWF3_BPCLCD3                  _LCDWF3.Bits.BPCLCD3
#define LCDWF3_BPDLCD3                  _LCDWF3.Bits.BPDLCD3
#define LCDWF3_BPELCD3                  _LCDWF3.Bits.BPELCD3
#define LCDWF3_BPFLCD3                  _LCDWF3.Bits.BPFLCD3
#define LCDWF3_BPGLCD3                  _LCDWF3.Bits.BPGLCD3
#define LCDWF3_BPHLCD3                  _LCDWF3.Bits.BPHLCD3

#define LCDWF3_BPALCD3_MASK             1U
#define LCDWF3_BPBLCD3_MASK             2U
#define LCDWF3_BPCLCD3_MASK             4U
#define LCDWF3_BPDLCD3_MASK             8U
#define LCDWF3_BPELCD3_MASK             16U
#define LCDWF3_BPFLCD3_MASK             32U
#define LCDWF3_BPGLCD3_MASK             64U
#define LCDWF3_BPHLCD3_MASK             128U


/*** LCDWF4 - LCD Waveform Register 4; 0x00000894 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD4     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF4STR;
extern volatile LCDWF4STR _LCDWF4 @0x00000894;
#define LCDWF4                          _LCDWF4.Byte
#define LCDWF4_BPALCD4                  _LCDWF4.Bits.BPALCD4
#define LCDWF4_BPBLCD4                  _LCDWF4.Bits.BPBLCD4
#define LCDWF4_BPCLCD4                  _LCDWF4.Bits.BPCLCD4
#define LCDWF4_BPDLCD4                  _LCDWF4.Bits.BPDLCD4
#define LCDWF4_BPELCD4                  _LCDWF4.Bits.BPELCD4
#define LCDWF4_BPFLCD4                  _LCDWF4.Bits.BPFLCD4
#define LCDWF4_BPGLCD4                  _LCDWF4.Bits.BPGLCD4
#define LCDWF4_BPHLCD4                  _LCDWF4.Bits.BPHLCD4

#define LCDWF4_BPALCD4_MASK             1U
#define LCDWF4_BPBLCD4_MASK             2U
#define LCDWF4_BPCLCD4_MASK             4U
#define LCDWF4_BPDLCD4_MASK             8U
#define LCDWF4_BPELCD4_MASK             16U
#define LCDWF4_BPFLCD4_MASK             32U
#define LCDWF4_BPGLCD4_MASK             64U
#define LCDWF4_BPHLCD4_MASK             128U


/*** LCDWF5 - LCD Waveform Register 5; 0x00000895 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD5     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF5STR;
extern volatile LCDWF5STR _LCDWF5 @0x00000895;
#define LCDWF5                          _LCDWF5.Byte
#define LCDWF5_BPALCD5                  _LCDWF5.Bits.BPALCD5
#define LCDWF5_BPBLCD5                  _LCDWF5.Bits.BPBLCD5
#define LCDWF5_BPCLCD5                  _LCDWF5.Bits.BPCLCD5
#define LCDWF5_BPDLCD5                  _LCDWF5.Bits.BPDLCD5
#define LCDWF5_BPELCD5                  _LCDWF5.Bits.BPELCD5
#define LCDWF5_BPFLCD5                  _LCDWF5.Bits.BPFLCD5
#define LCDWF5_BPGLCD5                  _LCDWF5.Bits.BPGLCD5
#define LCDWF5_BPHLCD5                  _LCDWF5.Bits.BPHLCD5

#define LCDWF5_BPALCD5_MASK             1U
#define LCDWF5_BPBLCD5_MASK             2U
#define LCDWF5_BPCLCD5_MASK             4U
#define LCDWF5_BPDLCD5_MASK             8U
#define LCDWF5_BPELCD5_MASK             16U
#define LCDWF5_BPFLCD5_MASK             32U
#define LCDWF5_BPGLCD5_MASK             64U
#define LCDWF5_BPHLCD5_MASK             128U


/*** LCDWF6 - LCD Waveform Register 6; 0x00000896 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD6     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF6STR;
extern volatile LCDWF6STR _LCDWF6 @0x00000896;
#define LCDWF6                          _LCDWF6.Byte
#define LCDWF6_BPALCD6                  _LCDWF6.Bits.BPALCD6
#define LCDWF6_BPBLCD6                  _LCDWF6.Bits.BPBLCD6
#define LCDWF6_BPCLCD6                  _LCDWF6.Bits.BPCLCD6
#define LCDWF6_BPDLCD6                  _LCDWF6.Bits.BPDLCD6
#define LCDWF6_BPELCD6                  _LCDWF6.Bits.BPELCD6
#define LCDWF6_BPFLCD6                  _LCDWF6.Bits.BPFLCD6
#define LCDWF6_BPGLCD6                  _LCDWF6.Bits.BPGLCD6
#define LCDWF6_BPHLCD6                  _LCDWF6.Bits.BPHLCD6

#define LCDWF6_BPALCD6_MASK             1U
#define LCDWF6_BPBLCD6_MASK             2U
#define LCDWF6_BPCLCD6_MASK             4U
#define LCDWF6_BPDLCD6_MASK             8U
#define LCDWF6_BPELCD6_MASK             16U
#define LCDWF6_BPFLCD6_MASK             32U
#define LCDWF6_BPGLCD6_MASK             64U
#define LCDWF6_BPHLCD6_MASK             128U


/*** LCDWF7 - LCD Waveform Register 7; 0x00000897 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD7     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF7STR;
extern volatile LCDWF7STR _LCDWF7 @0x00000897;
#define LCDWF7                          _LCDWF7.Byte
#define LCDWF7_BPALCD7                  _LCDWF7.Bits.BPALCD7
#define LCDWF7_BPBLCD7                  _LCDWF7.Bits.BPBLCD7
#define LCDWF7_BPCLCD7                  _LCDWF7.Bits.BPCLCD7
#define LCDWF7_BPDLCD7                  _LCDWF7.Bits.BPDLCD7
#define LCDWF7_BPELCD7                  _LCDWF7.Bits.BPELCD7
#define LCDWF7_BPFLCD7                  _LCDWF7.Bits.BPFLCD7
#define LCDWF7_BPGLCD7                  _LCDWF7.Bits.BPGLCD7
#define LCDWF7_BPHLCD7                  _LCDWF7.Bits.BPHLCD7

#define LCDWF7_BPALCD7_MASK             1U
#define LCDWF7_BPBLCD7_MASK             2U
#define LCDWF7_BPCLCD7_MASK             4U
#define LCDWF7_BPDLCD7_MASK             8U
#define LCDWF7_BPELCD7_MASK             16U
#define LCDWF7_BPFLCD7_MASK             32U
#define LCDWF7_BPGLCD7_MASK             64U
#define LCDWF7_BPHLCD7_MASK             128U


/*** LCDWF8 - LCD Waveform Register 8; 0x00000898 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD8     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF8STR;
extern volatile LCDWF8STR _LCDWF8 @0x00000898;
#define LCDWF8                          _LCDWF8.Byte
#define LCDWF8_BPALCD8                  _LCDWF8.Bits.BPALCD8
#define LCDWF8_BPBLCD8                  _LCDWF8.Bits.BPBLCD8
#define LCDWF8_BPCLCD8                  _LCDWF8.Bits.BPCLCD8
#define LCDWF8_BPDLCD8                  _LCDWF8.Bits.BPDLCD8
#define LCDWF8_BPELCD8                  _LCDWF8.Bits.BPELCD8
#define LCDWF8_BPFLCD8                  _LCDWF8.Bits.BPFLCD8
#define LCDWF8_BPGLCD8                  _LCDWF8.Bits.BPGLCD8
#define LCDWF8_BPHLCD8                  _LCDWF8.Bits.BPHLCD8

#define LCDWF8_BPALCD8_MASK             1U
#define LCDWF8_BPBLCD8_MASK             2U
#define LCDWF8_BPCLCD8_MASK             4U
#define LCDWF8_BPDLCD8_MASK             8U
#define LCDWF8_BPELCD8_MASK             16U
#define LCDWF8_BPFLCD8_MASK             32U
#define LCDWF8_BPGLCD8_MASK             64U
#define LCDWF8_BPHLCD8_MASK             128U


/*** LCDWF9 - LCD Waveform Register 9; 0x00000899 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD9     :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF9STR;
extern volatile LCDWF9STR _LCDWF9 @0x00000899;
#define LCDWF9                          _LCDWF9.Byte
#define LCDWF9_BPALCD9                  _LCDWF9.Bits.BPALCD9
#define LCDWF9_BPBLCD9                  _LCDWF9.Bits.BPBLCD9
#define LCDWF9_BPCLCD9                  _LCDWF9.Bits.BPCLCD9
#define LCDWF9_BPDLCD9                  _LCDWF9.Bits.BPDLCD9
#define LCDWF9_BPELCD9                  _LCDWF9.Bits.BPELCD9
#define LCDWF9_BPFLCD9                  _LCDWF9.Bits.BPFLCD9
#define LCDWF9_BPGLCD9                  _LCDWF9.Bits.BPGLCD9
#define LCDWF9_BPHLCD9                  _LCDWF9.Bits.BPHLCD9

#define LCDWF9_BPALCD9_MASK             1U
#define LCDWF9_BPBLCD9_MASK             2U
#define LCDWF9_BPCLCD9_MASK             4U
#define LCDWF9_BPDLCD9_MASK             8U
#define LCDWF9_BPELCD9_MASK             16U
#define LCDWF9_BPFLCD9_MASK             32U
#define LCDWF9_BPGLCD9_MASK             64U
#define LCDWF9_BPHLCD9_MASK             128U


/*** LCDWF10 - LCD Waveform Register 10; 0x0000089A ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD10    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF10STR;
extern volatile LCDWF10STR _LCDWF10 @0x0000089A;
#define LCDWF10                         _LCDWF10.Byte
#define LCDWF10_BPALCD10                _LCDWF10.Bits.BPALCD10
#define LCDWF10_BPBLCD10                _LCDWF10.Bits.BPBLCD10
#define LCDWF10_BPCLCD10                _LCDWF10.Bits.BPCLCD10
#define LCDWF10_BPDLCD10                _LCDWF10.Bits.BPDLCD10
#define LCDWF10_BPELCD10                _LCDWF10.Bits.BPELCD10
#define LCDWF10_BPFLCD10                _LCDWF10.Bits.BPFLCD10
#define LCDWF10_BPGLCD10                _LCDWF10.Bits.BPGLCD10
#define LCDWF10_BPHLCD10                _LCDWF10.Bits.BPHLCD10

#define LCDWF10_BPALCD10_MASK           1U
#define LCDWF10_BPBLCD10_MASK           2U
#define LCDWF10_BPCLCD10_MASK           4U
#define LCDWF10_BPDLCD10_MASK           8U
#define LCDWF10_BPELCD10_MASK           16U
#define LCDWF10_BPFLCD10_MASK           32U
#define LCDWF10_BPGLCD10_MASK           64U
#define LCDWF10_BPHLCD10_MASK           128U


/*** LCDWF11 - LCD Waveform Register 11; 0x0000089B ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD11    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF11STR;
extern volatile LCDWF11STR _LCDWF11 @0x0000089B;
#define LCDWF11                         _LCDWF11.Byte
#define LCDWF11_BPALCD11                _LCDWF11.Bits.BPALCD11
#define LCDWF11_BPBLCD11                _LCDWF11.Bits.BPBLCD11
#define LCDWF11_BPCLCD11                _LCDWF11.Bits.BPCLCD11
#define LCDWF11_BPDLCD11                _LCDWF11.Bits.BPDLCD11
#define LCDWF11_BPELCD11                _LCDWF11.Bits.BPELCD11
#define LCDWF11_BPFLCD11                _LCDWF11.Bits.BPFLCD11
#define LCDWF11_BPGLCD11                _LCDWF11.Bits.BPGLCD11
#define LCDWF11_BPHLCD11                _LCDWF11.Bits.BPHLCD11

#define LCDWF11_BPALCD11_MASK           1U
#define LCDWF11_BPBLCD11_MASK           2U
#define LCDWF11_BPCLCD11_MASK           4U
#define LCDWF11_BPDLCD11_MASK           8U
#define LCDWF11_BPELCD11_MASK           16U
#define LCDWF11_BPFLCD11_MASK           32U
#define LCDWF11_BPGLCD11_MASK           64U
#define LCDWF11_BPHLCD11_MASK           128U


/*** LCDWF12 - LCD Waveform Register 12; 0x0000089C ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD12    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF12STR;
extern volatile LCDWF12STR _LCDWF12 @0x0000089C;
#define LCDWF12                         _LCDWF12.Byte
#define LCDWF12_BPALCD12                _LCDWF12.Bits.BPALCD12
#define LCDWF12_BPBLCD12                _LCDWF12.Bits.BPBLCD12
#define LCDWF12_BPCLCD12                _LCDWF12.Bits.BPCLCD12
#define LCDWF12_BPDLCD12                _LCDWF12.Bits.BPDLCD12
#define LCDWF12_BPELCD12                _LCDWF12.Bits.BPELCD12
#define LCDWF12_BPFLCD12                _LCDWF12.Bits.BPFLCD12
#define LCDWF12_BPGLCD12                _LCDWF12.Bits.BPGLCD12
#define LCDWF12_BPHLCD12                _LCDWF12.Bits.BPHLCD12

#define LCDWF12_BPALCD12_MASK           1U
#define LCDWF12_BPBLCD12_MASK           2U
#define LCDWF12_BPCLCD12_MASK           4U
#define LCDWF12_BPDLCD12_MASK           8U
#define LCDWF12_BPELCD12_MASK           16U
#define LCDWF12_BPFLCD12_MASK           32U
#define LCDWF12_BPGLCD12_MASK           64U
#define LCDWF12_BPHLCD12_MASK           128U


/*** LCDWF13 - LCD Waveform Register 13; 0x0000089D ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD13    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF13STR;
extern volatile LCDWF13STR _LCDWF13 @0x0000089D;
#define LCDWF13                         _LCDWF13.Byte
#define LCDWF13_BPALCD13                _LCDWF13.Bits.BPALCD13
#define LCDWF13_BPBLCD13                _LCDWF13.Bits.BPBLCD13
#define LCDWF13_BPCLCD13                _LCDWF13.Bits.BPCLCD13
#define LCDWF13_BPDLCD13                _LCDWF13.Bits.BPDLCD13
#define LCDWF13_BPELCD13                _LCDWF13.Bits.BPELCD13
#define LCDWF13_BPFLCD13                _LCDWF13.Bits.BPFLCD13
#define LCDWF13_BPGLCD13                _LCDWF13.Bits.BPGLCD13
#define LCDWF13_BPHLCD13                _LCDWF13.Bits.BPHLCD13

#define LCDWF13_BPALCD13_MASK           1U
#define LCDWF13_BPBLCD13_MASK           2U
#define LCDWF13_BPCLCD13_MASK           4U
#define LCDWF13_BPDLCD13_MASK           8U
#define LCDWF13_BPELCD13_MASK           16U
#define LCDWF13_BPFLCD13_MASK           32U
#define LCDWF13_BPGLCD13_MASK           64U
#define LCDWF13_BPHLCD13_MASK           128U


/*** LCDWF14 - LCD Waveform Register 14; 0x0000089E ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD14    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF14STR;
extern volatile LCDWF14STR _LCDWF14 @0x0000089E;
#define LCDWF14                         _LCDWF14.Byte
#define LCDWF14_BPALCD14                _LCDWF14.Bits.BPALCD14
#define LCDWF14_BPBLCD14                _LCDWF14.Bits.BPBLCD14
#define LCDWF14_BPCLCD14                _LCDWF14.Bits.BPCLCD14
#define LCDWF14_BPDLCD14                _LCDWF14.Bits.BPDLCD14
#define LCDWF14_BPELCD14                _LCDWF14.Bits.BPELCD14
#define LCDWF14_BPFLCD14                _LCDWF14.Bits.BPFLCD14
#define LCDWF14_BPGLCD14                _LCDWF14.Bits.BPGLCD14
#define LCDWF14_BPHLCD14                _LCDWF14.Bits.BPHLCD14

#define LCDWF14_BPALCD14_MASK           1U
#define LCDWF14_BPBLCD14_MASK           2U
#define LCDWF14_BPCLCD14_MASK           4U
#define LCDWF14_BPDLCD14_MASK           8U
#define LCDWF14_BPELCD14_MASK           16U
#define LCDWF14_BPFLCD14_MASK           32U
#define LCDWF14_BPGLCD14_MASK           64U
#define LCDWF14_BPHLCD14_MASK           128U


/*** LCDWF15 - LCD Waveform Register 15; 0x0000089F ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD15    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF15STR;
extern volatile LCDWF15STR _LCDWF15 @0x0000089F;
#define LCDWF15                         _LCDWF15.Byte
#define LCDWF15_BPALCD15                _LCDWF15.Bits.BPALCD15
#define LCDWF15_BPBLCD15                _LCDWF15.Bits.BPBLCD15
#define LCDWF15_BPCLCD15                _LCDWF15.Bits.BPCLCD15
#define LCDWF15_BPDLCD15                _LCDWF15.Bits.BPDLCD15
#define LCDWF15_BPELCD15                _LCDWF15.Bits.BPELCD15
#define LCDWF15_BPFLCD15                _LCDWF15.Bits.BPFLCD15
#define LCDWF15_BPGLCD15                _LCDWF15.Bits.BPGLCD15
#define LCDWF15_BPHLCD15                _LCDWF15.Bits.BPHLCD15

#define LCDWF15_BPALCD15_MASK           1U
#define LCDWF15_BPBLCD15_MASK           2U
#define LCDWF15_BPCLCD15_MASK           4U
#define LCDWF15_BPDLCD15_MASK           8U
#define LCDWF15_BPELCD15_MASK           16U
#define LCDWF15_BPFLCD15_MASK           32U
#define LCDWF15_BPGLCD15_MASK           64U
#define LCDWF15_BPHLCD15_MASK           128U


/*** LCDWF16 - LCD Waveform Register 16; 0x000008A0 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD16    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF16STR;
extern volatile LCDWF16STR _LCDWF16 @0x000008A0;
#define LCDWF16                         _LCDWF16.Byte
#define LCDWF16_BPALCD16                _LCDWF16.Bits.BPALCD16
#define LCDWF16_BPBLCD16                _LCDWF16.Bits.BPBLCD16
#define LCDWF16_BPCLCD16                _LCDWF16.Bits.BPCLCD16
#define LCDWF16_BPDLCD16                _LCDWF16.Bits.BPDLCD16
#define LCDWF16_BPELCD16                _LCDWF16.Bits.BPELCD16
#define LCDWF16_BPFLCD16                _LCDWF16.Bits.BPFLCD16
#define LCDWF16_BPGLCD16                _LCDWF16.Bits.BPGLCD16
#define LCDWF16_BPHLCD16                _LCDWF16.Bits.BPHLCD16

#define LCDWF16_BPALCD16_MASK           1U
#define LCDWF16_BPBLCD16_MASK           2U
#define LCDWF16_BPCLCD16_MASK           4U
#define LCDWF16_BPDLCD16_MASK           8U
#define LCDWF16_BPELCD16_MASK           16U
#define LCDWF16_BPFLCD16_MASK           32U
#define LCDWF16_BPGLCD16_MASK           64U
#define LCDWF16_BPHLCD16_MASK           128U


/*** LCDWF17 - LCD Waveform Register 17; 0x000008A1 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD17    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF17STR;
extern volatile LCDWF17STR _LCDWF17 @0x000008A1;
#define LCDWF17                         _LCDWF17.Byte
#define LCDWF17_BPALCD17                _LCDWF17.Bits.BPALCD17
#define LCDWF17_BPBLCD17                _LCDWF17.Bits.BPBLCD17
#define LCDWF17_BPCLCD17                _LCDWF17.Bits.BPCLCD17
#define LCDWF17_BPDLCD17                _LCDWF17.Bits.BPDLCD17
#define LCDWF17_BPELCD17                _LCDWF17.Bits.BPELCD17
#define LCDWF17_BPFLCD17                _LCDWF17.Bits.BPFLCD17
#define LCDWF17_BPGLCD17                _LCDWF17.Bits.BPGLCD17
#define LCDWF17_BPHLCD17                _LCDWF17.Bits.BPHLCD17

#define LCDWF17_BPALCD17_MASK           1U
#define LCDWF17_BPBLCD17_MASK           2U
#define LCDWF17_BPCLCD17_MASK           4U
#define LCDWF17_BPDLCD17_MASK           8U
#define LCDWF17_BPELCD17_MASK           16U
#define LCDWF17_BPFLCD17_MASK           32U
#define LCDWF17_BPGLCD17_MASK           64U
#define LCDWF17_BPHLCD17_MASK           128U


/*** LCDWF18 - LCD Waveform Register 18; 0x000008A2 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD18    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF18STR;
extern volatile LCDWF18STR _LCDWF18 @0x000008A2;
#define LCDWF18                         _LCDWF18.Byte
#define LCDWF18_BPALCD18                _LCDWF18.Bits.BPALCD18
#define LCDWF18_BPBLCD18                _LCDWF18.Bits.BPBLCD18
#define LCDWF18_BPCLCD18                _LCDWF18.Bits.BPCLCD18
#define LCDWF18_BPDLCD18                _LCDWF18.Bits.BPDLCD18
#define LCDWF18_BPELCD18                _LCDWF18.Bits.BPELCD18
#define LCDWF18_BPFLCD18                _LCDWF18.Bits.BPFLCD18
#define LCDWF18_BPGLCD18                _LCDWF18.Bits.BPGLCD18
#define LCDWF18_BPHLCD18                _LCDWF18.Bits.BPHLCD18

#define LCDWF18_BPALCD18_MASK           1U
#define LCDWF18_BPBLCD18_MASK           2U
#define LCDWF18_BPCLCD18_MASK           4U
#define LCDWF18_BPDLCD18_MASK           8U
#define LCDWF18_BPELCD18_MASK           16U
#define LCDWF18_BPFLCD18_MASK           32U
#define LCDWF18_BPGLCD18_MASK           64U
#define LCDWF18_BPHLCD18_MASK           128U


/*** LCDWF19 - LCD Waveform Register 19; 0x000008A3 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD19    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF19STR;
extern volatile LCDWF19STR _LCDWF19 @0x000008A3;
#define LCDWF19                         _LCDWF19.Byte
#define LCDWF19_BPALCD19                _LCDWF19.Bits.BPALCD19
#define LCDWF19_BPBLCD19                _LCDWF19.Bits.BPBLCD19
#define LCDWF19_BPCLCD19                _LCDWF19.Bits.BPCLCD19
#define LCDWF19_BPDLCD19                _LCDWF19.Bits.BPDLCD19
#define LCDWF19_BPELCD19                _LCDWF19.Bits.BPELCD19
#define LCDWF19_BPFLCD19                _LCDWF19.Bits.BPFLCD19
#define LCDWF19_BPGLCD19                _LCDWF19.Bits.BPGLCD19
#define LCDWF19_BPHLCD19                _LCDWF19.Bits.BPHLCD19

#define LCDWF19_BPALCD19_MASK           1U
#define LCDWF19_BPBLCD19_MASK           2U
#define LCDWF19_BPCLCD19_MASK           4U
#define LCDWF19_BPDLCD19_MASK           8U
#define LCDWF19_BPELCD19_MASK           16U
#define LCDWF19_BPFLCD19_MASK           32U
#define LCDWF19_BPGLCD19_MASK           64U
#define LCDWF19_BPHLCD19_MASK           128U


/*** LCDWF20 - LCD Waveform Register 20; 0x000008A4 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD20    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF20STR;
extern volatile LCDWF20STR _LCDWF20 @0x000008A4;
#define LCDWF20                         _LCDWF20.Byte
#define LCDWF20_BPALCD20                _LCDWF20.Bits.BPALCD20
#define LCDWF20_BPBLCD20                _LCDWF20.Bits.BPBLCD20
#define LCDWF20_BPCLCD20                _LCDWF20.Bits.BPCLCD20
#define LCDWF20_BPDLCD20                _LCDWF20.Bits.BPDLCD20
#define LCDWF20_BPELCD20                _LCDWF20.Bits.BPELCD20
#define LCDWF20_BPFLCD20                _LCDWF20.Bits.BPFLCD20
#define LCDWF20_BPGLCD20                _LCDWF20.Bits.BPGLCD20
#define LCDWF20_BPHLCD20                _LCDWF20.Bits.BPHLCD20

#define LCDWF20_BPALCD20_MASK           1U
#define LCDWF20_BPBLCD20_MASK           2U
#define LCDWF20_BPCLCD20_MASK           4U
#define LCDWF20_BPDLCD20_MASK           8U
#define LCDWF20_BPELCD20_MASK           16U
#define LCDWF20_BPFLCD20_MASK           32U
#define LCDWF20_BPGLCD20_MASK           64U
#define LCDWF20_BPHLCD20_MASK           128U


/*** LCDWF21 - LCD Waveform Register 21; 0x000008A5 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD21    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF21STR;
extern volatile LCDWF21STR _LCDWF21 @0x000008A5;
#define LCDWF21                         _LCDWF21.Byte
#define LCDWF21_BPALCD21                _LCDWF21.Bits.BPALCD21
#define LCDWF21_BPBLCD21                _LCDWF21.Bits.BPBLCD21
#define LCDWF21_BPCLCD21                _LCDWF21.Bits.BPCLCD21
#define LCDWF21_BPDLCD21                _LCDWF21.Bits.BPDLCD21
#define LCDWF21_BPELCD21                _LCDWF21.Bits.BPELCD21
#define LCDWF21_BPFLCD21                _LCDWF21.Bits.BPFLCD21
#define LCDWF21_BPGLCD21                _LCDWF21.Bits.BPGLCD21
#define LCDWF21_BPHLCD21                _LCDWF21.Bits.BPHLCD21

#define LCDWF21_BPALCD21_MASK           1U
#define LCDWF21_BPBLCD21_MASK           2U
#define LCDWF21_BPCLCD21_MASK           4U
#define LCDWF21_BPDLCD21_MASK           8U
#define LCDWF21_BPELCD21_MASK           16U
#define LCDWF21_BPFLCD21_MASK           32U
#define LCDWF21_BPGLCD21_MASK           64U
#define LCDWF21_BPHLCD21_MASK           128U


/*** LCDWF22 - LCD Waveform Register 22; 0x000008A6 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD22    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF22STR;
extern volatile LCDWF22STR _LCDWF22 @0x000008A6;
#define LCDWF22                         _LCDWF22.Byte
#define LCDWF22_BPALCD22                _LCDWF22.Bits.BPALCD22
#define LCDWF22_BPBLCD22                _LCDWF22.Bits.BPBLCD22
#define LCDWF22_BPCLCD22                _LCDWF22.Bits.BPCLCD22
#define LCDWF22_BPDLCD22                _LCDWF22.Bits.BPDLCD22
#define LCDWF22_BPELCD22                _LCDWF22.Bits.BPELCD22
#define LCDWF22_BPFLCD22                _LCDWF22.Bits.BPFLCD22
#define LCDWF22_BPGLCD22                _LCDWF22.Bits.BPGLCD22
#define LCDWF22_BPHLCD22                _LCDWF22.Bits.BPHLCD22

#define LCDWF22_BPALCD22_MASK           1U
#define LCDWF22_BPBLCD22_MASK           2U
#define LCDWF22_BPCLCD22_MASK           4U
#define LCDWF22_BPDLCD22_MASK           8U
#define LCDWF22_BPELCD22_MASK           16U
#define LCDWF22_BPFLCD22_MASK           32U
#define LCDWF22_BPGLCD22_MASK           64U
#define LCDWF22_BPHLCD22_MASK           128U


/*** LCDWF23 - LCD Waveform Register 23; 0x000008A7 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD23    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF23STR;
extern volatile LCDWF23STR _LCDWF23 @0x000008A7;
#define LCDWF23                         _LCDWF23.Byte
#define LCDWF23_BPALCD23                _LCDWF23.Bits.BPALCD23
#define LCDWF23_BPBLCD23                _LCDWF23.Bits.BPBLCD23
#define LCDWF23_BPCLCD23                _LCDWF23.Bits.BPCLCD23
#define LCDWF23_BPDLCD23                _LCDWF23.Bits.BPDLCD23
#define LCDWF23_BPELCD23                _LCDWF23.Bits.BPELCD23
#define LCDWF23_BPFLCD23                _LCDWF23.Bits.BPFLCD23
#define LCDWF23_BPGLCD23                _LCDWF23.Bits.BPGLCD23
#define LCDWF23_BPHLCD23                _LCDWF23.Bits.BPHLCD23

#define LCDWF23_BPALCD23_MASK           1U
#define LCDWF23_BPBLCD23_MASK           2U
#define LCDWF23_BPCLCD23_MASK           4U
#define LCDWF23_BPDLCD23_MASK           8U
#define LCDWF23_BPELCD23_MASK           16U
#define LCDWF23_BPFLCD23_MASK           32U
#define LCDWF23_BPGLCD23_MASK           64U
#define LCDWF23_BPHLCD23_MASK           128U


/*** LCDWF24 - LCD Waveform Register 24; 0x000008A8 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD24    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF24STR;
extern volatile LCDWF24STR _LCDWF24 @0x000008A8;
#define LCDWF24                         _LCDWF24.Byte
#define LCDWF24_BPALCD24                _LCDWF24.Bits.BPALCD24
#define LCDWF24_BPBLCD24                _LCDWF24.Bits.BPBLCD24
#define LCDWF24_BPCLCD24                _LCDWF24.Bits.BPCLCD24
#define LCDWF24_BPDLCD24                _LCDWF24.Bits.BPDLCD24
#define LCDWF24_BPELCD24                _LCDWF24.Bits.BPELCD24
#define LCDWF24_BPFLCD24                _LCDWF24.Bits.BPFLCD24
#define LCDWF24_BPGLCD24                _LCDWF24.Bits.BPGLCD24
#define LCDWF24_BPHLCD24                _LCDWF24.Bits.BPHLCD24

#define LCDWF24_BPALCD24_MASK           1U
#define LCDWF24_BPBLCD24_MASK           2U
#define LCDWF24_BPCLCD24_MASK           4U
#define LCDWF24_BPDLCD24_MASK           8U
#define LCDWF24_BPELCD24_MASK           16U
#define LCDWF24_BPFLCD24_MASK           32U
#define LCDWF24_BPGLCD24_MASK           64U
#define LCDWF24_BPHLCD24_MASK           128U


/*** LCDWF25 - LCD Waveform Register 25; 0x000008A9 ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD25    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF25STR;
extern volatile LCDWF25STR _LCDWF25 @0x000008A9;
#define LCDWF25                         _LCDWF25.Byte
#define LCDWF25_BPALCD25                _LCDWF25.Bits.BPALCD25
#define LCDWF25_BPBLCD25                _LCDWF25.Bits.BPBLCD25
#define LCDWF25_BPCLCD25                _LCDWF25.Bits.BPCLCD25
#define LCDWF25_BPDLCD25                _LCDWF25.Bits.BPDLCD25
#define LCDWF25_BPELCD25                _LCDWF25.Bits.BPELCD25
#define LCDWF25_BPFLCD25                _LCDWF25.Bits.BPFLCD25
#define LCDWF25_BPGLCD25                _LCDWF25.Bits.BPGLCD25
#define LCDWF25_BPHLCD25                _LCDWF25.Bits.BPHLCD25

#define LCDWF25_BPALCD25_MASK           1U
#define LCDWF25_BPBLCD25_MASK           2U
#define LCDWF25_BPCLCD25_MASK           4U
#define LCDWF25_BPDLCD25_MASK           8U
#define LCDWF25_BPELCD25_MASK           16U
#define LCDWF25_BPFLCD25_MASK           32U
#define LCDWF25_BPGLCD25_MASK           64U
#define LCDWF25_BPHLCD25_MASK           128U


/*** LCDWF26 - LCD Waveform Register 26; 0x000008AA ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD26    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF26STR;
extern volatile LCDWF26STR _LCDWF26 @0x000008AA;
#define LCDWF26                         _LCDWF26.Byte
#define LCDWF26_BPALCD26                _LCDWF26.Bits.BPALCD26
#define LCDWF26_BPBLCD26                _LCDWF26.Bits.BPBLCD26
#define LCDWF26_BPCLCD26                _LCDWF26.Bits.BPCLCD26
#define LCDWF26_BPDLCD26                _LCDWF26.Bits.BPDLCD26
#define LCDWF26_BPELCD26                _LCDWF26.Bits.BPELCD26
#define LCDWF26_BPFLCD26                _LCDWF26.Bits.BPFLCD26
#define LCDWF26_BPGLCD26                _LCDWF26.Bits.BPGLCD26
#define LCDWF26_BPHLCD26                _LCDWF26.Bits.BPHLCD26

#define LCDWF26_BPALCD26_MASK           1U
#define LCDWF26_BPBLCD26_MASK           2U
#define LCDWF26_BPCLCD26_MASK           4U
#define LCDWF26_BPDLCD26_MASK           8U
#define LCDWF26_BPELCD26_MASK           16U
#define LCDWF26_BPFLCD26_MASK           32U
#define LCDWF26_BPGLCD26_MASK           64U
#define LCDWF26_BPHLCD26_MASK           128U


/*** LCDWF27 - LCD Waveform Register 27; 0x000008AB ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD27    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF27STR;
extern volatile LCDWF27STR _LCDWF27 @0x000008AB;
#define LCDWF27                         _LCDWF27.Byte
#define LCDWF27_BPALCD27                _LCDWF27.Bits.BPALCD27
#define LCDWF27_BPBLCD27                _LCDWF27.Bits.BPBLCD27
#define LCDWF27_BPCLCD27                _LCDWF27.Bits.BPCLCD27
#define LCDWF27_BPDLCD27                _LCDWF27.Bits.BPDLCD27
#define LCDWF27_BPELCD27                _LCDWF27.Bits.BPELCD27
#define LCDWF27_BPFLCD27                _LCDWF27.Bits.BPFLCD27
#define LCDWF27_BPGLCD27                _LCDWF27.Bits.BPGLCD27
#define LCDWF27_BPHLCD27                _LCDWF27.Bits.BPHLCD27

#define LCDWF27_BPALCD27_MASK           1U
#define LCDWF27_BPBLCD27_MASK           2U
#define LCDWF27_BPCLCD27_MASK           4U
#define LCDWF27_BPDLCD27_MASK           8U
#define LCDWF27_BPELCD27_MASK           16U
#define LCDWF27_BPFLCD27_MASK           32U
#define LCDWF27_BPGLCD27_MASK           64U
#define LCDWF27_BPHLCD27_MASK           128U


/*** LCDWF28 - LCD Waveform Register 28; 0x000008AC ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD28    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF28STR;
extern volatile LCDWF28STR _LCDWF28 @0x000008AC;
#define LCDWF28                         _LCDWF28.Byte
#define LCDWF28_BPALCD28                _LCDWF28.Bits.BPALCD28
#define LCDWF28_BPBLCD28                _LCDWF28.Bits.BPBLCD28
#define LCDWF28_BPCLCD28                _LCDWF28.Bits.BPCLCD28
#define LCDWF28_BPDLCD28                _LCDWF28.Bits.BPDLCD28
#define LCDWF28_BPELCD28                _LCDWF28.Bits.BPELCD28
#define LCDWF28_BPFLCD28                _LCDWF28.Bits.BPFLCD28
#define LCDWF28_BPGLCD28                _LCDWF28.Bits.BPGLCD28
#define LCDWF28_BPHLCD28                _LCDWF28.Bits.BPHLCD28

#define LCDWF28_BPALCD28_MASK           1U
#define LCDWF28_BPBLCD28_MASK           2U
#define LCDWF28_BPCLCD28_MASK           4U
#define LCDWF28_BPDLCD28_MASK           8U
#define LCDWF28_BPELCD28_MASK           16U
#define LCDWF28_BPFLCD28_MASK           32U
#define LCDWF28_BPGLCD28_MASK           64U
#define LCDWF28_BPHLCD28_MASK           128U


/*** LCDWF29 - LCD Waveform Register 29; 0x000008AD ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD29    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF29STR;
extern volatile LCDWF29STR _LCDWF29 @0x000008AD;
#define LCDWF29                         _LCDWF29.Byte
#define LCDWF29_BPALCD29                _LCDWF29.Bits.BPALCD29
#define LCDWF29_BPBLCD29                _LCDWF29.Bits.BPBLCD29
#define LCDWF29_BPCLCD29                _LCDWF29.Bits.BPCLCD29
#define LCDWF29_BPDLCD29                _LCDWF29.Bits.BPDLCD29
#define LCDWF29_BPELCD29                _LCDWF29.Bits.BPELCD29
#define LCDWF29_BPFLCD29                _LCDWF29.Bits.BPFLCD29
#define LCDWF29_BPGLCD29                _LCDWF29.Bits.BPGLCD29
#define LCDWF29_BPHLCD29                _LCDWF29.Bits.BPHLCD29

#define LCDWF29_BPALCD29_MASK           1U
#define LCDWF29_BPBLCD29_MASK           2U
#define LCDWF29_BPCLCD29_MASK           4U
#define LCDWF29_BPDLCD29_MASK           8U
#define LCDWF29_BPELCD29_MASK           16U
#define LCDWF29_BPFLCD29_MASK           32U
#define LCDWF29_BPGLCD29_MASK           64U
#define LCDWF29_BPHLCD29_MASK           128U


/*** LCDWF30 - LCD Waveform Register 30; 0x000008AE ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD30    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF30STR;
extern volatile LCDWF30STR _LCDWF30 @0x000008AE;
#define LCDWF30                         _LCDWF30.Byte
#define LCDWF30_BPALCD30                _LCDWF30.Bits.BPALCD30
#define LCDWF30_BPBLCD30                _LCDWF30.Bits.BPBLCD30
#define LCDWF30_BPCLCD30                _LCDWF30.Bits.BPCLCD30
#define LCDWF30_BPDLCD30                _LCDWF30.Bits.BPDLCD30
#define LCDWF30_BPELCD30                _LCDWF30.Bits.BPELCD30
#define LCDWF30_BPFLCD30                _LCDWF30.Bits.BPFLCD30
#define LCDWF30_BPGLCD30                _LCDWF30.Bits.BPGLCD30
#define LCDWF30_BPHLCD30                _LCDWF30.Bits.BPHLCD30

#define LCDWF30_BPALCD30_MASK           1U
#define LCDWF30_BPBLCD30_MASK           2U
#define LCDWF30_BPCLCD30_MASK           4U
#define LCDWF30_BPDLCD30_MASK           8U
#define LCDWF30_BPELCD30_MASK           16U
#define LCDWF30_BPFLCD30_MASK           32U
#define LCDWF30_BPGLCD30_MASK           64U
#define LCDWF30_BPHLCD30_MASK           128U


/*** LCDWF31 - LCD Waveform Register 31; 0x000008AF ***/
typedef union {
  byte Byte;
  struct {
    byte BPALCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPBLCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPCLCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPDLCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPELCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPFLCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPGLCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
    byte BPHLCD31    :1;                                       /* Segment on/off Frontplane/Backplane Operation */
  } Bits;
} LCDWF31STR;
extern volatile LCDWF31STR _LCDWF31 @0x000008AF;
#define LCDWF31                         _LCDWF31.Byte
#define LCDWF31_BPALCD31                _LCDWF31.Bits.BPALCD31
#define LCDWF31_BPBLCD31                _LCDWF31.Bits.BPBLCD31
#define LCDWF31_BPCLCD31                _LCDWF31.Bits.BPCLCD31
#define LCDWF31_BPDLCD31                _LCDWF31.Bits.BPDLCD31
#define LCDWF31_BPELCD31                _LCDWF31.Bits.BPELCD31
#define LCDWF31_BPFLCD31                _LCDWF31.Bits.BPFLCD31
#define LCDWF31_BPGLCD31                _LCDWF31.Bits.BPGLCD31
#define LCDWF31_BPHLCD31                _LCDWF31.Bits.BPHLCD31

#define LCDWF31_BPALCD31_MASK           1U
#define LCDWF31_BPBLCD31_MASK           2U
#define LCDWF31_BPCLCD31_MASK           4U
#define LCDWF31_BPDLCD31_MASK           8U
#define LCDWF31_BPELCD31_MASK           16U
#define LCDWF31_BPFLCD31_MASK           32U
#define LCDWF31_BPGLCD31_MASK           64U
#define LCDWF31_BPHLCD31_MASK           128U


/*** SRS - System Reset Status Register; 0x00001800 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte LVD         :1;                                       /* Low Voltage Detect */
    byte             :1; 
    byte ILAD        :1;                                       /* Illegal Address */
    byte ILOP        :1;                                       /* Illegal Opcode */
    byte COP         :1;                                       /* Computer Operating Properly (COP) Watchdog */
    byte PIN         :1;                                       /* External Reset Pin */
    byte POR         :1;                                       /* Power-On Reset */
  } Bits;
} SRSSTR;
extern volatile SRSSTR _SRS @0x00001800;
#define SRS                             _SRS.Byte
#define SRS_LVD                         _SRS.Bits.LVD
#define SRS_ILAD                        _SRS.Bits.ILAD
#define SRS_ILOP                        _SRS.Bits.ILOP
#define SRS_COP                         _SRS.Bits.COP
#define SRS_PIN                         _SRS.Bits.PIN
#define SRS_POR                         _SRS.Bits.POR

#define SRS_LVD_MASK                    2U
#define SRS_ILAD_MASK                   8U
#define SRS_ILOP_MASK                   16U
#define SRS_COP_MASK                    32U
#define SRS_PIN_MASK                    64U
#define SRS_POR_MASK                    128U


/*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***/
typedef union {
  byte Byte;
  struct {
    byte BDFR        :1;                                       /* Background Debug Force Reset */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SBDFRSTR;
extern volatile SBDFRSTR _SBDFR @0x00001801;
#define SBDFR                           _SBDFR.Byte
#define SBDFR_BDFR                      _SBDFR.Bits.BDFR

#define SBDFR_BDFR_MASK                 1U


/*** SOPT1 - System Options Register 1; 0x00001802 ***/
typedef union {
  byte Byte;
  struct {
    byte RSTPE       :1;                                       /* RESET Pin Enable */
    byte BKGDPE      :1;                                       /* Background Debug Mode Pin Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte STOPE       :1;                                       /* Stop Mode Enable */
    byte COPT        :1;                                       /* COP Watchdog Timeout */
    byte COPE        :1;                                       /* COP Watchdog Enable */
  } Bits;
} SOPT1STR;
extern volatile SOPT1STR _SOPT1 @0x00001802;
#define SOPT1                           _SOPT1.Byte
#define SOPT1_RSTPE                     _SOPT1.Bits.RSTPE
#define SOPT1_BKGDPE                    _SOPT1.Bits.BKGDPE
#define SOPT1_STOPE                     _SOPT1.Bits.STOPE
#define SOPT1_COPT                      _SOPT1.Bits.COPT
#define SOPT1_COPE                      _SOPT1.Bits.COPE

#define SOPT1_RSTPE_MASK                1U
#define SOPT1_BKGDPE_MASK               2U
#define SOPT1_STOPE_MASK                32U
#define SOPT1_COPT_MASK                 64U
#define SOPT1_COPE_MASK                 128U


/*** SOPT2 - System Options Register 2; 0x00001803 ***/
typedef union {
  byte Byte;
  struct {
    byte ACIC        :1;                                       /* Analog Comparator to Input Capture Enable */
    byte IICPS       :1;                                       /* IIC Pin Select */
    byte SPIPS       :1;                                       /* SPI Pin Select */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte COPCLKS     :1;                                       /* COP Watchdog Clock Select */
  } Bits;
} SOPT2STR;
extern volatile SOPT2STR _SOPT2 @0x00001803;
#define SOPT2                           _SOPT2.Byte
#define SOPT2_ACIC                      _SOPT2.Bits.ACIC
#define SOPT2_IICPS                     _SOPT2.Bits.IICPS
#define SOPT2_SPIPS                     _SOPT2.Bits.SPIPS
#define SOPT2_COPCLKS                   _SOPT2.Bits.COPCLKS

#define SOPT2_ACIC_MASK                 1U
#define SOPT2_IICPS_MASK                2U
#define SOPT2_SPIPS_MASK                4U
#define SOPT2_COPCLKS_MASK              128U


/*** SDID - System Device Identification Register; 0x00001806 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SDIDH - System Device Identification Register High; 0x00001806 ***/
    union {
      byte Byte;
      struct {
        byte ID8         :1;                                       /* Part Identification Number, bit 8 */
        byte ID9         :1;                                       /* Part Identification Number, bit 9 */
        byte ID10        :1;                                       /* Part Identification Number, bit 10 */
        byte ID11        :1;                                       /* Part Identification Number, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpID_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SDIDHSTR;
    #define SDIDH                       _SDID.Overlap_STR.SDIDHSTR.Byte
    #define SDIDH_ID8                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID8
    #define SDIDH_ID9                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID9
    #define SDIDH_ID10                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID10
    #define SDIDH_ID11                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID11
    #define SDIDH_ID_8                  _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpID_8
    #define SDIDH_ID                    SDIDH_ID_8
    
    #define SDIDH_ID8_MASK              1U
    #define SDIDH_ID9_MASK              2U
    #define SDIDH_ID10_MASK             4U
    #define SDIDH_ID11_MASK             8U
    #define SDIDH_ID_8_MASK             15U
    #define SDIDH_ID_8_BITNUM           0U
    

    /*** SDIDL - System Device Identification Register Low; 0x00001807 ***/
    union {
      byte Byte;
      struct {
        byte ID0         :1;                                       /* Part Identification Number, bit 0 */
        byte ID1         :1;                                       /* Part Identification Number, bit 1 */
        byte ID2         :1;                                       /* Part Identification Number, bit 2 */
        byte ID3         :1;                                       /* Part Identification Number, bit 3 */
        byte ID4         :1;                                       /* Part Identification Number, bit 4 */
        byte ID5         :1;                                       /* Part Identification Number, bit 5 */
        byte ID6         :1;                                       /* Part Identification Number, bit 6 */
        byte ID7         :1;                                       /* Part Identification Number, bit 7 */
      } Bits;
    } SDIDLSTR;
    #define SDIDL                       _SDID.Overlap_STR.SDIDLSTR.Byte
    #define SDIDL_ID0                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID0
    #define SDIDL_ID1                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID1
    #define SDIDL_ID2                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID2
    #define SDIDL_ID3                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID3
    #define SDIDL_ID4                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID4
    #define SDIDL_ID5                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID5
    #define SDIDL_ID6                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID6
    #define SDIDL_ID7                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID7
    
    #define SDIDL_ID0_MASK              1U
    #define SDIDL_ID1_MASK              2U
    #define SDIDL_ID2_MASK              4U
    #define SDIDL_ID3_MASK              8U
    #define SDIDL_ID4_MASK              16U
    #define SDIDL_ID5_MASK              32U
    #define SDIDL_ID6_MASK              64U
    #define SDIDL_ID7_MASK              128U
    
  } Overlap_STR;

} SDIDSTR;
extern volatile SDIDSTR _SDID @0x00001806;
#define SDID                            _SDID.Word


/*** SPMSC1 - System Power Management Status and Control 1 Register; 0x00001808 ***/
typedef union {
  byte Byte;
  struct {
    byte BGBE        :1;                                       /* Bandgap Buffer Enable */
    byte             :1; 
    byte LVDE        :1;                                       /* Low-Voltage Detect Enable */
    byte LVDSE       :1;                                       /* Low-Voltage Detect Stop Enable */
    byte LVDRE       :1;                                       /* Low-Voltage Detect Reset Enable */
    byte LVDIE       :1;                                       /* Low-Voltage Detect Interrupt Enable */
    byte LVDACK      :1;                                       /* Low-Voltage Detect Acknowledge */
    byte LVDF        :1;                                       /* Low-Voltage Detect Flag */
  } Bits;
} SPMSC1STR;
extern volatile SPMSC1STR _SPMSC1 @0x00001808;
#define SPMSC1                          _SPMSC1.Byte
#define SPMSC1_BGBE                     _SPMSC1.Bits.BGBE
#define SPMSC1_LVDE                     _SPMSC1.Bits.LVDE
#define SPMSC1_LVDSE                    _SPMSC1.Bits.LVDSE
#define SPMSC1_LVDRE                    _SPMSC1.Bits.LVDRE
#define SPMSC1_LVDIE                    _SPMSC1.Bits.LVDIE
#define SPMSC1_LVDACK                   _SPMSC1.Bits.LVDACK
#define SPMSC1_LVDF                     _SPMSC1.Bits.LVDF

#define SPMSC1_BGBE_MASK                1U
#define SPMSC1_LVDE_MASK                4U
#define SPMSC1_LVDSE_MASK               8U
#define SPMSC1_LVDRE_MASK               16U
#define SPMSC1_LVDIE_MASK               32U
#define SPMSC1_LVDACK_MASK              64U
#define SPMSC1_LVDF_MASK                128U


/*** SPMSC2 - System Power Management Status and Control 2 Register; 0x00001809 ***/
typedef union {
  byte Byte;
  struct {
    byte PPDC        :1;                                       /* Partial Power Down Control */
    byte PPDE        :1;                                       /* Partial Power-Down Enable */
    byte PPDACK      :1;                                       /* Partial Power Down Acknowledge */
    byte PPDF        :1;                                       /* Partial Power Down Flag */
    byte             :1; 
    byte LPWUI       :1;                                       /* Low Power Wake Up on Interrupt */
    byte LPRS        :1;                                       /* Low Power Regulator Status */
    byte LPR         :1;                                       /* Low Power Regulator Control */
  } Bits;
} SPMSC2STR;
extern volatile SPMSC2STR _SPMSC2 @0x00001809;
#define SPMSC2                          _SPMSC2.Byte
#define SPMSC2_PPDC                     _SPMSC2.Bits.PPDC
#define SPMSC2_PPDE                     _SPMSC2.Bits.PPDE
#define SPMSC2_PPDACK                   _SPMSC2.Bits.PPDACK
#define SPMSC2_PPDF                     _SPMSC2.Bits.PPDF
#define SPMSC2_LPWUI                    _SPMSC2.Bits.LPWUI
#define SPMSC2_LPRS                     _SPMSC2.Bits.LPRS
#define SPMSC2_LPR                      _SPMSC2.Bits.LPR

#define SPMSC2_PPDC_MASK                1U
#define SPMSC2_PPDE_MASK                2U
#define SPMSC2_PPDACK_MASK              4U
#define SPMSC2_PPDF_MASK                8U
#define SPMSC2_LPWUI_MASK               32U
#define SPMSC2_LPRS_MASK                64U
#define SPMSC2_LPR_MASK                 128U


/*** SPMSC3 - System Power Management Status and Control 3 Register; 0x0000180B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte LVWIE       :1;                                       /* Low-Voltage Warning Interrupt Enable */
    byte             :1; 
    byte             :1; 
    byte LVWACK      :1;                                       /* Low-Voltage Warning Acknowledge */
    byte LVWF        :1;                                       /* Low-Voltage Warning Flag */
  } Bits;
} SPMSC3STR;
extern volatile SPMSC3STR _SPMSC3 @0x0000180B;
#define SPMSC3                          _SPMSC3.Byte
#define SPMSC3_LVWIE                    _SPMSC3.Bits.LVWIE
#define SPMSC3_LVWACK                   _SPMSC3.Bits.LVWACK
#define SPMSC3_LVWF                     _SPMSC3.Bits.LVWF

#define SPMSC3_LVWIE_MASK               8U
#define SPMSC3_LVWACK_MASK              64U
#define SPMSC3_LVWF_MASK                128U


/*** SCGC1 - System Clock Gating Control 1 Register; 0x0000180E ***/
typedef union {
  byte Byte;
  struct {
    byte SCI         :1;                                       /* SCI Clock Gate Control */
    byte             :1; 
    byte IIC         :1;                                       /* IIC Clock Gate Control */
    byte             :1; 
    byte ADC         :1;                                       /* ADC Clock Gate Control */
    byte TPM1        :1;                                       /* TPM1 Clock Gate Control */
    byte TPM2        :1;                                       /* TPM2 Clock Gate Control */
    byte             :1; 
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpTPM_1 :2;
    byte         :1;
  } MergedBits;
} SCGC1STR;
extern volatile SCGC1STR _SCGC1 @0x0000180E;
#define SCGC1                           _SCGC1.Byte
#define SCGC1_SCI                       _SCGC1.Bits.SCI
#define SCGC1_IIC                       _SCGC1.Bits.IIC
#define SCGC1_ADC                       _SCGC1.Bits.ADC
#define SCGC1_TPM1                      _SCGC1.Bits.TPM1
#define SCGC1_TPM2                      _SCGC1.Bits.TPM2
#define SCGC1_TPM_1                     _SCGC1.MergedBits.grpTPM_1
#define SCGC1_TPM                       SCGC1_TPM_1

#define SCGC1_SCI_MASK                  1U
#define SCGC1_IIC_MASK                  4U
#define SCGC1_ADC_MASK                  16U
#define SCGC1_TPM1_MASK                 32U
#define SCGC1_TPM2_MASK                 64U
#define SCGC1_TPM_1_MASK                96U
#define SCGC1_TPM_1_BITNUM              5U


/*** SCGC2 - System Clock Gating Control 2 Register; 0x0000180F ***/
typedef union {
  byte Byte;
  struct {
    byte SPI         :1;                                       /* SPI Clock Gate Control */
    byte LCD         :1;                                       /* LCD Clock Gate Control */
    byte TOD         :1;                                       /* TOD Clock Gate Control */
    byte ACMP        :1;                                       /* ACMP Clock Gate Control */
    byte KBI         :1;                                       /* KBI Clock Gate Control */
    byte IRQ         :1;                                       /* IRQ Clock Gate Control */
    byte FLS         :1;                                       /* FLASH Register Clock Gate Control */
    byte DBG         :1;                                       /* DBG Clock Gate Control */
  } Bits;
} SCGC2STR;
extern volatile SCGC2STR _SCGC2 @0x0000180F;
#define SCGC2                           _SCGC2.Byte
#define SCGC2_SPI                       _SCGC2.Bits.SPI
#define SCGC2_LCD                       _SCGC2.Bits.LCD
#define SCGC2_TOD                       _SCGC2.Bits.TOD
#define SCGC2_ACMP                      _SCGC2.Bits.ACMP
#define SCGC2_KBI                       _SCGC2.Bits.KBI
#define SCGC2_IRQ                       _SCGC2.Bits.IRQ
#define SCGC2_FLS                       _SCGC2.Bits.FLS
#define SCGC2_DBG                       _SCGC2.Bits.DBG

#define SCGC2_SPI_MASK                  1U
#define SCGC2_LCD_MASK                  2U
#define SCGC2_TOD_MASK                  4U
#define SCGC2_ACMP_MASK                 8U
#define SCGC2_KBI_MASK                  16U
#define SCGC2_IRQ_MASK                  32U
#define SCGC2_FLS_MASK                  64U
#define SCGC2_DBG_MASK                  128U


/*** DBGCA - Debug Comparator A Register; 0x00001810 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Comparator A High Compare Bit 8 */
        byte Bit9        :1;                                       /* Comparator A High Compare Bit 9 */
        byte Bit10       :1;                                       /* Comparator A High Compare Bit 10 */
        byte Bit11       :1;                                       /* Comparator A High Compare Bit 11 */
        byte Bit12       :1;                                       /* Comparator A High Compare Bit 12 */
        byte Bit13       :1;                                       /* Comparator A High Compare Bit 13 */
        byte Bit14       :1;                                       /* Comparator A High Compare Bit 14 */
        byte Bit15       :1;                                       /* Comparator A High Compare Bit 15 */
      } Bits;
    } DBGCAHSTR;
    #define DBGCAH                      _DBGCA.Overlap_STR.DBGCAHSTR.Byte
    #define DBGCAH_Bit8                 _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit8
    #define DBGCAH_Bit9                 _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit9
    #define DBGCAH_Bit10                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit10
    #define DBGCAH_Bit11                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit11
    #define DBGCAH_Bit12                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit12
    #define DBGCAH_Bit13                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit13
    #define DBGCAH_Bit14                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit14
    #define DBGCAH_Bit15                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit15
    
    #define DBGCAH_Bit8_MASK            1U
    #define DBGCAH_Bit9_MASK            2U
    #define DBGCAH_Bit10_MASK           4U
    #define DBGCAH_Bit11_MASK           8U
    #define DBGCAH_Bit12_MASK           16U
    #define DBGCAH_Bit13_MASK           32U
    #define DBGCAH_Bit14_MASK           64U
    #define DBGCAH_Bit15_MASK           128U
    

    /*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Comparator A Low Compare Bit 0 */
        byte Bit1        :1;                                       /* Comparator A Low Compare Bit 1 */
        byte Bit2        :1;                                       /* Comparator A Low Compare Bit 2 */
        byte Bit3        :1;                                       /* Comparator A Low Compare Bit 3 */
        byte Bit4        :1;                                       /* Comparator A Low Compare Bit 4 */
        byte Bit5        :1;                                       /* Comparator A Low Compare Bit 5 */
        byte Bit6        :1;                                       /* Comparator A Low Compare Bit 6 */
        byte Bit7        :1;                                       /* Comparator A Low Compare Bit 7 */
      } Bits;
    } DBGCALSTR;
    #define DBGCAL                      _DBGCA.Overlap_STR.DBGCALSTR.Byte
    #define DBGCAL_Bit0                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit0
    #define DBGCAL_Bit1                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit1
    #define DBGCAL_Bit2                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit2
    #define DBGCAL_Bit3                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit3
    #define DBGCAL_Bit4                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit4
    #define DBGCAL_Bit5                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit5
    #define DBGCAL_Bit6                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit6
    #define DBGCAL_Bit7                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit7
    
    #define DBGCAL_Bit0_MASK            1U
    #define DBGCAL_Bit1_MASK            2U
    #define DBGCAL_Bit2_MASK            4U
    #define DBGCAL_Bit3_MASK            8U
    #define DBGCAL_Bit4_MASK            16U
    #define DBGCAL_Bit5_MASK            32U
    #define DBGCAL_Bit6_MASK            64U
    #define DBGCAL_Bit7_MASK            128U
    
  } Overlap_STR;

} DBGCASTR;
extern volatile DBGCASTR _DBGCA @0x00001810;
#define DBGCA                           _DBGCA.Word


/*** DBGCB - Debug Comparator B Register; 0x00001812 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Comparator B High Compare Bit 8 */
        byte Bit9        :1;                                       /* Comparator B High Compare Bit 9 */
        byte Bit10       :1;                                       /* Comparator B High Compare Bit 10 */
        byte Bit11       :1;                                       /* Comparator B High Compare Bit 11 */
        byte Bit12       :1;                                       /* Comparator B High Compare Bit 12 */
        byte Bit13       :1;                                       /* Comparator B High Compare Bit 13 */
        byte Bit14       :1;                                       /* Comparator B High Compare Bit 14 */
        byte Bit15       :1;                                       /* Comparator B High Compare Bit 15 */
      } Bits;
    } DBGCBHSTR;
    #define DBGCBH                      _DBGCB.Overlap_STR.DBGCBHSTR.Byte
    #define DBGCBH_Bit8                 _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit8
    #define DBGCBH_Bit9                 _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit9
    #define DBGCBH_Bit10                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit10
    #define DBGCBH_Bit11                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit11
    #define DBGCBH_Bit12                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit12
    #define DBGCBH_Bit13                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit13
    #define DBGCBH_Bit14                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit14
    #define DBGCBH_Bit15                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit15
    
    #define DBGCBH_Bit8_MASK            1U
    #define DBGCBH_Bit9_MASK            2U
    #define DBGCBH_Bit10_MASK           4U
    #define DBGCBH_Bit11_MASK           8U
    #define DBGCBH_Bit12_MASK           16U
    #define DBGCBH_Bit13_MASK           32U
    #define DBGCBH_Bit14_MASK           64U
    #define DBGCBH_Bit15_MASK           128U
    

    /*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Comparator B Low Compare Bit 0 */
        byte Bit1        :1;                                       /* Comparator B Low Compare Bit 1 */
        byte Bit2        :1;                                       /* Comparator B Low Compare Bit 2 */
        byte Bit3        :1;                                       /* Comparator B Low Compare Bit 3 */
        byte Bit4        :1;                                       /* Comparator B Low Compare Bit 4 */
        byte Bit5        :1;                                       /* Comparator B Low Compare Bit 5 */
        byte Bit6        :1;                                       /* Comparator B Low Compare Bit 6 */
        byte Bit7        :1;                                       /* Comparator B Low Compare Bit 7 */
      } Bits;
    } DBGCBLSTR;
    #define DBGCBL                      _DBGCB.Overlap_STR.DBGCBLSTR.Byte
    #define DBGCBL_Bit0                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit0
    #define DBGCBL_Bit1                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit1
    #define DBGCBL_Bit2                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit2
    #define DBGCBL_Bit3                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit3
    #define DBGCBL_Bit4                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit4
    #define DBGCBL_Bit5                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit5
    #define DBGCBL_Bit6                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit6
    #define DBGCBL_Bit7                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit7
    
    #define DBGCBL_Bit0_MASK            1U
    #define DBGCBL_Bit1_MASK            2U
    #define DBGCBL_Bit2_MASK            4U
    #define DBGCBL_Bit3_MASK            8U
    #define DBGCBL_Bit4_MASK            16U
    #define DBGCBL_Bit5_MASK            32U
    #define DBGCBL_Bit6_MASK            64U
    #define DBGCBL_Bit7_MASK            128U
    
  } Overlap_STR;

} DBGCBSTR;
extern volatile DBGCBSTR _DBGCB @0x00001812;
#define DBGCB                           _DBGCB.Word


/*** DBGCC - Debug Comparator C Register; 0x00001814 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGCCH - Debug Comparator C High Register; 0x00001814 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Comparator C High Compare Bit 8 */
        byte Bit9        :1;                                       /* Comparator C High Compare Bit 9 */
        byte Bit10       :1;                                       /* Comparator C High Compare Bit 10 */
        byte Bit11       :1;                                       /* Comparator C High Compare Bit 11 */
        byte Bit12       :1;                                       /* Comparator C High Compare Bit 12 */
        byte Bit13       :1;                                       /* Comparator C High Compare Bit 13 */
        byte Bit14       :1;                                       /* Comparator C High Compare Bit 14 */
        byte Bit15       :1;                                       /* Comparator C High Compare Bit 15 */
      } Bits;
    } DBGCCHSTR;
    #define DBGCCH                      _DBGCC.Overlap_STR.DBGCCHSTR.Byte
    #define DBGCCH_Bit8                 _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit8
    #define DBGCCH_Bit9                 _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit9
    #define DBGCCH_Bit10                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit10
    #define DBGCCH_Bit11                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit11
    #define DBGCCH_Bit12                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit12
    #define DBGCCH_Bit13                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit13
    #define DBGCCH_Bit14                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit14
    #define DBGCCH_Bit15                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit15
    
    #define DBGCCH_Bit8_MASK            1U
    #define DBGCCH_Bit9_MASK            2U
    #define DBGCCH_Bit10_MASK           4U
    #define DBGCCH_Bit11_MASK           8U
    #define DBGCCH_Bit12_MASK           16U
    #define DBGCCH_Bit13_MASK           32U
    #define DBGCCH_Bit14_MASK           64U
    #define DBGCCH_Bit15_MASK           128U
    

    /*** DBGCCL - Debug Comparator C Low Register; 0x00001815 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Comparator C Low Compare Bit 0 */
        byte Bit1        :1;                                       /* Comparator C Low Compare Bit 1 */
        byte Bit2        :1;                                       /* Comparator C Low Compare Bit 2 */
        byte Bit3        :1;                                       /* Comparator C Low Compare Bit 3 */
        byte Bit4        :1;                                       /* Comparator C Low Compare Bit 4 */
        byte Bit5        :1;                                       /* Comparator C Low Compare Bit 5 */
        byte Bit6        :1;                                       /* Comparator C Low Compare Bit 6 */
        byte Bit7        :1;                                       /* Comparator C Low Compare Bit 7 */
      } Bits;
    } DBGCCLSTR;
    #define DBGCCL                      _DBGCC.Overlap_STR.DBGCCLSTR.Byte
    #define DBGCCL_Bit0                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit0
    #define DBGCCL_Bit1                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit1
    #define DBGCCL_Bit2                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit2
    #define DBGCCL_Bit3                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit3
    #define DBGCCL_Bit4                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit4
    #define DBGCCL_Bit5                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit5
    #define DBGCCL_Bit6                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit6
    #define DBGCCL_Bit7                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit7
    
    #define DBGCCL_Bit0_MASK            1U
    #define DBGCCL_Bit1_MASK            2U
    #define DBGCCL_Bit2_MASK            4U
    #define DBGCCL_Bit3_MASK            8U
    #define DBGCCL_Bit4_MASK            16U
    #define DBGCCL_Bit5_MASK            32U
    #define DBGCCL_Bit6_MASK            64U
    #define DBGCCL_Bit7_MASK            128U
    
  } Overlap_STR;

} DBGCCSTR;
extern volatile DBGCCSTR _DBGCC @0x00001814;
#define DBGCC                           _DBGCC.Word


/*** DBGF - Debug FIFO Register; 0x00001816 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGFH - Debug FIFO High Register; 0x00001816 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* FIFO High Data Bit 8 */
        byte Bit9        :1;                                       /* FIFO High Data Bit 9 */
        byte Bit10       :1;                                       /* FIFO High Data Bit 10 */
        byte Bit11       :1;                                       /* FIFO High Data Bit 11 */
        byte Bit12       :1;                                       /* FIFO High Data Bit 12 */
        byte Bit13       :1;                                       /* FIFO High Data Bit 13 */
        byte Bit14       :1;                                       /* FIFO High Data Bit 14 */
        byte Bit15       :1;                                       /* FIFO High Data Bit 15 */
      } Bits;
    } DBGFHSTR;
    #define DBGFH                       _DBGF.Overlap_STR.DBGFHSTR.Byte
    #define DBGFH_Bit8                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit8
    #define DBGFH_Bit9                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit9
    #define DBGFH_Bit10                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit10
    #define DBGFH_Bit11                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit11
    #define DBGFH_Bit12                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit12
    #define DBGFH_Bit13                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit13
    #define DBGFH_Bit14                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit14
    #define DBGFH_Bit15                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit15
    
    #define DBGFH_Bit8_MASK             1U
    #define DBGFH_Bit9_MASK             2U
    #define DBGFH_Bit10_MASK            4U
    #define DBGFH_Bit11_MASK            8U
    #define DBGFH_Bit12_MASK            16U
    #define DBGFH_Bit13_MASK            32U
    #define DBGFH_Bit14_MASK            64U
    #define DBGFH_Bit15_MASK            128U
    

    /*** DBGFL - Debug FIFO Low Register; 0x00001817 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* FIFO Low Data Bit 0 */
        byte Bit1        :1;                                       /* FIFO Low Data Bit 1 */
        byte Bit2        :1;                                       /* FIFO Low Data Bit 2 */
        byte Bit3        :1;                                       /* FIFO Low Data Bit 3 */
        byte Bit4        :1;                                       /* FIFO Low Data Bit 4 */
        byte Bit5        :1;                                       /* FIFO Low Data Bit 5 */
        byte Bit6        :1;                                       /* FIFO Low Data Bit 6 */
        byte Bit7        :1;                                       /* FIFO Low Data Bit 7 */
      } Bits;
    } DBGFLSTR;
    #define DBGFL                       _DBGF.Overlap_STR.DBGFLSTR.Byte
    #define DBGFL_Bit0                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit0
    #define DBGFL_Bit1                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit1
    #define DBGFL_Bit2                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit2
    #define DBGFL_Bit3                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit3
    #define DBGFL_Bit4                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit4
    #define DBGFL_Bit5                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit5
    #define DBGFL_Bit6                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit6
    #define DBGFL_Bit7                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit7
    
    #define DBGFL_Bit0_MASK             1U
    #define DBGFL_Bit1_MASK             2U
    #define DBGFL_Bit2_MASK             4U
    #define DBGFL_Bit3_MASK             8U
    #define DBGFL_Bit4_MASK             16U
    #define DBGFL_Bit5_MASK             32U
    #define DBGFL_Bit6_MASK             64U
    #define DBGFL_Bit7_MASK             128U
    
  } Overlap_STR;

} DBGFSTR;
extern volatile DBGFSTR _DBGF @0x00001816;
#define DBGF                            _DBGF.Word


/*** DBGCAX - Debug Comparator A Extension Register; 0x00001818 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte RWA         :1;                                       /* Read/Write Comparator A Value Bit */
    byte RWAEN       :1;                                       /* Read/Write Comparator A Enable Bit */
  } Bits;
} DBGCAXSTR;
extern volatile DBGCAXSTR _DBGCAX @0x00001818;
#define DBGCAX                          _DBGCAX.Byte
#define DBGCAX_RWA                      _DBGCAX.Bits.RWA
#define DBGCAX_RWAEN                    _DBGCAX.Bits.RWAEN

#define DBGCAX_RWA_MASK                 64U
#define DBGCAX_RWAEN_MASK               128U


/*** DBGCBX - Debug Comparator B Extension Register; 0x00001819 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte RWB         :1;                                       /* Read/Write Comparator B Value Bit */
    byte RWBEN       :1;                                       /* Read/Write Comparator B Enable Bit */
  } Bits;
} DBGCBXSTR;
extern volatile DBGCBXSTR _DBGCBX @0x00001819;
#define DBGCBX                          _DBGCBX.Byte
#define DBGCBX_RWB                      _DBGCBX.Bits.RWB
#define DBGCBX_RWBEN                    _DBGCBX.Bits.RWBEN

#define DBGCBX_RWB_MASK                 64U
#define DBGCBX_RWBEN_MASK               128U


/*** DBGCCX - Debug Comparator C Extension Register; 0x0000181A ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte RWC         :1;                                       /* Read/Write Comparator C Value Bit */
    byte RWCEN       :1;                                       /* Read/Write Comparator C Enable Bit */
  } Bits;
} DBGCCXSTR;
extern volatile DBGCCXSTR _DBGCCX @0x0000181A;
#define DBGCCX                          _DBGCCX.Byte
#define DBGCCX_RWC                      _DBGCCX.Bits.RWC
#define DBGCCX_RWCEN                    _DBGCCX.Bits.RWCEN

#define DBGCCX_RWC_MASK                 64U
#define DBGCCX_RWCEN_MASK               128U


/*** DBGC - Debug Control Register; 0x0000181C ***/
typedef union {
  byte Byte;
  struct {
    byte LOOP1       :1;                                       /* Select LOOP1 Capture Mode */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte BRKEN       :1;                                       /* Break Enable Bit */
    byte TAG         :1;                                       /* Tag or Force Bit */
    byte ARM         :1;                                       /* Arm Bit */
    byte DBGEN       :1;                                       /* DBG Module Enable Bit */
  } Bits;
} DBGCSTR;
extern volatile DBGCSTR _DBGC @0x0000181C;
#define DBGC                            _DBGC.Byte
#define DBGC_LOOP1                      _DBGC.Bits.LOOP1
#define DBGC_BRKEN                      _DBGC.Bits.BRKEN
#define DBGC_TAG                        _DBGC.Bits.TAG
#define DBGC_ARM                        _DBGC.Bits.ARM
#define DBGC_DBGEN                      _DBGC.Bits.DBGEN

#define DBGC_LOOP1_MASK                 1U
#define DBGC_BRKEN_MASK                 16U
#define DBGC_TAG_MASK                   32U
#define DBGC_ARM_MASK                   64U
#define DBGC_DBGEN_MASK                 128U


/*** DBGT - Debug Trigger Register; 0x0000181D ***/
typedef union {
  byte Byte;
  struct {
    byte TRG0        :1;                                       /* Trigger Mode Bit 0 */
    byte TRG1        :1;                                       /* Trigger Mode Bit 1 */
    byte TRG2        :1;                                       /* Trigger Mode Bit 2 */
    byte TRG3        :1;                                       /* Trigger Mode Bit 3 */
    byte             :1; 
    byte             :1; 
    byte BEGIN       :1;                                       /* Begin/End Trigger Bit */
    byte TRGSEL      :1;                                       /* Trigger Selection Bit */
  } Bits;
  struct {
    byte grpTRG  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGTSTR;
extern volatile DBGTSTR _DBGT @0x0000181D;
#define DBGT                            _DBGT.Byte
#define DBGT_TRG0                       _DBGT.Bits.TRG0
#define DBGT_TRG1                       _DBGT.Bits.TRG1
#define DBGT_TRG2                       _DBGT.Bits.TRG2
#define DBGT_TRG3                       _DBGT.Bits.TRG3
#define DBGT_BEGIN                      _DBGT.Bits.BEGIN
#define DBGT_TRGSEL                     _DBGT.Bits.TRGSEL
#define DBGT_TRG                        _DBGT.MergedBits.grpTRG

#define DBGT_TRG0_MASK                  1U
#define DBGT_TRG1_MASK                  2U
#define DBGT_TRG2_MASK                  4U
#define DBGT_TRG3_MASK                  8U
#define DBGT_BEGIN_MASK                 64U
#define DBGT_TRGSEL_MASK                128U
#define DBGT_TRG_MASK                   15U
#define DBGT_TRG_BITNUM                 0U


/*** DBGS - Debug Status Register; 0x0000181E ***/
typedef union {
  byte Byte;
  struct {
    byte ARMF        :1;                                       /* Arm Flag Bit */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte CF          :1;                                       /* Trigger C Match Bit */
    byte BF          :1;                                       /* Trigger B Match Bit */
    byte AF          :1;                                       /* Trigger A Match Bit */
  } Bits;
} DBGSSTR;
extern volatile DBGSSTR _DBGS @0x0000181E;
#define DBGS                            _DBGS.Byte
#define DBGS_ARMF                       _DBGS.Bits.ARMF
#define DBGS_CF                         _DBGS.Bits.CF
#define DBGS_BF                         _DBGS.Bits.BF
#define DBGS_AF                         _DBGS.Bits.AF

#define DBGS_ARMF_MASK                  1U
#define DBGS_CF_MASK                    32U
#define DBGS_BF_MASK                    64U
#define DBGS_AF_MASK                    128U


/*** DBGCNT - Debug Count Status Register; 0x0000181F ***/
typedef union {
  byte Byte;
  struct {
    byte CNT0        :1;                                       /* FIFO Valid Count Bits, bit 0 */
    byte CNT1        :1;                                       /* FIFO Valid Count Bits, bit 1 */
    byte CNT2        :1;                                       /* FIFO Valid Count Bits, bit 2 */
    byte CNT3        :1;                                       /* FIFO Valid Count Bits, bit 3 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpCNT  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGCNTSTR;
extern volatile DBGCNTSTR _DBGCNT @0x0000181F;
#define DBGCNT                          _DBGCNT.Byte
#define DBGCNT_CNT0                     _DBGCNT.Bits.CNT0
#define DBGCNT_CNT1                     _DBGCNT.Bits.CNT1
#define DBGCNT_CNT2                     _DBGCNT.Bits.CNT2
#define DBGCNT_CNT3                     _DBGCNT.Bits.CNT3
#define DBGCNT_CNT                      _DBGCNT.MergedBits.grpCNT

#define DBGCNT_CNT0_MASK                1U
#define DBGCNT_CNT1_MASK                2U
#define DBGCNT_CNT2_MASK                4U
#define DBGCNT_CNT3_MASK                8U
#define DBGCNT_CNT_MASK                 15U
#define DBGCNT_CNT_BITNUM               0U


/*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***/
typedef union {
  byte Byte;
  struct {
    byte DIV0        :1;                                       /* Divisor for FLASH Clock Divider, bit 0 */
    byte DIV1        :1;                                       /* Divisor for FLASH Clock Divider, bit 1 */
    byte DIV2        :1;                                       /* Divisor for FLASH Clock Divider, bit 2 */
    byte DIV3        :1;                                       /* Divisor for FLASH Clock Divider, bit 3 */
    byte DIV4        :1;                                       /* Divisor for FLASH Clock Divider, bit 4 */
    byte DIV5        :1;                                       /* Divisor for FLASH Clock Divider, bit 5 */
    byte PRDIV8      :1;                                       /* Prescale (Divide) FLASH Clock by 8 */
    byte DIVLD       :1;                                       /* Divisor Loaded Status Flag */
  } Bits;
  struct {
    byte grpDIV  :6;
    byte grpPRDIV_8 :1;
    byte         :1;
  } MergedBits;
} FCDIVSTR;
extern volatile FCDIVSTR _FCDIV @0x00001820;
#define FCDIV                           _FCDIV.Byte
#define FCDIV_DIV0                      _FCDIV.Bits.DIV0
#define FCDIV_DIV1                      _FCDIV.Bits.DIV1
#define FCDIV_DIV2                      _FCDIV.Bits.DIV2
#define FCDIV_DIV3                      _FCDIV.Bits.DIV3
#define FCDIV_DIV4                      _FCDIV.Bits.DIV4
#define FCDIV_DIV5                      _FCDIV.Bits.DIV5
#define FCDIV_PRDIV8                    _FCDIV.Bits.PRDIV8
#define FCDIV_DIVLD                     _FCDIV.Bits.DIVLD
#define FCDIV_DIV                       _FCDIV.MergedBits.grpDIV

#define FCDIV_DIV0_MASK                 1U
#define FCDIV_DIV1_MASK                 2U
#define FCDIV_DIV2_MASK                 4U
#define FCDIV_DIV3_MASK                 8U
#define FCDIV_DIV4_MASK                 16U
#define FCDIV_DIV5_MASK                 32U
#define FCDIV_PRDIV8_MASK               64U
#define FCDIV_DIVLD_MASK                128U
#define FCDIV_DIV_MASK                  63U
#define FCDIV_DIV_BITNUM                0U


/*** FOPT - FLASH Options Register; 0x00001821 ***/
typedef union {
  byte Byte;
  struct {
    byte SEC00       :1;                                       /* Security State Code, bit 0 */
    byte SEC01       :1;                                       /* Security State Code, bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte FNORED      :1;                                       /* Vector Redirection Disable */
    byte KEYEN       :1;                                       /* Backdoor Key Mechanism Enable */
  } Bits;
  struct {
    byte grpSEC0 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} FOPTSTR;
extern volatile FOPTSTR _FOPT @0x00001821;
#define FOPT                            _FOPT.Byte
#define FOPT_SEC00                      _FOPT.Bits.SEC00
#define FOPT_SEC01                      _FOPT.Bits.SEC01
#define FOPT_FNORED                     _FOPT.Bits.FNORED
#define FOPT_KEYEN                      _FOPT.Bits.KEYEN
#define FOPT_SEC0                       _FOPT.MergedBits.grpSEC0

#define FOPT_SEC00_MASK                 1U
#define FOPT_SEC01_MASK                 2U
#define FOPT_FNORED_MASK                64U
#define FOPT_KEYEN_MASK                 128U
#define FOPT_SEC0_MASK                  3U
#define FOPT_SEC0_BITNUM                0U


/*** FCNFG - FLASH Configuration Register; 0x00001823 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYACC      :1;                                       /* Enable Writing of Access Key */
    byte             :1; 
    byte             :1; 
  } Bits;
} FCNFGSTR;
extern volatile FCNFGSTR _FCNFG @0x00001823;
#define FCNFG                           _FCNFG.Byte
#define FCNFG_KEYACC                    _FCNFG.Bits.KEYACC

#define FCNFG_KEYACC_MASK               32U


/*** FPROT - FLASH Protection Register; 0x00001824 ***/
typedef union {
  byte Byte;
  struct {
    byte FPDIS       :1;                                       /* FLASH Protection Disable */
    byte FPS1        :1;                                       /* FLASH Protect Select Bit 1 */
    byte FPS2        :1;                                       /* FLASH Protect Select Bit 2 */
    byte FPS3        :1;                                       /* FLASH Protect Select Bit 3 */
    byte FPS4        :1;                                       /* FLASH Protect Select Bit 4 */
    byte FPS5        :1;                                       /* FLASH Protect Select Bit 5 */
    byte FPS6        :1;                                       /* FLASH Protect Select Bit 6 */
    byte FPS7        :1;                                       /* FLASH Protect Select Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS_1 :7;
  } MergedBits;
} FPROTSTR;
extern volatile FPROTSTR _FPROT @0x00001824;
#define FPROT                           _FPROT.Byte
#define FPROT_FPDIS                     _FPROT.Bits.FPDIS
#define FPROT_FPS1                      _FPROT.Bits.FPS1
#define FPROT_FPS2                      _FPROT.Bits.FPS2
#define FPROT_FPS3                      _FPROT.Bits.FPS3
#define FPROT_FPS4                      _FPROT.Bits.FPS4
#define FPROT_FPS5                      _FPROT.Bits.FPS5
#define FPROT_FPS6                      _FPROT.Bits.FPS6
#define FPROT_FPS7                      _FPROT.Bits.FPS7
#define FPROT_FPS_1                     _FPROT.MergedBits.grpFPS_1
#define FPROT_FPS                       FPROT_FPS_1

#define FPROT_FPDIS_MASK                1U
#define FPROT_FPS1_MASK                 2U
#define FPROT_FPS2_MASK                 4U
#define FPROT_FPS3_MASK                 8U
#define FPROT_FPS4_MASK                 16U
#define FPROT_FPS5_MASK                 32U
#define FPROT_FPS6_MASK                 64U
#define FPROT_FPS7_MASK                 128U
#define FPROT_FPS_1_MASK                254U
#define FPROT_FPS_1_BITNUM              1U


/*** FSTAT - Flash Status Register; 0x00001825 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte FBLANK      :1;                                       /* FLASH Flag Indicating the Erase Verify Operation Status */
    byte             :1; 
    byte FACCERR     :1;                                       /* FLASH Access Error Flag */
    byte FPVIOL      :1;                                       /* FLASH Protection Violation Flag */
    byte FCCF        :1;                                       /* FLASH Command Complete Interrupt Flag */
    byte FCBEF       :1;                                       /* FLASH Command Buffer Empty Flag */
  } Bits;
} FSTATSTR;
extern volatile FSTATSTR _FSTAT @0x00001825;
#define FSTAT                           _FSTAT.Byte
#define FSTAT_FBLANK                    _FSTAT.Bits.FBLANK
#define FSTAT_FACCERR                   _FSTAT.Bits.FACCERR
#define FSTAT_FPVIOL                    _FSTAT.Bits.FPVIOL
#define FSTAT_FCCF                      _FSTAT.Bits.FCCF
#define FSTAT_FCBEF                     _FSTAT.Bits.FCBEF

#define FSTAT_FBLANK_MASK               4U
#define FSTAT_FACCERR_MASK              16U
#define FSTAT_FPVIOL_MASK               32U
#define FSTAT_FCCF_MASK                 64U
#define FSTAT_FCBEF_MASK                128U


/*** FCMD - FLASH Command Register; 0x00001826 ***/
typedef union {
  byte Byte;
  struct {
    byte FCMD0       :1;                                       /* FLASH Command Bit 0 */
    byte FCMD1       :1;                                       /* FLASH Command Bit 1 */
    byte FCMD2       :1;                                       /* FLASH Command Bit 2 */
    byte FCMD3       :1;                                       /* FLASH Command Bit 3 */
    byte FCMD4       :1;                                       /* FLASH Command Bit 4 */
    byte FCMD5       :1;                                       /* FLASH Command Bit 5 */
    byte FCMD6       :1;                                       /* FLASH Command Bit 6 */
    byte FCMD7       :1;                                       /* FLASH Command Bit 7 */
  } Bits;
} FCMDSTR;
extern volatile FCMDSTR _FCMD @0x00001826;
#define FCMD                            _FCMD.Byte
#define FCMD_FCMD0                      _FCMD.Bits.FCMD0
#define FCMD_FCMD1                      _FCMD.Bits.FCMD1
#define FCMD_FCMD2                      _FCMD.Bits.FCMD2
#define FCMD_FCMD3                      _FCMD.Bits.FCMD3
#define FCMD_FCMD4                      _FCMD.Bits.FCMD4
#define FCMD_FCMD5                      _FCMD.Bits.FCMD5
#define FCMD_FCMD6                      _FCMD.Bits.FCMD6
#define FCMD_FCMD7                      _FCMD.Bits.FCMD7

#define FCMD_FCMD0_MASK                 1U
#define FCMD_FCMD1_MASK                 2U
#define FCMD_FCMD2_MASK                 4U
#define FCMD_FCMD3_MASK                 8U
#define FCMD_FCMD4_MASK                 16U
#define FCMD_FCMD5_MASK                 32U
#define FCMD_FCMD6_MASK                 64U
#define FCMD_FCMD7_MASK                 128U


/*** TODC - TOD Control Register; 0x00001830 ***/
typedef union {
  byte Byte;
  struct {
    byte TODPS0      :1;                                       /* TOD Prescaler Bits, bit 0 */
    byte TODPS1      :1;                                       /* TOD Prescaler Bits, bit 1 */
    byte TODPS2      :1;                                       /* TOD Prescaler Bits, bit 2 */
    byte TODCLKEN    :1;                                       /* TOD Clock Enable */
    byte TODR        :1;                                       /* TOD Reset */
    byte TODCLKS0    :1;                                       /* TOD Clock Source, bit 0 */
    byte TODCLKS1    :1;                                       /* TOD Clock Source, bit 1 */
    byte TODEN       :1;                                       /* Time of Day Enable */
  } Bits;
  struct {
    byte grpTODPS :3;
    byte         :1;
    byte         :1;
    byte grpTODCLKS :2;
    byte         :1;
  } MergedBits;
} TODCSTR;
extern volatile TODCSTR _TODC @0x00001830;
#define TODC                            _TODC.Byte
#define TODC_TODPS0                     _TODC.Bits.TODPS0
#define TODC_TODPS1                     _TODC.Bits.TODPS1
#define TODC_TODPS2                     _TODC.Bits.TODPS2
#define TODC_TODCLKEN                   _TODC.Bits.TODCLKEN
#define TODC_TODR                       _TODC.Bits.TODR
#define TODC_TODCLKS0                   _TODC.Bits.TODCLKS0
#define TODC_TODCLKS1                   _TODC.Bits.TODCLKS1
#define TODC_TODEN                      _TODC.Bits.TODEN
#define TODC_TODPS                      _TODC.MergedBits.grpTODPS
#define TODC_TODCLKS                    _TODC.MergedBits.grpTODCLKS

#define TODC_TODPS0_MASK                1U
#define TODC_TODPS1_MASK                2U
#define TODC_TODPS2_MASK                4U
#define TODC_TODCLKEN_MASK              8U
#define TODC_TODR_MASK                  16U
#define TODC_TODCLKS0_MASK              32U
#define TODC_TODCLKS1_MASK              64U
#define TODC_TODEN_MASK                 128U
#define TODC_TODPS_MASK                 7U
#define TODC_TODPS_BITNUM               0U
#define TODC_TODCLKS_MASK               96U
#define TODC_TODCLKS_BITNUM             5U


/*** TODSC - TOD Status and Control Register; 0x00001831 ***/
typedef union {
  byte Byte;
  struct {
    byte MTCHWC      :1;                                       /* Match Write Complete */
    byte MTCHEN      :1;                                       /* Match Function Enable */
    byte MTCHIE      :1;                                       /* Match Interrupt Enable */
    byte SECIE       :1;                                       /* Second Interrupt Enable */
    byte QSECIE      :1;                                       /* Quarter-Second Interrupt Enable */
    byte MTCHF       :1;                                       /* Match Interrupt Flag */
    byte SECF        :1;                                       /* Second Interrupt Flag */
    byte QSECF       :1;                                       /* Quarter-Second Interrupt Flag */
  } Bits;
} TODSCSTR;
extern volatile TODSCSTR _TODSC @0x00001831;
#define TODSC                           _TODSC.Byte
#define TODSC_MTCHWC                    _TODSC.Bits.MTCHWC
#define TODSC_MTCHEN                    _TODSC.Bits.MTCHEN
#define TODSC_MTCHIE                    _TODSC.Bits.MTCHIE
#define TODSC_SECIE                     _TODSC.Bits.SECIE
#define TODSC_QSECIE                    _TODSC.Bits.QSECIE
#define TODSC_MTCHF                     _TODSC.Bits.MTCHF
#define TODSC_SECF                      _TODSC.Bits.SECF
#define TODSC_QSECF                     _TODSC.Bits.QSECF

#define TODSC_MTCHWC_MASK               1U
#define TODSC_MTCHEN_MASK               2U
#define TODSC_MTCHIE_MASK               4U
#define TODSC_SECIE_MASK                8U
#define TODSC_QSECIE_MASK               16U
#define TODSC_MTCHF_MASK                32U
#define TODSC_SECF_MASK                 64U
#define TODSC_QSECF_MASK                128U


/*** TODM - TOD Match Register; 0x00001832 ***/
typedef union {
  byte Byte;
  struct {
    byte MQSEC0      :1;                                       /* Match Quarter-Second Bits, bit 0 */
    byte MQSEC1      :1;                                       /* Match Quarter-Second Bits, bit 1 */
    byte TODM0       :1;                                       /* TOD Match Value, bit 0 */
    byte TODM1       :1;                                       /* TOD Match Value, bit 1 */
    byte TODM2       :1;                                       /* TOD Match Value, bit 2 */
    byte TODM3       :1;                                       /* TOD Match Value, bit 3 */
    byte TODM4       :1;                                       /* TOD Match Value, bit 4 */
    byte TODM5       :1;                                       /* TOD Match Value, bit 5 */
  } Bits;
  struct {
    byte grpMQSEC :2;
    byte grpTODM :6;
  } MergedBits;
} TODMSTR;
extern volatile TODMSTR _TODM @0x00001832;
#define TODM                            _TODM.Byte
#define TODM_MQSEC0                     _TODM.Bits.MQSEC0
#define TODM_MQSEC1                     _TODM.Bits.MQSEC1
#define TODM_TODM0                      _TODM.Bits.TODM0
#define TODM_TODM1                      _TODM.Bits.TODM1
#define TODM_TODM2                      _TODM.Bits.TODM2
#define TODM_TODM3                      _TODM.Bits.TODM3
#define TODM_TODM4                      _TODM.Bits.TODM4
#define TODM_TODM5                      _TODM.Bits.TODM5
#define TODM_MQSEC                      _TODM.MergedBits.grpMQSEC
#define TODM_TODM                       _TODM.MergedBits.grpTODM

#define TODM_MQSEC0_MASK                1U
#define TODM_MQSEC1_MASK                2U
#define TODM_TODM0_MASK                 4U
#define TODM_TODM1_MASK                 8U
#define TODM_TODM2_MASK                 16U
#define TODM_TODM3_MASK                 32U
#define TODM_TODM4_MASK                 64U
#define TODM_TODM5_MASK                 128U
#define TODM_MQSEC_MASK                 3U
#define TODM_MQSEC_BITNUM               0U
#define TODM_TODM_MASK                  252U
#define TODM_TODM_BITNUM                2U


/*** TODCNT - TOD Counter Register; 0x00001833 ***/
typedef union {
  byte Byte;
} TODCNTSTR;
extern volatile TODCNTSTR _TODCNT @0x00001833;
#define TODCNT                          _TODCNT.Byte


/*** PTAPE - Port A Pull Enable Register; 0x00001840 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAPE0      :1;                                       /* Internal Pull Enable for Port A Bit 0 */
    byte PTAPE1      :1;                                       /* Internal Pull Enable for Port A Bit 1 */
    byte PTAPE2      :1;                                       /* Internal Pull Enable for Port A Bit 2 */
    byte PTAPE3      :1;                                       /* Internal Pull Enable for Port A Bit 3 */
    byte PTAPE4      :1;                                       /* Internal Pull Enable for Port A Bit 4 */
    byte PTAPE5      :1;                                       /* Internal Pull Enable for Port A Bit 5 */
    byte PTAPE6      :1;                                       /* Internal Pull Enable for Port A Bit 6 */
    byte PTAPE7      :1;                                       /* Internal Pull Enable for Port A Bit 7 */
  } Bits;
} PTAPESTR;
extern volatile PTAPESTR _PTAPE @0x00001840;
#define PTAPE                           _PTAPE.Byte
#define PTAPE_PTAPE0                    _PTAPE.Bits.PTAPE0
#define PTAPE_PTAPE1                    _PTAPE.Bits.PTAPE1
#define PTAPE_PTAPE2                    _PTAPE.Bits.PTAPE2
#define PTAPE_PTAPE3                    _PTAPE.Bits.PTAPE3
#define PTAPE_PTAPE4                    _PTAPE.Bits.PTAPE4
#define PTAPE_PTAPE5                    _PTAPE.Bits.PTAPE5
#define PTAPE_PTAPE6                    _PTAPE.Bits.PTAPE6
#define PTAPE_PTAPE7                    _PTAPE.Bits.PTAPE7

#define PTAPE_PTAPE0_MASK               1U
#define PTAPE_PTAPE1_MASK               2U
#define PTAPE_PTAPE2_MASK               4U
#define PTAPE_PTAPE3_MASK               8U
#define PTAPE_PTAPE4_MASK               16U
#define PTAPE_PTAPE5_MASK               32U
#define PTAPE_PTAPE6_MASK               64U
#define PTAPE_PTAPE7_MASK               128U


/*** PTASE - Port A Slew Rate Enable Register; 0x00001841 ***/
typedef union {
  byte Byte;
  struct {
    byte PTASE0      :1;                                       /* Output Slew Rate Enable for Port A Bit 0 */
    byte PTASE1      :1;                                       /* Output Slew Rate Enable for Port A Bit 1 */
    byte PTASE2      :1;                                       /* Output Slew Rate Enable for Port A Bit 2 */
    byte PTASE3      :1;                                       /* Output Slew Rate Enable for Port A Bit 3 */
    byte PTASE4      :1;                                       /* Output Slew Rate Enable for Port A Bit 4 */
    byte PTASE5      :1;                                       /* Output Slew Rate Enable for Port A Bit 5 */
    byte PTASE6      :1;                                       /* Output Slew Rate Enable for Port A Bit 6 */
    byte PTASE7      :1;                                       /* Output Slew Rate Enable for Port A Bit 7 */
  } Bits;
} PTASESTR;
extern volatile PTASESTR _PTASE @0x00001841;
#define PTASE                           _PTASE.Byte
#define PTASE_PTASE0                    _PTASE.Bits.PTASE0
#define PTASE_PTASE1                    _PTASE.Bits.PTASE1
#define PTASE_PTASE2                    _PTASE.Bits.PTASE2
#define PTASE_PTASE3                    _PTASE.Bits.PTASE3
#define PTASE_PTASE4                    _PTASE.Bits.PTASE4
#define PTASE_PTASE5                    _PTASE.Bits.PTASE5
#define PTASE_PTASE6                    _PTASE.Bits.PTASE6
#define PTASE_PTASE7                    _PTASE.Bits.PTASE7

#define PTASE_PTASE0_MASK               1U
#define PTASE_PTASE1_MASK               2U
#define PTASE_PTASE2_MASK               4U
#define PTASE_PTASE3_MASK               8U
#define PTASE_PTASE4_MASK               16U
#define PTASE_PTASE5_MASK               32U
#define PTASE_PTASE6_MASK               64U
#define PTASE_PTASE7_MASK               128U


/*** PTADS - Port A Drive Strength Selection Register; 0x00001842 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADS0      :1;                                       /* Output Drive Strength Selection for Port A Bit 0 */
    byte PTADS1      :1;                                       /* Output Drive Strength Selection for Port A Bit 1 */
    byte PTADS2      :1;                                       /* Output Drive Strength Selection for Port A Bit 2 */
    byte PTADS3      :1;                                       /* Output Drive Strength Selection for Port A Bit 3 */
    byte PTADS4      :1;                                       /* Output Drive Strength Selection for Port A Bit 4 */
    byte PTADS5      :1;                                       /* Output Drive Strength Selection for Port A Bit 5 */
    byte PTADS6      :1;                                       /* Output Drive Strength Selection for Port A Bit 6 */
    byte PTADS7      :1;                                       /* Output Drive Strength Selection for Port A Bit 7 */
  } Bits;
} PTADSSTR;
extern volatile PTADSSTR _PTADS @0x00001842;
#define PTADS                           _PTADS.Byte
#define PTADS_PTADS0                    _PTADS.Bits.PTADS0
#define PTADS_PTADS1                    _PTADS.Bits.PTADS1
#define PTADS_PTADS2                    _PTADS.Bits.PTADS2
#define PTADS_PTADS3                    _PTADS.Bits.PTADS3
#define PTADS_PTADS4                    _PTADS.Bits.PTADS4
#define PTADS_PTADS5                    _PTADS.Bits.PTADS5
#define PTADS_PTADS6                    _PTADS.Bits.PTADS6
#define PTADS_PTADS7                    _PTADS.Bits.PTADS7

#define PTADS_PTADS0_MASK               1U
#define PTADS_PTADS1_MASK               2U
#define PTADS_PTADS2_MASK               4U
#define PTADS_PTADS3_MASK               8U
#define PTADS_PTADS4_MASK               16U
#define PTADS_PTADS5_MASK               32U
#define PTADS_PTADS6_MASK               64U
#define PTADS_PTADS7_MASK               128U


/*** PTBPE - Port B Pull Enable Register; 0x00001844 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBPE0      :1;                                       /* Internal Pull Enable for Port B Bit 0 */
    byte PTBPE1      :1;                                       /* Internal Pull Enable for Port B Bit 1 */
    byte PTBPE2      :1;                                       /* Internal Pull Enable for Port B Bit 2 */
    byte PTBPE3      :1;                                       /* Internal Pull Enable for Port B Bit 3 */
    byte PTBPE4      :1;                                       /* Internal Pull Enable for Port B Bit 4 */
    byte PTBPE5      :1;                                       /* Internal Pull Enable for Port B Bit 5 */
    byte PTBPE6      :1;                                       /* Internal Pull Enable for Port B Bit 6 */
    byte PTBPE7      :1;                                       /* Internal Pull Enable for Port B Bit 7 */
  } Bits;
} PTBPESTR;
extern volatile PTBPESTR _PTBPE @0x00001844;
#define PTBPE                           _PTBPE.Byte
#define PTBPE_PTBPE0                    _PTBPE.Bits.PTBPE0
#define PTBPE_PTBPE1                    _PTBPE.Bits.PTBPE1
#define PTBPE_PTBPE2                    _PTBPE.Bits.PTBPE2
#define PTBPE_PTBPE3                    _PTBPE.Bits.PTBPE3
#define PTBPE_PTBPE4                    _PTBPE.Bits.PTBPE4
#define PTBPE_PTBPE5                    _PTBPE.Bits.PTBPE5
#define PTBPE_PTBPE6                    _PTBPE.Bits.PTBPE6
#define PTBPE_PTBPE7                    _PTBPE.Bits.PTBPE7

#define PTBPE_PTBPE0_MASK               1U
#define PTBPE_PTBPE1_MASK               2U
#define PTBPE_PTBPE2_MASK               4U
#define PTBPE_PTBPE3_MASK               8U
#define PTBPE_PTBPE4_MASK               16U
#define PTBPE_PTBPE5_MASK               32U
#define PTBPE_PTBPE6_MASK               64U
#define PTBPE_PTBPE7_MASK               128U


/*** PTBSE - Port B Slew Rate Enable Register; 0x00001845 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBSE0      :1;                                       /* Output Slew Rate Enable for Port B Bit 0 */
    byte PTBSE1      :1;                                       /* Output Slew Rate Enable for Port B Bit 1 */
    byte PTBSE2      :1;                                       /* Output Slew Rate Enable for Port B Bit 2 */
    byte PTBSE3      :1;                                       /* Output Slew Rate Enable for Port B Bit 3 */
    byte PTBSE4      :1;                                       /* Output Slew Rate Enable for Port B Bit 4 */
    byte PTBSE5      :1;                                       /* Output Slew Rate Enable for Port B Bit 5 */
    byte PTBSE6      :1;                                       /* Output Slew Rate Enable for Port B Bit 6 */
    byte PTBSE7      :1;                                       /* Output Slew Rate Enable for Port B Bit 7 */
  } Bits;
} PTBSESTR;
extern volatile PTBSESTR _PTBSE @0x00001845;
#define PTBSE                           _PTBSE.Byte
#define PTBSE_PTBSE0                    _PTBSE.Bits.PTBSE0
#define PTBSE_PTBSE1                    _PTBSE.Bits.PTBSE1
#define PTBSE_PTBSE2                    _PTBSE.Bits.PTBSE2
#define PTBSE_PTBSE3                    _PTBSE.Bits.PTBSE3
#define PTBSE_PTBSE4                    _PTBSE.Bits.PTBSE4
#define PTBSE_PTBSE5                    _PTBSE.Bits.PTBSE5
#define PTBSE_PTBSE6                    _PTBSE.Bits.PTBSE6
#define PTBSE_PTBSE7                    _PTBSE.Bits.PTBSE7

#define PTBSE_PTBSE0_MASK               1U
#define PTBSE_PTBSE1_MASK               2U
#define PTBSE_PTBSE2_MASK               4U
#define PTBSE_PTBSE3_MASK               8U
#define PTBSE_PTBSE4_MASK               16U
#define PTBSE_PTBSE5_MASK               32U
#define PTBSE_PTBSE6_MASK               64U
#define PTBSE_PTBSE7_MASK               128U


/*** PTBDS - Port B Drive Strength Selection Register; 0x00001846 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDS0      :1;                                       /* Output Drive Strength Selection for Port B Bit 0 */
    byte PTBDS1      :1;                                       /* Output Drive Strength Selection for Port B Bit 1 */
    byte PTBDS2      :1;                                       /* Output Drive Strength Selection for Port B Bit 2 */
    byte PTBDS3      :1;                                       /* Output Drive Strength Selection for Port B Bit 3 */
    byte PTBDS4      :1;                                       /* Output Drive Strength Selection for Port B Bit 4 */
    byte PTBDS5      :1;                                       /* Output Drive Strength Selection for Port B Bit 5 */
    byte PTBDS6      :1;                                       /* Output Drive Strength Selection for Port B Bit 6 */
    byte PTBDS7      :1;                                       /* Output Drive Strength Selection for Port B Bit 7 */
  } Bits;
} PTBDSSTR;
extern volatile PTBDSSTR _PTBDS @0x00001846;
#define PTBDS                           _PTBDS.Byte
#define PTBDS_PTBDS0                    _PTBDS.Bits.PTBDS0
#define PTBDS_PTBDS1                    _PTBDS.Bits.PTBDS1
#define PTBDS_PTBDS2                    _PTBDS.Bits.PTBDS2
#define PTBDS_PTBDS3                    _PTBDS.Bits.PTBDS3
#define PTBDS_PTBDS4                    _PTBDS.Bits.PTBDS4
#define PTBDS_PTBDS5                    _PTBDS.Bits.PTBDS5
#define PTBDS_PTBDS6                    _PTBDS.Bits.PTBDS6
#define PTBDS_PTBDS7                    _PTBDS.Bits.PTBDS7

#define PTBDS_PTBDS0_MASK               1U
#define PTBDS_PTBDS1_MASK               2U
#define PTBDS_PTBDS2_MASK               4U
#define PTBDS_PTBDS3_MASK               8U
#define PTBDS_PTBDS4_MASK               16U
#define PTBDS_PTBDS5_MASK               32U
#define PTBDS_PTBDS6_MASK               64U
#define PTBDS_PTBDS7_MASK               128U


/*** PTCPE - Port C Pull Enable Register; 0x00001848 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCPE0      :1;                                       /* Internal Pull Enable for Port C Bit 0 */
    byte PTCPE1      :1;                                       /* Internal Pull Enable for Port C Bit 1 */
    byte PTCPE2      :1;                                       /* Internal Pull Enable for Port C Bit 2 */
    byte PTCPE3      :1;                                       /* Internal Pull Enable for Port C Bit 3 */
    byte PTCPE4      :1;                                       /* Internal Pull Enable for Port C Bit 4 */
    byte PTCPE5      :1;                                       /* Internal Pull Enable for Port C Bit 5 */
    byte PTCPE6      :1;                                       /* Internal Pull Enable for Port C Bit 6 */
    byte PTCPE7      :1;                                       /* Internal Pull Enable for Port C Bit 7 */
  } Bits;
} PTCPESTR;
extern volatile PTCPESTR _PTCPE @0x00001848;
#define PTCPE                           _PTCPE.Byte
#define PTCPE_PTCPE0                    _PTCPE.Bits.PTCPE0
#define PTCPE_PTCPE1                    _PTCPE.Bits.PTCPE1
#define PTCPE_PTCPE2                    _PTCPE.Bits.PTCPE2
#define PTCPE_PTCPE3                    _PTCPE.Bits.PTCPE3
#define PTCPE_PTCPE4                    _PTCPE.Bits.PTCPE4
#define PTCPE_PTCPE5                    _PTCPE.Bits.PTCPE5
#define PTCPE_PTCPE6                    _PTCPE.Bits.PTCPE6
#define PTCPE_PTCPE7                    _PTCPE.Bits.PTCPE7

#define PTCPE_PTCPE0_MASK               1U
#define PTCPE_PTCPE1_MASK               2U
#define PTCPE_PTCPE2_MASK               4U
#define PTCPE_PTCPE3_MASK               8U
#define PTCPE_PTCPE4_MASK               16U
#define PTCPE_PTCPE5_MASK               32U
#define PTCPE_PTCPE6_MASK               64U
#define PTCPE_PTCPE7_MASK               128U


/*** PTCSE - Port C Slew Rate Enable Register; 0x00001849 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCSE0      :1;                                       /* Output Slew Rate Enable for Port C Bit 0 */
    byte PTCSE1      :1;                                       /* Output Slew Rate Enable for Port C Bit 1 */
    byte PTCSE2      :1;                                       /* Output Slew Rate Enable for Port C Bit 2 */
    byte PTCSE3      :1;                                       /* Output Slew Rate Enable for Port C Bit 3 */
    byte PTCSE4      :1;                                       /* Output Slew Rate Enable for Port C Bit 4 */
    byte PTCSE5      :1;                                       /* Output Slew Rate Enable for Port C Bit 5 */
    byte PTCSE6      :1;                                       /* Output Slew Rate Enable for Port C Bit 6 */
    byte PTCSE7      :1;                                       /* Output Slew Rate Enable for Port C Bit 7 */
  } Bits;
} PTCSESTR;
extern volatile PTCSESTR _PTCSE @0x00001849;
#define PTCSE                           _PTCSE.Byte
#define PTCSE_PTCSE0                    _PTCSE.Bits.PTCSE0
#define PTCSE_PTCSE1                    _PTCSE.Bits.PTCSE1
#define PTCSE_PTCSE2                    _PTCSE.Bits.PTCSE2
#define PTCSE_PTCSE3                    _PTCSE.Bits.PTCSE3
#define PTCSE_PTCSE4                    _PTCSE.Bits.PTCSE4
#define PTCSE_PTCSE5                    _PTCSE.Bits.PTCSE5
#define PTCSE_PTCSE6                    _PTCSE.Bits.PTCSE6
#define PTCSE_PTCSE7                    _PTCSE.Bits.PTCSE7

#define PTCSE_PTCSE0_MASK               1U
#define PTCSE_PTCSE1_MASK               2U
#define PTCSE_PTCSE2_MASK               4U
#define PTCSE_PTCSE3_MASK               8U
#define PTCSE_PTCSE4_MASK               16U
#define PTCSE_PTCSE5_MASK               32U
#define PTCSE_PTCSE6_MASK               64U
#define PTCSE_PTCSE7_MASK               128U


/*** PTCDS - Port C Drive Strength Selection Register; 0x0000184A ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDS0      :1;                                       /* Output Drive Strength Selection for Port C Bit 0 */
    byte PTCDS1      :1;                                       /* Output Drive Strength Selection for Port C Bit 1 */
    byte PTCDS2      :1;                                       /* Output Drive Strength Selection for Port C Bit 2 */
    byte PTCDS3      :1;                                       /* Output Drive Strength Selection for Port C Bit 3 */
    byte PTCDS4      :1;                                       /* Output Drive Strength Selection for Port C Bit 4 */
    byte PTCDS5      :1;                                       /* Output Drive Strength Selection for Port C Bit 5 */
    byte PTCDS6      :1;                                       /* Output Drive Strength Selection for Port C Bit 6 */
    byte PTCDS7      :1;                                       /* Output Drive Strength Selection for Port C Bit 7 */
  } Bits;
} PTCDSSTR;
extern volatile PTCDSSTR _PTCDS @0x0000184A;
#define PTCDS                           _PTCDS.Byte
#define PTCDS_PTCDS0                    _PTCDS.Bits.PTCDS0
#define PTCDS_PTCDS1                    _PTCDS.Bits.PTCDS1
#define PTCDS_PTCDS2                    _PTCDS.Bits.PTCDS2
#define PTCDS_PTCDS3                    _PTCDS.Bits.PTCDS3
#define PTCDS_PTCDS4                    _PTCDS.Bits.PTCDS4
#define PTCDS_PTCDS5                    _PTCDS.Bits.PTCDS5
#define PTCDS_PTCDS6                    _PTCDS.Bits.PTCDS6
#define PTCDS_PTCDS7                    _PTCDS.Bits.PTCDS7

#define PTCDS_PTCDS0_MASK               1U
#define PTCDS_PTCDS1_MASK               2U
#define PTCDS_PTCDS2_MASK               4U
#define PTCDS_PTCDS3_MASK               8U
#define PTCDS_PTCDS4_MASK               16U
#define PTCDS_PTCDS5_MASK               32U
#define PTCDS_PTCDS6_MASK               64U
#define PTCDS_PTCDS7_MASK               128U


/*** PTDPE - Port D Pull Enable Register; 0x0000184C ***/
typedef union {
  byte Byte;
  struct {
    byte PTDPE0      :1;                                       /* Internal Pull Enable for Port D Bit 0 */
    byte PTDPE1      :1;                                       /* Internal Pull Enable for Port D Bit 1 */
    byte PTDPE2      :1;                                       /* Internal Pull Enable for Port D Bit 2 */
    byte PTDPE3      :1;                                       /* Internal Pull Enable for Port D Bit 3 */
    byte PTDPE4      :1;                                       /* Internal Pull Enable for Port D Bit 4 */
    byte PTDPE5      :1;                                       /* Internal Pull Enable for Port D Bit 5 */
    byte PTDPE6      :1;                                       /* Internal Pull Enable for Port D Bit 6 */
    byte PTDPE7      :1;                                       /* Internal Pull Enable for Port D Bit 7 */
  } Bits;
} PTDPESTR;
extern volatile PTDPESTR _PTDPE @0x0000184C;
#define PTDPE                           _PTDPE.Byte
#define PTDPE_PTDPE0                    _PTDPE.Bits.PTDPE0
#define PTDPE_PTDPE1                    _PTDPE.Bits.PTDPE1
#define PTDPE_PTDPE2                    _PTDPE.Bits.PTDPE2
#define PTDPE_PTDPE3                    _PTDPE.Bits.PTDPE3
#define PTDPE_PTDPE4                    _PTDPE.Bits.PTDPE4
#define PTDPE_PTDPE5                    _PTDPE.Bits.PTDPE5
#define PTDPE_PTDPE6                    _PTDPE.Bits.PTDPE6
#define PTDPE_PTDPE7                    _PTDPE.Bits.PTDPE7

#define PTDPE_PTDPE0_MASK               1U
#define PTDPE_PTDPE1_MASK               2U
#define PTDPE_PTDPE2_MASK               4U
#define PTDPE_PTDPE3_MASK               8U
#define PTDPE_PTDPE4_MASK               16U
#define PTDPE_PTDPE5_MASK               32U
#define PTDPE_PTDPE6_MASK               64U
#define PTDPE_PTDPE7_MASK               128U


/*** PTDSE - Port D Slew Rate Enable Register; 0x0000184D ***/
typedef union {
  byte Byte;
  struct {
    byte PTDSE0      :1;                                       /* Output Slew Rate Enable for Port D Bit 0 */
    byte PTDSE1      :1;                                       /* Output Slew Rate Enable for Port D Bit 1 */
    byte PTDSE2      :1;                                       /* Output Slew Rate Enable for Port D Bit 2 */
    byte PTDSE3      :1;                                       /* Output Slew Rate Enable for Port D Bit 3 */
    byte PTDSE4      :1;                                       /* Output Slew Rate Enable for Port D Bit 4 */
    byte PTDSE5      :1;                                       /* Output Slew Rate Enable for Port D Bit 5 */
    byte PTDSE6      :1;                                       /* Output Slew Rate Enable for Port D Bit 6 */
    byte PTDSE7      :1;                                       /* Output Slew Rate Enable for Port D Bit 7 */
  } Bits;
} PTDSESTR;
extern volatile PTDSESTR _PTDSE @0x0000184D;
#define PTDSE                           _PTDSE.Byte
#define PTDSE_PTDSE0                    _PTDSE.Bits.PTDSE0
#define PTDSE_PTDSE1                    _PTDSE.Bits.PTDSE1
#define PTDSE_PTDSE2                    _PTDSE.Bits.PTDSE2
#define PTDSE_PTDSE3                    _PTDSE.Bits.PTDSE3
#define PTDSE_PTDSE4                    _PTDSE.Bits.PTDSE4
#define PTDSE_PTDSE5                    _PTDSE.Bits.PTDSE5
#define PTDSE_PTDSE6                    _PTDSE.Bits.PTDSE6
#define PTDSE_PTDSE7                    _PTDSE.Bits.PTDSE7

#define PTDSE_PTDSE0_MASK               1U
#define PTDSE_PTDSE1_MASK               2U
#define PTDSE_PTDSE2_MASK               4U
#define PTDSE_PTDSE3_MASK               8U
#define PTDSE_PTDSE4_MASK               16U
#define PTDSE_PTDSE5_MASK               32U
#define PTDSE_PTDSE6_MASK               64U
#define PTDSE_PTDSE7_MASK               128U


/*** PTDDS - Port D Drive Strength Selection Register; 0x0000184E ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDS0      :1;                                       /* Output Drive Strength Selection for Port D Bit 0 */
    byte PTDDS1      :1;                                       /* Output Drive Strength Selection for Port D Bit 1 */
    byte PTDDS2      :1;                                       /* Output Drive Strength Selection for Port D Bit 2 */
    byte PTDDS3      :1;                                       /* Output Drive Strength Selection for Port D Bit 3 */
    byte PTDDS4      :1;                                       /* Output Drive Strength Selection for Port D Bit 4 */
    byte PTDDS5      :1;                                       /* Output Drive Strength Selection for Port D Bit 5 */
    byte PTDDS6      :1;                                       /* Output Drive Strength Selection for Port D Bit 6 */
    byte PTDDS7      :1;                                       /* Output Drive Strength Selection for Port D Bit 7 */
  } Bits;
} PTDDSSTR;
extern volatile PTDDSSTR _PTDDS @0x0000184E;
#define PTDDS                           _PTDDS.Byte
#define PTDDS_PTDDS0                    _PTDDS.Bits.PTDDS0
#define PTDDS_PTDDS1                    _PTDDS.Bits.PTDDS1
#define PTDDS_PTDDS2                    _PTDDS.Bits.PTDDS2
#define PTDDS_PTDDS3                    _PTDDS.Bits.PTDDS3
#define PTDDS_PTDDS4                    _PTDDS.Bits.PTDDS4
#define PTDDS_PTDDS5                    _PTDDS.Bits.PTDDS5
#define PTDDS_PTDDS6                    _PTDDS.Bits.PTDDS6
#define PTDDS_PTDDS7                    _PTDDS.Bits.PTDDS7

#define PTDDS_PTDDS0_MASK               1U
#define PTDDS_PTDDS1_MASK               2U
#define PTDDS_PTDDS2_MASK               4U
#define PTDDS_PTDDS3_MASK               8U
#define PTDDS_PTDDS4_MASK               16U
#define PTDDS_PTDDS5_MASK               32U
#define PTDDS_PTDDS6_MASK               64U
#define PTDDS_PTDDS7_MASK               128U


/*** PTEPE - Port E Pull Enable Register; 0x00001850 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEPE0      :1;                                       /* Internal Pull Enable for Port E Bit 0 */
    byte PTEPE1      :1;                                       /* Internal Pull Enable for Port E Bit 1 */
    byte PTEPE2      :1;                                       /* Internal Pull Enable for Port E Bit 2 */
    byte PTEPE3      :1;                                       /* Internal Pull Enable for Port E Bit 3 */
    byte PTEPE4      :1;                                       /* Internal Pull Enable for Port E Bit 4 */
    byte PTEPE5      :1;                                       /* Internal Pull Enable for Port E Bit 5 */
    byte PTEPE6      :1;                                       /* Internal Pull Enable for Port E Bit 6 */
    byte PTEPE7      :1;                                       /* Internal Pull Enable for Port E Bit 7 */
  } Bits;
} PTEPESTR;
extern volatile PTEPESTR _PTEPE @0x00001850;
#define PTEPE                           _PTEPE.Byte
#define PTEPE_PTEPE0                    _PTEPE.Bits.PTEPE0
#define PTEPE_PTEPE1                    _PTEPE.Bits.PTEPE1
#define PTEPE_PTEPE2                    _PTEPE.Bits.PTEPE2
#define PTEPE_PTEPE3                    _PTEPE.Bits.PTEPE3
#define PTEPE_PTEPE4                    _PTEPE.Bits.PTEPE4
#define PTEPE_PTEPE5                    _PTEPE.Bits.PTEPE5
#define PTEPE_PTEPE6                    _PTEPE.Bits.PTEPE6
#define PTEPE_PTEPE7                    _PTEPE.Bits.PTEPE7

#define PTEPE_PTEPE0_MASK               1U
#define PTEPE_PTEPE1_MASK               2U
#define PTEPE_PTEPE2_MASK               4U
#define PTEPE_PTEPE3_MASK               8U
#define PTEPE_PTEPE4_MASK               16U
#define PTEPE_PTEPE5_MASK               32U
#define PTEPE_PTEPE6_MASK               64U
#define PTEPE_PTEPE7_MASK               128U


/*** PTESE - Port E Slew Rate Enable Register; 0x00001851 ***/
typedef union {
  byte Byte;
  struct {
    byte PTESE0      :1;                                       /* Output Slew Rate Enable for Port E Bit 0 */
    byte PTESE1      :1;                                       /* Output Slew Rate Enable for Port E Bit 1 */
    byte PTESE2      :1;                                       /* Output Slew Rate Enable for Port E Bit 2 */
    byte PTESE3      :1;                                       /* Output Slew Rate Enable for Port E Bit 3 */
    byte PTESE4      :1;                                       /* Output Slew Rate Enable for Port E Bit 4 */
    byte PTESE5      :1;                                       /* Output Slew Rate Enable for Port E Bit 5 */
    byte PTESE6      :1;                                       /* Output Slew Rate Enable for Port E Bit 6 */
    byte PTESE7      :1;                                       /* Output Slew Rate Enable for Port E Bit 7 */
  } Bits;
} PTESESTR;
extern volatile PTESESTR _PTESE @0x00001851;
#define PTESE                           _PTESE.Byte
#define PTESE_PTESE0                    _PTESE.Bits.PTESE0
#define PTESE_PTESE1                    _PTESE.Bits.PTESE1
#define PTESE_PTESE2                    _PTESE.Bits.PTESE2
#define PTESE_PTESE3                    _PTESE.Bits.PTESE3
#define PTESE_PTESE4                    _PTESE.Bits.PTESE4
#define PTESE_PTESE5                    _PTESE.Bits.PTESE5
#define PTESE_PTESE6                    _PTESE.Bits.PTESE6
#define PTESE_PTESE7                    _PTESE.Bits.PTESE7

#define PTESE_PTESE0_MASK               1U
#define PTESE_PTESE1_MASK               2U
#define PTESE_PTESE2_MASK               4U
#define PTESE_PTESE3_MASK               8U
#define PTESE_PTESE4_MASK               16U
#define PTESE_PTESE5_MASK               32U
#define PTESE_PTESE6_MASK               64U
#define PTESE_PTESE7_MASK               128U


/*** PTEDS - Port E Drive Strength Selection Register; 0x00001852 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDS0      :1;                                       /* Output Drive Strength Selection for Port E Bit 0 */
    byte PTEDS1      :1;                                       /* Output Drive Strength Selection for Port E Bit 1 */
    byte PTEDS2      :1;                                       /* Output Drive Strength Selection for Port E Bit 2 */
    byte PTEDS3      :1;                                       /* Output Drive Strength Selection for Port E Bit 3 */
    byte PTEDS4      :1;                                       /* Output Drive Strength Selection for Port E Bit 4 */
    byte PTEDS5      :1;                                       /* Output Drive Strength Selection for Port E Bit 5 */
    byte PTEDS6      :1;                                       /* Output Drive Strength Selection for Port E Bit 6 */
    byte PTEDS7      :1;                                       /* Output Drive Strength Selection for Port E Bit 7 */
  } Bits;
} PTEDSSTR;
extern volatile PTEDSSTR _PTEDS @0x00001852;
#define PTEDS                           _PTEDS.Byte
#define PTEDS_PTEDS0                    _PTEDS.Bits.PTEDS0
#define PTEDS_PTEDS1                    _PTEDS.Bits.PTEDS1
#define PTEDS_PTEDS2                    _PTEDS.Bits.PTEDS2
#define PTEDS_PTEDS3                    _PTEDS.Bits.PTEDS3
#define PTEDS_PTEDS4                    _PTEDS.Bits.PTEDS4
#define PTEDS_PTEDS5                    _PTEDS.Bits.PTEDS5
#define PTEDS_PTEDS6                    _PTEDS.Bits.PTEDS6
#define PTEDS_PTEDS7                    _PTEDS.Bits.PTEDS7

#define PTEDS_PTEDS0_MASK               1U
#define PTEDS_PTEDS1_MASK               2U
#define PTEDS_PTEDS2_MASK               4U
#define PTEDS_PTEDS3_MASK               8U
#define PTEDS_PTEDS4_MASK               16U
#define PTEDS_PTEDS5_MASK               32U
#define PTEDS_PTEDS6_MASK               64U
#define PTEDS_PTEDS7_MASK               128U


/*** NVFTRIM - Nonvolatile ICS Fine Trim; 0x0000FFAE ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* ICS Fine Trim */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} NVFTRIMSTR;
/* Tip for register initialization in the user code:  const byte NVFTRIM_INIT @0x0000FFAE = <NVFTRIM_INITVAL>; */
#define _NVFTRIM (*(const NVFTRIMSTR * __far)0x0000FFAE)
#define NVFTRIM                         _NVFTRIM.Byte
#define NVFTRIM_FTRIM                   _NVFTRIM.Bits.FTRIM

#define NVFTRIM_FTRIM_MASK              1U


/*** NVICSTRM - Nonvolatile ICS Trim Register; 0x0000FFAF ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* ICS Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* ICS Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* ICS Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* ICS Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* ICS Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* ICS Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* ICS Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* ICS Trim Setting, bit 7 */
  } Bits;
} NVICSTRMSTR;
/* Tip for register initialization in the user code:  const byte NVICSTRM_INIT @0x0000FFAF = <NVICSTRM_INITVAL>; */
#define _NVICSTRM (*(const NVICSTRMSTR * __far)0x0000FFAF)
#define NVICSTRM                        _NVICSTRM.Byte
#define NVICSTRM_TRIM0                  _NVICSTRM.Bits.TRIM0
#define NVICSTRM_TRIM1                  _NVICSTRM.Bits.TRIM1
#define NVICSTRM_TRIM2                  _NVICSTRM.Bits.TRIM2
#define NVICSTRM_TRIM3                  _NVICSTRM.Bits.TRIM3
#define NVICSTRM_TRIM4                  _NVICSTRM.Bits.TRIM4
#define NVICSTRM_TRIM5                  _NVICSTRM.Bits.TRIM5
#define NVICSTRM_TRIM6                  _NVICSTRM.Bits.TRIM6
#define NVICSTRM_TRIM7                  _NVICSTRM.Bits.TRIM7

#define NVICSTRM_TRIM0_MASK             1U
#define NVICSTRM_TRIM1_MASK             2U
#define NVICSTRM_TRIM2_MASK             4U
#define NVICSTRM_TRIM3_MASK             8U
#define NVICSTRM_TRIM4_MASK             16U
#define NVICSTRM_TRIM5_MASK             32U
#define NVICSTRM_TRIM6_MASK             64U
#define NVICSTRM_TRIM7_MASK             128U


/*** NVBACKKEY0 - Backdoor Comparison Key 0; 0x0000FFB0 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 7 */
  } Bits;
} NVBACKKEY0STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY0_INIT @0x0000FFB0 = <NVBACKKEY0_INITVAL>; */
#define _NVBACKKEY0 (*(const NVBACKKEY0STR * __far)0x0000FFB0)
#define NVBACKKEY0                      _NVBACKKEY0.Byte
#define NVBACKKEY0_KEY0                 _NVBACKKEY0.Bits.KEY0
#define NVBACKKEY0_KEY1                 _NVBACKKEY0.Bits.KEY1
#define NVBACKKEY0_KEY2                 _NVBACKKEY0.Bits.KEY2
#define NVBACKKEY0_KEY3                 _NVBACKKEY0.Bits.KEY3
#define NVBACKKEY0_KEY4                 _NVBACKKEY0.Bits.KEY4
#define NVBACKKEY0_KEY5                 _NVBACKKEY0.Bits.KEY5
#define NVBACKKEY0_KEY6                 _NVBACKKEY0.Bits.KEY6
#define NVBACKKEY0_KEY7                 _NVBACKKEY0.Bits.KEY7
/* NVBACKKEY_ARR: Access 8 NVBACKKEYx registers in an array */
#define NVBACKKEY_ARR                   ((volatile byte * __far) &NVBACKKEY0)

#define NVBACKKEY0_KEY0_MASK            1U
#define NVBACKKEY0_KEY1_MASK            2U
#define NVBACKKEY0_KEY2_MASK            4U
#define NVBACKKEY0_KEY3_MASK            8U
#define NVBACKKEY0_KEY4_MASK            16U
#define NVBACKKEY0_KEY5_MASK            32U
#define NVBACKKEY0_KEY6_MASK            64U
#define NVBACKKEY0_KEY7_MASK            128U


/*** NVBACKKEY1 - Backdoor Comparison Key 1; 0x0000FFB1 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 7 */
  } Bits;
} NVBACKKEY1STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY1_INIT @0x0000FFB1 = <NVBACKKEY1_INITVAL>; */
#define _NVBACKKEY1 (*(const NVBACKKEY1STR * __far)0x0000FFB1)
#define NVBACKKEY1                      _NVBACKKEY1.Byte
#define NVBACKKEY1_KEY0                 _NVBACKKEY1.Bits.KEY0
#define NVBACKKEY1_KEY1                 _NVBACKKEY1.Bits.KEY1
#define NVBACKKEY1_KEY2                 _NVBACKKEY1.Bits.KEY2
#define NVBACKKEY1_KEY3                 _NVBACKKEY1.Bits.KEY3
#define NVBACKKEY1_KEY4                 _NVBACKKEY1.Bits.KEY4
#define NVBACKKEY1_KEY5                 _NVBACKKEY1.Bits.KEY5
#define NVBACKKEY1_KEY6                 _NVBACKKEY1.Bits.KEY6
#define NVBACKKEY1_KEY7                 _NVBACKKEY1.Bits.KEY7

#define NVBACKKEY1_KEY0_MASK            1U
#define NVBACKKEY1_KEY1_MASK            2U
#define NVBACKKEY1_KEY2_MASK            4U
#define NVBACKKEY1_KEY3_MASK            8U
#define NVBACKKEY1_KEY4_MASK            16U
#define NVBACKKEY1_KEY5_MASK            32U
#define NVBACKKEY1_KEY6_MASK            64U
#define NVBACKKEY1_KEY7_MASK            128U


/*** NVBACKKEY2 - Backdoor Comparison Key 2; 0x0000FFB2 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 7 */
  } Bits;
} NVBACKKEY2STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY2_INIT @0x0000FFB2 = <NVBACKKEY2_INITVAL>; */
#define _NVBACKKEY2 (*(const NVBACKKEY2STR * __far)0x0000FFB2)
#define NVBACKKEY2                      _NVBACKKEY2.Byte
#define NVBACKKEY2_KEY0                 _NVBACKKEY2.Bits.KEY0
#define NVBACKKEY2_KEY1                 _NVBACKKEY2.Bits.KEY1
#define NVBACKKEY2_KEY2                 _NVBACKKEY2.Bits.KEY2
#define NVBACKKEY2_KEY3                 _NVBACKKEY2.Bits.KEY3
#define NVBACKKEY2_KEY4                 _NVBACKKEY2.Bits.KEY4
#define NVBACKKEY2_KEY5                 _NVBACKKEY2.Bits.KEY5
#define NVBACKKEY2_KEY6                 _NVBACKKEY2.Bits.KEY6
#define NVBACKKEY2_KEY7                 _NVBACKKEY2.Bits.KEY7

#define NVBACKKEY2_KEY0_MASK            1U
#define NVBACKKEY2_KEY1_MASK            2U
#define NVBACKKEY2_KEY2_MASK            4U
#define NVBACKKEY2_KEY3_MASK            8U
#define NVBACKKEY2_KEY4_MASK            16U
#define NVBACKKEY2_KEY5_MASK            32U
#define NVBACKKEY2_KEY6_MASK            64U
#define NVBACKKEY2_KEY7_MASK            128U


/*** NVBACKKEY3 - Backdoor Comparison Key 3; 0x0000FFB3 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 7 */
  } Bits;
} NVBACKKEY3STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY3_INIT @0x0000FFB3 = <NVBACKKEY3_INITVAL>; */
#define _NVBACKKEY3 (*(const NVBACKKEY3STR * __far)0x0000FFB3)
#define NVBACKKEY3                      _NVBACKKEY3.Byte
#define NVBACKKEY3_KEY0                 _NVBACKKEY3.Bits.KEY0
#define NVBACKKEY3_KEY1                 _NVBACKKEY3.Bits.KEY1
#define NVBACKKEY3_KEY2                 _NVBACKKEY3.Bits.KEY2
#define NVBACKKEY3_KEY3                 _NVBACKKEY3.Bits.KEY3
#define NVBACKKEY3_KEY4                 _NVBACKKEY3.Bits.KEY4
#define NVBACKKEY3_KEY5                 _NVBACKKEY3.Bits.KEY5
#define NVBACKKEY3_KEY6                 _NVBACKKEY3.Bits.KEY6
#define NVBACKKEY3_KEY7                 _NVBACKKEY3.Bits.KEY7

#define NVBACKKEY3_KEY0_MASK            1U
#define NVBACKKEY3_KEY1_MASK            2U
#define NVBACKKEY3_KEY2_MASK            4U
#define NVBACKKEY3_KEY3_MASK            8U
#define NVBACKKEY3_KEY4_MASK            16U
#define NVBACKKEY3_KEY5_MASK            32U
#define NVBACKKEY3_KEY6_MASK            64U
#define NVBACKKEY3_KEY7_MASK            128U


/*** NVBACKKEY4 - Backdoor Comparison Key 4; 0x0000FFB4 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 7 */
  } Bits;
} NVBACKKEY4STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY4_INIT @0x0000FFB4 = <NVBACKKEY4_INITVAL>; */
#define _NVBACKKEY4 (*(const NVBACKKEY4STR * __far)0x0000FFB4)
#define NVBACKKEY4                      _NVBACKKEY4.Byte
#define NVBACKKEY4_KEY0                 _NVBACKKEY4.Bits.KEY0
#define NVBACKKEY4_KEY1                 _NVBACKKEY4.Bits.KEY1
#define NVBACKKEY4_KEY2                 _NVBACKKEY4.Bits.KEY2
#define NVBACKKEY4_KEY3                 _NVBACKKEY4.Bits.KEY3
#define NVBACKKEY4_KEY4                 _NVBACKKEY4.Bits.KEY4
#define NVBACKKEY4_KEY5                 _NVBACKKEY4.Bits.KEY5
#define NVBACKKEY4_KEY6                 _NVBACKKEY4.Bits.KEY6
#define NVBACKKEY4_KEY7                 _NVBACKKEY4.Bits.KEY7

#define NVBACKKEY4_KEY0_MASK            1U
#define NVBACKKEY4_KEY1_MASK            2U
#define NVBACKKEY4_KEY2_MASK            4U
#define NVBACKKEY4_KEY3_MASK            8U
#define NVBACKKEY4_KEY4_MASK            16U
#define NVBACKKEY4_KEY5_MASK            32U
#define NVBACKKEY4_KEY6_MASK            64U
#define NVBACKKEY4_KEY7_MASK            128U


/*** NVBACKKEY5 - Backdoor Comparison Key 5; 0x0000FFB5 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 7 */
  } Bits;
} NVBACKKEY5STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY5_INIT @0x0000FFB5 = <NVBACKKEY5_INITVAL>; */
#define _NVBACKKEY5 (*(const NVBACKKEY5STR * __far)0x0000FFB5)
#define NVBACKKEY5                      _NVBACKKEY5.Byte
#define NVBACKKEY5_KEY0                 _NVBACKKEY5.Bits.KEY0
#define NVBACKKEY5_KEY1                 _NVBACKKEY5.Bits.KEY1
#define NVBACKKEY5_KEY2                 _NVBACKKEY5.Bits.KEY2
#define NVBACKKEY5_KEY3                 _NVBACKKEY5.Bits.KEY3
#define NVBACKKEY5_KEY4                 _NVBACKKEY5.Bits.KEY4
#define NVBACKKEY5_KEY5                 _NVBACKKEY5.Bits.KEY5
#define NVBACKKEY5_KEY6                 _NVBACKKEY5.Bits.KEY6
#define NVBACKKEY5_KEY7                 _NVBACKKEY5.Bits.KEY7

#define NVBACKKEY5_KEY0_MASK            1U
#define NVBACKKEY5_KEY1_MASK            2U
#define NVBACKKEY5_KEY2_MASK            4U
#define NVBACKKEY5_KEY3_MASK            8U
#define NVBACKKEY5_KEY4_MASK            16U
#define NVBACKKEY5_KEY5_MASK            32U
#define NVBACKKEY5_KEY6_MASK            64U
#define NVBACKKEY5_KEY7_MASK            128U


/*** NVBACKKEY6 - Backdoor Comparison Key 6; 0x0000FFB6 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 7 */
  } Bits;
} NVBACKKEY6STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY6_INIT @0x0000FFB6 = <NVBACKKEY6_INITVAL>; */
#define _NVBACKKEY6 (*(const NVBACKKEY6STR * __far)0x0000FFB6)
#define NVBACKKEY6                      _NVBACKKEY6.Byte
#define NVBACKKEY6_KEY0                 _NVBACKKEY6.Bits.KEY0
#define NVBACKKEY6_KEY1                 _NVBACKKEY6.Bits.KEY1
#define NVBACKKEY6_KEY2                 _NVBACKKEY6.Bits.KEY2
#define NVBACKKEY6_KEY3                 _NVBACKKEY6.Bits.KEY3
#define NVBACKKEY6_KEY4                 _NVBACKKEY6.Bits.KEY4
#define NVBACKKEY6_KEY5                 _NVBACKKEY6.Bits.KEY5
#define NVBACKKEY6_KEY6                 _NVBACKKEY6.Bits.KEY6
#define NVBACKKEY6_KEY7                 _NVBACKKEY6.Bits.KEY7

#define NVBACKKEY6_KEY0_MASK            1U
#define NVBACKKEY6_KEY1_MASK            2U
#define NVBACKKEY6_KEY2_MASK            4U
#define NVBACKKEY6_KEY3_MASK            8U
#define NVBACKKEY6_KEY4_MASK            16U
#define NVBACKKEY6_KEY5_MASK            32U
#define NVBACKKEY6_KEY6_MASK            64U
#define NVBACKKEY6_KEY7_MASK            128U


/*** NVBACKKEY7 - Backdoor Comparison Key 7; 0x0000FFB7 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 7 */
  } Bits;
} NVBACKKEY7STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY7_INIT @0x0000FFB7 = <NVBACKKEY7_INITVAL>; */
#define _NVBACKKEY7 (*(const NVBACKKEY7STR * __far)0x0000FFB7)
#define NVBACKKEY7                      _NVBACKKEY7.Byte
#define NVBACKKEY7_KEY0                 _NVBACKKEY7.Bits.KEY0
#define NVBACKKEY7_KEY1                 _NVBACKKEY7.Bits.KEY1
#define NVBACKKEY7_KEY2                 _NVBACKKEY7.Bits.KEY2
#define NVBACKKEY7_KEY3                 _NVBACKKEY7.Bits.KEY3
#define NVBACKKEY7_KEY4                 _NVBACKKEY7.Bits.KEY4
#define NVBACKKEY7_KEY5                 _NVBACKKEY7.Bits.KEY5
#define NVBACKKEY7_KEY6                 _NVBACKKEY7.Bits.KEY6
#define NVBACKKEY7_KEY7                 _NVBACKKEY7.Bits.KEY7

#define NVBACKKEY7_KEY0_MASK            1U
#define NVBACKKEY7_KEY1_MASK            2U
#define NVBACKKEY7_KEY2_MASK            4U
#define NVBACKKEY7_KEY3_MASK            8U
#define NVBACKKEY7_KEY4_MASK            16U
#define NVBACKKEY7_KEY5_MASK            32U
#define NVBACKKEY7_KEY6_MASK            64U
#define NVBACKKEY7_KEY7_MASK            128U


/*** NVPROT - Nonvolatile FLASH Protection Register; 0x0000FFBD ***/
typedef union {
  byte Byte;
  struct {
    byte FPDIS       :1;                                       /* FLASH Protection Disable */
    byte FPS1        :1;                                       /* FLASH Protect Select Bit 1 */
    byte FPS2        :1;                                       /* FLASH Protect Select Bit 2 */
    byte FPS3        :1;                                       /* FLASH Protect Select Bit 3 */
    byte FPS4        :1;                                       /* FLASH Protect Select Bit 4 */
    byte FPS5        :1;                                       /* FLASH Protect Select Bit 5 */
    byte FPS6        :1;                                       /* FLASH Protect Select Bit 6 */
    byte FPS7        :1;                                       /* FLASH Protect Select Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS_1 :7;
  } MergedBits;
} NVPROTSTR;
/* Tip for register initialization in the user code:  const byte NVPROT_INIT @0x0000FFBD = <NVPROT_INITVAL>; */
#define _NVPROT (*(const NVPROTSTR * __far)0x0000FFBD)
#define NVPROT                          _NVPROT.Byte
#define NVPROT_FPDIS                    _NVPROT.Bits.FPDIS
#define NVPROT_FPS1                     _NVPROT.Bits.FPS1
#define NVPROT_FPS2                     _NVPROT.Bits.FPS2
#define NVPROT_FPS3                     _NVPROT.Bits.FPS3
#define NVPROT_FPS4                     _NVPROT.Bits.FPS4
#define NVPROT_FPS5                     _NVPROT.Bits.FPS5
#define NVPROT_FPS6                     _NVPROT.Bits.FPS6
#define NVPROT_FPS7                     _NVPROT.Bits.FPS7
#define NVPROT_FPS_1                    _NVPROT.MergedBits.grpFPS_1
#define NVPROT_FPS                      NVPROT_FPS_1

#define NVPROT_FPDIS_MASK               1U
#define NVPROT_FPS1_MASK                2U
#define NVPROT_FPS2_MASK                4U
#define NVPROT_FPS3_MASK                8U
#define NVPROT_FPS4_MASK                16U
#define NVPROT_FPS5_MASK                32U
#define NVPROT_FPS6_MASK                64U
#define NVPROT_FPS7_MASK                128U
#define NVPROT_FPS_1_MASK               254U
#define NVPROT_FPS_1_BITNUM             1U


/*** NVOPT - Nonvolatile Flash Options Register; 0x0000FFBF ***/
typedef union {
  byte Byte;
  struct {
    byte SEC00       :1;                                       /* Security State Code, bit 0 */
    byte SEC01       :1;                                       /* Security State Code, bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte FNORED      :1;                                       /* Vector Redirection Disable */
    byte KEYEN       :1;                                       /* Backdoor Key Mechanism Enable */
  } Bits;
  struct {
    byte grpSEC0 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} NVOPTSTR;
/* Tip for register initialization in the user code:  const byte NVOPT_INIT @0x0000FFBF = <NVOPT_INITVAL>; */
#define _NVOPT (*(const NVOPTSTR * __far)0x0000FFBF)
#define NVOPT                           _NVOPT.Byte
#define NVOPT_SEC00                     _NVOPT.Bits.SEC00
#define NVOPT_SEC01                     _NVOPT.Bits.SEC01
#define NVOPT_FNORED                    _NVOPT.Bits.FNORED
#define NVOPT_KEYEN                     _NVOPT.Bits.KEYEN
#define NVOPT_SEC0                      _NVOPT.MergedBits.grpSEC0

#define NVOPT_SEC00_MASK                1U
#define NVOPT_SEC01_MASK                2U
#define NVOPT_FNORED_MASK               64U
#define NVOPT_KEYEN_MASK                128U
#define NVOPT_SEC0_MASK                 3U
#define NVOPT_SEC0_BITNUM               0U



/* Flash commands */
#define mBlank                          0x05
#define mBurstProg                      0x25
#define mByteProg                       0x20
#define mMassErase                      0x41
#define mPageErase                      0x40


/***********************************************/
/**   D E P R E C I A T E D   S Y M B O L S   **/
/***********************************************/
#endif
/*lint -restore  +esym(961,18.4) +esym(961,19.7) Enable MISRA rule (1.1,18.4,6.4,19.7) checking. */
