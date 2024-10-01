var dataJson = {"arch":{"ispc":true,"isunix":false,"ismac":false},"build":"Controller","ref":false,"files":[{"name":"ert_main.c","type":"source","group":"main","path":"C:\\Users\\Marij\\Documents\\GitHub\\roboteam_microcontroller6.0\\Control\\Controller_ert_rtw","tag":"","groupDisplay":"Main file","code":"/*\r\n * Academic License - for use in teaching, academic research, and meeting\r\n * course requirements at degree granting institutions only.  Not for\r\n * government, commercial, or other organizational use.\r\n *\r\n * File: ert_main.c\r\n *\r\n * Code generated for Simulink model 'Controller'.\r\n *\r\n * Model version                  : 1.89\r\n * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023\r\n * C/C++ source code generated on : Tue Oct  1 15:57:18 2024\r\n *\r\n * Target selection: ert.tlc\r\n * Embedded hardware selection: ARM Compatible->ARM Cortex-M\r\n * Code generation objectives:\r\n *    1. Execution efficiency\r\n *    2. RAM efficiency\r\n * Validation result: Not run\r\n */\r\n\r\n#include <stddef.h>\r\n#include <stdio.h>            /* This example main program uses printf/fflush */\r\n#include \"Controller.h\"                /* Model header file */\r\n\r\n/* Global variables used by function prototype control */\r\n\r\n/* '<Root>/WheelSpeeds' */\r\nstatic real32_T arg_Wheelspeeds[4] = { 0.0F, 0.0F, 0.0F, 0.0F };\r\n\r\n/* '<Root>/Gyro' */\r\nstatic real32_T arg_YawRate = 0.0F;\r\n\r\n/* '<Root>/Yaw' */\r\nstatic real32_T arg_Yaw = 0.0F;\r\n\r\n/* '<Root>/VelRef' */\r\nstatic real32_T arg_VelRef[2] = { 0.0F, 0.0F };\r\n\r\n/* '<Root>/YawRef' */\r\nstatic real32_T arg_YawRef = 0.0F;\r\n\r\n/* '<Root>/AccRef' */\r\nstatic real32_T arg_AccRef[2] = { 0.0F, 0.0F };\r\n\r\n/* '<Root>/YawRateRef' */\r\nstatic real_T arg_YawRateRef = 0.0;\r\n\r\n/* '<Root>/YawAccRef' */\r\nstatic real_T arg_YawAccRef = 0.0;\r\n\r\n/* '<Root>/Accelerometer' */\r\nstatic real_T arg_Accelerometer[2] = { 0.0, 0.0 };\r\n\r\n/* '<Root>/Motorefforts' */\r\nstatic real32_T arg_Motorefforts[4];\r\n\r\n/*\r\n * Associating rt_OneStep with a real-time clock or interrupt service routine\r\n * is what makes the generated code \"real-time\".  The function rt_OneStep is\r\n * always associated with the base rate of the model.  Subrates are managed\r\n * by the base rate from inside the generated code.  Enabling/disabling\r\n * interrupts and floating point context switches are target specific.  This\r\n * example code indicates where these should take place relative to executing\r\n * the generated code step function.  Overrun behavior should be tailored to\r\n * your application needs.  This example simply sets an error status in the\r\n * real-time model and returns from rt_OneStep.\r\n */\r\nvoid rt_OneStep(void);\r\nvoid rt_OneStep(void)\r\n{\r\n  static boolean_T OverrunFlag = false;\r\n\r\n  /* Disable interrupts here */\r\n\r\n  /* Check for overrun */\r\n  if (OverrunFlag) {\r\n    return;\r\n  }\r\n\r\n  OverrunFlag = true;\r\n\r\n  /* Save FPU context here (if necessary) */\r\n  /* Re-enable timer or interrupt here */\r\n  /* Set model inputs here */\r\n\r\n  /* Step the model */\r\n  Controller_step(arg_Wheelspeeds, arg_YawRate, arg_Yaw, arg_VelRef, arg_YawRef,\r\n                  arg_AccRef, arg_YawRateRef, arg_YawAccRef, arg_Accelerometer,\r\n                  arg_Motorefforts);\r\n\r\n  /* Get model outputs here */\r\n\r\n  /* Indicate task complete */\r\n  OverrunFlag = false;\r\n\r\n  /* Disable interrupts here */\r\n  /* Restore FPU context here (if necessary) */\r\n  /* Enable interrupts here */\r\n}\r\n\r\n/*\r\n * The example main function illustrates what is required by your\r\n * application code to initialize, execute, and terminate the generated code.\r\n * Attaching rt_OneStep to a real-time clock is target specific. This example\r\n * illustrates how you do this relative to initializing the model.\r\n */\r\nint_T main(int_T argc, const char *argv[])\r\n{\r\n  /* Unused arguments */\r\n  (void)(argc);\r\n  (void)(argv);\r\n\r\n  /* Initialize model */\r\n  Controller_initialize();\r\n\r\n  /* Attach rt_OneStep to a timer or interrupt service routine with\r\n   * period 0.01 seconds (base rate of the model) here.\r\n   * The call syntax for rt_OneStep is\r\n   *\r\n   *  rt_OneStep();\r\n   */\r\n  printf(\"Warning: The simulation will run forever. \"\r\n         \"Generated ERT main won't simulate model step behavior. \"\r\n         \"To change this behavior select the 'MAT-file logging' option.\\n\");\r\n  fflush((NULL));\r\n  while (1) {\r\n    /*  Perform application tasks here */\r\n  }\r\n\r\n  /* The option 'Remove error status field in real-time model data structure'\r\n   * is selected, therefore the following code does not need to execute.\r\n   */\r\n  return 0;\r\n}\r\n\r\n/*\r\n * File trailer for generated code.\r\n *\r\n * [EOF]\r\n */\r\n"},{"name":"Controller.c","type":"source","group":"model","path":"C:\\Users\\Marij\\Documents\\GitHub\\roboteam_microcontroller6.0\\Control\\Controller_ert_rtw","tag":"","groupDisplay":"Model files","code":"/*\r\n * Academic License - for use in teaching, academic research, and meeting\r\n * course requirements at degree granting institutions only.  Not for\r\n * government, commercial, or other organizational use.\r\n *\r\n * File: Controller.c\r\n *\r\n * Code generated for Simulink model 'Controller'.\r\n *\r\n * Model version                  : 1.89\r\n * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023\r\n * C/C++ source code generated on : Tue Oct  1 15:57:18 2024\r\n *\r\n * Target selection: ert.tlc\r\n * Embedded hardware selection: ARM Compatible->ARM Cortex-M\r\n * Code generation objectives:\r\n *    1. Execution efficiency\r\n *    2. RAM efficiency\r\n * Validation result: Not run\r\n */\r\n\r\n#include \"Controller.h\"\r\n#include \"rtwtypes.h\"\r\n#include <math.h>\r\n#include \"math.h\"\r\n\r\n/* Block signals and states (default storage) */\r\nDW rtDW;\r\nstatic real_T rtGetNaN(void);\r\nstatic real32_T rtGetNaNF(void);\r\n\r\n/*===========*\r\n * Constants *\r\n *===========*/\r\n#define RT_PI                          3.14159265358979323846\r\n#define RT_PIF                         3.1415927F\r\n#define RT_LN_10                       2.30258509299404568402\r\n#define RT_LN_10F                      2.3025851F\r\n#define RT_LOG10E                      0.43429448190325182765\r\n#define RT_LOG10EF                     0.43429449F\r\n#define RT_E                           2.7182818284590452354\r\n#define RT_EF                          2.7182817F\r\n\r\n/*\r\n * UNUSED_PARAMETER(x)\r\n *   Used to specify that a function parameter (argument) is required but not\r\n *   accessed by the function body.\r\n */\r\n#ifndef UNUSED_PARAMETER\r\n#if defined(__LCC__)\r\n#define UNUSED_PARAMETER(x)                                      /* do nothing */\r\n#else\r\n\r\n/*\r\n * This is the semi-ANSI standard way of indicating that an\r\n * unused function parameter is required.\r\n */\r\n#define UNUSED_PARAMETER(x)            (void) (x)\r\n#endif\r\n#endif\r\n\r\nextern real_T rtInf;\r\nextern real_T rtMinusInf;\r\nextern real_T rtNaN;\r\nextern real32_T rtInfF;\r\nextern real32_T rtMinusInfF;\r\nextern real32_T rtNaNF;\r\nstatic boolean_T rtIsInf(real_T value);\r\nstatic boolean_T rtIsInfF(real32_T value);\r\nstatic boolean_T rtIsNaN(real_T value);\r\nstatic boolean_T rtIsNaNF(real32_T value);\r\nreal_T rtNaN = -(real_T)NAN;\r\nreal_T rtInf = (real_T)INFINITY;\r\nreal_T rtMinusInf = -(real_T)INFINITY;\r\nreal32_T rtNaNF = -(real32_T)NAN;\r\nreal32_T rtInfF = (real32_T)INFINITY;\r\nreal32_T rtMinusInfF = -(real32_T)INFINITY;\r\n\r\n/* Return rtNaN needed by the generated code. */\r\nstatic real_T rtGetNaN(void)\r\n{\r\n  return rtNaN;\r\n}\r\n\r\n/* Return rtNaNF needed by the generated code. */\r\nstatic real32_T rtGetNaNF(void)\r\n{\r\n  return rtNaNF;\r\n}\r\n\r\n/* Test if value is infinite */\r\nstatic boolean_T rtIsInf(real_T value)\r\n{\r\n  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);\r\n}\r\n\r\n/* Test if single-precision value is infinite */\r\nstatic boolean_T rtIsInfF(real32_T value)\r\n{\r\n  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);\r\n}\r\n\r\n/* Test if value is not a number */\r\nstatic boolean_T rtIsNaN(real_T value)\r\n{\r\n  return (boolean_T)(isnan(value) != 0);\r\n}\r\n\r\n/* Test if single-precision value is not a number */\r\nstatic boolean_T rtIsNaNF(real32_T value)\r\n{\r\n  return (boolean_T)(isnan(value) != 0);\r\n}\r\n\r\n/* Model step function */\r\nvoid Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate, real32_T\r\n                     arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef,\r\n                     real32_T arg_AccRef[2], real_T arg_YawRateRef, real_T\r\n                     arg_YawAccRef, real_T arg_Accelerometer[2], real32_T\r\n                     arg_Motorefforts[4])\r\n{\r\n  int32_T b_k;\r\n  int32_T idx;\r\n  real32_T rtb_Product[4];\r\n  real32_T varargin_1[4];\r\n  real32_T FilterDifferentiatorTF_tmp;\r\n  real32_T arg_AccRef_0;\r\n  real32_T arg_AccRef_1;\r\n  real32_T q;\r\n  real32_T rtb_FilterDifferentiatorTF;\r\n  real32_T rtb_Sum;\r\n  real32_T rtb_y_c;\r\n  real32_T u0;\r\n  boolean_T exitg1;\r\n  boolean_T rEQ0;\r\n  UNUSED_PARAMETER(arg_Wheelspeeds);\r\n  UNUSED_PARAMETER(arg_YawRate);\r\n  UNUSED_PARAMETER(arg_VelRef);\r\n  UNUSED_PARAMETER(arg_YawRateRef);\r\n  UNUSED_PARAMETER(arg_YawAccRef);\r\n  UNUSED_PARAMETER(arg_Accelerometer);\r\n\r\n  /* Sum: '<Root>/Sum' incorporates:\r\n   *  Inport: '<Root>/Yaw'\r\n   *  Inport: '<Root>/YawRef'\r\n   */\r\n  rtb_Sum = arg_YawRef - arg_Yaw;\r\n\r\n  /* MATLAB Function: '<S1>/DeFlipper' */\r\n  if (rtIsNaNF(rtb_Sum + 3.14159274F)) {\r\n    rtb_y_c = (rtNaNF);\r\n  } else if (rtIsInfF(rtb_Sum + 3.14159274F)) {\r\n    rtb_y_c = (rtNaNF);\r\n  } else if (rtb_Sum + 3.14159274F == 0.0F) {\r\n    rtb_y_c = 0.0F;\r\n  } else {\r\n    rtb_y_c = fmodf(rtb_Sum + 3.14159274F, 6.28318548F);\r\n    rEQ0 = (rtb_y_c == 0.0F);\r\n    if (!rEQ0) {\r\n      q = fabsf((rtb_Sum + 3.14159274F) / 6.28318548F);\r\n      rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);\r\n    }\r\n\r\n    if (rEQ0) {\r\n      rtb_y_c = 0.0F;\r\n    } else if (rtb_Sum + 3.14159274F < 0.0F) {\r\n      rtb_y_c += 6.28318548F;\r\n    }\r\n  }\r\n\r\n  if (rtb_y_c < 0.0F) {\r\n    rtb_y_c += 6.28318548F;\r\n  }\r\n\r\n  /* Gain: '<S39>/Integral Gain' incorporates:\r\n   *  MATLAB Function: '<S1>/DeFlipper'\r\n   */\r\n  rtb_Sum = (rtb_y_c - 3.14159274F) * 0.0F;\r\n\r\n  /* DiscreteIntegrator: '<S42>/Integrator' */\r\n  q = 0.005F * rtb_Sum + rtDW.Integrator_DSTATE;\r\n\r\n  /* DiscreteTransferFcn: '<S35>/Filter Differentiator TF' incorporates:\r\n   *  Gain: '<S33>/Derivative Gain'\r\n   *  MATLAB Function: '<S1>/DeFlipper'\r\n   */\r\n  FilterDifferentiatorTF_tmp = (rtb_y_c - 3.14159274F) * 0.4F - -0.333333343F *\r\n    rtDW.FilterDifferentiatorTF_states;\r\n\r\n  /* Sum: '<S51>/Sum' incorporates:\r\n   *  DiscreteTransferFcn: '<S35>/Filter Differentiator TF'\r\n   *  Gain: '<S45>/Filter Coefficient'\r\n   *  Gain: '<S47>/Proportional Gain'\r\n   *  MATLAB Function: '<S1>/DeFlipper'\r\n   *  Product: '<S35>/DenCoefOut'\r\n   */\r\n  rtb_y_c = ((rtb_y_c - 3.14159274F) * 3.0F + q) + (FilterDifferentiatorTF_tmp -\r\n    rtDW.FilterDifferentiatorTF_states) * 0.666666687F * 100.0F;\r\n\r\n  /* Product: '<S1>/Product' */\r\n  rtb_Product[0] = rtb_y_c;\r\n\r\n  /* MATLAB Function: '<S3>/Desaturator' incorporates:\r\n   *  Product: '<S1>/Product'\r\n   */\r\n  rtb_FilterDifferentiatorTF = fabsf(rtb_y_c);\r\n  varargin_1[0] = rtb_FilterDifferentiatorTF;\r\n\r\n  /* Product: '<S1>/Product' */\r\n  rtb_Product[1] = rtb_y_c;\r\n\r\n  /* MATLAB Function: '<S3>/Desaturator' */\r\n  varargin_1[1] = rtb_FilterDifferentiatorTF;\r\n\r\n  /* Product: '<S1>/Product' */\r\n  rtb_Product[2] = rtb_y_c;\r\n\r\n  /* MATLAB Function: '<S3>/Desaturator' */\r\n  varargin_1[2] = rtb_FilterDifferentiatorTF;\r\n\r\n  /* Product: '<S1>/Product' */\r\n  rtb_Product[3] = rtb_y_c;\r\n\r\n  /* MATLAB Function: '<S3>/Desaturator' incorporates:\r\n   *  Constant: '<Root>/Forcelimit'\r\n   */\r\n  varargin_1[3] = rtb_FilterDifferentiatorTF;\r\n  if (!rtIsNaNF(rtb_FilterDifferentiatorTF)) {\r\n    idx = 1;\r\n  } else {\r\n    idx = 0;\r\n    b_k = 2;\r\n    exitg1 = false;\r\n    while ((!exitg1) && (b_k < 5)) {\r\n      if (!rtIsNaNF(varargin_1[b_k - 1])) {\r\n        idx = b_k;\r\n        exitg1 = true;\r\n      } else {\r\n        b_k++;\r\n      }\r\n    }\r\n  }\r\n\r\n  if (idx == 0) {\r\n    rtb_y_c = rtb_FilterDifferentiatorTF;\r\n  } else {\r\n    rtb_y_c = varargin_1[idx - 1];\r\n    for (b_k = idx + 1; b_k < 5; b_k++) {\r\n      rtb_FilterDifferentiatorTF = varargin_1[b_k - 1];\r\n      if (rtb_y_c < rtb_FilterDifferentiatorTF) {\r\n        rtb_y_c = rtb_FilterDifferentiatorTF;\r\n      }\r\n    }\r\n  }\r\n\r\n  rtb_FilterDifferentiatorTF = rtb_y_c / 37.0370369F;\r\n  if (1.0F - rtb_FilterDifferentiatorTF < 0.0F) {\r\n    rtb_y_c = 0.0F;\r\n  } else if (rtIsNaNF(1.0F - rtb_FilterDifferentiatorTF)) {\r\n    rtb_y_c = 0.0F;\r\n  } else {\r\n    rtb_y_c = 1.0F - rtb_FilterDifferentiatorTF;\r\n  }\r\n\r\n  if (rtb_FilterDifferentiatorTF < 1.0F) {\r\n    rtb_FilterDifferentiatorTF = 1.0F;\r\n  } else if (rtIsNaNF(rtb_FilterDifferentiatorTF)) {\r\n    rtb_FilterDifferentiatorTF = 1.0F;\r\n  }\r\n\r\n  /* Gain: '<S2>/MassFeedForward' incorporates:\r\n   *  Constant: '<S2>/BodyForceCouplingMatrix'\r\n   *  Inport: '<Root>/AccRef'\r\n   *  Product: '<S2>/Body2Wheels'\r\n   */\r\n  arg_AccRef_0 = arg_AccRef[0];\r\n  arg_AccRef_1 = arg_AccRef[1];\r\n  for (idx = 0; idx < 4; idx++) {\r\n    /* Saturate: '<Root>/Saturation' incorporates:\r\n     *  Constant: '<S2>/BodyForceCouplingMatrix'\r\n     *  Gain: '<Root>/ForceToTorque'\r\n     *  Gain: '<S2>/MassFeedForward'\r\n     *  Gain: '<S4>/IToV'\r\n     *  Gain: '<S4>/TorqueToI'\r\n     *  Gain: '<S4>/VToPWM'\r\n     *  MATLAB Function: '<S3>/Desaturator'\r\n     *  Product: '<S2>/Body2Wheels'\r\n     */\r\n    u0 = ((12.5F * arg_AccRef_0 * rtConstP.pooled1[idx] + rtConstP.pooled1[idx +\r\n           4] * (12.5F * arg_AccRef_1)) * rtb_y_c + rtb_Product[idx] /\r\n          rtb_FilterDifferentiatorTF) * 0.027F * 30.4878044F * 0.934579432F *\r\n      0.0416666679F;\r\n    if (u0 > 0.1F) {\r\n      /* Outport: '<Root>/Motorefforts' */\r\n      arg_Motorefforts[idx] = 0.1F;\r\n    } else if (u0 < -0.1F) {\r\n      /* Outport: '<Root>/Motorefforts' */\r\n      arg_Motorefforts[idx] = -0.1F;\r\n    } else {\r\n      /* Outport: '<Root>/Motorefforts' */\r\n      arg_Motorefforts[idx] = u0;\r\n    }\r\n\r\n    /* End of Saturate: '<Root>/Saturation' */\r\n  }\r\n\r\n  /* Update for DiscreteIntegrator: '<S42>/Integrator' */\r\n  rtDW.Integrator_DSTATE = 0.005F * rtb_Sum + q;\r\n\r\n  /* Update for DiscreteTransferFcn: '<S35>/Filter Differentiator TF' */\r\n  rtDW.FilterDifferentiatorTF_states = FilterDifferentiatorTF_tmp;\r\n}\r\n\r\n/* Model initialize function */\r\nvoid Controller_initialize(void)\r\n{\r\n  /* (no initialization code required) */\r\n}\r\n\r\n/*\r\n * File trailer for generated code.\r\n *\r\n * [EOF]\r\n */\r\n"},{"name":"Controller.h","type":"header","group":"model","path":"C:\\Users\\Marij\\Documents\\GitHub\\roboteam_microcontroller6.0\\Control\\Controller_ert_rtw","tag":"","groupDisplay":"Model files","code":"/*\r\n * Academic License - for use in teaching, academic research, and meeting\r\n * course requirements at degree granting institutions only.  Not for\r\n * government, commercial, or other organizational use.\r\n *\r\n * File: Controller.h\r\n *\r\n * Code generated for Simulink model 'Controller'.\r\n *\r\n * Model version                  : 1.89\r\n * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023\r\n * C/C++ source code generated on : Tue Oct  1 15:57:18 2024\r\n *\r\n * Target selection: ert.tlc\r\n * Embedded hardware selection: ARM Compatible->ARM Cortex-M\r\n * Code generation objectives:\r\n *    1. Execution efficiency\r\n *    2. RAM efficiency\r\n * Validation result: Not run\r\n */\r\n\r\n#ifndef Controller_h_\r\n#define Controller_h_\r\n#ifndef Controller_COMMON_INCLUDES_\r\n#define Controller_COMMON_INCLUDES_\r\n#include \"rtwtypes.h\"\r\n#include \"math.h\"\r\n#endif                                 /* Controller_COMMON_INCLUDES_ */\r\n\r\n/* Block signals and states (default storage) for system '<Root>' */\r\ntypedef struct {\r\n  real32_T Integrator_DSTATE;          /* '<S42>/Integrator' */\r\n  real32_T FilterDifferentiatorTF_states;/* '<S35>/Filter Differentiator TF' */\r\n} DW;\r\n\r\n/* Constant parameters (default storage) */\r\ntypedef struct {\r\n  /* Pooled Parameter (Expression: [cos(front_angle), sin(front_angle); -cos(front_angle), sin(front_angle); -cos(back_angle), -sin(back_angle); cos(back_angle), -sin(back_angle)])\r\n   * Referenced by:\r\n   *   '<S2>/BodyForceCouplingMatrix'\r\n   *   '<S60>/BodyForceCouplingMatrix'\r\n   */\r\n  real32_T pooled1[8];\r\n} ConstP;\r\n\r\n/* Block signals and states (default storage) */\r\nextern DW rtDW;\r\n\r\n/* Constant parameters (default storage) */\r\nextern const ConstP rtConstP;\r\n\r\n/* Model entry point functions */\r\nextern void Controller_initialize(void);\r\n\r\n/* Customized model step function */\r\nextern void Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate,\r\n  real32_T arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef, real32_T\r\n  arg_AccRef[2], real_T arg_YawRateRef, real_T arg_YawAccRef, real_T\r\n  arg_Accelerometer[2], real32_T arg_Motorefforts[4]);\r\n\r\n/*-\r\n * These blocks were eliminated from the model due to optimizations:\r\n *\r\n * Block '<Root>/YeetusChrist' : Eliminated nontunable gain of 1\r\n */\r\n\r\n/*-\r\n * The generated code includes comments that allow you to trace directly\r\n * back to the appropriate location in the model.  The basic format\r\n * is <system>/block_name, where system is the system number (uniquely\r\n * assigned by Simulink) and block_name is the name of the block.\r\n *\r\n * Use the MATLAB hilite_system command to trace the generated code back\r\n * to the model.  For example,\r\n *\r\n * hilite_system('<S3>')    - opens system 3\r\n * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3\r\n *\r\n * Here is the system hierarchy for this model\r\n *\r\n * '<Root>' : 'Controller'\r\n * '<S1>'   : 'Controller/AngleForceRequest'\r\n * '<S2>'   : 'Controller/BodyMassFeedforward'\r\n * '<S3>'   : 'Controller/Limiting and Prioritization'\r\n * '<S4>'   : 'Controller/TorqueControl'\r\n * '<S5>'   : 'Controller/AngleForceRequest/DeFlipper'\r\n * '<S6>'   : 'Controller/AngleForceRequest/Discrete PID Controller'\r\n * '<S7>'   : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'\r\n * '<S8>'   : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'\r\n * '<S9>'   : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'\r\n * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'\r\n * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'\r\n * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'\r\n * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'\r\n * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'\r\n * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'\r\n * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'\r\n * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'\r\n * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'\r\n * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'\r\n * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'\r\n * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'\r\n * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'\r\n * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'\r\n * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'\r\n * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'\r\n * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'\r\n * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'\r\n * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'\r\n * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'\r\n * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'\r\n * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'\r\n * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'\r\n * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'\r\n * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'\r\n * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'\r\n * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp'\r\n * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'\r\n * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'\r\n * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'\r\n * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'\r\n * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'\r\n * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'\r\n * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'\r\n * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Internal Parameters'\r\n * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'\r\n * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'\r\n * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'\r\n * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'\r\n * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'\r\n * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'\r\n * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'\r\n * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'\r\n * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'\r\n * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'\r\n * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'\r\n * '<S56>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'\r\n * '<S57>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'\r\n * '<S58>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'\r\n * '<S59>'  : 'Controller/Limiting and Prioritization/Desaturator'\r\n * '<S60>'  : 'Controller/TorqueControl/WheelfrictionFF'\r\n * '<S61>'  : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'\r\n */\r\n#endif                                 /* Controller_h_ */\r\n\r\n/*\r\n * File trailer for generated code.\r\n *\r\n * [EOF]\r\n */\r\n"},{"name":"Controller_data.c","type":"source","group":"data","path":"C:\\Users\\Marij\\Documents\\GitHub\\roboteam_microcontroller6.0\\Control\\Controller_ert_rtw","tag":"","groupDisplay":"Data files","code":"/*\r\n * Academic License - for use in teaching, academic research, and meeting\r\n * course requirements at degree granting institutions only.  Not for\r\n * government, commercial, or other organizational use.\r\n *\r\n * File: Controller_data.c\r\n *\r\n * Code generated for Simulink model 'Controller'.\r\n *\r\n * Model version                  : 1.89\r\n * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023\r\n * C/C++ source code generated on : Tue Oct  1 15:57:18 2024\r\n *\r\n * Target selection: ert.tlc\r\n * Embedded hardware selection: ARM Compatible->ARM Cortex-M\r\n * Code generation objectives:\r\n *    1. Execution efficiency\r\n *    2. RAM efficiency\r\n * Validation result: Not run\r\n */\r\n\r\n#include \"Controller.h\"\r\n\r\n/* Constant parameters (default storage) */\r\nconst ConstP rtConstP = {\r\n  /* Pooled Parameter (Expression: [cos(front_angle), sin(front_angle); -cos(front_angle), sin(front_angle); -cos(back_angle), -sin(back_angle); cos(back_angle), -sin(back_angle)])\r\n   * Referenced by:\r\n   *   '<S2>/BodyForceCouplingMatrix'\r\n   *   '<S60>/BodyForceCouplingMatrix'\r\n   */\r\n  { 0.707106769F, -0.707106769F, -0.852524519F, 0.852524519F, 0.707106769F,\r\n    0.707106769F, -0.522687256F, -0.522687256F }\r\n};\r\n\r\n/*\r\n * File trailer for generated code.\r\n *\r\n * [EOF]\r\n */\r\n"},{"name":"rtwtypes.h","type":"header","group":"utility","path":"C:\\Users\\Marij\\Documents\\GitHub\\roboteam_microcontroller6.0\\Control\\Controller_ert_rtw","tag":"","groupDisplay":"Utility files","code":"/*\r\n * Academic License - for use in teaching, academic research, and meeting\r\n * course requirements at degree granting institutions only.  Not for\r\n * government, commercial, or other organizational use.\r\n *\r\n * File: rtwtypes.h\r\n *\r\n * Code generated for Simulink model 'Controller'.\r\n *\r\n * Model version                  : 1.89\r\n * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023\r\n * C/C++ source code generated on : Tue Oct  1 15:57:18 2024\r\n *\r\n * Target selection: ert.tlc\r\n * Embedded hardware selection: ARM Compatible->ARM Cortex-M\r\n * Code generation objectives:\r\n *    1. Execution efficiency\r\n *    2. RAM efficiency\r\n * Validation result: Not run\r\n */\r\n\r\n#ifndef RTWTYPES_H\r\n#define RTWTYPES_H\r\n\r\n/* Logical type definitions */\r\n#if (!defined(__cplusplus))\r\n#ifndef false\r\n#define false                          (0U)\r\n#endif\r\n\r\n#ifndef true\r\n#define true                           (1U)\r\n#endif\r\n#endif\r\n\r\n/*=======================================================================*\r\n * Target hardware information\r\n *   Device type: ARM Compatible->ARM Cortex-M\r\n *   Number of bits:     char:   8    short:   16    int:  32\r\n *                       long:  32    long long:  64\r\n *                       native word size:  32\r\n *   Byte ordering: LittleEndian\r\n *   Signed integer division rounds to: Zero\r\n *   Shift right on a signed integer as arithmetic shift: on\r\n *=======================================================================*/\r\n\r\n/*=======================================================================*\r\n * Fixed width word size data types:                                     *\r\n *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *\r\n *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *\r\n *   real32_T, real64_T           - 32 and 64 bit floating point numbers *\r\n *=======================================================================*/\r\ntypedef signed char int8_T;\r\ntypedef unsigned char uint8_T;\r\ntypedef short int16_T;\r\ntypedef unsigned short uint16_T;\r\ntypedef int int32_T;\r\ntypedef unsigned int uint32_T;\r\ntypedef long long int64_T;\r\ntypedef unsigned long long uint64_T;\r\ntypedef float real32_T;\r\ntypedef double real64_T;\r\n\r\n/*===========================================================================*\r\n * Generic type definitions: boolean_T, char_T, byte_T, int_T, uint_T,       *\r\n *                           real_T, time_T, ulong_T, ulonglong_T.           *\r\n *===========================================================================*/\r\ntypedef double real_T;\r\ntypedef double time_T;\r\ntypedef unsigned char boolean_T;\r\ntypedef int int_T;\r\ntypedef unsigned int uint_T;\r\ntypedef unsigned long ulong_T;\r\ntypedef unsigned long long ulonglong_T;\r\ntypedef char char_T;\r\ntypedef unsigned char uchar_T;\r\ntypedef char_T byte_T;\r\n\r\n/*=======================================================================*\r\n * Min and Max:                                                          *\r\n *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *\r\n *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *\r\n *=======================================================================*/\r\n#define MAX_int8_T                     ((int8_T)(127))\r\n#define MIN_int8_T                     ((int8_T)(-128))\r\n#define MAX_uint8_T                    ((uint8_T)(255U))\r\n#define MAX_int16_T                    ((int16_T)(32767))\r\n#define MIN_int16_T                    ((int16_T)(-32768))\r\n#define MAX_uint16_T                   ((uint16_T)(65535U))\r\n#define MAX_int32_T                    ((int32_T)(2147483647))\r\n#define MIN_int32_T                    ((int32_T)(-2147483647-1))\r\n#define MAX_uint32_T                   ((uint32_T)(0xFFFFFFFFU))\r\n#define MAX_int64_T                    ((int64_T)(9223372036854775807LL))\r\n#define MIN_int64_T                    ((int64_T)(-9223372036854775807LL-1LL))\r\n#define MAX_uint64_T                   ((uint64_T)(0xFFFFFFFFFFFFFFFFULL))\r\n\r\n/* Block D-Work pointer type */\r\ntypedef void * pointer_T;\r\n\r\n#endif                                 /* RTWTYPES_H */\r\n\r\n/*\r\n * File trailer for generated code.\r\n *\r\n * [EOF]\r\n */\r\n"}],"features":{"annotation":false,"coverage":true,"profiling":true,"tooltip":true,"coverageTooltip":true,"showJustificationLinks":true,"useMWTable":false,"showProfilingInfo":true,"showTaskSummary":true,"showProtectedV2Report":true}};