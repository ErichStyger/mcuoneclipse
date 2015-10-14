#include "derivative.h"

const unsigned char ascii[] = {  
 /* */ 0x00,0x00, 
 /*!*/ 0x00,0x00, 
 /*"*/ 0x00,0x00, 
 /*#*/ 0x00,0x00, 
 /*$*/ 0x00,0x00, 
 /*%*/ 0x00,0x00, 
 /*&*/ 0x00,0x00, 
 /*'*/ 0x00,0x00, 
 /*(*/ 0x00,0xA3, 
 /*)*/ 0x93,0x00, 
 /***/ 0x6C,0x5C, 
 /*+*/ 0x0C,0x18, 
 /*,*/ 0x00,0x00, 
 /*-*/ 0x08,0x10, 
 /*.*/ 0x00,0x00, 
 /* */ 0x00,0x00, 
 /*0*/ 0x97,0xE3, 
 /*1*/ 0x12,0x00, 
 /*2*/ 0x8b,0xb1, 
 /*3*/ 0x9b,0x91, 
 /*4*/ 0x1A,0x12, 
 /*5*/ 0x99,0x93, 
 /*6*/ 0x99,0xb3, 
 /*7*/ 0x13,0x01, 
 /*8*/ 0x9b,0xb3, 
 /*9*/ 0x9b,0x93, 
 /*:*/ 0x00,0x00, 
 /*;*/ 0x00,0x00, 
 /*<*/ 0x00,0x00, 
 /*=*/ 0x40,0x04, 
 /*>*/ 0x00,0x00, 
 /*?*/ 0x00,0x00, 
 /*@*/ 0x00,0x00, 
 /*A*/ 0x1B,0x33,   
 /*B*/ 0xDB,0x89,  
 /*C*/ 0x81,0xA3,  
 /*D*/ 0xD3,0x89,  
 /*E*/ 0x89,0xB3,     
 /*F*/ 0x09,0x33,   
 /*G*/ 0xc9,0xA3,  
 /*H*/ 0x1A,0x32, 
 /*I*/ 0xC1,0x89,   
 /*J*/ 0x41,0xA9,   
 /*K*/ 0x24,0x32,   
 /*L*/ 0x80,0xA2,    
 /*M*/ 0x16,0x26,   
 /*N*/ 0x32,0x26,   
 /*O*/ 0x93,0xA3, 
 /*P*/ 0x0B,0x33, 
 /*Q*/ 0xB3,0xA3, 
 /*R*/ 0x2B,0x33, 
 /*S*/ 0x99,0x93, 
 /*T*/ 0x41,0x09,   
 /*U*/ 0x92,0xa2,   
 /*V*/ 0x32,0x04,   
 /*W*/ 0x32,0x62, 
 /*X*/ 0x24,0x44,   
 /*Y*/ 0x44,0x04,   
 /*Z*/ 0x85,0xc1,   
 /*[ */ 0x00,0xA3, 
 /*\ */ 0x40,0x04,  
 /*] */ 0x93,0x00, 
 /*^ */ 0x00,0x00,  
 /*_ */ 0x80,0x80,  
 };
 
 
 void SetAlpha(char alphanum, char data){
   
   
   data = (data-32)*2;
   
 switch(alphanum) {
 
  case 1:
  LCDWF2 = ascii[data];
  LCDWF5 = ascii[data+1];
  break;
  
  case 2:
  LCDWF14 = ascii[data];
  LCDWF11 = ascii[data+1];
  break;

  case 3:
  LCDWF12 = ascii[data];
  LCDWF10 = ascii[data+1];
  break;
  
  case 4:
  LCDWF15 = ascii[data];
  LCDWF13 = ascii[data+1];
  break;
  
  case 5:
  LCDWF19 = ascii[data];
  LCDWF18 = ascii[data+1];
  break;


  case 6:
  LCDWF22 = ascii[data];
  LCDWF21 = ascii[data+1];
  break;
  
  case 7:
  LCDWF25 = ascii[data];
  LCDWF24 = ascii[data+1];
  break;
  
  case 8:
  LCDWF20 = ascii[data];
  LCDWF23 = ascii[data+1];
  break;
  
  case 9:
  LCDWF31 = ascii[data];
  LCDWF17 = ascii[data+1];
  break;
  
default:
                             
      break;
 }
 
 
 
 }
 
 void ClearDisplay(void)
 {
      LCDWF2 = 0x00;
      LCDWF5 = 0x00;
      LCDWF10 = 0x00;
      LCDWF11 = 0x00;
      LCDWF12 = 0x00;
      LCDWF13 = 0x00;
      LCDWF14 = 0x00;
      LCDWF15 = 0x00;
      LCDWF16 = 0x00;  
      LCDWF17 = 0x00;
      LCDWF18 = 0x00;
      LCDWF19 = 0x00;
      LCDWF20 = 0x00;
      LCDWF21 = 0x00;
      LCDWF22 = 0x00;
      LCDWF23 = 0x00;
      LCDWF24 = 0x00;
      LCDWF25 = 0x00;
      LCDWF26 = 0x00;
      LCDWF27 = 0x00;
      LCDWF28 = 0x00;
      LCDWF29 = 0x00;
      LCDWF30 = 0x00;
      LCDWF31 = 0x00;
 }
 
 
  void SetDisplay(void){
      LCDWF2 = 0xff;
      LCDWF5 = 0xff;
      LCDWF10 = 0xff;
      LCDWF11 = 0xff;
      LCDWF12 = 0xff;
      LCDWF13 = 0xff;
      LCDWF14 = 0xff;
      LCDWF15 = 0xff;
      LCDWF16 = 0xff;  
      LCDWF17 = 0xff;
      LCDWF18 = 0xff;
      LCDWF19 = 0xff;
      LCDWF20 = 0xff;
      LCDWF21 = 0xff;
      LCDWF22 = 0xff;
      LCDWF23 = 0xff;
      LCDWF24 = 0xff;
      LCDWF25 = 0xff;
      LCDWF26 = 0xff;
      LCDWF27 = 0xff;
      LCDWF28 = 0xff;
      LCDWF29 = 0xff;
      LCDWF30 = 0xff;
      LCDWF31 = 0xff;
 }



 void Colon(char Cnum,char ON_OFF)
 {
       switch(Cnum) {
 
  case 1:
  if(ON_OFF){
    
  LCDWF16 |= 0x20;
  
  } else {
  LCDWF16 &= 0xCF;
  }
  break;
  
  case 2:
    if(ON_OFF){
    
  LCDWF27 |= 0x20;
  
  } else {
  LCDWF27 &= 0xCF;
  }
  break;

  case 3:
    if(ON_OFF){
    
  LCDWF29 |= 0x10;
  
  } else {
  LCDWF29 &= 0xEF;
  }
  break;
  
  case 4:
  if(ON_OFF){
    
  LCDWF28 |= 0x01;
  
  } else {
  LCDWF28 &= 0xFE;
  }
  break;
  
  default:
                             
      break;
 }
 }
 void Freescale(char ON_OFF)
 {
       
  if(ON_OFF){
    
  LCDWF16 |= 0x01;
  
  } else {
  LCDWF16 &= 0xfe;
  } 
 }
 
 void WriteDirection(unsigned char direction)
{

     switch(direction) {
 
  case 1:
  LCDWF26 = 0x40;
  break;
  
  case 2:
 LCDWF26 = 0x10;
  break;

  case 3:
 LCDWF26 = 0x04;
  break;
   
  case 4:
  LCDWF26 = 0x01;
  break;
  
  case 5:
  LCDWF26 = 0x01;
  break;

   case 6:
  LCDWF26 = 0x01;
  break;
  
default:
                             
      break;
 }
 
  
}
