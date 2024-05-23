#ifndef _VPC_SENSOR_H_
#define _VPC_SENSOR_H_

#include "main.h"
#include <stdbool.h>

#define SDA_ADDRESS 0x4a
#define CONFIG_ADDRESS 0x00
#define CAL_ADDRESS 0x05
#define VOLTAGE_ADDRESS 0x02
#define CURRENT_ADDRESS 0x04
#define POWER_ADDRESS 0x03
#define SHUNT_CAL 2048 // Used for the voltage and current conversion, reference to 8.1.2


extern bool VPC_write_OK;
extern bool VPC_read_OK;


void init_VPC_sensor();

void VPC_write(uint8_t register, uint8_t *data);

uint16_t VPC_read(uint8_t reg_toRead);

float VPC_getVoltage();

float VPC_getCurrent();

float VPC_getPower();

#endif /* _VPC_SENSOR_H_ */