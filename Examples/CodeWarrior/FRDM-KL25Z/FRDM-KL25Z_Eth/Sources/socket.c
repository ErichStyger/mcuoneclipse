/**
 * \file
 * \brief Implementation of sockets for W5100
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * Credits to:
 * - http://www.ermicro.com/blog/?p=1773
 * - http://www.seanet.com/~karllunt/w5100_library.html
 *
 * This module implements sockets for W5100.
 */

#include "socket.h"
#include "w5100.h"
#include "WAIT1.h"

uint8_t SOCK_CloseSocket(uint8_t sock) {
  uint8_t val;
  uint16_t sockaddr;
  
  if (sock>=W5100_NUM_SOCKETS) {
    return ERR_VALUE;
  }
  sockaddr = W5100_SKT_BASE(sock);
  /* Send Close Command */
  W5100_MemWriteByte(sockaddr+W5100_CR_OFFSET, W5100_CR_CLOSE);
  do { /* Waiting until the S0_CR is clear */
    W5100_MemReadByte(sockaddr+W5100_CR_OFFSET, &val);
  } while(val!=0);
  return ERR_OK;
}

uint8_t SOCK_Disconnect(uint8_t sock) {
  uint8_t val;
  uint16_t sockaddr;

  if (sock>=W5100_NUM_SOCKETS) {
    return ERR_VALUE;
  }
  sockaddr = W5100_SKT_BASE(sock);
  /* Send Disconnect Command */
  W5100_MemWriteByte(sockaddr+W5100_CR_OFFSET, W5100_CR_DISCON);
  do { /* Wait for Disconnecting Process */
    W5100_MemReadByte(sockaddr+W5100_CR_OFFSET, &val);
  } while(val!=0);
  return ERR_OK;
}

uint8_t SOCK_OpenSocket(uint8_t sock, uint8_t eth_protocol, uint16_t tcp_port) {
  uint8_t val;
  uint16_t sockaddr;

  if (sock>=W5100_NUM_SOCKETS) {
    return ERR_VALUE; /* out of range */
  }
  sockaddr =  W5100_SKT_BASE(sock);
  /* Make sure we close the socket first */
  if (W5100_MemReadByte(sockaddr+W5100_SR_OFFSET, &val)!=ERR_OK) {
    return ERR_FAILED; /* failure */
  }
  if (val==W5100_SOCK_CLOSED) {
    /* make sure we close the socket */
    SOCK_CloseSocket(sock);
  }
  /* Assigned Socket 0 Mode Register */
  W5100_MemWriteByte(sockaddr+W5100_MR_OFFSET, eth_protocol);
  /* Now open the Socket 0 */
  W5100_MemWriteWord(sockaddr+W5100_PORT_OFFSET, tcp_port);
  W5100_MemWriteByte(sockaddr+W5100_CR_OFFSET, W5100_CR_OPEN);  /* Open Socket */
  /* Wait for Opening Process */
  do {
    W5100_MemReadByte(sockaddr+W5100_CR_OFFSET, &val);
  } while(val!=0);
  /* Check for Init Status */
  W5100_MemReadByte(sockaddr+W5100_SR_OFFSET, &val);
  if (val==W5100_SOCK_INIT) {
    return ERR_OK;
  } else {
    SOCK_CloseSocket(sock);
  }
  return ERR_FAILED;
}

uint8_t SOCK_Listen(uint8_t sock) {
  uint8_t val;
  uint16_t sockaddr;
  
  if (sock>=W5100_NUM_SOCKETS) {
    return ERR_VALUE;
  }
  sockaddr = W5100_SKT_BASE(sock);
  W5100_MemReadByte(sockaddr+W5100_SR_OFFSET, &val);
  if (val==W5100_SOCK_INIT) {
    /* Send the LISTEN Command */
    W5100_MemWriteByte(sockaddr+W5100_CR_OFFSET, W5100_CR_LISTEN);
    /* Wait for Listening Process */
    do {
      W5100_MemReadByte(sockaddr+W5100_CR_OFFSET, &val);
    } while(val!=0);
    /* Check for Listen Status */
    W5100_MemReadByte(sockaddr+W5100_SR_OFFSET, &val);
    if (val==W5100_SOCK_LISTEN) {
      return ERR_OK;
    } else {
      SOCK_CloseSocket(sock);
    }
  }
  return ERR_FAILED;
}

uint8_t SOCK_Send(uint8_t sock, const uint8_t *buf, size_t buflen) {
  uint16_t offaddr, realaddr, txsize, timeout, sockaddr;
  uint8_t val;

  if (buflen<=0 || sock>=W5100_NUM_SOCKETS) {
    return ERR_VALUE;
  }
  sockaddr = W5100_SKT_BASE(sock);
  /* Make sure the TX Free Size Register is available */
  W5100_MemReadWord(sockaddr+W5100_TX_FSR_OFFSET, &txsize);
  timeout=0;
  while (txsize<buflen) {
    WAIT1_WaitOSms(1);
    W5100_MemReadWord(sockaddr+W5100_TX_FSR_OFFSET, &txsize);
   /* Timeout for approximately 1000 ms */
   if (timeout++ > 1000) {
     /* Disconnect the connection */
     SOCK_Disconnect(sock);
     return ERR_FAILED;
    }
  }  
  /* Read the Tx Write Pointer */
  W5100_MemReadWord(sockaddr+W5100_TX_WR_OFFSET, &offaddr);
  while(buflen) {
    buflen--;
    /* Calculate the real W5100 physical Tx Buffer Address */
    realaddr = (W5100_TXBUFADDR+(0x0800*sock)) + (offaddr&W5100_TX_BUF_MASK);
    /* Copy the application data to the W5100 Tx Buffer */
    W5100_MemWriteByte(realaddr, *buf);
    offaddr++;
    buf++;
  }
  /* Increase the S0_TX_WR value, so it point to the next transmit */
  W5100_MemWriteWord(sockaddr+W5100_TX_WR_OFFSET, offaddr);
  /* Now Send the SEND command */
  W5100_MemWriteByte(sockaddr+W5100_CR_OFFSET, W5100_CR_SEND);
  /* Wait for Sending Process */
  do {
    W5100_MemReadByte(sockaddr+W5100_CR_OFFSET, &val);
  } while(val!=0);
  return ERR_OK;
}

uint8_t SOCK_Receive(uint8_t sock, uint8_t *buf, size_t bufSize, size_t readSize) {
  uint16_t offaddr, realaddr;
  uint16_t sockaddr;

  if (readSize<=0 || sock>=W5100_NUM_SOCKETS) {
    return ERR_VALUE; /* failure */
  }
  if (readSize>bufSize) { /* If the requested size > MAX_BUF, just truncate it */
    readSize = bufSize-2;
  }
  sockaddr = W5100_SKT_BASE(sock);
  /* Read the Rx Read Pointer */
  W5100_MemReadWord(sockaddr+W5100_RX_RD_OFFSET, &offaddr);
  while (readSize) {
    readSize--;
    realaddr = (W5100_RXBUFADDR + (0x0800*sock))+(offaddr&W5100_RX_BUF_MASK);
    W5100_MemReadByte(realaddr, buf);
    offaddr++;
    buf++;
  }
  *buf='\0';  /* string terminated character */
  /* Increase the S0_RX_RD value, so it point to the next receive */
  W5100_MemWriteWord(sockaddr+W5100_RX_RD_OFFSET, offaddr);
  /* Now Send the RECV command */
  W5100_MemWriteByte(sockaddr+W5100_CR_OFFSET, W5100_CR_RECV);
  WAIT1_Waitus(5);    /* Wait for Receive Process */
  return ERR_OK;
}

uint8_t SOCK_ReceivedSize(uint8_t sock, uint16_t *rxSize) {
  uint16_t sockaddr;
  
  *rxSize = 0;
  if (sock>=W5100_NUM_SOCKETS)  {
    return ERR_VALUE;
  }
  sockaddr = W5100_SKT_BASE(sock); // calc base addr for this socket
  return W5100_MemReadWord(sockaddr+W5100_RX_RSR_OFFSET, rxSize);
}

uint8_t SOCK_GetStatus(uint8_t sock, uint8_t *status) {
  uint16_t sockaddr;
  
  if (sock>=W5100_NUM_SOCKETS)  {
    return ERR_VALUE;
  }
  sockaddr = W5100_SKT_BASE(sock);
  return W5100_MemReadByte(sockaddr+W5100_SR_OFFSET, status);
}

void SOCK_Deinit(void){
  /* nothing needed */
}

void SOCK_Init(void) {
  /* nothing needed */
}
