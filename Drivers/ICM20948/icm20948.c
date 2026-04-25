/*
 * icm20948.c
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#include "icm20948.h"
#include "spi.h"


static void write_reg(uint8_t reg, uint8_t data);
static uint8_t read_reg(uint8_t reg);

void ICM20948_Init(void)
{
    SPI1_Init();
    SPI1_Enabled();

    // WHO_AM_I check (critical first test)
    uint8_t who = read_reg(0x00);

    if (who != 0xEA)
    {
        // SPI or wiring failure
        while (1);
    }

    // basic wake-up sequence (simplified)
    select_bank(0x00);
    write_reg(0x06, 0x01); // wake / clock select
    write_reg(0x07, 0x00); // Select gyro
    SPI1_Disabled();
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
    SPI1_Transfer(reg | 0x80); // Prepare for read
    SPI1_Transfer(0x00); // Send dummy data to start the ICM output process
    val = SPI1_Receive(); // read the ICM output through MISO

    while(SPI1->SR & SPI_SR_BSY);
    SPI1_CS_High();
    return val;
}

void select_bank(uint8_t bank)
{
    write_reg(REG_BANK_SEL, bank << 4);
}
