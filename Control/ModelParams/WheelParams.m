wheel_back_angle = deg2rad(45);  % rad
wheel_front_angle = deg2rad(30); % rad
wheel_distance = 0.0810; % m
wheel_radius = 0.027; % m
wheel_inertia = 1e-3; % kg/m^2

wheel_strafetraction = 0.1; % Ns/m
wheel_lineardrivetraction = 1; % Ns/m
wheel_staticdrivetraction = 100; % Ns/m
wheel_subwheels = 25;

Dmat = [cos(wheel_front_angle), sin(wheel_front_angle); -cos(wheel_front_angle), sin(wheel_front_angle); -cos(wheel_back_angle), -sin(wheel_back_angle); cos(wheel_back_angle), -sin(wheel_back_angle)];
Dforce = 1./Dmat;
Dinv = DinvCalc(wheel_front_angle, wheel_back_angle);
wheel_angles = deg2rad([wheel_front_angle, pi - wheel_front_angle, pi + wheel_back_angle, 2*pi - wheel_back_angle]);