function [s] = robotParameters(s)
    switch s.robotParameters.robotVersion
        case '2023'
            s.robotParameters.Kt                    = 0.0335; % Motor torque constant
            s.robotParameters.R                     = 1.03; % Motor resistance

            s.robotParameters.SPEED_CONSTANT        = 2*pi/60 * 285;
            s.robotParameters.MAX_PWM               = 6000;
            s.robotParameters.MAX_VOLTAGE           = 24;
            s.robotParameters.WHEEL_GEAR_RATIO      = 2.65;
            s.robotParameters.OMEGAtoPWM            = (1/s.robotParameters.SPEED_CONSTANT)*(s.robotParameters.MAX_PWM/s.robotParameters.MAX_VOLTAGE)*s.robotParameters.WHEEL_GEAR_RATIO;
            s.robotParameters.PWMtoVoltage          = (s.robotParameters.MAX_VOLTAGE)/(s.robotParameters.MAX_PWM);

            s.robotParameters.radius_robot          = 0.081; % This is the radius between the wheel contact point and centre of the robot
            s.robotParameters.radius_wheel          = 0.028;
            s.robotParameters.theta                 = 60/180*pi;
            s.robotParameters.phi                   = 30/180*pi;

            s.robotParameters.wheelList             = {'wheel1';'wheel2';'wheel3';'wheel4'};
        case '2024'
            s.robotParameters.Kt                    = 0.0328; % Motor torque constant
            s.robotParameters.R                     = 1.07; % Motor resistance

            s.robotParameters.SPEED_CONSTANT        = 2*pi/60 * 291;
            s.robotParameters.MAX_PWM               = 1;
            s.robotParameters.MAX_VOLTAGE           = 24;
            s.robotParameters.WHEEL_GEAR_RATIO      = 1;
            s.robotParameters.OMEGAtoPWM            = 22.1979;
            s.robotParameters.PWMtoVoltage          = 0.004;
            s.robotParameters.OMEGAtoPWM            = (1/s.robotParameters.SPEED_CONSTANT)*(s.robotParameters.MAX_PWM/s.robotParameters.MAX_VOLTAGE)*s.robotParameters.WHEEL_GEAR_RATIO;
            s.robotParameters.PWMtoVoltage          = (s.robotParameters.MAX_VOLTAGE)/(s.robotParameters.MAX_PWM);

            s.robotParameters.radius_robot          = 0.081; % This is the radius between the wheel contact point and centre of the robot
            s.robotParameters.radius_wheel          = 0.028;
            s.robotParameters.theta                 = 45/180*pi;
            s.robotParameters.phi                   = 30/180*pi;

            s.robotParameters.wheelList             = {'wheel1';'wheel2';'wheel3';'wheel4'};
        otherwise
            error("Enter a valid robot version, so either '2023' or '2024'")

    end
    
end

