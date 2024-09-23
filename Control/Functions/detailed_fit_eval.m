function [out] = detailed_fit_eval(theta, b, c, param1, param2, param3, param4)
%DETAILED_FIT_EVAL Friction Feedforward curve-fit
y_sign = sign(sin(b .* theta + c));
out = y_sign .* (param1 .* sin(param2 .* theta + param3) + param4);
end

