function discretize_plant(ts, options)
arguments
    ts {mustBePositive}
    options.model (1,1) string = "Plant"
    options.STF (1,1) boolean = true
end
%DISCRETIZE_PLANT Recursively creates discretized versions of model and the
%referenced submodels it contains.
% TS: sample time
% MODEL: Model to produce discretized version of, defaults to "Plant"

proj = currentProject;
model = options.model;
STF = options.STF;

model_d = model+"_d"
model_fname = "Subsystems/"+model+".slx";
model_d_fname = "Subsystems/"+model_d+".slx";

copyfile(model_fname, model_d_fname, 'f');
addFile(proj, model_d_fname);
load_system(model_d);
ref_models = find_system(model_d, 'RegExp','on','BlockType','SubSystem','ReferencedSubsystem', '.');
sldiscmdl(model_d, ts, {'all', 'parammask', 'current', 'off'});

% Extract unique submodels
subfiles = [""];
for i=1:length(ref_models)
    file = get_param(ref_models(i), 'ReferencedSubSystem');
    if sum(subfiles == file)==0
        parts = split(file, '.');
        subfiles = [subfiles, parts(1)];
    end
end
subfiles = subfiles(2:end);

% Discretize unique submodels
for i=1:length(subfiles)
    discretize_plant(ts, subfiles(i));
end

% Change the referenced submodels to their new discretized versions
for i=1:length(ref_models)
    file = get_param(ref_models(i), 'ReferencedSubSystem');
    parts = split(file, '.');
    set_param(string(ref_models(i)), "ReferencedSubSystem", parts(1)+"_d");
end

% Finalize the job
save_system(model_d);
close_system(model_d);

end

