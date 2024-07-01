/* 
The dribbler control of RoboTeam Twente
Created by Chris Krommendijk


*/

#include "dribbler_ctrl.h"
#include "dribbler.h"
#include "dribbler_board.h"
datactrl dribblerCtrl= {
    .antiWindup_speed=0.2f, // [A]
    .kp_speed=20.5f,
    .ki_speed=0.1f,
    .antiWindup_current=22.0f, // [V]
    .kp_current=30.0f,
    .ki_current=0.05f,
    .current_offset=0.0f, //[A]
    .speed_desired=200.0f // [rad/s] max 500 rad/s
};
float iTerm_speed=0;
float iTerm_current=0;
float output_speedLoop=0;
float output_currentLoop=0;
float measured_speed=0;
float measured_current=0;
int sign;
float output_speedEMA=0.0f;

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
            output_currentLoop=-23.0f;

        dribbler_SetSpeed(output_currentLoop/24.0f, 1);
        }
    else
        {
            output_speedLoop=0.0f;
            output_currentLoop=0.0f;
            dribbler_SetSpeed(output_currentLoop, 1);
        }
}
}
void FilterDribbler()
{


 if(!ballsensor_hasBall())
 {
    // Will be used to determine the current offset with the use of an Exponential moving average filter
    // EMA filter: y(i)=alpha*x(i)+(1-alpha)*y(i-1)
    // Current offset will only be determined when the motor is off
     dribblerCtrl.current_offset=0.25f*dribbler_getCurrent()+ (1-0.25f)*dribblerCtrl.current_offset;
     return;
 }
// Determination of meausered current
float output_speedEMA=0.25f*output_speedLoop+(1-0.25f)*output_speedEMA;
if (output_speedEMA>0.0f)
{
    sign=1;
}
else if (output_speedEMA<0.0f)
{
    sign=-1;
}
else
{
    sign=0;
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
 
measured_speed= (backEmfDribbler * motorBackEmfConstantInv);
}

