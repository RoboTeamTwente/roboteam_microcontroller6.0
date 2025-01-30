function [sLineProp] = customLineProperties(s)
    sLineProp.TitleFontName = 'Oswald';
    sLineProp.TitleFontSize = 25;
    sLineProp.TitleColor = '#5A1C74';
    sLineProp.LegendFontName = 'Roboto';
    sLineProp.LegendFontSize = 12;
    sLineProp.LegendFontWeight = 'normal';
    sLineProp.AxesFontName = 'Roboto';
    sLineProp.AxesFontSize = 12;
    sLineProp.AxesFontWeight = 'normal';

    % sLineProp.LineWidth = [3 2];

    sLineProp.colorListWheels = {"#0072BD", "#D95319", "#EDB120", "#7E2F8E"};
    sLineProp.colourChoice = {	'#0072BD'; % 1 blue
                	            '#4DBEEE'; % 2 blue light
                                '#D95319'; % 3 orange
                                '#FFEE58'; % 4 orange light
                                '#2E7D32'; % 5 green
                                '#66BB6A'; % 6 green light
                                '#9575CD'; % 7 purple
                                '#D1C4E9'; % 8 purple light "#9575CD"
                                '#78909C'; % 9 grey
                                'r',
                                'g',
                                'b',
                                'c',
                                'm',
                                '#0072BD'; % 1 blue
                	            '#4DBEEE'; % 2 blue light
                                '#D95319'; % 3 orange
                                '#FFEE58'; % 4 orange light
                                '#2E7D32'; % 5 green
                                '#66BB6A'; % 6 green light
                                '#9575CD'; % 7 purple
                                '#D1C4E9'; % 8 purple light "#9575CD"
                                '#78909C'; % 9 grey
                                'r',
                                'g',
                                'b',
                                'c',
                                'm'};
    
    set(0,'defaultfigurewindowstyle','docked')
    % set(0,'defaultfigurewindowstyle','normal')
    %{
        % https://nl.mathworks.com/help/matlab/creating_plots/default-property-values.html
        % get(0,'default')
        % get(0,'factory')
        sLineProp.defaultPropertiesSet = fieldnames(get(0,'default'));
        sLineProp.defaultPropertiesSetMannually = {sLineProp.defaultPropertiesSet{3:end}}.';
    %}
end

