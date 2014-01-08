/**
 * \file
 * \brief Implementation of sockets for W5100
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * This module is based on the fantastic work and blog of rwb:
 * (http://www.ermicro.com/blog/?p=1773).
 *
 * This module implements sockets for W5100.
 */

#include "socket.h"
#include "w5100.h"
#include "WAIT1.h"

#define _DEBUG_MODE  0

void SOCK_Close(uint8_t sock) {
  uint8_t val;
  
  if (sock!=0) {
    return;
  }
  /* Send Close Command */
  W5100_MemWriteByte(W5100_S0_CR, W5100_CR_CLOSE);
  do { /* Waiting until the S0_CR is clear */
    W5100_MemReadByte(W5100_S0_CR, &val);
  } while(val!=0);
}

void SOCK_Disconnect(uint8_t sock) {
  uint8_t val;

  if (sock!=0) {
    return;
  }
  /* Send Disconnect Command */
  W5100_MemWriteByte(W5100_S0_CR, W5100_CR_DISCON);
  do { /* Wait for Disconnecting Process */
    W5100_MemReadByte(W5100_S0_CR, &val);
  } while(val!=0);
}

uint8_t SOCK_Socket(uint8_t sock, uint8_t eth_protocol, uint16_t tcp_port) {
  uint8_t val, retval = 0;

  if (sock!=0) {
    return retval;
  }
  /* Make sure we close the socket first */
  if (W5100_MemReadByte(W5100_S0_SR, &val)!=ERR_OK) {
    return 0; /* failure */
  }
  if (val==W5100_SOCK_CLOSED) {
    SOCK_Close(sock);
  }
  /* Assigned Socket 0 Mode Register */
  W5100_MemWriteByte(W5100_S0_MR, eth_protocol);
  /* Now open the Socket 0 */
  W5100_MemWriteWord(W5100_S0_PORT, tcp_port);
  W5100_MemWriteByte(W5100_S0_CR, W5100_CR_OPEN);  /* Open Socket */
  /* Wait for Opening Process */
  do {
    W5100_MemReadByte(W5100_S0_CR, &val);
  } while(val!=0);
  /* Check for Init Status */
  W5100_MemReadByte(W5100_S0_SR, &val);
  if (val==W5100_SOCK_INIT) {
    retval = 1;
  } else {
    SOCK_Close(sock);
  }
  return retval;
}

uint8_t SOCK_Listen(uint8_t sock) {
  uint8_t val, retval = 0;
  
  if (sock!=0) {
    return retval;
  }
  W5100_MemReadByte(W5100_S0_SR, &val);
  if (val==W5100_SOCK_INIT) {
    /* Send the LISTEN Command */
    W5100_MemWriteByte(W5100_S0_CR, W5100_CR_LISTEN);
    /* Wait for Listening Process */
    do {
      W5100_MemReadByte(W5100_S0_CR, &val);
    } while(val!=0);
    /* Check for Listen Status */
    W5100_MemReadByte(W5100_S0_SR, &val);
    if (val==W5100_SOCK_LISTEN) {
      retval = 1;
    } else {
      SOCK_Close(sock);
    }
  }
  return retval;
}

uint16_t SOCK_Send(uint8_t sock, const uint8_t *buf, uint16_t buflen) {
  uint16_t offaddr, realaddr, txsize, timeout;
  uint8_t val;

  if (buflen<=0 || sock!=0) {
    return 0;
  }
#if _DEBUG_MODE
  printf("Send Size: %d\n",buflen);
#endif
  /* Make sure the TX Free Size Register is available */
  W5100_MemReadWord(W5100_SO_TX_FSR, &txsize);
#if _DEBUG_MODE
  printf("TX Free Size: %d\n",txsize);
#endif
  timeout=0;
  while (txsize<buflen) {
    WAIT1_WaitOSms(1);
    
    W5100_MemReadWord(W5100_SO_TX_FSR, &txsize);
   /* Timeout for approximately 1000 ms */
   if (timeout++ > 1000) {
#if _DEBUG_MODE
     printf("TX Free Size Error!\n");
#endif
     /* Disconnect the connection */
     SOCK_Disconnect(sock);
     return 0;
   }
 }  
 /* Read the Tx Write Pointer */
 W5100_MemReadWord(W5100_S0_TX_WR, &offaddr);
#if _DEBUG_MODE
  printf("TX Buffer: %x\n", offaddr);
#endif  
  while(buflen) {
    buflen--;
    /* Calculate the real W5100 physical Tx Buffer Address */
    realaddr = W5100_TXBUFADDR+(offaddr&W5100_TX_BUF_MASK);
    /* Copy the application data to the W5100 Tx Buffer */
    W5100_MemWriteByte(realaddr, *buf);
    offaddr++;
    buf++;
  }
  /* Increase the S0_TX_WR value, so it point to the next transmit */
  W5100_MemWriteWord(W5100_S0_TX_WR, offaddr);
  /* Now Send the SEND command */
  W5100_MemWriteByte(W5100_S0_CR, W5100_CR_SEND);
  /* Wait for Sending Process */
  do {
    W5100_MemReadByte(W5100_S0_CR, &val);
  } while(val!=0);
  return 1;
}

#define W5100_MAX_BUF 512
//static uint8_t buf[W5100_MAX_BUF];

uint16_t SOCK_Recv(uint8_t sock, uint8_t *buf, uint16_t buflen) {
  uint16_t offaddr, realaddr;    

  if (buflen<=0 || sock!=0) {
    return 1;   
  }
  /* If the request size > MAX_BUF,just truncate it */
  if (buflen>W5100_MAX_BUF) {
    buflen = W5100_MAX_BUF-2;
  }
  /* Read the Rx Read Pointer */
  W5100_MemReadWord(W5100_S0_RX_RD, &offaddr);
#if _DEBUG_MODE
  printf("RX Buffer: %x\n",offaddr);
#endif  
  while (buflen) {
    buflen--;
    realaddr = W5100_RXBUFADDR+(offaddr&W5100_RX_BUF_MASK);
    W5100_MemWriteByte(realaddr, *buf);
    offaddr++;
    buf++;
  }
  *buf='\0';  /* String terminated character */
  /* Increase the S0_RX_RD value, so it point to the next receive */
  W5100_MemWriteWord(W5100_S0_RX_RD, offaddr);
  /* Now Send the RECV command */
  W5100_MemWriteByte(W5100_S0_CR, W5100_CR_RECV);
  WAIT1_Waitus(5);    // Wait for Receive Process
  return 1;
}


uint16_t SOCK_Recv_size(void) {
  uint16_t val;
  
  W5100_MemReadWord(W5100_S0_RX_RSR, &val);
  return val;
}

int strindex(char *s, char *t) {
  uint16_t i,n;

  n=UTIL1_strlen(t);
  for(i=0;*(s+i); i++) {
    if (UTIL1_strncmp(s+i,t,n) == 0)
      return i;
  }
  return -1;
}

void SOCK_Init(void) { 
}
