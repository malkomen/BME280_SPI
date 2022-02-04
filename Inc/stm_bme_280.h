#ifndef STM_BME_280_H_
#define STM_BME_280_H_

#include "stm32f4xx_hal.h"
#include <string.h>
#include <math.h>
/*
 *  USE EXAMPLE:
 *  BME280_ReadedData_t BME280_Data;
 * 	BME280_Initial(BME280_STANDBY_MS_1000, BME280_FILTER_X4,
		BME280_TEMP_OVERSAMPLING_X4, BME280_PRES_OVERSAMPLING_X2,
		BME280_HUM_OVERSAMPLING_X1, BME280_MODE_NORMAL);
 *  BME280_Data.temp = BME280_ReadTemperature();
 *	BME280_Data.pres = BME280_ReadPressure();
 *	BME280_Data.humi = BME280_ReadHumidity();
 *	BME280_Data.alti = BME280_ReadAltitude(kSEA_LEVEL_PRESURE_PA);
 */
#define kSEA_LEVEL_PRESURE_HPA  (1013.25)
#define kSEA_LEVEL_PRESURE_PA	(1013250)
//------------------------------------------------
#define LED_GPIO_PORT 		GPIOA
#define LED_PIN 			GPIO_PIN_5
#define LED_ON 				HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET)
#define LED_OFF 			HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET)
#define LED_TGL 			HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN)
//------------------------------------------------
static inline uint16_t convert16BitData(uint16_t data)
{
	return ((((data)>>8)&0xff)|(((data)<<8)&0xff00));
}
//------------------------------------------------
static inline uint32_t convert24BitData(uint32_t data)
{
	return ((((data)>>16)&0x000000ff)|((data)&0x0000ff00)|(((data)<<16)&0x00ff0000));
}
//------------------------------------------------
/* Registers */
#define BME280_ADDRESS 			0xEC //BME280 I2C ADDRES (0x76<<1)
#define BME280_REG_ID 			0xD0 //BME280 ID REGISTER
#define BME280_ID 				0x60 //BME280 I2C ID
#define BME280_REG_SOFTRESET 	0xE0 //BME280 SOFT RESET REGISTER
#define BME280_SOFTRESET_VALUE 	0xB6 //BME280 SOFT RESET VALUE
#define BME280_REG_CTRL_HUM 	0xF2 // Humidity measure control register
#define BME280_REGISTER_STATUS 	0xF3 //BME280 STATUS REGISTER
#define BME280_REG_CTRL_MEAS 	0xF4 // Control register pressure and temperature measure
#define BME280_STATUS_MEASURING 0X08 //Running conversion
#define BME280_STATUS_IM_UPDATE 0X01 //NVM data copying
#define BME280_REG_CONFIG 		0xF5 // Configuration register
#define BME280_REGISTER_PRESSUREDATA 	0xF7
#define BME280_REGISTER_TEMPDATA 		0xFA
#define BME280_REGISTER_HUMIDDATA 		0xFD
//------------------------------------------------
#define BME280_REGISTER_DIG_T1 0x88
#define BME280_REGISTER_DIG_T2 0x8A
#define BME280_REGISTER_DIG_T3 0x8C
#define BME280_REGISTER_DIG_P1 0x8E
#define BME280_REGISTER_DIG_P2 0x90
#define BME280_REGISTER_DIG_P3 0x92
#define BME280_REGISTER_DIG_P4 0x94
#define BME280_REGISTER_DIG_P5 0x96
#define BME280_REGISTER_DIG_P6 0x98
#define BME280_REGISTER_DIG_P7 0x9A
#define BME280_REGISTER_DIG_P8 0x9C
#define BME280_REGISTER_DIG_P9 0x9E
#define BME280_REGISTER_DIG_H1 0xA1
#define BME280_REGISTER_DIG_H2 0xE1
#define BME280_REGISTER_DIG_H3 0xE3
#define BME280_REGISTER_DIG_H4 0xE4
#define BME280_REGISTER_DIG_H5 0xE5
#define BME280_REGISTER_DIG_H6 0xE7
//------------------------------------------------
#define BME280_STBY_MSK 	0xE0
//------------------------------------------------
#define BME280_FILTER_MSK 	0x1C
//------------------------------------------------
#define BME280_OSRS_T_MSK 	0xE0
#define BME280_OSRS_P_MSK	0x1C
#define BME280_OSRS_H_MSK 	0x07
//------------------------------------------------
#define BME280_MODE_MSK 	0x03
//------------------------------------------------
typedef enum BME280_status{
	BME280_OK 		= 0,
	BME280_ERROR 	= 1
}BME280_status;

typedef enum BME280_standby_Time_Enum{
	BME280_STANDBY_MS_0_5  = 0x00,
	BME280_STANDBY_MS_10   = 0xC0,
	BME280_STANDBY_MS_20   = 0xE0,
	BME280_STANDBY_MS_62_5 = 0x20,
	BME280_STANDBY_MS_125  = 0x40,
	BME280_STANDBY_MS_250  = 0x60,
	BME280_STANDBY_MS_500  = 0x80,
	BME280_STANDBY_MS_1000 = 0xA0
}BME280_standby_Time_E;

typedef enum BME280_filter_Enum {
	BME280_FILTER_OFF = 0x00,
	BME280_FILTER_X2  = 0x04,
	BME280_FILTER_X4  = 0x08,
	BME280_FILTER_X8  = 0x0C,
	BME280_FILTER_X16 = 0x10
}BME280_filter_E;

typedef enum BME280_overSamplingTemp_Enum{
	BME280_TEMP_OVERSAMPLING_SKIPPED = 0x00,
	BME280_TEMP_OVERSAMPLING_X1 = 0x20,
	BME280_TEMP_OVERSAMPLING_X2 = 0x40,
	BME280_TEMP_OVERSAMPLING_X4 = 0x60,
	BME280_TEMP_OVERSAMPLING_X8 = 0x80,
	BME280_TEMP_OVERSAMPLING_X16 = 0xA0
}BME280_overSamplingTemp_E;

typedef enum BME280_overSamplingHum_Enum{
	BME280_HUM_OVERSAMPLING_SKIPPED = 0x00,
	BME280_HUM_OVERSAMPLING_X1 = 0x01,
	BME280_HUM_OVERSAMPLING_X2 = 0x02,
	BME280_HUM_OVERSAMPLING_X4 = 0x03,
	BME280_HUM_OVERSAMPLING_X8 = 0x04,
	BME280_HUM_OVERSAMPLING_X16 = 0x05
}BME280_overSamplingHum_E;

typedef enum BME280_overSamplingPres_Enum{
	BME280_PRES_OVERSAMPLING_SKIPPED = 0x00,
	BME280_PRES_OVERSAMPLING_X1 = 0x04,
	BME280_PRES_OVERSAMPLING_X2 = 0x08,
	BME280_PRES_OVERSAMPLING_X4 = 0x0C,
	BME280_PRES_OVERSAMPLING_X8 = 0x10,
	BME280_PRES_OVERSAMPLING_X16 = 0x14
}BME280_overSamplingPres_E;

typedef enum BME280_mode_Enum{
	BME280_MODE_SLEEP = 0x00,
	BME280_MODE_FORCED_1 = 0x01,
	BME280_MODE_FORCED_2 = 0x02,
	BME280_MODE_NORMAL = 0x03
}BME280_mode_E;

typedef struct{
  uint16_t dig_T1;
  int16_t dig_T2;
  int16_t dig_T3;
} BME280_Temp;

typedef struct{
  uint16_t dig_P1;
  int16_t dig_P2;
  int16_t dig_P3;
  int16_t dig_P4;
  int16_t dig_P5;
  int16_t dig_P6;
  int16_t dig_P7;
  int16_t dig_P8;
  int16_t dig_P9;
} BME280_Pres;

typedef struct{
  uint8_t dig_H1;
  int16_t dig_H2;
  uint8_t dig_H3;
  int16_t dig_H4;
  int16_t dig_H5;
  int8_t dig_H6;
} BME280_Humid;

typedef struct{
	uint8_t sensorID;
	BME280_standby_Time_E standbyTime;
	BME280_filter_E filter;
	BME280_overSamplingTemp_E tempOversampl;
	BME280_overSamplingPres_E presOversampl;
	BME280_overSamplingHum_E humOversampl;
	BME280_mode_E sensMode;
	uint32_t measurementStatus;
	uint8_t tempOn:1;
	uint8_t presOn:1;
	uint8_t humiOn:1;
}BME280_Settings;

typedef struct{
  BME280_Temp tempValue;
  BME280_Pres presureValue;
  BME280_Humid humidValue;
} BME280_CalibData;

typedef struct{
	float temp;
	float pres;
	float humi;
	float alti;
}BME280_ReadedData_t;
//------------------------------------------------
BME280_status BME280_Initial(BME280_standby_Time_E standbyTime, BME280_filter_E filter,
					BME280_overSamplingTemp_E tempOversampl, BME280_overSamplingPres_E presOversampl,
					BME280_overSamplingHum_E humOversampl, BME280_mode_E sensMode, uint16_t timeout);
float BME280_ReadTemperature(void);
float BME280_ReadPressure(void);
float BME280_ReadHumidity(void);
float BME280_ReadAltitude(float seaLevel);
float BME280_ReadAltitudeDefSeaLevel(void);
//------------------------------------------------
#endif /* STM_BME_280_H_ */
