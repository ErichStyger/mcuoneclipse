/*
 * Platform.h
 *
 *  Created on: 27.07.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_PLATFORM_H_
#define SOURCES_PLATFORM_H_

/* transceiver types */
#define PL_RH_TRANSCEIVER_NRF24L01  0 /* nRF24L01+ */
#define PL_RH_TRANSCEIVER_RH_RF95   1 /* LoRa */

#if 0
  #define PL_RH_TRANSCEIVER_TYPE  PL_RH_TRANSCEIVER_NRF24L01
#else
  #define PL_RH_TRANSCEIVER_TYPE  PL_RH_TRANSCEIVER_RH_RF95
#endif

#endif /* SOURCES_PLATFORM_H_ */
