function [y] = posminconstEval(x,b,c,d)
    y = sineEval(x,d,b,c);
    y(y > 0) = d;
    y(y <= 0) = -d;
end

