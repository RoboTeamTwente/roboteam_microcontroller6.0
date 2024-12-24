/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.174
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Dec 24 23:04:40 2024
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
  real32_T Integrator_DSTATE[2];       /* '<S103>/Integrator' */
  real32_T Filter_DSTATE[2];           /* '<S98>/Filter' */
  real32_T Integrator_DSTATE_h;        /* '<S45>/Integrator' */
  real32_T FilterDifferentiatorTF_states;/* '<S38>/Filter Differentiator TF' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: Dmat
   * Referenced by: '<S6>/Constant1'
   */
  real_T Constant1_Value[8];

  /* Pooled Parameter (Expression: Dmat)
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S67>/BodyForceCouplingMatrix'
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
  arg_AccRef[2], real32_T arg_YawRateRef, real32_T arg_YawAccRef, real32_T
  arg_Accelerometer[2], real32_T arg_Motorefforts[4], real32_T arg_Debug[32]);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Constant' : Unused code path elimination
 * Block '<S65>/Check Signal Attributes' : Unused code path elimination
 * Block '<S63>/Digital Filter' : Unused code path elimination
 * Block '<S66>/Check Signal Attributes' : Unused code path elimination
 * Block '<S64>/Digital Filter' : Unused code path elimination
 * Block '<S4>/Discrete-Time Integrator' : Unused code path elimination
 * Block '<S4>/Rad2M' : Unused code path elimination
 * Block '<S4>/Sum' : Unused code path elimination
 * Block '<S4>/Wheels2Body' : Unused code path elimination
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
 * '<S63>'  : 'Controller/StateEst/Digital Filter Design'
 * '<S64>'  : 'Controller/StateEst/Digital Filter Design1'
 * '<S65>'  : 'Controller/StateEst/Digital Filter Design/Check Signal Attributes'
 * '<S66>'  : 'Controller/StateEst/Digital Filter Design1/Check Signal Attributes'
 * '<S67>'  : 'Controller/TorqueControl/WheelfrictionFF'
 * '<S68>'  : 'Controller/TorqueControl/WheelfrictionFF/MATLAB Function'
 * '<S69>'  : 'Controller/VelocityFeedback/SpeedControl'
 * '<S70>'  : 'Controller/VelocityFeedback/SpeedControl/Anti-windup'
 * '<S71>'  : 'Controller/VelocityFeedback/SpeedControl/D Gain'
 * '<S72>'  : 'Controller/VelocityFeedback/SpeedControl/External Derivative'
 * '<S73>'  : 'Controller/VelocityFeedback/SpeedControl/Filter'
 * '<S74>'  : 'Controller/VelocityFeedback/SpeedControl/Filter ICs'
 * '<S75>'  : 'Controller/VelocityFeedback/SpeedControl/I Gain'
 * '<S76>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain'
 * '<S77>'  : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain Fdbk'
 * '<S78>'  : 'Controller/VelocityFeedback/SpeedControl/Integrator'
 * '<S79>'  : 'Controller/VelocityFeedback/SpeedControl/Integrator ICs'
 * '<S80>'  : 'Controller/VelocityFeedback/SpeedControl/N Copy'
 * '<S81>'  : 'Controller/VelocityFeedback/SpeedControl/N Gain'
 * '<S82>'  : 'Controller/VelocityFeedback/SpeedControl/P Copy'
 * '<S83>'  : 'Controller/VelocityFeedback/SpeedControl/Parallel P Gain'
 * '<S84>'  : 'Controller/VelocityFeedback/SpeedControl/Reset Signal'
 * '<S85>'  : 'Controller/VelocityFeedback/SpeedControl/Saturation'
 * '<S86>'  : 'Controller/VelocityFeedback/SpeedControl/Saturation Fdbk'
 * '<S87>'  : 'Controller/VelocityFeedback/SpeedControl/Sum'
 * '<S88>'  : 'Controller/VelocityFeedback/SpeedControl/Sum Fdbk'
 * '<S89>'  : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode'
 * '<S90>'  : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode Sum'
 * '<S91>'  : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Integral'
 * '<S92>'  : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Ngain'
 * '<S93>'  : 'Controller/VelocityFeedback/SpeedControl/postSat Signal'
 * '<S94>'  : 'Controller/VelocityFeedback/SpeedControl/preSat Signal'
 * '<S95>'  : 'Controller/VelocityFeedback/SpeedControl/Anti-windup/Passthrough'
 * '<S96>'  : 'Controller/VelocityFeedback/SpeedControl/D Gain/Internal Parameters'
 * '<S97>'  : 'Controller/VelocityFeedback/SpeedControl/External Derivative/Error'
 * '<S98>'  : 'Controller/VelocityFeedback/SpeedControl/Filter/Disc. Forward Euler Filter'
 * '<S99>'  : 'Controller/VelocityFeedback/SpeedControl/Filter ICs/Internal IC - Filter'
 * '<S100>' : 'Controller/VelocityFeedback/SpeedControl/I Gain/Internal Parameters'
 * '<S101>' : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain/Passthrough'
 * '<S102>' : 'Controller/VelocityFeedback/SpeedControl/Ideal P Gain Fdbk/Disabled'
 * '<S103>' : 'Controller/VelocityFeedback/SpeedControl/Integrator/Discrete'
 * '<S104>' : 'Controller/VelocityFeedback/SpeedControl/Integrator ICs/Internal IC'
 * '<S105>' : 'Controller/VelocityFeedback/SpeedControl/N Copy/Disabled'
 * '<S106>' : 'Controller/VelocityFeedback/SpeedControl/N Gain/Internal Parameters'
 * '<S107>' : 'Controller/VelocityFeedback/SpeedControl/P Copy/Disabled'
 * '<S108>' : 'Controller/VelocityFeedback/SpeedControl/Parallel P Gain/Internal Parameters'
 * '<S109>' : 'Controller/VelocityFeedback/SpeedControl/Reset Signal/Disabled'
 * '<S110>' : 'Controller/VelocityFeedback/SpeedControl/Saturation/Passthrough'
 * '<S111>' : 'Controller/VelocityFeedback/SpeedControl/Saturation Fdbk/Disabled'
 * '<S112>' : 'Controller/VelocityFeedback/SpeedControl/Sum/Sum_PID'
 * '<S113>' : 'Controller/VelocityFeedback/SpeedControl/Sum Fdbk/Disabled'
 * '<S114>' : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode/Disabled'
 * '<S115>' : 'Controller/VelocityFeedback/SpeedControl/Tracking Mode Sum/Passthrough'
 * '<S116>' : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Integral/TsSignalSpecification'
 * '<S117>' : 'Controller/VelocityFeedback/SpeedControl/Tsamp - Ngain/Passthrough'
 * '<S118>' : 'Controller/VelocityFeedback/SpeedControl/postSat Signal/Forward_Path'
 * '<S119>' : 'Controller/VelocityFeedback/SpeedControl/preSat Signal/Forward_Path'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
