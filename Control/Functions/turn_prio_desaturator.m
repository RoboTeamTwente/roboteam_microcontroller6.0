function y = turn_prio_desaturator(turn, move, limit)
%TURN_PRIO Desaturation function that prioritizes turning over moving
turn_utilization = max(abs(turn))/limit;
y = max([(1.0 - turn_utilization), 0.0]) * move + turn / max([turn_utilization, 1.0]);
end

