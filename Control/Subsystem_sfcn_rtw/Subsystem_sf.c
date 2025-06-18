/*
 * Subsystem_sf.c
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

#include "Subsystem_sf.h"
#include "Subsystem_sf_types.h"
#include "rtwtypes.h"
#include <math.h>
#include "Subsystem_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *Subsystem_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";

/* System initialize for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  if (ssIsFirstInitCond(S)) {
    /* InitializeConditions for DiscreteIntegrator: '<S1>/BodyAngularMomentum' */
    ((real_T *)ssGetDWork(S, 1))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/YawInt' */
    ((real_T *)ssGetDWork(S, 2))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/PositionInt' */
    ((real_T *)ssGetDWork(S, 0))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/BodyMomentum' */
    ((real_T *)ssGetDWork(S, 3))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/PositionInt' */
    ((real_T *)ssGetDWork(S, 0))[1] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/BodyMomentum' */
    ((real_T *)ssGetDWork(S, 3))[1] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S8>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 4))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S16>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 5))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S7>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 6))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S14>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 7))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S6>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 8))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S12>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 9))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S5>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 10))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S10>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 11))[0] = 0.0;
  } else {
    /* InitializeConditions for DiscreteIntegrator: '<S1>/BodyAngularMomentum' */
    ((real_T *)ssGetDWork(S, 1))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/YawInt' */
    ((real_T *)ssGetDWork(S, 2))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/PositionInt' */
    ((real_T *)ssGetDWork(S, 0))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/BodyMomentum' */
    ((real_T *)ssGetDWork(S, 3))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/PositionInt' */
    ((real_T *)ssGetDWork(S, 0))[1] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S1>/BodyMomentum' */
    ((real_T *)ssGetDWork(S, 3))[1] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S8>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 4))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S16>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 5))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S7>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 6))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S14>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 7))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S6>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 8))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S12>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 9))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S5>/WheelAngle' */
    ((real_T *)ssGetDWork(S, 10))[0] = 0.0;

    /* InitializeConditions for DiscreteIntegrator: '<S10>/WheelMomentum' */
    ((real_T *)ssGetDWork(S, 11))[0] = 0.0;
  }
}

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#if defined(MATLAB_MEX_FILE)
#endif

  Subsystem_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  B_Subsystem_T *_rtB;
  real_T absvel;
  real_T rtb_Rmotor;
  real_T rtb_Rmotor_mv;
  real_T rtb_Rmotor_n;
  real_T rtb_Rot2Trans;
  real_T rtb_Rot2Trans_i;
  real_T rtb_Rot2Trans_k;
  real_T rtb_Rot2Trans_kj;
  real_T rtb_TotalSlip;
  real_T rtb_TotalSlip_b;
  real_T rtb_TotalSlip_k;
  real_T rtb_TotalSlip_o;
  real_T rtb_force;
  real_T rtb_force_c;
  real_T rtb_force_j;
  real_T rtb_force_k_idx_1;
  real_T rtb_force_l;
  real_T rtb_force_n_idx_1;
  _rtB = ((B_Subsystem_T *) ssGetLocalBlockIO(S));

  /* Gain: '<S1>/BodyAngularVel' incorporates:
   *  DiscreteIntegrator: '<S1>/BodyAngularMomentum'
   */
  _rtB->BodyAngularVel = 50.0 * ((real_T *)ssGetDWork(S, 1))[0];

  /* Gain: '<S1>/BodyVel' incorporates:
   *  DiscreteIntegrator: '<S1>/BodyMomentum'
   */
  _rtB->BodyVel[0] = 0.4 * ((real_T *)ssGetDWork(S, 3))[0];
  _rtB->BodyVel[1] = 0.4 * ((real_T *)ssGetDWork(S, 3))[1];

  /* MATLAB Function: '<S1>/Angle2Rotmat1' incorporates:
   *  DiscreteIntegrator: '<S1>/YawInt'
   *  Gain: '<S1>/Invert'
   */
  rtb_Rot2Trans = sin(-((real_T *)ssGetDWork(S, 2))[0]);
  rtb_Rot2Trans_kj = cos(-((real_T *)ssGetDWork(S, 2))[0]);

  /* Product: '<S1>/IF2BFF' incorporates:
   *  MATLAB Function: '<S1>/Angle2Rotmat1'
   *  Sum: '<S1>/Sum6'
   */
  ((real_T *)ssGetOutputPortSignal(S, 5))[0] = rtb_Rot2Trans_kj * _rtB->BodyVel
    [0] + -rtb_Rot2Trans * _rtB->BodyVel[1];
  ((real_T *)ssGetOutputPortSignal(S, 5))[1] = rtb_Rot2Trans * _rtB->BodyVel[0]
    + rtb_Rot2Trans_kj * _rtB->BodyVel[1];

  /* Product: '<S8>/Body2Wheels' incorporates:
   *  Constant: '<S8>/Bod2WheelsMat'
   */
  rtb_Rot2Trans_k = 0.70710678118654735 * ((real_T *)ssGetOutputPortSignal(S, 5))
    [0] + -0.70710678118654768 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Product: '<S7>/Body2Wheels' incorporates:
   *  Constant: '<S7>/Bod2WheelsMat'
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_TotalSlip_b = -0.70710678118654768 * ((real_T *)ssGetOutputPortSignal(S, 5))
    [0] + -0.70710678118654746 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Product: '<S6>/Body2Wheels' incorporates:
   *  Constant: '<S6>/Bod2WheelsMat'
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_force_c = -0.86602540378443871 * ((real_T *)ssGetOutputPortSignal(S, 5))[0]
    + 0.49999999999999994 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Product: '<S5>/Body2Wheels' incorporates:
   *  Constant: '<S5>/Bod2WheelsMat'
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_force_l = 0.86602540378443871 * ((real_T *)ssGetOutputPortSignal(S, 5))[0]
    + 0.49999999999999994 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Product: '<S7>/Body2Wheels' incorporates:
   *  Constant: '<S7>/Bod2WheelsMat'
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_Rot2Trans_i = 0.70710678118654746 * ((real_T *)ssGetOutputPortSignal(S, 5))
    [0] + 0.70710678118654768 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Product: '<S6>/Body2Wheels' incorporates:
   *  Constant: '<S6>/Bod2WheelsMat'
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_TotalSlip_k = -0.49999999999999994 * ((real_T *)ssGetOutputPortSignal(S, 5))
    [0] + 0.86602540378443871 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Product: '<S5>/Body2Wheels' incorporates:
   *  Constant: '<S5>/Bod2WheelsMat'
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_Rmotor = -0.49999999999999994 * ((real_T *)ssGetOutputPortSignal(S, 5))[0]
    + -0.86602540378443871 * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Gain: '<S16>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S16>/WheelMomentum'
   */
  _rtB->WheelInertia = 99999.999999999985 * ((real_T *)ssGetDWork(S, 5))[0];

  /* Gain: '<S8>/Rot2Trans' */
  rtb_Rot2Trans = 0.027 * _rtB->WheelInertia;

  /* Gain: '<S8>/BodyRot2Trans1' incorporates:
   *  Gain: '<S5>/BodyRot2Trans1'
   *  Gain: '<S6>/BodyRot2Trans1'
   *  Gain: '<S7>/BodyRot2Trans1'
   */
  rtb_Rmotor_mv = 0.081 * _rtB->BodyAngularVel;
  rtb_Rot2Trans_kj = rtb_Rmotor_mv;

  /* Sum: '<S8>/TotalSlip' incorporates:
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_TotalSlip = ((0.0 - rtb_Rot2Trans_k) - rtb_Rot2Trans) - rtb_Rot2Trans_kj;

  /* MATLAB Function: '<S8>/MATLAB Function' incorporates:
   *  Constant: '<S8>/LinearFric'
   *  Constant: '<S8>/StaticFric'
   *  Constant: '<S8>/Subwheels'
   *  DiscreteIntegrator: '<S8>/WheelAngle'
   *  Product: '<S8>/Body2Wheels'
   *  Sum: '<S8>/Sum'
   */
  absvel = fabs(rtb_Rot2Trans_k + rtb_Rot2Trans_kj);
  rtb_force = (0.5 * absvel / (0.5 * absvel + 1.0) * 0.4 * sin(((real_T *)
    ssGetDWork(S, 4))[0] * 25.0) + 1.0) * (exp(-fabs(rtb_TotalSlip) * 1000.0) *
    100.0 + 5.0) * rtb_TotalSlip;

  /* SignalConversion generated from: '<S8>/Wheel2Body' incorporates:
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Gain: '<S8>/StrafeTraction'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_Rmotor_n = (0.70710678118654768 * ((real_T *)ssGetOutputPortSignal(S, 5))
                  [0] + -0.70710678118654735 * ((real_T *)ssGetOutputPortSignal
    (S, 5))[1]) * -0.1;

  /* Gain: '<S14>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S14>/WheelMomentum'
   */
  _rtB->WheelInertia_a = 99999.999999999985 * ((real_T *)ssGetDWork(S, 7))[0];

  /* Gain: '<S7>/Rot2Trans' */
  rtb_Rot2Trans_kj = 0.027 * _rtB->WheelInertia_a;

  /* Gain: '<S7>/BodyRot2Trans1' */
  rtb_Rot2Trans_k = rtb_Rmotor_mv;

  /* Sum: '<S7>/TotalSlip' incorporates:
   *  Product: '<S7>/Body2Wheels'
   */
  rtb_TotalSlip_o = ((0.0 - rtb_TotalSlip_b) - rtb_Rot2Trans_kj) -
    rtb_Rot2Trans_k;

  /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
   *  Constant: '<S7>/LinearFric'
   *  Constant: '<S7>/StaticFric'
   *  Constant: '<S7>/Subwheels'
   *  DiscreteIntegrator: '<S7>/WheelAngle'
   *  Product: '<S7>/Body2Wheels'
   *  Sum: '<S7>/Sum'
   */
  absvel = fabs(rtb_TotalSlip_b + rtb_Rot2Trans_k);
  rtb_force_j = (0.5 * absvel / (0.5 * absvel + 1.0) * 0.4 * sin(((real_T *)
    ssGetDWork(S, 6))[0] * 25.0) + 1.0) * (exp(-fabs(rtb_TotalSlip_o) * 1000.0) *
    100.0 + 5.0) * rtb_TotalSlip_o;

  /* SignalConversion generated from: '<S7>/Wheel2Body' incorporates:
   *  Gain: '<S7>/StrafeTraction'
   *  Product: '<S7>/Body2Wheels'
   */
  rtb_force_k_idx_1 = -0.1 * rtb_Rot2Trans_i;

  /* Gain: '<S12>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S12>/WheelMomentum'
   */
  _rtB->WheelInertia_l = 99999.999999999985 * ((real_T *)ssGetDWork(S, 9))[0];

  /* Gain: '<S6>/Rot2Trans' */
  rtb_Rot2Trans_k = 0.027 * _rtB->WheelInertia_l;

  /* Gain: '<S6>/BodyRot2Trans1' */
  rtb_Rot2Trans_i = rtb_Rmotor_mv;

  /* Sum: '<S6>/TotalSlip' incorporates:
   *  Product: '<S6>/Body2Wheels'
   */
  rtb_TotalSlip_b = ((0.0 - rtb_force_c) - rtb_Rot2Trans_k) - rtb_Rot2Trans_i;

  /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
   *  Constant: '<S6>/LinearFric'
   *  Constant: '<S6>/StaticFric'
   *  Constant: '<S6>/Subwheels'
   *  DiscreteIntegrator: '<S6>/WheelAngle'
   *  Product: '<S6>/Body2Wheels'
   *  Sum: '<S6>/Sum'
   */
  absvel = fabs(rtb_force_c + rtb_Rot2Trans_i);
  rtb_force_c = (0.5 * absvel / (0.5 * absvel + 1.0) * 0.4 * sin(((real_T *)
    ssGetDWork(S, 8))[0] * 25.0) + 1.0) * (exp(-fabs(rtb_TotalSlip_b) * 1000.0) *
    100.0 + 5.0) * rtb_TotalSlip_b;

  /* SignalConversion generated from: '<S6>/Wheel2Body' incorporates:
   *  Gain: '<S6>/StrafeTraction'
   *  Product: '<S6>/Body2Wheels'
   */
  rtb_force_n_idx_1 = -0.1 * rtb_TotalSlip_k;

  /* Gain: '<S10>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S10>/WheelMomentum'
   */
  _rtB->WheelInertia_g = 99999.999999999985 * ((real_T *)ssGetDWork(S, 11))[0];

  /* Gain: '<S5>/Rot2Trans' */
  rtb_Rot2Trans_i = 0.027 * _rtB->WheelInertia_g;

  /* Sum: '<S5>/TotalSlip' incorporates:
   *  Product: '<S5>/Body2Wheels'
   */
  rtb_TotalSlip_k = ((0.0 - rtb_force_l) - rtb_Rot2Trans_i) - rtb_Rmotor_mv;

  /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
   *  Constant: '<S5>/LinearFric'
   *  Constant: '<S5>/StaticFric'
   *  Constant: '<S5>/Subwheels'
   *  DiscreteIntegrator: '<S5>/WheelAngle'
   *  Product: '<S5>/Body2Wheels'
   *  Sum: '<S5>/Sum'
   */
  absvel = fabs(rtb_force_l + rtb_Rmotor_mv);
  rtb_force_l = (0.5 * absvel / (0.5 * absvel + 1.0) * 0.4 * sin(((real_T *)
    ssGetDWork(S, 10))[0] * 25.0) + 1.0) * (exp(-fabs(rtb_TotalSlip_k) * 1000.0)
    * 100.0 + 5.0) * rtb_TotalSlip_k;

  /* SignalConversion generated from: '<S5>/Wheel2Body' incorporates:
   *  Gain: '<S5>/StrafeTraction'
   *  Product: '<S5>/Body2Wheels'
   */
  rtb_Rmotor *= -0.1;

  /* Sum: '<S1>/Sum6' incorporates:
   *  Constant: '<S5>/Wheel2BodMat'
   *  Constant: '<S6>/Wheel2BodMat'
   *  Constant: '<S7>/Wheel2BodMat'
   *  Constant: '<S8>/Wheel2BodMat'
   *  Product: '<S5>/Wheel2Body'
   *  Product: '<S6>/Wheel2Body'
   *  Product: '<S7>/Wheel2Body'
   *  Product: '<S8>/Wheel2Body'
   *  SignalConversion generated from: '<S5>/Wheel2Body'
   *  SignalConversion generated from: '<S6>/Wheel2Body'
   *  SignalConversion generated from: '<S7>/Wheel2Body'
   *  SignalConversion generated from: '<S8>/Wheel2Body'
   *  Sum: '<S1>/Sum7'
   *  Sum: '<S1>/Sum8'
   */
  ((real_T *)ssGetOutputPortSignal(S, 5))[0] = (((-0.86602540378443871 *
    rtb_force_c + -0.49999999999999994 * rtb_force_n_idx_1) +
    (0.86602540378443871 * rtb_force_l + -0.49999999999999994 * rtb_Rmotor)) + (
    -0.70710678118654768 * rtb_force_j + 0.70710678118654746 * rtb_force_k_idx_1))
    + (0.70710678118654735 * rtb_force + 0.70710678118654768 * rtb_Rmotor_n);
  ((real_T *)ssGetOutputPortSignal(S, 5))[1] = (((0.49999999999999994 *
    rtb_force_c + 0.86602540378443871 * rtb_force_n_idx_1) +
    (0.49999999999999994 * rtb_force_l + -0.86602540378443871 * rtb_Rmotor)) + (
    -0.70710678118654746 * rtb_force_j + 0.70710678118654768 * rtb_force_k_idx_1))
    + (-0.70710678118654768 * rtb_force + -0.70710678118654735 * rtb_Rmotor_n);

  /* MATLAB Function: '<S1>/Angle2Rotmat' incorporates:
   *  DiscreteIntegrator: '<S1>/YawInt'
   */
  rtb_Rmotor = sin(((real_T *)ssGetDWork(S, 2))[0]);
  rtb_Rmotor_n = cos(((real_T *)ssGetDWork(S, 2))[0]);

  /* Product: '<S1>/BFF2IF' incorporates:
   *  MATLAB Function: '<S1>/Angle2Rotmat'
   */
  _rtB->BFF2IF[0] = rtb_Rmotor_n * ((real_T *)ssGetOutputPortSignal(S, 5))[0] +
    -rtb_Rmotor * ((real_T *)ssGetOutputPortSignal(S, 5))[1];
  _rtB->BFF2IF[1] = rtb_Rmotor * ((real_T *)ssGetOutputPortSignal(S, 5))[0] +
    rtb_Rmotor_n * ((real_T *)ssGetOutputPortSignal(S, 5))[1];

  /* Outport: '<Root>/BFFAcceleration' incorporates:
   *  Gain: '<S1>/BodyAccel'
   *  Sum: '<S1>/Sum6'
   */
  ((real_T *)ssGetOutputPortSignal(S, 5))[0] = 0.4 * ((real_T *)
    ssGetOutputPortSignal(S, 5))[0];

  /* Outport: '<Root>/Position' incorporates:
   *  DiscreteIntegrator: '<S1>/PositionInt'
   */
  ((real_T *)ssGetOutputPortSignal(S, 1))[0] = ((real_T *)ssGetDWork(S, 0))[0];

  /* Outport: '<Root>/BFFAcceleration' incorporates:
   *  Gain: '<S1>/BodyAccel'
   *  Sum: '<S1>/Sum6'
   */
  ((real_T *)ssGetOutputPortSignal(S, 5))[1] = 0.4 * ((real_T *)
    ssGetOutputPortSignal(S, 5))[1];

  /* Outport: '<Root>/Position' incorporates:
   *  DiscreteIntegrator: '<S1>/PositionInt'
   */
  ((real_T *)ssGetOutputPortSignal(S, 1))[1] = ((real_T *)ssGetDWork(S, 0))[1];

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S5>/WheelForce2BodyTorque'
   *  Gain: '<S6>/WheelForce2BodyTorque'
   *  Gain: '<S7>/WheelForce2BodyTorque'
   *  Gain: '<S8>/WheelForce2BodyTorque'
   *  Sum: '<S1>/Sum4'
   *  Sum: '<S1>/Sum5'
   */
  _rtB->Sum3 = ((0.081 * rtb_force_c + 0.081 * rtb_force_l) + 0.081 *
                rtb_force_j) + 0.081 * rtb_force;

  /* Gain: '<S10>/Rmotor' incorporates:
   *  Constant: '<S4>/ConstVbat'
   *  Gain: '<S10>/Back-EMF'
   *  Product: '<S10>/PWM2V'
   *  Sum: '<S10>/Sum'
   */
  rtb_Rmotor_n = (24.0F * *((const real32_T **)ssGetInputPortSignalPtrs(S, 0))[0]
                  - 0.032800000160932541 * _rtB->WheelInertia_g) *
    0.93457937240600586;

  /* Sum: '<S10>/Sum1' incorporates:
   *  Gain: '<S10>/MotorGyration'
   *  Gain: '<S10>/RotFriction'
   *  Gain: '<S5>/Force2Torque'
   *  Sum: '<S10>/Sum2'
   */
  _rtB->Sum1 = (0.027 * rtb_force_l + -9.9999997473787516E-6 *
                _rtB->WheelInertia_g) + 0.032800000160932541 * rtb_Rmotor_n;

  /* Gain: '<S12>/Rmotor' incorporates:
   *  Constant: '<S4>/ConstVbat'
   *  Gain: '<S12>/Back-EMF'
   *  Product: '<S12>/PWM2V'
   *  Sum: '<S12>/Sum'
   */
  rtb_Rmotor = (24.0F * *((const real32_T **)ssGetInputPortSignalPtrs(S, 0))[1]
                - 0.032800000160932541 * _rtB->WheelInertia_l) *
    0.93457937240600586;

  /* Gain: '<S14>/Rmotor' incorporates:
   *  Constant: '<S4>/ConstVbat'
   *  Gain: '<S14>/Back-EMF'
   *  Product: '<S14>/PWM2V'
   *  Sum: '<S14>/Sum'
   */
  rtb_force_l = (24.0F * *((const real32_T **)ssGetInputPortSignalPtrs(S, 0))[2]
                 - 0.032800000160932541 * _rtB->WheelInertia_a) *
    0.93457937240600586;

  /* Gain: '<S16>/Rmotor' incorporates:
   *  Constant: '<S4>/ConstVbat'
   *  Gain: '<S16>/Back-EMF'
   *  Product: '<S16>/PWM2V'
   *  Sum: '<S16>/Sum'
   */
  rtb_Rmotor_mv = (24.0F * *((const real32_T **)ssGetInputPortSignalPtrs(S, 0))
                   [3] - 0.032800000160932541 * _rtB->WheelInertia) *
    0.93457937240600586;

  /* Outport: '<Root>/WheelCurrents' */
  ((real_T *)ssGetOutputPortSignal(S, 4))[0] = rtb_Rmotor_n;
  ((real_T *)ssGetOutputPortSignal(S, 4))[1] = rtb_Rmotor;
  ((real_T *)ssGetOutputPortSignal(S, 4))[2] = rtb_force_l;
  ((real_T *)ssGetOutputPortSignal(S, 4))[3] = rtb_Rmotor_mv;

  /* Sum: '<S16>/Sum1' incorporates:
   *  Gain: '<S16>/MotorGyration'
   *  Gain: '<S16>/RotFriction'
   *  Gain: '<S8>/Force2Torque'
   *  Sum: '<S16>/Sum2'
   */
  _rtB->Sum1_o = (0.027 * rtb_force + -9.9999997473787516E-6 *
                  _rtB->WheelInertia) + 0.032800000160932541 * rtb_Rmotor_mv;

  /* Sum: '<S14>/Sum1' incorporates:
   *  Gain: '<S14>/MotorGyration'
   *  Gain: '<S14>/RotFriction'
   *  Gain: '<S7>/Force2Torque'
   *  Sum: '<S14>/Sum2'
   */
  _rtB->Sum1_d = (0.027 * rtb_force_j + -9.9999997473787516E-6 *
                  _rtB->WheelInertia_a) + 0.032800000160932541 * rtb_force_l;

  /* Sum: '<S12>/Sum1' incorporates:
   *  Gain: '<S12>/MotorGyration'
   *  Gain: '<S12>/RotFriction'
   *  Gain: '<S6>/Force2Torque'
   *  Sum: '<S12>/Sum2'
   */
  _rtB->Sum1_l = (0.027 * rtb_force_c + -9.9999997473787516E-6 *
                  _rtB->WheelInertia_l) + 0.032800000160932541 * rtb_Rmotor;

  /* Outport: '<Root>/WheelAngles' incorporates:
   *  DiscreteIntegrator: '<S5>/WheelAngle'
   *  DiscreteIntegrator: '<S6>/WheelAngle'
   *  DiscreteIntegrator: '<S7>/WheelAngle'
   *  DiscreteIntegrator: '<S8>/WheelAngle'
   */
  ((real_T *)ssGetOutputPortSignal(S, 0))[0] = ((real_T *)ssGetDWork(S, 10))[0];
  ((real_T *)ssGetOutputPortSignal(S, 0))[1] = ((real_T *)ssGetDWork(S, 8))[0];
  ((real_T *)ssGetOutputPortSignal(S, 0))[2] = ((real_T *)ssGetDWork(S, 6))[0];
  ((real_T *)ssGetOutputPortSignal(S, 0))[3] = ((real_T *)ssGetDWork(S, 4))[0];

  /* Outport: '<Root>/Yaw' incorporates:
   *  DiscreteIntegrator: '<S1>/YawInt'
   */
  ((real_T *)ssGetOutputPortSignal(S, 3))[0] = ((real_T *)ssGetDWork(S, 2))[0];

  /* Outport: '<Root>/AngVel' */
  ((real_T *)ssGetOutputPortSignal(S, 2))[0] = _rtB->BodyAngularVel;
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  B_Subsystem_T *_rtB;
  _rtB = ((B_Subsystem_T *) ssGetLocalBlockIO(S));

  /* Update for DiscreteIntegrator: '<S1>/BodyAngularMomentum' */
  ((real_T *)ssGetDWork(S, 1))[0] = 0.01 * _rtB->Sum3 + ((real_T *)ssGetDWork(S,
    1))[0];

  /* Update for DiscreteIntegrator: '<S1>/YawInt' */
  ((real_T *)ssGetDWork(S, 2))[0] = 0.01 * _rtB->BodyAngularVel + ((real_T *)
    ssGetDWork(S, 2))[0];

  /* Update for DiscreteIntegrator: '<S1>/PositionInt' */
  ((real_T *)ssGetDWork(S, 0))[0] = 0.01 * _rtB->BodyVel[0] + ((real_T *)
    ssGetDWork(S, 0))[0];

  /* Update for DiscreteIntegrator: '<S1>/BodyMomentum' */
  ((real_T *)ssGetDWork(S, 3))[0] = 0.01 * _rtB->BFF2IF[0] + ((real_T *)
    ssGetDWork(S, 3))[0];

  /* Update for DiscreteIntegrator: '<S1>/PositionInt' */
  ((real_T *)ssGetDWork(S, 0))[1] = 0.01 * _rtB->BodyVel[1] + ((real_T *)
    ssGetDWork(S, 0))[1];

  /* Update for DiscreteIntegrator: '<S1>/BodyMomentum' */
  ((real_T *)ssGetDWork(S, 3))[1] = 0.01 * _rtB->BFF2IF[1] + ((real_T *)
    ssGetDWork(S, 3))[1];

  /* Update for DiscreteIntegrator: '<S8>/WheelAngle' */
  ((real_T *)ssGetDWork(S, 4))[0] = 0.01 * _rtB->WheelInertia + ((real_T *)
    ssGetDWork(S, 4))[0];

  /* Update for DiscreteIntegrator: '<S16>/WheelMomentum' */
  ((real_T *)ssGetDWork(S, 5))[0] = 0.01 * _rtB->Sum1_o + ((real_T *)ssGetDWork
    (S, 5))[0];

  /* Update for DiscreteIntegrator: '<S7>/WheelAngle' */
  ((real_T *)ssGetDWork(S, 6))[0] = 0.01 * _rtB->WheelInertia_a + ((real_T *)
    ssGetDWork(S, 6))[0];

  /* Update for DiscreteIntegrator: '<S14>/WheelMomentum' */
  ((real_T *)ssGetDWork(S, 7))[0] = 0.01 * _rtB->Sum1_d + ((real_T *)ssGetDWork
    (S, 7))[0];

  /* Update for DiscreteIntegrator: '<S6>/WheelAngle' */
  ((real_T *)ssGetDWork(S, 8))[0] = 0.01 * _rtB->WheelInertia_l + ((real_T *)
    ssGetDWork(S, 8))[0];

  /* Update for DiscreteIntegrator: '<S12>/WheelMomentum' */
  ((real_T *)ssGetDWork(S, 9))[0] = 0.01 * _rtB->Sum1_l + ((real_T *)ssGetDWork
    (S, 9))[0];

  /* Update for DiscreteIntegrator: '<S5>/WheelAngle' */
  ((real_T *)ssGetDWork(S, 10))[0] = 0.01 * _rtB->WheelInertia_g + ((real_T *)
    ssGetDWork(S, 10))[0];

  /* Update for DiscreteIntegrator: '<S10>/WheelMomentum' */
  ((real_T *)ssGetDWork(S, 11))[0] = 0.01 * _rtB->Sum1 + ((real_T *)ssGetDWork(S,
    11))[0];
  UNUSED_PARAMETER(tid);
}

/* Termination for root system: '<Root>' */
static void mdlTerminate(SimStruct *S)
{
  UNUSED_PARAMETER(S);

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

  if (ssGetUserData(S) != (NULL) ) {
    rt_FREE(ssGetLocalBlockIO(S));
  }

  rt_FREE(ssGetUserData(S));

#endif

}

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#include "Subsystem_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 1);           /* Number of sample times */
  ssSetNumContStates(S, 0);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 6))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortVectorDimension(S, 0, 4))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 0, 0.01);
  ssSetOutputPortOffsetTime(S, 0, 0.0);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

  /* outport number: 1 */
  if (!ssSetOutputPortVectorDimension(S, 1, 2))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 1, 0.01);
  ssSetOutputPortOffsetTime(S, 1, 0.0);
  ssSetOutputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);

  /* outport number: 2 */
  if (!ssSetOutputPortVectorDimension(S, 2, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 2, 0.01);
  ssSetOutputPortOffsetTime(S, 2, 0.0);
  ssSetOutputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);

  /* outport number: 3 */
  if (!ssSetOutputPortVectorDimension(S, 3, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 3, 0.01);
  ssSetOutputPortOffsetTime(S, 3, 0.0);
  ssSetOutputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);

  /* outport number: 4 */
  if (!ssSetOutputPortVectorDimension(S, 4, 4))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 4, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 4, 0.01);
  ssSetOutputPortOffsetTime(S, 4, 0.0);
  ssSetOutputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);

  /* outport number: 5 */
  if (!ssSetOutputPortVectorDimension(S, 5, 2))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 5, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 5, 0.01);
  ssSetOutputPortOffsetTime(S, 5, 0.0);
  ssSetOutputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 1))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortVectorDimension(S, 0, 4))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_SINGLE);
    }

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortSampleTime(S, 0, 0.01);
    ssSetInputPortOffsetTime(S, 0, 0.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 16)) {
    return;
  }

  /* '<S1>/PositionInt': DSTATE */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 2);
  ssSetDWorkUsedAsDState(S, 0, 1);

  /* '<S1>/BodyAngularMomentum': DSTATE */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 1);
  ssSetDWorkUsedAsDState(S, 1, 1);

  /* '<S1>/YawInt': DSTATE */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 1);
  ssSetDWorkUsedAsDState(S, 2, 1);

  /* '<S1>/BodyMomentum': DSTATE */
  ssSetDWorkName(S, 3, "DWORK3");
  ssSetDWorkWidth(S, 3, 2);
  ssSetDWorkUsedAsDState(S, 3, 1);

  /* '<S8>/WheelAngle': DSTATE */
  ssSetDWorkName(S, 4, "DWORK4");
  ssSetDWorkWidth(S, 4, 1);
  ssSetDWorkUsedAsDState(S, 4, 1);

  /* '<S16>/WheelMomentum': DSTATE */
  ssSetDWorkName(S, 5, "DWORK5");
  ssSetDWorkWidth(S, 5, 1);
  ssSetDWorkUsedAsDState(S, 5, 1);

  /* '<S7>/WheelAngle': DSTATE */
  ssSetDWorkName(S, 6, "DWORK6");
  ssSetDWorkWidth(S, 6, 1);
  ssSetDWorkUsedAsDState(S, 6, 1);

  /* '<S14>/WheelMomentum': DSTATE */
  ssSetDWorkName(S, 7, "DWORK7");
  ssSetDWorkWidth(S, 7, 1);
  ssSetDWorkUsedAsDState(S, 7, 1);

  /* '<S6>/WheelAngle': DSTATE */
  ssSetDWorkName(S, 8, "DWORK8");
  ssSetDWorkWidth(S, 8, 1);
  ssSetDWorkUsedAsDState(S, 8, 1);

  /* '<S12>/WheelMomentum': DSTATE */
  ssSetDWorkName(S, 9, "DWORK9");
  ssSetDWorkWidth(S, 9, 1);
  ssSetDWorkUsedAsDState(S, 9, 1);

  /* '<S5>/WheelAngle': DSTATE */
  ssSetDWorkName(S, 10, "DWORK10");
  ssSetDWorkWidth(S, 10, 1);
  ssSetDWorkUsedAsDState(S, 10, 1);

  /* '<S10>/WheelMomentum': DSTATE */
  ssSetDWorkName(S, 11, "DWORK11");
  ssSetDWorkWidth(S, 11, 1);
  ssSetDWorkUsedAsDState(S, 11, 1);

  /* '<S10>/Sum': DWORK1 */
  ssSetDWorkName(S, 12, "DWORK12");
  ssSetDWorkWidth(S, 12, 1);

  /* '<S12>/Sum': DWORK1 */
  ssSetDWorkName(S, 13, "DWORK13");
  ssSetDWorkWidth(S, 13, 1);

  /* '<S14>/Sum': DWORK1 */
  ssSetDWorkName(S, 14, "DWORK14");
  ssSetDWorkWidth(S, 14, 1);

  /* '<S16>/Sum': DWORK1 */
  ssSetDWorkName(S, 15, "DWORK15");
  ssSetDWorkWidth(S, 15, 1);

  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 0);

  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL) ) {
      return;
    }
  } else {
    return;                /* Parameter mismatch will be reported by Simulink */
  }

#endif                                 /* MATLAB_MEX_FILE */

  /* Options */
  ssSetOptions(S, (SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_PORT_SAMPLE_TIMES_ASSIGNED ));

#if SS_SFCN_FOR_SIM

  {
    ssSupportsMultipleExecInstances(S, true);
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.01);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
}

#if defined(MATLAB_MEX_FILE)
#include "fixedpoint.c"
#include "simulink.c"
#else
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME                Subsystem_sf
#include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
