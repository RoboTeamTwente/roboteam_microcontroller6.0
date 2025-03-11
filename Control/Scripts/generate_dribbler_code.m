function generate_dribbler_code()
controllerModel = 'DribblerController';

if(~bdIsLoaded(controllerModel))
    open_system(controllerModel);
end

slbuild(controllerModel);
coder.report.generate(controllerModel);
copyfile("DribblerController_ert_rtw/DribblerController.c", "../Core/Src/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/DribblerController.h" ,"../Core/Inc/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/rtwtypes.h", "../Core/Inc/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/DribblerController_data.c", "../Core/Src/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/rt_nonfinite.c", "../Core/Src/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/rt_nonfinite.h", "../Core/Inc/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/DribblerController_types.h", "../Core/Inc/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/rtGetNaN.h", "../Core/Inc/dribbler_board/Control")
copyfile("DribblerController_ert_rtw/rtGetNaN.c", "../Core/Src/dribbler_board/Control")
end
