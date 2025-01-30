function [vel_u,vel_v,vel_w,angle_ref] = global2local(vel_x,vel_y,vel_w,angle_ref,angle_robot_now)
	vel_u =  cos(angle_robot_now) .* vel_x + sin(angle_robot_now) .* vel_y;
	vel_v = -sin(angle_robot_now) .* vel_x + cos(angle_robot_now) .* vel_y;
    vel_w = vel_w;
	angle_ref = angle_ref;
end

