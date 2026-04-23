/*
 * icm20948.c
 *
 *  Created on: Apr 23, 2026
 *      Author: ututo
 */

#include "icm20948.h"


#define CS_LOW()  (GPIOA->BSRR = (1<<(4+16)))
#define CS_HIGH() (GPIOA->BSRR = (1<<4))

void ICM20948_Init(void)
{
    SPI1_Init();

    // WHO_AM_I check (critical first test)
    uint8_t who = read_reg(0x00);

    if (who != 0xEA)
    {
        // SPI or wiring failure
        while (1);
    }

    // basic wake-up sequence (simplified)
    write_reg(0x06, 0x01); // wake / clock select
}


static void write_reg(uint8_t reg, uint8_t data)
{
    CS_LOW();
    SPI1_Transfer(reg & 0x7F);
    SPI1_Transfer(data);
    CS_HIGH();
}

static uint8_t read_reg(uint8_t reg)
{
    uint8_t val;
    CS_LOW();
    SPI1_Transfer(reg | 0x80);
    val = SPI1_Transfer(0x00);
    CS_HIGH();
    return val;
}
