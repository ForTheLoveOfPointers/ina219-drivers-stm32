/*
 * icm20948.h
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#ifndef ICM20948_ICM20948_H_
#define ICM20948_ICM20948_H_

#include "stdint.h"

typedef struct {

} icm20948_t;


void ICM20948_Init(void);
uint8_t ICM20948_ReadWhoAmI(void);

#endif /* ICM20948_ICM20948_H_ */
