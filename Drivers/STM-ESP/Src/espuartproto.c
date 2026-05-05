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
	uint8_t frame_len = 3 + espuart->len + 2;
	HAL_StatusTypeDef status = HAL_UART_Transmit(&ESPUART, buffer, frame_len, 500);
	if(status != HAL_OK)
		return status;

	// Check for ACK response and integrity
	__HAL_UART_FLUSH_DRREGISTER(&ESPUART);
	uint8_t rx_buf[MAX_FRAME_SIZE];
	uint8_t rx_len;

	status = ESPUART_Receive(rx_buf, &rx_len);
	if(status != HAL_OK)
		return status;
	if(rx_buf[1] != TYPE_ACK || rx_buf[2] != 0)
		return HAL_ERROR;
	return HAL_OK;

}


HAL_StatusTypeDef ESPUART_Recieve(uint8_t *out_buf, uint8_t *out_len) {
	ESPUART_RxContext ctx = {0};
	ctx.state = RX_WAIT_START;

	uint8_t byte;
	uint32_t start = HAL_GetTick();

	while((HAL_GetTick() - start) < ACK_TIMEOUT) {

		if(HAL_UART_Receive(&ESPUART, &byte, 1, 10) == HAL_OK) {

			if(ESPUART_ProcessByte(&ctx, byte)) {
				memcpy(out_buf, ctx.buffer, ctx.index);
				*out_len = ctx.index;
				return HAL_OK;
			}
		}
	}

	return HAL_TIMEOUT;

}

bool ESPUART_ProcessByte(ESPUART_RxContext *ctx, uint8_t byte) {

    switch(ctx->state) {

        case RX_WAIT_START:
            if(byte == START_BYTE) {
                ctx->index = 0;
                ctx->buffer[ctx->index++] = byte;
                ctx->state = RX_TYPE;
            }
            break;

        case RX_TYPE:
            ctx->buffer[ctx->index++] = byte;
            ctx->state = RX_LEN;
            break;

        case RX_LEN:
            ctx->buffer[ctx->index++] = byte;
            ctx->expected_len = byte;
            ctx->state = (byte > 0) ? RX_PAYLOAD : RX_CHECKSUM;
            break;

        case RX_PAYLOAD:
            ctx->buffer[ctx->index++] = byte;
            if(ctx->index == (3 + ctx->expected_len)) {
                ctx->state = RX_CHECKSUM;
            }
            break;

        case RX_CHECKSUM:
            ctx->buffer[ctx->index++] = byte;
            ctx->state = RX_END;
            break;

        case RX_END:
            ctx->buffer[ctx->index++] = byte;

            // Validate frame
            if(byte == END_BYTE &&
               ESPUART_VerifyCheksum(ctx->buffer, ctx->index)) {

                ctx->state = RX_WAIT_START;
                return true;
            }

            ctx->state = RX_WAIT_START;
            break;
    }

    return false;
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



void cast_int16(uint8_t* buf, int16_t data) {
	buf[0] = (uint8_t)((data >> 8) & 0xFF); // MSB
	buf[1] = (uint8_t)(data & 0xFF); // LSB
}

void cast_uint16(uint8_t* buf, uint16_t data) {
	buf[0] = (uint8_t)((data >> 8) & 0xFF); // MSB
	buf[1] = (uint8_t)(data & 0xFF); // LSB
}
