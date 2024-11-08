/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.107
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Nov  7 15:57:08 2024
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
  real_T Integrator_DSTATE[2];         /* '<S94>/Integrator' */
  real_T Filter_DSTATE[2];             /* '<S89>/Filter' */
  real32_T Integrator_DSTATE_h;        /* '<S43>/Integrator' */
  real32_T FilterDifferentiatorTF_states;/* '<S36>/Filter Differentiator TF' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: Dinv
   * Referenced by: '<Root>/Constant'
   */
  real_T Constant_Value[8];

  /* Expression: Dmat
   * Referenced by: '<Root>/Constant1'
   */
  real_T Constant1_Value[8];

  /* Pooled Parameter (Expression: Dmat)
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S111>/BodyForceCouplingMatrix'
   */
  real32_T pooled5[8];
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
  arg_AccRef[2], real32_T arg_YawRateRef, real32_T arg_YawAccRef, real32_T
  arg_Accelerometer[2], real32_T arg_Motorefforts[4]);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/RotInertiaFeedforward' : Eliminated nontunable gain of 1
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
 * '<S4>'   : 'Controller/SpeedControl'
 * '<S5>'   : 'Controller/TorqueControl'
 * '<S6>'   : 'Controller/AngleForceRequest/DeFlipper'
 * '<S7>'   : 'Controller/AngleForceRequest/Discrete PID Controller'
 * '<S8>'   : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'
 * '<S9>'   : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'
 * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'
 * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'
 * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'
 * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'
 * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'
 * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'
 * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'
 * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'
 * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'
 * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'
 * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'
 * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'
 * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'
 * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'
 * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'
 * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'
 * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'
 * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'
 * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'
 * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'
 * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'
 * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'
 * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'
 * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'
 * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'
 * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Internal Parameters'
 * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'
 * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'
 * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'
 * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'
 * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S56>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S57>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S58>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S59>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S60>'  : 'Controller/Limiting and Prioritization/Desaturator'
 * '<S61>'  : 'Controller/SpeedControl/Anti-windup'
 * '<S62>'  : 'Controller/SpeedControl/D Gain'
 * '<S63>'  : 'Controller/SpeedControl/External Derivative'
 * '<S64>'  : 'Controller/SpeedControl/Filter'
 * '<S65>'  : 'Controller/SpeedControl/Filter ICs'
 * '<S66>'  : 'Controller/SpeedControl/I Gain'
 * '<S67>'  : 'Controller/SpeedControl/Ideal P Gain'
 * '<S68>'  : 'Controller/SpeedControl/Ideal P Gain Fdbk'
 * '<S69>'  : 'Controller/SpeedControl/Integrator'
 * '<S70>'  : 'Controller/SpeedControl/Integrator ICs'
 * '<S71>'  : 'Controller/SpeedControl/N Copy'
 * '<S72>'  : 'Controller/SpeedControl/N Gain'
 * '<S73>'  : 'Controller/SpeedControl/P Copy'
 * '<S74>'  : 'Controller/SpeedControl/Parallel P Gain'
 * '<S75>'  : 'Controller/SpeedControl/Reset Signal'
 * '<S76>'  : 'Controller/SpeedControl/Saturation'
 * '<S77>'  : 'Controller/SpeedControl/Saturation Fdbk'
 * '<S78>'  : 'Controller/SpeedControl/Sum'
 * '<S79>'  : 'Controller/SpeedControl/Sum Fdbk'
 * '<S80>'  : 'Controller/SpeedControl/Tracking Mode'
 * '<S81>'  : 'Controller/SpeedControl/Tracking Mode Sum'
 * '<S82>'  : 'Controller/SpeedControl/Tsamp - Integral'
 * '<S83>'  : 'Controller/SpeedControl/Tsamp - Ngain'
 * '<S84>'  : 'Controller/SpeedControl/postSat Signal'
 * '<S85>'  : 'Controller/SpeedControl/preSat Signal'
 * '<S86>'  : 'Controller/SpeedControl/Anti-windup/Passthrough'
 * '<S87>'  : 'Controller/SpeedControl/D Gain/Internal Parameters'
 * '<S88>'  : 'Controller/SpeedControl/External Derivative/Error'
 * '<S89>'  : 'Controller/SpeedControl/Filter/Disc. Forward Euler Filter'
 * '<S90>'  : 'Controller/SpeedControl/Filter ICs/Internal IC - Filter'
 * '<S91>'  : 'Controller/SpeedControl/I Gain/Internal Parameters'
 * '<S92>'  : 'Controller/SpeedControl/Ideal P Gain/Passthrough'
 * '<S93>'  : 'Controller/SpeedControl/Ideal P Gain Fdbk/Disabled'
 * '<S94>'  : 'Controller/SpeedControl/Integrator/Discrete'
 * '<S95>'  : 'Controller/SpeedControl/Integrator ICs/Internal IC'
 * '<S96>'  : 'Controller/SpeedControl/N Copy/Disabled'
 * '<S97>'  : 'Controller/SpeedControl/N Gain/Internal Parameters'
 * '<S98>'  : 'Controller/SpeedControl/P Copy/Disabled'
 * '<S99>'  : 'Controller/SpeedControl/Parallel P Gain/Internal Parameters'
 * '<S100>' : 'Controller/SpeedControl/Reset Signal/Disabled'
 * '<S101>' : 'Controller/SpeedControl/Saturation/Passthrough'
 * '<S102>' : 'Controller/SpeedControl/Saturation Fdbk/Disabled'
 * '<S103>' : 'Controller/SpeedControl/Sum/Sum_PID'
 * '<S104>' : 'Controller/SpeedControl/Sum Fdbk/Disabled'
 * '<S105>' : 'Controller/SpeedControl/Tracking Mode/Disabled'
 * '<S106>' : 'Controller/SpeedControl/Tracking Mode Sum/Passthrough'
 * '<S107>' : 'Controller/SpeedControl/Tsamp - Integral/TsSignalSpecification'
 * '<S108>' : 'Controller/SpeedControl/Tsamp - Ngain/Passthrough'
 * '<S109>' : 'Controller/SpeedControl/postSat Signal/Forward_Path'
 * '<S110>' : 'Controller/SpeedControl/preSat Signal/Forward_Path'
 * '<S111>' : 'Controller/TorqueControl/WheelfrictionFF'
 * '<S112>' : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
