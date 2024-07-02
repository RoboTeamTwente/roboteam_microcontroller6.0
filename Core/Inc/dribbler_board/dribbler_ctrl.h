#include <stdint.h>
#include <stdbool.h> // Include the header file that defines the "bool" type



typedef struct _datactrl
{
	float current_limit;
	float speed_desired; // [rad/s] motor speed

	float antiWindup_speed;
	float antiWindup_current;

	float ki_speed;
	float kp_speed;
	float ki_current;
	float kp_current;

	float filter_Current;
	float filter_Speed;

	float current_offset;
	bool ReachedSpeed;

} datactrl; // Rename the conflicting variable name to 'datactrl_t'

extern datactrl dribblerCtrl;
void DribblerController();
void FilterDribbler(void);