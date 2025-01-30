/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.213
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Jan 29 18:23:52 2025
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
#include <string.h>
#include <math.h>
#include "math.h"

/* Block signals and states (default storage) */
DW rtDW;
extern real32_T rt_powf_snf(real32_T u0, real32_T u1);
extern real32_T rt_atan2f_snf(real32_T u0, real32_T u1);
extern real32_T rt_hypotf_snf(real32_T u0, real32_T u1);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
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

/* Return rtInf needed by the generated code. */
static real_T rtGetInf(void)
{
  return rtInf;
}

/* Get rtInfF needed by the generated code. */
static real32_T rtGetInfF(void)
{
  return rtInfF;
}

/* Return rtMinusInf needed by the generated code. */
static real_T rtGetMinusInf(void)
{
  return rtMinusInf;
}

/* Return rtMinusInfF needed by the generated code. */
static real32_T rtGetMinusInfF(void)
{
  return rtMinusInfF;
}

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

real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    real32_T tmp;
    real32_T tmp_0;
    tmp = fabsf(u0);
    tmp_0 = fabsf(u1);
    if (rtIsInfF(u1)) {
      if (tmp == 1.0F) {
        y = 1.0F;
      } else if (tmp > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (tmp_0 == 0.0F) {
      y = 1.0F;
    } else if (tmp_0 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = sqrtf(u0);
    } else if ((u0 < 0.0F) && (u1 > floorf(u1))) {
      y = (rtNaNF);
    } else {
      y = powf(u0, u1);
    }
  }

  return y;
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
                     real32_T arg_AccRef[2], real32_T arg_YawRateRef, real32_T
                     arg_YawAccRef, real32_T arg_Accelerometer[2], real32_T
                     arg_Motorefforts[4], real32_T arg_Debug[32], real32_T
                     arg_Velest[2])
{
  int32_T i;
  int32_T ioIdx;
  real32_T rtb_VectorConcatenate1[32];
  real32_T rtb_Sum3[4];
  real32_T varargin_1[4];
  real32_T DigitalFilter_TEMP_STATES_idx_0;
  real32_T FilterDifferentiatorTF_tmp;
  real32_T TmpSignalConversionAtFilterDiff;
  real32_T arg_AccRef_0;
  real32_T arg_AccRef_1;
  real32_T arg_VelRef_0;
  real32_T arg_VelRef_1;
  real32_T arg_Wheelspeeds_0;
  real32_T arg_Wheelspeeds_1;
  real32_T pooled1;
  real32_T pooled1_0;
  real32_T q;
  real32_T rtb_FilterCoefficient_0;
  real32_T rtb_FilterCoefficient_idx_0;
  real32_T rtb_Saturation_idx_0;
  real32_T rtb_Saturation_idx_1;
  real32_T rtb_Sum;
  real32_T rtb_Sum2_idx_0;
  real32_T rtb_Sum_d_0;
  real32_T rtb_Sum_d_idx_0;
  real32_T rtb_y_c;
  real32_T u0;
  boolean_T exitg1;
  boolean_T rEQ0;
  UNUSED_PARAMETER(arg_YawRate);
  UNUSED_PARAMETER(arg_Accelerometer);

  /* SignalConversion generated from: '<Root>/Vector Concatenate1' */
  memset(&rtb_VectorConcatenate1[8], 0, 24U * sizeof(real32_T));

  /* Gain: '<S4>/Rad2M' incorporates:
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/WheelSpeeds'
   *  Product: '<S4>/Wheels2Body'
   */
  arg_Wheelspeeds_0 = arg_Wheelspeeds[0];
  DigitalFilter_TEMP_STATES_idx_0 = arg_Wheelspeeds[1];
  arg_Wheelspeeds_1 = arg_Wheelspeeds[2];
  rtb_Sum2_idx_0 = arg_Wheelspeeds[3];
  for (i = 0; i < 2; i++) {
    /* Product: '<S4>/Wheels2Body' incorporates:
     *  Constant: '<S4>/Constant'
     *  Gain: '<S4>/Rad2M'
     */
    rtDW.Wheels2Body[i] = ((0.027F * arg_Wheelspeeds_0 *
      rtConstP.Constant_Value_h[i] + rtConstP.Constant_Value_h[i + 2] * (0.027F *
      DigitalFilter_TEMP_STATES_idx_0)) + rtConstP.Constant_Value_h[i + 4] *
      (0.027F * arg_Wheelspeeds_1)) + rtConstP.Constant_Value_h[i + 6] * (0.027F
      * rtb_Sum2_idx_0);
  }

  /* S-Function (sdspbiquad): '<S63>/Digital Filter' */
  arg_Wheelspeeds_0 = (0.245237276F * rtDW.Wheels2Body[0] - -0.509525478F *
                       rtDW.DigitalFilter_FILT_STATES[0]) - 0.0F *
    rtDW.DigitalFilter_FILT_STATES[1];
  DigitalFilter_TEMP_STATES_idx_0 = arg_Wheelspeeds_0;
  rtDW.DigitalFilter[0] = (arg_Wheelspeeds_0 + rtDW.DigitalFilter_FILT_STATES[0])
    + 0.0F * rtDW.DigitalFilter_FILT_STATES[1];
  arg_Wheelspeeds_0 = (0.245237276F * rtDW.Wheels2Body[1] - -0.509525478F *
                       rtDW.DigitalFilter_FILT_STATES[2]) - 0.0F *
    rtDW.DigitalFilter_FILT_STATES[3];
  rtDW.DigitalFilter[1] = (arg_Wheelspeeds_0 + rtDW.DigitalFilter_FILT_STATES[2])
    + 0.0F * rtDW.DigitalFilter_FILT_STATES[3];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/VelRef'
   *  Sum: '<S4>/Sum'
   */
  arg_Wheelspeeds_1 = arg_VelRef[0] - rtDW.DigitalFilter[0];
  rtb_Sum2_idx_0 = arg_Wheelspeeds_1;

  /* Gain: '<S104>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S96>/Filter'
   *  Gain: '<S94>/Derivative Gain'
   *  Sum: '<S96>/SumD'
   */
  rtb_FilterCoefficient_0 = (0.0F * arg_Wheelspeeds_1 - rtDW.Filter_DSTATE[0]) *
    100.0F;
  rtb_FilterCoefficient_idx_0 = rtb_FilterCoefficient_0;

  /* Sum: '<S110>/Sum' incorporates:
   *  DiscreteIntegrator: '<S101>/Integrator'
   */
  rtb_Sum_d_0 = (arg_Wheelspeeds_1 + rtDW.Integrator_DSTATE[0]) +
    rtb_FilterCoefficient_0;
  rtb_Sum_d_idx_0 = rtb_Sum_d_0;

  /* Saturate: '<S108>/Saturation' */
  if (rtb_Sum_d_0 > 7.22962952F) {
    rtb_Saturation_idx_0 = 7.22962952F;
  } else if (rtb_Sum_d_0 < -7.22962952F) {
    rtb_Saturation_idx_0 = -7.22962952F;
  } else {
    rtb_Saturation_idx_0 = rtb_Sum_d_0;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/VelRef'
   *  Sum: '<S4>/Sum'
   */
  arg_Wheelspeeds_1 = arg_VelRef[1] - rtDW.DigitalFilter[1];

  /* Gain: '<S104>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S96>/Filter'
   *  Gain: '<S94>/Derivative Gain'
   *  Sum: '<S96>/SumD'
   */
  rtb_FilterCoefficient_0 = (0.0F * arg_Wheelspeeds_1 - rtDW.Filter_DSTATE[1]) *
    100.0F;

  /* Sum: '<S110>/Sum' incorporates:
   *  DiscreteIntegrator: '<S101>/Integrator'
   */
  rtb_Sum_d_0 = (arg_Wheelspeeds_1 + rtDW.Integrator_DSTATE[1]) +
    rtb_FilterCoefficient_0;

  /* Saturate: '<S108>/Saturation' */
  if (rtb_Sum_d_0 > 7.22962952F) {
    rtb_Saturation_idx_1 = 7.22962952F;
  } else if (rtb_Sum_d_0 < -7.22962952F) {
    rtb_Saturation_idx_1 = -7.22962952F;
  } else {
    rtb_Saturation_idx_1 = rtb_Sum_d_0;
  }

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

  /* Gain: '<S42>/Integral Gain' incorporates:
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  rtb_Sum = (rtb_y_c - 3.14159274F) * 0.1F;

  /* DiscreteIntegrator: '<S45>/Integrator' */
  q = 0.005F * rtb_Sum + rtDW.Integrator_DSTATE_h;

  /* DiscreteTransferFcn: '<S38>/Filter Differentiator TF' incorporates:
   *  Gain: '<S36>/Derivative Gain'
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  FilterDifferentiatorTF_tmp = (rtb_y_c - 3.14159274F) * 0.8F - -0.6F *
    rtDW.FilterDifferentiatorTF_states;

  /* Sum: '<Root>/Sum3' incorporates:
   *  DiscreteTransferFcn: '<S38>/Filter Differentiator TF'
   *  Gain: '<S48>/Filter Coefficient'
   *  Gain: '<S50>/Proportional Gain'
   *  Inport: '<Root>/YawAccRef'
   *  MATLAB Function: '<S1>/CubicCompensator'
   *  MATLAB Function: '<S1>/DeFlipper'
   *  Product: '<S38>/DenCoefOut'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S54>/Sum'
   */
  TmpSignalConversionAtFilterDiff = ((((rtb_y_c - 3.14159274F) * 9.0F + q) +
    (FilterDifferentiatorTF_tmp - rtDW.FilterDifferentiatorTF_states) * 0.8F *
    50.0F) + rt_powf_snf(rtb_y_c - 3.14159274F, 3.0F) * 100.0F) + arg_YawAccRef;
  rtb_Sum3[0] = TmpSignalConversionAtFilterDiff;

  /* MATLAB Function: '<S3>/Desaturator' incorporates:
   *  Sum: '<Root>/Sum3'
   */
  rtb_y_c = fabsf(TmpSignalConversionAtFilterDiff);
  varargin_1[0] = rtb_y_c;

  /* Sum: '<Root>/Sum3' */
  rtb_Sum3[1] = TmpSignalConversionAtFilterDiff;

  /* MATLAB Function: '<S3>/Desaturator' */
  varargin_1[1] = rtb_y_c;

  /* Sum: '<Root>/Sum3' */
  rtb_Sum3[2] = TmpSignalConversionAtFilterDiff;

  /* MATLAB Function: '<S3>/Desaturator' */
  varargin_1[2] = rtb_y_c;

  /* Sum: '<Root>/Sum3' */
  rtb_Sum3[3] = TmpSignalConversionAtFilterDiff;

  /* MATLAB Function: '<S3>/Desaturator' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  varargin_1[3] = rtb_y_c;
  if (!rtIsNaNF(rtb_y_c)) {
    i = 1;
  } else {
    i = 0;
    ioIdx = 2;
    exitg1 = false;
    while ((!exitg1) && (ioIdx < 5)) {
      if (!rtIsNaNF(varargin_1[ioIdx - 1])) {
        i = ioIdx;
        exitg1 = true;
      } else {
        ioIdx++;
      }
    }
  }

  if (i != 0) {
    rtb_y_c = varargin_1[i - 1];
    for (ioIdx = i + 1; ioIdx < 5; ioIdx++) {
      TmpSignalConversionAtFilterDiff = varargin_1[ioIdx - 1];
      if (rtb_y_c < TmpSignalConversionAtFilterDiff) {
        rtb_y_c = TmpSignalConversionAtFilterDiff;
      }
    }
  }

  TmpSignalConversionAtFilterDiff = rtb_y_c / 3.61481476F;
  if (1.0F - TmpSignalConversionAtFilterDiff < 0.0F) {
    rtb_y_c = 0.0F;
  } else if (rtIsNaNF(1.0F - TmpSignalConversionAtFilterDiff)) {
    rtb_y_c = 0.0F;
  } else {
    rtb_y_c = 1.0F - TmpSignalConversionAtFilterDiff;
  }

  if (TmpSignalConversionAtFilterDiff < 1.0F) {
    TmpSignalConversionAtFilterDiff = 1.0F;
  } else if (rtIsNaNF(TmpSignalConversionAtFilterDiff)) {
    TmpSignalConversionAtFilterDiff = 1.0F;
  }

  /* Gain: '<S2>/MassFeedForward' incorporates:
   *  Constant: '<S2>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/AccRef'
   *  Product: '<S2>/Body2Wheels'
   */
  arg_AccRef_0 = arg_AccRef[0];
  arg_AccRef_1 = arg_AccRef[1];

  /* Product: '<S65>/Body2Wheels' incorporates:
   *  Constant: '<S65>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/VelRef'
   */
  arg_VelRef_0 = arg_VelRef[1];
  arg_VelRef_1 = arg_VelRef[0];
  for (i = 0; i < 4; i++) {
    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Product: '<S2>/Body2Wheels'
     */
    pooled1 = rtConstP.pooled1[i];
    pooled1_0 = rtConstP.pooled1[i + 4];

    /* Saturate: '<Root>/DO NOT REMOVE THIS' incorporates:
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Constant: '<S6>/Constant1'
     *  Gain: '<Root>/ForceToTorque'
     *  Gain: '<S2>/MassFeedForward'
     *  Gain: '<S5>/IToV'
     *  Gain: '<S5>/OmegaToV'
     *  Gain: '<S5>/TorqueToI'
     *  Gain: '<S5>/VToPWM'
     *  Inport: '<Root>/WheelSpeeds'
     *  MATLAB Function: '<S3>/Desaturator'
     *  Product: '<S2>/Body2Wheels'
     *  Product: '<S6>/Body2Wheels'
     *  Sum: '<Root>/Sum1'
     *  Sum: '<S5>/Sum'
     */
    u0 = (((real32_T)((2.5F * arg_AccRef_0 * pooled1 + 2.5F * arg_AccRef_1 *
                       pooled1_0) + (rtConstP.Constant1_Value[i + 4] *
             rtb_Saturation_idx_1 + rtConstP.Constant1_Value[i] *
             rtb_Saturation_idx_0)) * rtb_y_c + rtb_Sum3[i] /
           TmpSignalConversionAtFilterDiff) * 0.027F * 30.4878044F *
          0.934579432F + 0.0328F * arg_Wheelspeeds[i]) * 0.0416666679F;
    if (u0 > 0.2F) {
      u0 = 0.2F;
    } else if (u0 < -0.2F) {
      u0 = -0.2F;
    }

    rtb_Sum3[i] = u0;

    /* End of Saturate: '<Root>/DO NOT REMOVE THIS' */

    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[i] = u0;

    /* SignalConversion generated from: '<Root>/Vector Concatenate' */
    rtb_VectorConcatenate1[i] = u0;

    /* MATLAB Function: '<S65>/MATLAB Function' incorporates:
     *  Constant: '<S65>/BodyForceCouplingMatrix'
     *  Product: '<S65>/Body2Wheels'
     */
    rtb_VectorConcatenate1[i + 4] = pooled1_0 * arg_VelRef_0 + pooled1 *
      arg_VelRef_1;
  }

  /* MATLAB Function: '<S65>/MATLAB Function' incorporates:
   *  Constant: '<S65>/Roborad'
   *  Inport: '<Root>/VelRef'
   *  Inport: '<Root>/YawRateRef'
   */
  TmpSignalConversionAtFilterDiff = rt_atan2f_snf(arg_VelRef[1], arg_VelRef[0]);
  rtb_y_c = rt_hypotf_snf(arg_VelRef[0], arg_VelRef[1]) / 0.1F;
  arg_AccRef_0 = 2.0626F * TmpSignalConversionAtFilterDiff;
  pooled1 = sinf(TmpSignalConversionAtFilterDiff + 1.0472F);
  arg_AccRef_1 = sinf(TmpSignalConversionAtFilterDiff - 1.0472F);
  arg_VelRef_0 = sinf(TmpSignalConversionAtFilterDiff - 2.3562F);
  arg_VelRef_1 = sinf(TmpSignalConversionAtFilterDiff + 2.3562F);
  TmpSignalConversionAtFilterDiff = 0.5F - cosf(fabsf(arg_YawRateRef / rtb_y_c) *
    3.14159274F) * 0.5F;
  if (rtIsNaNF(TmpSignalConversionAtFilterDiff)) {
    TmpSignalConversionAtFilterDiff = 1.0F;
  }

  if (fabsf(arg_YawRateRef) > rtb_y_c) {
    TmpSignalConversionAtFilterDiff = 1.0F;
  }

  rtb_y_c = TmpSignalConversionAtFilterDiff * 0.3F;
  if (rtIsNaNF(rtb_VectorConcatenate1[4])) {
    pooled1_0 = (rtNaNF);
  } else if (rtb_VectorConcatenate1[4] < 0.0F) {
    pooled1_0 = -1.0F;
  } else {
    pooled1_0 = (real32_T)(rtb_VectorConcatenate1[4] > 0.0F);
  }

  if (rtIsNaNF(pooled1)) {
    pooled1 = (rtNaNF);
  } else if (pooled1 < 0.0F) {
    pooled1 = -1.0F;
  } else {
    pooled1 = (real32_T)(pooled1 > 0.0F);
  }

  rtb_VectorConcatenate1[4] = ((sinf(arg_AccRef_0 - 0.764611661F) * 0.46F +
    1.23F) * pooled1 * (1.0F - TmpSignalConversionAtFilterDiff) + rtb_y_c) *
    pooled1_0;
  if (rtIsNaNF(rtb_VectorConcatenate1[5])) {
    pooled1_0 = (rtNaNF);
  } else if (rtb_VectorConcatenate1[5] < 0.0F) {
    pooled1_0 = -1.0F;
  } else {
    pooled1_0 = (real32_T)(rtb_VectorConcatenate1[5] > 0.0F);
  }

  if (rtIsNaNF(arg_AccRef_1)) {
    pooled1 = (rtNaNF);
  } else if (arg_AccRef_1 < 0.0F) {
    pooled1 = -1.0F;
  } else {
    pooled1 = (real32_T)(arg_AccRef_1 > 0.0F);
  }

  rtb_VectorConcatenate1[5] = ((sinf(arg_AccRef_0 - 2.33703566F) * 0.46F + 1.23F)
    * pooled1 * (1.0F - TmpSignalConversionAtFilterDiff) + rtb_y_c) * pooled1_0;
  if (rtIsNaNF(rtb_VectorConcatenate1[6])) {
    pooled1_0 = (rtNaNF);
  } else if (rtb_VectorConcatenate1[6] < 0.0F) {
    pooled1_0 = -1.0F;
  } else {
    pooled1_0 = (real32_T)(rtb_VectorConcatenate1[6] > 0.0F);
  }

  if (rtIsNaNF(arg_VelRef_0)) {
    pooled1 = (rtNaNF);
  } else if (arg_VelRef_0 < 0.0F) {
    pooled1 = -1.0F;
  } else {
    pooled1 = (real32_T)(arg_VelRef_0 > 0.0F);
  }

  rtb_VectorConcatenate1[6] = ((sinf(arg_AccRef_0 - 1.00311434F) * 0.46F + 1.23F)
    * pooled1 * (1.0F - TmpSignalConversionAtFilterDiff) + rtb_y_c) * pooled1_0;
  if (rtIsNaNF(rtb_VectorConcatenate1[7])) {
    pooled1_0 = (rtNaNF);
  } else if (rtb_VectorConcatenate1[7] < 0.0F) {
    pooled1_0 = -1.0F;
  } else {
    pooled1_0 = (real32_T)(rtb_VectorConcatenate1[7] > 0.0F);
  }

  if (rtIsNaNF(arg_VelRef_1)) {
    pooled1 = (rtNaNF);
  } else if (arg_VelRef_1 < 0.0F) {
    pooled1 = -1.0F;
  } else {
    pooled1 = (real32_T)(arg_VelRef_1 > 0.0F);
  }

  rtb_VectorConcatenate1[7] = ((sinf(arg_AccRef_0 + 4.16457F) * 0.46F + 1.23F) *
    pooled1 * (1.0F - TmpSignalConversionAtFilterDiff) + rtb_y_c) * pooled1_0;

  /* Outport: '<Root>/Velest' incorporates:
   *  Sum: '<S4>/Sum'
   */
  arg_Velest[0] = rtDW.DigitalFilter[0];
  arg_Velest[1] = rtDW.DigitalFilter[1];

  /* Outport: '<Root>/Debug' */
  memcpy(&arg_Debug[0], &rtb_VectorConcatenate1[0], sizeof(real32_T) << 5U);

  /* Update for S-Function (sdspbiquad): '<S63>/Digital Filter' */
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = DigitalFilter_TEMP_STATES_idx_0;

  /* Update for DiscreteIntegrator: '<S101>/Integrator' incorporates:
   *  Gain: '<S98>/Integral Gain'
   *  Sum: '<S93>/SumI2'
   *  Sum: '<S93>/SumI4'
   */
  rtDW.Integrator_DSTATE[0] += ((rtb_Saturation_idx_0 - rtb_Sum_d_idx_0) + 10.0F
    * rtb_Sum2_idx_0) * 0.01F;

  /* Update for DiscreteIntegrator: '<S96>/Filter' */
  rtDW.Filter_DSTATE[0] += 0.01F * rtb_FilterCoefficient_idx_0;

  /* Update for S-Function (sdspbiquad): '<S63>/Digital Filter' */
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = arg_Wheelspeeds_0;

  /* Update for DiscreteIntegrator: '<S101>/Integrator' incorporates:
   *  Gain: '<S98>/Integral Gain'
   *  Sum: '<Root>/Sum2'
   *  Sum: '<S110>/Sum'
   *  Sum: '<S93>/SumI2'
   *  Sum: '<S93>/SumI4'
   */
  rtDW.Integrator_DSTATE[1] += ((rtb_Saturation_idx_1 - rtb_Sum_d_0) + 10.0F *
    arg_Wheelspeeds_1) * 0.01F;

  /* Update for DiscreteIntegrator: '<S96>/Filter' incorporates:
   *  Gain: '<S104>/Filter Coefficient'
   */
  rtDW.Filter_DSTATE[1] += 0.01F * rtb_FilterCoefficient_0;

  /* Update for DiscreteIntegrator: '<S45>/Integrator' */
  rtDW.Integrator_DSTATE_h = 0.005F * rtb_Sum + q;

  /* Update for DiscreteTransferFcn: '<S38>/Filter Differentiator TF' */
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
