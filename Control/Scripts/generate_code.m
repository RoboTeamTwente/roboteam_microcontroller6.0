function generate_code()
controllerModel = 'Controller';

if(~bdIsLoaded(controllerModel))
    open_system(controllerModel);
end

slbuild(controllerModel);
coder.report.generate(controllerModel);
copyfile("Controller_ert_rtw\Controller.c", "../Core/Src/top_board/Control")
copyfile("Controller_ert_rtw\Controller.h" ,"../Core/Inc/top_board/Control")
copyfile("Controller_ert_rtw\rtwtypes.h", "../Core/Inc/top_board/Control")
copyfile("Controller_ert_rtw\Controller_data.c", "../Core/Src/top_board/Control")

end

