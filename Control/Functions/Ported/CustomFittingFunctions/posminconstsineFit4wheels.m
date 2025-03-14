function [a_best,b_best,c_best,d_best] = posminconstsineFit4wheels(x,y,abcd)

    p = 2;

    n_pointsInRange = 50;

    b = abcd(2,:);
    c = abcd(3,:);
    if abcd(1,1) == -1
        a_range = linspace(0, max(y,[],"all")*2, n_pointsInRange);
    else
        a_range = abcd(1,1);
    end
    if abcd(4,1) == -1
        d_range = linspace(0, max(y,[],"all")*2, n_pointsInRange);
    else
        d_range = abcd(4,1);
    end
        
    errorSumBest = inf;

    ia_best = 1;
    id_best = 1;
    ic_best = 1;

    for ia = 1:length(a_range)
        for id = 1:length(d_range)
            [y_fit(:,1)] = posminconstsineEval(x(:,1),a_range(ia),b(1),c(1),d_range(id));
            [y_fit(:,2)] = posminconstsineEval(x(:,2),a_range(ia),b(2),c(2),d_range(id));
            [y_fit(:,3)] = posminconstsineEval(x(:,3),a_range(ia),b(3),c(3),d_range(id));
            [y_fit(:,4)] = posminconstsineEval(x(:,4),a_range(ia),b(4),c(4),d_range(id));
            errorSum = sum(abs(y-y_fit).^p,"all");
            if errorSumBest > errorSum
                errorSumBest = errorSum;
                ia_best = ia;
                id_best = id;
            end
        end
    end

    a_best = a_range(ia_best)*ones(1,size(x,2));
    b_best = b;
    c_best = c;
    d_best = d_range(id_best)*ones(1,size(x,2));

end

