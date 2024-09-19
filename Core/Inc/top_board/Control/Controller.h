/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Sep 19 12:26:50 2024
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
  real32_T Integrator_DSTATE;          /* '<S35>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S30>/Filter' */
} DW;

/* Block signals and states (default storage) */
extern DW rtDW;

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
 * '<S1>'   : 'Controller/Discrete PID Controller'
 * '<S2>'   : 'Controller/Discrete PID Controller/Anti-windup'
 * '<S3>'   : 'Controller/Discrete PID Controller/D Gain'
 * '<S4>'   : 'Controller/Discrete PID Controller/External Derivative'
 * '<S5>'   : 'Controller/Discrete PID Controller/Filter'
 * '<S6>'   : 'Controller/Discrete PID Controller/Filter ICs'
 * '<S7>'   : 'Controller/Discrete PID Controller/I Gain'
 * '<S8>'   : 'Controller/Discrete PID Controller/Ideal P Gain'
 * '<S9>'   : 'Controller/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S10>'  : 'Controller/Discrete PID Controller/Integrator'
 * '<S11>'  : 'Controller/Discrete PID Controller/Integrator ICs'
 * '<S12>'  : 'Controller/Discrete PID Controller/N Copy'
 * '<S13>'  : 'Controller/Discrete PID Controller/N Gain'
 * '<S14>'  : 'Controller/Discrete PID Controller/P Copy'
 * '<S15>'  : 'Controller/Discrete PID Controller/Parallel P Gain'
 * '<S16>'  : 'Controller/Discrete PID Controller/Reset Signal'
 * '<S17>'  : 'Controller/Discrete PID Controller/Saturation'
 * '<S18>'  : 'Controller/Discrete PID Controller/Saturation Fdbk'
 * '<S19>'  : 'Controller/Discrete PID Controller/Sum'
 * '<S20>'  : 'Controller/Discrete PID Controller/Sum Fdbk'
 * '<S21>'  : 'Controller/Discrete PID Controller/Tracking Mode'
 * '<S22>'  : 'Controller/Discrete PID Controller/Tracking Mode Sum'
 * '<S23>'  : 'Controller/Discrete PID Controller/Tsamp - Integral'
 * '<S24>'  : 'Controller/Discrete PID Controller/Tsamp - Ngain'
 * '<S25>'  : 'Controller/Discrete PID Controller/postSat Signal'
 * '<S26>'  : 'Controller/Discrete PID Controller/preSat Signal'
 * '<S27>'  : 'Controller/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S28>'  : 'Controller/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S29>'  : 'Controller/Discrete PID Controller/External Derivative/External Ydot'
 * '<S30>'  : 'Controller/Discrete PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S31>'  : 'Controller/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S32>'  : 'Controller/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S33>'  : 'Controller/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S34>'  : 'Controller/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S35>'  : 'Controller/Discrete PID Controller/Integrator/Discrete'
 * '<S36>'  : 'Controller/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S37>'  : 'Controller/Discrete PID Controller/N Copy/Disabled'
 * '<S38>'  : 'Controller/Discrete PID Controller/N Gain/Internal Parameters'
 * '<S39>'  : 'Controller/Discrete PID Controller/P Copy/Disabled'
 * '<S40>'  : 'Controller/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S41>'  : 'Controller/Discrete PID Controller/Reset Signal/Disabled'
 * '<S42>'  : 'Controller/Discrete PID Controller/Saturation/Passthrough'
 * '<S43>'  : 'Controller/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S44>'  : 'Controller/Discrete PID Controller/Sum/Sum_PID'
 * '<S45>'  : 'Controller/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S46>'  : 'Controller/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S47>'  : 'Controller/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S48>'  : 'Controller/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S49>'  : 'Controller/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S50>'  : 'Controller/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S51>'  : 'Controller/Discrete PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
