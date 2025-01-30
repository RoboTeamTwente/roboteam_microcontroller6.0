function [w1,w2,w3,w4] = body2wheels(vu,vv,vw,phi,theta,Rr,Rw)
    % D = [-sin(phi)   cos(phi)   Rr;
    %      -sin(phi)  -cos(phi)   Rr;
    %      sin(theta) -cos(theta) Rr;
    %      sin(theta)  cos(theta) Rr];
    D = [cos(phi)       sin(phi)   Rr;
         -cos(phi)      sin(phi)   Rr;
         -cos(theta)    -sin(theta) Rr;
         cos(theta)     -sin(theta) Rr];
    w1 = ( D(1,1)*vu + D(1,2)*vv + D(1,3)*vw )/(Rw);
    w2 = ( D(2,1)*vu + D(2,2)*vv + D(2,3)*vw )/(Rw);
    w3 = ( D(3,1)*vu + D(3,2)*vv + D(3,3)*vw )/(Rw);
    w4 = ( D(4,1)*vu + D(4,2)*vv + D(4,3)*vw )/(Rw);
end

