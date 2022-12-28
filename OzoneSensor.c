/*!
 * @file OzoneSensor.c
 * @brief Simple I2C driver for Ozone Sensor
 * @license The MIT License (MIT)
 * @author Rob Tipping
 * @version V0.1
 * @date 28/12/2022
 * @url
 */
#include "OzoneSensor.h"

#define	OZONE_ADDRESS	 (OZONE_ADDRESS_3 << 1) // Define sensor address and bit shift by 1


//Initialise
uint8_t OZONE_Initialise(OZONE *dev, I2C_HandleTypeDef *i2cHandle)
{
	dev->i2cHandle = i2cHandle;
	dev->value = 0;



	//Handshake returns 1 if error with device.
	uint8_t regData[3] = {0x00};

	if (OZONE_ReadRegisters( dev, 0x00, regData, 3) != HAL_OK)
		return 1;

	if (regData[0] != (OZONE_ADDRESS >> 1))
		return 1;

	if (regData[1] != 0xDF)
			return 1;

	if (regData[2] != 0x10)
			return 1;

	//Set Up  mode
	regData[0] = MEASURE_MODE_PASSIVE; // 0 = Auto // 1 = Passive
	OZONE_WriteRegister(dev, MODE_REGISTER, regData);


	return 0;
}


HAL_StatusTypeDef OZONE_ReadOzoneData(OZONE *dev)
{
	uint8_t regData[2] = {PASSIVE_READ_DATA, 0};
	OZONE_WriteRegister(dev, SET_PASSIVE_REGISTER, regData);
	HAL_StatusTypeDef status = OZONE_ReadRegisters( dev, PASS_DATA_HIGE_REGISTER, regData, 2);
	dev->value = (regData[0] << 8) + regData[1];

	return status;
}


//Low-Level Functions
HAL_StatusTypeDef OZONE_ReadRegister(OZONE *dev, uint8_t reg, uint8_t *data)
{
	return HAL_I2C_Mem_Read( dev->i2cHandle, OZONE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef OZONE_ReadRegisters(OZONE *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
	return HAL_I2C_Mem_Read( dev->i2cHandle, OZONE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);
}

HAL_StatusTypeDef OZONE_WriteRegister(OZONE *dev, uint8_t reg, uint8_t *data)
{
	return HAL_I2C_Mem_Write( dev->i2cHandle, OZONE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}
