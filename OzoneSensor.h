/*!
 * @file OzoneSensor.h
 * @brief Simple I2C driver for Ozone Sensor
 * @license The MIT License (MIT)
 * @author Rob Tipping
 * @version V0.1
 * @date 28/12/2022
 * @url
 */
#ifndef __OzoneSensor_H__
#define __OzoneSensor_H__

#include "stm32L0xx_hal.h" // Needed for I2C

#define           OZONE_ADDRESS_0           0x70	// A0=0, A1=0
#define           OZONE_ADDRESS_1           0x71	// A0=1, A1=0
#define           OZONE_ADDRESS_2           0x72	// A0=0, A1=1
#define           OZONE_ADDRESS_3           0x73	// A0=1, A1=1

#define           MEASURE_MODE_AUTOMATIC    0x00           ///< active  mode
#define           MEASURE_MODE_PASSIVE      0x01           ///< passive mode
#define           AUTO_READ_DATA            0x00           ///< auto read ozone data
#define           PASSIVE_READ_DATA         0x01           ///< passive read ozone data

// passive mode only works if registers 3 & 4 are set to 1
#define           MODE_REGISTER             0x03           ///< mode register
#define           SET_PASSIVE_REGISTER      0x04           ///< read ozone data register
#define           AUTO_DATA_HIGE_REGISTER   0x09           ///< AUTO data high eight bits
#define           AUTO_DATA_LOW_REGISTER    0x0A           ///< AUTO data Low  eight bits
#define           PASS_DATA_HIGE_REGISTER   0x07           ///< AUTO data high eight bits
#define           PASS_DATA_LOW_REGISTER    0x08           ///< AUTO data Low  eight bits


typedef struct{
	I2C_HandleTypeDef *i2cHandle;
	uint16_t value;

}OZONE;


//Initialisation
uint8_t OZONE_Initialise(OZONE *dev, I2C_HandleTypeDef *i2cHandle);



//Read Data
HAL_StatusTypeDef OZONE_ReadOzoneData(OZONE *dev);


//low level functions
HAL_StatusTypeDef OZONE_ReadRegister(OZONE *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef OZONE_ReadRegisters(OZONE *dev, uint8_t reg, uint8_t *data, uint8_t length);

HAL_StatusTypeDef OZONE_WriteRegister(OZONE *dev, uint8_t reg, uint8_t *data);

#endif
