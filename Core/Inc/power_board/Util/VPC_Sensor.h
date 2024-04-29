#ifndef _VPC_SENSOR_H_
#define _VPC_SENSOR_H_

#include "main.h"

#define SDA_ADDRESS 0x4a
#define CONFIG_ADDRESS 0x00
#define CAL_ADDRESS 0x05
#define VOLTAGE_ADDRESS 0x02
#define CURRENT_ADDRESS 0x04
#define POWER_ADDRESS 0x03
#define SHUNT_CAL 2048 // Used for the voltage and current conversion, reference to 8.1.2


void init_VPC_sensor();

void VPC_write(uint8_t register, uint8_t *data);

uint16_t VPC_read(uint8_t reg_toRead);

float getVoltage();

float getCurrent();

float getPower();

#endif /* _VPC_SENSOR_H_ */