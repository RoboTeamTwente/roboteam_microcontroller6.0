function [out] = friction_feedforward(wheelRefs, rho, theta, omega, radius_robot)
%FRICTION_FEEDFORWARD Motor-level friction feedforward based on the work
%from 2023/2024
% Each row corresponds to a wheel
params = [0.487679493914719,0.035811727826830,-0.903990540061869,1.265865298506564;0.362439663999906,0.036702678870859,-2.033990278346956,1.036757957843577;0.400408293666698,0.034616181149416,-0.993340223619706,1.244729721334767;0.373047227302758,0.036516068519141,4.438567112212430,1.057087869495094];
params(:,2) = params(:,2)*180/pi;
c = [1.047197551196598;-1.047197551196598;-2.356194490192345;2.356194490192345];
% The same for all wheels
b = 0.0175*180/pi;
% The detailed fit eval for each wheel
z_posminconst = [detailedFitEval(theta, b, c(1), params(1,:));
    detailedFitEval(theta, b, c(2), params(2,:));
    detailedFitEval(theta, b, c(3), params(3,:));
    detailedFitEval(theta, b, c(4), params(4,:));];

% Possibly replace z_posminconst with the 4th parameter of the right sign
wheelsign = sign(wheelRefs);
z_sign = sign(z_posminconst);
eq_signs = wheelsign == z_sign;
z_posminconst_fixed = z_posminconst.*eq_signs + params(:,4).*not(eq_signs).*wheelsign;

% Gamma, same for all wheels
vw_max_round_to_rotational = rho/radius_robot;
gamma = 0.5-0.5*single(cos(pi*  abs(omega/vw_max_round_to_rotational)));
if abs(omega) > vw_max_round_to_rotational
    gamma = single(1.0);
end
if gamma > 1
    gamma = single(1.0);
end

% Final output voltage calculation
out = ((1-gamma)*z_posminconst_fixed + gamma*wheelsign);
out = single(out);
end

