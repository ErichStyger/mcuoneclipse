/*
 * MMA8451.h
 *
 *  Created on: Aug 17, 2012
 *      Author: Erich Styger
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
  volatile bool dataReceivedFlg; /* set to TRUE by the interrupt if we have received data */
  volatile bool dataTransmittedFlg; /* set to TRUE by the interrupt if we have set data */
  LDD_TDeviceData *handle; /* pointer to the device handle */
} MMA8451_TDataState;

/* \brief Run the demo application */
void MMA8451_Run(void);

#endif /* MMA8451_H_ */
