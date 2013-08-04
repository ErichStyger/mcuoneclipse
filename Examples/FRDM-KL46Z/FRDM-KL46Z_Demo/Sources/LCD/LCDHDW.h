/*^^^^^^^^^^^^^^^^   LCD HARDWARE CONECTION 
 FB-GD6363AP.h
             Marconi Daugther Card to GD-5366AP configuration
             8x35 Dot Matrix LCD  + 8 special characters
             3 Volts

^^^^^^^^^^^^^^^^^^^^^^^^*/



#define _CHARNUM    (35)  //number of chars that can be written
#define _CHAR_SIZE   (6)  // Used only when Dot Matrix is used
#define _LCDTYPE     (1)  //indicate how many LCD_WF are required to write a single Character / or Colum in case of DOT matrix LCD


#define  EnableLCDpin(RegNum,LCDn)    LCDPEN##RegNum##_PEN##LCDn = 1
#define  EnableBackplane(RegNum, LCDn)      LCDBPEN##RegNum##_BPEN##LCDn  = 1    


// with mask
#define  SetBackplane(ComNum, LCDn)   LCDWF##LCDn  = (1 << (ComNum))
                                                      
#define  CharacterPlace(LCDn)        LCDWF##LCDn        // _LCDWF0
                        
#define BP_FLAG 0x80 // used to indicate if the WF is used as backplane
                                 
                                            
// Enable all LCD pins to be used as LCD function  inlcuding Backplanes and Front planes
     #define     EnablePin4    EnableLCDpin (5,40)
     #define     EnablePin3    EnableLCDpin (5,41)
     #define     EnablePin2    EnableLCDpin (5,42)
     #define     EnablePin1    EnableLCDpin (5,43)
     #define     EnablePin23    EnableLCDpin (0,0)
     #define     EnablePin24    EnableLCDpin (0,1)
     #define     EnablePin25    EnableLCDpin (0,2)
     #define     EnablePin26    EnableLCDpin (0,3)
     #define     EnablePin27    EnableLCDpin (0,4)
     #define     EnablePin28    EnableLCDpin (0,5)
     #define     EnablePin29    EnableLCDpin (0,6)
     #define     EnablePin30    EnableLCDpin (0,7)
     #define     EnablePin31    EnableLCDpin (1,8)
     #define     EnablePin32    EnableLCDpin (1,9)
     #define     EnablePin33    EnableLCDpin (1,10)
     #define     EnablePin34    EnableLCDpin (1,11)
     #define     EnablePin35    EnableLCDpin (1,12)
     #define     EnablePin5    EnableLCDpin (4,39)
     #define     EnablePin6    EnableLCDpin (4,38)
     #define     EnablePin7    EnableLCDpin (4,37)
     #define     EnablePin8    EnableLCDpin (4,36)
     #define     EnablePin9    EnableLCDpin (4,35)
     #define     EnablePin10    EnableLCDpin (4,34)
     #define     EnablePin11    EnableLCDpin (4,33)
     #define     EnablePin12    EnableLCDpin (4,32)
     #define     EnablePin13    EnableLCDpin (3,31)
     #define     EnablePin14    EnableLCDpin (3,30)
     #define     EnablePin15    EnableLCDpin (3,29)
     #define     EnablePin16    EnableLCDpin (3,28)
     #define     EnablePin17    EnableLCDpin (3,27)
     #define     EnablePin18    EnableLCDpin (3,26)
     #define     EnablePin19    EnableLCDpin (3,25)
     #define     EnablePin20    EnableLCDpin (3,24)
     #define     EnablePin21    EnableLCDpin (2,23)
     #define     EnablePin36    EnableLCDpin (1,13)
     #define     EnablePin37    EnableLCDpin (1,14)
     #define     EnablePin38    EnableLCDpin (1,15)
     #define     EnablePin39    EnableLCDpin (2,16)
     #define     EnablePin40    EnableLCDpin (2,17)
     #define     EnablePin41    EnableLCDpin (2,18)
     #define     EnablePin42    EnableLCDpin (2,19)
     #define     EnablePin43    EnableLCDpin (2,20)
     #define     EnablePin44    EnableLCDpin (2,21)
     #define     EnablePin22    EnableLCDpin (2,22)



/*Related with register names */



// Enable the LCD pin like a Backplane functionality 
// (registernumber,LCD pin number)
     #define     EnablePin4    EnableLCDpin (5,40)
     #define     EnablePin3    EnableLCDpin (5,41)
     #define     EnablePin2    EnableLCDpin (5,42)
     #define     EnablePin1    EnableLCDpin (5,43)
     #define     EnablePin23    EnableLCDpin (0,0)
     #define     EnablePin24    EnableLCDpin (0,1)
     #define     EnablePin25    EnableLCDpin (0,2)
     #define     EnablePin26    EnableLCDpin (0,3)



// Give the mask to the Backplane  
// (ComNumber/BitNumber/priority  segun el LCD manual ,  LCDn)
        #define SetCom1         SetBackplane(0,0)
        #define SetCom2         SetBackplane(1,1)
        #define SetCom3         SetBackplane(2,2)
        #define SetCom4         SetBackplane(3,3)
        #define SetCom5         SetBackplane(0,0)
        #define SetCom6         SetBackplane(1,1)
        #define SetCom7         SetBackplane(2,2)
        #define SetCom8         SetBackplane(3,3)




// Indicate how Character is connected to LCDn

#ifdef GD5602P
#define   Char1        41  // LCD Pin 40
#define   Char2        40  // LCD Pin 39
#define   Char3        39  // LCD Pin 38
#define   Char4        38  // LCD Pin 37
#define   Char5        37  // LCD Pin 36
#define   Char6        36  // LCD Pin 35
#define   Char7        35  // LCD Pin 34
#define   Char8        34  // LCD Pin 33
#define   Char9        33  // LCD Pin 32
#define   Char10        17  // LCD Pin 5
#define   Char11        16  // LCD Pin 6
#define   Char12        15  // LCD Pin 7
#define   Char13        14  // LCD Pin 8
#define   Char14        13  // LCD Pin 9
#define   Char15        12  // LCD Pin 10
#define   Char16        11  // LCD Pin 11
#define   Char17        10  // LCD Pin 12
#define   Char18        9  // LCD Pin 13
#define   Char19        8  // LCD Pin 14
#define   Char20        7  // LCD Pin 15
#define   Char21        6  // LCD Pin 16
#define   Char22        5  // LCD Pin 17
#define   Char23        4  // LCD Pin 18
#define   Char24        3  // LCD Pin 19
#define   Char25        2  // LCD Pin 20
#define   Char26        1  // LCD Pin 21
#define   Char27        32  // LCD Pin 31
#define   Char28        31  // LCD Pin 30
#define   Char29        30  // LCD Pin 29
#define   Char30        29  // LCD Pin 28
#define   Char31        28  // LCD Pin 27
#define   Char32        27  // LCD Pin 26
#define   Char33        26  // LCD Pin 25
#define   Char34        25  // LCD Pin 24
#define   Char35        24  // LCD Pin 23
#define   Char36        0  // LCD Pin 22
#endif

#ifdef  GD5663AP
#define   CHAR1        0  // LCD Pin 1
#define   CHAR2        1  // LCD Pin 2
#define   CHAR3        2  // LCD Pin 3
#define   CHAR4        3  // LCD Pin 4
#define   CHAR5        4  // LCD Pin 5
#define   CHAR6        5  // LCD Pin 6
#define   CHAR7        6  // LCD Pin 7
#define   CHAR8        7  // LCD Pin 8
#define   CHAR9        8  // LCD Pin 9
#define   CHAR10        9  // LCD Pin 10
#define   CHAR11        10  // LCD Pin 11
#define   CHAR12        11  // LCD Pin 12
#define   CHAR13        12  // LCD Pin 13
#define   CHAR14        13  // LCD Pin 14
#define   CHAR15        14  // LCD Pin 15
#define   CHAR16        15  // LCD Pin 16
#define   CHAR17        16  // LCD Pin 17
#define   CHAR18        17  // LCD Pin 18
#define   CHAR19        18  // LCD Pin 19
#define   CHAR20        19  // LCD Pin 20
#define   CHAR21        20  // LCD Pin 21
#define   CHAR22        21  // LCD Pin 22
#define   CHAR23        32  // LCD Pin 36
#define   CHAR24        33  // LCD Pin 35
#define   CHAR25        34  // LCD Pin 34
#define   CHAR26        35  // LCD Pin 33
#define   CHAR27        36  // LCD Pin 32
#define   CHAR28        37  // LCD Pin 31
#define   CHAR29        38  // LCD Pin 30
#define   CHAR30        39  // LCD Pin 29
#define   CHAR31        40  // LCD Pin 28
#define   CHAR32        41  // LCD Pin 27
#define   CHAR33        42  // LCD Pin 26
#define   CHAR34        43  // LCD Pin 25
#define   CHAR35        44  // LCD Pin 24
#define   CHAR_S1        45  // LCD Pin 23

#define   CHARCOM0        31  // LCD Pin 37
#define   CHARCOM1        30  // LCD Pin 38
#define   CHARCOM2        29  // LCD Pin 39
#define   CHARCOM3        28  // LCD Pin 40
#define   CHARCOM4        27  // LCD Pin 41
#define   CHARCOM5        26  // LCD Pin 42
#define   CHARCOM6        25  // LCD Pin 43
#define   CHARCOM7        24  // LCD Pin 44

/* Define which LCDWF are used as backplane (COM0 to COM7 are set as reference but is not configured here */
#define  BP_COM0        31
#define  BP_COM1        30
#define  BP_COM2        29
#define  BP_COM3        28
#define  BP_COM4        27
#define  BP_COM5        26
#define  BP_COM6        25
#define  BP_COM7        24

#endif







 // *((uint8 *)&LCD_WF3TO0 + CHAR_S1) |= 0xFF;
 // *((uint8 *)&LCD_WF3TO0 + CHAR_S1) |= 0x00;


#define SymbolON(LCDn,bit)     *((uint8 *)&LCD_WF3TO0 + LCDn)  |=  (1<<(bit))         
#define SymbolOFF(LCDn,bit)    *((uint8 *)&LCD_WF3TO0 + LCDn)  &= ~(1<<(bit))         
#define LCD_WF(x)              *((uint8 *)&LCD_WF3TO0 + x) 


#define   _LCD_FREESCALE_ON()    SymbolON(CHAR_S1,0)
#define   _LCD_BATTERY_ON()    SymbolON(CHAR_S1,1)
#define   _LCD_LEVEL4_ON()    SymbolON(CHAR_S1,2)
#define   _LCD_LEVEL3_ON()    SymbolON(CHAR_S1,3)
#define   _LCD_LEVEL2_ON()    SymbolON(CHAR_S1,4)
#define   _LCD_LEVEL1_ON()    SymbolON(CHAR_S1,5)
#define   _LCD_SNOW_ON()    SymbolON(CHAR_S1,6)
#define   _LCD_FIRE_ON()    SymbolON(CHAR_S1,7)

#define   _LCD_FREESCALE_OFF()      SymbolOFF(CHAR_S1,0)
#define   _LCD_BATTERY_OFF()      SymbolOFF(CHAR_S1,1)
#define   _LCD_LEVEL4_OFF()      SymbolOFF(CHAR_S1,2)
#define   _LCD_LEVEL3_OFF()      SymbolOFF(CHAR_S1,3)
#define   _LCD_LEVEL2_OFF()      SymbolOFF(CHAR_S1,4)
#define   _LCD_LEVEL1_OFF()      SymbolOFF(CHAR_S1,5)
#define   _LCD_SNOW_OFF()      SymbolOFF(CHAR_S1,6)
#define   _LCD_FIRE_OFF()      SymbolOFF(CHAR_S1,7)


//  (LCDn, BitNumber)



#define MapSegment(SegmentName,Mask)   (1<<(##Mask##)) 
          
          #define  SEG1               MapSegment (0,0)
          #define  SEG2               MapSegment (1,1)
          #define  SEG3               MapSegment (2,2)
          #define  SEG4               MapSegment (3,3)
          #define  SEG5               MapSegment (4,4)
          #define  SEG6               MapSegment (5,5)
          #define  SEG7               MapSegment (6,6)
          #define  SEG8               MapSegment (7,7)
          
          
  

/*Map segment to COM mask*/
#define  SEGB   0x01
#define  SEGC   0x02

#define  SEGH   0x01
#define  SEGF   0x02
#define  SEGE   0x04
#define  SEGN   0x08

#define  SEGA   0x01
#define  SEGJ   0x02
#define  SEGG   0x04
#define  SEGM   0x08

#define  SEGK   0x01
#define  SEGL   0x02
#define  SEGD   0x04


//Ascii table American Standar
#define _ALLON  (SEG1  | SEG2 | SEG3 | SEG4 | SEG5  | SEG6 | SEG7 | SEG8)  





