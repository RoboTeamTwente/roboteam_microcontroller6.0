function [out] = friction_feedforward(wheelRefs, rho, theta, omega, robot_radius)
%FRICTION_FEEDFORWARD Motor-level friction feedforward
vw_max_round_to_rotational = rho / robot_radius;
c = [1.0472, -1.0472, -2.3562, 2.3562];
param3 = [-0.764611677882548, -2.33703565345706, -1.00311434719396, 4.16457002728926];
z_translation = detailed_fit_eval(theta, 1.0, c, 0.46, 2.0626, param3, 1.23);
ref_sign = sign(wheelRefs);
gamma = min([0.5 - 0.5 * cos(pi .* abs(omega / vw_max_round_to_rotational)), 1.0]);
if abs(omega) > vw_max_round_to_rotational
    gamma = cast(1, 'single');
end
out = ref_sign.*((1 - gamma) .* z_translation + gamma .* 0.3);
end

