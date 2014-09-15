/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_GPIO.h
*
* @brief  Macros and constants to control the GPIOs
*
* @version 1.0.29.0
* 
* @date Sep-12-2012
* 
*
***********************************************************************************************************************/


#ifndef TSS_GPIO_H
  #define TSS_GPIO_H

  #include "TSS_Sensor.h"

  /* PORT identificators */    
  
  #define TSS_PORTX_CHK     0xFF
  
  #define TSS_PORTM_CHK     0x10 >> 4         /* Identificatior of All PORT Method using electrodes */      

  #define TSS_PORTAX_CHK    0x10 
  #define TSS_PORTA_CHK     0x10

  #define TSS_PORTBX_CHK    0x11
  #define TSS_PORTB_CHK     0x11

  #define TSS_PORTCX_CHK    0x12
  #define TSS_PORTC_CHK     0x12
  
  #define TSS_PORTDX_CHK    0x13
  #define TSS_PORTD_CHK     0x13

  #define TSS_PORTEX_CHK    0x14
  #define TSS_PORTE_CHK     0x14

  #define TSS_PORTFX_CHK    0x15
  #define TSS_PORTF_CHK     0x15

  #define TSS_PORTGX_CHK    0x16
  #define TSS_PORTG_CHK     0x16

  #define TSS_PORTHX_CHK    0x17
  #define TSS_PORTH_CHK     0x17

  #define TSS_PORTIX_CHK    0x18
  #define TSS_PORTI_CHK     0x18

  #define TSS_PORTJX_CHK    0x19
  #define TSS_PORTJ_CHK     0x19
  
  /* Decoding Macros */
  #define TSS_ELEC_PORT2NAME_RESULT(res)      TSS_PORT##res##_CHK
  #define TSS_ELEC_PORT2NAME_CONV(text)       TSS_ELEC_PORT2NAME_RESULT(text)
  #define TSS_ELEC_PORT_CHK(elec)             TSS_ELEC_PORT2NAME_CONV(elec)
  
  /*********************************************************************************
  *    Determination what PORT  is used for later conditional PORT module 
  *    initialization
  *********************************************************************************/

  #define TSS_DETECT_EL_PORT(el,port)   (TSS_ELEC_PORT_CHK(TSS_E##el##_P) == TSS_PORT##port##X_CHK)

  #define TSS_DETECT_PORT(port)         (TSS_DETECT_EL_PORT(0,port) || TSS_DETECT_EL_PORT(1,port) || TSS_DETECT_EL_PORT(2,port) || TSS_DETECT_EL_PORT(3,port) || TSS_DETECT_EL_PORT(4,port) || TSS_DETECT_EL_PORT(5,port) || TSS_DETECT_EL_PORT(6,port) || TSS_DETECT_EL_PORT(7,port) || TSS_DETECT_EL_PORT(8,port) || TSS_DETECT_EL_PORT(9,port) || TSS_DETECT_EL_PORT(10,port) || TSS_DETECT_EL_PORT(11,port) || TSS_DETECT_EL_PORT(12,port) || TSS_DETECT_EL_PORT(13,port) || TSS_DETECT_EL_PORT(14,port) || TSS_DETECT_EL_PORT(15,port) || TSS_DETECT_EL_PORT(16,port) || TSS_DETECT_EL_PORT(17,port) || TSS_DETECT_EL_PORT(18,port) || TSS_DETECT_EL_PORT(19,port) || TSS_DETECT_EL_PORT(20,port) || TSS_DETECT_EL_PORT(21,port) || TSS_DETECT_EL_PORT(22,port) || TSS_DETECT_EL_PORT(23,port) || TSS_DETECT_EL_PORT(24,port) || TSS_DETECT_EL_PORT(25,port) || TSS_DETECT_EL_PORT(26,port) || TSS_DETECT_EL_PORT(27,port) || TSS_DETECT_EL_PORT(28,port) || TSS_DETECT_EL_PORT(29,port) || TSS_DETECT_EL_PORT(30,port) || TSS_DETECT_EL_PORT(31,port) || TSS_DETECT_EL_PORT(32,port) || TSS_DETECT_EL_PORT(33,port) || TSS_DETECT_EL_PORT(34,port) || TSS_DETECT_EL_PORT(35,port) || TSS_DETECT_EL_PORT(36,port) || TSS_DETECT_EL_PORT(37,port) || TSS_DETECT_EL_PORT(38,port) || TSS_DETECT_EL_PORT(39,port) || TSS_DETECT_EL_PORT(40,port) || TSS_DETECT_EL_PORT(41,port) || TSS_DETECT_EL_PORT(42,port) || TSS_DETECT_EL_PORT(43,port) || TSS_DETECT_EL_PORT(44,port) || TSS_DETECT_EL_PORT(45,port) || TSS_DETECT_EL_PORT(46,port) || TSS_DETECT_EL_PORT(47,port) || TSS_DETECT_EL_PORT(48,port) || TSS_DETECT_EL_PORT(49,port) || TSS_DETECT_EL_PORT(50,port) || TSS_DETECT_EL_PORT(51,port) || TSS_DETECT_EL_PORT(52,port) || TSS_DETECT_EL_PORT(53,port) || TSS_DETECT_EL_PORT(54,port) || TSS_DETECT_EL_PORT(55,port) || TSS_DETECT_EL_PORT(56,port) || TSS_DETECT_EL_PORT(57,port) || TSS_DETECT_EL_PORT(58,port) || TSS_DETECT_EL_PORT(59,port) || TSS_DETECT_EL_PORT(60,port) || TSS_DETECT_EL_PORT(61,port) || TSS_DETECT_EL_PORT(62,port) || TSS_DETECT_EL_PORT(63,port))
  
  #define TSS_DETECT_PORT_METHOD(port,method)  ((TSS_DETECT_EL_PORT(0,port) && TSS_DETECT_EL_METHOD(0,method)) ||(TSS_DETECT_EL_PORT(1,port) && TSS_DETECT_EL_METHOD(1,method)) ||(TSS_DETECT_EL_PORT(2,port) && TSS_DETECT_EL_METHOD(2,method)) ||(TSS_DETECT_EL_PORT(3,port) && TSS_DETECT_EL_METHOD(3,method)) ||(TSS_DETECT_EL_PORT(4,port) && TSS_DETECT_EL_METHOD(4,method)) ||(TSS_DETECT_EL_PORT(5,port) && TSS_DETECT_EL_METHOD(5,method)) ||(TSS_DETECT_EL_PORT(6,port) && TSS_DETECT_EL_METHOD(6,method)) ||(TSS_DETECT_EL_PORT(7,port) && TSS_DETECT_EL_METHOD(7,method)) ||(TSS_DETECT_EL_PORT(8,port) && TSS_DETECT_EL_METHOD(8,method)) ||(TSS_DETECT_EL_PORT(9,port) && TSS_DETECT_EL_METHOD(9,method)) ||(TSS_DETECT_EL_PORT(10,port) && TSS_DETECT_EL_METHOD(10,method)) ||(TSS_DETECT_EL_PORT(11,port) && TSS_DETECT_EL_METHOD(11,method)) ||(TSS_DETECT_EL_PORT(12,port) && TSS_DETECT_EL_METHOD(12,method)) ||(TSS_DETECT_EL_PORT(13,port) && TSS_DETECT_EL_METHOD(13,method)) ||(TSS_DETECT_EL_PORT(14,port) && TSS_DETECT_EL_METHOD(14,method)) ||(TSS_DETECT_EL_PORT(15,port) && TSS_DETECT_EL_METHOD(15,method)) ||(TSS_DETECT_EL_PORT(16,port) && TSS_DETECT_EL_METHOD(16,method)) ||(TSS_DETECT_EL_PORT(17,port) && TSS_DETECT_EL_METHOD(17,method)) ||(TSS_DETECT_EL_PORT(18,port) && TSS_DETECT_EL_METHOD(18,method)) ||(TSS_DETECT_EL_PORT(19,port) && TSS_DETECT_EL_METHOD(19,method)) ||(TSS_DETECT_EL_PORT(20,port) && TSS_DETECT_EL_METHOD(20,method)) ||(TSS_DETECT_EL_PORT(21,port) && TSS_DETECT_EL_METHOD(21,method)) ||(TSS_DETECT_EL_PORT(22,port) && TSS_DETECT_EL_METHOD(22,method)) ||(TSS_DETECT_EL_PORT(23,port) && TSS_DETECT_EL_METHOD(23,method)) ||(TSS_DETECT_EL_PORT(24,port) && TSS_DETECT_EL_METHOD(24,method)) ||(TSS_DETECT_EL_PORT(25,port) && TSS_DETECT_EL_METHOD(25,method)) ||(TSS_DETECT_EL_PORT(26,port) && TSS_DETECT_EL_METHOD(26,method)) ||(TSS_DETECT_EL_PORT(27,port) && TSS_DETECT_EL_METHOD(27,method)) ||(TSS_DETECT_EL_PORT(28,port) && TSS_DETECT_EL_METHOD(28,method)) ||(TSS_DETECT_EL_PORT(29,port) && TSS_DETECT_EL_METHOD(29,method)) ||(TSS_DETECT_EL_PORT(30,port) && TSS_DETECT_EL_METHOD(30,method)) ||(TSS_DETECT_EL_PORT(31,port) && TSS_DETECT_EL_METHOD(31,method)) ||(TSS_DETECT_EL_PORT(32,port) && TSS_DETECT_EL_METHOD(32,method)) ||(TSS_DETECT_EL_PORT(33,port) && TSS_DETECT_EL_METHOD(33,method)) ||(TSS_DETECT_EL_PORT(34,port) && TSS_DETECT_EL_METHOD(34,method)) ||(TSS_DETECT_EL_PORT(35,port) && TSS_DETECT_EL_METHOD(35,method)) ||(TSS_DETECT_EL_PORT(36,port) && TSS_DETECT_EL_METHOD(36,method)) ||(TSS_DETECT_EL_PORT(37,port) && TSS_DETECT_EL_METHOD(37,method)) ||(TSS_DETECT_EL_PORT(38,port) && TSS_DETECT_EL_METHOD(38,method)) ||(TSS_DETECT_EL_PORT(39,port) && TSS_DETECT_EL_METHOD(39,method)) ||(TSS_DETECT_EL_PORT(40,port) && TSS_DETECT_EL_METHOD(40,method)) ||(TSS_DETECT_EL_PORT(41,port) && TSS_DETECT_EL_METHOD(41,method)) ||(TSS_DETECT_EL_PORT(42,port) && TSS_DETECT_EL_METHOD(42,method)) ||(TSS_DETECT_EL_PORT(43,port) && TSS_DETECT_EL_METHOD(43,method)) ||(TSS_DETECT_EL_PORT(44,port) && TSS_DETECT_EL_METHOD(44,method)) ||(TSS_DETECT_EL_PORT(45,port) && TSS_DETECT_EL_METHOD(45,method)) ||(TSS_DETECT_EL_PORT(46,port) && TSS_DETECT_EL_METHOD(46,method)) ||(TSS_DETECT_EL_PORT(47,port) && TSS_DETECT_EL_METHOD(47,method)) ||(TSS_DETECT_EL_PORT(48,port) && TSS_DETECT_EL_METHOD(48,method)) ||(TSS_DETECT_EL_PORT(49,port) && TSS_DETECT_EL_METHOD(49,method)) ||(TSS_DETECT_EL_PORT(50,port) && TSS_DETECT_EL_METHOD(50,method)) ||(TSS_DETECT_EL_PORT(51,port) && TSS_DETECT_EL_METHOD(51,method)) ||(TSS_DETECT_EL_PORT(52,port) && TSS_DETECT_EL_METHOD(52,method)) ||(TSS_DETECT_EL_PORT(53,port) && TSS_DETECT_EL_METHOD(53,method)) ||(TSS_DETECT_EL_PORT(54,port) && TSS_DETECT_EL_METHOD(54,method)) ||(TSS_DETECT_EL_PORT(55,port) && TSS_DETECT_EL_METHOD(55,method)) ||(TSS_DETECT_EL_PORT(56,port) && TSS_DETECT_EL_METHOD(56,method)) ||(TSS_DETECT_EL_PORT(57,port) && TSS_DETECT_EL_METHOD(57,method)) ||(TSS_DETECT_EL_PORT(58,port) && TSS_DETECT_EL_METHOD(58,method)) ||(TSS_DETECT_EL_PORT(59,port) && TSS_DETECT_EL_METHOD(59,method)) ||(TSS_DETECT_EL_PORT(60,port) && TSS_DETECT_EL_METHOD(60,method)) ||(TSS_DETECT_EL_PORT(61,port) && TSS_DETECT_EL_METHOD(61,method)) ||(TSS_DETECT_EL_PORT(62,port) && TSS_DETECT_EL_METHOD(62,method)) ||(TSS_DETECT_EL_PORT(63,port) && TSS_DETECT_EL_METHOD(63,method)))

  #define TSS_DETECT_PORT_MODULE(port,module)  ((TSS_DETECT_EL_PORT(0,port) && TSS_DETECT_EL_MODULE(0,module)) ||(TSS_DETECT_EL_PORT(1,port) && TSS_DETECT_EL_MODULE(1,module)) ||(TSS_DETECT_EL_PORT(2,port) && TSS_DETECT_EL_MODULE(2,module)) ||(TSS_DETECT_EL_PORT(3,port) && TSS_DETECT_EL_MODULE(3,module)) ||(TSS_DETECT_EL_PORT(4,port) && TSS_DETECT_EL_MODULE(4,module)) ||(TSS_DETECT_EL_PORT(5,port) && TSS_DETECT_EL_MODULE(5,module)) ||(TSS_DETECT_EL_PORT(6,port) && TSS_DETECT_EL_MODULE(6,module)) ||(TSS_DETECT_EL_PORT(7,port) && TSS_DETECT_EL_MODULE(7,module)) ||(TSS_DETECT_EL_PORT(8,port) && TSS_DETECT_EL_MODULE(8,module)) ||(TSS_DETECT_EL_PORT(9,port) && TSS_DETECT_EL_MODULE(9,module)) ||(TSS_DETECT_EL_PORT(10,port) && TSS_DETECT_EL_MODULE(10,module)) ||(TSS_DETECT_EL_PORT(11,port) && TSS_DETECT_EL_MODULE(11,module)) ||(TSS_DETECT_EL_PORT(12,port) && TSS_DETECT_EL_MODULE(12,module)) ||(TSS_DETECT_EL_PORT(13,port) && TSS_DETECT_EL_MODULE(13,module)) ||(TSS_DETECT_EL_PORT(14,port) && TSS_DETECT_EL_MODULE(14,module)) ||(TSS_DETECT_EL_PORT(15,port) && TSS_DETECT_EL_MODULE(15,module)) ||(TSS_DETECT_EL_PORT(16,port) && TSS_DETECT_EL_MODULE(16,module)) ||(TSS_DETECT_EL_PORT(17,port) && TSS_DETECT_EL_MODULE(17,module)) ||(TSS_DETECT_EL_PORT(18,port) && TSS_DETECT_EL_MODULE(18,module)) ||(TSS_DETECT_EL_PORT(19,port) && TSS_DETECT_EL_MODULE(19,module)) ||(TSS_DETECT_EL_PORT(20,port) && TSS_DETECT_EL_MODULE(20,module)) ||(TSS_DETECT_EL_PORT(21,port) && TSS_DETECT_EL_MODULE(21,module)) ||(TSS_DETECT_EL_PORT(22,port) && TSS_DETECT_EL_MODULE(22,module)) ||(TSS_DETECT_EL_PORT(23,port) && TSS_DETECT_EL_MODULE(23,module)) ||(TSS_DETECT_EL_PORT(24,port) && TSS_DETECT_EL_MODULE(24,module)) ||(TSS_DETECT_EL_PORT(25,port) && TSS_DETECT_EL_MODULE(25,module)) ||(TSS_DETECT_EL_PORT(26,port) && TSS_DETECT_EL_MODULE(26,module)) ||(TSS_DETECT_EL_PORT(27,port) && TSS_DETECT_EL_MODULE(27,module)) ||(TSS_DETECT_EL_PORT(28,port) && TSS_DETECT_EL_MODULE(28,module)) ||(TSS_DETECT_EL_PORT(29,port) && TSS_DETECT_EL_MODULE(29,module)) ||(TSS_DETECT_EL_PORT(30,port) && TSS_DETECT_EL_MODULE(30,module)) ||(TSS_DETECT_EL_PORT(31,port) && TSS_DETECT_EL_MODULE(31,module)) ||(TSS_DETECT_EL_PORT(32,port) && TSS_DETECT_EL_MODULE(32,module)) ||(TSS_DETECT_EL_PORT(33,port) && TSS_DETECT_EL_MODULE(33,module)) ||(TSS_DETECT_EL_PORT(34,port) && TSS_DETECT_EL_MODULE(34,module)) ||(TSS_DETECT_EL_PORT(35,port) && TSS_DETECT_EL_MODULE(35,module)) ||(TSS_DETECT_EL_PORT(36,port) && TSS_DETECT_EL_MODULE(36,module)) ||(TSS_DETECT_EL_PORT(37,port) && TSS_DETECT_EL_MODULE(37,module)) ||(TSS_DETECT_EL_PORT(38,port) && TSS_DETECT_EL_MODULE(38,module)) ||(TSS_DETECT_EL_PORT(39,port) && TSS_DETECT_EL_MODULE(39,module)) ||(TSS_DETECT_EL_PORT(40,port) && TSS_DETECT_EL_MODULE(40,module)) ||(TSS_DETECT_EL_PORT(41,port) && TSS_DETECT_EL_MODULE(41,module)) ||(TSS_DETECT_EL_PORT(42,port) && TSS_DETECT_EL_MODULE(42,module)) ||(TSS_DETECT_EL_PORT(43,port) && TSS_DETECT_EL_MODULE(43,module)) ||(TSS_DETECT_EL_PORT(44,port) && TSS_DETECT_EL_MODULE(44,module)) ||(TSS_DETECT_EL_PORT(45,port) && TSS_DETECT_EL_MODULE(45,module)) ||(TSS_DETECT_EL_PORT(46,port) && TSS_DETECT_EL_MODULE(46,module)) ||(TSS_DETECT_EL_PORT(47,port) && TSS_DETECT_EL_MODULE(47,module)) ||(TSS_DETECT_EL_PORT(48,port) && TSS_DETECT_EL_MODULE(48,module)) ||(TSS_DETECT_EL_PORT(49,port) && TSS_DETECT_EL_MODULE(49,module)) ||(TSS_DETECT_EL_PORT(50,port) && TSS_DETECT_EL_MODULE(50,module)) ||(TSS_DETECT_EL_PORT(51,port) && TSS_DETECT_EL_MODULE(51,module)) ||(TSS_DETECT_EL_PORT(52,port) && TSS_DETECT_EL_MODULE(52,module)) ||(TSS_DETECT_EL_PORT(53,port) && TSS_DETECT_EL_MODULE(53,module)) ||(TSS_DETECT_EL_PORT(54,port) && TSS_DETECT_EL_MODULE(54,module)) ||(TSS_DETECT_EL_PORT(55,port) && TSS_DETECT_EL_MODULE(55,module)) ||(TSS_DETECT_EL_PORT(56,port) && TSS_DETECT_EL_MODULE(56,module)) ||(TSS_DETECT_EL_PORT(57,port) && TSS_DETECT_EL_MODULE(57,module)) ||(TSS_DETECT_EL_PORT(58,port) && TSS_DETECT_EL_MODULE(58,module)) ||(TSS_DETECT_EL_PORT(59,port) && TSS_DETECT_EL_MODULE(59,module)) ||(TSS_DETECT_EL_PORT(60,port) && TSS_DETECT_EL_MODULE(60,module)) ||(TSS_DETECT_EL_PORT(61,port) && TSS_DETECT_EL_MODULE(61,module)) ||(TSS_DETECT_EL_PORT(62,port) && TSS_DETECT_EL_MODULE(62,module)) ||(TSS_DETECT_EL_PORT(63,port) && TSS_DETECT_EL_MODULE(63,module)))
  
  #define TSS_PORT_METHOD_USED          (TSS_DETECT_PORT(A) || TSS_DETECT_PORT(B) || TSS_DETECT_PORT(C) || TSS_DETECT_PORT(D) || TSS_DETECT_PORT(E) || TSS_DETECT_PORT(F) || TSS_DETECT_PORT(G) || TSS_DETECT_PORT(H) || TSS_DETECT_PORT(I) || TSS_DETECT_PORT(J))     

  /*******************************************************
   *************** Srength Availability Macros ***********
   *******************************************************/

  #ifdef PTASE_PTASE0
    #define PTASE0_EXISTS       1
  #else
    #define PTASE0_EXISTS       0
  #endif
  #ifdef PTASE_PTASE1
    #define PTASE1_EXISTS       1
  #else
    #define PTASE1_EXISTS       0
  #endif
  #ifdef PTASE_PTASE2
    #define PTASE2_EXISTS       1
  #else
    #define PTASE2_EXISTS       0
  #endif
  #ifdef PTASE_PTASE3
    #define PTASE3_EXISTS       1
  #else
    #define PTASE3_EXISTS       0
  #endif
  #ifdef PTASE_PTASE4
    #define PTASE4_EXISTS       1
  #else
    #define PTASE4_EXISTS       0
  #endif
  #ifdef PTASE_PTASE5
    #define PTASE5_EXISTS       1
  #else
    #define PTASE5_EXISTS       0
  #endif
  #ifdef PTASE_PTASE6
    #define PTASE6_EXISTS       1
  #else
    #define PTASE6_EXISTS       0
  #endif
  #ifdef PTASE_PTASE7
    #define PTASE7_EXISTS       1
  #else
    #define PTASE7_EXISTS       0
  #endif
  
  #ifdef PTBSE_PTBSE0
    #define PTBSE0_EXISTS       1
  #else
    #define PTBSE0_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE1
    #define PTBSE1_EXISTS       1
  #else
    #define PTBSE1_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE2
    #define PTBSE2_EXISTS       1
  #else
    #define PTBSE2_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE3
    #define PTBSE3_EXISTS       1
  #else
    #define PTBSE3_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE4
    #define PTBSE4_EXISTS       1
  #else
    #define PTBSE4_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE5
    #define PTBSE5_EXISTS       1
  #else
    #define PTBSE5_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE6
    #define PTBSE6_EXISTS       1
  #else
    #define PTBSE6_EXISTS       0
  #endif
  #ifdef PTBSE_PTBSE7
    #define PTBSE7_EXISTS       1
  #else
    #define PTBSE7_EXISTS       0
  #endif
  
  #ifdef PTCSE_PTCSE0
    #define PTCSE0_EXISTS       1
  #else
    #define PTCSE0_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE1
    #define PTCSE1_EXISTS       1
  #else
    #define PTCSE1_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE2
    #define PTCSE2_EXISTS       1
  #else
    #define PTCSE2_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE3
    #define PTCSE3_EXISTS       1
  #else
    #define PTCSE3_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE4
    #define PTCSE4_EXISTS       1
  #else
    #define PTCSE4_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE5
    #define PTCSE5_EXISTS       1
  #else
    #define PTCSE5_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE6
    #define PTCSE6_EXISTS       1
  #else
    #define PTCSE6_EXISTS       0
  #endif
  #ifdef PTCSE_PTCSE7
    #define PTCSE7_EXISTS       1
  #else
    #define PTCSE7_EXISTS       0
  #endif
  
  #ifdef PTDSE_PTDSE0
    #define PTDSE0_EXISTS       1
  #else
    #define PTDSE0_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE1
    #define PTDSE1_EXISTS       1
  #else
    #define PTDSE1_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE2
    #define PTDSE2_EXISTS       1
  #else
    #define PTDSE2_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE3
    #define PTDSE3_EXISTS       1
  #else
    #define PTDSE3_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE4
    #define PTDSE4_EXISTS       1
  #else
    #define PTDSE4_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE5
    #define PTDSE5_EXISTS       1
  #else
    #define PTDSE5_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE6
    #define PTDSE6_EXISTS       1
  #else
    #define PTDSE6_EXISTS       0
  #endif
  #ifdef PTDSE_PTDSE7
    #define PTDSE7_EXISTS       1
  #else
    #define PTDSE7_EXISTS       0
  #endif
  
  #ifdef PTESE_PTESE0
    #define PTESE0_EXISTS       1
  #else
    #define PTESE0_EXISTS       0
  #endif
  #ifdef PTESE_PTESE1
    #define PTESE1_EXISTS       1
  #else
    #define PTESE1_EXISTS       0
  #endif
  #ifdef PTESE_PTESE2
    #define PTESE2_EXISTS       1
  #else
    #define PTESE2_EXISTS       0
  #endif
  #ifdef PTESE_PTESE3
    #define PTESE3_EXISTS       1
  #else
    #define PTESE3_EXISTS       0
  #endif
  #ifdef PTESE_PTESE4
    #define PTESE4_EXISTS       1
  #else
    #define PTESE4_EXISTS       0
  #endif
  #ifdef PTESE_PTESE5
    #define PTESE5_EXISTS       1
  #else
    #define PTESE5_EXISTS       0
  #endif
  #ifdef PTESE_PTESE6
    #define PTESE6_EXISTS       1
  #else
    #define PTESE6_EXISTS       0
  #endif
  #ifdef PTESE_PTESE7
    #define PTESE7_EXISTS       1
  #else
    #define PTESE7_EXISTS       0
  #endif
  
  #ifdef PTFSE_PTFSE0
    #define PTFSE0_EXISTS       1
  #else
    #define PTFSE0_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE1
    #define PTFSE1_EXISTS       1
  #else
    #define PTFSE1_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE2
    #define PTFSE2_EXISTS       1
  #else
    #define PTFSE2_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE3
    #define PTFSE3_EXISTS       1
  #else
    #define PTFSE3_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE4
    #define PTFSE4_EXISTS       1
  #else
    #define PTFSE4_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE5
    #define PTFSE5_EXISTS       1
  #else
    #define PTFSE5_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE6
    #define PTFSE6_EXISTS       1
  #else
    #define PTFSE6_EXISTS       0
  #endif
  #ifdef PTFSE_PTFSE7
    #define PTFSE7_EXISTS       1
  #else
    #define PTFSE7_EXISTS       0
  #endif
  
  #ifdef PTGSE_PTGSE0
    #define PTGSE0_EXISTS       1
  #else
    #define PTGSE0_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE1
    #define PTGSE1_EXISTS       1
  #else
    #define PTGSE1_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE2
    #define PTGSE2_EXISTS       1
  #else
    #define PTGSE2_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE3
    #define PTGSE3_EXISTS       1
  #else
    #define PTGSE3_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE4
    #define PTGSE4_EXISTS       1
  #else
    #define PTGSE4_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE5
    #define PTGSE5_EXISTS       1
  #else
    #define PTGSE5_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE6
    #define PTGSE6_EXISTS       1
  #else
    #define PTGSE6_EXISTS       0
  #endif
  #ifdef PTGSE_PTGSE7
    #define PTGSE7_EXISTS       1
  #else
    #define PTGSE7_EXISTS       0
  #endif
  
  #ifdef PTHSE_PTHSE0
    #define PTHSE0_EXISTS       1
  #else
    #define PTHSE0_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE1
    #define PTHSE1_EXISTS       1
  #else
    #define PTHSE1_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE2
    #define PTHSE2_EXISTS       1
  #else
    #define PTHSE2_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE3
    #define PTHSE3_EXISTS       1
  #else
    #define PTHSE3_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE4
    #define PTHSE4_EXISTS       1
  #else
    #define PTHSE4_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE5
    #define PTHSE5_EXISTS       1
  #else
    #define PTHSE5_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE6
    #define PTHSE6_EXISTS       1
  #else
    #define PTHSE6_EXISTS       0
  #endif
  #ifdef PTHSE_PTHSE7
    #define PTHSE7_EXISTS       1
  #else
    #define PTHSE7_EXISTS       0
  #endif
  
  #ifdef PTISE_PTISE0
    #define PTISE0_EXISTS       1
  #else
    #define PTISE0_EXISTS       0
  #endif
  #ifdef PTISE_PTISE1
    #define PTISE1_EXISTS       1
  #else
    #define PTISE1_EXISTS       0
  #endif
  #ifdef PTISE_PTISE2
    #define PTISE2_EXISTS       1
  #else
    #define PTISE2_EXISTS       0
  #endif
  #ifdef PTISE_PTISE3
    #define PTISE3_EXISTS       1
  #else
    #define PTISE3_EXISTS       0
  #endif
  #ifdef PTISE_PTISE4
    #define PTISE4_EXISTS       1
  #else
    #define PTISE4_EXISTS       0
  #endif
  #ifdef PTISE_PTISE5
    #define PTISE5_EXISTS       1
  #else
    #define PTISE5_EXISTS       0
  #endif
  #ifdef PTISE_PTISE6
    #define PTISE6_EXISTS       1
  #else
    #define PTISE6_EXISTS       0
  #endif
  #ifdef PTISE_PTISE7
    #define PTISE7_EXISTS       1
  #else
    #define PTISE7_EXISTS       0
  #endif
  
  #ifdef PTJSE_PTJSE0
    #define PTJSE0_EXISTS       1
  #else
    #define PTJSE0_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE1
    #define PTJSE1_EXISTS       1
  #else
    #define PTJSE1_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE2
    #define PTJSE2_EXISTS       1
  #else
    #define PTJSE2_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE3
    #define PTJSE3_EXISTS       1
  #else
    #define PTJSE3_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE4
    #define PTJSE4_EXISTS       1
  #else
    #define PTJSE4_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE5
    #define PTJSE5_EXISTS       1
  #else
    #define PTJSE5_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE6
    #define PTJSE6_EXISTS       1
  #else
    #define PTJSE6_EXISTS       0
  #endif
  #ifdef PTJSE_PTJSE7
    #define PTJSE7_EXISTS       1
  #else
    #define PTJSE7_EXISTS       0
  #endif
  
  #ifdef PTKSE_PTKSE0
    #define PTKSE0_EXISTS       1
  #else
    #define PTKSE0_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE1
    #define PTKSE1_EXISTS       1
  #else
    #define PTKSE1_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE2
    #define PTKSE2_EXISTS       1
  #else
    #define PTKSE2_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE3
    #define PTKSE3_EXISTS       1
  #else
    #define PTKSE3_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE4
    #define PTKSE4_EXISTS       1
  #else
    #define PTKSE4_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE5
    #define PTKSE5_EXISTS       1
  #else
    #define PTKSE5_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE6
    #define PTKSE6_EXISTS       1
  #else
    #define PTKSE6_EXISTS       0
  #endif
  #ifdef PTKSE_PTKSE7
    #define PTKSE7_EXISTS       1
  #else
    #define PTKSE7_EXISTS       0
  #endif
  
  #ifdef PTLSE_PTLSE0
    #define PTLSE0_EXISTS       1
  #else
    #define PTLSE0_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE1
    #define PTLSE1_EXISTS       1
  #else
    #define PTLSE1_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE2
    #define PTLSE2_EXISTS       1
  #else
    #define PTLSE2_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE3
    #define PTLSE3_EXISTS       1
  #else
    #define PTLSE3_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE4
    #define PTLSE4_EXISTS       1
  #else
    #define PTLSE4_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE5
    #define PTLSE5_EXISTS       1
  #else
    #define PTLSE5_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE6
    #define PTLSE6_EXISTS       1
  #else
    #define PTLSE6_EXISTS       0
  #endif
  #ifdef PTLSE_PTLSE7
    #define PTLSE7_EXISTS       1
  #else
    #define PTLSE7_EXISTS       0
  #endif

  /*************** Srength Settings Macros ***************/

  #define TSS_GPIO_PIN_STR(port, pin)           PT##port##DS_PT##port##DS##pin      /* Defines the port-pin strength register name */
  #define TSS_GPIO_PIN_STR_CHK(port, pin)       PT##port##DS##pin##_EXISTS          /* Defines the port-pin strength register name */  

  #define TSS_GPIO_STRENGTH_SET(port, pin)      (TSS_GPIO_PIN_STR(port, pin) = 1U)  /* Writes "1" to the strength-pin register */
  #define TSS_GPIO_STRENGTH_CLEAR(port, pin)    (TSS_GPIO_PIN_STR(port, pin) = 0U)  /* Writes "0" to the strength-pin register */
  #define TSS_GPIO_STRENGTH_CHECK(port, pin)    TSS_GPIO_PIN_STR_CHK(port, pin)          
  #define EL2GPIO_CONV_STR_SET(port, pin)	TSS_GPIO_STRENGTH_SET(port, pin)
  #define EL2GPIO_CONV_STR_CLEAR(port, pin)	TSS_GPIO_STRENGTH_CLEAR(port, pin)
  #define EL2GPIO_CONV_STR_CHECK(port, pin)	TSS_GPIO_STRENGTH_CHECK(port, pin)
  #define TSS_ELECTRODE_STRENGTH_SET(elec)      EL2GPIO_CONV_STR_SET(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_STRENGTH_CLEAR(elec)    EL2GPIO_CONV_STR_CLEAR(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_STRENGTH_CHECK(elec)    EL2GPIO_CONV_STR_CHECK(TSS_E##elec##_P,TSS_E##elec##_B)
  
  /*******************************************************
   *************** Slew Rate Availaility Macros **********
   *******************************************************/

  #ifdef PTADS_PTADS0
    #define PTADS0_EXISTS       1
  #else
    #define PTADS0_EXISTS       0
  #endif
  #ifdef PTADS_PTADS1
    #define PTADS1_EXISTS       1
  #else
    #define PTADS1_EXISTS       0
  #endif
  #ifdef PTADS_PTADS2
    #define PTADS2_EXISTS       1
  #else
    #define PTADS2_EXISTS       0
  #endif
  #ifdef PTADS_PTADS3
    #define PTADS3_EXISTS       1
  #else
    #define PTADS3_EXISTS       0
  #endif
  #ifdef PTADS_PTADS4
    #define PTADS4_EXISTS       1
  #else
    #define PTADS4_EXISTS       0
  #endif
  #ifdef PTADS_PTADS5
    #define PTADS5_EXISTS       1
  #else
    #define PTADS5_EXISTS       0
  #endif
  #ifdef PTADS_PTADS6
    #define PTADS6_EXISTS       1
  #else
    #define PTADS6_EXISTS       0
  #endif
  #ifdef PTADS_PTADS7
    #define PTADS7_EXISTS       1
  #else
    #define PTADS7_EXISTS       0
  #endif
  
  #ifdef PTBDS_PTBDS0
    #define PTBDS0_EXISTS       1
  #else
    #define PTBDS0_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS1
    #define PTBDS1_EXISTS       1
  #else
    #define PTBDS1_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS2
    #define PTBDS2_EXISTS       1
  #else
    #define PTBDS2_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS3
    #define PTBDS3_EXISTS       1
  #else
    #define PTBDS3_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS4
    #define PTBDS4_EXISTS       1
  #else
    #define PTBDS4_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS5
    #define PTBDS5_EXISTS       1
  #else
    #define PTBDS5_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS6
    #define PTBDS6_EXISTS       1
  #else
    #define PTBDS6_EXISTS       0
  #endif
  #ifdef PTBDS_PTBDS7
    #define PTBDS7_EXISTS       1
  #else
    #define PTBDS7_EXISTS       0
  #endif
  
  #ifdef PTCDS_PTCDS0
    #define PTCDS0_EXISTS       1
  #else
    #define PTCDS0_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS1
    #define PTCDS1_EXISTS       1
  #else
    #define PTCDS1_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS2
    #define PTCDS2_EXISTS       1
  #else
    #define PTCDS2_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS3
    #define PTCDS3_EXISTS       1
  #else
    #define PTCDS3_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS4
    #define PTCDS4_EXISTS       1
  #else
    #define PTCDS4_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS5
    #define PTCDS5_EXISTS       1
  #else
    #define PTCDS5_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS6
    #define PTCDS6_EXISTS       1
  #else
    #define PTCDS6_EXISTS       0
  #endif
  #ifdef PTCDS_PTCDS7
    #define PTCDS7_EXISTS       1
  #else
    #define PTCDS7_EXISTS       0
  #endif
  
  #ifdef PTDDS_PTDDS0
    #define PTDDS0_EXISTS       1
  #else
    #define PTDDS0_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS1
    #define PTDDS1_EXISTS       1
  #else
    #define PTDDS1_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS2
    #define PTDDS2_EXISTS       1
  #else
    #define PTDDS2_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS3
    #define PTDDS3_EXISTS       1
  #else
    #define PTDDS3_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS4
    #define PTDDS4_EXISTS       1
  #else
    #define PTDDS4_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS5
    #define PTDDS5_EXISTS       1
  #else
    #define PTDDS5_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS6
    #define PTDDS6_EXISTS       1
  #else
    #define PTDDS6_EXISTS       0
  #endif
  #ifdef PTDDS_PTDDS7
    #define PTDDS7_EXISTS       1
  #else
    #define PTDDS7_EXISTS       0
  #endif
  
  #ifdef PTEDS_PTEDS0
    #define PTEDS0_EXISTS       1
  #else
    #define PTEDS0_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS1
    #define PTEDS1_EXISTS       1
  #else
    #define PTEDS1_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS2
    #define PTEDS2_EXISTS       1
  #else
    #define PTEDS2_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS3
    #define PTEDS3_EXISTS       1
  #else
    #define PTEDS3_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS4
    #define PTEDS4_EXISTS       1
  #else
    #define PTEDS4_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS5
    #define PTEDS5_EXISTS       1
  #else
    #define PTEDS5_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS6
    #define PTEDS6_EXISTS       1
  #else
    #define PTEDS6_EXISTS       0
  #endif
  #ifdef PTEDS_PTEDS7
    #define PTEDS7_EXISTS       1
  #else
    #define PTEDS7_EXISTS       0
  #endif
  
  #ifdef PTFDS_PTFDS0
    #define PTFDS0_EXISTS       1
  #else
    #define PTFDS0_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS1
    #define PTFDS1_EXISTS       1
  #else
    #define PTFDS1_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS2
    #define PTFDS2_EXISTS       1
  #else
    #define PTFDS2_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS3
    #define PTFDS3_EXISTS       1
  #else
    #define PTFDS3_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS4
    #define PTFDS4_EXISTS       1
  #else
    #define PTFDS4_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS5
    #define PTFDS5_EXISTS       1
  #else
    #define PTFDS5_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS6
    #define PTFDS6_EXISTS       1
  #else
    #define PTFDS6_EXISTS       0
  #endif
  #ifdef PTFDS_PTFDS7
    #define PTFDS7_EXISTS       1
  #else
    #define PTFDS7_EXISTS       0
  #endif
  
  #ifdef PTGDS_PTGDS0
    #define PTGDS0_EXISTS       1
  #else
    #define PTGDS0_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS1
    #define PTGDS1_EXISTS       1
  #else
    #define PTGDS1_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS2
    #define PTGDS2_EXISTS       1
  #else
    #define PTGDS2_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS3
    #define PTGDS3_EXISTS       1
  #else
    #define PTGDS3_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS4
    #define PTGDS4_EXISTS       1
  #else
    #define PTGDS4_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS5
    #define PTGDS5_EXISTS       1
  #else
    #define PTGDS5_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS6
    #define PTGDS6_EXISTS       1
  #else
    #define PTGDS6_EXISTS       0
  #endif
  #ifdef PTGDS_PTGDS7
    #define PTGDS7_EXISTS       1
  #else
    #define PTGDS7_EXISTS       0
  #endif
  
  #ifdef PTHDS_PTHDS0
    #define PTHDS0_EXISTS       1
  #else
    #define PTHDS0_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS1
    #define PTHDS1_EXISTS       1
  #else
    #define PTHDS1_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS2
    #define PTHDS2_EXISTS       1
  #else
    #define PTHDS2_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS3
    #define PTHDS3_EXISTS       1
  #else
    #define PTHDS3_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS4
    #define PTHDS4_EXISTS       1
  #else
    #define PTHDS4_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS5
    #define PTHDS5_EXISTS       1
  #else
    #define PTHDS5_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS6
    #define PTHDS6_EXISTS       1
  #else
    #define PTHDS6_EXISTS       0
  #endif
  #ifdef PTHDS_PTHDS7
    #define PTHDS7_EXISTS       1
  #else
    #define PTHDS7_EXISTS       0
  #endif
  
  #ifdef PTIDS_PTIDS0
    #define PTIDS0_EXISTS       1
  #else
    #define PTIDS0_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS1
    #define PTIDS1_EXISTS       1
  #else
    #define PTIDS1_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS2
    #define PTIDS2_EXISTS       1
  #else
    #define PTIDS2_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS3
    #define PTIDS3_EXISTS       1
  #else
    #define PTIDS3_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS4
    #define PTIDS4_EXISTS       1
  #else
    #define PTIDS4_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS5
    #define PTIDS5_EXISTS       1
  #else
    #define PTIDS5_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS6
    #define PTIDS6_EXISTS       1
  #else
    #define PTIDS6_EXISTS       0
  #endif
  #ifdef PTIDS_PTIDS7
    #define PTIDS7_EXISTS       1
  #else
    #define PTIDS7_EXISTS       0
  #endif
  
  #ifdef PTJDS_PTJDS0
    #define PTJDS0_EXISTS       1
  #else
    #define PTJDS0_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS1
    #define PTJDS1_EXISTS       1
  #else
    #define PTJDS1_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS2
    #define PTJDS2_EXISTS       1
  #else
    #define PTJDS2_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS3
    #define PTJDS3_EXISTS       1
  #else
    #define PTJDS3_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS4
    #define PTJDS4_EXISTS       1
  #else
    #define PTJDS4_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS5
    #define PTJDS5_EXISTS       1
  #else
    #define PTJDS5_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS6
    #define PTJDS6_EXISTS       1
  #else
    #define PTJDS6_EXISTS       0
  #endif
  #ifdef PTJDS_PTJDS7
    #define PTJDS7_EXISTS       1
  #else
    #define PTJDS7_EXISTS       0
  #endif
  
  #ifdef PTKDS_PTKDS0
    #define PTKDS0_EXISTS       1
  #else
    #define PTKDS0_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS1
    #define PTKDS1_EXISTS       1
  #else
    #define PTKDS1_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS2
    #define PTKDS2_EXISTS       1
  #else
    #define PTKDS2_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS3
    #define PTKDS3_EXISTS       1
  #else
    #define PTKDS3_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS4
    #define PTKDS4_EXISTS       1
  #else
    #define PTKDS4_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS5
    #define PTKDS5_EXISTS       1
  #else
    #define PTKDS5_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS6
    #define PTKDS6_EXISTS       1
  #else
    #define PTKDS6_EXISTS       0
  #endif
  #ifdef PTKDS_PTKDS7
    #define PTKDS7_EXISTS       1
  #else
    #define PTKDS7_EXISTS       0
  #endif
  
  #ifdef PTLDS_PTLDS0
    #define PTLDS0_EXISTS       1
  #else
    #define PTLDS0_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS1
    #define PTLDS1_EXISTS       1
  #else
    #define PTLDS1_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS2
    #define PTLDS2_EXISTS       1
  #else
    #define PTLDS2_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS3
    #define PTLDS3_EXISTS       1
  #else
    #define PTLDS3_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS4
    #define PTLDS4_EXISTS       1
  #else
    #define PTLDS4_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS5
    #define PTLDS5_EXISTS       1
  #else
    #define PTLDS5_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS6
    #define PTLDS6_EXISTS       1
  #else
    #define PTLDS6_EXISTS       0
  #endif
  #ifdef PTLDS_PTLDS7
    #define PTLDS7_EXISTS       1
  #else
    #define PTLDS7_EXISTS       0
  #endif

  /*************** Slew Rate Settings Macros ***********/

  #define TSS_GPIO_PIN_SLW(port, pin)           PT##port##SE_PT##port##SE##pin      /* Defines the port-pin slewrate register name */
  #define TSS_GPIO_PIN_SLW_CHK(port, pin)       PT##port##SE##pin##_EXISTS          /* Defines the port-pin slewrate register name */  

  #define TSS_GPIO_SLEWRATE_SET(port, pin)      (TSS_GPIO_PIN_SLW(port, pin) = 1U)  /* Writes "1" to the slewrate-pin register */
  #define TSS_GPIO_SLEWRATE_CLEAR(port, pin)    (TSS_GPIO_PIN_SLW(port, pin) = 0U)  /* Writes "0" to the slewrate-pin register */
  #define TSS_GPIO_SLEWRATE_CHECK(port, pin)    TSS_GPIO_PIN_SLW_CHK(port, pin)          
  #define EL2GPIO_CONV_SLW_SET(port, pin)	TSS_GPIO_SLEWRATE_SET(port, pin)
  #define EL2GPIO_CONV_SLW_CLEAR(port, pin)	TSS_GPIO_SLEWRATE_CLEAR(port, pin)
  #define EL2GPIO_CONV_SLW_CHECK(port, pin)	TSS_GPIO_SLEWRATE_CHECK(port, pin)
  #define TSS_ELECTRODE_SLEWRATE_SET(elec)      EL2GPIO_CONV_SLW_SET(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_SLEWRATE_CLEAR(elec)    EL2GPIO_CONV_SLW_CLEAR(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_SLEWRATE_CHECK(elec)    EL2GPIO_CONV_SLW_CHECK(TSS_E##elec##_P,TSS_E##elec##_B)

  /*******************************************************
   ************ GPIOs Constants Definitions **************
   *******************************************************/

  #define TSS_GPIO_DIR_IN    0U
  #define TSS_GPIO_DIR_OUT   1U

  /*******************************************************
   ******************* GPIOs Tasks Macros ****************
   *******************************************************/

  #if TSS_KINETIS_MCU /* Kinetis */
    /***** RGPIO Macros *****/
    #ifdef RGPIO_PDORA 
      /* Classic reg */
      #define TSS_RGPIO_DOR(port)            RGPIO_PDOR##port          /* Set to GPIO OUTPUT */ /* Old DATA reg */
      #define TSS_RGPIO_OER(port)            RGPIO_POER##port          /* Set pin to OUTPUT 1, Input 0 */ /* Old DD reg */
      /* SET registers, Toggle */
      #define TSS_RGPIO_SOR(port)            RGPIO_PSOR##port          /* Set to LOG 1 by 1*/  
      #define TSS_RGPIO_COR(port)            RGPIO_PCOR##port          /* Set to LOG 0 by 1*/
      #define TSS_RGPIO_TOR(port)            RGPIO_PTOR##port          /* Inverse by 1*/
      #define TSS_RGPIO_DIR(port)            RGPIO_PDIR##port          /* Port DATA input, 1 = LOG 1 */
    #else
      /* Classic reg */
      #define TSS_RGPIO_DOR(port)            GPIO##port##_PDOR          /* Set to GPIO OUTPUT */ /* Old DATA reg */
      #define TSS_RGPIO_OER(port)            GPIO##port##_PDDR          /* Set pin to OUTPUT 1, Input 0 */ /* Old DD reg */
      /* SET registers, Toggle */
      #define TSS_RGPIO_SOR(port)            GPIO##port##_PSOR          /* Set to LOG 1 by 1*/  
      #define TSS_RGPIO_COR(port)            GPIO##port##_PCOR          /* Set to LOG 0 by 1*/
      #define TSS_RGPIO_TOR(port)            GPIO##port##_PTOR          /* Inverse by 1*/
      #define TSS_RGPIO_DIR(port)            GPIO##port##_PDIR          /* Port DATA input, 1 = LOG 1 */
    #endif

    #define TSS_GPIO_IN(port, pin)         TSS_RGPIO_OER(port) &= ~(1u << pin); /* Sets port-pin as input */
    #define TSS_GPIO_OUT(port, pin)        TSS_RGPIO_OER(port) |= (1u << pin); /* Sets port-pin as output */
    #define TSS_GPIO_READ(port, pin)       (TSS_RGPIO_DIR(port) & (1u << pin)) /* Reads port-pin */
    #define TSS_GPIO_SET(port, pin)        TSS_RGPIO_SOR(port) = (1u << pin); /* Writes "1" to the port-pin */
    #define TSS_GPIO_CLEAR(port, pin)      TSS_RGPIO_COR(port) = (1u << pin); /* Writes "0" to the port-pin */
  #elif TSS_CFM_MCU /* TSS_CFM_MCU */
    #define TSS_GPIO_D(port)               PT##port##_D   /* Defines the port register name */
    #define TSS_GPIO_DD(port)              PT##port##_DD  /* Defines the port direction register name */
    #define TSS_GPIO_PV(port)              PT##port##_PV  /* Defines the port value register name */
  
    #define TSS_GPIO_IN(port, pin)         (TSS_GPIO_DD(port) &= ~(1u << pin))  /* Sets port-pin as input */
    #define TSS_GPIO_OUT(port, pin)        (TSS_GPIO_DD(port) |= (1u << pin)) /* Sets port-pin as output */
    #define TSS_GPIO_READ(port, pin)       (TSS_GPIO_PV(port) & (1u << pin) ) /* Reads port-pin */
    #define TSS_GPIO_SET(port, pin)        (TSS_GPIO_D(port) |= (1u << pin)) /* Writes "1" to the port-pin */
    #define TSS_GPIO_CLEAR(port, pin)      (TSS_GPIO_D(port) &= ~(1u << pin)) /* Writes "0" to the port-pin */
    #define TSS_GPIO_PORT_ADR(port)        (&TSS_GPIO_D(port)) /* Gets the electrode port address */
  #else
    #if (TSS_GPIO_VERSION == 1)
      #define TSS_GPIO_PORT(port)            PT##port##D                     /* Defines the port register name */
      #define TSS_GPIO_PIN_DD(port, pin)     PT##port##DD_PT##port##DD##pin  /* Defines the port-pin register name */
      #define TSS_GPIO_PIN(port, pin)        PT##port##D_PT##port##D##pin    /* Defines the port-pin direction register name */

      #define TSS_GPIO_IN(port, pin)         (TSS_GPIO_PIN_DD(port, pin) = TSS_GPIO_DIR_IN)  /* Sets port-pin as input */
      #define TSS_GPIO_OUT(port, pin)        (TSS_GPIO_PIN_DD(port, pin) = TSS_GPIO_DIR_OUT) /* Sets port-pin as output */
      #define TSS_GPIO_READ(port, pin)       (TSS_GPIO_PORT(port) & (1u << pin) ) /* Reads port-pin */
      #define TSS_GPIO_SET(port, pin)        (TSS_GPIO_PIN(port, pin) = 1U)       /* Writes "1" to the port-pin */
      #define TSS_GPIO_CLEAR(port, pin)      (TSS_GPIO_PIN(port, pin) = 0U)       /* Writes "0" to the port-pin */
      #define TSS_GPIO_PORT_ADR(port)        (&TSS_GPIO_PORT(port))               /* Gets the electrode port address */
    #elif (TSS_GPIO_VERSION == 2)
      #define TSS_GPIO_PORT(port)             PORT_PT##port##D                     /* Defines the port register name */
      #define TSS_GPIO_CONTROL_PORT(port)     PORT_PT##port##OE                    /* Defines the port register name */
      #define TSS_GPIO_PIN_IE(port, pin)      PORT_PT##port##IE_PT##port##IE##pin  /* Defines the port input enable register name */
      #define TSS_GPIO_PIN_OE(port, pin)      PORT_PT##port##OE_PT##port##OE##pin  /* Defines the port output enable register name */
      #define TSS_GPIO_PIN(port, pin)         PORT_PT##port##D_PT##port##D##pin    /* Defines the port-pin direction register name */

      #define TSS_GPIO_IN(port, pin)          TSS_GPIO_PIN_OE(port, pin) = 0u; TSS_GPIO_PIN_IE(port, pin) = 1u; /* Sets port-pin as input */
      #define TSS_GPIO_OUT(port, pin)         TSS_GPIO_PIN_IE(port, pin) = 0u; TSS_GPIO_PIN_OE(port, pin) = 1u; /* Sets port-pin as output */
      #define TSS_GPIO_READ(port, pin)        (TSS_GPIO_PORT(port) & (1u << pin)) /* Reads port-pin */
      #define TSS_GPIO_SET(port, pin)         TSS_GPIO_PIN(port, pin) = 1U;       /* Writes "1" to the port-pin */
      #define TSS_GPIO_CLEAR(port, pin)       TSS_GPIO_PIN(port, pin) = 0U;       /* Writes "0" to the port-pin */
      #define TSS_GPIO_PORT_ADR(port)         (&TSS_GPIO_PORT(port))              /* Gets the electrode port address */
      #define TSS_GPIO_CONTROL_PORT_ADR(port) (&TSS_GPIO_CONTROL_PORT(port))              /* Gets the electrode port address */
    #endif

  #endif

  /*******************************************************
   ************ Electrode Macros Definitions *************
   *******************************************************/
  #define TSS_ELECTRODE_DISCHARGE(X)      TSS_GPIO_CLEAR(TSS_E##X##_P,TSS_E##X##_B);TSS_GPIO_OUT(TSS_E##X##_P,TSS_E##X##_B)
  #define TSS_ELECTRODE_CHARGE(X)         TSS_GPIO_IN(TSS_E##X##_P,TSS_E##X##_B)                                
  #define TSS_ELECTRODE_DISCHARGED(X)     ((TSS_GPIO_READ(TSS_E##X##_P,TSS_E##X##_B)) == 0)
  #define TSS_ELECTRODE_INPUT(elec)       TSS_GPIO_IN(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_HIGH(elec)        TSS_GPIO_SET(TSS_E##elec##_P,TSS_E##elec##_B); TSS_GPIO_OUT(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_LOW(elec)         TSS_GPIO_CLEAR(TSS_E##elec##_P,TSS_E##elec##_B); TSS_GPIO_OUT(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_LOW_OUT(elec)     TSS_GPIO_OUT(TSS_E##elec##_P,TSS_E##elec##_B)
  #define TSS_ELECTRODE_BIT_NUM(elec)     TSS_E##elec##_B

  #if TSS_USE_DEFAULT_ELECTRODE_LEVEL_LOW
    #define TSS_ELECTRODE_DEFAULT(elec)     TSS_ELECTRODE_DISCHARGE(elec)
  #else
    #define TSS_ELECTRODE_DEFAULT(elec)     ;
  #endif

  #if(TSS_GPIO_VERSION == 2)
    #define TSS_SAVE_EL_PORT_ADR(elec)      (tss_pu8ElectrodePortAdr = TSS_GPIO_PORT_ADR(TSS_E##elec##_P));(tss_pu8ElectrodePortControlAdr = TSS_GPIO_CONTROL_PORT_ADR(TSS_E##elec##_P));
    #define TSS_SAVE_EL_PORT_MASK(elec)     (tss_u8ElectrodePortMask = 1 << TSS_E##elec##_B)
    #define TSS_SAVE_ELECTRODE_PORT(elec)   TSS_SAVE_EL_PORT_ADR(elec);TSS_SAVE_EL_PORT_MASK(elec);

    #define TSS_SET_ELECTRODE_HIGH()        *tss_pu8ElectrodePortAdr |= tss_u8ElectrodePortMask;
    #define TSS_SET_ELECTRODE_LOW()         *tss_pu8ElectrodePortAdr &= ~tss_u8ElectrodePortMask;
    #define TSS_SET_ELECTRODE_OUTPUT()      *(tss_pu8ElectrodePortControlAdr+8) &= ~tss_u8ElectrodePortMask;*(tss_pu8ElectrodePortControlAdr) |= tss_u8ElectrodePortMask;
    #define TSS_SET_ELECTRODE_OUTPUT_HIGH() TSS_SET_ELECTRODE_HIGH();TSS_SET_ELECTRODE_OUTPUT();
    #define TSS_SET_ELECTRODE_OUTPUT_LOW()  TSS_SET_ELECTRODE_LOW();TSS_SET_ELECTRODE_OUTPUT();
  #else

    /*! GPIO - Peripheral register structure */
    #ifdef __COLDFIRE__
      #pragma pack(1) 
    #endif
    typedef struct TSS_GPIO_MemMap {
      UINT8 D;
      UINT8 DD;      
    } volatile *TSS_GPIO_MemMapPtr;
  
    #define TSS_SAVE_EL_PORT_ADR(elec)      (tss_pu8ElectrodePortAdr = TSS_GPIO_PORT_ADR(TSS_E##elec##_P))
    #define TSS_SAVE_EL_PORT_MASK(elec)     (tss_u8ElectrodePortMask = 1 << TSS_E##elec##_B)
    #define TSS_SAVE_ELECTRODE_PORT(elec)   TSS_SAVE_EL_PORT_ADR(elec);TSS_SAVE_EL_PORT_MASK(elec);

    #define TSS_SET_ELECTRODE_HIGH()        *tss_pu8ElectrodePortAdr |= tss_u8ElectrodePortMask;
    #define TSS_SET_ELECTRODE_LOW()         *tss_pu8ElectrodePortAdr &= ~tss_u8ElectrodePortMask;
    #define TSS_SET_ELECTRODE_OUTPUT()      *(tss_pu8ElectrodePortAdr+1) |= tss_u8ElectrodePortMask;
    #define TSS_SET_ELECTRODE_OUTPUT_HIGH() TSS_SET_ELECTRODE_HIGH();TSS_SET_ELECTRODE_OUTPUT();
    #define TSS_SET_ELECTRODE_OUTPUT_LOW()  TSS_SET_ELECTRODE_LOW();TSS_SET_ELECTRODE_OUTPUT();
  #endif 
 
  #define TSS_CLEAR_SAMPLE_INTERRUPTED_FLAG()   (tss_u8SampleIntFlag = 0U)
  #define TSS_SAMPLE_INTERRUPTED                (tss_u8SampleIntFlag != 0U)

  /* Solving of Headers compatibility */
  #if TSS_KINETIS_MCU || TSS_CFM_MCU /* Kinetis */
    #ifndef RGPIO_PDORA 
      #define RGPIO_MemMapPtr                 GPIO_MemMapPtr
    #endif
    #ifndef GPIO_PDDR_PDD_MASK
      #define PDDR                            POER
    #endif
  #endif  

  /* Special MCU exceptions solving */
  #if TSS_DETECT_PORT(A)
    #ifndef VectorNumber_Vporta  
      #define VectorNumber_Vporta           VectorNumber_Vport
    #endif
  #endif

  #if TSS_DETECT_PORT(B)
    #ifndef VectorNumber_Vportb  
      #define VectorNumber_Vportb           VectorNumber_Vport
    #endif
  #endif

  #if TSS_DETECT_PORT(C)
    #ifndef VectorNumber_Vportc  
      #define VectorNumber_Vportc           VectorNumber_Vport
    #endif
  #endif
  /* DZ60 exception */
  #if TSS_DETECT_PORT(D)
    #ifndef VectorNumber_Vportd  
      #define VectorNumber_Vportd           VectorNumber_Vport
    #endif
  #endif

  #if TSS_DETECT_PORT(J)
    #ifndef VectorNumber_Vportj  
      #define VectorNumber_Vportj           VectorNumber_Vport
    #endif
  #endif

#endif  /* TSS_GPIO_H */
