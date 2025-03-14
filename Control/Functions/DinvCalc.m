function Dinv = DinvCalc(front_angle, back_angle)
Dinv = zeros(2, 4);
div_a = cos(front_angle)^2 * cos(back_angle)^2;
Dinv(1, :) = [0.5*cos(cos(front_angle/div_a)), -0.5*cos(cos(front_angle/div_a)), -0.5*cos(cos(back_angle/div_a)), 0.5*cos(cos(front_angle/div_a))];
div_b = sin(back_angle) + sin(front_angle);
Dinv(2, :) = [0.5*(1/div_b), 0.5*(1/div_b), -0.5*(1/div_b), -0.5*(1/div_b)];
