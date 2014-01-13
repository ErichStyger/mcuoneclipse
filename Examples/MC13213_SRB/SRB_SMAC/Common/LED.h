/**
 * \file
 * \brief LED driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic LED driver for up to 5 LEDs.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef LED_H_
#define LED_H_

#include "Platform.h"

#if PL_HAS_LED
/*! \todo Implement following interface. Does not have to be with functions. Consider macros for efficiency. */
#if 0
void LED1_On(void);
void LED2_On(void);
void LED3_On(void);
void LED4_On(void);
void LED5_On(void);

void LED1_Off(void);
void LED2_Off(void);
void LED3_Off(void);
void LED4_Off(void);
void LED5_Off(void);

void LED1_Neg(void);
void LED2_Neg(void);
void LED3_Neg(void);
void LED4_Neg(void);
void LED5_Neg(void);

uint8_t LED1_Get(void);
uint8_t LED2_Get(void);
uint8_t LED3_Get(void);
uint8_t LED4_Get(void);
uint8_t LED5_Get(void);

void LED1_Put(uint8_t val);
void LED2_Put(uint8_t val);
void LED3_Put(uint8_t val);
void LED4_Put(uint8_t val);
void LED5_Put(uint8_t val);
#endif

  #if PL_LED_CATHODE_PIN
    #define LED_TURN_ON(nr)  (LED##nr##_ClrVal())       
       /*!< Macro to turn a numbered cathode LED on */
    #define LED_TURN_OFF(nr) (LED##nr##_SetVal())       
       /*!< Macro to turn a numbered cathode LED off */
    #define LED_TEST(nr)     (LED##nr##_GetVal()==0)    
       /*!< Macro which test if a cathode LED is on (returns FALSE if off and TRUE if LED is on) */
    #define LED_PUT(nr,val)  (LED##nr##_PutVal(!(val))) 
       /*!< Macro to set a cathode LED value. Pass TRUE to turn it on and FALSE to turn it off) */
  #else
    #define LED_TURN_ON(nr)  (LED##nr##_SetVal())       
      /*!< Macro to turn a numbered anode LED on */
    #define LED_TURN_OFF(nr) (LED##nr##_ClrVal())       
      /*!< Macro to turn a numbered anode LED off */
    #define LED_TEST(nr)     (LED##nr##_GetVal()!=0)    
      /*!< Macro which test if an anode LED is on (returns FALSE if off and TRUE if LED is on) */
    #define LED_PUT(nr,val)  (LED##nr##_PutVal(val))    
      /*!< Macro to set an anode LED value. Pass TRUE to turn it on and FALSE to turn it off) */
  #endif

  #if PL_NOF_LED >= 1
    #include "LED1.h"
    #define LED1_On()     (LED_TURN_ON(1))    
      /*!< Macro to turn LED on */
    #define LED1_Off()    (LED_TURN_OFF(1))   
      /*!< Macro to turn LED off */
    #define LED1_Neg()    (LED1_NegVal())     
      /*!< Macro to negate LED */
    #define LED1_Get()    (LED_TEST(1))       
      /*!< Macro to get LED value */
    #define LED1_Put(val) (LED_PUT(1,val))    
      /*!< Macro to put LED value */
  #else  
    #define LED1_On()     /* nothing */
    #define LED1_Off()    /* nothing */
    #define LED1_Neg()    /* nothing */
    #define LED1_Get()    0
    #define LED1_Put(x)   /* nothing */
  #endif
  #if PL_NOF_LED >= 2
    #include "LED2.h"
    #define LED2_On()     (LED_TURN_ON(2))  
      /*!< Macro to turn LED on */
    #define LED2_Off()    (LED_TURN_OFF(2)) 
      /*!< Macro to turn LED off */
    #define LED2_Neg()    (LED2_NegVal())   
      /*!< Macro to negate LED */
    #define LED2_Get()    (LED_TEST(2))     
      /*!< Macro to get LED value */
    #define LED2_Put(val) (LED_PUT(2,val))  
      /*!< Macro to put LED value */
  #else  
    #define LED2_On()   
      /*!< nothing */
    #define LED2_Off()  
      /*!< nothing */
    #define LED2_Neg()  
      /*!< nothing */
    #define LED2_Get()  0
      /*!< no LED, just returning zero */
    #define LED2_Put(x) 
      /*!< nothing */
  #endif
  #if PL_NOF_LED >= 3
    #include "LED3.h"
    #define LED3_On()     (LED_TURN_ON(3))  
      /*!< Macro to turn LED on */    
    #define LED3_Off()    (LED_TURN_OFF(3)) 
      /*!< Macro to turn LED off */
    #define LED3_Neg()    (LED3_NegVal())   
      /*!< Macro to negate LED */
    #define LED3_Get()    (LED_TEST(3))     
      /*!< Macro to get LED value */
    #define LED3_Put(val) (LED_PUT(3,val))  
      /*!< Macro to put LED value */
  #else  
    #define LED3_On()   /* nothing */       /*!< Macro to turn LED on */
    #define LED3_Off()  /* nothing */
    #define LED3_Neg()  /* nothing */
    #define LED3_Get()  0
    #define LED3_Put(x) /* nothing */
  #endif
  #if PL_NOF_LED >= 4
    #include "LED4.h"
    #define LED4_On()     (LED_TURN_ON(4))  
      /*!< Macro to turn LED on */
    #define LED4_Off()    (LED_TURN_OFF(4)) 
      /*!< Macro to turn LED off */
    #define LED4_Neg()    (LED4_NegVal())   
      /*!< Macro to negate LED */
    #define LED4_Get()    (LED_TEST(4))     
      /*!< Macro to get LED value */
    #define LED4_Put(val) (LED_PUT(4,val))  
      /*!< Macro to put LED value */
  #else  
    #define LED4_On()   /* nothing */
    #define LED4_Off()  /* nothing */
    #define LED4_Neg()  /* nothing */
    #define LED4_Get()  0
    #define LED4_Put(x) /* nothing */
  #endif
  #if PL_NOF_LED >= 5
    #include "LED5.h"
    #define LED5_On()     (LED_TURN_ON(5))  
      /*!< Macro to turn LED on */
    #define LED5_Off()    (LED_TURN_OFF(5)) 
      /*!< Macro to turn LED off */
    #define LED5_Neg()    (LED5_NegVal())   
      /*!< Macro to negate LED */
    #define LED5_Get()    (LED_TEST(5))     
      /*!< Macro to get LED value */
    #define LED5_Put(val) (LED_PUT(5,val))  
      /*!< Macro to put LED value */
  #else  
    #define LED5_On()   /* nothing */
    #define LED5_Off()  /* nothing */
    #define LED5_Neg()  /* nothing */
    #define LED5_Get()  0
    #define LED5_Put(x) /* nothing */
  #endif

#if PL_HAS_SHELL
  #include "CLS1.h"

/*!
   * \brief Parses a command
   * \param cmd Command string to be parsed
   * \param handled Sets this variable to TRUE if command was handled
   * \param io I/O stream to be used for input/output
   * \return Error code, ERR_OK if everything was fine
   */
  uint8_t LED_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif
  
/*! \brief LED driver initialization */
void LED_Init(void);

#endif /* PL_HAS_LED */

#endif /* LED_H_ */
