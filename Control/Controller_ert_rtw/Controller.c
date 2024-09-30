/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.84
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Sep 27 13:17:58 2024
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

/* Model step function */
void Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate, real32_T
                     arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef,
                     real32_T arg_AccRef[2], real_T arg_YawRateRef, real_T
                     arg_YawAccRef, real32_T arg_Motorefforts[4])
{
  int32_T b_k;
  int32_T idx;
  real32_T rtb_Product[4];
  real32_T varargin_1[4];
  real32_T FilterDifferentiatorTF_tmp;
  real32_T arg_AccRef_0;
  real32_T arg_AccRef_1;
  real32_T q;
  real32_T rtb_FilterDifferentiatorTF;
  real32_T rtb_Sum;
  real32_T rtb_y_c;
  real32_T u0;
  boolean_T exitg1;
  boolean_T rEQ0;
  UNUSED_PARAMETER(arg_Wheelspeeds);
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

  /* Gain: '<S39>/Integral Gain' incorporates:
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  rtb_Sum = (rtb_y_c - 3.14159274F) * 0.0F;

  /* DiscreteIntegrator: '<S42>/Integrator' */
  q = 0.005F * rtb_Sum + rtDW.Integrator_DSTATE;

  /* DiscreteTransferFcn: '<S35>/Filter Differentiator TF' incorporates:
   *  Gain: '<S33>/Derivative Gain'
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  FilterDifferentiatorTF_tmp = (rtb_y_c - 3.14159274F) * 0.4F - -0.333333343F *
    rtDW.FilterDifferentiatorTF_states;

  /* Sum: '<S51>/Sum' incorporates:
   *  DiscreteTransferFcn: '<S35>/Filter Differentiator TF'
   *  Gain: '<S45>/Filter Coefficient'
   *  Gain: '<S47>/Proportional Gain'
   *  MATLAB Function: '<S1>/DeFlipper'
   *  Product: '<S35>/DenCoefOut'
   */
  rtb_y_c = ((rtb_y_c - 3.14159274F) * 3.0F + q) + (FilterDifferentiatorTF_tmp -
    rtDW.FilterDifferentiatorTF_states) * 0.666666687F * 100.0F;

  /* Product: '<S1>/Product' */
  rtb_Product[0] = rtb_y_c;

  /* MATLAB Function: '<S3>/Desaturator' incorporates:
   *  Product: '<S1>/Product'
   */
  rtb_FilterDifferentiatorTF = fabsf(rtb_y_c);
  varargin_1[0] = rtb_FilterDifferentiatorTF;

  /* Product: '<S1>/Product' */
  rtb_Product[1] = rtb_y_c;

  /* MATLAB Function: '<S3>/Desaturator' */
  varargin_1[1] = rtb_FilterDifferentiatorTF;

  /* Product: '<S1>/Product' */
  rtb_Product[2] = rtb_y_c;

  /* MATLAB Function: '<S3>/Desaturator' */
  varargin_1[2] = rtb_FilterDifferentiatorTF;

  /* Product: '<S1>/Product' */
  rtb_Product[3] = rtb_y_c;

  /* MATLAB Function: '<S3>/Desaturator' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  varargin_1[3] = rtb_FilterDifferentiatorTF;
  if (!rtIsNaNF(rtb_FilterDifferentiatorTF)) {
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
    rtb_y_c = rtb_FilterDifferentiatorTF;
  } else {
    rtb_y_c = varargin_1[idx - 1];
    for (b_k = idx + 1; b_k < 5; b_k++) {
      rtb_FilterDifferentiatorTF = varargin_1[b_k - 1];
      if (rtb_y_c < rtb_FilterDifferentiatorTF) {
        rtb_y_c = rtb_FilterDifferentiatorTF;
      }
    }
  }

  rtb_FilterDifferentiatorTF = rtb_y_c / 37.0370369F;
  if (1.0F - rtb_FilterDifferentiatorTF < 0.0F) {
    rtb_y_c = 0.0F;
  } else if (rtIsNaNF(1.0F - rtb_FilterDifferentiatorTF)) {
    rtb_y_c = 0.0F;
  } else {
    rtb_y_c = 1.0F - rtb_FilterDifferentiatorTF;
  }

  if (rtb_FilterDifferentiatorTF < 1.0F) {
    rtb_FilterDifferentiatorTF = 1.0F;
  } else if (rtIsNaNF(rtb_FilterDifferentiatorTF)) {
    rtb_FilterDifferentiatorTF = 1.0F;
  }

  /* Gain: '<S2>/MassFeedForward' incorporates:
   *  Constant: '<S2>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/AccRef'
   *  Product: '<S2>/Body2Wheels'
   */
  arg_AccRef_0 = arg_AccRef[0];
  arg_AccRef_1 = arg_AccRef[1];
  for (idx = 0; idx < 4; idx++) {
    /* Saturate: '<Root>/Saturation' incorporates:
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Gain: '<Root>/ForceToTorque'
     *  Gain: '<S2>/MassFeedForward'
     *  Gain: '<S4>/IToV'
     *  Gain: '<S4>/TorqueToI'
     *  Gain: '<S4>/VToPWM'
     *  MATLAB Function: '<S3>/Desaturator'
     *  Product: '<S2>/Body2Wheels'
     */
    u0 = ((12.5F * arg_AccRef_0 * rtConstP.pooled1[idx] + rtConstP.pooled1[idx +
           4] * (12.5F * arg_AccRef_1)) * rtb_y_c + rtb_Product[idx] /
          rtb_FilterDifferentiatorTF) * 0.027F * 30.4878044F * 0.934579432F *
      0.0416666679F;
    if (u0 > 0.1F) {
      /* Outport: '<Root>/Motorefforts' */
      arg_Motorefforts[idx] = 0.1F;
    } else if (u0 < -0.1F) {
      /* Outport: '<Root>/Motorefforts' */
      arg_Motorefforts[idx] = -0.1F;
    } else {
      /* Outport: '<Root>/Motorefforts' */
      arg_Motorefforts[idx] = u0;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* Update for DiscreteIntegrator: '<S42>/Integrator' */
  rtDW.Integrator_DSTATE = 0.005F * rtb_Sum + q;

  /* Update for DiscreteTransferFcn: '<S35>/Filter Differentiator TF' */
  rtDW.FilterDifferentiatorTF_states = FilterDifferentiatorTF_tmp;
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
