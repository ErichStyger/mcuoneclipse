#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <string.h> /* include peripheral declarations */

#define ON  1
#define OFF 0
#define   TOP               0
#define   LEFT              1
#define   UP                2
#define   RIGHT             3
#define   DOWN              4
#define   BOTTOM            5
#define AsmStop  __asm STOP;  
 
volatile unsigned char state = 0;
volatile unsigned char sec = 5;
volatile unsigned char tsec = 5;
volatile unsigned char mins = 9;
volatile unsigned char tmins = 5;
volatile unsigned char hour = 3;
volatile unsigned char thour= 2;

volatile unsigned char Result = 0;
volatile unsigned char C_x = 0;
volatile unsigned char C_y = 0;
volatile unsigned char C_z = 0;


extern  char ascii[]; 
extern  void SetAlpha(char alphanum, char data);
extern  void ClearDisplay(void);
extern  void SetDisplay(void); 
extern  void Colon(char Cnum,char ON_OFF) ;
extern  void Freescale(char ON_OFF); 
extern  void WriteDirection(unsigned char direction);
unsigned char *string;
unsigned int length, i;
 





/////////////////////////////////////////////////////////////////////////////////////////
// Peripheral Init
// --------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////
void Sys_Peripheral_Init(void){
 
  SOPT1 =    0x63; //disable cop. enable stop.
  SPMSC1 = 0x00; //LVD disabled
 
 // For Stop2
 // SPMSC2_PPDC = 1;
  
  IRQSC_IRQPE =1;
 
////////////////////////////////////////////////////////////////////////////  
// Init ADC
////////////////////////////////////////////////////////////////////////
   ADCCFG = 0x60; 
   APCTL1_ADPC6 = 1; //Rz Light sensor
   APCTL1_ADPC0  = 1; //Pot
   APCTL1_ADPC1 = 1; //X
   APCTL1_ADPC2  = 1; //Y
   APCTL1_ADPC3 = 1; //Z
   
  
  
  
////////////////////////////////////////////////////////////////////////////  
// Init TOD
////////////////////////////////////////////////////////////////////////
  
  TODC_TODCLKS = 0;
  TODC_TODPS = 1;
  TODC_TODEN =1;
////////////////////////////////////////////////////////////////////////////  
// Init TPM
////////////////////////////////////////////////////////////////////////
      
    // Timer2 overflow about every 1ms
  TPM1MOD = 8000;
  // Stops timer2 and select 1 as prescaler divisor
  TPM1SC = 0x08;  
 
   // Timer2 overflow about every 1ms
  TPM2MOD = 8000;
  // Stops timer2 and select 1 as prescaler divisor
  TPM2SC = 0x00;
 
////////////////////////////////////////////////////////////////////////////  
// Init KBI
////////////////////////////////////////////////////////////////////////
     PTAPE = 0x80; //enable pullups for KBI7
     KBIPE = 0x80; //Enable KBI7
     KBISC_KBIE = 1; //Enable KBI Interrupts
     KBISC_KBACK  = 1; // Clear Pending interrupt
  
  EnableInterrupts;
  
  
    
////////////////////////////////////////////////////////////////////////////  
// Clock Init ICS
////////////////////////////////////////////////////////////////////////
                           ICSC2 = 0x07;
                           ICSC1 = 0x00;
////////////////////////////////////////////////////////////////////////////  
// Init GPIO
////////////////////////////////////////////////////////////////////////
       PTADD = 0x3F;
       PTBDD = 0xFF;
       PTCDD =0x7f;
       PTDDD = 0xFF;
       PTEDD =0xff;
       
       PTAD = 0x00;
       PTBD = 0x00 ;
       PTCD =0x00;
       PTDD = 0x00;
       PTED =0x00; 
       
////////////////////////////////////////////////////////////////////////////  
// Init LCD 
////////////////////////////////////////////////////////////////////////
     
   LCDPEN0 = 0xFF;
   LCDPEN1 = 0xFF;
   LCDPEN2 = 0xFF;
   LCDPEN3 = 0xFF;
    
             //Enable all LCD Pins 
    
    //Enable Back Plane Pins
    LCDBPEN0 = 0xDB; 
    LCDBPEN1 = 0x03;

     
    //Set Back Planes
    LCDWF0 = 0x01;
    LCDWF3 = 0x02;
    LCDWF6 = 0x04;
    LCDWF9 = 0x08;
    LCDWF1 = 0x10;
    LCDWF7 = 0x20;
    LCDWF4 = 0x40;
    LCDWF8 = 0x80;
      
    //Front plane data
      
      SetDisplay();
      
      
      ///LCD Control registers
      LCDRVC = 0x8b;
      LCDSUPPLY = 0x83;
      LCDC0 =    0xA7;  
      
      //Set up blink mode
      
      LCDBCTL_BRATE =4;
      //LCDBCTL_BLINK  = 1; 
     
      
    
}

////////////////////////////////////////////////////////////////////////////  
// Play sound at passed frequency for Quarter Second
////////////////////////////////////////////////////////////////////////

void PlaySound(unsigned int frequency)
{
  TPM1C0SC = 0x54;
  TPM1C0V=frequency;
  
  TODSC_QSECF =1;
  while(TODSC_QSECF ==0);
     TODSC_QSECF =1;
  while(TODSC_QSECF ==0);
  
  TPM1C0SC = 0x00;
}


////////////////////////////////////////////////////////////////////////////  
// Scroll String
////////////////////////////////////////////////////////////////////////
void ScrollString(unsigned char *strng)
{
   int j,l;
    l = strlen(strng)-8;
    j = 0;
   while(j!= l)//Scroll Demo Board   
      {
            
      SetAlpha(1,strng[j]);      
      SetAlpha(2,strng[j+1]);
      SetAlpha(3,strng[j+2]);      
      SetAlpha(4,strng[j+3]);
      SetAlpha(5,strng[j+4]);      
      SetAlpha(6,strng[j+5]);
      SetAlpha(7,strng[j+6]);
      SetAlpha(8,strng[j+7]);
      SetAlpha(9,strng[j+8]);      
               j=j+1;
              
               
      while(TODSC_QSECF == 0);
      TODSC_QSECF = 1;         
   
     
      }
   
}

////////////////////////////////////////////////////////////////////////////  
// Display String  //must be less than 9 characters
////////////////////////////////////////////////////////////////////////
void DisplayString(unsigned char *dstrng)
{
   int j,l;
   char n;
    l = strlen(dstrng);
    j = 0;
    n = 1;
      while(j!=l){
        
      SetAlpha(n,dstrng[j]);
      j = j+1;
      n++;      
      }
}



////////////////////////////////////////////////////////////////////////////  
// State 0 display time in stop mode
////////////////////////////////////////////////////////////////////////
void StopClock(void)
{
     ClearDisplay();
      
      while(TODSC_SECF == 0);
      TODSC_SECIE = 1;
      
      Colon(3,ON);
      Colon(2,ON);
      
      Freescale(ON);
      
/////////////////////STATE 0////////////////////////
//////Simple Clock in stop Mode////////////////////     
     while(state ==0){
     //display current second while in stop mode
     
     
  
      
      AsmStop;
      
    ADCSC1 = 0x20; //Read Pot 
     
    while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    
    Result = ADCRL;
    
    Result = Result/16;
    Result |=0x80;
    LCDRVC = Result; 
  //  TPM2Cx_PWM(2,25,666,0x04);
              
      SetAlpha(4,thour+48);
      SetAlpha(5,hour+48);      
      SetAlpha(6,tmins+48);
      SetAlpha(7,mins+48);
      SetAlpha(8,tsec+48);
      SetAlpha(9,sec+48); 
}

}

////////////////////////////////////////////////////////////////////////////  
// State 1 Compare Light sensor to POT and ALARM
//   if Light sensor reading is higher than POT
////////////////////////////////////////////////////////////////////////
void LightSense(void) {
    int Low, High;
    
    ClearDisplay();
    Freescale(ON);
    SetAlpha(1,'P'); 
    SetAlpha(2,'T'); 
    SetAlpha(3,'0');
    
    SetAlpha(4,'0'); 
    SetAlpha(5,' '); 
    SetAlpha(6,'R');
     
     
    SetAlpha(7,'Z'); 
    SetAlpha(8,'0'); 
    SetAlpha(9,'0'); 
    
    TODSC_SECIE = 0;
   
  ////////////STATE 1///////////////////    
 ////////// ADC Features State//////////
  /////Display POT Reading and  Rz reading
  /////Sound Alarm if RZ is Greater than POT 
  while(state == 1) {
    
    
    
    ADCSC1 = 0x20; //Read Pot 
     
    while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    Result = ADCRL;
    
    Low = Result&0x0F;
    High = (Result&0xf0)/16;
    
    if(Low<=0x09){
    SetAlpha(4,Low+48);
    } else    {
     SetAlpha(4,Low+55);}
     
      if(High<=0x09){
    SetAlpha(3,High+48);
    } else    {
     SetAlpha(3,High+55);}
     
     ADCSC1 = 0x26; //Read Rz
 while (!(ADCSC1 & 0x80));  // ADC conversion completed?
    if(ADCRL>=Result){
     PlaySound(2350);}
    
    Result = ADCRL;
    
    Low = Result&0x0F;
    High = (Result&0xf0)/16;
    
    if(Low<=0x09){
    SetAlpha(9,Low+48);
    } else    {
     SetAlpha(9,Low+55);}
     
      if(High<=0x09){
    SetAlpha(8,High+48);
    } else    {
     SetAlpha(8,High+55);}
         
 }
 
}

////////////////////////////////////////////////////////////////////////////  
// State 2 Accelerometer Demo
//   Show Right/Left UP/ Down 
////////////////////////////////////////////////////////////////////////
void AccelDemo(void) {

   unsigned char x,y,z;
 TODSC_SECIE = 0;
 ClearDisplay();
 Freescale(ON);
 
 string = "         ACCEL DEMO TILT BOARD UP DOWN LEFT RIGHT         ";
   
 ScrollString(string);
 
 /////////////////////////////////
 while(state==2){
 
 //Get X Y Z

ADCSC1 = 0x21; //Read Pot 
while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    x = ADCRL;
 
ADCSC1 = 0x22; //Read Pot 
while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    y = ADCRL;
 
 
ADCSC1 = 0x23; //Read Pot 
while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    z = ADCRL;
 
 //Check Right Left UP Down
 
 if(x>=(C_x + 25)){
 //Set Right
   
     string = "RIGHT    ";
     DisplayString(string);
     WriteDirection(RIGHT);
      PlaySound(2350);
      
 } else if(x<=(C_x -25)){
 //Set Left
     
     string = "LEFT     ";
     WriteDirection(LEFT);
     DisplayString(string);
      PlaySound(2350);
      
 } else if(y<=(C_y - 25)){
 //Set UP
     
     string = "UP       ";
     DisplayString(string);
     WriteDirection(UP);
      PlaySound(2350);
     
 } else if(y>=C_y +25){
 //Set Down
     
     string = "DOWN     ";
     DisplayString(string);
     WriteDirection(DOWN);
      PlaySound(2350);
 
 }else {
     
     string = "MOVE     ";
     DisplayString(string);
 
 }

 
 
 }
    
}

// Initialize the TPM2 for PWM outputs (Channel 2 for PTC1 LED)
void TPM2Cx_PWM(byte CHAN, byte DUTY_CYCLE, word MOD, byte CLK_PS) {

    int val;
    
    if (MOD==0) {
      
       TPM2SC=0x00;                       // disable PWM.
       return; 
    }
    if ((TPM2MODH==(MOD>>8)) && (TPM2MODL==(MOD-1))) {
      
    } else {
      
       TPM2MODH = (byte) (MOD>>8);        // set period 
       TPM2MODL = (byte) (MOD-1);
    }
    
    switch (CHAN) {
    
      case 0: 
           TPM2C0SC = 0x24;               // Center-aligned low-true pulses
           if (MOD>100){
              val = DUTY_CYCLE*(MOD/100);
           }
           else {
              val = DUTY_CYCLE*MOD/100;
           }
           
           TPM2C0VH = (byte) (val>>8);    // set duty cycle for Channel 0
           TPM2C0VL = (byte) (val);
      break;
        
      case 1:
           TPM2C1SC = 0x24;               // Center-aligned low-true pulses
           if (MOD>100){
              val = DUTY_CYCLE*(MOD/100);
           }
           else {
              val = DUTY_CYCLE*MOD/100;
           }
           
           TPM2C1VH = (byte) (val>>8);    // set duty cycle for Channel 1
           TPM2C1VL = (byte) (val);
      break;
        
      
      break;
        
      default:
      break;      
    }
    
    TPM2SC   = (byte) (0x28|(CLK_PS&0x07));        // All center-aligned, bus frequency/Prescale, start timer
} //end TPM2Cx_PWM

////////////////////////////////////////////////////////////////////////////  
// Main Routine
////////////////////////////////////////////////////////////////////////

void main(void) 
 {
  Sys_Peripheral_Init();
  
  //Calibrate Accell
  ADCSC1 = 0x21; //Read Pot 
while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    C_x = ADCRL;
 
ADCSC1 = 0x22; //Read Pot 
while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    C_y = ADCRL;
 
 
ADCSC1 = 0x23; //Read Pot 
while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    C_z = ADCRL;
  
  
  string = "         9S08LL16 DEMO BOARD         ";
  
  ScrollString(string);
 state = 3;

     string = "LOGICANLY";
     DisplayString(string);

 for(;;)  //Main Loop
 
 {   
    ADCSC1 = 0x20; //Read Pot 
     
    while (!(ADCSC1 & 0x80));  // Waits until ADC conversion is completed
    
    Result = ADCRL;
 
       TPM2Cx_PWM(0,(byte)((Result&0x00FF)>>1),666,0x07);
        TPM2Cx_PWM(1,(byte)((Result&0x00FF)>>1),666,0x07);
  
  if(state == 0)
      { StopClock(); //clock demo
       }else if(state ==1){
          LightSense(); //light sense demo
       }else if(state ==2){
            AccelDemo();  //Accelerometer Demo
       }
    }    
 }

   /* loop forever */




/////////////////////////////////////////////////////////////////////////////////////////
// KBI_ISR
// --------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////
interrupt VectorNumber_Vkeyboard void KBI_ISR(void){
 

  if (PTAD_PTAD7 == 0)
    {
    while(PTAD_PTAD7 ==0);
    while(PTAD_PTAD7 ==0);
    if(PTAD_PTAD7 ==1){
      
    if(state >=2){
    state =0 ;
    }else {
      state = state +1 ;
    }
    } 
    }
  
  
  
  
  //clear KBF
  KBISC_KBACK = 1;
  
}

/////////////////////////////////////////////////////////////////////////////////////////
// TOD_ISR
// --------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////
interrupt VectorNumber_Vtod void tod_ISR(void){
                TODSC_SECF = 1; 
       sec = sec +1;
       
       if(sec ==10) {
       tsec = tsec +1;
       sec =0; 
       
       }
       if(tsec ==6){
       mins = mins +1;
       tsec = 0;
       }
       
       if (mins == 10){
       tmins = tmins +1;
       mins =0;
       
       }
       if(tmins == 6){
       hour = hour +1;
       tmins = 0;
       }
       
       if(hour  == 10){
       thour = thour +1;
       hour  = 0;
       }
       
       if ((thour == 2)&&(hour ==4)){
       thour = 0;
       hour = 0 ;
       
       }
  
}

/////////////////////////////////////////////////////////////////////////////////////////
// TPM_ISR
// --------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////

interrupt VectorNumber_Vtpm1ch0 void timer1_CH0(void)
{
  
  // Clear CH0F flag
  TPM1C0SC &=0x7F;
 
  //Clear the 16-bit timer1 counter
  TPM1CNTH = 0x00;
  
}