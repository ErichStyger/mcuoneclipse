#include "Cpu.h"
#include "LCD.h"
#include "LCDConfig.h"

/*used to indicate in which position of the LCD is the next character to write */
static uint8 bLCD_CharPosition;
uint8 lcd_alternate_mode;  //this variable must be 0 or 4 
uint8 bflgLCD_Scroll = 0x01;

extern const uint32 *LCD_TO_PORT[];
extern const uint32 MASK_BIT[32];

char   lcdBuffer[32]; // used for temporary storage for formating strings

/*
local functions
*/
void vfnLCD_Init(void);
void vfnEnablePins(void);  // Pin Enable/ BPEN / COM configurations
void vfnSetBackplanes(void); // reconfigure COM to default values
void vfnBP_VScroll(int8 scroll_count);
void vfnLCD_Home (void);
void vfnLCD_Contrast (uint8 lbContrast);
void vfnLCD_Write_MsgPlace (uint8 *lbpMessage, uint8 lbSize );
void vfnLCD_Write_Msg (uint8 *lbpMessage);
void vfnLCD_All_Segments_ON (void);    
void vfnLCD_All_Segments_Char (uint8 val);
void vfnLCD_All_Segments_OFF (void);

void vfnLCD_Write_Char (uint8 lbValue);  // This function is dependent on the LCD panel
void PutPoint(uint8 x, uint8 y);
void ClrPoint(uint8 x, uint8 y);
void SetX(uint8 x, uint8 value);


void lcd_pinmux(uint8  mux_val);

void vfnLCD_interrupt_init(void);
void vfnLCD_isrv(void);



void print_slcd_registers(void)
{
 // printf("\n\r LCD_GCR ");
  /* 
    printf("\n\r LCD_GCR = %i",LCD_GCR);
   printf("\n\r LCD_AR = %i",LCD_AR);
   printf("\n\r LCD_FDCR = %i",LCD_FDCR);
   printf("\n\r LCD_FDSR = %i",LCD_FDSR);
   printf("\n\r LCD_PENL = %i",LCD_PENL);
  
   printf("\n\r LCD_PENH = %i",LCD_PENH);
   printf("\n\r LCD_BPENL = %i",LCD_BPENL);
   printf("\n\r LCD_BPENH = %i",LCD_BPENH);
   printf("\n\r LCD_WF3TO0 = %i",LCD_WF3TO0);
   printf("\n\r LCD_WF7TO4 = %i",LCD_WF7TO4);
   printf("\n\r LCD_WF11TO8 = %i",LCD_WF11TO8);
   printf("\n\r LCD_WF15TO12 = %i",LCD_WF15TO12);
   printf("\n\r LCD_WF19TO16 = %i",LCD_WF19TO16);
   printf("\n\r LCD_WF23TO20 = %i",LCD_WF23TO20);
   printf("\n\r LCD_WF27TO24 = %i",LCD_WF27TO24);
   printf("\n\r LCD_WF31TO28 = %i",LCD_WF31TO28);
   printf("\n\r LCD_WF35TO32 = %i",LCD_WF35TO32);
   printf("\n\r LCD_WF39TO36 = %i",LCD_WF39TO36);
   printf("\n\r LCD_WF43TO40 = %i",LCD_WF43TO40);
   printf("\n\r LCD_WF47TO44 = %i",LCD_WF47TO44);
   printf("\n\r LCD_WF51TO48 = %i",LCD_WF51TO48);
   printf("\n\r LCD_WF55TO52 = %i",LCD_WF55TO52);
   printf("\n\r LCD_WF59TO56 = %i",LCD_WF59TO56);
   printf("\n\r LCD_WF63TO60 = %i",LCD_WF63TO60);

*/
}
                      
void vfnLCD_Init(void)
{
     SIM_SCGC5 |= SIM_SCGC5_SLCD_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
     
     //* configure pins for LCD operation    
  PORTC_PCR20 = 0x00000000;     //VLL2
  PORTC_PCR21 = 0x00000000;     //VLL1
  PORTC_PCR22 = 0x00000000;     //VCAP2
  PORTC_PCR23 = 0x00000000;     //VCAP1

     
     
     // Enable IRCLK 
     MCG_C1  = MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK;
     MCG_C2 &= ~MCG_C2_IRCS_MASK ;  //0 32KHZ internal reference clock; 1= 4MHz irc


     vfnLCD_interrupt_init();       
     
     LCD_GCR = 0x0;
     LCD_AR  = 0x0;

 //    lcd_pinmux(0); 
     
/* LCD configurartion according to */     
      LCD_GCR =  (   LCD_GCR_RVEN_MASK*_LCDRVEN  
                   | LCD_GCR_RVTRIM(_LCDRVTRIM)    //0-15
                   | LCD_GCR_CPSEL_MASK*_LCDCPSEL 
                   | LCD_GCR_LADJ(_LCDLOADADJUST)     //0-3*/
                   | LCD_GCR_VSUPPLY_MASK*_LCDSUPPLY  //0-1*/
                   |!LCD_GCR_FDCIEN_MASK
                   | LCD_GCR_ALTDIV(_LCDALTDIV)  //0-3
                   |!LCD_GCR_LCDDOZE_MASK  
                   |!LCD_GCR_LCDSTP_MASK
                   |!LCD_GCR_LCDEN_MASK    //WILL BE ENABLE ON SUBSEQUENT STEP
                   | LCD_GCR_SOURCE_MASK*_LCDCLKSOURCE
                   | LCD_GCR_ALTSOURCE_MASK*_LCDALRCLKSOURCE  
                   | LCD_GCR_LCLK(_LCDLCK)   //0-7
                   | LCD_GCR_DUTY(_LCDDUTY)   //0-7
                 );    
     
      lcd_alternate_mode = LCD_NORMAL_MODE;          //Message will be written to default backplanes  if = 4
     
      vfnEnablePins();         // Enable LCD pins and Configure BackPlanes
 
      
      LCD_GCR |= LCD_GCR_LCDEN_MASK;
   /*   LCD_GCR |= LCD_GCR_LCDIEN_MASK;    // Enable interrupts */
      
      
   /* Configure LCD Auxiliar Register*/   
      LCD_AR  = LCD_AR_BRATE(_LCDBLINKRATE); // all other flags set as zero
     // print_slcd_registers();
}
  

/* Enable pins according  WF_ORDERING_TABLE, BP_ORDERING_TABLE
 //Enable the LCD module frontplane waveform output (FP[39:0])
  LCD_PENH = 0xFFFFFFFF;
  LCD_PENL = 0xFFFFFFFF;

*/

  void vfnEnablePins (void)
  {
   uint8 i;
   uint32 *p_pen;
   uint8 pen_offset;   // 0 or 1   
   uint8 pen_bit;      //0 to 31

   LCD_PENL = 0x0;
   LCD_PENH = 0x0;
   LCD_BPENL = 0x0;
   LCD_BPENH = 0x0;
   
   p_pen = (uint32 *)&LCD_PENL;

    for (i=0;i<_LCDUSEDPINS;i++) 
    {
      pen_offset = WF_ORDERING_TABLE[i]/32;
      pen_bit    = WF_ORDERING_TABLE[i]%32;
      p_pen[pen_offset] |= MASK_BIT[pen_bit];
      if (i>= _LCDFRONTPLANES)    // Pin is a backplane
      {
        p_pen[pen_offset+2] |= MASK_BIT[pen_bit];  // Enable  BPEN 
        LCD_WF8B((uint8)WF_ORDERING_TABLE[i]) = MASK_BIT[i - _LCDFRONTPLANES];   // fill with 0x01, 0x02, etc 
      } 
    }
  }
  
/*
  Fill Backplanes with normal mask for  0x01, 0x02,  according to BP_ORDERING_TABLE;
*/
void vfnSetBackplanes(void)
 {
   uint8 i;
   for (i=0;i<_LCDBACKPLANES;i++)
   {
       LCD_WF8B((uint8)WF_ORDERING_TABLE[i+_LCDFRONTPLANES]) = 0x01<<i;
   }  
  }

 
 /*
 
 rotate Backplanes  scroll_y units
   if scroll_y>0  rotate to the right
   if scroll_y<0  rotate to the left
   if scroll_y=0  set normal configuration

*/
void vfnBP_VScroll(int8 scroll_count)
 {
   uint8 bp_count;
   if (scroll_count != 0)
   {  
    for (bp_count=0;bp_count< _LCDBACKPLANES; bp_count++)
    {
       if (scroll_count>0)
         LCD_WF8B((uint8)WF_ORDERING_TABLE[_LCDFRONTPLANES +bp_count]) =  0x01<<(scroll_count+bp_count);
      else   //(scroll_count<0)
        { 
           LCD_WF8B((uint8)WF_ORDERING_TABLE[_LCDFRONTPLANES +bp_count]) =   0x01>>(-scroll_count+bp_count);       
        }
    }  
   }
    else vfnSetBackplanes(); 
  }



void vfnLCD_Home (void)
 {
      bLCD_CharPosition =  0;
 }

void vfnLCD_Contrast (uint8 lbContrast)
{
       lbContrast &= 0x0F;                                               //Forced to the only values accepted 
       LCD_GCR |= LCD_GCR_RVTRIM(lbContrast);
}
 
 void  vfnLCD_Write_MsgPlace (uint8 *lbpMessage, uint8 lbSize )
 {
          
          if (lbSize > _CHARNUM)
          {
               vfnLCD_Scroll(lbpMessage, lbSize);
          }
          else
          {
            do
            {
                    vfnLCD_Write_Char (*lbpMessage);
                    lbpMessage ++;     
             }while (--lbSize);
          }

 }
 
 
 
 /*
 vfnLCD_Write_Msg.  Display a Message starting at the first character of display
   until _CHARNUM  or End of string.
 */
 
void  vfnLCD_Write_Msg (uint8 *lbpMessage) {
  uint8 lbSize      = 0;          
  bLCD_CharPosition = 0;  //Home display
  while (lbSize<_CHARNUM && *lbpMessage!='\0') {
    vfnLCD_Write_Char(*lbpMessage++);
    lbSize++;     
  }
  if (lbSize<_CHARNUM) {
    while (lbSize++< _CHARNUM) {
      vfnLCD_Write_Char(BLANK_CHARACTER);  // complete data with blanks
    }
  }
}

void vfnLCD_All_Segments_ON (void)
{
 uint8 lbTotalBytes = _CHARNUM * _LCDTYPE;              
 uint8 lbCounter=0;
 uint8 *lbpLCDWF;
 
    lbpLCDWF = (uint8 *)&LCD_WF3TO0;
      
        while (lbCounter < lbTotalBytes)
          {
              lbpLCDWF[(uint8)WF_ORDERING_TABLE[lbCounter++]]=_ALLON;
          }
         
}


void vfnLCD_All_Segments_Char (uint8 val)
{
 uint8 lbTotalBytes = _CHARNUM * _LCDTYPE;              
 uint8 lbCounter=0;
 uint8 *lbpLCDWF;
    lbpLCDWF = (uint8 *)&LCD_WF3TO0;
        while (lbCounter < lbTotalBytes)
          {
              lbpLCDWF[WF_ORDERING_TABLE[lbCounter++]]=val;
          }
         
}


void vfnLCD_All_Segments_OFF (void)
{              
 uint8 lbTotalBytes = _CHARNUM * _LCDTYPE;              
 uint8 lbCounter=0;
 uint8 *lbpLCDWF;
 
    lbpLCDWF = (uint8 *)&LCD_WF3TO0;
        while (lbCounter < lbTotalBytes)
          {
              lbpLCDWF[WF_ORDERING_TABLE[lbCounter++]]=0;
          }
}


         
/*

 Write a Char at position bLCD_CharPosition;
 After write is complete  bLCD_CharPosition point to next position 
 
 Verify Char is a Valid character  between '0'  and 'z'
 in this case char is between 'a' to 'z' are taken as upper case
 
 If the char is a invalid char it is taken as ':'  code, in this case as SPACE

Aug-16   LP  arrayOffset was added due that array size with matrix symbols is greater than uint8

*/
#ifdef DOT_MATRIX

void vfnLCD_Write_Char (uint8 lbValue)
{
          uint8 char_val, temp;   //for test only
          uint8 *lbpLCDWF;
          uint8 lbCounter;
          
          uint16 arrayOffset;
          uint8 position;

          
          lbpLCDWF = (uint8 *)&LCD_WF3TO0;
          
          
/*only ascci character if value not writeable write as @*/

          if (lbValue>='a' && lbValue<='z') lbValue -= 32; // UpperCase
          if (lbValue<ASCCI_TABLE_START || lbValue >ASCCI_TABLE_END) lbValue = BLANK_CHARACTER;  // default value as space

          lbValue -=ASCCI_TABLE_START;        // Remove the offset to search in the ascci table
          
          arrayOffset = (lbValue * _CHAR_SIZE); // Compensate matrix offset
          
          
          
// ensure bLCD position is in valid limit
          
          lbCounter =0;  //number of writings to complete one char
          while (lbCounter<_CHAR_SIZE  && bLCD_CharPosition < _CHARNUM )
          {
              //    position = (bLCD_CharPosition) *_CHAR_SIZE + lbCounter; //-1 to compensate first incomplete character
              //     position = (bLCD_CharPosition) *_LCDTYPE + lbCounter; //-1 to compensate first incomplete character
                     position = bLCD_CharPosition; // for DOt matrix 
            
                    
                    char_val = ASCII_TO_WF_CODIFICATION_TABLE[arrayOffset + lbCounter]; 
                    if (bLCD_CharPosition==0) //write complete character
                    {
                     lbpLCDWF[WF_ORDERING_TABLE[position]] = char_val;  //all 4 bits correspond to 7 digit character
                    }
                    else  //bit0 of second character is a symbol (DP o COL on the LCD) and must not be written
                    {
                    
                      temp = lbpLCDWF[WF_ORDERING_TABLE[position]] & 0x01;  //bit 0 correspond to a Symbol
                      lbpLCDWF[WF_ORDERING_TABLE[position]] = char_val | temp;  //only bit 1,2,3 correspond to 7 digit character
                    }  
                    
                    if (char_val==0) lbCounter = _CHAR_SIZE; //end of this character
                    lbCounter++;
                    bLCD_CharPosition++;
          }

}

#else

// For 7 Segment LCD
void vfnLCD_Write_Char (uint8 lbValue) {
  uint8 char_val;
  uint8 temp;
  uint8 *lbpLCDWF;
  uint8 lbCounter;
  uint16 arrayOffset;
  uint8 position;
  
  lbpLCDWF = (uint8 *)&LCD_WF3TO0;
  /* only ascii character if value not writeable write as @ */
  if (lbValue>='a' && lbValue<='z') {
    lbValue -= 32; // UpperCase
  }
  if (lbValue<ASCCI_TABLE_START || lbValue >ASCCI_TABLE_END) {
    lbValue = BLANK_CHARACTER;  // default value as space
  }
  lbValue -=ASCCI_TABLE_START;        // Remove the offset to search in the ascci table
  arrayOffset = (lbValue * _CHAR_SIZE); // Compensate matrix offset
  // ensure bLCD position is in valid limit
  lbCounter = 0;  //number of writings to complete one char
  while (lbCounter<_CHAR_SIZE  && bLCD_CharPosition < _CHARNUM) {
    position = (bLCD_CharPosition) *_LCDTYPE + lbCounter; 
    temp=0;
    if (lbCounter==1) {
      temp = lbpLCDWF[WF_ORDERING_TABLE[position]] & 0x01;//bit 0 has the special symbol information
    } 
    char_val = ASCII_TO_WF_CODIFICATION_TABLE[arrayOffset + lbCounter];
    lbpLCDWF[WF_ORDERING_TABLE[position]] = char_val | temp;
    //  if (char_val==0) lbCounter = _CHAR_SIZE; //end of this character
    lbCounter++;
  }
  bLCD_CharPosition++;
}

#endif



void PutPoint(uint8 x, uint8 y)
 {
   uint8 *lbpLCDWF;
   lbpLCDWF = (uint8 *)&LCD_WF3TO0;
   
   if (x>= _CHARNUM  || y>7) return;
   lbpLCDWF[WF_ORDERING_TABLE[x]] |= (1<<y); 
       
 }
 

void ClrPoint(uint8 x, uint8 y)
 {
   uint8 *lbpLCDWF;
              lbpLCDWF = (uint8 *)&LCD_WF3TO0;
              if (x>= _CHARNUM  || y>7) return;
              lbpLCDWF[WF_ORDERING_TABLE[x]] &= ~(1<<y); 
 
 }
 
 

void SetX(uint8 x, uint8 value)
 {
   uint8 *lbpLCDWF;
   lbpLCDWF = (uint8 *)&LCD_WF3TO0;
 
              if (x>= _CHARNUM) return;
              lbpLCDWF[WF_ORDERING_TABLE[x]] = value;  
      
 }
 


/*
 Configure LCD used pins as MUX=0  for LCD normal operation (analog operation)
 Configure LCD used pins as MUX=7  for LCD Fault detectionoperation (pull resistor  control enabled)
 only 0 or 7 is allowed for LCD operation
*/ 

void lcd_pinmux(uint8  mux_val)
{
   uint8 i;
  
   for (i=0;i< _LCDUSEDPINS; i++)
   {
      *(uint32 *)LCD_TO_PORT[WF_ORDERING_TABLE[i]] &= ~PORT_PCR_MUX_MASK; //Clear previos value
      *(uint32 *)LCD_TO_PORT[WF_ORDERING_TABLE[i]] |= PORT_PCR_MUX(mux_val); // Set new value
   }
}
 
/*
  vfnLCD_interrupt_init
 for kinetis NVIC must be initialized in order to 

*/
void vfnLCD_interrupt_init(void)
{

}

/*


*/
void vfnLCD_isrv(void) 
 {
   LcdInterruptCallBack(); // User defined function
 }


/*
   This table relates LCD_Px to PORT Control Pin
   in used for pinmux function
*/


const uint32 *LCD_TO_PORT[60] =
 {
    (uint32 *) &PORTB_PCR0,  //LCD_P00
    (uint32 *) &PORTB_PCR1,  //LCD_P01
    (uint32 *) &PORTB_PCR2,  //LCD_P02
    (uint32 *) &PORTB_PCR3,  //LCD_P03
    (uint32 *) &PORTC_PCR20,  //LCD_P04
    (uint32 *) &PORTC_PCR21,  //LCD_P05
    //(uint32 *) &PORTC_PCR22,  //LCD_P06
    (uint32 *) &PORTB_PCR0,  //LCD_P00  test
    
    (uint32 *) &PORTB_PCR7,  //LCD_P07
    (uint32 *) &PORTB_PCR8,  //LCD_P08
    (uint32 *) &PORTB_PCR9,  //LCD_P09
    (uint32 *) &PORTB_PCR10,  //LCD_P10
    (uint32 *) &PORTB_PCR11,  //LCD_P11
    (uint32 *) &PORTB_PCR16,  //LCD_P12
    (uint32 *) &PORTB_PCR17,  //LCD_P13
    (uint32 *) &PORTB_PCR18,  //LCD_P14
    (uint32 *) &PORTB_PCR19,  //LCD_P15
    (uint32 *) &PORTB_PCR20,  //LCD_P16
    (uint32 *) &PORTB_PCR21,  //LCD_P17
    (uint32 *) &PORTB_PCR22,  //LCD_P18
    (uint32 *) &PORTB_PCR23,  //LCD_P19
    (uint32 *) &PORTC_PCR0,  //LCD_P20
    (uint32 *) &PORTC_PCR1,  //LCD_P21
    (uint32 *) &PORTC_PCR2,  //LCD_P22
    (uint32 *) &PORTC_PCR3,  //LCD_P23
    (uint32 *) &PORTC_PCR4,  //LCD_P24
    (uint32 *) &PORTC_PCR5,  //LCD_P25
    (uint32 *) &PORTC_PCR6,  //LCD_P26
    (uint32 *) &PORTC_PCR7,  //LCD_P27
    (uint32 *) &PORTC_PCR8,  //LCD_P28
    (uint32 *) &PORTC_PCR9,  //LCD_P29
    (uint32 *) &PORTC_PCR10,  //LCD_P30
    (uint32 *) &PORTC_PCR11,  //LCD_P31
    (uint32 *) &PORTC_PCR12,  //LCD_P32
    (uint32 *) &PORTC_PCR13,  //LCD_P33
    (uint32 *) &PORTC_PCR16,  //LCD_P36
    (uint32 *) &PORTC_PCR17,  //LCD_P37
    (uint32 *) &PORTC_PCR18,  //LCD_P38
    (uint32 *) &PORTC_PCR23,  //LCD_P39
    (uint32 *) &PORTD_PCR0,  //LCD_P40
    (uint32 *) &PORTD_PCR1,  //LCD_P41
    (uint32 *) &PORTD_PCR2,  //LCD_P42
    (uint32 *) &PORTD_PCR3,  //LCD_P43
    (uint32 *) &PORTD_PCR4,  //LCD_P44
    (uint32 *) &PORTD_PCR5,  //LCD_P45
    (uint32 *) &PORTD_PCR6,  //LCD_P46
    (uint32 *) &PORTD_PCR7,  //LCD_P47
    (uint32 *) &PORTE_PCR0,  //LCD_P48
    (uint32 *) &PORTE_PCR1,  //LCD_P49
    (uint32 *) &PORTE_PCR2,  //LCD_P50
    (uint32 *) &PORTE_PCR3,  //LCD_P51
    (uint32 *) &PORTE_PCR4,  //LCD_P52
    (uint32 *) &PORTE_PCR5,  //LCD_P53
    (uint32 *) &PORTE_PCR6,  //LCD_P54
    (uint32 *) &PORTE_PCR16,  //LCD_P55
    (uint32 *) &PORTE_PCR17,  //LCD_P56
    (uint32 *) &PORTE_PCR18,  //LCD_P57
    (uint32 *) &PORTE_PCR19,  //LCD_P58
    (uint32 *) &PORTE_PCR20,  //LCD_P59
    (uint32 *) &PORTE_PCR21,  //LCD_P60


    };

const uint32 MASK_BIT[32] = 
{
       0x00000001 ,
       0x00000002 ,
       0x00000004 ,
       0x00000008 ,
       0x00000010 ,
       0x00000020 ,
       0x00000040 ,
       0x00000080 ,
       0x00000100 ,
       0x00000200 ,
       0x00000400 ,
       0x00000800 ,
       0x00001000 ,
       0x00002000 ,
       0x00004000 ,
       0x00008000 ,
       0x00010000 ,
       0x00020000 ,
       0x00040000 ,
       0x00080000 ,
       0x00100000 ,
       0x00200000 ,
       0x00400000 ,
       0x00800000 ,
       0x01000000 ,
       0x02000000 ,
       0x04000000 ,
       0x08000000 ,
       0x10000000 ,
       0x20000000 ,
       0x40000000 ,
       0x80000000 ,
};

