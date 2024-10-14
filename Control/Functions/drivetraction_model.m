function output_force = drivetraction_model(relvel, absvel, whangle, decaying_friction, linear_friction, subwheel_frequency)
%DRIVETRACTION_MODEL Models the wacky interaction between the wheel and the
%ground.
% Subwheel frequency in subwheels/rotation

fmax = decaying_friction;

% A fictional approximation of what the friction might be like
friction_coeffiction = fmax - relvel/(fmax + relvel) + linear_friction;
% A term to very vaguely model the effect of the subwheels
subwheel_modulation = 1 + (0.1*(absvel)/(1 + absvel))*sin(whangle*subwheel_frequency);
output_force = friction_coeffiction*subwheel_modulation*relvel;
end

