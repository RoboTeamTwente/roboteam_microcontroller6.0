/* 
The dribbler control of RoboTeam Twente
Created by Chris Krommendijk


*/

#include "dribbler_ctrl.h"
#include "dribbler.h"
#include "dribbler_board.h"
datactrl dribblerCtrl= {
    .antiWindup_speed=0.15f, // [A]
    .kp_speed=0.00625f,
    .ki_speed=0.0125f,
    .antiWindup_current=14.0f, 
    .kp_current=12.5f,
    .ki_current=2.1f,
    .current_offset=0.0f, //[A]
    .speed_desired=450.0f, // [rad/s] max 500 rad/s
    .ReachedSpeed=false
};
float iTerm_speed=0;
float iTerm_current=0;
float output_speedLoop=0;
float output_currentLoop=0;
float measured_speed=0;
float measured_current=0;
int sign;
float output_currentEMAPrevious=0.0f;
float measured_speedPrevious=0.0f;
void DribblerController()
{
 // Motor speed controller
 if(dribblerCommand.dribblerOn)
 {
    if(ballsensor_hasBall())
    {
        float Error_speed=dribblerCtrl.speed_desired-measured_speed;
        float pError_speed = dribblerCtrl.kp_speed * Error_speed;
        float iError_speed = dribblerCtrl.ki_speed * Error_speed;
        float iTerm_speedNew = iTerm_speed+ iError_speed;
        if (iTerm_speedNew > dribblerCtrl.antiWindup_speed)
        {
            iTerm_speedNew = dribblerCtrl.antiWindup_speed;
        }
        else if (iTerm_speedNew < -dribblerCtrl.antiWindup_speed)
        {
            iTerm_speedNew = -dribblerCtrl.antiWindup_speed;
        }

        iTerm_speed= iTerm_speedNew;

        output_speedLoop = pError_speed + iTerm_speed;
        if (output_speedLoop>dribblerCtrl.current_limit)
        {
            output_speedLoop=dribblerCtrl.current_limit;
        }
        else if (output_speedLoop<-dribblerCtrl.current_limit)
        {
            output_speedLoop=-dribblerCtrl.current_limit;
        }

        // Current controller
        float Error_current = output_speedLoop - measured_current;
        float pError_current = dribblerCtrl.kp_current * Error_current;
        float iError_current = dribblerCtrl.ki_current * Error_current;
        float iTerm_currentNew = iTerm_current + iError_current;
        if (iTerm_currentNew > dribblerCtrl.antiWindup_current)
        {
            iTerm_currentNew = dribblerCtrl.antiWindup_current;
        }
        else if (iTerm_currentNew < -dribblerCtrl.antiWindup_current)
        {
            iTerm_currentNew = -dribblerCtrl.antiWindup_current;
        }
        iTerm_current = iTerm_currentNew;
        output_currentLoop = pError_current + iTerm_current;
        if (output_currentLoop>23.9f)
            output_currentLoop=23.9f;
        else if (output_currentLoop<-23.9f)
            output_currentLoop=-23.9f;

        dribbler_SetSpeed(output_currentLoop/24.0f, 1);
        }
    else if (!ballsensor_hasBall())
        {
            output_speedLoop=0.0f;
            output_currentLoop=0.0f;
            dribbler_SetSpeed(output_currentLoop, 1);
        }
}
}
void FilterDribbler()
{

// Determination of meausered current
float output_currentEMA=0.5f*output_currentLoop+(1.0f-0.5f)*output_currentEMAPrevious;
output_currentEMAPrevious=output_currentEMA;
if (output_currentEMA>0.0f)
{
    sign=1;
}
else if (output_currentEMA<0.0f)
{
    sign=-1;
}
else
{
    sign=1;
}
measured_current=sign*(dribbler_getCurrent()-dribblerCtrl.current_offset); 
 
// speed estimator or speed from encoder 

// Tigers uses the Average voltage however there control loop runs at 1KHz and the filtering loop is done at 40KHz
// We do it both at 1KHz so we don't use the average 
// to Do implement when encoder is available use encoder other wise use estimator
float motorResistance = 22.8f; // [Ohm] (5.84 Ohm)
float motorBackEmfConstantInv = 28.06f; // [rad/(V*s)] is the speed constant 268 rpm/V = 28.06 rad/(V*s) in the datasheet

float restiveLossDribbler = (motorResistance * measured_current);
float backEmfDribbler = output_currentLoop - restiveLossDribbler;
float errorPercentage = 0.05f; 

measured_speed= 1.0f*(backEmfDribbler * motorBackEmfConstantInv)+measured_speedPrevious*(0.0f);
measured_speedPrevious=measured_speed;
if (measured_speed>(1-errorPercentage)*dribblerCtrl.speed_desired && measured_speed<(1+errorPercentage)*dribblerCtrl.speed_desired)
{
    dribblerCtrl.ReachedSpeed=true;
}
else 
{
    dribblerCtrl.ReachedSpeed=false;
}

if(!ballsensor_hasBall())
 {
    // Will be used to determine the current offset with the use of an Exponential moving average filter
    // EMA filter: y(i)=alpha*x(i)+(1-alpha)*y(i-1)
    // Current offset will only be determined when the motor is off
     dribblerCtrl.current_offset=0.5f*dribbler_getCurrent()+ (1-0.5f)*dribblerCtrl.current_offset;
 }
}

