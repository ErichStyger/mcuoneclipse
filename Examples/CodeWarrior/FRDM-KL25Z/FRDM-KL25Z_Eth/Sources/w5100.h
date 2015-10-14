/**
 * \file
 * \brief This is the interface to the W5100.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * Credits to:
 * - http://www.ermicro.com/blog/?p=1773
 * - http://www.seanet.com/~karllunt/w5100_library.html
 *
 * This module provides an interface to the Wiztronic W5100 Ethernet chip.
 */

#ifndef __W5100_H_
#define __W5100_H_

#include "PE_Types.h"
#include "CLS1.h"

/* SPI COMMANDS */
#define W5100_CMD_READ 0x0F
#define W5100_CMD_WRITE 0xF0

/* COMMON REGISTERS */
#define W5100_MR      0x0000 /* MR (Mode Register */
  #define W5100_MR_BIT_IND    (1<<0) /* indirect bus interface mode */
  #define W5100_MR_BIT_AI     (1<<1) /* address auto-increment in indirect bus interface, 1 to enable */
  #define W5100_MR_BIT_PPPoE  (1<<3) /* PPPoE mode, 1 to enable */
  #define W5100_MR_BIT_PB     (1<<4) /* ping block bit, 1 to block pings */
  #define W5100_MR_BIT_RST    (1<<7) /* reset bit, 1 to reset internal registers */
#define W5100_GAR0    0x0001 /* gateway IP address */
#define W5100_GAR1    0x0002
#define W5100_GAR2    0x0003
#define W5100_GAR3    0x0004
#define W5100_SUBR0   0x0005 /* subnet mask register */
#define W5100_SUBR1   0x0006
#define W5100_SUBR2   0x0007
#define W5100_SUBR3   0x0008
#define W5100_SHAR0   0x0009 /* source hardware address register */ 
#define W5100_SHAR1   0x000A
#define W5100_SHAR2   0x000B
#define W5100_SHAR3   0x000C
#define W5100_SHAR4   0x000D
#define W5100_SHAR5   0x000E
#define W5100_SIPR0   0x000F /* source IP address register */
#define W5100_SIPR1   0x0010
#define W5100_SIPR2   0x0011
#define W5100_SIPR3   0x0012
#define W5100_IR      0x0015  /* interrupt register */
  #define W5100_IR_BIT_S0_INT       (1<<0) /* occurrence of socket 0 interrupt */
  #define W5100_IR_BIT_S1_INT       (1<<1) /* occurrence of socket 0 interrupt */
  #define W5100_IR_BIT_S2_INT       (1<<2) /* occurrence of socket 0 interrupt */
  #define W5100_IR_BIT_S3_INT       (1<<3) /* occurrence of socket 0 interrupt */
  #define W5100_IR_BIT_PPPoE_CLOSE  (1<<5) /* PPPoE Connection close */
  #define W5100_IR_BIT_UNREACH      (1<<6) /* Destination unreachable */
  #define W5100_IR_BIT_CONFLICT     (1<<7) /* IP conflict */
#define W5100_IMR     0x0016 /* interrupt mask register */
#define W5100_RTR0    0x0017 /* retry time-value register */
#define W5100_RTR1    0x0018
#define W5100_RCR     0x0019 /* retry count register */
#define W5100_RMSR    0x001A /* RX memory size register */
#define W5100_TMSR    0x001B /* TX memory size register */
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
#define W5100_PATR0   0x001C /* Authentication type in PPPoE mode */
#define W5100_PATR1   0x001D
#define W5100_PTIMER  0x0028 /* PPP Link Control Protocol Request Timer */
#define W5100_PMAGIC  0x0029 /* PPP Link Control Magic number */
#define W5100_UIPR0   0x002A  /* Unreachable IP Address Register */
#define W5100_UIPR1   0x002B
#define W5100_UIPR2   0x002C
#define W5100_UIPR3   0x002D
#define W5100_UPORT0  0x002E /* Unreachable Port Register */
#define W5100_UPORT1  0x002F

/* SOCKET REGISTERS */
#define W5100_S0_MR       0x0400  /* Socket 0: Mode Register Address */
#define W5100_S0_CR       0x0401  /* Socket 0: Command Register Address */
#define W5100_S0_IR       0x0402  /* Socket 0: Interrupt Register Address */
#define W5100_S0_SR       0x0403  /* Socket 0: Status Register Address */
#define W5100_S0_PORT     0x0404  /* Socket 0: Source Port: 0x0404 to 0x0405 */
#define W5100_SO_TX_FSR   0x0420  /* Socket 0: Tx Free Size Register: 0x0420 to 0x0421 */
#define W5100_S0_TX_RD    0x0422  /* Socket 0: Tx Read Pointer Register: 0x0422 to 0x0423 */
#define W5100_S0_TX_WR    0x0424  /* Socket 0: Tx Write Pointer Register: 0x0424 to 0x0425 */
#define W5100_S0_RX_RSR   0x0426  /* Socket 0: Rx Received Size Pointer Register: 0x0425 to 0x0427 */
#define W5100_S0_RX_RD    0x0428  /* Socket 0: Rx Read Pointer: 0x0428 to 0x0429 */

#define W5100_TXBUFADDR  0x4000   /* W5100 Send Buffer Base Address */
#define W5100_RXBUFADDR  0x6000   /* W5100 Read Buffer Base Address */

/* SOCKET COMMANDS */
#define W5100_CR_OPEN      0x01 /* Initialize or open socket */
#define W5100_CR_LISTEN    0x02 /* Wait connection request in tcp mode(Server mode) */
#define W5100_CR_CONNECT   0x04 /* Send connection request in tcp mode(Client mode) */
#define W5100_CR_DISCON    0x08 /* Send closing reqeuset in tcp mode */
#define W5100_CR_CLOSE     0x10 /* Close socket */
#define W5100_CR_SEND      0x20 /* Update Tx memory pointer and send data */
#define W5100_CR_SEND_MAC  0x21 /* Send data with MAC address, so without ARP process */
#define W5100_CR_SEND_KEEP 0x22 /* Send keep alive message */
#define W5100_CR_RECV      0x40 /* Update Rx memory buffer pointer and receive data */

/* SOCKET PROTOCOL */
#define W5100_CLOSED  0x00
#define W5100_TCP     0x01
#define W5100_UDP     0x02
#define W5100_IPRAW   0x03

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

/* S0_SR socket status values */
#define W5100_SOCK_CLOSED      0x00   /* Closed */
#define W5100_SOCK_INIT        0x13   /* Init state */
#define W5100_SOCK_LISTEN      0x14   /* Listen state */
#define W5100_SOCK_SYNSENT     0x15   /* Connection state */
#define W5100_SOCK_SYNRECV     0x16   /* Connection state */
#define W5100_SOCK_ESTABLISHED 0x17   /* Success to connect */
#define W5100_SOCK_FIN_WAIT    0x18   /* Closing state */
#define W5100_SOCK_CLOSING     0x1A   /* Closing state */
#define W5100_SOCK_TIME_WAIT   0x1B   /* Closing state */
#define W5100_SOCK_CLOSE_WAIT  0x1C   /* Closing state */
#define W5100_SOCK_LAST_ACK    0x1D   /* Closing state */
#define W5100_SOCK_UDP         0x22   /* UDP socket */
#define W5100_SOCK_IPRAW       0x32   /* IP raw mode socket */
#define W5100_SOCK_MACRAW      0x42   /* MAC raw mode socket */
#define W5100_SOCK_PPPOE       0x5F   /* PPPOE socket */

#define W5100_TX_BUF_MASK      0x07FF   /* Tx 2K Buffer Mask */
#define W5100_RX_BUF_MASK      0x07FF   /* Rx 2K Buffer Mask */
#define W5100_NET_MEMALLOC     0x05     /* Use 2K of Tx/Rx Buffer */

#define W5100_TCP_PORT         80       /* TCP/IP Port */

/* SOCK_RW constants */
#define W5100_READ    0
#define W5100_WRITE   1
#define W5100_WRITE_P 2

typedef struct w5100_config {
  uint8_t gateway[4]; /* gateway address, e.g. 192.168.0.1 */
  uint8_t netmask[4]; /* network mask, e.g. 255.255.255.0 */
  uint8_t hwaddr[6]; /* hardware MAC address, e.g. 90:a2:da:0D:42:dd */
  uint8_t ipaddr[4]; /* own IP address, e.g. 192.168.0.90 */
} w5100_config_t;

/*
 *  Use W5100_SKT_REG_BASE and W5100_SKT_OFFSET to calc the address of each set of socket registers.
 *  For example, the base address of the socket registers for socket 2 would be:
 *  (W5100_SKT_REG_BASE + (2 * W5100_SKT_OFFSET))
 */
#define  W5100_SKT_REG_BASE   0x0400    /* start of socket registers */
#define  W5100_SKT_OFFSET     0x0100    /* offset to each socket regester set */
#define  W5100_SKT_BASE(n)    (W5100_SKT_REG_BASE+(n*W5100_SKT_OFFSET))
#define  W5100_NUM_SOCKETS    4

/*
 *  The following offsets are added to a socket's base register address to find
 *  a specific socket register.  For example, the address of the command register
 *  for socket 2 would be:
 *  (W5100_SKT_BASE(2) + W5100_CR_OFFSET
 */
#define  W5100_MR_OFFSET      0x0000    /* socket Mode Register offset */
#define  W5100_CR_OFFSET      0x0001    /* socket Command Register offset */
#define  W5100_IR_OFFSET      0x0002    /* socket Interrupt Register offset */
#define  W5100_SR_OFFSET      0x0003    /* socket Status Register offset */
#define  W5100_PORT_OFFSET    0x0004    /* socket Port Register offset (2 bytes) */
#define  W5100_DHAR_OFFSET    0x0006    /* socket Destination Hardware Address Register (MAC, 6 bytes) */
#define  W5100_DIPR_OFFSET    0x000C    /* socket Destination IP Address Register (IP, 4 bytes) */
#define  W5100_DPORT_OFFSET   0x0010    /* socket Destination Port Register (2 bytes) */
#define  W5100_MSS_OFFSET     0x0012    /* socket Maximum Segment Size (2 bytes) */
#define  W5100_PROTO_OFFSET   0x0014    /* socket IP Protocol Register */
#define  W5100_TOS_OFFSET     0x0015    /* socket Type Of Service Register */
#define  W5100_TTL_OFFSET     0x0016    /* socket Time To Live Register */
#define  W5100_TX_FSR_OFFSET  0x0020    /* socket Transmit Free Size Register (2 bytes) */
#define  W5100_TX_RR_OFFSET   0x0022    /* socket Transmit Read Pointer Register (2 bytes) */
#define  W5100_TX_WR_OFFSET   0x0024    /* socket Transmit Write Pointer Register (2 bytes) */
#define  W5100_RX_RSR_OFFSET  0x0026    /* socket Receive Received Size Register (2 bytes) */
#define  W5100_RX_RD_OFFSET   0x0028    /* socket Receive Read Pointer Register (2 bytes) */

/*
 *  The following #defines are values written to a socket's Mode register to select
 *  the protocol and other operating characteristics.
 */
#define  W5100_SKT_MR_CLOSE   0x00      /* Unused socket */
#define  W5100_SKT_MR_TCP     0x01      /* TCP */
#define  W5100_SKT_MR_UDP     0x02      /* UDP */
#define  W5100_SKT_MR_IPRAW   0x03      /* IP LAYER RAW SOCK */
#define  W5100_SKT_MR_MACRAW  0x04      /* MAC LAYER RAW SOCK */
#define  W5100_SKT_MR_PPPOE   0x05      /* PPPoE */
#define  W5100_SKT_MR_ND      0x20      /* No Delayed Ack(TCP) flag */
#define  W5100_SKT_MR_MULTI   0x80      /* support multicasting */


/*!
 * \brief Requests the SPI bus and sets the CS low.
 */
void W5100_RequestSPIBus(void);

/*!
 * \brief Sets the CS High and releases the SPI bus.
 */
void W5100_ReleaseSPIBus(void);

/*!
 * \brief Callback callded from LDD SPI driver
 * \param UserDataPtr Pointer to user data structure
 */
void W5100_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*!
 * \brief Write the network configuration to the device.
 * \param config Pointer to configuration structure.
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t W5100_WriteConfig(w5100_config_t *config);

/*!
 * \brief Read the network configuration from the device.
 * \param config Pointer to configuration structure.
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t W5100_ReadConfig(w5100_config_t *config);

/*!
 * \brief Write a byte to the device.
 * \param addr Device memory address.
 * \param val value to write
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t W5100_MemWriteByte(uint16_t addr, uint8_t val);

/*!
 * \brief Read a byte from the device.
 * \param addr Device memory address.
 * \param val Pointer to where to store the value
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t W5100_MemReadByte(uint16_t addr, uint8_t *val);

/*!
 * \brief Write a word (16bit) to the device.
 * \param addr Device memory address.
 * \param val value to write
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t W5100_MemWriteWord(uint16_t addr, uint16_t val);

/*!
 * \brief Read a word (16bit) from the device.
 * \param addr Device memory address.
 * \param val Pointer to where to store the value
 * \return Error code, ERR_OK if everything is fine.
 */
uint8_t W5100_MemReadWord(uint16_t addr, uint16_t *val);

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t W5100_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io);

/*!
 * \brief Driver initialization routine.
 */
void W5100_Init(void);

#endif
