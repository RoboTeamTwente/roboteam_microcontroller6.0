/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.31
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Sep 19 16:58:49 2024
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
  real32_T Integrator_DSTATE;          /* '<S39>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S34>/Filter' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: BodyForceCouplingMatrix_Value
   * Referenced by: '<S2>/BodyForceCouplingMatrix'
   */
  real32_T BodyForceCouplingMatrix_Value[8];
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
 * '<S3>'   : 'Controller/Desaturator'
 * '<S4>'   : 'Controller/AngleForceRequest/DeFlipper'
 * '<S5>'   : 'Controller/AngleForceRequest/Discrete PID Controller'
 * '<S6>'   : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup'
 * '<S7>'   : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain'
 * '<S8>'   : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative'
 * '<S9>'   : 'Controller/AngleForceRequest/Discrete PID Controller/Filter'
 * '<S10>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs'
 * '<S11>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain'
 * '<S12>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain'
 * '<S13>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S14>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator'
 * '<S15>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs'
 * '<S16>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy'
 * '<S17>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain'
 * '<S18>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy'
 * '<S19>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain'
 * '<S20>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal'
 * '<S21>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation'
 * '<S22>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk'
 * '<S23>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum'
 * '<S24>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk'
 * '<S25>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode'
 * '<S26>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum'
 * '<S27>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral'
 * '<S28>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain'
 * '<S29>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal'
 * '<S30>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal'
 * '<S31>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S32>'  : 'Controller/AngleForceRequest/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S33>'  : 'Controller/AngleForceRequest/Discrete PID Controller/External Derivative/Error'
 * '<S34>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S35>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S36>'  : 'Controller/AngleForceRequest/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S37>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S38>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S39>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator/Discrete'
 * '<S40>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S41>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Copy/Disabled'
 * '<S42>'  : 'Controller/AngleForceRequest/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S43>'  : 'Controller/AngleForceRequest/Discrete PID Controller/P Copy/Disabled'
 * '<S44>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S45>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Reset Signal/Disabled'
 * '<S46>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation/Passthrough'
 * '<S47>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S48>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum/Sum_PID'
 * '<S49>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S50>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S51>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S52>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S53>'  : 'Controller/AngleForceRequest/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S54>'  : 'Controller/AngleForceRequest/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S55>'  : 'Controller/AngleForceRequest/Discrete PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
