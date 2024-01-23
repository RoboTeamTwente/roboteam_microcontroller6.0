
#ifndef UTILS_CONTROL_UTIL_H_
#define UTILS_CONTROL_UTIL_H_

#include <math.h>
#include <stdbool.h>

///////////////////////////////////////////////////// DEFINITIONS

// System
#define TIME_DIFF 0.01F 		// time difference due to 100Hz frequency
#define WIRELESS_RX_COUNT 4000  // count after which wireless should go to timeout after last packet. Multiply with period base (62.5 us) to get to the time in seconds.


struct PIDstruct{
	float kP;			// The gain of the proportional action 
	float kI;			// The gain of the integrating action
	float kD;			// The gain fo the deriving action
	float I;			// The integral of this PID
	float prev_e;		// The previous error
	float timeDiff;		// The time difference due to 100Hz frequency
	float minOutput;	// Not being used at this moment. The minimal output of this PID
	float maxOutput;	// Not being used at this moment. The maximal output of this PID
	float ramp;			// Not being used at this moment. The maximal change of this PID value
	float prev_PID;		// The previous PID value
} static PIDdefault = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, TIME_DIFF, -1000000, 1000000, 1000000, 0};

typedef struct PIDstruct PIDvariables;

#endif /* UTILS_CONTROL_UTIL_H_ */

