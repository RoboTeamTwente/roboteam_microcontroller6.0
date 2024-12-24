/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DribblerController.h
 *
 * Code generated for Simulink model 'DribblerController'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Dec 24 22:58:45 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef DribblerController_h_
#define DribblerController_h_
#ifndef DribblerController_COMMON_INCLUDES_
#define DribblerController_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* DribblerController_COMMON_INCLUDES_ */

#include "DribblerController_types.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UD_DSTATE;                    /* '<S2>/UD' */
  real_T DigitalFilter_states[50];     /* '<S3>/Digital Filter' */
  real_T Filter_DSTATE;                /* '<S84>/Filter' */
  real_T Integrator_DSTATE;            /* '<S89>/Integrator' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  real_T Filter_DSTATE_b;              /* '<S33>/Filter' */
  real_T Integrator_DSTATE_a;          /* '<S38>/Integrator' */
  real_T DigitalFilter_simContextBuf[100];/* '<S3>/Digital Filter' */
  real_T DigitalFilter_simRevCoeff[51];/* '<S3>/Digital Filter' */
} DW_DribblerController_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<Root>/Gain' */
} ConstB_DribblerController_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [-0.00030885767480369773 -0.00876466878804146865 -0.020161541133976113 -0.00690802381451350884 0.0108713568485573099 -0.00362025719012729107 -0.00574129751956535539 0.0102380672900746171 -0.00597747543534707295 -0.00474909782584612226 0.01343565548064817 -0.0112288111156075669 -0.00255684621620127931 0.0177813530377556803 -0.0199106986099109318 0.0029732693463601057 0.0224143789298945732 -0.0340355326622340804 0.0155228542809866792 0.0265301518586944958 -0.0604471025019019254 0.0476435196367374636 0.0293714697780637669 -0.149210039191467331 0.25871593762741818 0.697052866642395519 0.25871593762741818 -0.149210039191467331 0.0293714697780637669 0.0476435196367374636 -0.0604471025019019254 0.0265301518586944958 0.0155228542809866792 -0.0340355326622340804 0.0224143789298945732 0.0029732693463601057 -0.0199106986099109318 0.0177813530377556803 -0.00255684621620127931 -0.0112288111156075669 0.01343565548064817 -0.00474909782584612226 -0.00597747543534707295 0.0102380672900746171 -0.00574129751956535539 -0.00362025719012729107 0.0108713568485573099 -0.00690802381451350884 -0.020161541133976113 -0.00876466878804146865 -0.00030885767480369773]
   * Referenced by: '<S3>/Digital Filter'
   */
  real_T DigitalFilter_Coefficients[51];
} ConstP_DribblerController_T;

/* Real-time Model Data Structure */
struct tag_RTM_DribblerController_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_DribblerController_T DribblerController_DW;
extern const ConstB_DribblerController_T DribblerController_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_DribblerController_T DribblerController_ConstP;

/* Model entry point functions */
extern void DribblerController_initialize(void);
extern void DribblerController_terminate(void);

/* Customized model step function */
extern void DribblerController_step(real_T arg_encoder, boolean_T arg_ball_detec,
  real_T arg_current, real_T *arg_motor_effort);

/* Real-time Model object */
extern RT_MODEL_DribblerController_T *const DribblerController_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S55>/Check Signal Attributes' : Unused code path elimination
 * Block '<S97>/Data Type Duplicate' : Unused code path elimination
 * Block '<S97>/Data Type Propagation' : Unused code path elimination
 * Block '<S30>/Kb' : Eliminated nontunable gain of 1
 * Block '<S35>/Integral Gain' : Eliminated nontunable gain of 1
 * Block '<S43>/Proportional Gain' : Eliminated nontunable gain of 1
 * Block '<S81>/Kb' : Eliminated nontunable gain of 1
 * Block '<S86>/Integral Gain' : Eliminated nontunable gain of 1
 * Block '<S94>/Proportional Gain' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'DribblerController'
 * '<S1>'   : 'DribblerController/Current PI'
 * '<S2>'   : 'DribblerController/Discrete Derivative'
 * '<S3>'   : 'DribblerController/LPF'
 * '<S4>'   : 'DribblerController/Speed PI'
 * '<S5>'   : 'DribblerController/Current PI/Anti-windup'
 * '<S6>'   : 'DribblerController/Current PI/D Gain'
 * '<S7>'   : 'DribblerController/Current PI/External Derivative'
 * '<S8>'   : 'DribblerController/Current PI/Filter'
 * '<S9>'   : 'DribblerController/Current PI/Filter ICs'
 * '<S10>'  : 'DribblerController/Current PI/I Gain'
 * '<S11>'  : 'DribblerController/Current PI/Ideal P Gain'
 * '<S12>'  : 'DribblerController/Current PI/Ideal P Gain Fdbk'
 * '<S13>'  : 'DribblerController/Current PI/Integrator'
 * '<S14>'  : 'DribblerController/Current PI/Integrator ICs'
 * '<S15>'  : 'DribblerController/Current PI/N Copy'
 * '<S16>'  : 'DribblerController/Current PI/N Gain'
 * '<S17>'  : 'DribblerController/Current PI/P Copy'
 * '<S18>'  : 'DribblerController/Current PI/Parallel P Gain'
 * '<S19>'  : 'DribblerController/Current PI/Reset Signal'
 * '<S20>'  : 'DribblerController/Current PI/Saturation'
 * '<S21>'  : 'DribblerController/Current PI/Saturation Fdbk'
 * '<S22>'  : 'DribblerController/Current PI/Sum'
 * '<S23>'  : 'DribblerController/Current PI/Sum Fdbk'
 * '<S24>'  : 'DribblerController/Current PI/Tracking Mode'
 * '<S25>'  : 'DribblerController/Current PI/Tracking Mode Sum'
 * '<S26>'  : 'DribblerController/Current PI/Tsamp - Integral'
 * '<S27>'  : 'DribblerController/Current PI/Tsamp - Ngain'
 * '<S28>'  : 'DribblerController/Current PI/postSat Signal'
 * '<S29>'  : 'DribblerController/Current PI/preSat Signal'
 * '<S30>'  : 'DribblerController/Current PI/Anti-windup/Back Calculation'
 * '<S31>'  : 'DribblerController/Current PI/D Gain/Internal Parameters'
 * '<S32>'  : 'DribblerController/Current PI/External Derivative/Error'
 * '<S33>'  : 'DribblerController/Current PI/Filter/Disc. Forward Euler Filter'
 * '<S34>'  : 'DribblerController/Current PI/Filter ICs/Internal IC - Filter'
 * '<S35>'  : 'DribblerController/Current PI/I Gain/Internal Parameters'
 * '<S36>'  : 'DribblerController/Current PI/Ideal P Gain/Passthrough'
 * '<S37>'  : 'DribblerController/Current PI/Ideal P Gain Fdbk/Disabled'
 * '<S38>'  : 'DribblerController/Current PI/Integrator/Discrete'
 * '<S39>'  : 'DribblerController/Current PI/Integrator ICs/Internal IC'
 * '<S40>'  : 'DribblerController/Current PI/N Copy/Disabled'
 * '<S41>'  : 'DribblerController/Current PI/N Gain/Internal Parameters'
 * '<S42>'  : 'DribblerController/Current PI/P Copy/Disabled'
 * '<S43>'  : 'DribblerController/Current PI/Parallel P Gain/Internal Parameters'
 * '<S44>'  : 'DribblerController/Current PI/Reset Signal/Disabled'
 * '<S45>'  : 'DribblerController/Current PI/Saturation/Enabled'
 * '<S46>'  : 'DribblerController/Current PI/Saturation Fdbk/Disabled'
 * '<S47>'  : 'DribblerController/Current PI/Sum/Sum_PID'
 * '<S48>'  : 'DribblerController/Current PI/Sum Fdbk/Disabled'
 * '<S49>'  : 'DribblerController/Current PI/Tracking Mode/Disabled'
 * '<S50>'  : 'DribblerController/Current PI/Tracking Mode Sum/Passthrough'
 * '<S51>'  : 'DribblerController/Current PI/Tsamp - Integral/TsSignalSpecification'
 * '<S52>'  : 'DribblerController/Current PI/Tsamp - Ngain/Passthrough'
 * '<S53>'  : 'DribblerController/Current PI/postSat Signal/Forward_Path'
 * '<S54>'  : 'DribblerController/Current PI/preSat Signal/Forward_Path'
 * '<S55>'  : 'DribblerController/LPF/Check Signal Attributes'
 * '<S56>'  : 'DribblerController/Speed PI/Anti-windup'
 * '<S57>'  : 'DribblerController/Speed PI/D Gain'
 * '<S58>'  : 'DribblerController/Speed PI/External Derivative'
 * '<S59>'  : 'DribblerController/Speed PI/Filter'
 * '<S60>'  : 'DribblerController/Speed PI/Filter ICs'
 * '<S61>'  : 'DribblerController/Speed PI/I Gain'
 * '<S62>'  : 'DribblerController/Speed PI/Ideal P Gain'
 * '<S63>'  : 'DribblerController/Speed PI/Ideal P Gain Fdbk'
 * '<S64>'  : 'DribblerController/Speed PI/Integrator'
 * '<S65>'  : 'DribblerController/Speed PI/Integrator ICs'
 * '<S66>'  : 'DribblerController/Speed PI/N Copy'
 * '<S67>'  : 'DribblerController/Speed PI/N Gain'
 * '<S68>'  : 'DribblerController/Speed PI/P Copy'
 * '<S69>'  : 'DribblerController/Speed PI/Parallel P Gain'
 * '<S70>'  : 'DribblerController/Speed PI/Reset Signal'
 * '<S71>'  : 'DribblerController/Speed PI/Saturation'
 * '<S72>'  : 'DribblerController/Speed PI/Saturation Fdbk'
 * '<S73>'  : 'DribblerController/Speed PI/Sum'
 * '<S74>'  : 'DribblerController/Speed PI/Sum Fdbk'
 * '<S75>'  : 'DribblerController/Speed PI/Tracking Mode'
 * '<S76>'  : 'DribblerController/Speed PI/Tracking Mode Sum'
 * '<S77>'  : 'DribblerController/Speed PI/Tsamp - Integral'
 * '<S78>'  : 'DribblerController/Speed PI/Tsamp - Ngain'
 * '<S79>'  : 'DribblerController/Speed PI/postSat Signal'
 * '<S80>'  : 'DribblerController/Speed PI/preSat Signal'
 * '<S81>'  : 'DribblerController/Speed PI/Anti-windup/Back Calculation'
 * '<S82>'  : 'DribblerController/Speed PI/D Gain/Internal Parameters'
 * '<S83>'  : 'DribblerController/Speed PI/External Derivative/Error'
 * '<S84>'  : 'DribblerController/Speed PI/Filter/Disc. Forward Euler Filter'
 * '<S85>'  : 'DribblerController/Speed PI/Filter ICs/Internal IC - Filter'
 * '<S86>'  : 'DribblerController/Speed PI/I Gain/Internal Parameters'
 * '<S87>'  : 'DribblerController/Speed PI/Ideal P Gain/Passthrough'
 * '<S88>'  : 'DribblerController/Speed PI/Ideal P Gain Fdbk/Disabled'
 * '<S89>'  : 'DribblerController/Speed PI/Integrator/Discrete'
 * '<S90>'  : 'DribblerController/Speed PI/Integrator ICs/Internal IC'
 * '<S91>'  : 'DribblerController/Speed PI/N Copy/Disabled'
 * '<S92>'  : 'DribblerController/Speed PI/N Gain/Internal Parameters'
 * '<S93>'  : 'DribblerController/Speed PI/P Copy/Disabled'
 * '<S94>'  : 'DribblerController/Speed PI/Parallel P Gain/Internal Parameters'
 * '<S95>'  : 'DribblerController/Speed PI/Reset Signal/Disabled'
 * '<S96>'  : 'DribblerController/Speed PI/Saturation/External'
 * '<S97>'  : 'DribblerController/Speed PI/Saturation/External/Saturation Dynamic'
 * '<S98>'  : 'DribblerController/Speed PI/Saturation Fdbk/Disabled'
 * '<S99>'  : 'DribblerController/Speed PI/Sum/Sum_PID'
 * '<S100>' : 'DribblerController/Speed PI/Sum Fdbk/Disabled'
 * '<S101>' : 'DribblerController/Speed PI/Tracking Mode/Disabled'
 * '<S102>' : 'DribblerController/Speed PI/Tracking Mode Sum/Passthrough'
 * '<S103>' : 'DribblerController/Speed PI/Tsamp - Integral/TsSignalSpecification'
 * '<S104>' : 'DribblerController/Speed PI/Tsamp - Ngain/Passthrough'
 * '<S105>' : 'DribblerController/Speed PI/postSat Signal/Forward_Path'
 * '<S106>' : 'DribblerController/Speed PI/preSat Signal/Forward_Path'
 */
#endif                                 /* DribblerController_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
