function y = desaturator(turn, move, limit)
%DESATURATOR Combines and desaturates the inputs without any bias
y = move + turn;
util_factor = max(abs(y))/limit;
if util_factor > 1.0
    y = y / util_factor;
end
end

