/*
 * espuartproto.h
 *
 *  Created on: Apr 27, 2026
 *      Author: ututo
 *
 * -------------------------------------------------------------------------------------------------------------------------------------
 * Protocol is made to communicate via UART between both an STM32 and an ESP32 MCUs.                                                   |
 * The implementation is pretty simple. The STM32 should only send sensor data (e.g. voltage readings, gyroscope data),                |
 * this sensor data will be send by the ESP32 via wi-fi to a remote DB.                                                                |
 *                																													   |
 * The FRAME FORMAT is the following:																						           |
 *																																	   |
 * START BYTE | TYPE | LEN | PAYLOAD | CHECKSUM | END BYTE 																			   |
 *																																	   |
 * Where:																															   |
 *																																	   |
 * START BYTE = 0xAA																												   |
 * END BYTE = 0x55																													   |
 *																																	   |
 * and TYPE could have the following 3 values:																						   |
 *																																	   |
 * TYPE = 0x01  -> Is gyroscope data from the ICM20948																		           |
 * TYPE = 0x02  -> Power data from the INA219. Contains bus voltage and current readings, both 2 bytes in length, in that order.       |
 * TYPE = 0x03  -> Send gyro and power data in the same frame																	       |
 *																															           |
 * LEN is a 1 byte field, containing the length of the payload.																	       |
 * PAYLOAD is the sensor data, up to 256 bytes																						   |
 * CHECKSUM has a length of 1 byte, and is computed by XORing START ^ TYPE ^ LEN ^ PAYLOAD																		   |
 * -------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef STM_ESP_INCLUDE_ESPUARTPROTO_H_
#define STM_ESP_INCLUDE_ESPUARTPROTO_H_


#include <stdint.h>
#include "stm32f4xx_hal.h"

#define START_BYTE 0xAA
#define END_BYTE 0x55

#define TYPE_IMU   0x01
#define TYPE_POWER 0x02
#define TYPE_ALL 0x03

#define ESPUART huart1

typedef struct {
	uint8_t type;
	uint8_t len;
	uint8_t *payload;
	uint8_t checksum;
} espuart_t;


extern UART_HandleTypeDef ESPUART;

HAL_StatusTypeDef ESPUART_Transmit(espuart_t *espuart);
void ESPUART_Checksum(espuart_t *espuart);

#endif /* STM_ESP_INCLUDE_ESPUARTPROTO_H_ */
