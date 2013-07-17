/*
 * nRF24L01.h
 */

#ifndef NRF24L01_H_
#define NRF24L01_H_

#include "PE_Types.h"

/* Memory Map - register address defines */
#define RF24_CONFIG      0x00 /* CONFIG register */
#define RF24_EN_AA       0x01 /* EN_AA register */
#define RF24_EN_RXADDR   0x02 /* EN_RXADDR register */
#define RF24_SETUP_AW    0x03 /* SETUP_AW register */
#define RF24_SETUP_RETR  0x04
#define RF24_RF_CH       0x05
#define RF24_RF_SETUP    0x06 /* SETUP register */
#define RF24_STATUS      0x07
#define RF24_OBSERVE_TX  0x08
#define RF24_RPD     0x09    /* Mnemonic for nRF24L01+ */
//#define CD          0x09   /* Mnemonic from nRF24L01, new is RPD */
#define RF24_RX_ADDR_P0  0x0A
#define RF24_RX_ADDR_P1  0x0B
#define RF24_RX_ADDR_P2  0x0C
#define RF24_RX_ADDR_P3  0x0D
#define RF24_RX_ADDR_P4  0x0E
#define RF24_RX_ADDR_P5  0x0F
#define RF24_TX_ADDR     0x10
#define RF24_RX_PW_P0    0x11
#define RF24_RX_PW_P1    0x12
#define RF24_RX_PW_P2    0x13
#define RF24_RX_PW_P3    0x14
#define RF24_RX_PW_P4    0x15
#define RF24_RX_PW_P5    0x16
#define RF24_FIFO_STATUS 0x17

/* Bit Mnemonics */
/* CONFIG Register Bits */
#define RF24_MASK_RX_DR  (1<<6)  /* Mask interrupt caused by RX_DR: 1: interrupt masked. 0: interrupt enabled */
#define RF24_MASK_TX_DS  (1<<5)  /* Mask interrupt caused by TX_DS: 1: interrupt masked. 0: interrupt enabled */
#define RF24_MASK_MAX_RT (1<<4)  /* Mask interrupt caused by MAX_RT. 1: interrupt not reflected on IRQ pin. 0: reflect MAX_RT as active low interrupt on IRQ pin */
#define RF24_EN_CRC      (1<<3)  /* Enable CRC. Forced high if on of the bits in EN_AA is high */
#define RF24_CRCO        (1<<2)  /* CRC encoding scheme, 0: 1 byte, 1: 2 bytes */
#define RF24_PWR_UP      (1<<1)  /* 1: Power up, 0: Power down */
#define RF24_PRIM_RX     (1<<0)  /* 1: PRX, 0: PTX */
#define RF24_PRIM_TX     (0)     /* 0: PTX */

#define RF24_ENAA_P5     5
#define RF24_ENAA_P4     4
#define RF24_ENAA_P3     3
#define RF24_ENAA_P2     2
#define RF24_ENAA_P1     1
#define RF24_ENAA_P0     0
#define RF24_ERX_P5      5
#define RF24_ERX_P4      4
#define RF24_ERX_P3      3
#define RF24_ERX_P2      2
#define RF24_ERX_P1      1
#define RF24_ERX_P0      0
#define RF24_AW          0
#define RF24_ARD         4
#define RF24_ARC         0
#define RF24_PLL_LOCK    4
#define RF24_RF_DR_HIGH  3
#define RF24_RF_DR_LOW   5
#define RF24_RF_PWR      1
#define RF24_LNA_HCURR   0        
#define RF24_RX_DR       6
#define RF24_TX_DS       5
#define RF24_MAX_RT      4
#define RF24_RX_P_NO     1
#define RF24_TX_FULL     0
#define RF24_PLOS_CNT    4
#define RF24_ARC_CNT     0
#define RF24_TX_REUSE    6
#define RF24_FIFO_FULL   5
#define RF24_TX_EMPTY    4
#define RF24_RX_FULL     1
#define RF24_RX_EMPTY    0

/* Command Name Mnemonics (Instructions) */
#define RF24_R_REGISTER     0x00
#define RF24_W_REGISTER     0x20
#define RF24_REGISTER_MASK  0x1F
#define RF24_R_RX_PAYLOAD   0x61
#define RF24_W_TX_PAYLOAD   0xA0
#define RF24_FLUSH_TX       0xE1
#define RF24_FLUSH_RX       0xE2
#define RF24_REUSE_TX_PL    0xE3
#define RF24_NOP            0xFF

#define RF24_CONFIG_DEFAULT_VAL         0x08
#define RF24_EN_AA_DEFAULT_VAL          0x3F
#define RF24_EN_RXADDR_DEFAULT_VAL      0x03
#define RF24_SETUP_AW_DEFAULT_VAL       0x03
#define RF24_SETUP_RETR_DEFAULT_VAL     0x03
#define RF24_RF_CH_DEFAULT_VAL          0x02
#define RF24_RF_SETUP_DEFAULT_VAL       0x0F
#define RF24_STATUS_DEFAULT_VAL         0x0E
#define RF24_OBSERVE_TX_DEFAULT_VAL     0x00
#define RF24_CD_DEFAULT_VAL             0x00
#define RF24_RX_ADDR_P0_B0_DEFAULT_VAL  0xE7
#define RF24_RX_ADDR_P0_B1_DEFAULT_VAL  0xE7
#define RF24_RX_ADDR_P0_B2_DEFAULT_VAL  0xE7
#define RF24_RX_ADDR_P0_B3_DEFAULT_VAL  0xE7
#define RF24_RX_ADDR_P0_B4_DEFAULT_VAL  0xE7
#define RF24_RX_ADDR_P1_B0_DEFAULT_VAL  0xC2
#define RF24_RX_ADDR_P1_B1_DEFAULT_VAL  0xC2
#define RF24_RX_ADDR_P1_B2_DEFAULT_VAL  0xC2
#define RF24_RX_ADDR_P1_B3_DEFAULT_VAL  0xC2
#define RF24_RX_ADDR_P1_B4_DEFAULT_VAL  0xC2
#define RF24_RX_ADDR_P2_DEFAULT_VAL     0xC3
#define RF24_RX_ADDR_P3_DEFAULT_VAL     0xC4
#define RF24_RX_ADDR_P4_DEFAULT_VAL     0xC5
#define RF24_RX_ADDR_P5_DEFAULT_VAL     0xC6
#define RF24_TX_ADDR_B0_DEFAULT_VAL     0xE7
#define RF24_TX_ADDR_B1_DEFAULT_VAL     0xE7
#define RF24_TX_ADDR_B2_DEFAULT_VAL     0xE7
#define RF24_TX_ADDR_B3_DEFAULT_VAL     0xE7
#define RF24_TX_ADDR_B4_DEFAULT_VAL     0xE7
#define RF24_RX_PW_P0_DEFAULT_VAL       0x00
#define RF24_RX_PW_P1_DEFAULT_VAL       0x00
#define RF24_RX_PW_P2_DEFAULT_VAL       0x00
#define RF24_RX_PW_P3_DEFAULT_VAL       0x00
#define RF24_RX_PW_P4_DEFAULT_VAL       0x00
#define RF24_RX_PW_P5_DEFAULT_VAL       0x00
#define RF24_FIFO_STATUS_DEFAULT_VAL    0x11

/* CONFIG register bitwise definitions */
#define RF24_CONFIG_RESERVED     0x80
#define RF24_CONFIG_MASK_RX_DR   0x40
#define RF24_CONFIG_MASK_TX_DS   0x20
#define RF24_CONFIG_MASK_MAX_RT  0x10
#define RF24_CONFIG_EN_CRC       0x08
#define RF24_CONFIG_CRCO         0x04
#define RF24_CONFIG_PWR_UP       0x02
#define RF24_CONFIG_PRIM_RX      0x01

/* EN_AA register bitwise definitions */
#define RF24_EN_AA_RESERVED      0xC0
#define RF24_EN_AA_ENAA_ALL      0x3F
#define RF24_EN_AA_ENAA_P5       0x20
#define RF24_EN_AA_ENAA_P4       0x10
#define RF24_EN_AA_ENAA_P3       0x08
#define RF24_EN_AA_ENAA_P2       0x04
#define RF24_EN_AA_ENAA_P1       0x02
#define RF24_EN_AA_ENAA_P0       0x01
#define RF24_EN_AA_ENAA_NONE     0x00

/* EN_RXADDR register bitwise definitions */
#define RF24_EN_RXADDR_RESERVED  0xC0
#define RF24_EN_RXADDR_ERX_ALL   0x3F
#define RF24_EN_RXADDR_ERX_P5    0x20
#define RF24_EN_RXADDR_ERX_P4    0x10
#define RF24_EN_RXADDR_ERX_P3    0x08
#define RF24_EN_RXADDR_ERX_P2    0x04
#define RF24_EN_RXADDR_ERX_P1    0x02
#define RF24_EN_RXADDR_ERX_P0    0x01
#define RF24_EN_RXADDR_ERX_NONE  0x00

/* SETUP_AW register bitwise definitions */
#define RF24_SETUP_AW_RESERVED 0xFC
#define RF24_SETUP_AW          0x03
#define RF24_SETUP_AW_5BYTES   0x03
#define RF24_SETUP_AW_4BYTES   0x02
#define RF24_SETUP_AW_3BYTES   0x01
#define RF24_SETUP_AW_ILLEGAL  0x00

/* SETUP_RETR register bitwise definitions */
#define RF24_SETUP_RETR_ARD        0xF0
#define RF24_SETUP_RETR_ARD_4000   0xF0
#define RF24_SETUP_RETR_ARD_3750   0xE0
#define RF24_SETUP_RETR_ARD_3500   0xD0
#define RF24_SETUP_RETR_ARD_3250   0xC0
#define RF24_SETUP_RETR_ARD_3000   0xB0
#define RF24_SETUP_RETR_ARD_2750   0xA0
#define RF24_SETUP_RETR_ARD_2500   0x90
#define RF24_SETUP_RETR_ARD_2250   0x80
#define RF24_SETUP_RETR_ARD_2000   0x70
#define RF24_SETUP_RETR_ARD_1750   0x60
#define RF24_SETUP_RETR_ARD_1500   0x50
#define RF24_SETUP_RETR_ARD_1250   0x40
#define RF24_SETUP_RETR_ARD_1000   0x30
#define RF24_SETUP_RETR_ARD_750    0x20
#define RF24_SETUP_RETR_ARD_500    0x10
#define RF24_SETUP_RETR_ARD_250    0x00
#define RF24_SETUP_RETR_ARC        0x0F
#define RF24_SETUP_RETR_ARC_15     0x0F
#define RF24_SETUP_RETR_ARC_14     0x0E
#define RF24_SETUP_RETR_ARC_13     0x0D
#define RF24_SETUP_RETR_ARC_12     0x0C
#define RF24_SETUP_RETR_ARC_11     0x0B
#define RF24_SETUP_RETR_ARC_10     0x0A
#define RF24_SETUP_RETR_ARC_9      0x09
#define RF24_SETUP_RETR_ARC_8      0x08
#define RF24_SETUP_RETR_ARC_7      0x07
#define RF24_SETUP_RETR_ARC_6      0x06
#define RF24_SETUP_RETR_ARC_5      0x05
#define RF24_SETUP_RETR_ARC_4      0x04
#define RF24_SETUP_RETR_ARC_3      0x03
#define RF24_SETUP_RETR_ARC_2      0x02
#define RF24_SETUP_RETR_ARC_1      0x01
#define RF24_SETUP_RETR_ARC_0      0x00

/* RF_CH register bitwise definitions */
#define RF24_RF_CH_RESERVED    0x80

/* RF_SETUP register bitwise definitions */
#define RF24_RF_SETUP_RESERVED    0xE0
#define RF24_RF_SETUP_PLL_LOCK    0x10
#define RF24_RF_SETUP_RF_DR       0x08
#define RF24_RF_SETUP_RF_DR_250   0x20
#define RF24_RF_SETUP_RF_DR_1000  0x00
#define RF24_RF_SETUP_RF_DR_2000  0x08
#define RF24_RF_SETUP_RF_PWR      0x06
#define RF24_RF_SETUP_RF_PWR_0    0x06
#define RF24_RF_SETUP_RF_PWR_6    0x04
#define RF24_RF_SETUP_RF_PWR_12   0x02
#define RF24_RF_SETUP_RF_PWR_18   0x00
#define RF24_RF_SETUP_LNA_HCURR   0x01

/* STATUS register bit definitions */
#define RF24_STATUS_RESERVED                    0x80   /* bit 1xxx xxxx: This bit is reserved */
#define RF24_STATUS_RX_DR                       0x40   /* bit x1xx xxxx: Data ready RX FIFO interrupt. Asserted when new data arrives RX FIFO */
#define RF24_STATUS_TX_DS                       0x20   /* bit xx1x xxxx: Data sent TX FIFO interrupt. Asserted when packet transmitted on TX. */
#define RF24_STATUS_MAX_RT                      0x10   /* bit xxx1 xxxx: maximum number of TX retransmit interrupts */
#define RF24_STATUS_RX_P_NO                     0x0E
#define RF24_STATUS_RX_P_NO_RX_FIFO_NOT_EMPTY   0x0E
#define RF24_STATUS_RX_P_NO_UNUSED              0x0C
#define RF24_STATUS_RX_P_NO_5                   0x0A
#define RF24_STATUS_RX_P_NO_4                   0x08
#define RF24_STATUS_RX_P_NO_3                   0x06
#define RF24_STATUS_RX_P_NO_2                   0x04
#define RF24_STATUS_RX_P_NO_1                   0x02
#define RF24_STATUS_RX_P_NO_0                   0x00   /* bit xxxx 111x: pipe number for payload */
#define RF24_STATUS_TX_FULL                     0x01   /* bit xxxx xxx1: if bit set, then TX FIFO is full */

/* OBSERVE_TX register bitwise definitions */
#define RF24_OBSERVE_TX_PLOS_CNT   0xF0
#define RF24_OBSERVE_TX_ARC_CNT    0x0F

/* CD register bitwise definitions for nRF24L01 */
//#define RF24_CD_RESERVED   0xFE
//#define RF24_CD_CD         0x01

/* RPD register bitwise definitions for nRF24L01+ */
#define RF24_RPD_RESERVED    0xFE
#define RF24_RPD_RPD         0x01

/* RX_PW_P0 register bitwise definitions */
#define RF24_RX_PW_P0_RESERVED 0xC0

/* RX_PW_P0 register bitwise definitions */
#define RF24_RX_PW_P0_RESERVED 0xC0

/* RX_PW_P1 register bitwise definitions */
#define RF24_RX_PW_P1_RESERVED 0xC0

/* RX_PW_P2 register bitwise definitions */
#define RF24_RX_PW_P2_RESERVED 0xC0

/* RX_PW_P3 register bitwise definitions */
#define RF24_RX_PW_P3_RESERVED 0xC0

/* RX_PW_P4 register bitwise definitions */
#define RF24_RX_PW_P4_RESERVED 0xC0

/* RX_PW_P5 register bitwise definitions */
#define RF24_RX_PW_P5_RESERVED 0xC0

/* FIFO_STATUS register bitwise definitions */
#define RF24_FIFO_STATUS_RESERVED  0x8C
#define RF24_FIFO_STATUS_TX_REUSE  0x40
#define RF24_FIFO_STATUS_TX_FULL   0x20
#define RF24_FIFO_STATUS_TX_EMPTY  0x10
#define RF24_FIFO_STATUS_RX_FULL   0x02
#define RF24_FIFO_STATUS_RX_EMPTY  0x01


void RF_WriteRegister(uint8_t reg, uint8_t val);
uint8_t RF_ReadRegister(uint8_t reg);
void RF_ReadRegisterData(uint8_t reg, uint8_t *buf, uint8_t bufSize);
void RF_WriteRegisterData(uint8_t reg, uint8_t *buf, uint8_t bufSize);

uint8_t RF_GetStatus(void);

void RF_TxPayload(uint8_t *payload, uint8_t payloadSize);
void RF_RxPayload(uint8_t *payload, uint8_t payloadSize);
bool RF_DataIsReady(void);

void RF_ResetStatusIRQ(uint8_t flags);

void RF_Init(void);

#if 0
bool RF_MaxRetryReached(void);
uint8_t RF_GetChannel(void);
void RF_SetChannel(uint8_t channel);
void RF_SetPayloadSize(uint8_t payloadSize);
#endif

#endif /* NRF24L01_H_ */
