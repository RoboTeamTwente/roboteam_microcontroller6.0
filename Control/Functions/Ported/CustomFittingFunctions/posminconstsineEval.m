function [y] = posminconstsineEval(x,a,b,c,d)
    y = posminconstEval(x,b,c,d) + sineEval(x,a,b,c);
end

