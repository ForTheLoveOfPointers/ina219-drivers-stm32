/*
 * espuartproto.c
 *
 *  Created on: Apr 27, 2026
 *      Author: ututo
 */

#include "espuartproto.h"

HAL_StatusTypeDef ESPUART_Transmit(espuart_t *espuart) {

	uint8_t buffer[15]; // 6 bytes of data for ICM and 4 bytes for INA, total = 3 (header) + 10 (max payload) + 1 (checksum) + 1 (end byte) = 15

	espuart->checksum = ESPUART_Checksum(espuart);

	// Build header
	buffer[0] = START_BYTE;
	buffer[1] = espuart->type;
	buffer[2] = espuart->len;

	// Copy payload
	for (uint8_t i; i < espuart->len; i++)
	{
		buffer[i] = espuart->payload[i];
	}

	// Append checksum and end-byte
	uint8_t end = 3 + espuart->len;
	buffer[end] = espuart->checksum;
	buffer[end+1] = END_BYTE;

	// Send
	return HAL_UART_Transmit(&ESPUART, espuart->payload, espuart->len, 500);

}

void ESPUART_Checksum(espuart_t *espuart) {
	uint8_t checksum = espuart->type ^ espuart->len;

	for(int i = 0; i < espuart->len; i++) {
		checksum ^= espuart->payload[i];
	}

	espuart->checksum = checksum;
}
