function [y] = posminconst4wheelsEval(x,b,c,d)
    for i = 1:length(x)
        switch x(2,i)
            case 1
                y_forsign = sineEval(x(1,i),d,b(1),c(1));
                if y_forsign > 0
                    y(1,i) = d;
                else
                    y(1,i) = -d;
                end
            case 2
                y_forsign = sineEval(x(1,i),d,b(2),c(2));
                if y_forsign > 0
                    y(1,i) = d;
                else
                    y(1,i) = -d;
                end
            case 3
                y_forsign = sineEval(x(1,i),d,b(3),c(3));
                if y_forsign > 0
                    y(1,i) = d;
                else
                    y(1,i) = -d;
                end
            case 4
                y_forsign = sineEval(x(1,i),d,b(4),c(4));
                if y_forsign > 0
                    y(1,i) = d;
                else
                    y(1,i) = -d;
                end
        end
    end
end

