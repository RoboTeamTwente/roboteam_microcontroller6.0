clc, clear, close all

set(0,'defaultfigurewindowstyle','docked')
addpath('Functions')
addpath('CustomFittingFunctions')



unwrapAngle = true;

load('frictionFeedForwardDetailed.mat');
s.dampingfriction = tempVariable;
identifiedDamping = 0.04;
% 2*24*0.001367311

s.robotParameters.robotVersion = '2024';

%% System parameters/constants
[s] = robotParameters(s);

%% Plotting: Properties
[sLineProp] = customLineProperties(s);

acceleration_angle = deg2rad(180);
acceleration_magnitude = 2.0;
% angular_acceleration = -pi
angular_acceleration = 0;
% m = 2.581
m = 2.632;
inertia = 0;
rho = 2.0;
theta = deg2rad(0);
vw = 0;





RotMat = @(angle) [cos(angle) -sin(angle);
                   sin(angle)  cos(angle)];
accVecTranslational = RotMat(acceleration_angle)*(acceleration_magnitude*[1;0]);
accVec = [accVecTranslational; angular_acceleration];
% F = m*a | M = I*alpha
Fvec = [m;m;inertia].*accVec;

% Transfrom body force to wheel forces
[Fw1divR,Fw2divR,Fw3divR,Fw4divR] = body2wheels(Fvec(1),Fvec(2),Fvec(3),s.robotParameters.phi,s.robotParameters.theta,s.robotParameters.radius_robot,s.robotParameters.radius_wheel);
    % Did not give force but F/Rw, so multiply by Rw to get F
    Fw1 = Fw1divR*s.robotParameters.radius_wheel;
    Fw2 = Fw2divR*s.robotParameters.radius_wheel;
    Fw3 = Fw3divR*s.robotParameters.radius_wheel;
    Fw4 = Fw4divR*s.robotParameters.radius_wheel;
FwaccVec = [Fw1;Fw2;Fw3;Fw4];
% M = Fr
MwaccVec = FwaccVec * s.robotParameters.radius_wheel;
Mfricperwheel = [0;0;0;0];
motorTorque = MwaccVec + Mfricperwheel;
% Kt*i = T
motorCurrent = motorTorque / s.robotParameters.Kt;
motorVoltageMassFF = motorCurrent * s.robotParameters.R;



vu = rho * cos(theta);
vv = rho * sin(theta);

[w1,w2,w3,w4] = body2wheels(vu,vv,vw,s.robotParameters.phi,s.robotParameters.theta,s.robotParameters.radius_robot,s.robotParameters.radius_wheel);
wheelRefVec = [w1,w2,w3,w4].';
for j = 1:4
    wheelRef = wheelRefVec(j);

    feedforwardVoltageDamping(j,1) = wheelRef*identifiedDamping;
    feedforwardVoltageFriction(j,1) = wheelFeedforward(s,wheelRef, rho, rad2deg(theta), vw, j);
end

% STILL MISSING FEEDBACK VOLTAGE:
appliedMotorVoltageFF = motorVoltageMassFF + feedforwardVoltageFriction + feedforwardVoltageDamping
% L*(di/dt) + Ri = V - wK
% Assuming L is small (not a good assumption since di/dt can be nig):
% i = (V - wK)/R
appliedMotorCurrentFF = (appliedMotorVoltageFF - wheelRefVec.*s.robotParameters.Kt)/s.robotParameters.R

% Inductance might be important, ask Csongor for reasonable di/dt value in
% motor
% I might have the inductance direction wrong
% And it assumes the backEMF is already present which it will have once it
% has its reference velocity, however, that is of course not the case since
% it will start from some/0 velocity, so the applied current is
% underestimated
voltageFeedback = 2*24*0.001367311*wheelRefVec;
inductance = 0.000802;
appliedMotorCurrentFF2Temp = (voltageFeedback + (appliedMotorVoltageFF - motorVoltageMassFF) - wheelRefVec.*s.robotParameters.Kt)/s.robotParameters.R
didt = appliedMotorCurrentFF2Temp./(1/1000);
appliedMotorCurrentFF2 = (-inductance*didt + voltageFeedback + (appliedMotorVoltageFF - motorVoltageMassFF) - wheelRefVec.*s.robotParameters.Kt)/s.robotParameters.R;




















































