/**
 * \file
 * \brief This is the interface for the Radio Application part.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module acts as the application part of the network stack.
 */

#ifndef RAPP_H_
#define RAPP_H_

#include "Platform.h"
#include "RNWK.h"

/* payload format is:
 * <type><size><data>
 */
#define RAPP_HEADER_SIZE   (2) /* <type><size> */
#define RAPP_PAYLOAD_SIZE  (RNWK_PAYLOAD_SIZE-RAPP_HEADER_SIZE)
#define RAPP_BUFFER_SIZE   (RNWK_BUFFER_SIZE)

/* PHY buffer access macros */
#define RAPP_BUF_IDX_TYPE                 (RNWK_BUF_IDX_PAYLOAD+0) /* <type> index */
#define RAPP_BUF_IDX_SIZE                 (RNWK_BUF_IDX_PAYLOAD+1) /* <size> index */
#define RAPP_BUF_IDX_PAYLOAD              (RNWK_BUF_IDX_PAYLOAD+2) /* <app payload> index */

#define RAPP_BUF_TYPE(phy)                ((phy)[RAPP_BUF_IDX_TYPE])
#define RAPP_BUF_SIZE(phy)                ((phy)[RAPP_BUF_IDX_SIZE])

#define RAPP_BUF_PAYLOAD_START(phy)       (RNWK_BUF_PAYLOAD_START(phy)+RAPP_HEADER_SIZE)

/* type ID's for application messages */
typedef enum RAPP_MSG_Type {
#if PL_IS_INTRO
  RAPP_MSG_TYPE_ACCEL = 0x00,
#endif
#if PL_IS_WILCO_SPS || PL_IS_WILCO_SENSOR
  RAPP_PRESSURE_PART1 = 0x01,
  RAPP_PRESSURE_PART2 = 0x02,
#endif
  RAPP_MSG_TYPE_STDIN = 0x03,
  RAPP_MSG_TYPE_STDOUT = 0x04,
  RAPP_MSG_TYPE_STDERR = 0x05
} RAPP_MSG_Type;

uint8_t RAPP_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RAPP_MSG_Type type);

uint8_t RAPP_Process(void);

#if PL_HAS_SHELL
#include "CLS1.h"
uint8_t RAPP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*! \brief Initializes the module */
void RAPP_Init(void);

/*! \brief Deinitializes the module */
void RAPP_Deinit(void);

#endif /* RAPP_H_ */
