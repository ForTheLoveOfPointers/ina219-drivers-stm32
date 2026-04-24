/*
 * icm20948.h
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#ifndef ICM20948_ICM20948_H_
#define ICM20948_ICM20948_H_

#include "stdint.h"

#define REG_BANK_SEL 0x7F

typedef struct {

} icm20948_t;


void ICM20948_Init(void);
uint8_t ICM20948_ReadWhoAmI(void);
void select_bank(uint8_t bank);

#endif /* ICM20948_ICM20948_H_ */
