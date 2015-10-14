/**
 * \file
 * \brief This is the Platform configuration header file
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_USE_ETH    (1)
  /*!< If using Ethernet (1) or not (0) */
#define PL_USE_SD     (1)
  /*!< If using SD card (1) or not (0) */

#define PL_USE_DHCP   (0 && PL_USE_ETH)
  /*!< If using DHCP (1) or not (0) */
#define PL_USE_INI    (1 && PL_USE_SD)
  /*!< If using .ini file (1) or not (0) */

#endif /* PLATFORM_H_ */
