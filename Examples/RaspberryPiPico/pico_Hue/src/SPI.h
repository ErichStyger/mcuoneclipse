/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 */

#ifndef MYSPI_H_
#define MYSPI_H_

bool Get_Lamp_State(void); /* this function returns the actual state of the lamp */

void SPI_Init(void);
void SPI_Deinit(void);

#endif /* SPI_H_ */
