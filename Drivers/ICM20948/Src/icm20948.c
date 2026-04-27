/*
 * icm20948.c
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#include "icm20948.h"
#include <stdio.h>


static void write_reg(uint8_t reg, uint8_t data);
static uint8_t read_reg(uint8_t reg);

float GYRO_SEL = 131.0f;

void ICM20948_Init(void)
{
	SPI1_Init();
	SPI1_Enabled();

	HAL_Delay(10);

	// -------------------------
	// WHO_AM_I check
	// -------------------------
	select_bank(0);
	uint8_t who = read_reg(0x00);

	if (who != 0xEA)
	{
		while (1);
	}

	// -------------------------
	// RESET
	// -------------------------
	write_reg(0x06, 0x80); // PWR_MGMT_1 reset
	HAL_Delay(100);

	// -------------------------
	// WAKE UP (clear sleep bit)
	// -------------------------
	uint8_t pwr = read_reg(0x06);
	pwr &= ~(0x40); // clear sleep bit
	write_reg(0x06, pwr);
	HAL_Delay(10);

	// -------------------------
	// SET CLOCK SOURCE (PLL gyro X)
	// -------------------------
	pwr = read_reg(0x06);
	pwr = (pwr & 0xF8) | 0x01;
	write_reg(0x06, pwr);
	HAL_Delay(10);

	// -------------------------
	// ENABLE GYRO + ACCEL
	// -------------------------
	write_reg(0x07, 0x00); // PWR_MGMT_2
	HAL_Delay(100);

	// -------------------------
	// ENABLE SPI MODE (Prevents I2C switching)
	// -------------------------
	uint8_t user = read_reg(0x03); // USER_CTRL
	user |= 0x10;
	write_reg(0x03, user);
	HAL_Delay(10);

	// -------------------------
	// ODR ALIGN ENABLE (CRITICAL)
	// -------------------------
	select_bank(2);
	write_reg(0x09, 0x01); // ODR_ALIGN_EN
	HAL_Delay(10);

	// -------------------------
	// GYRO CONFIG
	// -------------------------
	// ±250 dps + DLPF enabled
	uint8_t gyro_cfg = read_reg(0x01);
	gyro_cfg |= 0x01; // enable DLPF
	write_reg(0x01, gyro_cfg);

	// Sample rate divider = 0 (max rate)
	write_reg(0x00, 0x00);

	HAL_Delay(10);

	// -------------------------
	// BACK TO BANK 0
	// -------------------------
	select_bank(0);

	HAL_Delay(50);

	SPI1_Disabled();
}


void read_gyro(float* gyro_dps) {
	uint8_t buffer[6];

	select_bank(0);

	SPI1_CS_Low();
	SPI1_Transfer(0x33 | 0x80);
	for (int i = 0; i < 6; i++)
	{

		buffer[i] = SPI1_Transfer(0x00);
	}

	while(SPI1->SR & SPI_SR_BSY);
	SPI1_CS_High();


	printf("%02X %02X %02X %02X %02X %02X\n",
	       buffer[0], buffer[1], buffer[2],
	       buffer[3], buffer[4], buffer[5]);

	int16_t gx = (buffer[0] << 8) | buffer[1];
	int16_t gy = (buffer[2] << 8) | buffer[3];
	int16_t gz = (buffer[4] << 8) | buffer[5];

	gyro_dps[0] = gx / GYRO_SEL;
	gyro_dps[1] = gy / GYRO_SEL;
	gyro_dps[2] = gz / GYRO_SEL;
}


static void write_reg(uint8_t reg, uint8_t data)
{
	SPI1_CS_Low();
    SPI1_Transfer(reg & 0x7F);
    SPI1_Transfer(data);

    while(SPI1->SR & SPI_SR_BSY);
    SPI1_CS_High();
}

static uint8_t read_reg(uint8_t reg)
{
    uint8_t val;

    SPI1_CS_Low();
    SPI1_Transfer(reg | 0x80);  // send address
	val = SPI1_Transfer(0x00);   // dummy clock to read data

    while(SPI1->SR & SPI_SR_BSY);
    SPI1_CS_High();

    return val;
}

void select_bank(uint8_t bank)
{
    write_reg(REG_BANK_SEL, bank << 4);
}
