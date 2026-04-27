/*
 * spi.c
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#include "spi.h"


/* Takes care of initializing the SPI clock via registers */
void SPI1_Init(void) {
	SPI1_Disabled();
	// Initialize clocks
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// PA5 SCK, PA6 MISO, PA7 MOSI -> AF5
	GPIOA->MODER &= ~((3<<(5*2))|(3<<(6*2))|(3<<(7*2)));
	GPIOA->MODER |=  ((2<<(5*2))|(2<<(6*2))|(2<<(7*2)));

	GPIOA->OSPEEDR |= (3<<(5*2)) | (3<<(6*2)) | (3<<(7*2));

	// Set GPIOA 4 as CS/SS
	GPIOA->MODER &= ~(0x3 << (4*2));
	GPIOA->MODER |= (0x1 << (4*2));

	GPIOA->OTYPER &= ~(1 << 4);      // push-pull
	GPIOA->OSPEEDR |= (3 << (4*2));  // high speed (optional)
	GPIOA->PUPDR &= ~(3 << (4*2));   // no pull-up/down

	GPIOA->BSRR = (1 << 4);


	GPIOA->AFR[0] &= ~((0xF<<(5*4))|(0xF<<(6*4))|(0xF<<(7*4)));
	GPIOA->AFR[0] |=  ((5<<(5*4))|(5<<(6*4))|(5<<(7*4)));



	// SPI config: Master, software NSS, mode 0 (adjust if needed)
	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
	SPI1->CR1 &= ~SPI_CR1_BR;
	SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;

}

void SPI1_Enabled(void) {
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI1_Disabled(void) {

	SPI1->CR1 &= ~SPI_CR1_SPE;

}

uint8_t SPI1_Transfer(uint8_t data) {
	while (!(SPI1->SR & SPI_SR_TXE)); // If Tx buff is not empty, wait
	*((volatile uint8_t*)&SPI1->DR) = data;
	while (!(SPI1->SR & SPI_SR_RXNE));
	return *((volatile uint8_t*)&SPI1->DR);
}


void SPI1_CS_Low(void)
{
	GPIOA->BSRR = (1 << (4 + 16));
}

void SPI1_CS_High(void)
{
	GPIOA->BSRR = (1 << 4);
}
