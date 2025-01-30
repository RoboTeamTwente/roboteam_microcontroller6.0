/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.213
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Jan 29 18:23:52 2025
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
  real32_T Wheels2Body[2];             /* '<S4>/Wheels2Body' */
  real32_T DigitalFilter[2];           /* '<S63>/Digital Filter' */
  real32_T DigitalFilter_FILT_STATES[4];/* '<S63>/Digital Filter' */
  real32_T Integrator_DSTATE[2];       /* '<S101>/Integrator' */
  real32_T Filter_DSTATE[2];           /* '<S96>/Filter' */
  real32_T Integrator_DSTATE_h;        /* '<S45>/Integrator' */
  real32_T FilterDifferentiatorTF_states;/* '<S38>/Filter Differentiator TF' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: Dforce
   * Referenced by: '<S6>/Constant1'
   */
  real_T Constant1_Value[8];

  /* Pooled Parameter (Expression: Dmat)
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S65>/BodyForceCouplingMatrix'
   */
  real32_T pooled1[8];

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S4>/Constant'
   */
  real32_T Constant_Value_h[8];
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
  arg_Accelerometer[2], real32_T arg_Motorefforts[4], real32_T arg_Debug[32],
  real32_T arg_Velest[2]);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S64>/Check Signal Attributes' : Unused code path elimination
 * Block '<Root>/RotInertiaFeedforward' : Eliminated nontunable gain of 1
 * Block '<S93>/Kb' : Eliminated nontunable gain of 1
 * Block '<S106>/Proportional Gain' : Eliminated nontunable gain of 1
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
 * '<S4>'   : 'Controller/StateEst'
 * '<S5>'   : 'Controller/TorqueControl'
 * '<S6>'   : 'Controller/VelocityFeedback'
 * '<S7>'   : 'Controller/AngleForceRequest/CubicCompensator'
 * '<S8>'   : 'Controller/AngleForceRequest/DeFlipper'
 * '<S9>'   : 'Controller/AngleForceRequest/Discrete PID Controller'
 * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'
 * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'
 * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'
 * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'
 * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'
 * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'
 * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'
 * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'
 * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'
 * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'
 * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'
 * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'
 * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'
 * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'
 * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'
 * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'
 * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'
 * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'
 * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'
 * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'
 * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'
 * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'
 * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'
 * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'
 * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'
 * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'
 * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'
 * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Internal Parameters'
 * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'
 * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'
 * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'
 * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'
 * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S56>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S57>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S58>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S59>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S60>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S61>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S62>'  : 'Controller/Limiting and Prioritization/Desaturator'
 * '<S63>'  : 'Controller/StateEst/Digital Filter Design2'
 * '<S64>'  : 'Controller/StateEst/Digital Filter Design2/Check Signal Attributes'
 * '<S65>'  : 'Controller/TorqueControl/WheelfrictionFF'
 * '<S66>'  : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'
 * '<S67>'  : 'Controller/VelocityFeedback/SpeedControl'
 * '<S68>'  : 'Controller/VelocityFeedback/SpeedControl/Anti-windup'
 * '<S69>'  : 'Controller/VelocityFeedback/SpeedControl/D Gain'
 * '<S70>'  : 'Controller/VelocityFeedback/SpeedControl/External Derivative'
 * '<S71>'  : 'Controller/VelocityFeedback/SpeedControl/Filter'
 * '<S72>'  : 'Controller/VelocityFeedback/SpeedControl/Filter ICs'
 * '<S73>'  : 'Controller/VelocityFeedback/SpeedControl/I Gain'
 * '<S74>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain'
 * '<S75>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain Fdbk'
 * '<S76>'  : 'Controller/VelocityFeedback/SpeedControl/Integrator'
 * '<S77>'  : 'Controller/VelocityFeedback/SpeedControl/Integrator ICs'
 * '<S78>'  : 'Controller/VelocityFeedback/SpeedControl/N Copy'
 * '<S79>'  : 'Controller/VelocityFeedback/SpeedControl/N Gain'
 * '<S80>'  : 'Controller/VelocityFeedback/SpeedControl/P Copy'
 * '<S81>'  : 'Controller/VelocityFeedback/SpeedControl/Parallel P Gain'
 * '<S82>'  : 'Controller/VelocityFeedback/SpeedControl/Reset Signal'
 * '<S83>'  : 'Controller/VelocityFeedback/SpeedControl/Saturation'
 * '<S84>'  : 'Controller/VelocityFeedback/SpeedControl/Saturation Fdbk'
 * '<S85>'  : 'Controller/VelocityFeedback/SpeedControl/Sum'
 * '<S86>'  : 'Controller/VelocityFeedback/SpeedControl/Sum Fdbk'
 * '<S87>'  : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode'
 * '<S88>'  : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode Sum'
 * '<S89>'  : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Integral'
 * '<S90>'  : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Ngain'
 * '<S91>'  : 'Controller/VelocityFeedback/SpeedControl/postSat Signal'
 * '<S92>'  : 'Controller/VelocityFeedback/SpeedControl/preSat Signal'
 * '<S93>'  : 'Controller/VelocityFeedback/SpeedControl/Anti-windup/Back Calculation'
 * '<S94>'  : 'Controller/VelocityFeedback/SpeedControl/D Gain/Internal Parameters'
 * '<S95>'  : 'Controller/VelocityFeedback/SpeedControl/External Derivative/Error'
 * '<S96>'  : 'Controller/VelocityFeedback/SpeedControl/Filter/Disc. Forward Euler Filter'
 * '<S97>'  : 'Controller/VelocityFeedback/SpeedControl/Filter ICs/Internal IC - Filter'
 * '<S98>'  : 'Controller/VelocityFeedback/SpeedControl/I Gain/Internal Parameters'
 * '<S99>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain/Passthrough'
 * '<S100>' : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain Fdbk/Disabled'
 * '<S101>' : 'Controller/VelocityFeedback/SpeedControl/Integrator/Discrete'
 * '<S102>' : 'Controller/VelocityFeedback/SpeedControl/Integrator ICs/Internal IC'
 * '<S103>' : 'Controller/VelocityFeedback/SpeedControl/N Copy/Disabled'
 * '<S104>' : 'Controller/VelocityFeedback/SpeedControl/N Gain/Internal Parameters'
 * '<S105>' : 'Controller/VelocityFeedback/SpeedControl/P Copy/Disabled'
 * '<S106>' : 'Controller/VelocityFeedback/SpeedControl/Parallel P Gain/Internal Parameters'
 * '<S107>' : 'Controller/VelocityFeedback/SpeedControl/Reset Signal/Disabled'
 * '<S108>' : 'Controller/VelocityFeedback/SpeedControl/Saturation/Enabled'
 * '<S109>' : 'Controller/VelocityFeedback/SpeedControl/Saturation Fdbk/Disabled'
 * '<S110>' : 'Controller/VelocityFeedback/SpeedControl/Sum/Sum_PID'
 * '<S111>' : 'Controller/VelocityFeedback/SpeedControl/Sum Fdbk/Disabled'
 * '<S112>' : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode/Disabled'
 * '<S113>' : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode Sum/Passthrough'
 * '<S114>' : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Integral/TsSignalSpecification'
 * '<S115>' : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Ngain/Passthrough'
 * '<S116>' : 'Controller/VelocityFeedback/SpeedControl/postSat Signal/Forward_Path'
 * '<S117>' : 'Controller/VelocityFeedback/SpeedControl/preSat Signal/Forward_Path'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
