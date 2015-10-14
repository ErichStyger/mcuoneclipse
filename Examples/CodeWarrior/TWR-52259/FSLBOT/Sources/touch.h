/**
 *\brief Interface for a MPR121 touchsensor driver
 *\author Andreas Schoepfer andreas.schoepfer@stud.hslu.ch
 *\date 26.10.11
 * 
 * To correct a faulty initialization of the touchsensor, 
 * you have to power off and power on the complete MechBot.
 * ELEPowerOff is only for saving energy and doesn't help to 
 * correct an initialization. 
 * * 
 */

#ifndef TOUCH_H_
#define TOUCH_H_



/**
 * \brief Power on and initialize the touchsensor with the standard configuration
 */
void TOUCH_init(void);

/**
 * \brief Check the status of all 12 electrodes, by reading the status bits
 * at address 0x0 and 0x01 of MPR121.
 * @param eleNbr Pointer to the store the statusbits. LSB->ELE0; 1:touched, 0:untouched 
 * @return ERR_OK if successful
 */
uint8_t TOUCH_getELE(uint16_t* eleNbr);

/**
 * \brief Power off the touchsensor, for saving energy.
 */
void TOUCH_powerOff(void);

#endif /* TOUCH_H_ */
