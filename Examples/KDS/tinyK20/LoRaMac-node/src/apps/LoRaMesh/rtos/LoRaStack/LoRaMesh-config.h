/**
 * \file LoRaMesh-config.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
 * \version 1.0
 *
 * \brief LoRa stack board specific configuration file
 */

#ifndef __LORAMESH_CONFIG_H_
#define __LORAMESH_CONFIG_H_

#include "board.h"
#include "LoRaMesh_AppConfig.h"

/* Default configuration items, can be overwritten by the application configuration header file: */

#ifndef LORAMESH_CONFIG_MAJOR_VERSION
#define LORAMESH_CONFIG_MAJOR_VERSION                       (0)
#endif

/*! Class A&B receive delay in us  */
#ifndef LORAMESH_CONFIG_RECEIVE_DELAY1
#define LORAMESH_CONFIG_RECEIVE_DELAY1                      (1000000)
#endif
#ifndef LORAMESH_CONFIG_RECEIVE_DELAY2
#define LORAMESH_CONFIG_RECEIVE_DELAY2                      (2000000)
#endif

/*! Join accept receive delay in us */
#ifndef LORAMESH_CONFIG_JOIN_ACCEPT_DELAY1
#define LORAMESH_CONFIG_JOIN_ACCEPT_DELAY1                  (5000000)
#endif
#ifndef LORAMESH_CONFIG_JOIN_ACCEPT_DELAY2
#define LORAMESH_CONFIG_JOIN_ACCEPT_DELAY2                  (6000000)
#endif

/*! Class A&B maximum receive window delay in us */
#ifndef LORAMESH_CONFIG_MAX_RX_WINDOW
#define LORAMESH_CONFIG_MAX_RX_WINDOW                       (300000)//(1000000)
#endif

/*! Transmission timeout */
#ifndef LORAMESH_CONFIG_TX_TIMEOUT
#define LORAMESH_CONFIG_TX_TIMEOUT                          (1000000)
#endif

/*! Maximum allowed gap for the FCNT field */
#ifndef LORAMESH_CONFIG_MAX_FCNT_GAP
#define LORAMESH_CONFIG_MAX_FCNT_GAP                        (16384)
#endif

#ifndef LORAMESH_CONFIG_ADR_ACK_LIMIT
#define LORAMESH_CONFIG_ADR_ACK_LIMIT                       (64)
/*! ADR acknowledgement counter limit */
#endif
#ifndef LORAMESH_CONFIG_ADR_ACK_DELAY
#define LORAMESH_CONFIG_ADR_ACK_DELAY                       (32)
/*! Number of ADR acknowledgement requests before returning to default datarate */
#endif

/* Advertising constants */
#ifndef LORAMESH_CONFIG_ADV_CHANNEL_FREQUENCY
#define LORAMESH_CONFIG_ADV_CHANNEL_FREQUENCY               (868300000)
/*! Advertising beacon channel in Hz */
#endif
#ifndef LORAMESH_CONFIG_ADV_BANDWIDTH
#define LORAMESH_CONFIG_ADV_BANDWIDTH                       (0)
/*! Advertising bandwidth */
#endif
#ifndef LORAMESH_CONFIG_ADV_DATARATE
#define LORAMESH_CONFIG_ADV_DATARATE                        (DR_5)
/*! Advertising data rate */
#endif
#ifndef LORAMESH_CONFIG_ADV_TX_POWER
#define LORAMESH_CONFIG_ADV_TX_POWER                        (1)
/*! Advertising tx power */
#endif
#ifndef LORAMESH_CONFIG_ADV_INTERVAL
#define LORAMESH_CONFIG_ADV_INTERVAL                        (30000000)
/*! Advertising interval in us */
#endif
#ifndef LORAMESH_CONFIG_ADV_SLOT_DURATION
#define LORAMESH_CONFIG_ADV_SLOT_DURATION                   (2000000)
/*! Advertising reception window in us */
#endif
#ifndef LORAMESH_CONFIG_ADV_EXPLICIT_HDR_OFF
#define LORAMESH_CONFIG_ADV_EXPLICIT_HDR_OFF                (true)
/*! Advertising explicit header mode off */
#endif
#ifndef LORAMESH_CONFIG_ADV_PACKET_LEN
#define LORAMESH_CONFIG_ADV_PACKET_LEN                      (14)
/*! Advertising reception window in us */
#endif
#ifndef LORAMESH_CONFIG_ADV_CRC_ON
#define LORAMESH_CONFIG_ADV_CRC_ON                          (false)
/*! Advertising CRC on */
#endif

/* Maximal number of multicast groups */
#ifndef LORAMESH_CONFIG_MAX_NOF_MULTICAST_GROUPS
#define LORAMESH_CONFIG_MAX_NOF_MULTICAST_GROUPS            (8)
#endif

/* Maximal number of multicast groups */
#ifndef LORAMESH_CONFIG_MAX_NOF_CHILD_NODES
#define LORAMESH_CONFIG_MAX_NOF_CHILD_NODES                 (8)
#endif

/*! Maximal number of fPort handlers */
#ifndef LORAMESH_CONFIG_MAX_NOF_PORT_HANDLERS
#define LORAMESH_CONFIG_MAX_NOF_PORT_HANDLERS               (16)
#endif

/* Maximal number of LoRaMesh scheduler events */
#ifndef LORAMESH_CONFIG_MAX_NOF_SCHEDULER_EVENTS
#define LORAMESH_CONFIG_MAX_NOF_SCHEDULER_EVENTS            (64)
#endif

#ifndef LORAMESH_CONFIG_MAX_NOF_SCHEDULER_EVENT_HANDLERS
#define LORAMESH_CONFIG_MAX_NOF_SCHEDULER_EVENT_HANDLERS    (16)
#endif

#ifndef LORAMESH_CONFIG_TRANSCEIVER_PAYLOAD_SIZE
#define LORAMESH_CONFIG_TRANSCEIVER_PAYLOAD_SIZE            (255)
/*!< Size of the physical transceiver payload (bytes) */
#endif

/* Configuration for Rx and Tx queues */
#ifndef LORAMESH_CONFIG_MSG_QUEUE_RX_LENGTH
#define LORAMESH_CONFIG_MSG_QUEUE_RX_LENGTH                 (2)
/*!< Number items in the Rx message queue. The higher, the more items can be buffered. */
#endif
#ifndef LORAMESH_CONFIG_MSG_QUEUE_TX_LENGTH
#define LORAMESH_CONFIG_MSG_QUEUE_TX_LENGTH                 (2)
/*!< Number items in the Tx message queue. The higher, the more items can be buffered. */
#endif
#ifndef LORAMESH_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS
#define LORAMESH_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS         (200/portTICK_RATE_MS)
/*!< Blocking time for putting items into the message queue before timeout. Use portMAX_DELAY for blocking. */
#endif

#endif /* __LORAMESH_CONFIG_H_ */
