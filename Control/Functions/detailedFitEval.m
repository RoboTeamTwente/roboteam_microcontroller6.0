function [y] = detailedFitEval(x,b,c,param)
    y = NaN(length(x),1);
    y_sign = sin(b*x+c);
    for i = 1:length(x)
        if y_sign(i) >= 0
            y(i) = param(1)*sin(param(2)*x(i) + param(3)) + param(4);
        else
            y(i) = -(param(1)*sin(param(2)*x(i) + param(3)) + param(4));
        end
    end
end

