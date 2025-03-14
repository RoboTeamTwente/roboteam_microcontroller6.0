function [b_best,c_best,d_best] = posminconstFit4wheels(x,y,bcd)

    p = 2;

    n_pointsInRange = 50;

    b = bcd(1,:);
    c = bcd(2,:);
    if bcd(3,1) == -1
        d_range = linspace(0, max(y,[],"all")*2, n_pointsInRange);
    else
        d_range = bcd(3,1);
    end
        
    errorSumBest = inf;

    % id_best = 1;
    % ib_best = 1;
    % ic_best = 1;

    for id = 1:length(d_range)
        [y_fit(:,1)] = posminconstEval(x(:,1),b(1),c(1),d_range(id));
        [y_fit(:,2)] = posminconstEval(x(:,2),b(2),c(2),d_range(id));
        [y_fit(:,3)] = posminconstEval(x(:,3),b(3),c(3),d_range(id));
        [y_fit(:,4)] = posminconstEval(x(:,4),b(4),c(4),d_range(id));
        errorSum = sum(abs(y-y_fit).^p,"all");
        if errorSumBest > errorSum
            errorSumBest = errorSum;
            id_best = id;
        end
    end

    b_best = b;
    c_best = c;
    d_best = d_range(id_best)*ones(1,size(x,2));

end

