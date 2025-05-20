function processModelReferences(modelName)
    % Load the model if not already open
    if ~bdIsLoaded(modelName)
        load_system(modelName);
    end

    % Find all Model Reference blocks
    modelRefs = find_system("MotorInteraction", 'RegExp','on','BlockType','SubSystem','ReferencedSubsystem', '.')

    % Process each referenced model
    for i = 1:length(modelRefs)
        refModel = get_param(modelRefs{i}, 'ModelName');
        fprintf('Processing: %s → %s\n', modelRefs{i}, refModel);
        
        % Recursively process the referenced model
        processModelReferences(refModel);
    end
end