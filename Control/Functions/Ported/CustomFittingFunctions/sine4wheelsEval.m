function [y] = sine4wheelsEval(x,a,b,c)
    for i = 1:length(x)
        switch x(2,i)
            case 1
                y(1,i) = a*sin(b(1)*x(1,i)+c(1));
            case 2
                y(1,i) = a*sin(b(2)*x(1,i)+c(2));
            case 3
                y(1,i) = a*sin(b(3)*x(1,i)+c(3));
            case 4
                y(1,i) = a*sin(b(4)*x(1,i)+c(4));
        end
    end      
end

