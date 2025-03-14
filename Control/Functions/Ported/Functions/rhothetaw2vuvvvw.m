function [vel_x,vel_y,angularVelocity,angle] = rhothetaw2vuvvvw(rho,theta,angularVelocity,angle)
	vel_x = rho .* cos(theta);
	vel_y = rho .* sin(theta);
	angularVelocity = angularVelocity;
	angle = angle;
end

