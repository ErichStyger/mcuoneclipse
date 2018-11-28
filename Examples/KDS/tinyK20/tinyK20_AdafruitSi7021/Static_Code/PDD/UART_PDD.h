/*
  PDD layer implementation for peripheral type UART
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(UART_PDD_H_)
#define UART_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error UART PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK10D5) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MK10D7) /* UART0, UART1, UART2, UART3, UART4 */ && \
      !defined(MCU_MK10F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK10DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK11DA5) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK11DA5WS) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK11D5) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK11D5WS) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK12D5) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK20D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK20D5) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MK20D7) /* UART0, UART1, UART2, UART3, UART4 */ && \
      !defined(MCU_MK20F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK20DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK21DA5) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK21DA5WS) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK21D5) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK21D5WS) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK21FA12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK21FA12WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK21F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK21F12WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK22D5) /* UART0, UART1, UART2, UART3 */ && \
      !defined(MCU_MK22F12810) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MK22F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK22F25612) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MK22F51212) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MK24F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK30D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK30D7) /* UART0, UART1, UART2, UART3, UART4 */ && \
      !defined(MCU_MK30DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK40D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK40D7) /* UART0, UART1, UART2, UART3, UART4 */ && \
      !defined(MCU_MK40DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK40X256VMD100) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK50D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK50D7) /* UART0, UART1, UART2, UART3, UART4 */ && \
      !defined(MCU_MK50DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK51D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK51D7) /* UART0, UART1, UART2, UART3, UART4 */ && \
      !defined(MCU_MK51DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK52D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK52DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK53D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK53DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK60D10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK60F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK60F15) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK60DZ10) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK60N512VMD100) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK61F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK61F15) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK61F12WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK61F15WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK63F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK63F12WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK64F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK70F12) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK70F15) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK70F12WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MK70F15WS) /* UART0, UART1, UART2, UART3, UART4, UART5 */ && \
      !defined(MCU_MKE02Z2) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKE02Z4) /* UART0, UART1, UART2 */ && \
      !defined(MCU_SKEAZN642) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKE04Z1284) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKE04Z4) /* UART0 */ && \
      !defined(MCU_SKEAZN84) /* UART0 */ && \
      !defined(MCU_MKE06Z4) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKL14Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL15Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL16Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL24Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL25Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL26Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL34Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL36Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKL46Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKV10Z7) /* UART0, UART1 */ && \
      !defined(MCU_MKV31F12810) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKV31F25612) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKV31F51212) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKW01Z4) /* UART1, UART2 */ && \
      !defined(MCU_MKW21D5) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKW21D5WS) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKW22D5) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKW22D5WS) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKW24D5) /* UART0, UART1, UART2 */ && \
      !defined(MCU_MKW24D5WS) /* UART0, UART1, UART2 */ && \
      !defined(MCU_SKEAZ1284) /* UART0, UART1, UART2 */
  // Unsupported MCU is active
  #error UART PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt masks */
#define UART_PDD_INTERRUPT_TRANSMITTER          UART_C2_TIE_MASK /**< Transmitter interrupt enable mask */
#define UART_PDD_INTERRUPT_TRANSMITTER_COMPLETE UART_C2_TCIE_MASK /**< Transmitter complete interrupt enable mask */
#define UART_PDD_INTERRUPT_RECEIVER             UART_C2_RIE_MASK /**< Receiver interrupt enable mask */
#define UART_PDD_INTERRUPT_IDLE                 UART_C2_ILIE_MASK /**< Idle interrupt enable mask */
#define UART_PDD_INTERRUPT_PARITY_ERROR         UART_C3_PEIE_MASK /**< Parity error interrupt enable mask */
#define UART_PDD_INTERRUPT_FRAMING_ERROR        UART_C3_FEIE_MASK /**< Framing error interrupt enable mask */
#define UART_PDD_INTERRUPT_NOISE_ERROR          UART_C3_NEIE_MASK /**< Noise error interrupt enable mask */
#define UART_PDD_INTERRUPT_OVERRUN_ERROR        UART_C3_ORIE_MASK /**< Overrun error interrupt enable mask */

/* Status flags constants. */
#define UART_PDD_TX_DATA_EMPTY_FLAG    UART_S1_TDRE_MASK /**< Transmitter FIFO word count is at or below watermark */
#define UART_PDD_TX_IDLE_FLAG          UART_S1_TC_MASK /**< No transmission in progress (transmission activity complete) */
#define UART_PDD_RX_DATA_FULL_FLAG     UART_S1_RDRF_MASK /**< Receiver FIFO word count is above watermark */
#define UART_PDD_RX_IDLE_FLAG          UART_S1_IDLE_MASK /**< Receiver input has become idle (after receiving a valid frame) */
#define UART_PDD_RX_OVERRUN_FLAG       UART_S1_OR_MASK /**< Receiver buffer overrun */
#define UART_PDD_RX_NOISE_FLAG         UART_S1_NF_MASK /**< Receiver input detect a noise. */
#define UART_PDD_RX_FRAMING_ERROR_FLAG UART_S1_FE_MASK /**< Receiver framing error detect */
#define UART_PDD_RX_PARITY_ERROR_FLAG  UART_S1_PF_MASK /**< Receiver parity error detect */

/* Status 2 flags constants. */
#define UART_PDD_LIN_BREAK_DETECT_FLAG    UART_S2_LBKDIF_MASK /**< LIN break character is detected on the receiver input */
#define UART_PDD_RXD_PIN_ACTIVE_EDGE_FLAG UART_S2_RXEDGIF_MASK /**< Active edge occurs on the RxD pin */
#define UART_PDD_RECEIVER_ACTIVE_FLAG     UART_S2_RAF_MASK /**< Receiver active, RxD input not idle */

/* Received data status constants. */
#define UART_PDD_DATA_RECEIVED_WITH_NOISE        UART_ED_NOISY_MASK /**< The data was received with noise */
#define UART_PDD_DATA_RECEIVED_WITH_PARITY_ERROR UART_ED_PARITYE_MASK /**< The dataword was received with a parity error */

/* Enable FIFO masks */
#define UART_PDD_TX_FIFO_ENABLE UART_PFIFO_TXFE_MASK /**< Transmitter FIFO enable mask */
#define UART_PDD_RX_FIFO_ENABLE UART_PFIFO_RXFE_MASK /**< Receiver FIFO enable mask */

/* FIFO flush masks */
#define UART_PDD_TX_FIFO_FLUSH UART_CFIFO_TXFLUSH_MASK /**< Transmitter FIFO flush command mask */
#define UART_PDD_RX_FIFO_FLUSH UART_CFIFO_RXFLUSH_MASK /**< Receiver FIFO flush command mask */

#if ((defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)))
/* Rx buffer full, Tx buffer empty and error interrupt masks constant */
  #define UART_PDD_TX_FIFO_OVERFLOW_INT  UART_CFIFO_TXOFE_MASK /**< Transmit FIFO overflow interrupt mask */
  #define UART_PDD_RX_FIFO_UNDERFLOW_INT UART_CFIFO_RXUFE_MASK /**< Receive FIFO underflow interrupt mask */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Rx buffer full, Tx buffer empty and error interrupt masks constant */
  #define UART_PDD_RX_FIFO_OVERFLOW_INT  UART_CFIFO_RXOFE_MASK /**< Receive FIFO overflow interrupt mask */
  #define UART_PDD_TX_FIFO_OVERFLOW_INT  UART_CFIFO_TXOFE_MASK /**< Transmit FIFO overflow interrupt mask */
  #define UART_PDD_RX_FIFO_UNDERFLOW_INT UART_CFIFO_RXUFE_MASK /**< Receive FIFO underflow interrupt mask */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)))
/* FIFO status flags constant */
  #define UART_PDD_TX_FIFO_EMPTY_FLAG     UART_SFIFO_TXEMPT_MASK /**< Transmit buffer/FIFO empty mask */
  #define UART_PDD_RX_FIFO_EMPTY_FLAG     UART_SFIFO_RXEMPT_MASK /**< Receive buffer/FIFO empty mask */
  #define UART_PDD_TX_FIFO_OVERFLOW_FLAG  UART_SFIFO_TXOF_MASK /**< Transmit FIFO overflow flag mask */
  #define UART_PDD_RX_FIFO_UNDERFLOW_FLAG UART_SFIFO_RXUF_MASK /**< Receive FIFO underflow flag mask */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* FIFO status flags constant */
  #define UART_PDD_TX_FIFO_EMPTY_FLAG     UART_SFIFO_TXEMPT_MASK /**< Transmit buffer/FIFO empty mask */
  #define UART_PDD_RX_FIFO_EMPTY_FLAG     UART_SFIFO_RXEMPT_MASK /**< Receive buffer/FIFO empty mask */
  #define UART_PDD_RX_FIFO_OVERFLOW_FLAG  UART_SFIFO_RXOF_MASK /**< Receive FIFO overflow flag mask */
  #define UART_PDD_TX_FIFO_OVERFLOW_FLAG  UART_SFIFO_TXOF_MASK /**< Transmit FIFO overflow flag mask */
  #define UART_PDD_RX_FIFO_UNDERFLOW_FLAG UART_SFIFO_RXUF_MASK /**< Receive FIFO underflow flag mask */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* ISO7816 Interrupt masks */
#define UART_PDD_ISO7816_WAIT_TIMER_INT                UART_IE7816_WTE_MASK /**< Wait timer interrupt mask */
#define UART_PDD_ISO7816_CHAR_WAIT_TIMER_INT           UART_IE7816_CWTE_MASK /**< Character wait timer interrupt mask */
#define UART_PDD_ISO7816_BLOCK_WAIT_TIMER_INT          UART_IE7816_BWTE_MASK /**< Block wait timer interrupt mask */
#define UART_PDD_ISO7816_INITIAL_CHAR_DETECTED_INT     UART_IE7816_INITDE_MASK /**< Initial character detected interrupt mask */
#define UART_PDD_ISO7816_GUARD_TIMER_VIOLATED_INT      UART_IE7816_GTVE_MASK /**< Guard timer violated interrupt mask */
#define UART_PDD_ISO7816_TRANSMIT_THRESHOLD_EXCEED_INT UART_IE7816_TXTE_MASK /**< Transmit threshold exceeded interrupt mask */
#define UART_PDD_ISO7816_RECEIVE_THRESHOLD_EXCEED_INT  UART_IE7816_RXTE_MASK /**< Receive threshold exceeded interrupt mask */

/* ISO7816 interrupt flag masks */
#define UART_PDD_ISO7816_WAIT_TIMER_FLAG                UART_IS7816_WT_MASK /**< Wait timer interrupt flag mask */
#define UART_PDD_ISO7816_CHAR_WAIT_TIMER_FLAG           UART_IS7816_CWT_MASK /**< Character wait timer interrupt flag mask */
#define UART_PDD_ISO7816_BLOCK_WAIT_TIMER_FLAG          UART_IS7816_BWT_MASK /**< Block wait timer interrupt flag mask */
#define UART_PDD_ISO7816_INITIAL_CHAR_DETECTED_FLAG     UART_IS7816_INITD_MASK /**< Initial character detected interrupt flag mask */
#define UART_PDD_ISO7816_GUARD_TIMER_VIOLATED_FLAG      UART_IS7816_GTV_MASK /**< Guard timer violated interrupt flag mask */
#define UART_PDD_ISO7816_TRANSMIT_THRESHOLD_EXCEED_FLAG UART_IS7816_TXT_MASK /**< Transmit threshold exceeded interrupt flag mask */
#define UART_PDD_ISO7816_RECEIVE_THRESHOLD_EXCEED_FLAG  UART_IS7816_RXT_MASK /**< Receive threshold exceeded interrupt flag mask */

/* CEA709.1-B interrupt masks constant */
#define UART_PDD_CEA7091B_PREAMBLE_ERROR_FLAG     UART_S3_PEF_MASK /**< Preamble error flag mask */
#define UART_PDD_CEA7091B_WBASE_EXPIRED_FLAG      UART_S3_WBEF_MASK /**< WBASE expired flag mask */
#define UART_PDD_CEA7091B_INIT_SYNC_DETECTED_FLAG UART_S3_ISD_MASK /**< Initial sync detection flag mask */
#define UART_PDD_CEA7091B_PACKED_RECEIVED_FLAG    UART_S3_PRXF_MASK /**< Packet received flag mask */
#define UART_PDD_CEA7091B_PACKED_TRANSMITTED_FLAG UART_S3_PTXF_MASK /**< Packet transmitted flag mask */
#define UART_PDD_CEA7091B_PACKED_CYCLE_TIMER_FLAG UART_S3_PCTEF_MASK /**< Packet cycle timer expired flag mask */
#define UART_PDD_CEA7091B_PREAMBLE_START_FLAG     UART_S3_PSF_MASK /**< Preamble start flag mask */
#define UART_PDD_CEA7091B_TRANSMISSION_FAIL_FLAG  UART_S3_TXFF_MASK /**< Transmission fail flag mask */

/* CEA709.1-B interrupt masks constant */
#define UART_PDD_CEA7091B_COLLISION_DETECTED_FLAG UART_S4_CDET_MASK /**< Collision detection flag mask */
#define UART_PDD_CEA7091B_FRAMING_ERROR_FLAG      UART_S4_FE_MASK /**< Framing error flag mask */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Loop mode */
  #define UART_PDD_LOOP_MODE_NORMAL       0U       /**< Normal operation mode. No loopback selected. */
  #define UART_PDD_LOOP_MODE_LOCAL_LOOP   0x1U     /**< Local loopback mode. */
  #define UART_PDD_LOOP_MODE_RX_TO_TX_PIN 0x2U     /**< Receiver input connected to TXD pin (single wire operation) */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Loop mode */
  #define UART_PDD_LOOP_MODE_NORMAL       0U       /**< Normal operation mode. No loopback selected */
  #define UART_PDD_LOOP_MODE_LOCAL_LOOP   0x80U    /**< Local loopback mode. Receiver input internally connected to transmitter output */
  #define UART_PDD_LOOP_MODE_RX_TO_TX_PIN 0xA0U    /**< Receiver input connected to TXD pin (single wire operation) */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Data width */
  #define UART_PDD_WIDTH_8 0U                      /**< 8-bit communication */
  #define UART_PDD_WIDTH_9 0x10U                   /**< 9-bit communication */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Data width */
  #define UART_PDD_WIDTH_8  0U                     /**< 8-bit communication */
  #define UART_PDD_WIDTH_9  0x1U                   /**< 9-bit communication */
  #define UART_PDD_WIDTH_10 0x2U                   /**< 10-bit communication (10th bit can be used only as parity bit) */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Wake-up condition constants. */
#define UART_PDD_BY_IDLE_LINE    0U              /**< Idle line wake-up */
#define UART_PDD_BY_ADDRESS_MARK 0x8U            /**< Address mark wake-up */

/* Idle line type constants. */
#define UART_PDD_AFTER_START_BIT 0U              /**< Idle character bit count starts after start bit. */
#define UART_PDD_AFTER_STOP_BIT  0x4U            /**< Idle character bit count starts after stop bit. */

/* Parity types */
#define UART_PDD_PARITY_NONE 0U                  /**< No parity */
#define UART_PDD_PARITY_EVEN 0x2U                /**< Even parity */
#define UART_PDD_PARITY_ODD  0x3U                /**< Even parity */

/* Receiver power states. */
#define UART_PDD_POWER_NORMAL  0U                /**< Normal operation. */
#define UART_PDD_POWER_STANDBY 0x2U              /**< Standby mode (waiting for a wakeup condition). */

/* UART data shift order constants */
#define UART_PDD_LSB_FIRST 0x20U                 /**< Data transfers start with least significant bit */
#define UART_PDD_MSB_FIRST 0U                    /**< Data transfers start with most significant bit */

/* Break transmit character length constants */
#define UART_PDD_BREAK_CHARACTER_10_11_12_BITS 0U /**< Break character is 10, 11, or 12 bits long */
#define UART_PDD_BREAK_CHARACTER_13_14_BITS    0x4U /**< Break character is 13 or 14 bits long */

/* Transmitter pin data direction (in single-wire mode) constants */
#define UART_PDD_TX_PIN_IS_AN_INPUT  0U          /**< TxD pin is an input in single wire mode */
#define UART_PDD_TX_PIN_IS_AN_OUTPUT 0x20U       /**< TxD pin is an output in single wire mode */

/* Position of a parity bit */
#define UART_PDD_PARITY_BIT_POSITION_9  0U       /**< Parity bit is the 9-th bit in the serial transmission */
#define UART_PDD_PARITY_BIT_POSITION_10 0x20U    /**< Parity bit is the 10-th bit in the serial transmission */

/* Request-to-send transmitter polarity constants */
#define UART_PDD_RTS_ACTIVE_LOW  0U              /**< Transmitter RTS is active low */
#define UART_PDD_RTS_ACTIVE_HIGH 0x4U            /**< Transmitter RTS is active high */

/* Parity types */
#define UART_PDD_TX_NARROW_PULSE_3_DIV_16 0U     /**< 3/16 narrow pulse */
#define UART_PDD_TX_NARROW_PULSE_1_DIV_16 0x1U   /**< 1/16 narrow pulse */
#define UART_PDD_TX_NARROW_PULSE_1_DIV_32 0x2U   /**< 1/32 narrow pulse */
#define UART_PDD_TX_NARROW_PULSE_1_DIV_4  0x3U   /**< 1/4 narrow pulse */

/* Transmit FIFO/Buffer depth constants. */
#define UART_PDD_TX_FIFO_SIZE_1   0U             /**< Transmit FIFO/Buffer depth = 1 dataword */
#define UART_PDD_TX_FIFO_SIZE_4   0x10U          /**< Transmit FIFO/Buffer depth = 4 datawords */
#define UART_PDD_TX_FIFO_SIZE_8   0x20U          /**< Transmit FIFO/Buffer depth = 8 datawords */
#define UART_PDD_TX_FIFO_SIZE_16  0x30U          /**< Transmit FIFO/Buffer depth = 16 datawords */
#define UART_PDD_TX_FIFO_SIZE_32  0x40U          /**< Transmit FIFO/Buffer depth = 32 datawords */
#define UART_PDD_TX_FIFO_SIZE_64  0x50U          /**< Transmit FIFO/Buffer depth = 64 datawords */
#define UART_PDD_TX_FIFO_SIZE_128 0x60U          /**< Transmit FIFO/Buffer depth = 128 datawords */

/* Receive FIFO/Buffer depth constants. */
#define UART_PDD_RX_FIFO_SIZE_1   0U             /**< Receive FIFO/Buffer depth = 1 dataword */
#define UART_PDD_RX_FIFO_SIZE_4   0x1U           /**< Receive FIFO/Buffer depth = 4 datawords */
#define UART_PDD_RX_FIFO_SIZE_8   0x2U           /**< Receive FIFO/Buffer depth = 8 datawords */
#define UART_PDD_RX_FIFO_SIZE_16  0x3U           /**< Receive FIFO/Buffer depth = 16 datawords */
#define UART_PDD_RX_FIFO_SIZE_32  0x4U           /**< Receive FIFO/Buffer depth = 32 datawords */
#define UART_PDD_RX_FIFO_SIZE_64  0x5U           /**< Receive FIFO/Buffer depth = 64 datawords */
#define UART_PDD_RX_FIFO_SIZE_128 0x6U           /**< Receive FIFO/Buffer depth = 128 datawords */

/* Transfer type constants */
#define UART_PDD_ISO7816_TRANSFER_TYPE_T0 0U     /**< T = 0 per the ISO-7816 specification */
#define UART_PDD_ISO7816_TRANSFER_TYPE_T1 0x2U   /**< T = 1 per the ISO-7816 specification */

/* Collision polarity constants */
#define UART_PDD_CEA7091b_COLLISION_SIGNAL_LOW  0U /**< Collision signal is active low */
#define UART_PDD_CEA7091b_COLLISION_SIGNAL_HIGH 0x10U /**< Collision signal is active high */

/* CEA709.1-B collision status constants. */
#define UART_PDD_CEA7091B_NO_COLLISION            0U /**< No collision */
#define UART_PDD_CEA7091B_COLLISION_PREAMBLE      0x4U /**< Collision occurred during preamble */
#define UART_PDD_CEA7091B_COLLISION_SYNCH_OR_DATA 0x8U /**< Collision occurred during byte sync or data */
#define UART_PDD_CEA7091B_COLLISION_LINE_CODE     0xCU /**< Collision occurred during line code violation */

/* Stop bit lengths */
#define UART_PDD_STOP_BIT_LEN_1 0U               /**< One stop bit. */
#define UART_PDD_STOP_BIT_LEN_2 0x20U            /**< Two stop bits. */


/* ----------------------------------------------------------------------------
   -- SetBaudRate
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets new baud rate value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BaudRate New baud rate value. This parameter is a 13-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDH, UART0_BDL,
 *          UART1_BDH, UART1_BDL, UART2_BDH, UART2_BDL, UART3_BDH, UART3_BDL,
 *          UART4_BDH, UART4_BDL, UART5_BDH, UART5_BDL (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetBaudRate(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetBaudRate(PeripheralBase, BaudRate) ( \
    (UART_BDH_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_BDH_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_BDH_SBR_MASK))) | ( \
      (uint8_t)((uint16_t)(BaudRate) >> 8U)))), \
    (UART_BDL_REG(PeripheralBase) = \
     (uint8_t)(BaudRate)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBaudRateHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads baud rate high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_BDH, UART1_BDH,
 *          UART2_BDH, UART3_BDH, UART4_BDH, UART5_BDH (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadBaudRateHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadBaudRateHighReg(PeripheralBase) ( \
    UART_BDH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBaudRateHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into baud rate high
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the baud rate high register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDH, UART1_BDH,
 *          UART2_BDH, UART3_BDH, UART4_BDH, UART5_BDH (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteBaudRateHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteBaudRateHighReg(PeripheralBase, Value) ( \
    UART_BDH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBaudRateLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads baud rate low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_BDL, UART1_BDL,
 *          UART2_BDL, UART3_BDL, UART4_BDL, UART5_BDL (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadBaudRateLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadBaudRateLowReg(PeripheralBase) ( \
    UART_BDL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBaudRateLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into baud rate low
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the baud rate low register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDL, UART1_BDL,
 *          UART2_BDL, UART3_BDL, UART4_BDL, UART5_BDL (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteBaudRateLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteBaudRateLowReg(PeripheralBase, Value) ( \
    UART_BDL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetLoopMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Selects the loop mode operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param LoopMode Loop mode. This parameter is of "Loop mode" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetLoopMode(<peripheral>_BASE_PTR, UART_PDD_LOOP_MODE_NORMAL);
 *      @endcode
 */
  #define UART_PDD_SetLoopMode(PeripheralBase, LoopMode) ( \
      ((LoopMode) == UART_PDD_LOOP_MODE_NORMAL) ? ( \
        UART_C1_REG(PeripheralBase) &= \
         (uint8_t)(( \
          (uint8_t)(~(uint8_t)UART_C1_LOOPS_MASK)) & ( \
          (uint8_t)(~(uint8_t)UART_C1_RSRC_MASK)))) : (((LoopMode) == UART_PDD_LOOP_MODE_LOCAL_LOOP) ? ( \
        UART_C1_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(UART_C1_REG(PeripheralBase) | UART_C1_LOOPS_MASK)) & ( \
          (uint8_t)(~(uint8_t)UART_C1_RSRC_MASK)))) : ( \
        UART_C1_REG(PeripheralBase) |= \
         (uint8_t)(UART_C1_LOOPS_MASK | UART_C1_RSRC_MASK)) \
      ) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Selects the loop mode operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param LoopMode Loop mode. This parameter is of "Loop mode" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetLoopMode(<peripheral>_BASE_PTR, UART_PDD_LOOP_MODE_NORMAL);
 *      @endcode
 */
  #define UART_PDD_SetLoopMode(PeripheralBase, LoopMode) ( \
      UART_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         UART_C1_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)(UART_C1_LOOPS_MASK | UART_C1_RSRC_MASK))))) | ( \
        (uint8_t)(LoopMode))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableOperateInWaitMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables operate in wait mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device in wait mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableOperateInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableOperateInWaitMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      UART_C1_REG(PeripheralBase) |= \
       UART_C1_UARTSWAI_MASK) : ( \
      UART_C1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)UART_C1_UARTSWAI_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataWidth
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets the communication width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Width Data width. This parameter is of "Data width" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART0_C4,
 *          UART1_C1, UART1_C4, UART2_C1, UART2_C4, UART3_C1, UART3_C4, UART4_C1,
 *          UART4_C4, UART5_C1, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetDataWidth(<peripheral>_BASE_PTR, UART_PDD_WIDTH_8);
 *      @endcode
 */
  #define UART_PDD_SetDataWidth(PeripheralBase, Width) ( \
      UART_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C1_M_MASK))) | ( \
        (uint8_t)(Width))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets the communication width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Width Data width. This parameter is of "Data width" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART0_C4,
 *          UART1_C1, UART1_C4, UART2_C1, UART2_C4, UART3_C1, UART3_C4, UART4_C1,
 *          UART4_C4, UART5_C1, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetDataWidth(<peripheral>_BASE_PTR, UART_PDD_WIDTH_8);
 *      @endcode
 */
  #define UART_PDD_SetDataWidth(PeripheralBase, Width) ( \
      ( \
       ((Width) == UART_PDD_WIDTH_8) ? ( \
        UART_C1_REG(PeripheralBase) &= \
         (uint8_t)(~(uint8_t)UART_C1_M_MASK)) : (((Width) == UART_PDD_WIDTH_9) ? ( \
        UART_C1_REG(PeripheralBase) |= \
         UART_C1_M_MASK) : ( \
        UART_C1_REG(PeripheralBase) |= \
         UART_C1_M_MASK) \
      )), \
      ( \
       ((Width) == UART_PDD_WIDTH_8) ? ( \
        UART_C4_REG(PeripheralBase) &= \
         (uint8_t)(~(uint8_t)UART_C4_M10_MASK)) : (((Width) == UART_PDD_WIDTH_9) ? ( \
        UART_C4_REG(PeripheralBase) &= \
         (uint8_t)(~(uint8_t)UART_C4_M10_MASK)) : ( \
        UART_C4_REG(PeripheralBase) |= \
         UART_C4_M10_MASK) \
      )) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetWakeupCondition
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the wake-up condition.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Condition Wake-up condition. This parameter is of "Wake-up condition
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetWakeupCondition(<peripheral>_BASE_PTR,
 *      UART_PDD_BY_IDLE_LINE);
 *      @endcode
 */
#define UART_PDD_SetWakeupCondition(PeripheralBase, Condition) ( \
    UART_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C1_WAKE_MASK))) | ( \
      (uint8_t)(Condition))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectIdleLineType
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the idle line type, it determines when the receiver starts
 * counting logic 1s as idle character bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Idle line type. This parameter is of "Idle line type constants."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SelectIdleLineType(<peripheral>_BASE_PTR,
 *      UART_PDD_AFTER_START_BIT);
 *      @endcode
 */
#define UART_PDD_SelectIdleLineType(PeripheralBase, Type) ( \
    UART_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C1_ILT_MASK))) | ( \
      (uint8_t)(Type))) \
  )

/* ----------------------------------------------------------------------------
   -- SetParity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a communication parity type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Parity Parity type. This parameter is of "Parity types" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetParity(<peripheral>_BASE_PTR, UART_PDD_PARITY_NONE);
 *      @endcode
 */
#define UART_PDD_SetParity(PeripheralBase, Parity) ( \
    UART_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)0x3U))) | ( \
      (uint8_t)(Parity))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadControl1Reg(PeripheralBase) ( \
    UART_C1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 1 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C1, UART1_C1,
 *          UART2_C1, UART3_C1, UART4_C1, UART5_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteControl1Reg(PeripheralBase, Value) ( \
    UART_C1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART0_C3,
 *          UART1_C2, UART1_C3, UART2_C2, UART2_C3, UART3_C2, UART3_C3, UART4_C2,
 *          UART4_C3, UART5_C2, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableInterrupt(<peripheral>_BASE_PTR,
 *      UART_PDD_INTERRUPT_TRANSMITTER);
 *      @endcode
 */
#define UART_PDD_EnableInterrupt(PeripheralBase, Mask) ( \
    (UART_C2_REG(PeripheralBase) |= \
     (uint8_t)((uint8_t)(Mask) & (uint8_t)(~(uint8_t)0xFU))), \
    (UART_C3_REG(PeripheralBase) |= \
     (uint8_t)((uint8_t)(Mask) & 0xFU)) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART0_C3,
 *          UART1_C2, UART1_C3, UART2_C2, UART2_C3, UART3_C2, UART3_C3, UART4_C2,
 *          UART4_C3, UART5_C2, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_DisableInterrupt(<peripheral>_BASE_PTR,
 *      UART_PDD_INTERRUPT_TRANSMITTER);
 *      @endcode
 */
#define UART_PDD_DisableInterrupt(PeripheralBase, Mask) ( \
    (UART_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)((uint8_t)(Mask) & (uint8_t)(~(uint8_t)0xFU)))), \
    (UART_C3_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)((uint8_t)(Mask) & 0xFU))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxCompleteInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the status of the transmiter complete interrupt enable bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_GetTxCompleteInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetTxCompleteInterruptMask(PeripheralBase) ( \
    (uint8_t)(UART_C2_REG(PeripheralBase) & UART_C2_TCIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitter
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables UART transmitter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables transmitter. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableTransmitter(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableTransmitter(PeripheralBase, State) ( \
    UART_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C2_TE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C2_TE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiver
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables UART receiver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receiver. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiver(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableReceiver(PeripheralBase, State) ( \
    UART_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C2_RE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C2_RE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetReceiverPowerState
   ---------------------------------------------------------------------------- */

/**
 * @brief Places the receiver in a standby state where it waits for automatic
 * hardware detection of a selected wakeup condition.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Receiver power state to be set. This parameter is of "Receiver
 *        power states." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetReceiverPowerState(<peripheral>_BASE_PTR,
 *      UART_PDD_POWER_NORMAL);
 *      @endcode
 */
#define UART_PDD_SetReceiverPowerState(PeripheralBase, State) ( \
    UART_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C2_RWU_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Set the break signal.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_SetBreak(PeripheralBase) ( \
    UART_C2_REG(PeripheralBase) |= \
     UART_C2_SBK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the break signal.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_ClearBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ClearBreak(PeripheralBase) ( \
    UART_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)UART_C2_SBK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SendBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Send the break character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SendBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_SendBreak(PeripheralBase) ( \
    (UART_C2_REG(PeripheralBase) |= \
     UART_C2_SBK_MASK), \
    (UART_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)UART_C2_SBK_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadControl2Reg(PeripheralBase) ( \
    UART_C2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 2 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C2, UART1_C2,
 *          UART2_C2, UART3_C2, UART4_C2, UART5_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteControl2Reg(PeripheralBase, Value) ( \
    UART_C2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus1Flags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1, UART3_S1, UART4_S1, UART5_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadStatus1Flags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadStatus1Flags(PeripheralBase) ( \
    UART_S1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxCompleteStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the status of the transmiter complete interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1, UART3_S1, UART4_S1, UART5_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetTxCompleteStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetTxCompleteStatus(PeripheralBase) ( \
    (uint8_t)(UART_S1_REG(PeripheralBase) & UART_S1_TC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInterruptStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1, UART3_S1, UART4_S1, UART5_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadInterruptStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadInterruptStatusReg(PeripheralBase) ( \
    UART_S1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetBreak
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1, UART3_S1, UART4_S1, UART5_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetBreak(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetBreak(PeripheralBase) ( \
    (( \
      (uint8_t)(UART_S1_REG(PeripheralBase) & (uint8_t)(UART_S1_FE_MASK | UART_S1_RDRF_MASK))) == ( \
      (uint8_t)(UART_S1_FE_MASK | UART_S1_RDRF_MASK))) ? ( \
      0x1U) : ( \
      0U) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1, UART3_S1, UART4_S1, UART5_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadStatus1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadStatus1Reg(PeripheralBase) ( \
    UART_S1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatus2Flags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the flags of the status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadStatus2Flags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadStatus2Flags(PeripheralBase) ( \
    (uint8_t)(( \
     UART_S2_REG(PeripheralBase)) & ( \
     (uint8_t)(UART_S2_LBKDIF_MASK | (UART_S2_RXEDGIF_MASK | UART_S2_RAF_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearStatus2Flags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the flags of the status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_ClearStatus2Flags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_ClearStatus2Flags(PeripheralBase, Mask) ( \
    UART_S2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART_S2_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)(UART_S2_LBKDIF_MASK | UART_S2_RXEDGIF_MASK))))) | ( \
      (uint8_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataShiftOrder
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)))
/**
 * @brief Sets the UART data shift order.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Order UART data shift order value. The user should use one from the
 *        enumerated values. This parameter is of "UART data shift order constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR, UART_PDD_LSB_FIRST);
 *      @endcode
 */
  #define UART_PDD_SetDataShiftOrder(PeripheralBase, Order) ( \
      (PeripheralBase == UART0_BASE_PTR) ? ( \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_MSBF_MASK))) | ( \
          (uint8_t)(Order))) \
      ) : ( /* (PeripheralBase==UART1_BASE_PTR) || (PeripheralBase==UART2_BASE_PTR) || (PeripheralBase==UART3_BASE_PTR) || (PeripheralBase==UART4_BASE_PTR) || (PeripheralBase==UART5_BASE_PTR) */ \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(( \
           UART_S2_REG(PeripheralBase)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_MSBF_MASK)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
           (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
          (uint8_t)(Order))) \
      ) \
    )
#elif ((defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Sets the UART data shift order.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Order UART data shift order value. The user should use one from the
 *        enumerated values. This parameter is of "UART data shift order constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR, UART_PDD_LSB_FIRST);
 *      @endcode
 */
  #define UART_PDD_SetDataShiftOrder(PeripheralBase, Order) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         UART_S2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_MSBF_MASK)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
         (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
        (uint8_t)(Order))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets the UART data shift order.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Order UART data shift order value. The user should use one from the
 *        enumerated values. This parameter is of "UART data shift order constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR, UART_PDD_LSB_FIRST);
 *      @endcode
 */
  #define UART_PDD_SetDataShiftOrder(PeripheralBase, Order) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_MSBF_MASK))) | ( \
        (uint8_t)(Order))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableReceiveDataInversion
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)))
/**
 * @brief Enables receive data inversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive data inversion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveDataInversion(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveDataInversion(PeripheralBase, State) ( \
      (PeripheralBase == UART0_BASE_PTR) ? ( \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_RXINV_MASK))) | ( \
          (uint8_t)((uint8_t)(State) << UART_S2_RXINV_SHIFT))) \
      ) : ( /* (PeripheralBase==UART1_BASE_PTR) || (PeripheralBase==UART2_BASE_PTR) || (PeripheralBase==UART3_BASE_PTR) || (PeripheralBase==UART4_BASE_PTR) || (PeripheralBase==UART5_BASE_PTR) */ \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(( \
           UART_S2_REG(PeripheralBase)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RXINV_MASK)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
           (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
          (uint8_t)((uint8_t)(State) << UART_S2_RXINV_SHIFT))) \
      ) \
    )
#elif ((defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Enables receive data inversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive data inversion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveDataInversion(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveDataInversion(PeripheralBase, State) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         UART_S2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RXINV_MASK)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
         (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
        (uint8_t)((uint8_t)(State) << UART_S2_RXINV_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Enables receive data inversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive data inversion. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveDataInversion(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveDataInversion(PeripheralBase, State) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_RXINV_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_S2_RXINV_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- EnableReceiveWakeupIdleDetect
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)))
/**
 * @brief Enables receive wakeup idle detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive wakeup idle detect. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveWakeupIdleDetect(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveWakeupIdleDetect(PeripheralBase, State) ( \
      (PeripheralBase == UART0_BASE_PTR) ? ( \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_RWUID_MASK))) | ( \
          (uint8_t)((uint8_t)(State) << UART_S2_RWUID_SHIFT))) \
      ) : ( /* (PeripheralBase==UART1_BASE_PTR) || (PeripheralBase==UART2_BASE_PTR) || (PeripheralBase==UART3_BASE_PTR) || (PeripheralBase==UART4_BASE_PTR) || (PeripheralBase==UART5_BASE_PTR) */ \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(( \
           UART_S2_REG(PeripheralBase)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RWUID_MASK)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
           (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
          (uint8_t)((uint8_t)(State) << UART_S2_RWUID_SHIFT))) \
      ) \
    )
#elif ((defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Enables receive wakeup idle detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive wakeup idle detect. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveWakeupIdleDetect(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveWakeupIdleDetect(PeripheralBase, State) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         UART_S2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RWUID_MASK)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
         (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
        (uint8_t)((uint8_t)(State) << UART_S2_RWUID_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Enables receive wakeup idle detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables receive wakeup idle detect. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveWakeupIdleDetect(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveWakeupIdleDetect(PeripheralBase, State) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_RWUID_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_S2_RWUID_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetBreakLength
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)))
/**
 * @brief Sets the break transmit character length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Break transmit character length value. The user should use one
 *        from the enumerated values. This parameter is of "Break transmit
 *        character length constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetBreakLength(<peripheral>_BASE_PTR,
 *      UART_PDD_BREAK_CHARACTER_10_11_12_BITS);
 *      @endcode
 */
  #define UART_PDD_SetBreakLength(PeripheralBase, Length) ( \
      (PeripheralBase == UART0_BASE_PTR) ? ( \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_BRK13_MASK))) | ( \
          (uint8_t)(Length))) \
      ) : ( /* (PeripheralBase==UART1_BASE_PTR) || (PeripheralBase==UART2_BASE_PTR) || (PeripheralBase==UART3_BASE_PTR) || (PeripheralBase==UART4_BASE_PTR) || (PeripheralBase==UART5_BASE_PTR) */ \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(( \
           UART_S2_REG(PeripheralBase)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_BRK13_MASK)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
           (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
          (uint8_t)(Length))) \
      ) \
    )
#elif ((defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Sets the break transmit character length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Break transmit character length value. The user should use one
 *        from the enumerated values. This parameter is of "Break transmit
 *        character length constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetBreakLength(<peripheral>_BASE_PTR,
 *      UART_PDD_BREAK_CHARACTER_10_11_12_BITS);
 *      @endcode
 */
  #define UART_PDD_SetBreakLength(PeripheralBase, Length) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         UART_S2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_BRK13_MASK)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
         (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
        (uint8_t)(Length))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Sets the break transmit character length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Break transmit character length value. The user should use one
 *        from the enumerated values. This parameter is of "Break transmit
 *        character length constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetBreakLength(<peripheral>_BASE_PTR,
 *      UART_PDD_BREAK_CHARACTER_10_11_12_BITS);
 *      @endcode
 */
  #define UART_PDD_SetBreakLength(PeripheralBase, Length) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_BRK13_MASK))) | ( \
        (uint8_t)(Length))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- EnableLinBreakLongerCharacterDetection
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)))
/**
 * @brief Enables LIN break detection for longer character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables LIN break detection for longer character.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableLinBreakLongerCharacterDetection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableLinBreakLongerCharacterDetection(PeripheralBase, State) ( \
      (PeripheralBase == UART0_BASE_PTR) ? ( \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_LBKDE_MASK))) | ( \
          (uint8_t)((uint8_t)(State) << UART_S2_LBKDE_SHIFT))) \
      ) : ( /* (PeripheralBase==UART1_BASE_PTR) || (PeripheralBase==UART2_BASE_PTR) || (PeripheralBase==UART3_BASE_PTR) || (PeripheralBase==UART4_BASE_PTR) || (PeripheralBase==UART5_BASE_PTR) */ \
        UART_S2_REG(PeripheralBase) = \
         (uint8_t)(( \
          (uint8_t)(( \
           UART_S2_REG(PeripheralBase)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_LBKDE_MASK)) & (( \
           (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
           (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
          (uint8_t)((uint8_t)(State) << UART_S2_LBKDE_SHIFT))) \
      ) \
    )
#elif ((defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)))
/**
 * @brief Enables LIN break detection for longer character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables LIN break detection for longer character.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableLinBreakLongerCharacterDetection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableLinBreakLongerCharacterDetection(PeripheralBase, State) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         UART_S2_REG(PeripheralBase)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_LBKDE_MASK)) & (( \
         (uint8_t)(~(uint8_t)UART_S2_RXEDGIF_MASK)) & ( \
         (uint8_t)(~(uint8_t)UART_S2_LBKDIF_MASK)))))) | ( \
        (uint8_t)((uint8_t)(State) << UART_S2_LBKDE_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Enables LIN break detection for longer character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables LIN break detection for longer character.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableLinBreakLongerCharacterDetection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableLinBreakLongerCharacterDetection(PeripheralBase, State) ( \
      UART_S2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_S2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_S2_LBKDE_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_S2_LBKDE_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- ReadStatus2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadStatus2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadStatus2Reg(PeripheralBase) ( \
    UART_S2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatus2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into status 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the status 2 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S2, UART1_S2,
 *          UART2_S2, UART3_S2, UART4_S2, UART5_S2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteStatus2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteStatus2Reg(PeripheralBase, Value) ( \
    UART_S2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar9Bit
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the 9th bit of the character from the receive buffer shifted
 * to its bit position (9th). Must be called prior to calling GetChar8 to read the
 * whole 9-bit character.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 9-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: UART0_C3, UART1_C3,
 *          UART2_C3, UART3_C3, UART4_C3, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = UART_PDD_GetChar9Bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetChar9Bit(PeripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)((uint16_t)(UART_C3_REG(PeripheralBase) & UART_C3_R8_MASK) >> UART_C3_R8_SHIFT)) << ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar9
   ---------------------------------------------------------------------------- */

/**
 * @brief Puts 9-bits character into the transmit buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Char 9-bits character to be written to the data register. This
 *        parameter is a 9-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3, UART0_D,
 *          UART1_C3, UART1_D, UART2_C3, UART2_D, UART3_C3, UART3_D, UART4_C3,
 *          UART4_D, UART5_C3, UART5_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_PutChar9(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_PutChar9(PeripheralBase, Char) ( \
    (UART_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C3_T8_MASK))) | ( \
      (uint8_t)((uint8_t)((uint16_t)(Char) >> 8U) << UART_C3_T8_SHIFT)))), \
    (UART_D_REG(PeripheralBase) = \
     (uint8_t)(Char)) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxPinDataDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmitter pin data direction in single-wire mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Transmitter pin data direction value. The user should use
 *        one from the enumerated values. This parameter is of "Transmitter pin
 *        data direction (in single-wire mode) constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3, UART1_C3,
 *          UART2_C3, UART3_C3, UART4_C3, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetTxPinDataDirection(<peripheral>_BASE_PTR,
 *      UART_PDD_TX_PIN_IS_AN_INPUT);
 *      @endcode
 */
#define UART_PDD_SetTxPinDataDirection(PeripheralBase, Direction) ( \
    UART_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C3_TXDIR_MASK))) | ( \
      (uint8_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitDataInversion
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables transmit data inversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables transmit data inversion. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3, UART1_C3,
 *          UART2_C3, UART3_C3, UART4_C3, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableTransmitDataInversion(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableTransmitDataInversion(PeripheralBase, State) ( \
    UART_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C3_TXINV_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C3_TXINV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C3, UART1_C3,
 *          UART2_C3, UART3_C3, UART4_C3, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadControl3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadControl3Reg(PeripheralBase) ( \
    UART_C3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 3
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 3 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C3, UART1_C3,
 *          UART2_C3, UART3_C3, UART4_C3, UART5_C3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteControl3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteControl3Reg(PeripheralBase, Value) ( \
    UART_C3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- PutChar8
   ---------------------------------------------------------------------------- */

/**
 * @brief Puts 8-bits character into the transmit buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Char 8-bits character to be written to the data register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_D, UART1_D,
 *          UART2_D, UART3_D, UART4_D, UART5_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_PutChar8(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_PutChar8(PeripheralBase, Char) ( \
    UART_D_REG(PeripheralBase) = \
     (uint8_t)(Char) \
  )

/* ----------------------------------------------------------------------------
   -- GetChar8
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns a 8-bit character from the receive buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_D, UART1_D,
 *          UART2_D, UART3_D, UART4_D, UART5_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetChar8(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetChar8(PeripheralBase) ( \
    UART_D_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_D, UART1_D,
 *          UART2_D, UART3_D, UART4_D, UART5_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadDataReg(PeripheralBase) ( \
    UART_D_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the data register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_D, UART1_D,
 *          UART2_D, UART3_D, UART4_D, UART5_D (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteDataReg(PeripheralBase, Value) ( \
    UART_D_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetMatchAddress1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns match address 1 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA1, UART1_MA1,
 *          UART2_MA1, UART3_MA1, UART4_MA1, UART5_MA1 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetMatchAddress1Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetMatchAddress1Value(PeripheralBase) ( \
    UART_MA1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetMatchAddress1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a new match address 1 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Match address 1 value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA1, UART1_MA1,
 *          UART2_MA1, UART3_MA1, UART4_MA1, UART5_MA1 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetMatchAddress1Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetMatchAddress1Value(PeripheralBase, Address) ( \
    UART_MA1_REG(PeripheralBase) = \
     (uint8_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMatchAddress1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads match address 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA1, UART1_MA1,
 *          UART2_MA1, UART3_MA1, UART4_MA1, UART5_MA1 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadMatchAddress1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadMatchAddress1Reg(PeripheralBase) ( \
    UART_MA1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMatchAddress1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into match address 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match address 1 register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA1, UART1_MA1,
 *          UART2_MA1, UART3_MA1, UART4_MA1, UART5_MA1 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteMatchAddress1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteMatchAddress1Reg(PeripheralBase, Value) ( \
    UART_MA1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetMatchAddress2Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns match address 2 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA2, UART1_MA2,
 *          UART2_MA2, UART3_MA2, UART4_MA2, UART5_MA2 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetMatchAddress2Value(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetMatchAddress2Value(PeripheralBase) ( \
    UART_MA2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetMatchAddress2Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a new match address 2 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Match address 2 value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA2, UART1_MA2,
 *          UART2_MA2, UART3_MA2, UART4_MA2, UART5_MA2 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetMatchAddress2Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetMatchAddress2Value(PeripheralBase, Address) ( \
    UART_MA2_REG(PeripheralBase) = \
     (uint8_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMatchAddress2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads match address 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MA2, UART1_MA2,
 *          UART2_MA2, UART3_MA2, UART4_MA2, UART5_MA2 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadMatchAddress2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadMatchAddress2Reg(PeripheralBase) ( \
    UART_MA2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMatchAddress2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into match address 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match address 2 register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MA2, UART1_MA2,
 *          UART2_MA2, UART3_MA2, UART4_MA2, UART5_MA2 (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteMatchAddress2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteMatchAddress2Reg(PeripheralBase, Value) ( \
    UART_MA2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMatchAddress1Mode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables address 1 match mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables address 1 match mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4, UART1_C4,
 *          UART2_C4, UART3_C4, UART4_C4, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableMatchAddress1Mode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableMatchAddress1Mode(PeripheralBase, State) ( \
    UART_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C4_MAEN1_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C4_MAEN1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMatchAddress2Mode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables address 2 match mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables address 2 match mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4, UART1_C4,
 *          UART2_C4, UART3_C4, UART4_C4, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableMatchAddress2Mode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableMatchAddress2Mode(PeripheralBase, State) ( \
    UART_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C4_MAEN2_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C4_MAEN2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPositionOfParityBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the position of the parity bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Position Position of a parity bit. This parameter is of "Position of a
 *        parity bit" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4, UART1_C4,
 *          UART2_C4, UART3_C4, UART4_C4, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetPositionOfParityBit(<peripheral>_BASE_PTR,
 *      UART_PDD_PARITY_BIT_POSITION_9);
 *      @endcode
 */
#define UART_PDD_SetPositionOfParityBit(PeripheralBase, Position) ( \
    UART_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C4_M10_MASK))) | ( \
      (uint8_t)(Position))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBaudRateFineAdjust
   ---------------------------------------------------------------------------- */

/**
 * @brief Set new baud rate fine adjust value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FineAdjust New baud rate fine adjust value. This parameter is a 5-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4, UART1_C4,
 *          UART2_C4, UART3_C4, UART4_C4, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetBaudRateFineAdjust(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetBaudRateFineAdjust(PeripheralBase, FineAdjust) ( \
    UART_C4_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C4_BRFA_MASK))) | ( \
      (uint8_t)(FineAdjust))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C4, UART1_C4,
 *          UART2_C4, UART3_C4, UART4_C4, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadControl4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadControl4Reg(PeripheralBase) ( \
    UART_C4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into control 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 4 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C4, UART1_C4,
 *          UART2_C4, UART3_C4, UART4_C4, UART5_C4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteControl4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteControl4Reg(PeripheralBase, Value) ( \
    UART_C4_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitDma
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables/disables a transmit DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmit DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5, UART1_C4, UART2_C4 (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableTransmitDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableTransmitDma(PeripheralBase, State) ( \
      UART_C4_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C4_TDMAS_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_C4_TDMAS_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables/disables a transmit DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmit DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5, UART1_C4, UART2_C4 (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableTransmitDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableTransmitDma(PeripheralBase, State) ( \
      UART_C5_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_C5_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C5_TDMAS_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_C5_TDMAS_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableReceiveDma
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables/disables a receive DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receive DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5, UART1_C4, UART2_C4 (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveDma(PeripheralBase, State) ( \
      UART_C4_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_C4_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C4_RDMAS_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_C4_RDMAS_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables/disables a receive DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receive DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5, UART1_C4, UART2_C4 (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiveDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define UART_PDD_EnableReceiveDma(PeripheralBase, State) ( \
      UART_C5_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(UART_C5_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C5_RDMAS_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << UART_C5_RDMAS_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadControl5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadControl5Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadControl5Reg(PeripheralBase) ( \
    UART_C5_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into control 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 5 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteControl5Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteControl5Reg(PeripheralBase, Value) ( \
    UART_C5_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxDataExtendedStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the received data status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_ED, UART1_ED,
 *          UART2_ED, UART3_ED, UART4_ED, UART5_ED (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_GetRxDataExtendedStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetRxDataExtendedStatus(PeripheralBase) ( \
    UART_ED_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadExtendedDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads extended data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_ED, UART1_ED,
 *          UART2_ED, UART3_ED, UART4_ED, UART5_ED (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadExtendedDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadExtendedDataReg(PeripheralBase) ( \
    UART_ED_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiverRequestToSend
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables receiver request-to-send, it allows the RTS output to
 * control the CTS input of the transmitting device to prevent receiver overrun.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receiver request-to-send. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MODEM,
 *          UART1_MODEM, UART2_MODEM, UART3_MODEM, UART4_MODEM, UART5_MODEM (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableReceiverRequestToSend(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableReceiverRequestToSend(PeripheralBase, State) ( \
    UART_MODEM_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_MODEM_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_MODEM_RXRTSE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_MODEM_RXRTSE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitterRequestToSendPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the polarity of the transmitter RTS.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Request-to-send transmitter polarity. This parameter is of
 *        "Request-to-send transmitter polarity constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MODEM,
 *          UART1_MODEM, UART2_MODEM, UART3_MODEM, UART4_MODEM, UART5_MODEM (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetTransmitterRequestToSendPolarity(<peripheral>_BASE_PTR,
 *      UART_PDD_RTS_ACTIVE_LOW);
 *      @endcode
 */
#define UART_PDD_SetTransmitterRequestToSendPolarity(PeripheralBase, Polarity) ( \
    UART_MODEM_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_MODEM_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_MODEM_TXRTSPOL_MASK))) | ( \
      (uint8_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitterRequestToSend
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables transmitter request-to-send, it allows control RTS
 * before and after a transmission.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter request-to-send. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MODEM,
 *          UART1_MODEM, UART2_MODEM, UART3_MODEM, UART4_MODEM, UART5_MODEM (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableTransmitterRequestToSend(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableTransmitterRequestToSend(PeripheralBase, State) ( \
    UART_MODEM_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_MODEM_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_MODEM_TXRTSE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_MODEM_TXRTSE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransmitterClearToSend
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables transmitter clear-to-send operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter clear-to-send operation. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MODEM,
 *          UART1_MODEM, UART2_MODEM, UART3_MODEM, UART4_MODEM, UART5_MODEM (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableTransmitterClearToSend(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableTransmitterClearToSend(PeripheralBase, State) ( \
    UART_MODEM_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_MODEM_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_MODEM_TXCTSE_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModemReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads modem register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_MODEM,
 *          UART1_MODEM, UART2_MODEM, UART3_MODEM, UART4_MODEM, UART5_MODEM (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadModemReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadModemReg(PeripheralBase) ( \
    UART_MODEM_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModemReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into modem register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the modem register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_MODEM,
 *          UART1_MODEM, UART2_MODEM, UART3_MODEM, UART4_MODEM, UART5_MODEM (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteModemReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteModemReg(PeripheralBase, Value) ( \
    UART_MODEM_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInfraredModulation
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables infrared modulation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of infrared modulation. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IR, UART1_IR,
 *          UART2_IR, UART3_IR, UART4_IR, UART5_IR (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableInfraredModulation(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableInfraredModulation(PeripheralBase, State) ( \
    UART_IR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_IR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_IR_IREN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_IR_IREN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransmitterNarrowPulse
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets a transmitter narrow pulse.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Pulse narrow pulse. This parameter is of "Parity types" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IR, UART1_IR,
 *          UART2_IR, UART3_IR, UART4_IR, UART5_IR (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetTransmitterNarrowPulse(<peripheral>_BASE_PTR,
 *      UART_PDD_TX_NARROW_PULSE_3_DIV_16);
 *      @endcode
 */
#define UART_PDD_SetTransmitterNarrowPulse(PeripheralBase, Pulse) ( \
    UART_IR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_IR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_IR_TNP_MASK))) | ( \
      (uint8_t)(Pulse))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInfraredReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads infrared register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_IR, UART1_IR,
 *          UART2_IR, UART3_IR, UART4_IR, UART5_IR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadInfraredReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadInfraredReg(PeripheralBase) ( \
    UART_IR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInfraredReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into infrared register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the infrared register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IR, UART1_IR,
 *          UART2_IR, UART3_IR, UART4_IR, UART5_IR (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteInfraredReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteInfraredReg(PeripheralBase, Value) ( \
    UART_IR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFifo
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables FIFO specified by the FifoMask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FifoMask Specifies receive or transmit FIFO. Use constants from group
 *        "Enable FIFO masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_PFIFO,
 *          UART1_PFIFO, UART2_PFIFO, UART3_PFIFO, UART4_PFIFO, UART5_PFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableFifo(<peripheral>_BASE_PTR, UART_PDD_TX_FIFO_ENABLE);
 *      @endcode
 */
#define UART_PDD_EnableFifo(PeripheralBase, FifoMask) ( \
    UART_PFIFO_REG(PeripheralBase) |= \
     (uint8_t)(FifoMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxFifoSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the maximum number of transmit datawords that can be stored in
 * the transmit buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Transmit FIFO/Buffer depth constants." type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: UART0_PFIFO,
 *          UART1_PFIFO, UART2_PFIFO, UART3_PFIFO, UART4_PFIFO, UART5_PFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetTxFifoSize(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetTxFifoSize(PeripheralBase) ( \
    (uint8_t)(UART_PFIFO_REG(PeripheralBase) & UART_PFIFO_TXFIFOSIZE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxFifoSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the maximum number of receive datawords that can be stored in
 * the receive buffer before an overrun occurs.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Receive FIFO/Buffer depth constants." type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: UART0_PFIFO,
 *          UART1_PFIFO, UART2_PFIFO, UART3_PFIFO, UART4_PFIFO, UART5_PFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_GetRxFifoSize(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetRxFifoSize(PeripheralBase) ( \
    (uint8_t)(UART_PFIFO_REG(PeripheralBase) & UART_PFIFO_RXFIFOSIZE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFifoParametersReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO parameters register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_PFIFO,
 *          UART1_PFIFO, UART2_PFIFO, UART3_PFIFO, UART4_PFIFO, UART5_PFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadFifoParametersReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadFifoParametersReg(PeripheralBase) ( \
    UART_PFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFifoParametersReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into FIFO parameters
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the FIFO parameters register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_PFIFO,
 *          UART1_PFIFO, UART2_PFIFO, UART3_PFIFO, UART4_PFIFO, UART5_PFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteFifoParametersReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteFifoParametersReg(PeripheralBase, Value) ( \
    UART_PFIFO_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- FlushFifo
   ---------------------------------------------------------------------------- */

/**
 * @brief Flushes FIFO specified by the FifoMask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param FifoMask Specifies receive or transmit FIFO. Use constants from group
 *        "FIFO flush masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_FlushFifo(<peripheral>_BASE_PTR, UART_PDD_TX_FIFO_FLUSH);
 *      @endcode
 */
#define UART_PDD_FlushFifo(PeripheralBase, FifoMask) ( \
    UART_CFIFO_REG(PeripheralBase) |= \
     (uint8_t)(FifoMask) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFifoInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupt FIFO requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of FIFO interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableFifoInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_EnableFifoInterruptMask(PeripheralBase, Mask) ( \
    UART_CFIFO_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFifoInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupt FIFO requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of FIFO interrupt requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_DisableFifoInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_DisableFifoInterruptMask(PeripheralBase, Mask) ( \
    UART_CFIFO_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFifoControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadFifoControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadFifoControlReg(PeripheralBase) ( \
    UART_CFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFifoControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into FIFO control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the FIFO control register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteFifoControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteFifoControlReg(PeripheralBase, Value) ( \
    UART_CFIFO_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFifoStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the FIFO status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_SFIFO,
 *          UART1_SFIFO, UART2_SFIFO, UART3_SFIFO, UART4_SFIFO, UART5_SFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadFifoStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadFifoStatusFlags(PeripheralBase) ( \
    UART_SFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFifoStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears FIFO status flags defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of flag requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_SFIFO,
 *          UART1_SFIFO, UART2_SFIFO, UART3_SFIFO, UART4_SFIFO, UART5_SFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_ClearFifoStatusFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_ClearFifoStatusFlags(PeripheralBase, Mask) ( \
    UART_SFIFO_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFifoStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadFifoStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadFifoStatusReg(PeripheralBase) ( \
    UART_CFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFifoStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into FIFO status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the FIFO status register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_CFIFO,
 *          UART1_CFIFO, UART2_CFIFO, UART3_CFIFO, UART4_CFIFO, UART5_CFIFO (depending on
 *          the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteFifoStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteFifoStatusReg(PeripheralBase, Value) ( \
    UART_CFIFO_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxFifoWatermarkReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO transmit watermark register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_TWFIFO,
 *          UART1_TWFIFO, UART2_TWFIFO, UART3_TWFIFO, UART4_TWFIFO, UART5_TWFIFO (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadTxFifoWatermarkReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadTxFifoWatermarkReg(PeripheralBase) ( \
    UART_TWFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxFifoWatermarkReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into FIFO transmit
 * watermark register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the FIFO transmit watermark register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_TWFIFO,
 *          UART1_TWFIFO, UART2_TWFIFO, UART3_TWFIFO, UART4_TWFIFO, UART5_TWFIFO (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteTxFifoWatermarkReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteTxFifoWatermarkReg(PeripheralBase, Value) ( \
    UART_TWFIFO_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxFifoCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO transmit count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_TCFIFO,
 *          UART1_TCFIFO, UART2_TCFIFO, UART3_TCFIFO, UART4_TCFIFO, UART5_TCFIFO (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadTxFifoCountReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadTxFifoCountReg(PeripheralBase) ( \
    UART_TCFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxFifoWatermarkReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO receive watermark register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_RWFIFO,
 *          UART1_RWFIFO, UART2_RWFIFO, UART3_RWFIFO, UART4_RWFIFO, UART5_RWFIFO (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadRxFifoWatermarkReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadRxFifoWatermarkReg(PeripheralBase) ( \
    UART_RWFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxFifoWatermarkReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into FIFO receive
 * watermark register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the FIFO receive watermark register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_RWFIFO,
 *          UART1_RWFIFO, UART2_RWFIFO, UART3_RWFIFO, UART4_RWFIFO, UART5_RWFIFO (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteRxFifoWatermarkReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteRxFifoWatermarkReg(PeripheralBase, Value) ( \
    UART_RWFIFO_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxFifoCountkReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads FIFO receive count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_RCFIFO,
 *          UART1_RCFIFO, UART2_RCFIFO, UART3_RCFIFO, UART4_RCFIFO, UART5_RCFIFO (depending
 *          on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadRxFifoCountkReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadRxFifoCountkReg(PeripheralBase) ( \
    UART_RCFIFO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableGenerateNackOnOverflow
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables generating NACK if a receive buffer overrun.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state generating NACK on overflow. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableGenerateNackOnOverflow(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableGenerateNackOnOverflow(PeripheralBase, State) ( \
    UART_C7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C7816_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C7816_ONACK_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C7816_ONACK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableGenerateNackOnError
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables generating NACK if a parity error occurs or if INIT
 * is set and an invalid initial character is detected.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state generating NACK on error. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableGenerateNackOnError(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableGenerateNackOnError(PeripheralBase, State) ( \
    UART_C7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C7816_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C7816_ANACK_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C7816_ANACK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInitialCharDetection
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables generating initial char detection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of initial char detection. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableInitialCharDetection(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableInitialCharDetection(PeripheralBase, State) ( \
    UART_C7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C7816_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C7816_INIT_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C7816_INIT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816TransferType
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transfer type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Transfer type. This parameter is of "Transfer type constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816TransferType(<peripheral>_BASE_PTR,
 *      UART_PDD_ISO7816_TRANSFER_TYPE_T0);
 *      @endcode
 */
#define UART_PDD_SetIso7816TransferType(PeripheralBase, Type) ( \
    UART_C7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C7816_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C7816_TTYPE_MASK))) | ( \
      (uint8_t)(Type))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableIso7816Functionality
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables ISO-7816 functionality.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of ISO-7816 functionality . This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableIso7816Functionality(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableIso7816Functionality(PeripheralBase, State) ( \
    UART_C7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART_C7816_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)UART_C7816_ISO_7816E_MASK)))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816ControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_Read7816ControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816ControlReg(PeripheralBase) ( \
    UART_C7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816ControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 control register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C7816, UART1_C7816
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816ControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816ControlReg(PeripheralBase, Value) ( \
    UART_C7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableIso7816Interrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables ISO7816 interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "ISO7816 Interrupt
 *        masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IE7816,
 *          UART1_IE7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableIso7816Interrupt(<peripheral>_BASE_PTR,
 *      UART_PDD_ISO7816_WAIT_TIMER_INT);
 *      @endcode
 */
#define UART_PDD_EnableIso7816Interrupt(PeripheralBase, Mask) ( \
    UART_IE7816_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableIso7816Interrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IE7816,
 *          UART1_IE7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_DisableIso7816Interrupt(<peripheral>_BASE_PTR,
 *      UART_PDD_INTERRUPT_TRANSMITTER);
 *      @endcode
 */
#define UART_PDD_DisableIso7816Interrupt(PeripheralBase, Mask) ( \
    UART_IE7816_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816InterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_IE7816,
 *          UART1_IE7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_Read7816InterruptEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816InterruptEnableReg(PeripheralBase) ( \
    UART_IE7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816InterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 interrupt
 * enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 interrupt enable register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IE7816,
 *          UART1_IE7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816InterruptEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816InterruptEnableReg(PeripheralBase, Value) ( \
    UART_IE7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadIso7816StatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the ISO7816 status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "ISO7816 interrupt flag masks" for
 *         processing return value.
 * @remarks The macro accesses the following registers: UART0_IS7816,
 *          UART1_IS7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadIso7816StatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadIso7816StatusReg(PeripheralBase) ( \
    UART_IS7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearIso7816InterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears ISO7816 interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "ISO7816 interrupt flag masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IS7816,
 *          UART1_IS7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_ClearIso7816InterruptFlags(<peripheral>_BASE_PTR,
 *      UART_PDD_ISO7816_WAIT_TIMER_FLAG);
 *      @endcode
 */
#define UART_PDD_ClearIso7816InterruptFlags(PeripheralBase, Mask) ( \
    UART_IS7816_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816InterruptStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 interrupt status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_IS7816,
 *          UART1_IS7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_Read7816InterruptStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816InterruptStatusReg(PeripheralBase) ( \
    UART_IS7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816InterruptStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 interrupt
 * status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 interrupt status register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IS7816,
 *          UART1_IS7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816InterruptStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816InterruptStatusReg(PeripheralBase, Value) ( \
    UART_IS7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816WaitTimerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the ISO7816 wait timer interrupt value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value ISO7816 wait timer interrupt value[0..255]. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WP7816T0,
 *          UART1_WP7816T0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816WaitTimerValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetIso7816WaitTimerValue(PeripheralBase, Value) ( \
    UART_WP7816T0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816WaitTimerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 wait timer interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_WP7816T0,
 *          UART1_WP7816T0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_Read7816WaitTimerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816WaitTimerReg(PeripheralBase) ( \
    UART_WP7816T0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816WaitTimerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 wait timer
 * interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 wait timer interrupt register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WP7816T0,
 *          UART1_WP7816T0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816WaitTimerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816WaitTimerReg(PeripheralBase, Value) ( \
    UART_WP7816T0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816CharacterWaitTimerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the ISO7816 character wait time integer value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value ISO7816 character wait time integer value[0..15]. This parameter
 *        is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WP7816T1,
 *          UART1_WP7816T1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816CharacterWaitTimerValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetIso7816CharacterWaitTimerValue(PeripheralBase, Value) ( \
    UART_WP7816T1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART_WP7816T1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)UART_WP7816T1_CWI_MASK)))) | ( \
      (uint8_t)((uint8_t)(Value) << UART_WP7816T1_CWI_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816BlockWaitTimerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the ISO7816 block wait time integer value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value ISO7816 block wait time integer value[0..15]. This parameter is
 *        a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WP7816T1,
 *          UART1_WP7816T1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816BlockWaitTimerValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetIso7816BlockWaitTimerValue(PeripheralBase, Value) ( \
    UART_WP7816T1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART_WP7816T1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)UART_WP7816T1_BWI_MASK)))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816WaitParameterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 wait parameter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_WP7816T1,
 *          UART1_WP7816T1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_Read7816WaitParameterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816WaitParameterReg(PeripheralBase) ( \
    UART_WP7816T1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816WaitParameterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 wait parameter
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 wait parameter register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WP7816T1,
 *          UART1_WP7816T1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816WaitParameterReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816WaitParameterReg(PeripheralBase, Value) ( \
    UART_WP7816T1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816WaitNReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 wait N register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_WN7816,
 *          UART1_WN7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_Read7816WaitNReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816WaitNReg(PeripheralBase) ( \
    UART_WN7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816WaitNReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 wait N register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 wait N register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WN7816,
 *          UART1_WN7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816WaitNReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816WaitNReg(PeripheralBase, Value) ( \
    UART_WN7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816WaitFdReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 wait FD register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_WF7816,
 *          UART1_WF7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_Read7816WaitFdReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816WaitFdReg(PeripheralBase) ( \
    UART_WF7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816WaitFdReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 wait FD
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 wait FD register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WF7816,
 *          UART1_WF7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816WaitFdReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816WaitFdReg(PeripheralBase, Value) ( \
    UART_WF7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816TransmitNackThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the ISO7816 transmit NAC threshold value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value ISO7816 transmit NACK threshold value[0..15]. This parameter is
 *        a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_ET7816,
 *          UART1_ET7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816TransmitNackThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetIso7816TransmitNackThreshold(PeripheralBase, Value) ( \
    UART_ET7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART_ET7816_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)UART_ET7816_TXTHRESHOLD_MASK)))) | ( \
      (uint8_t)((uint8_t)(Value) << UART_ET7816_TXTHRESHOLD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816ReceiveNackThreshold
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the ISO7816 receive NAC threshold value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value ISO7816 receive NACK threshold value[0..15]. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_ET7816,
 *          UART1_ET7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816ReceiveNackThreshold(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetIso7816ReceiveNackThreshold(PeripheralBase, Value) ( \
    UART_ET7816_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       UART_ET7816_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)UART_ET7816_RXTHRESHOLD_MASK)))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816ErrorThresholdReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 error threshold register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_ET7816,
 *          UART1_ET7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_Read7816ErrorThresholdReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816ErrorThresholdReg(PeripheralBase) ( \
    UART_ET7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816ErrorThresholdReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 error threshold
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the 7816 error threshold register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_ET7816,
 *          UART1_ET7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816ErrorThresholdReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816ErrorThresholdReg(PeripheralBase, Value) ( \
    UART_ET7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetIso7816TransmitLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the ISO7816 transmit length value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value ISO7816 transmit length value[0..15]. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_TL7816,
 *          UART1_TL7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetIso7816TransmitLength(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetIso7816TransmitLength(PeripheralBase, Value) ( \
    UART_TL7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- Read7816TransmitLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads 7816 transmit length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_TL7816,
 *          UART1_TL7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_Read7816TransmitLengthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_Read7816TransmitLengthReg(PeripheralBase) ( \
    UART_TL7816_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Write7816TransmitLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into 7816 transmit length
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit error length register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_TL7816,
 *          UART1_TL7816 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_Write7816TransmitLengthReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_Write7816TransmitLengthReg(PeripheralBase, Value) ( \
    UART_TL7816_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCea7091bMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the CEA709.1-B feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter clear-to-send operation. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      UART_PDD_EnableCea7091bMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableCea7091bMode(PeripheralBase, State) ( \
    UART_C6_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C6_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C6_EN709_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C6_EN709_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SendCea7091bPacket
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts CEA709.1-B transmission.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      UART_PDD_SendCea7091bPacket(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_SendCea7091bPacket(PeripheralBase) ( \
    UART_C6_REG(PeripheralBase) |= \
     UART_C6_TX709_MASK \
  )

/* ----------------------------------------------------------------------------
   -- IsCea7091bTransmittingPacket
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns if transmission CEA709.1-B packet is active.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_IsCea7091bTransmittingPacket(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_IsCea7091bTransmittingPacket(PeripheralBase) ( \
    (uint8_t)(UART_C6_REG(PeripheralBase) & UART_C6_TX709_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCea7091bCollision
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the collision detect functionality.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of collision detect functionality. This
 *        parameter is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      UART_PDD_EnableCea7091bCollision(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableCea7091bCollision(PeripheralBase, State) ( \
    UART_C6_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C6_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C6_CE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C6_CE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCea7091bCollisionSignalPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the collision polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Collision polarity. This parameter is of "Collision polarity
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      UART_PDD_SetCea7091bCollisionSignalPolarity(<peripheral>_BASE_PTR,
 *      UART_PDD_CEA7091b_COLLISION_SIGNAL_LOW);
 *      @endcode
 */
#define UART_PDD_SetCea7091bCollisionSignalPolarity(PeripheralBase, Polarity) ( \
    UART_C6_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C6_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C6_CP_MASK))) | ( \
      (uint8_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadCea7091bControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bControlReg(PeripheralBase) ( \
    UART_C6_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B control register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C6.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bControlReg(PeripheralBase, Value) ( \
    UART_C6_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetCea7091bPacketCycleTimeCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets EA709.1-B packet cycle time counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value EA709.1-B packet cycle time counter value[0..65535]. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_PCTL, UART0_PCTH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetCea7091bPacketCycleTimeCounter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetCea7091bPacketCycleTimeCounter(PeripheralBase, Value) ( \
    (UART_PCTL_REG(PeripheralBase) = \
     (uint8_t)(Value)), \
    (UART_PCTH_REG(PeripheralBase) = \
     (uint8_t)((uint16_t)(Value) >> 8U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetCea7091bPacketCycleTimeCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns EA709.1-B packet cycle time counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: UART0_PCTH, UART0_PCTL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      UART_PDD_GetCea7091bPacketCycleTimeCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetCea7091bPacketCycleTimeCounter(PeripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)((uint16_t)UART_PCTH_REG(PeripheralBase) << 8U)) | ( \
     (uint16_t)UART_PCTL_REG(PeripheralBase))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bPacketCycleTimeCounterHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B packet cycle time counter high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_PCTH.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bPacketCycleTimeCounterHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bPacketCycleTimeCounterHighReg(PeripheralBase) ( \
    UART_PCTH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bPacketCycleTimeCounterHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B packet
 * cycle time counter high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B packet cycle time counter
 *        high register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_PCTH.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bPacketCycleTimeCounterHighReg(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bPacketCycleTimeCounterHighReg(PeripheralBase, Value) ( \
    UART_PCTH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bPacketCycleTimeCounterLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B packet cycle time counter low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_PCTL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bPacketCycleTimeCounterLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bPacketCycleTimeCounterLowReg(PeripheralBase) ( \
    UART_PCTL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bPacketCycleTimeCounterLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B packet
 * cycle time counter low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B packet cycle time counter
 *        low register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_PCTL.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bPacketCycleTimeCounterLowReg(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bPacketCycleTimeCounterLowReg(PeripheralBase, Value) ( \
    UART_PCTL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetCea7091bSecondaryDelayTimer
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets EA709.1-B secondary delay timer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value EA709.1-B secondary delay timer value[0..65535]. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_SDTL, UART0_SDTH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetCea7091bSecondaryDelayTimer(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_SetCea7091bSecondaryDelayTimer(PeripheralBase, Value) ( \
    (UART_SDTL_REG(PeripheralBase) = \
     (uint8_t)(Value)), \
    (UART_SDTH_REG(PeripheralBase) = \
     (uint8_t)((uint16_t)(Value) >> 8U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetCea7091bSecondaryDelayTimer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns EA709.1-B secondary delay timer value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: UART0_SDTH, UART0_SDTL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      UART_PDD_GetCea7091bSecondaryDelayTimer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetCea7091bSecondaryDelayTimer(PeripheralBase) ( \
    (uint16_t)(( \
     (uint16_t)((uint16_t)UART_SDTH_REG(PeripheralBase) << 8U)) | ( \
     (uint16_t)UART_SDTL_REG(PeripheralBase))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bSecondaryDelayTimerHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B secondary delay timer high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_SDTH.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bSecondaryDelayTimerHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bSecondaryDelayTimerHighReg(PeripheralBase) ( \
    UART_SDTH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bSecondaryDelayTimerHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B secondary
 * delay timer high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B secondary delay timer high
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_SDTH.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bSecondaryDelayTimerHighReg(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bSecondaryDelayTimerHighReg(PeripheralBase, Value) ( \
    UART_SDTH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bSecondaryDelayTimerLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B secondary delay timer low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_SDTL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bSecondaryDelayTimerLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bSecondaryDelayTimerLowReg(PeripheralBase) ( \
    UART_SDTL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bSecondaryDelayTimerLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B secondary
 * delay timer low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B secondary delay timer low
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_SDTL.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bSecondaryDelayTimerLowReg(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bSecondaryDelayTimerLowReg(PeripheralBase, Value) ( \
    UART_SDTL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bPreambleReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B preamble register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_PRE.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bPreambleReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bPreambleReg(PeripheralBase) ( \
    UART_PRE_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bPreambleReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B preamble
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B preamble register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_PRE.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bPreambleReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bPreambleReg(PeripheralBase, Value) ( \
    UART_PRE_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bTxPacketLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B transmit packet length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_TPL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bTxPacketLengthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bTxPacketLengthReg(PeripheralBase) ( \
    UART_TPL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bTxPacketLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B transmit
 * packet length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B transmit packet length
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_TPL.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bTxPacketLengthReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bTxPacketLengthReg(PeripheralBase, Value) ( \
    UART_TPL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_IE.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bInterruptEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bInterruptEnableReg(PeripheralBase) ( \
    UART_IE_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B interrupt
 * enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B interrupt enable register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_IE.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bInterruptEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bInterruptEnableReg(PeripheralBase, Value) ( \
    UART_IE_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bWBaseReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B WBase register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_WB.
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadCea7091bWBaseReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bWBaseReg(PeripheralBase) ( \
    UART_WB_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bWBaseReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B WBase
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B WBase register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_WB.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bWBaseReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bWBaseReg(PeripheralBase, Value) ( \
    UART_WB_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bStatusReg0
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the CEA709.1-B status register 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "CEA709.1-B interrupt masks constant" for
 *         processing return value.
 * @remarks The macro accesses the following registers: UART0_S3.
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadCea7091bStatusReg0(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bStatusReg0(PeripheralBase) ( \
    UART_S3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearCea7091bInterruptFlags0
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears CEA709.1-B interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "CEA709.1-B interrupt masks constant". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S3.
 * @par Example:
 *      @code
 *      UART_PDD_ClearCea7091bInterruptFlags0(<peripheral>_BASE_PTR,
 *      UART_PDD_CEA7091B_PREAMBLE_ERROR_FLAG);
 *      @endcode
 */
#define UART_PDD_ClearCea7091bInterruptFlags0(PeripheralBase, Mask) ( \
    UART_S3_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bStatusReg0
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B status
 * register 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B status register 0. This
 *        parameter is a 8-bit value.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S3.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_WriteCea7091bStatusReg0(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bStatusReg0(PeripheralBase, Value) ( \
    UART_S3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bStatusReg1
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the CEA709.1-B status register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "CEA709.1-B interrupt masks constant" for
 *         processing return value.
 * @remarks The macro accesses the following registers: UART0_S4.
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ReadCea7091bStatusReg1(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bStatusReg1(PeripheralBase) ( \
    UART_S4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearCea7091bInterruptFlags1
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears CEA709.1-B interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "CEA709.1-B interrupt masks constant". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S4.
 * @par Example:
 *      @code
 *      UART_PDD_ClearCea7091bInterruptFlags1(<peripheral>_BASE_PTR,
 *      UART_PDD_CEA7091B_COLLISION_DETECTED_FLAG);
 *      @endcode
 */
#define UART_PDD_ClearCea7091bInterruptFlags1(PeripheralBase, Mask) ( \
    UART_S4_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetCea7091bCollisionStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the CEA709.1-B collision status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "CEA709.1-B collision status constants." type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: UART0_S4.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_GetCea7091bCollisionStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_GetCea7091bCollisionStatus(PeripheralBase) ( \
    (uint8_t)(UART_S4_REG(PeripheralBase) & UART_S4_CDET_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bStatusReg1
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B status
 * register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B status register 1. This
 *        parameter is a 8-bit value.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S4.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_WriteCea7091bStatusReg1(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bStatusReg1(PeripheralBase, Value) ( \
    UART_S4_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bRxPacketLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B received packet length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_RPL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bRxPacketLengthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bRxPacketLengthReg(PeripheralBase) ( \
    UART_RPL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bRxPreambleLengthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B received preamble length register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_RPREL.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bRxPreambleLengthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bRxPreambleLengthReg(PeripheralBase) ( \
    UART_RPREL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCea7091bCollisionPulseWidthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CEA709.1-B collision pulse width register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_CPW.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      UART_PDD_ReadCea7091bCollisionPulseWidthReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define UART_PDD_ReadCea7091bCollisionPulseWidthReg(PeripheralBase) ( \
    UART_CPW_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCea7091bCollisionPulseWidthReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into CEA709.1-B collision
 * pulse width register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CEA709.1-B collision pulse width
 *        register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_CPW.
 * @par Example:
 *      @code
 *      UART_PDD_WriteCea7091bCollisionPulseWidthReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteCea7091bCollisionPulseWidthReg(PeripheralBase, Value) ( \
    UART_CPW_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetStopBitLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the number of stop bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length Stop bit length. This parameter is of "Stop bit lengths" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_BDH, UART1_BDH,
 *          UART2_BDH, UART3_BDH, UART4_BDH, UART5_BDH (depending on the
 *          peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_SetStopBitLength(<peripheral>_BASE_PTR,
 *      UART_PDD_STOP_BIT_LEN_1);
 *      @endcode
 */
#define UART_PDD_SetStopBitLength(PeripheralBase, Length) ( \
    UART_BDH_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_BDH_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_BDH_SBNS_MASK))) | ( \
      (uint8_t)(Length))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLinBreakDetectDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a LIN break detect DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of LIN break detect DMA request. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_C5, UART1_C5,
 *          UART2_C5, UART3_C5, UART4_C5, UART5_C5 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_EnableLinBreakDetectDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define UART_PDD_EnableLinBreakDetectDma(PeripheralBase, State) ( \
    UART_C5_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(UART_C5_REG(PeripheralBase) & (uint8_t)(~(uint8_t)UART_C5_LBKDDMAS_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << UART_C5_LBKDDMAS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the interrupt status flags specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of the flags to be cleared. This parameter is a 8-bit value.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = UART_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    UART_S1_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatus1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into status 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the status 1 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: UART0_S1, UART1_S1,
 *          UART2_S1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      UART_PDD_WriteStatus1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define UART_PDD_WriteStatus1Reg(PeripheralBase, Value) ( \
    UART_S1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )
#endif  /* #if defined(UART_PDD_H_) */

/* UART_PDD.h, eof. */
