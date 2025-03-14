function [frictionTorqueMotorSineConstantFitted] = ffFrictionCurve(x,wheelNumber,wheelFrictionConstantPart,a1,b1,c1,phi,theta,Rr,Rw)

for i = 1:length(x)
    [w1,w2,w3,w4] = body2wheels(-sind(x(i)),cosd(x(i)),0,phi,theta,Rr,Rw);
    wList = [w1, w2, w3, w4];
    if wList(wheelNumber) > 0
        frictionTorqueMotorSineConstantFitted(i) = a1*sin(b1*x(i)+c1) + wheelFrictionConstantPart;
    else
        frictionTorqueMotorSineConstantFitted(i) = a1*sin(b1*x(i)+c1) - wheelFrictionConstantPart;
    end
end

end

