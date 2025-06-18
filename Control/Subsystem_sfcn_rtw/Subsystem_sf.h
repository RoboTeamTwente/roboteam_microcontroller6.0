/*
 * Subsystem_sf.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Subsystem_sf".
 *
 * Model version              : 1.2
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Wed May 21 15:16:46 2025
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Subsystem_sf_h_
#define Subsystem_sf_h_
#ifndef Subsystem_sf_COMMON_INCLUDES_
#define Subsystem_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                Subsystem_sf
#define S_FUNCTION_LEVEL               2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif

#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_nonfinite.h"
#include "math.h"
#if !defined(MATLAB_MEX_FILE)
#include "rt_matrx.h"
#endif

#if !defined(RTW_SFUNCTION_DEFINES)
#define RTW_SFUNCTION_DEFINES

typedef struct {
  void *blockIO;
  void *defaultParam;
  void *nonContDerivSig;
} LocalS;

#define ssSetLocalBlockIO(S, io)       ((LocalS *)ssGetUserData(S))->blockIO = ((void *)(io))
#define ssGetLocalBlockIO(S)           ((LocalS *)ssGetUserData(S))->blockIO
#define ssSetLocalDefaultParam(S, paramVector) ((LocalS *)ssGetUserData(S))->defaultParam = (paramVector)
#define ssGetLocalDefaultParam(S)      ((LocalS *)ssGetUserData(S))->defaultParam
#define ssSetLocalNonContDerivSig(S, pSig) ((LocalS *)ssGetUserData(S))->nonContDerivSig = (pSig)
#define ssGetLocalNonContDerivSig(S)   ((LocalS *)ssGetUserData(S))->nonContDerivSig
#endif
#endif                                 /* Subsystem_sf_COMMON_INCLUDES_ */

#include "Subsystem_sf_types.h"
#include <string.h>
#include <stddef.h>
#include "rt_defines.h"

/* Block signals (default storage) */
typedef struct {
  real_T BodyAngularVel;               /* '<S1>/BodyAngularVel' */
  real_T BodyVel[2];                   /* '<S1>/BodyVel' */
  real_T WheelInertia;                 /* '<S16>/WheelInertia' */
  real_T WheelInertia_a;               /* '<S14>/WheelInertia' */
  real_T WheelInertia_l;               /* '<S12>/WheelInertia' */
  real_T WheelInertia_g;               /* '<S10>/WheelInertia' */
  real_T BFF2IF[2];                    /* '<S1>/BFF2IF' */
  real_T Sum3;                         /* '<S1>/Sum3' */
  real_T Sum1;                         /* '<S10>/Sum1' */
  real_T Sum1_o;                       /* '<S16>/Sum1' */
  real_T Sum1_d;                       /* '<S14>/Sum1' */
  real_T Sum1_l;                       /* '<S12>/Sum1' */
} B_Subsystem_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T *MotorPWMs[4];              /* '<Root>/MotorPWMs' */
} ExternalUPtrs_Subsystem_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T *WheelAngles[4];              /* '<Root>/WheelAngles' */
  real_T *Position[2];                 /* '<Root>/Position' */
  real_T *AngVel;                      /* '<Root>/AngVel' */
  real_T *Yaw;                         /* '<Root>/Yaw' */
  real_T *WheelCurrents[4];            /* '<Root>/WheelCurrents' */
  real_T *BFFAcceleration[2];          /* '<Root>/BFFAcceleration' */
} ExtY_Subsystem_T;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Sum' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<S1>/Sum2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Plant_d_Bench/Subsystem Reference')    - opens subsystem Plant_d_Bench/Subsystem Reference
 * hilite_system('Plant_d_Bench/Subsystem Reference/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Plant_d_Bench'
 * '<S1>'   : 'Plant_d_Bench/Subsystem Reference'
 * '<S2>'   : 'Plant_d_Bench/Subsystem Reference/Angle2Rotmat'
 * '<S3>'   : 'Plant_d_Bench/Subsystem Reference/Angle2Rotmat1'
 * '<S4>'   : 'Plant_d_Bench/Subsystem Reference/Subsystem Reference4'
 * '<S5>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly0'
 * '<S6>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly1'
 * '<S7>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly2'
 * '<S8>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly3'
 * '<S9>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly0/MATLAB Function'
 * '<S10>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly0/Wheel'
 * '<S11>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly1/MATLAB Function'
 * '<S12>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly1/Wheel'
 * '<S13>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly2/MATLAB Function'
 * '<S14>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly2/Wheel'
 * '<S15>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly3/MATLAB Function'
 * '<S16>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly3/Wheel'
 */
#endif                                 /* Subsystem_sf_h_ */
