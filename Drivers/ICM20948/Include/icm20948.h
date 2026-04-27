/*
 * icm20948.h
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#ifndef ICM20948_ICM20948_H_
#define ICM20948_ICM20948_H_

#include "stdint.h"
#include "spi.h"
#include "stm32f4xx.h"

#define REG_BANK_SEL 0x7F


void ICM20948_Init(void);

void read_gyro(float* gyro_dps) ;
uint8_t ICM20948_ReadWhoAmI(void);

void select_bank(uint8_t bank);

#endif /* ICM20948_ICM20948_H_ */
