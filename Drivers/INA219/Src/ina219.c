/*
 * ina219.c
 *
 *  Created on: Apr 27, 2026
 *      Author: ututo
 */


#include "main.h"
#include "ina219.h"


uint16_t ina219_calibrationValue;
int16_t ina219_currentDivider_mA;
int16_t ina219_powerMultiplier_mW;


uint16_t Read16( uint8_t Register)
{
	uint8_t Value[2];

	HAL_I2C_Mem_Read(&INA219_I2C, INA219_ADDRESS, Register, 1, Value, 2, 1000);

	return ((Value[0] << 8) | Value[1]);
}


void Write16(uint8_t Register, uint16_t Value)
{
	uint8_t addr[2];
	addr[0] = (Value >> 8) & 0xff;  // upper byte
	addr[1] = (Value >> 0) & 0xff; // lower byte
	HAL_I2C_Mem_Write(&INA219_I2C, INA219_ADDRESS, Register, 1, (uint8_t*)addr, 2, 1000);
}


uint16_t Ina219_ReadBusVoltage(void)
{
	uint16_t result = Read16(INA219_REG_BUSVOLTAGE);

	return ((result >> 3  ) * 4);

}

int16_t Ina219_ReadCurrent_raw(void)
{
	int16_t result = Read16( INA219_REG_CURRENT);

	return (result );
}

float Ina219_ReadCurrent(void)
{
	int16_t result = Ina219_ReadCurrent_raw();

	return (result /(float) ina219_currentDivider_mA );
}

uint16_t Ina219_ReadShuntVolage(void)
{
	uint16_t result = Read16(INA219_REG_SHUNTVOLTAGE);

	return (result * 0.01 );
}

void Ina219_Reset(void)
{
	Write16(INA219_REG_CONFIG, INA219_CONFIG_RESET);
	HAL_Delay(1);
}

void Ina219_setCalibration(uint16_t CalibrationData)
{
	Write16(INA219_REG_CALIBRATION, CalibrationData);
}

uint16_t Ina219_getConfig(void)
{
	uint16_t result = Read16(INA219_REG_CONFIG);
	return result;
}

void Ina219_setConfig( uint16_t Config)
{
	Write16(INA219_REG_CONFIG, Config);
}

/*
 * Calibrate for 32V and 2A max.
 * Set ADC resolution to 12 bits.
 * */
void Ina219_Calibrate(void)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
	             INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
	             INA219_CONFIG_SADCRES_12BIT_1S_532US |
	             INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219_calibrationValue = 4096;
	ina219_currentDivider_mA = 10; // Current LSB = 100uA per bit (1000/100 = 10)
	ina219_powerMultiplier_mW = 2; // Power LSB = 1mW per bit (2/1)

	Ina219_setCalibration(ina219_calibrationValue);
	Ina219_setConfig(config);
}



uint8_t Ina219_Init(void)
{
	ina219_currentDivider_mA = 0;
	ina219_powerMultiplier_mW = 0;

	uint8_t ina219_isReady = HAL_I2C_IsDeviceReady(&INA219_I2C, INA219_ADDRESS , 3, 2);

	if(ina219_isReady == HAL_OK)
	{

		Ina219_Reset();
		Ina219_Calibrate();

		return 1;
	}

	else
	{
		return 0;
	}
}
