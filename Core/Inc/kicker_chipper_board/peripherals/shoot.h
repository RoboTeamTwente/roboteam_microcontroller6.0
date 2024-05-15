/* Description: Makes the robot chip or kick
 *
 * Instructions:
 * 1) First the robot's needs to charge
 * 2) when that has happened the kick or chip command can be executed
 *
 * Extra functions:
 *
 * Notes:
 * As opposed to other functionalities, shoot uses a callback() instead of an update(). This is because shoot
 * only needs to update when kicking is needed, while for example the velocity control needs to ran constantly. It would be
 * very inefficient to update shoot every cycle. The timer for the callback is set internally. The time after which another
 * callback should be made differs per shootState. While charging and kicking, updating has to be done frequently and while the
 * robot is ready to kick, updating can be done less frequent.
*/

#ifndef __shoot_H
#define __shoot_H

#include "gpio_util.h"
#include "tim_util.h"
#include <stdbool.h>
#include "voltage.h"

///////////////////////////////////////////////////// STRUCTS

typedef enum{
	shoot_Ready,
	shoot_Charging,
	shoot_Shooting,
	shoot_Off
}shoot_states;

typedef enum{
	shoot_Kick,
	shoot_Chip
}shoot_types;


///////////////////////////////////////////////////// DEFINITIONS


#define MIN_KICK_TIME 1.0 			// minimum time [ms] period of kicking
#define MAX_KICK_TIME 25.0 			// maximum time [ms] period of kicking
#define MIN_CHIP_TIME 10 			// minimum time [ms] period of chipping
#define MAX_CHIP_TIME 100 			// maximum time [ms] period of chipping
#define TIMER_FREQ 10000 			// frequency [Hz] of TIM16  (Clock frequency divided by prescaler)
#define READY_CALLBACK_FREQ 10 		// frequency [Hz] of callback when shootState is Ready
#define CHARGING_CALLBACK_FREQ 1 	// frequency [Hz] of callback when shootState is Charging
#define SHOOTING_CALLBACK_FREQ 10 	// frequency [Hz] of callback when shootState is Shooting
#define OFF_CALLBACK_FREQ 1 		// frequency [Hz] of callback when shootState is Off
#define START_REGHARGE_VOLT 220		// voltage [V] capacitor should start charging back up again
#define MIN_VOLT_SHOOT 80			// minimum voltage [V] for kicking

///////////////////////////////////////////////////// PUBLIC FUNCTION DECLARATIONS

void shoot_Init();

void shoot_DeInit();

void shoot_Callback();

void shoot_Shoot(shoot_types type);

shoot_states shoot_GetState();

void shoot_SetPower(float input);

void shoot_StartCharging();

void shoot_DisableCharging();

#endif /* __shoot_H */