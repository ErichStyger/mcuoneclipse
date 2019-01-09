/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file usb_user_config.h  << EST 'user_config.h' conflicts with MQX Lite
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains User Modifiable Macros for Virtual COM Loopback
 *        Application
 *
 *****************************************************************************/
#if 0 /* << EST */
#include "derivative.h"

#if (defined MCU_MK70F12) || (defined __MCF52277_H__)
	#define  HIGH_SPEED_DEVICE	(0)
#else
	#define  HIGH_SPEED_DEVICE	(0)
#endif

#if (defined MCU_MK20D7) || (defined MCU_MK40D7)
	#define MCGOUTCLK_72_MHZ
#endif

#if ((defined __MK_xxx_H__)||(defined MCU_mcf51jf128))
    #define  KEY_PRESS_SIM_TMR_INTERVAL		(1000)        /* 2s between simulated key press events */
#else
	#ifdef __MCF52277_H__
		#define  BUTTON_PRESS_SIMULATION	(1)
		#define  KEY_PRESS_SIM_TMR_INTERVAL	(2000)        /* 2s between simulated key press events */
	#endif
#endif

#else
#include "FSL_USB_Stack_Config.h"

/* device is Kinetis K22FN120 << EST */
#define  HIGH_SPEED_DEVICE            (0)


#endif
/*
   Below two MACROS are required for Virtual COM Loopback
   Application to execute
*/
#define LONG_SEND_TRANSACTION       /* support to send large data pkts */
#define LONG_RECEIVE_TRANSACTION    /* support to receive large data pkts */
#ifndef _MC9S08JS16_H
  #define USB_OUT_PKT_SIZE 32			/* Define the maximum data length received from the host */
#else
  #define USB_OUT_PKT_SIZE 16			/* Define the maximum data length received from the host */
#endif

/* User Defined MACRO to set number of Timer Objects */
#define MAX_TIMER_OBJECTS		   5

#if MAX_TIMER_OBJECTS
  /* When Enabled Timer Callback is invoked with an argument */
  #define TIMER_CALLBACK_ARG
  #undef TIMER_CALLBACK_ARG
#endif

#if 0 /* << EST */
#ifndef _MC9S08JS16_H
#define USB_PACKET_SIZE  uint_16 /* support 16/32 bit packet size */
#else
#define USB_PACKET_SIZE  uint_8 /* support 8 bit packet size */
#endif
#else
/* device is Kinetis K22FN120 << EST */
#define USB_PACKET_SIZE  uint_16 /* support 16/32 bit packet size */
#endif

#if 0 /* << EST */
#ifndef _MCF51JM128_H
/* Use double buffered endpoints 5 & 6. To be only used with S08 cores */
#define DOUBLE_BUFFERING_USED
#endif
#else
/* device is Kinetis K22FN120 << EST */
/* Use double buffered endpoints 5 & 6. To be only used with S08 cores */
#define DOUBLE_BUFFERING_USED
#endif
