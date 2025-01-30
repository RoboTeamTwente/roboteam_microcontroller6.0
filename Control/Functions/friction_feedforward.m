function [out] = friction_feedforward(wheelRefs, rho, theta, omega)
%FRICTION_FEEDFORWARD Motor-level friction feedforward
addpath("Functions/Ported/");
load("frictionFeedForwardDetailed.mat");
s.dampingfriction = tempVariable;
s.robotParameters.robotVersion = '2024';
[s] = robotParameters(s);
out(1) = wheelFeedforward(s, wheelRefs(1), rho, theta, omega, "wheel1");
out(2) = wheelFeedforward(s, wheelRefs(2), rho, theta, omega, "wheel2");
out(3) = wheelFeedforward(s, wheelRefs(3), rho, theta, omega, "wheel3");
out(4) = wheelFeedforward(s, wheelRefs(4), rho, theta, omega, "wheel4");


% vw_max_round_to_rotational = rho / robot_radius;
% c = [1.0472, -1.0472, -2.3562, 2.3562];
% param3 = [-0.764611677882548, -2.33703565345706, -1.00311434719396, 4.16457002728926];
% z_translation = detailed_fit_eval(theta, 1.0, c, 0.46, 2.0626, param3, 1.23);
% ref_sign = sign(wheelRefs);
% gamma = min([0.5 - 0.5 * cos(pi .* abs(omega / vw_max_round_to_rotational)), 1.0]);
% if abs(omega) > vw_max_round_to_rotational
%     gamma = cast(1, 'single');
% end
% out = ref_sign.*((1 - gamma) .* z_translation + gamma .* 0.3);
end

