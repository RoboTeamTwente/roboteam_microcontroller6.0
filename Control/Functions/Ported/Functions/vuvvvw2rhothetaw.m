function [rho,theta,w] = vuvvvw2rhothetaw(vu,vv,vw)
    % Note: theta is only w.r.t. the local body frame
    rho = sqrt((vu).^2 + (vv).^2);
    theta = atan2(vv, vu);
    w = vw;
end

