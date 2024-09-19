function [x] = limit_angle(u)
%LIMIT_ANGLE Limits the angle in a range of [-pi, pi]. Based on function in
%original C codebase.
x = mod(u+pi, 2*pi);
if x < 0.0
    x = x + 2*pi;
end
x = x - pi;
end

