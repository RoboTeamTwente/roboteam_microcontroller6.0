function [a_best,b_best,c_best] = sineFit4wheels(x,y,abc)
    % Sine fit: a*sin(b*x+c)

    p = 2;

    n_pointsInRange = 50;

    if abc(1,1) == -1
        a_range = linspace(0, max(y,[],"all")*2, n_pointsInRange);
    else
        a_range = abc(1,1);
    end
    b = abc(2,:);
    c = abc(3,:);
        
    errorSumBest = inf;

    % ia_best = 1;
    % ib_best = 1;
    % ic_best = 1;

    for ia = 1:length(a_range)
        [y_fit(:,1)] = sineEval(x(:,1),a_range(ia),b(1),c(1));
        [y_fit(:,2)] = sineEval(x(:,2),a_range(ia),b(2),c(2));
        [y_fit(:,3)] = sineEval(x(:,3),a_range(ia),b(3),c(3));
        [y_fit(:,4)] = sineEval(x(:,4),a_range(ia),b(4),c(4));
        errorSum = sum(abs(y-y_fit).^p,"all");
        if errorSumBest > errorSum
            errorSumBest = errorSum;
            ia_best = ia;
        end
    end
    
    a_best = a_range(ia_best)*ones(1,size(x,2));
    b_best = b;
    c_best = c;
    

end

