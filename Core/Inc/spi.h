/*
 * spi.h
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <stdint.h>
#include "stm32f4xx.h"

void SPI1_Init(void);
void SPI1_Transfer(uint8_t data);
uint8_t SPI1_Receive(void);

void SPI1_Enabled(void);
void SPI1_Disabled(void);

void SPI1_CS_Low(void);
void SPI1_CS_High(void);

#endif /* INC_SPI_H_ */
