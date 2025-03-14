function [y] = posminconstsine4wheelsEval(x,a,b,c,d)
    for i = 1:length(x)
        switch x(2,i)
            case 1
                y(1,i) = posminconstEval(x(1,i),b(1),c(1),d) + sineEval(x(1,i),a,b(1),c(1));
            case 2
                y(1,i) = posminconstEval(x(1,i),b(2),c(2),d) + sineEval(x(1,i),a,b(2),c(2));
            case 3
                y(1,i) = posminconstEval(x(1,i),b(3),c(3),d) + sineEval(x(1,i),a,b(3),c(3));
            case 4
                y(1,i) = posminconstEval(x(1,i),b(4),c(4),d) + sineEval(x(1,i),a,b(4),c(4));
        end
    end
end

