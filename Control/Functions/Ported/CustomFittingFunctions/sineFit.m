function [a_best,b_best,c_best] = sineFit(x,y,abc)
    % Sine fit: a*sin(b*x+c)

    p = 2;

    n_pointsInRange = 50;
    if abc(1) == -1
        a_range = linspace(0, max(y)*2, n_pointsInRange);
    else
        a_range = abc(1);
    end
    if abc(2) == -1
        b_range = linspace(0, (2*pi)/360, n_pointsInRange);
    else
        b_range = abc(2);
    end
    if abc(3) == -1
        c_range = linspace(-pi, pi, n_pointsInRange);
    else
        c_range = abc(3);
    end
    
    errorSumBest = inf;

    % ia_best = 1;
    % ib_best = 1;
    % ic_best = 1;

    for ia = 1:length(a_range)
        for ib = 1:length(b_range)
            for ic = 1:length(c_range)
                [y_fit] = sineEval(x,a_range(ia),b_range(ib),c_range(ic));
                errorSum = sum(abs(y-y_fit).^p);
                if errorSumBest > errorSum
                    errorSumBest = errorSum;
                    ia_best = ia;
                    ib_best = ib;
                    ic_best = ic;
                end
            end
        end
    end
    
    a_best = a_range(ia_best);
    b_best = b_range(ib_best);
    c_best = c_range(ic_best);

end

