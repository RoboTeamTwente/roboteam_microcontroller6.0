/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.116
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Nov  8 14:41:18 2024
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
  real_T Integrator_DSTATE[2];         /* '<S96>/Integrator' */
  real_T Filter_DSTATE[2];             /* '<S91>/Filter' */
  real32_T DigitalFilter_FILT_STATES[10];/* '<S3>/Digital Filter' */
  real32_T Integrator_DSTATE_h;        /* '<S44>/Integrator' */
  real32_T FilterDifferentiatorTF_states;/* '<S37>/Filter Differentiator TF' */
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
   *   '<S113>/BodyForceCouplingMatrix'
   */
  real32_T pooled4[8];
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
 * Block '<S61>/Check Signal Attributes' : Unused code path elimination
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
 * '<S3>'   : 'Controller/Digital Filter Design'
 * '<S4>'   : 'Controller/Limiting and Prioritization'
 * '<S5>'   : 'Controller/SpeedControl'
 * '<S6>'   : 'Controller/TorqueControl'
 * '<S7>'   : 'Controller/AngleForceRequest/DeFlipper'
 * '<S8>'   : 'Controller/AngleForceRequest/Discrete PID Controller'
 * '<S9>'   : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'
 * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'
 * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'
 * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'
 * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'
 * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'
 * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'
 * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'
 * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'
 * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'
 * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'
 * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'
 * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'
 * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'
 * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'
 * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'
 * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'
 * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'
 * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'
 * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'
 * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'
 * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'
 * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'
 * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'
 * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'
 * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'
 * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'
 * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Internal Parameters'
 * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'
 * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'
 * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'
 * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'
 * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S56>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S57>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S58>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S59>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S60>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S61>'  : 'Controller/Digital Filter Design/Check Signal Attributes'
 * '<S62>'  : 'Controller/Limiting and Prioritization/Desaturator'
 * '<S63>'  : 'Controller/SpeedControl/Anti-windup'
 * '<S64>'  : 'Controller/SpeedControl/D Gain'
 * '<S65>'  : 'Controller/SpeedControl/External Derivative'
 * '<S66>'  : 'Controller/SpeedControl/Filter'
 * '<S67>'  : 'Controller/SpeedControl/Filter ICs'
 * '<S68>'  : 'Controller/SpeedControl/I Gain'
 * '<S69>'  : 'Controller/SpeedControl/Ideal P Gain'
 * '<S70>'  : 'Controller/SpeedControl/Ideal P Gain Fdbk'
 * '<S71>'  : 'Controller/SpeedControl/Integrator'
 * '<S72>'  : 'Controller/SpeedControl/Integrator ICs'
 * '<S73>'  : 'Controller/SpeedControl/N Copy'
 * '<S74>'  : 'Controller/SpeedControl/N Gain'
 * '<S75>'  : 'Controller/SpeedControl/P Copy'
 * '<S76>'  : 'Controller/SpeedControl/Parallel P Gain'
 * '<S77>'  : 'Controller/SpeedControl/Reset Signal'
 * '<S78>'  : 'Controller/SpeedControl/Saturation'
 * '<S79>'  : 'Controller/SpeedControl/Saturation Fdbk'
 * '<S80>'  : 'Controller/SpeedControl/Sum'
 * '<S81>'  : 'Controller/SpeedControl/Sum Fdbk'
 * '<S82>'  : 'Controller/SpeedControl/Tracking Mode'
 * '<S83>'  : 'Controller/SpeedControl/Tracking Mode Sum'
 * '<S84>'  : 'Controller/SpeedControl/Tsamp - Integral'
 * '<S85>'  : 'Controller/SpeedControl/Tsamp - Ngain'
 * '<S86>'  : 'Controller/SpeedControl/postSat Signal'
 * '<S87>'  : 'Controller/SpeedControl/preSat Signal'
 * '<S88>'  : 'Controller/SpeedControl/Anti-windup/Passthrough'
 * '<S89>'  : 'Controller/SpeedControl/D Gain/Internal Parameters'
 * '<S90>'  : 'Controller/SpeedControl/External Derivative/Error'
 * '<S91>'  : 'Controller/SpeedControl/Filter/Disc. Forward Euler Filter'
 * '<S92>'  : 'Controller/SpeedControl/Filter ICs/Internal IC - Filter'
 * '<S93>'  : 'Controller/SpeedControl/I Gain/Internal Parameters'
 * '<S94>'  : 'Controller/SpeedControl/Ideal P Gain/Passthrough'
 * '<S95>'  : 'Controller/SpeedControl/Ideal P Gain Fdbk/Disabled'
 * '<S96>'  : 'Controller/SpeedControl/Integrator/Discrete'
 * '<S97>'  : 'Controller/SpeedControl/Integrator ICs/Internal IC'
 * '<S98>'  : 'Controller/SpeedControl/N Copy/Disabled'
 * '<S99>'  : 'Controller/SpeedControl/N Gain/Internal Parameters'
 * '<S100>' : 'Controller/SpeedControl/P Copy/Disabled'
 * '<S101>' : 'Controller/SpeedControl/Parallel P Gain/Internal Parameters'
 * '<S102>' : 'Controller/SpeedControl/Reset Signal/Disabled'
 * '<S103>' : 'Controller/SpeedControl/Saturation/Passthrough'
 * '<S104>' : 'Controller/SpeedControl/Saturation Fdbk/Disabled'
 * '<S105>' : 'Controller/SpeedControl/Sum/Sum_PID'
 * '<S106>' : 'Controller/SpeedControl/Sum Fdbk/Disabled'
 * '<S107>' : 'Controller/SpeedControl/Tracking Mode/Disabled'
 * '<S108>' : 'Controller/SpeedControl/Tracking Mode Sum/Passthrough'
 * '<S109>' : 'Controller/SpeedControl/Tsamp - Integral/TsSignalSpecification'
 * '<S110>' : 'Controller/SpeedControl/Tsamp - Ngain/Passthrough'
 * '<S111>' : 'Controller/SpeedControl/postSat Signal/Forward_Path'
 * '<S112>' : 'Controller/SpeedControl/preSat Signal/Forward_Path'
 * '<S113>' : 'Controller/TorqueControl/WheelfrictionFF'
 * '<S114>' : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
