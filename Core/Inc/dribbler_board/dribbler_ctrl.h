#include <stdint.h>



typedef struct _PICtrl
{
	int32_t setpoint; // S12.0

	int32_t kp; // S7.10
	int32_t ki; // S5.13

	int32_t iTerm; // S12.12

	int32_t output; // S12.0

	int32_t outputMin;
	int32_t outputMax;

	int32_t antiJitter; // S12.0
	int32_t antiJitterReciprocal; // S0.12

	uint8_t overload;
	uint8_t enabled;
} PICtrl;
void PICtrlInit(PICtrl* pPI, int32_t kp, int32_t ki, int32_t outputMin, int32_t outputMax);
void PICtrlEnable(PICtrl* pPI, uint8_t enable);
void PICtrlUpdate(PICtrl* pPI, int32_t measured);
void PICtrlSetpoint(PICtrl* pPI, int32_t setpoint);
void PICtrlSetAntiJitter(PICtrl* pPI, int32_t antiJitter_0);

typedef struct _datactrl
{
		uint8_t hallOnly;

		int32_t currentD;
		int32_t currentQ;

		int32_t speed;

		int32_t avgVoltageDQ[2]; // final voltage set by controllers
        
        float current_limit;
} datactrl;

extern datactrl dribblerCtrl;