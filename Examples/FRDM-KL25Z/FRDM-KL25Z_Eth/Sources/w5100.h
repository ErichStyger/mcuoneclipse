/*
 * w5100.h
 *
 *  Created on: Jan 3, 2014
 *      Author: tastyger
 */
#ifndef __W5100_H_
#define __W5100_H_

#include "PE_Types.h"
#include "CLS1.h"

/* SPI COMMANDS */
#define W5100_CMD_READ 0x0F
#define W5100_CMD_WRITE 0xF0

/* MEMORY MAP */
#define W5100_COMMON_REG 0x00
#define W5100_SOCKET_REG 0x04
#define W5100_TX_MEMORY 0x40
#define W5100_RX_MEMORY 0x60

/* COMMON REGISTERS */
#define W5100_MR    0x00 /* MR (Mode Register */
#define W5100_MR_BIT_IND    (1<<0) /* indirect bus interface mode */
#define W5100_MR_BIT_AI     (1<<1) /* address auto-increment in indirect bus interface, 1 to enable */
#define W5100_MR_BIT_PPPoE  (1<<3) /* PPPoE mode, 1 to enable */
#define W5100_MR_BIT_PB     (1<<4) /* ping block bit, 1 to block pings */
#define W5100_MR_BIT_RST    (1<<7) /* reset bit, 1 to reset internal registers */

#define W5100_GAR0 0x01 /* gateway IP address */
#define W5100_GAR1 0x02
#define W5100_GAR2 0x03
#define W5100_GAR3 0x04
#define W5100_SUBR0 0x05 /* subnet mask register */
#define W5100_SUBR1 0x06
#define W5100_SUBR2 0x07
#define W5100_SUBR3 0x08
#define W5100_SHAR0 0x09 /* source hardware address register */ 
#define W5100_SHAR1 0x0A
#define W5100_SHAR2 0x0B
#define W5100_SHAR3 0x0C
#define W5100_SHAR4 0x0D
#define W5100_SHAR5 0x0E
#define W5100_SIPR0 0x0F /* source IP address register */
#define W5100_SIPR1 0x10
#define W5100_SIPR2 0x11
#define W5100_SIPR3 0x12
#define W5100_IR 0x15  /* interrupt register */
#define W5100_IR_BIT_S0_INT       (1<<0) /* occurrence of socket 0 interrupt */
#define W5100_IR_BIT_S1_INT       (1<<1) /* occurrence of socket 0 interrupt */
#define W5100_IR_BIT_S2_INT       (1<<2) /* occurrence of socket 0 interrupt */
#define W5100_IR_BIT_S3_INT       (1<<3) /* occurrence of socket 0 interrupt */
#define W5100_IR_BIT_PPPoE_CLOSE  (1<<5) /* PPPoE Connection close */
#define W5100_IR_BIT_UNREACH      (1<<6) /* Destination unreachable */
#define W5100_IR_BIT_CONFLICT     (1<<7) /* IP conflict */

#define W5100_IMR 0x16 /* interrupt mask register */
#define W5100_RTR0 0x17 /* retry time-value register */
#define W5100_RTR1 0x18
#define W5100_RCR 0x19 /* retry count register */
#define W5100_RMSR 0x1A /* RX memory size register */
#define W5100_TMSR 0x1B /* TX memory size register */
#define W5100_xMSR_SOCKET_MEM_SIZE_1KB  0
#define W5100_xMSR_SOCKET_MEM_SIZE_2KB  1
#define W5100_xMSR_SOCKET_MEM_SIZE_4KB  2
#define W5100_xMSR_SOCKET_MEM_SIZE_8KB  3
#define W5100_xMSR_SOCKET_1_MEM_SIZE_1KB  (W5100_xMSR_SOCKET_MEM_SIZE_1KB<<0)
#define W5100_xMSR_SOCKET_1_MEM_SIZE_2KB  (W5100_xMSR_SOCKET_MEM_SIZE_2KB<<0)
#define W5100_xMSR_SOCKET_1_MEM_SIZE_4KB  (W5100_xMSR_SOCKET_MEM_SIZE_4KB<<0)
#define W5100_xMSR_SOCKET_1_MEM_SIZE_8KB  (W5100_xMSR_SOCKET_MEM_SIZE_8KB<<0)
#define W5100_xMSR_SOCKET_2_MEM_SIZE_1KB  (W5100_xMSR_SOCKET_MEM_SIZE_1KB<<2)
#define W5100_xMSR_SOCKET_2_MEM_SIZE_2KB  (W5100_xMSR_SOCKET_MEM_SIZE_2KB<<2)
#define W5100_xMSR_SOCKET_2_MEM_SIZE_4KB  (W5100_xMSR_SOCKET_MEM_SIZE_4KB<<2)
#define W5100_xMSR_SOCKET_2_MEM_SIZE_8KB  (W5100_xMSR_SOCKET_MEM_SIZE_8KB<<2)
#define W5100_xMSR_SOCKET_3_MEM_SIZE_1KB  (W5100_xMSR_SOCKET_MEM_SIZE_1KB<<4)
#define W5100_xMSR_SOCKET_3_MEM_SIZE_2KB  (W5100_xMSR_SOCKET_MEM_SIZE_2KB<<4)
#define W5100_xMSR_SOCKET_3_MEM_SIZE_4KB  (W5100_xMSR_SOCKET_MEM_SIZE_4KB<<4)
#define W5100_xMSR_SOCKET_3_MEM_SIZE_8KB  (W5100_xMSR_SOCKET_MEM_SIZE_8KB<<4)
#define W5100_xMSR_SOCKET_4_MEM_SIZE_1KB  (W5100_xMSR_SOCKET_MEM_SIZE_1KB<<6)
#define W5100_xMSR_SOCKET_4_MEM_SIZE_2KB  (W5100_xMSR_SOCKET_MEM_SIZE_2KB<<6)
#define W5100_xMSR_SOCKET_4_MEM_SIZE_4KB  (W5100_xMSR_SOCKET_MEM_SIZE_4KB<<6)
#define W5100_xMSR_SOCKET_4_MEM_SIZE_8KB  (W5100_xMSR_SOCKET_MEM_SIZE_8KB<<6)

#define W5100_PATR0 0x1C /* Authentication type in PPPoE mode */
#define W5100_PATR1 0x1D
#define W5100_PTIMER 0x28 /* PPP Link Control Protocol Request Timer */
#define W5100_PMAGIC 0x29 /* PPP Link Control Magic number */
#define W5100_UIPR0 0x2A  /* Unreachable IP Address Register */
#define W5100_UIPR1 0x2B
#define W5100_UIPR2 0x2C
#define W5100_UIPR3 0x2D
#define W5100_UPORT0 0x2E /* Unreachable Port Register */
#define W5100_UPORT1 0x2F

/* SOCKET REGISTERS */
#define W5100_Sn_MR 0x00
#define W5100_Sn_CR 0x01
#define W5100_Sn_IR 0x02
#define W5100_Sn_SR 0x03
#define W5100_Sn_PORT0 0x04
#define W5100_Sn_PORT1 0x05
#define W5100_Sn_DHAR0 0x06
#define W5100_Sn_DHAR1 0x07
#define W5100_Sn_DHAR2 0x08
#define W5100_Sn_DHAR3 0x09
#define W5100_Sn_DHAR4 0x0A
#define W5100_Sn_DHAR5 0x0B
#define W5100_Sn_DIPR0 0x0C
#define W5100_Sn_DIPR1 0x0D
#define W5100_Sn_DIPR2 0x0E
#define W5100_Sn_DIPR3 0x0F
#define W5100_Sn_DPORT0 0x10
#define W5100_Sn_DPORT1 0x11
#define W5100_Sn_MSSR0 0x12
#define W5100_Sn_MSSR1 0x13
#define W5100_Sn_PROTO 0x14
#define W5100_Sn_TOS 0x15
#define W5100_Sn_TTL 0x16
#define W5100_Sn_TX_FSR0 0x20
#define W5100_Sn_TX_FSR1 0x21
#define W5100_Sn_TX_RD0 0x22
#define W5100_Sn_TX_RD1 0x23
#define W5100_Sn_TX_WR0 0x24
#define W5100_Sn_TX_WR1 0x25
#define W5100_Sn_RX_RSR0 0x26
#define W5100_Sn_RX_RSR1 0x27
#define W5100_Sn_RX_RD0 0x28
#define W5100_Sn_RX_RD1 0x29

/* SOCKET COMMANDS */
#define W5100_OPEN 0x01
#define W5100_LISTEN 0x02
#define W5100_CONNECT 0x04
#define W5100_DISCON 0x08
#define W5100_CLOSE 0x10
#define W5100_SEND 0x20
#define W5100_SEND_MAC 0x21
#define W5100_SEND_KEEP 0x22
#define W5100_RECV 0x40

/* SOCKET PROTOCOL */
#define W5100_CLOSED 0x00
#define W5100_TCP 0x01
#define W5100_UDP 0x02
#define W5100_IPRAW 0x03

/* INTERRUPT BITS */
#define W5100_IR_CONFLICT 7
#define W5100_IR_UNREACH 6
#define W5100_IR_S3_INT 3
#define W5100_IR_S2_INT 2
#define W5100_IR_S1_INT 1
#define W5100_IR_S0_INT 0

/* SOCK INT BITS */
#define W5100_Sn_IR_SEND_OK 4
#define W5100_Sn_IR_TIMEOUT 3
#define W5100_Sn_IR_RECV 2
#define W5100_Sn_IR_DISCON 1
#define W5100_Sn_IR_CON 0

/* STATUS */
#define W5100_SOCK_CLOSED 0x00
#define W5100_SOCK_LISTEN 0x14
#define W5100_SOCK_ESTABLISHED 0x17
#define W5100_SOCK_CLOSE_WAIT 0x1C
#define W5100_SOCK_UDP 0x22

/* SOCK_RW constants */
#define W5100_READ 0
#define W5100_WRITE 1
#define W5100_WRITE_P 2

typedef struct w5100_config {
  uint8_t gateway[4]; /* gateway address, e.g. 192.168.0.1 */
  uint8_t netmask[4]; /* network mask, e.g. 255.255.255.0 */
  uint8_t hwaddr[6]; /* hardware MAC address, e.g. 90:a2:da:0D:42:dd */
  uint8_t ipaddr[4]; /* own IP address, e.g. 192.168.0.90 */
} w5100_config_t;

void W5100_RequestSPIBus(void);

void W5100_ReleaseSPIBus(void);

void W5100_OnBlockReceived(LDD_TUserData *UserDataPtr);

uint8_t W5100_WriteConfig(w5100_config_t *config);
uint8_t W5100_ReadConfig(w5100_config_t *config);

uint8_t W5100_MemWriteByte(uint16_t addr, uint8_t val);
uint8_t W5100_MemReadByte(uint16_t addr, uint8_t *val);

uint8_t W5100_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io);

void W5100_Init(void);


#endif
