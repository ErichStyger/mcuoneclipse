/**
 * \file gps-board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 02.11.2015
 * \brief Target board driver for GPS receiver
 *
 */

#ifndef __GPS_BOARD_H_
#define __GPS_BOARD_H_

/*!
 * Position data structure.
 */
typedef struct Position_s {
    uint32_t Latitude;
    uint32_t Longitude;
} Position_t;

/*!
 * \brief Low level handling of the PPS signal from the GPS receiver
 */
void GpsMcuOnPpsSignal( void );

/*!
 * \brief Low level Initialisation of the UART and IRQ for the GPS
 */
void GpsMcuInit( void );

/*!
 * \brief IRQ handler for the UART receiver
 */
void GpsMcuIrqNotify( UartNotifyId_t id );

#endif /* _GPS_BOARD_H_ */
