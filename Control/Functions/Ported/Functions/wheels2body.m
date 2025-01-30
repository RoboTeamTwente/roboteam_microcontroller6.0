function [vu,vv,vw] =  wheels2body(w1,w2,w3,w4,phi,theta,Rr,Rw)
    % Dpinv = 0.5*[-1/(sin(theta)+sin(phi)),                  -1/(sin(theta)+sin(phi)),                    1/(sin(theta)+sin(phi)),                       1/(sin(theta)+sin(phi));
    %               (cos(phi))/((cos(theta))^2+(cos(phi))^2), -(cos(phi))/((cos(theta))^2+(cos(phi))^2),  -(cos(theta))/((cos(theta))^2+(cos(phi))^2),    (cos(theta))/((cos(theta))^2+(cos(phi))^2);
    %               (sin(theta))/(sin(theta)+sin(phi)),        (sin(theta))/(sin(theta)+sin(phi)),         (sin(phi))/(sin(theta)+sin(phi)),              (sin(phi))/(sin(theta)+sin(phi))];
    Dpinv = 0.5*[(cos(phi))/( cos(phi)^2 + cos(theta)^2 ),  -(cos(phi))/( cos(phi)^2 + cos(theta)^2 ),  -(cos(theta))/( cos(phi)^2 + cos(theta)^2 ),    (cos(theta))/( cos(phi)^2 + cos(theta)^2 );
                 (1)/( sin(phi) + sin(theta) ),             (1)/( sin(phi) + sin(theta) ),              -(1)/( sin(phi) + sin(theta) ),                 -(1)/( sin(phi) + sin(theta) );
                 (sin(theta))/( sin(phi) + sin(theta) ),    (sin(theta))/( sin(phi) + sin(theta) ),     (sin(phi))/( sin(phi) + sin(theta) ),           (sin(phi))/( sin(phi) + sin(theta) )];
    vList = Dpinv*(Rw*[w1,w2,w3,w4].');
    vu = vList(1,:);
    vv = vList(2,:);
    vw = vList(3,:)/Rr;
end

