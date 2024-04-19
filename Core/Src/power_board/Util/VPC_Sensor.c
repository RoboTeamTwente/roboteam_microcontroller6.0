#include "VPC_Sensor.h"

uint8_t tempPayload[2] = {0,0};
uint8_t config[2] = {0b01000011,0b11100111}; //CONFIG_ADDRESS is a 16 bit register, reference to 7.6.1.1

// Reference to Sec 7.5.2 for writing
void init_VPC_sensor(){
    VPC_write(CONFIG_ADDRESS, config);
    uint8_t data[2];
    data[0] = SHUNT_CAL & 0xff;
    data[1] = SHUNT_CAL >> 0;
    VPC_write(CAL_ADDRESS, data);
}

/*
    To read from the sensor we first have to write, 
    as the value we get back is from the last written register
*/

void VPC_write(uint8_t reg_toWrite, uint8_t *data){
    if (HAL_I2C_Mem_Write(&hi2c1, (uint16_t) (SDA_ADDRESS << 1), reg_toWrite, sizeof(reg_toWrite), data, 2, 50) != HAL_OK){
        //LOG failure to write 
    }
}

uint16_t VPC_read(uint8_t reg_toRead){
    if (HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(SDA_ADDRESS << 1) | 0x01, reg_toRead, 1, tempPayload, 2, 50) != HAL_OK){
        // LOG failure to read 
    }
    return (tempPayload[0] << 8) | tempPayload[1];;
}

float getVoltage(){
    VPC_write(VOLTAGE_ADDRESS, 0x00);
    HAL_Delay(10);
    uint16_t reading = VPC_read(VOLTAGE_ADDRESS);
    return (float) (reading) * 0.0016;
}

float getCurrent(){
    VPC_write(CURRENT_ADDRESS, 0x00);
    HAL_Delay(10);
    return ((float) (VPC_read(CURRENT_ADDRESS)) * 0.0005f);
}

float getPower(){
    VPC_write(POWER_ADDRESS, 0x00);
    HAL_Delay(10);
    return ((float) (VPC_read(POWER_ADDRESS)) *0.0005f);
}