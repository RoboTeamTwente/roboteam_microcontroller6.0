Ts = 1e-2;
Fs = 1/Ts;

mechanical_timeconstant = 30e-3; % [s] time constant of the ball-less dribbler bar

% Speed estimation
speedpassfreq = 1/mechanical_timeconstant;
speedstopfreq = speedpassfreq+0.05*Fs;

% Speed control
dribbling_speed = 200; % [rad/s] desired dribbler bar speed when the ball is detected
max_current = 3; % [A]
