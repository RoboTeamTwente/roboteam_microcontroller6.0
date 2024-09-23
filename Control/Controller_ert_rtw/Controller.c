/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.50
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Sep 20 17:11:54 2024
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
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
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

/* Model step function */
void Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate, real32_T
                     arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef,
                     real32_T arg_AccRef[2], real_T arg_YawRateRef, real_T
                     arg_YawAccRef, real32_T arg_Motorefforts[4])
{
  int32_T b_k;
  int32_T idx;
  real32_T rtb_y[4];
  real32_T varargin_1[4];
  real32_T arg_AccRef_0;
  real32_T arg_AccRef_1;
  real32_T q;
  real32_T rtb_Sum;
  real32_T rtb_y_0;
  real32_T rtb_y_c;
  boolean_T exitg1;
  boolean_T rEQ0;
  UNUSED_PARAMETER(arg_YawRate);
  UNUSED_PARAMETER(arg_VelRef);
  UNUSED_PARAMETER(arg_YawRateRef);
  UNUSED_PARAMETER(arg_YawAccRef);

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Yaw'
   *  Inport: '<Root>/YawRef'
   */
  rtb_Sum = arg_YawRef - arg_Yaw;

  /* MATLAB Function: '<S1>/DeFlipper' */
  if (rtIsNaNF(rtb_Sum + 3.14159274F)) {
    rtb_y_c = (rtNaNF);
  } else if (rtIsInfF(rtb_Sum + 3.14159274F)) {
    rtb_y_c = (rtNaNF);
  } else if (rtb_Sum + 3.14159274F == 0.0F) {
    rtb_y_c = 0.0F;
  } else {
    rtb_y_c = fmodf(rtb_Sum + 3.14159274F, 6.28318548F);
    rEQ0 = (rtb_y_c == 0.0F);
    if (!rEQ0) {
      q = fabsf((rtb_Sum + 3.14159274F) / 6.28318548F);
      rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      rtb_y_c = 0.0F;
    } else if (rtb_Sum + 3.14159274F < 0.0F) {
      rtb_y_c += 6.28318548F;
    }
  }

  if (rtb_y_c < 0.0F) {
    rtb_y_c += 6.28318548F;
  }

  rtb_y_c -= 3.14159274F;

  /* End of MATLAB Function: '<S1>/DeFlipper' */

  /* Gain: '<S43>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S35>/Filter'
   *  Sum: '<S35>/SumD'
   */
  rtb_Sum = (rtb_y_c - rtDW.Filter_DSTATE) * 100.0F;

  /* Sum: '<S49>/Sum' incorporates:
   *  DiscreteIntegrator: '<S40>/Integrator'
   *  Gain: '<S45>/Proportional Gain'
   */
  q = (8.0F * rtb_y_c + rtDW.Integrator_DSTATE) + rtb_Sum;

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
  arg_AccRef_0 = arg_AccRef[0];
  arg_AccRef_1 = arg_AccRef[1];
  for (idx = 0; idx < 4; idx++) {
    /* MATLAB Function: '<S3>/Desaturator' incorporates:
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Gain: '<S2>/MassFeedForward'
     *  Product: '<S1>/Product'
     *  Product: '<S2>/Body2Wheels'
     */
    rtb_y_0 = (2.5F * arg_AccRef_0 * rtConstP.BodyForceCouplingMatrix_Value[idx]
               + rtConstP.BodyForceCouplingMatrix_Value[idx + 4] * (2.5F *
                arg_AccRef_1)) + q;
    rtb_y[idx] = rtb_y_0;
    varargin_1[idx] = fabsf(rtb_y_0);
  }

  /* MATLAB Function: '<S3>/Desaturator' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  if (!rtIsNaNF(varargin_1[0])) {
    idx = 1;
  } else {
    idx = 0;
    b_k = 2;
    exitg1 = false;
    while ((!exitg1) && (b_k < 5)) {
      if (!rtIsNaNF(varargin_1[b_k - 1])) {
        idx = b_k;
        exitg1 = true;
      } else {
        b_k++;
      }
    }
  }

  if (idx == 0) {
    q = varargin_1[0];
  } else {
    q = varargin_1[idx - 1];
    for (b_k = idx + 1; b_k < 5; b_k++) {
      arg_AccRef_0 = varargin_1[b_k - 1];
      if (q < arg_AccRef_0) {
        q = arg_AccRef_0;
      }
    }
  }

  q /= 37.0370369F;
  if (q > 1.0F) {
    rtb_y[0] /= q;
    rtb_y[1] /= q;
    rtb_y[2] /= q;
    rtb_y[3] /= q;
  }

  /* Gain: '<S4>/VToPWM' incorporates:
   *  Gain: '<Root>/ForceToTorque'
   *  Gain: '<S4>/IToV'
   *  Gain: '<S4>/TorqueToI'
   *  Gain: '<S58>/SpeedToTorque'
   *  Inport: '<Root>/Wheelspeeds'
   *  Sum: '<S4>/Sum1'
   */
  q = (0.027F * rtb_y[0] + 0.0001F * arg_Wheelspeeds[0]) * 30.4878044F *
    0.934579432F * 0.0416666679F;

  /* Saturate: '<Root>/Saturation' */
  if (q > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[0] = 0.1F;
  } else if (q < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[0] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[0] = q;
  }

  /* Gain: '<S4>/VToPWM' incorporates:
   *  Gain: '<Root>/ForceToTorque'
   *  Gain: '<S4>/IToV'
   *  Gain: '<S4>/TorqueToI'
   *  Gain: '<S58>/SpeedToTorque'
   *  Inport: '<Root>/Wheelspeeds'
   *  Sum: '<S4>/Sum1'
   */
  q = (0.027F * rtb_y[1] + 0.0001F * arg_Wheelspeeds[1]) * 30.4878044F *
    0.934579432F * 0.0416666679F;

  /* Saturate: '<Root>/Saturation' */
  if (q > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[1] = 0.1F;
  } else if (q < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[1] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[1] = q;
  }

  /* Gain: '<S4>/VToPWM' incorporates:
   *  Gain: '<Root>/ForceToTorque'
   *  Gain: '<S4>/IToV'
   *  Gain: '<S4>/TorqueToI'
   *  Gain: '<S58>/SpeedToTorque'
   *  Inport: '<Root>/Wheelspeeds'
   *  Sum: '<S4>/Sum1'
   */
  q = (0.027F * rtb_y[2] + 0.0001F * arg_Wheelspeeds[2]) * 30.4878044F *
    0.934579432F * 0.0416666679F;

  /* Saturate: '<Root>/Saturation' */
  if (q > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[2] = 0.1F;
  } else if (q < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[2] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[2] = q;
  }

  /* Gain: '<S4>/VToPWM' incorporates:
   *  Gain: '<Root>/ForceToTorque'
   *  Gain: '<S4>/IToV'
   *  Gain: '<S4>/TorqueToI'
   *  Gain: '<S58>/SpeedToTorque'
   *  Inport: '<Root>/Wheelspeeds'
   *  Sum: '<S4>/Sum1'
   */
  q = (0.027F * rtb_y[3] + 0.0001F * arg_Wheelspeeds[3]) * 30.4878044F *
    0.934579432F * 0.0416666679F;

  /* Saturate: '<Root>/Saturation' */
  if (q > 0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[3] = 0.1F;
  } else if (q < -0.1F) {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[3] = -0.1F;
  } else {
    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[3] = q;
  }

  /* Update for DiscreteIntegrator: '<S40>/Integrator' incorporates:
   *  Gain: '<S37>/Integral Gain'
   */
  rtDW.Integrator_DSTATE += 0.0F * rtb_y_c * 0.01F;

  /* Update for DiscreteIntegrator: '<S35>/Filter' */
  rtDW.Filter_DSTATE += 0.01F * rtb_Sum;
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
