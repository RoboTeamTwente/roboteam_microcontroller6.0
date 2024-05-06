#ifndef __voltage_H
#define __voltage_H

#include "main.h"
#include "tim_util.h"

#define NR_OF_SAMPLES 10

void voltage_Init();
void voltage_Read();
float voltage_Get();

#endif /* __voltage_H */
