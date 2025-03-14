function [b_best,c_best,d_best] = posminconstFit(x,y,bcd)

    p = 2;

    n_pointsInRange = 50;

    if bcd(1) == -1
        b_range = linspace(0, (2*pi)/360, n_pointsInRange);
    else
        b_range = bcd(1);
    end
    if bcd(2) == -1
        c_range = linspace(-pi, pi, n_pointsInRange);
    else
        c_range = bcd(2);
    end
    if bcd(3) == -1
        d_range = linspace(0, max(y)*2, n_pointsInRange);
    else
        d_range = bcd(3);
    end
    
    errorSumBest = inf;

    % id_best = 1;
    % ib_best = 1;
    % ic_best = 1;

    for ib = 1:length(b_range)
        for ic = 1:length(c_range)
            for id = 1:length(d_range)
                [y_fit] = posminconstEval(x,b_range(ib),c_range(ic),d_range(id));
                errorSum = sum(abs(y-y_fit).^p);
                if errorSumBest > errorSum
                    errorSumBest = errorSum;
                    
                    ib_best = ib;
                    ic_best = ic;
                    id_best = id;
                end
            end
        end
    end
    
    b_best = b_range(ib_best);
    c_best = c_range(ic_best);
    d_best = d_range(id_best);
end

