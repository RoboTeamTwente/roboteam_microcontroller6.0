% For motor limits, look at datasheet in repo
pwm_limit = 0.2;
nominal_voltage = 24; % V
torque_limit = 0.488*pwm_limit;    % Nm
fs = 100; % [Hz] Sample frequency of the controller
Ts = 1/fs; % [s] Sample time of the controller
