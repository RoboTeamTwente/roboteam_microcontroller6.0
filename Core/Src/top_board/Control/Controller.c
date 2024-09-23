/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Sep 23 16:23:19 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Controller.h"
#include "rtwtypes.h"
#include <math.h>
#include "math.h"

/* Block signals and states (default storage) */
DW rtDW;
extern real32_T rt_atan2f_snf(real32_T u0, real32_T u1);
extern real32_T rt_hypotf_snf(real32_T u0, real32_T u1);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

/* Return rtNaN needed by the generated code. */
static real_T rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2f((real32_T)tmp, (real32_T)tmp_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = atan2f(u0, u1);
  }

  return y;
}

real32_T rt_hypotf_snf(real32_T u0, real32_T u1)
{
  real32_T a;
  real32_T b;
  real32_T y;
  a = fabsf(u0);
  b = fabsf(u1);
  if (a < b) {
    a /= b;
    y = sqrtf(a * a + 1.0F) * b;
  } else if (a > b) {
    b /= a;
    y = sqrtf(b * b + 1.0F) * a;
  } else if (rtIsNaNF(b)) {
    y = (rtNaNF);
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/* Model step function */
void Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate, real32_T
                     arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef,
                     real32_T arg_AccRef[2], real_T arg_YawRateRef, real_T
                     arg_YawAccRef, real32_T arg_Motorefforts[4])
{
  int32_T b_k;
  int32_T idx;
  real32_T rtb_y[4];
  real32_T x[4];
  real32_T y_sign[4];
  real32_T arg_VelRef_0;
  real32_T arg_VelRef_1;
  real32_T b_gamma;
  real32_T q;
  real32_T rtb_y_0;
  real32_T vw_max_round_to_rotational;
  real32_T y_sign_0;
  boolean_T rEQ0;
  static const real32_T b[4] = { 1.0472F, -1.0472F, -2.3562F, 2.3562F };

  static const real32_T c[4] = { -0.764611661F, -2.33703566F, -1.00311434F,
    4.16457F };

  boolean_T exitg1;
  UNUSED_PARAMETER(arg_Wheelspeeds);
  UNUSED_PARAMETER(arg_YawRate);
  UNUSED_PARAMETER(arg_YawAccRef);

  /* MATLAB Function: '<S58>/MATLAB Function' incorporates:
   *  Constant: '<S58>/Roborad'
   *  Inport: '<Root>/VelRef'
   */
  b_gamma = rt_atan2f_snf(arg_VelRef[1], arg_VelRef[0]);
  vw_max_round_to_rotational = rt_hypotf_snf(arg_VelRef[0], arg_VelRef[1]) /
    0.0804F;
  q = 2.0626F * b_gamma;

  /* Product: '<S58>/Body2Wheels' incorporates:
   *  Constant: '<S58>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/VelRef'
   */
  arg_VelRef_0 = arg_VelRef[1];
  arg_VelRef_1 = arg_VelRef[0];

  /* MATLAB Function: '<S58>/MATLAB Function' incorporates:
   *  Constant: '<S58>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/YawRateRef'
   *  Product: '<S58>/Body2Wheels'
   */
  for (b_k = 0; b_k < 4; b_k++) {
    rtb_y_0 = rtConstP.pooled1[b_k + 4] * arg_VelRef_0 + rtConstP.pooled1[b_k] *
      arg_VelRef_1;
    y_sign_0 = sinf(b_gamma + b[b_k]);
    if (rtIsNaNF(y_sign_0)) {
      y_sign[b_k] = (rtNaNF);
    } else if (y_sign_0 < 0.0F) {
      y_sign[b_k] = -1.0F;
    } else {
      y_sign[b_k] = (real32_T)(y_sign_0 > 0.0F);
    }

    x[b_k] = sinf(q + c[b_k]);
    if (rtIsNaNF(rtb_y_0)) {
      rtb_y[b_k] = (rtNaNF);
    } else if (rtb_y_0 < 0.0F) {
      rtb_y[b_k] = -1.0F;
    } else {
      rtb_y[b_k] = (real32_T)(rtb_y_0 > 0.0F);
    }
  }

  b_gamma = 0.5F - cosf(fabsf((real32_T)arg_YawRateRef /
    vw_max_round_to_rotational) * 3.14159274F) * 0.5F;
  if (rtIsNaNF(b_gamma)) {
    b_gamma = 1.0F;
  }

  if (fabs(arg_YawRateRef) > vw_max_round_to_rotational) {
    b_gamma = 1.0F;
  }

  vw_max_round_to_rotational = b_gamma * 0.3F;
  rtb_y[0] *= (0.46F * x[0] + 1.23F) * y_sign[0] * (1.0F - b_gamma) +
    vw_max_round_to_rotational;
  rtb_y[1] *= (0.46F * x[1] + 1.23F) * y_sign[1] * (1.0F - b_gamma) +
    vw_max_round_to_rotational;
  rtb_y[2] *= (0.46F * x[2] + 1.23F) * y_sign[2] * (1.0F - b_gamma) +
    vw_max_round_to_rotational;
  rtb_y[3] *= (0.46F * x[3] + 1.23F) * y_sign[3] * (1.0F - b_gamma) +
    vw_max_round_to_rotational;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Yaw'
   *  Inport: '<Root>/YawRef'
   */
  b_gamma = arg_YawRef - arg_Yaw;

  /* MATLAB Function: '<S1>/DeFlipper' */
  if (rtIsNaNF(b_gamma + 3.14159274F)) {
    vw_max_round_to_rotational = (rtNaNF);
  } else if (rtIsInfF(b_gamma + 3.14159274F)) {
    vw_max_round_to_rotational = (rtNaNF);
  } else if (b_gamma + 3.14159274F == 0.0F) {
    vw_max_round_to_rotational = 0.0F;
  } else {
    vw_max_round_to_rotational = fmodf(b_gamma + 3.14159274F, 6.28318548F);
    rEQ0 = (vw_max_round_to_rotational == 0.0F);
    if (!rEQ0) {
      q = fabsf((b_gamma + 3.14159274F) / 6.28318548F);
      rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      vw_max_round_to_rotational = 0.0F;
    } else if (b_gamma + 3.14159274F < 0.0F) {
      vw_max_round_to_rotational += 6.28318548F;
    }
  }

  if (vw_max_round_to_rotational < 0.0F) {
    vw_max_round_to_rotational += 6.28318548F;
  }

  vw_max_round_to_rotational -= 3.14159274F;

  /* End of MATLAB Function: '<S1>/DeFlipper' */

  /* Gain: '<S43>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S35>/Filter'
   *  Gain: '<S33>/Derivative Gain'
   *  Sum: '<S35>/SumD'
   */
  b_gamma = (2.0F * vw_max_round_to_rotational - rtDW.Filter_DSTATE) * 100.0F;

  /* Sum: '<S49>/Sum' incorporates:
   *  DiscreteIntegrator: '<S40>/Integrator'
   *  Gain: '<S45>/Proportional Gain'
   */
  q = (16.0F * vw_max_round_to_rotational + rtDW.Integrator_DSTATE) + b_gamma;

  /* Saturate: '<S1>/Saturation' */
  if (q > 0.1F) {
    q = 0.1F;
  } else if (q < -0.1F) {
    q = -0.1F;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Gain: '<S2>/MassFeedForward' incorporates:
   *  Constant: '<S2>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/AccRef'
   *  Product: '<S2>/Body2Wheels'
   */
  arg_VelRef_0 = arg_AccRef[0];
  arg_VelRef_1 = arg_AccRef[1];
  for (idx = 0; idx < 4; idx++) {
    /* MATLAB Function: '<S3>/Desaturator' incorporates:
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Gain: '<S2>/MassFeedForward'
     *  Product: '<S1>/Product'
     *  Product: '<S2>/Body2Wheels'
     */
    y_sign_0 = (12.5F * arg_VelRef_0 * rtConstP.pooled1[idx] +
                rtConstP.pooled1[idx + 4] * (12.5F * arg_VelRef_1)) + q;
    y_sign[idx] = y_sign_0;
    x[idx] = fabsf(y_sign_0);
  }

  /* MATLAB Function: '<S3>/Desaturator' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  if (!rtIsNaNF(x[0])) {
    idx = 1;
  } else {
    idx = 0;
    b_k = 2;
    exitg1 = false;
    while ((!exitg1) && (b_k < 5)) {
      if (!rtIsNaNF(x[b_k - 1])) {
        idx = b_k;
        exitg1 = true;
      } else {
        b_k++;
      }
    }
  }

  if (idx == 0) {
    q = x[0];
  } else {
    q = x[idx - 1];
    for (b_k = idx + 1; b_k < 5; b_k++) {
      y_sign_0 = x[b_k - 1];
      if (q < y_sign_0) {
        q = y_sign_0;
      }
    }
  }

  q /= 37.0370369F;
  if (q > 1.0F) {
    y_sign[0] /= q;
    y_sign[1] /= q;
    y_sign[2] /= q;
    y_sign[3] /= q;
  }

  /* Saturate: '<Root>/Saturation' incorporates:
   *  Gain: '<Root>/ForceToTorque'
   *  Gain: '<S4>/IToV'
   *  Gain: '<S4>/TorqueToI'
   *  Gain: '<S4>/VToPWM'
   *  Sum: '<S4>/Sum'
   */
  y_sign_0 = (0.027F * y_sign[0] * 30.4878044F * 0.934579432F + rtb_y[0]) *
    0.0416666679F;
  if (y_sign_0 > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[0] = 0.1F;
  } else if (y_sign_0 < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[0] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[0] = y_sign_0;
  }

  y_sign_0 = (0.027F * y_sign[1] * 30.4878044F * 0.934579432F + rtb_y[1]) *
    0.0416666679F;
  if (y_sign_0 > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[1] = 0.1F;
  } else if (y_sign_0 < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[1] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[1] = y_sign_0;
  }

  y_sign_0 = (0.027F * y_sign[2] * 30.4878044F * 0.934579432F + rtb_y[2]) *
    0.0416666679F;
  if (y_sign_0 > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[2] = 0.1F;
  } else if (y_sign_0 < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[2] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[2] = y_sign_0;
  }

  y_sign_0 = (0.027F * y_sign[3] * 30.4878044F * 0.934579432F + rtb_y[3]) *
    0.0416666679F;
  if (y_sign_0 > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[3] = 0.1F;
  } else if (y_sign_0 < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[3] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[3] = y_sign_0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Update for DiscreteIntegrator: '<S40>/Integrator' incorporates:
   *  Gain: '<S37>/Integral Gain'
   */
  rtDW.Integrator_DSTATE += 0.0F * vw_max_round_to_rotational * 0.01F;

  /* Update for DiscreteIntegrator: '<S35>/Filter' */
  rtDW.Filter_DSTATE += 0.01F * b_gamma;
}

/* Model initialize function */
void Controller_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
