function [feedforwardVoltage] = wheelFeedforward(s,wheelRef, rho, theta, omega, wheel)
    

    useDetailedFit = true;

    wheelList = s.robotParameters.wheelList;

    % the_specific_fit_used = 'offsetSineFit4wheels';
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{1}).d = 0;
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{2}).d = 0;
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{3}).d = 0;
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{4}).d = 0;
    % the_specific_fit_used = 'offsetposminconstFit4wheels';
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{1}).a = 0;
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{2}).a = 0;
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{3}).a = 0;
    % s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{4}).a = 0;
    if useDetailedFit
        % b_fix  = [0.0175    0.0175    0.0175    0.0175];
        % c_fix  = [1.0472   -1.0472   -2.3562    2.3562];
        % params = [0.4223    0.3305    0.3462    0.3132;
        %           0.0360    0.0372    0.0344    0.0362;
        %          -0.9870   -2.0363   -1.0402    4.3223;
        %           1.0937    0.9747    1.0741    0.9691];
        the_specific_fit_used = 'detailedFit';
    else
        the_specific_fit_used = 'offsetposminconstsineFit4wheels';
    end
    

    vw_max_round_to_rotational = s.dampingfriction.vw_max_round_to_rotational_scaling*(rho/s.robotParameters.radius_robot);

    z_rotational = s.dampingfriction.rotation_feedforward_value(wheel);
    if useDetailedFit
        params = s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).params;
        params(2) = params(2)*180/pi;
        b = s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).b*180/pi;
        z_posminconst = detailedFitEval(theta,b,s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).c,params);
    else
        z_posminconst = posminconstsineEval(theta,s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).a,s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).b,s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).c,s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).d);
    end

    if wheelRef > 0
        wheel_velocity_larger_than_zero = 1;
    else
        wheel_velocity_larger_than_zero = 0;
    end

    z_posminconst_sign_fixed = z_posminconst;
    if wheel_velocity_larger_than_zero
        z_rotational_sign_fixed =  1*z_rotational;
        % SPECULATVE, MAY OR MAY NOT BE WHAT REALLY HAPPENS. JUST A GUESS.
        % PLEASE DO A PROPER TEST TO SEE THE ACTUAL BEHAVIOUR, MAYBE THE
        % SINE BEHAVIOUR NEEDS TO BE STRETCHED INSTEAD OF THE CONSTANT PART
        % BEING EXTENDED WHERE IT WOULD OTHERWISE DROP BELOW ZERO.
        if z_posminconst < 0
            if useDetailedFit
                z_posminconst_sign_fixed = s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).params(4);
            else
                z_posminconst_sign_fixed = s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).d;
            end
            
            % _________________________________
        end
    else
        z_rotational_sign_fixed = -1*z_rotational;
        % SPECULATVE, MAY OR MAY NOT BE WHAT REALLY HAPPENS. JUST A GUESS.
        % PLEASE DO A PROPER TEST TO SEE THE ACTUAL BEHAVIOUR, MAYBE THE
        % SINE BEHAVIOUR NEEDS TO BE STRETCHED INSTEAD OF THE CONSTANT PART
        % BEING EXTENDED WHERE IT WOULD OTHERWISE RISE ABOVE ZERO.
        if z_posminconst > 0
            if useDetailedFit
                z_posminconst_sign_fixed = -s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).params(4);
            else
                z_posminconst_sign_fixed = -s.dampingfriction.fit.translational.(the_specific_fit_used).(wheelList{wheel}).d;
            end
            
        end
    end
    
    gamma = 0.5-0.5*cos(pi*  abs(omega/vw_max_round_to_rotational)   );
    if abs(omega) > vw_max_round_to_rotational
        gamma = 1;
    end
    % gamma = 1/(1+exp(-6*(     abs(omega/vw_max_round_to_rotational)     -0.5)));
    % gamma = 1/(1+exp(-10*(     abs(omega/vw_max_round_to_rotational)     -0.5)));
    % gamma = sqrt(abs(omega/vw_max_round_to_rotational));
    % gamma = abs(omega/vw_max_round_to_rotational)^2;
    % gamma = abs(omega/vw_max_round_to_rotational);
    if gamma > 1
        gamma = 1;
    end
    
    % gamma = 0;
    % gamma = 1;
    feedforwardVoltage = ((1-gamma)*z_posminconst_sign_fixed + gamma*z_rotational_sign_fixed);
end

