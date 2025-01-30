function [a_best,b_best,c_best,d_best] = posminconstsineFit(x,y,abcd)

    p = 2;

    n_pointsInRange = 50;

    if abcd(1) == -1
        a_range = linspace(0, max(y)*2, n_pointsInRange);
    else
        a_range = abcd(1);
    end
    if abcd(2) == -1
        b_range = linspace(0, (2*pi)/360, n_pointsInRange);
    else
        b_range = abcd(2);
    end
    if abcd(3) == -1
        c_range = linspace(-pi, pi, n_pointsInRange);
    else
        c_range = abcd(3);
    end
    if abcd(4) == -1
        d_range = linspace(0, max(y)*2, n_pointsInRange);
    else
        d_range = abcd(4);
    end
    
    errorSumBest = inf;

    % ia_best = 1;
    % ib_best = 1;
    % ic_best = 1;
    % id_best = 1;

    for ia = 1:length(a_range)
        for ib = 1:length(b_range)
            for ic = 1:length(c_range)
                for id = 1:length(d_range)
                    [y_fit] = posminconstsineEval(x,a_range(ia),b_range(ib),c_range(ic),d_range(id));
                    errorSum = sum(abs(y-y_fit).^p);
                    if errorSumBest > errorSum
                        errorSumBest = errorSum;
                        
                        ia_best = ia;
                        ib_best = ib;
                        ic_best = ic;
                        id_best = id;
                    end
                end
            end
        end
    end
    
    a_best = a_range(ia_best);
    b_best = b_range(ib_best);
    c_best = c_range(ic_best);
    d_best = d_range(id_best);
end

