function output_force = drivetraction_linear(relvel, absvel, whangle, decaying_friction, linear_friction, subwheel_frequency)
%DRIVETRACTION_MODEL Models the wacky interaction between the wheel and the
%ground.
% Subwheel frequency in subwheels/rotation

output_force = linear_friction*relvel;
end

