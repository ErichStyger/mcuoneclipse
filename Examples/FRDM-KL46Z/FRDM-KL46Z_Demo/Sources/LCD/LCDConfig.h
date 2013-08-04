#ifndef __LCDConfig_H_
#define __LCDConfig_H_

#include "FRDM-s401.h"  //  4x7 segdisplay


#if 1  // VREF to VLL1
/* Following configuration is used for LCD default initialization  */
#define _LCDRVEN          (1)  //
#define _LCDRVTRIM        (8)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDCPSEL         (1)          //  charge pump select 0 or 1 
#define _LCDLOADADJUST    (3)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDALTDIV        (0)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDALRCLKSOURCE  (0)         // 0 -- External clock       1 --  Alternate clock

#define _LCDCLKPSL        (0)         //  Clock divider to generate the LCD Waveforms 
#define _LCDSUPPLY        (1) 
#define _LCDHREF          (0)          // 0 or 1 
#define _LCDCLKSOURCE     (1)         // 0 -- External clock       1 --  Alternate clock
#define _LCDLCK           (1)         //Any number between 0 and 7 
#define _LCDBLINKRATE     (3)         //Any number between 0 and 7 


#else    //VLL3 to VDD internally
/* Following configuration is used for LCD default initialization  */
#define _LCDCLKSOURCE     (1)         // 0 -- External clock       1 --  Alternate clock
#define _LCDALRCLKSOURCE  (0)         // 0 -- External clock       1 --  Alternate clock
#define _LCDCLKPSL        (0)         //  Clock divider to generate the LCD Waveforms 
#define _LCDSUPPLY        (0) 
#define _LCDLOADADJUST    (3)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDALTDIV        (0)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDRVTRIM        (0)           // CPSEL = 1     0 -- 8000 pf 1 -- 6000 pf  2 -- 4000 pf  3 -- 2000 pf
#define _LCDHREF          (0)          // 0 or 1 
#define _LCDCPSEL         (1)          // 0 or 1 
#define _LCDRVEN          (0)  //
#define _LCDBLINKRATE     (3)         //Any number between 0 and 7 
#define _LCDLCK           (0)         //Any number between 0 and 7 

#endif




/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Control Register 0  ~|~|~|~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDINTENABLE         (1)    

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Control Register 1  ~|~|~|~|~|~|~|~|~|~|~|~|~|*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDFRAMEINTERRUPT     (0)        //0 Disable Frame Frequency Interrupt
                                                                       //1 Enable an LCD interrupt that coincides with the LCD frame frequency
#define _LCDFULLCPLDIRIVE      (0)        // 0 GPIO shared with the LCD. Inputs levels and internal pullup reference to VDD
                                                                      // 1 If VSUPPLY=11and RVEN=0. Inputs levels and internal pullup reference to VLL3
#define _LCDWAITMODE           (0)       // 0 Allows the LCD driver and charge pump to continue running during wait mode
                                                                     //  1 Disable the LCD when the MCU goes into wait mode
#define _LCDSTOPMODE           (0)     // 0 Allows the LCD driver and charge pump to continue running during stop2 or stop3

                                                                     //  1 Disable the LCD when and charge pump when the MCU goes into stop2 or stop3                                                               

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Voltage Supply Register  ~|~|~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDHIGHREF             (0)      //0 Divide input VIREG=1.0v
                                                                    //1 Do not divide the input VIREG=1.67v
#define _LCDBBYPASS             (0)      //Determines whether the internal LCD op amp buffer is bypassed
                                                                      //0 Buffered mode
                                                                      //1 Unbuffered mode
                            
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Regulated Voltage Control |~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDCONTRAST                    (1)       //Contrast by software   0 -- Disable    1-- Enable
#define _LVLCONTRAST                    (0)       //Any number between 0  and 15, if the number is bigger the glass get darker

/*~|~|~|~|~|~|~|~|~|~|~|~|~|~  LCD  Blink Control Register ~|~|~|~|~|~|~|~|~|~|~|~*/
/*~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|*/
#define _LCDBLINKCONTROL         (0)   //0 Disable blink mode
                                                                       //1 Enable blink mode
#define _LCDALTMODE              (0)   //0 Normal display 
                                                                      //1 Alternate display for 4 backplanes or less the LCD backplane sequencer changes to otuput an alternate display
#define _LCDBLANKDISP           (0)  //0 Do not blank display
                                                                      //1 Blank display if you put it in 0 the text before blank is manteined     
#define _LCDBLINKMODE           (0)  //0 Display blank during the blink period 
                                                                     //1 Display alternate displat during blink period (Ignored if duty is 5 or greater)


//Calculated values
#define _LCDUSEDPINS   (_LCDFRONTPLANES + _LCDBACKPLANES)
#define _LCDDUTY       (_LCDBACKPLANES-1)         //Any number between 0 and 7 
#define  LCD_WF_BASE    LCD_WF3TO0

// General definitions used by the LCD library
#define  SymbolON(LCDn,bit)     *((uint8 *)&LCD_WF_BASE + LCDn)  |=  (1<<(bit))         
#define  SymbolOFF(LCDn,bit)    *((uint8 *)&LCD_WF_BASE + LCDn)  &= ~(1<<(bit))         
//#define  LCD_WF(x)              *((uint8 *)&LCD_WF_BASE + x) 

/*LCD Fault Detections Consts*/
#define  FP_TYPE  0x00         // pin is a Front Plane
#define  BP_TYPE  0x80         // pin is Back Plane

// Fault Detect Preescaler Options
#define FDPRS_1      0
#define FDPRS_2      1
#define FDPRS_4      2
#define FDPRS_8      3
#define FDPRS_16     4 
#define FDPRS_32     5
#define FDPRS_64     6
#define FDPRS_128    7

// Fault Detect Sample Window Width Values  
#define FDSWW_4           0
#define FDSWW_8           1
#define FDSWW_16          2
#define FDSWW_32          3
#define FDSWW_64          4
#define FDSWW_128         5
#define FDSWW_256         6
#define FDSWW_512         7

/*
  Mask Bit definitions used f
*/
#define     mBIT0   1
#define     mBIT1   2
#define     mBIT2   4
#define     mBIT3   8
#define     mBIT4   16
#define     mBIT5   32
#define     mBIT6   64
#define     mBIT7   128
#define     mBIT8   256
#define     mBIT9   512
#define     mBIT10   1024
#define     mBIT11   2048
#define     mBIT12   4096
#define     mBIT13   8192
#define     mBIT14   16384
#define     mBIT15   32768
#define     mBIT16   65536
#define     mBIT17   131072
#define     mBIT18   262144
#define     mBIT19   524288
#define     mBIT20   1048576
#define     mBIT21   2097152
#define     mBIT22   4194304
#define     mBIT23   8388608
#define     mBIT24   16777216
#define     mBIT25   33554432
#define     mBIT26   67108864
#define     mBIT27   134217728
#define     mBIT28   268435456
#define     mBIT29   536870912
#define     mBIT30   1073741824
#define     mBIT31   2147483648

#define    mBIT32      1
#define    mBIT33      2
#define    mBIT34      4
#define    mBIT35      8
#define    mBIT36      16
#define    mBIT37      32
#define    mBIT38      64
#define    mBIT39      128
#define    mBIT40      256
#define    mBIT41      512
#define    mBIT42      1024
#define    mBIT43      2048
#define    mBIT44      4096
#define    mBIT45      8192
#define    mBIT46      16384
#define    mBIT47      32768
#define    mBIT48      65536
#define    mBIT49      131072
#define    mBIT50      262144
#define    mBIT51      524288
#define    mBIT52      1048576
#define    mBIT53      2097152
#define    mBIT54      4194304
#define    mBIT55      8388608
#define    mBIT56      16777216
#define    mBIT57      33554432
#define    mBIT58      67108864
#define    mBIT59      134217728
#define    mBIT60      268435456
#define    mBIT61      536870912
#define    mBIT62      1073741824
#define    mBIT63      2147483648

#endif /* __LCDConfig_H_ */
