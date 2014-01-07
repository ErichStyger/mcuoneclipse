/**
 * \file
 * \brief This is the interface for a key matrix.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 *
 * This module implements a driver for a keyboard matrix (e.g. 4x4 keyboard).
 */

#ifndef KEY_MATRIX_H
#define KEY_MATRIX_H

#define KM_NO_KEY  -1

/*!
 * \brief Keyboard scan routine. 
 * \return key code (e.g. 0-15 for a 4x4 keyboard), KM_NO_KEY otherwise.
 */
int KM_ScanTask(void);             // Taste speichern und entprellen

/*!
 * \brief Initialization of the driver
 */
void KM_Init(void);

#endif /* KEY_MATRIX_H */
