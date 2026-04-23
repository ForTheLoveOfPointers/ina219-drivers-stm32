/*
 * spi.c
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#include "spi.h"
#include "stm32f4xx.h"

/* Takes care of initializing the SPI clock via registers */
void SPI1_Init(void) {
	// Initialize clocks
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Remap GPIO A port to pins 4 (SS/CS) 5 (SCK), 6 (MISO) and 7 (MOSI)
	GPIOA->MODER =  (0x2 << (5*2)) | (0x2 << (6*2)) | (0x2 << (7*2));
	GPIOA->AFR[0] |= (5 << (5*4)) | (5 << (6*4)) | (5 << (7*4));

	GPIOA->MODER |= (0x1 << (4*2)); // Set GPIOA 4 as CS/SS

	// SPI Config
	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;
	SPI1->CR1 |= SPI_CR1_BR_0;

	SPI1->CR1 |= SPI_CR1_SPE;
}

uint8_t SPI1_Transfer(uint8_t data) {
	while (!(SPI1->SR & SPI_SR_TXE)); // If Tx buff is not empty, wait
	SPI1->DR = data;
	while (!(SPI1->SR & SPI_SR_RXNE)); // If Rx buff is not empty, wait
	return SPI1->DR;
}

void SPI1_CS_Low(void)
{
    GPIOA->ODR &= ~(1 << 4);
}

void SPI1_CS_High(void)
{
    GPIOA->ODR |= (1 << 4);
}
