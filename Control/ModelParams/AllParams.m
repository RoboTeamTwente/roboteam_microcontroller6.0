% Body params
body.inertia = 0.1; % kg/m^2
body.mass = 2.5;    % kg

% Sensor params
gyro.noise = 0.1;
accel.noise = 2;

% Wheel position angles
wheels.back_angle = deg2rad(45);  % rad
wheels.front_angle = deg2rad(30); % rad
wheels.angles = [wheels.front_angle, pi - wheels.front_angle, ...
    pi + wheels.back_angle, 2*pi - wheels.back_angle];
wheels.distance = 0.0810; % m
wheels.radius = 0.027; % m
wheels.inertia = 1e-3; % kg/m^2
% Wheel friction params
wheels.strafetraction = 0.1; % Ns/m
wheels.lineardrivetraction = 100; % Ns/m
wheels.staticdrivetraction = 100; % Ns/m
wheels.subwheels = 25;
% Kinematic transformation matrices
wheels.Dmat = [cos(wheels.front_angle), sin(wheels.front_angle); 
    -cos(wheels.front_angle), sin(wheels.front_angle); 
    -cos(wheels.back_angle), -sin(wheels.back_angle); 
    cos(wheels.back_angle), -sin(wheels.back_angle)];
wheels.Dforce = 1./wheels.Dmat;
wheels.Dinv = DinvCalc(wheels.front_angle, wheels.back_angle);
wheels.force2body = [-sin(wheels.angles(1)-0.5*pi), -sin(wheels.angles(2)-0.5*pi), -sin(wheels.angles(3)-0.5*pi), -sin(wheels.angles(4)-0.5*pi); cos(wheels.angles(1)-0.5*pi), cos(wheels.angles(2)-0.5*pi), cos(wheels.angles(3)-0.5*pi), cos(wheels.angles(4)-0.5*pi)];
wheels.slipvec = null([wheels.force2body; 1 1 1 1]); % Could in theory be used to reduce slip in velocity estimate
% Using d = d - (dot(d, 0.5*Slipvec))*0.5*Slipvec'

% Motor params
motor.resistance = single(1.07); % Ohm
motor.gyration = single(0.0328); % Nm/A
motor.friction = single(1e-4);   % Nms/rad
motor.inductance = single(0.805e-3); % H
motor.tmax = single(155); % deg C

% Control params
ctrl.pwm_limit = single(1.0);
ctrl.nominal_voltage = single(24); % V
% ctrl.imax = ctrl.nominal_voltage*ctrl.pwm_limit/motor.resistance; % A
ctrl.imax = single(4.5); % A
ctrl.taumax = motor.gyration*ctrl.imax;    % Nm
ctrl.fmax = ctrl.taumax/wheels.radius;  % N
ctrl.fs = 100; % [Hz] Sample frequency of the controller
ctrl.Ts = 1/ctrl.fs; % [s] Sample time of the controller
Ts = ctrl.Ts;