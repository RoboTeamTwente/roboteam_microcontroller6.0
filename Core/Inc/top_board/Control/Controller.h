/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 2.29
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Feb 11 15:35:57 2025
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
  real32_T DigitalFilter[4];           /* '<S3>/Digital Filter' */
  real32_T DigitalFilter_FILT_STATES[8];/* '<S3>/Digital Filter' */
  real32_T Integrator_DSTATE[2];       /* '<S105>/Integrator' */
  real32_T Filter_DSTATE[2];           /* '<S100>/Filter' */
  real32_T Integrator_DSTATE_h;        /* '<S47>/Integrator' */
  real32_T FilterDifferentiatorTF_states;/* '<S40>/Filter Differentiator TF' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: wheels.Dforce
   * Referenced by: '<S7>/Constant1'
   */
  real_T Constant1_Value_f[8];

  /* Computed Parameter: BodyForceCouplingMatrix_Value
   * Referenced by: '<S2>/BodyForceCouplingMatrix'
   */
  real32_T BodyForceCouplingMatrix_Value[8];

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S5>/Constant'
   */
  real32_T Constant_Value_h[8];

  /* Computed Parameter: BodyForceCouplingMatrix_Value_d
   * Referenced by: '<S68>/BodyForceCouplingMatrix'
   */
  real32_T BodyForceCouplingMatrix_Value_d[8];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Encoders[4];                /* '<Root>/Encoders' */
} ExtU;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Controller_initialize(void);

/* Customized model step function */
extern void Controller_step(real32_T arg_Encoders[4], real32_T arg_YawRate,
  real32_T arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef, real32_T
  arg_AccRef[2], real32_T arg_YawRateRef, real32_T arg_YawAccRef, real32_T
  arg_Accelerometer[2], real32_T arg_Motorefforts[4], real32_T arg_Debug[32],
  real32_T arg_Velest[2], real32_T *arg_AFL, real32_T arg_VBat);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Discrete Transfer Fcn' : Unused code path elimination
 * Block '<S65>/Check Signal Attributes' : Unused code path elimination
 * Block '<S38>/Derivative Gain' : Eliminated nontunable gain of 1
 * Block '<S97>/Kb' : Eliminated nontunable gain of 1
 * Block '<S110>/Proportional Gain' : Eliminated nontunable gain of 1
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
 * '<S3>'   : 'Controller/Digital Filter Design2'
 * '<S4>'   : 'Controller/Limiting and Prioritization'
 * '<S5>'   : 'Controller/StateEst'
 * '<S6>'   : 'Controller/TorqueControl'
 * '<S7>'   : 'Controller/VelocityFeedback'
 * '<S8>'   : 'Controller/AngleForceRequest/CubicCompensator'
 * '<S9>'   : 'Controller/AngleForceRequest/DeFlipper'
 * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller'
 * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'
 * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'
 * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'
 * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'
 * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'
 * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'
 * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'
 * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'
 * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'
 * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'
 * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'
 * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'
 * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'
 * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'
 * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'
 * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'
 * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'
 * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'
 * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'
 * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'
 * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'
 * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'
 * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'
 * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preInt Signal'
 * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'
 * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'
 * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'
 * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'
 * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Internal Parameters'
 * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'
 * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'
 * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'
 * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S56>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'
 * '<S57>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S58>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S59>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S60>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S61>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S62>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S63>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preInt Signal/Internal PreInt'
 * '<S64>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S65>'  : 'Controller/Digital Filter Design2/Check Signal Attributes'
 * '<S66>'  : 'Controller/Limiting and Prioritization/Desaturator'
 * '<S67>'  : 'Controller/StateEst/MATLAB Function'
 * '<S68>'  : 'Controller/TorqueControl/WheelfrictionFF'
 * '<S69>'  : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'
 * '<S70>'  : 'Controller/VelocityFeedback/SpeedControl'
 * '<S71>'  : 'Controller/VelocityFeedback/SpeedControl/Anti-windup'
 * '<S72>'  : 'Controller/VelocityFeedback/SpeedControl/D Gain'
 * '<S73>'  : 'Controller/VelocityFeedback/SpeedControl/External Derivative'
 * '<S74>'  : 'Controller/VelocityFeedback/SpeedControl/Filter'
 * '<S75>'  : 'Controller/VelocityFeedback/SpeedControl/Filter ICs'
 * '<S76>'  : 'Controller/VelocityFeedback/SpeedControl/I Gain'
 * '<S77>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain'
 * '<S78>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain Fdbk'
 * '<S79>'  : 'Controller/VelocityFeedback/SpeedControl/Integrator'
 * '<S80>'  : 'Controller/VelocityFeedback/SpeedControl/Integrator ICs'
 * '<S81>'  : 'Controller/VelocityFeedback/SpeedControl/N Copy'
 * '<S82>'  : 'Controller/VelocityFeedback/SpeedControl/N Gain'
 * '<S83>'  : 'Controller/VelocityFeedback/SpeedControl/P Copy'
 * '<S84>'  : 'Controller/VelocityFeedback/SpeedControl/Parallel P Gain'
 * '<S85>'  : 'Controller/VelocityFeedback/SpeedControl/Reset Signal'
 * '<S86>'  : 'Controller/VelocityFeedback/SpeedControl/Saturation'
 * '<S87>'  : 'Controller/VelocityFeedback/SpeedControl/Saturation Fdbk'
 * '<S88>'  : 'Controller/VelocityFeedback/SpeedControl/Sum'
 * '<S89>'  : 'Controller/VelocityFeedback/SpeedControl/Sum Fdbk'
 * '<S90>'  : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode'
 * '<S91>'  : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode Sum'
 * '<S92>'  : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Integral'
 * '<S93>'  : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Ngain'
 * '<S94>'  : 'Controller/VelocityFeedback/SpeedControl/postSat Signal'
 * '<S95>'  : 'Controller/VelocityFeedback/SpeedControl/preInt Signal'
 * '<S96>'  : 'Controller/VelocityFeedback/SpeedControl/preSat Signal'
 * '<S97>'  : 'Controller/VelocityFeedback/SpeedControl/Anti-windup/Back Calculation'
 * '<S98>'  : 'Controller/VelocityFeedback/SpeedControl/D Gain/Internal Parameters'
 * '<S99>'  : 'Controller/VelocityFeedback/SpeedControl/External Derivative/Error'
 * '<S100>' : 'Controller/VelocityFeedback/SpeedControl/Filter/Disc. Forward Euler Filter'
 * '<S101>' : 'Controller/VelocityFeedback/SpeedControl/Filter ICs/Internal IC - Filter'
 * '<S102>' : 'Controller/VelocityFeedback/SpeedControl/I Gain/Internal Parameters'
 * '<S103>' : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain/Passthrough'
 * '<S104>' : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain Fdbk/Disabled'
 * '<S105>' : 'Controller/VelocityFeedback/SpeedControl/Integrator/Discrete'
 * '<S106>' : 'Controller/VelocityFeedback/SpeedControl/Integrator ICs/Internal IC'
 * '<S107>' : 'Controller/VelocityFeedback/SpeedControl/N Copy/Disabled'
 * '<S108>' : 'Controller/VelocityFeedback/SpeedControl/N Gain/Internal Parameters'
 * '<S109>' : 'Controller/VelocityFeedback/SpeedControl/P Copy/Disabled'
 * '<S110>' : 'Controller/VelocityFeedback/SpeedControl/Parallel P Gain/Internal Parameters'
 * '<S111>' : 'Controller/VelocityFeedback/SpeedControl/Reset Signal/Disabled'
 * '<S112>' : 'Controller/VelocityFeedback/SpeedControl/Saturation/Enabled'
 * '<S113>' : 'Controller/VelocityFeedback/SpeedControl/Saturation Fdbk/Disabled'
 * '<S114>' : 'Controller/VelocityFeedback/SpeedControl/Sum/Sum_PID'
 * '<S115>' : 'Controller/VelocityFeedback/SpeedControl/Sum Fdbk/Disabled'
 * '<S116>' : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode/Disabled'
 * '<S117>' : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode Sum/Passthrough'
 * '<S118>' : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Integral/TsSignalSpecification'
 * '<S119>' : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Ngain/Passthrough'
 * '<S120>' : 'Controller/VelocityFeedback/SpeedControl/postSat Signal/Forward_Path'
 * '<S121>' : 'Controller/VelocityFeedback/SpeedControl/preInt Signal/Internal PreInt'
 * '<S122>' : 'Controller/VelocityFeedback/SpeedControl/preSat Signal/Forward_Path'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
