/*
 * espuartproto.c
 *
 *  Created on: Apr 27, 2026
 *      Author: ututo
 */

#include "espuartproto.h"

HAL_StatusTypeDef ESPUART_Transmit(espuart_t *espuart) {

	uint8_t buffer[MAX_FRAME_SIZE]; // 6 bytes of data for ICM and 4 bytes for INA, total = 3 (header) + 10 (max payload) + 1 (checksum) + 1 (end byte) = 15

	ESPUART_Checksum(espuart);

	// Build header
	buffer[0] = START_BYTE;
	buffer[1] = espuart->type;
	buffer[2] = espuart->len;

	// Copy payload
	for (uint8_t i = 0; i < espuart->len; i++)
	{
		buffer[3+i] = espuart->payload[i];
	}

	// Append checksum and end-byte
	uint8_t end = 3 + espuart->len;
	buffer[end] = espuart->checksum;
	buffer[end+1] = END_BYTE;

	// Send
	HAL_StatusTypeDef status = HAL_UART_Transmit(&ESPUART, buffer, sizeof(buffer), 500);
	if(status != HAL_OK)
		return status;

	// Check for ACK response and integrity
	status = ESPUART_Recieve(buffer, ACK_SIZE);
	if(status != HAL_OK)
		return status;
	if(buffer[1] != TYPE_ACK || buffer[2] != 0)
		return HAL_ERROR;

	return HAL_OK;

}


HAL_StatusTypeDef ESPUART_Recieve(uint8_t *buffer, uint8_t size) {

	HAL_StatusTypeDef status = HAL_UART_Receive(&ESPUART, buffer, size, ACK_TIMEOUT);
	if(status != HAL_OK)
		return status;
	if(buffer[0] != START_BYTE)
		return HAL_ERROR;
	if(!ESPUART_VerifyCheksum(buffer, size))
		return HAL_ERROR;
	// TODO: Verify overall data integrity (that length is appropriate, END_BYTE exists, etc.

	return HAL_OK;
}

bool ESPUART_VerifyCheksum(uint8_t *frame_buff, uint8_t sz) {
	uint8_t checksum = frame_buff[0];

	for(uint8_t i =1; i < sz-2; i++ ) {
		checksum ^= frame_buff[i];
	}

	if(checksum != frame_buff[sz-2]) {
		return false;
	}
	return true;
}

void ESPUART_Checksum(espuart_t *espuart) {
	uint8_t checksum = START_BYTE ^ espuart->type ^ espuart->len;

	for(int i = 0; i < espuart->len; i++) {
		checksum ^= espuart->payload[i];
	}

	espuart->checksum = checksum;
}
