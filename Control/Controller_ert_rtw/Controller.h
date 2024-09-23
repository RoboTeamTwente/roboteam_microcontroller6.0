/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Sep 23 16:23:19 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef Controller_h_
#define Controller_h_
#ifndef Controller_COMMON_INCLUDES_
#define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T Integrator_DSTATE;          /* '<S40>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S35>/Filter' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [cos(front_angle), sin(front_angle); -cos(front_angle), sin(front_angle); -cos(back_angle), -sin(back_angle); cos(back_angle), -sin(back_angle)])
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S58>/BodyForceCouplingMatrix'
   */
  real32_T pooled1[8];
} ConstP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Controller_initialize(void);

/* Customized model step function */
extern void Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate,
  real32_T arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef, real32_T
  arg_AccRef[2], real_T arg_YawRateRef, real_T arg_YawAccRef, real32_T
  arg_Motorefforts[4]);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/YeetusChrist' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Controller'
 * '<S1>'   : 'Controller/AngleForceRequest'
 * '<S2>'   : 'Controller/BodyMassFeedforward'
 * '<S3>'   : 'Controller/Limiting and Prioritization'
 * '<S4>'   : 'Controller/TorqueControl'
 * '<S5>'   : 'Controller/AngleForceRequest/DeFlipper'
 * '<S6>'   : 'Controller/AngleForceRequest/Discrete PID Controller'
 * '<S7>'   : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'
 * '<S8>'   : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'
 * '<S9>'   : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'
 * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'
 * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'
 * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'
 * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'
 * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'
 * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'
 * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'
 * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'
 * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'
 * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'
 * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'
 * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'
 * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'
 * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'
 * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'
 * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'
 * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'
 * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'
 * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'
 * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'
 * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'
 * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'
 * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'
 * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Disabled'
 * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'
 * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'
 * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'
 * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'
 * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S56>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S57>'  : 'Controller/Limiting and Prioritization/Desaturator'
 * '<S58>'  : 'Controller/TorqueControl/WheelfrictionFF'
 * '<S59>'  : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
