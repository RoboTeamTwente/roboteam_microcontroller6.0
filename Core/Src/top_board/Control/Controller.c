/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.116
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Nov  8 14:41:18 2024
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
                     real32_T arg_AccRef[2], real32_T arg_YawRateRef, real32_T
                     arg_YawAccRef, real32_T arg_Accelerometer[2], real32_T
                     arg_Motorefforts[4])
{
  real_T rtb_FilterCoefficient[2];
  real_T rtb_FilterCoefficient_tmp[2];
  real_T rtb_Sum2[2];
  real_T rtb_Sum2_0;
  real_T tmp;
  int32_T idx;
  int32_T ioIdx;
  real32_T rtb_Rad2M[4];
  real32_T varargin_1[4];
  real32_T FilterDifferentiatorTF_tmp;
  real32_T arg_AccRef_0;
  real32_T arg_AccRef_1;
  real32_T q;
  real32_T rtb_FilterDifferentiatorTF;
  real32_T rtb_Sum_n;
  real32_T rtb_y_c;
  real32_T u0;
  boolean_T exitg1;
  boolean_T rEQ0;
  UNUSED_PARAMETER(arg_YawRate);
  UNUSED_PARAMETER(arg_YawRateRef);
  UNUSED_PARAMETER(arg_Accelerometer);

  /* S-Function (sdspbiquad): '<S3>/Digital Filter' incorporates:
   *  Inport: '<Root>/WheelSpeeds'
   */
  rtb_Sum_n = (0.102997117F * arg_Wheelspeeds[0] - -1.38894427F *
               rtDW.DigitalFilter_FILT_STATES[0]) - 0.800932765F *
    rtDW.DigitalFilter_FILT_STATES[1];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[0] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[1];
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = rtb_Sum_n;
  rtb_Sum_n = (0.0867664218F * q - -1.17006886F *
               rtDW.DigitalFilter_FILT_STATES[2]) - 0.517134547F *
    rtDW.DigitalFilter_FILT_STATES[3];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[2] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[3];
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = rtb_Sum_n;
  rtb_Sum_n = (0.0768889785F * q - -1.03686893F *
               rtDW.DigitalFilter_FILT_STATES[4]) - 0.344424844F *
    rtDW.DigitalFilter_FILT_STATES[5];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[4] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[5];
  rtDW.DigitalFilter_FILT_STATES[5] = rtDW.DigitalFilter_FILT_STATES[4];
  rtDW.DigitalFilter_FILT_STATES[4] = rtb_Sum_n;
  rtb_Sum_n = (0.0715710074F * q - -0.965154648F *
               rtDW.DigitalFilter_FILT_STATES[6]) - 0.251438677F *
    rtDW.DigitalFilter_FILT_STATES[7];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[6] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[7];
  rtDW.DigitalFilter_FILT_STATES[7] = rtDW.DigitalFilter_FILT_STATES[6];
  rtDW.DigitalFilter_FILT_STATES[6] = rtb_Sum_n;
  rtb_Sum_n = (0.264371276F * q - -0.471257478F *
               rtDW.DigitalFilter_FILT_STATES[8]) - 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtb_Rad2M[0] = (rtb_Sum_n + rtDW.DigitalFilter_FILT_STATES[8]) + 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtDW.DigitalFilter_FILT_STATES[9] = rtDW.DigitalFilter_FILT_STATES[8];
  rtDW.DigitalFilter_FILT_STATES[8] = rtb_Sum_n;
  rtb_Sum_n = (0.102997117F * arg_Wheelspeeds[1] - -1.38894427F *
               rtDW.DigitalFilter_FILT_STATES[0]) - 0.800932765F *
    rtDW.DigitalFilter_FILT_STATES[1];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[0] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[1];
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = rtb_Sum_n;
  rtb_Sum_n = (0.0867664218F * q - -1.17006886F *
               rtDW.DigitalFilter_FILT_STATES[2]) - 0.517134547F *
    rtDW.DigitalFilter_FILT_STATES[3];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[2] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[3];
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = rtb_Sum_n;
  rtb_Sum_n = (0.0768889785F * q - -1.03686893F *
               rtDW.DigitalFilter_FILT_STATES[4]) - 0.344424844F *
    rtDW.DigitalFilter_FILT_STATES[5];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[4] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[5];
  rtDW.DigitalFilter_FILT_STATES[5] = rtDW.DigitalFilter_FILT_STATES[4];
  rtDW.DigitalFilter_FILT_STATES[4] = rtb_Sum_n;
  rtb_Sum_n = (0.0715710074F * q - -0.965154648F *
               rtDW.DigitalFilter_FILT_STATES[6]) - 0.251438677F *
    rtDW.DigitalFilter_FILT_STATES[7];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[6] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[7];
  rtDW.DigitalFilter_FILT_STATES[7] = rtDW.DigitalFilter_FILT_STATES[6];
  rtDW.DigitalFilter_FILT_STATES[6] = rtb_Sum_n;
  rtb_Sum_n = (0.264371276F * q - -0.471257478F *
               rtDW.DigitalFilter_FILT_STATES[8]) - 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtb_Rad2M[1] = (rtb_Sum_n + rtDW.DigitalFilter_FILT_STATES[8]) + 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtDW.DigitalFilter_FILT_STATES[9] = rtDW.DigitalFilter_FILT_STATES[8];
  rtDW.DigitalFilter_FILT_STATES[8] = rtb_Sum_n;
  rtb_Sum_n = (0.102997117F * arg_Wheelspeeds[2] - -1.38894427F *
               rtDW.DigitalFilter_FILT_STATES[0]) - 0.800932765F *
    rtDW.DigitalFilter_FILT_STATES[1];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[0] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[1];
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = rtb_Sum_n;
  rtb_Sum_n = (0.0867664218F * q - -1.17006886F *
               rtDW.DigitalFilter_FILT_STATES[2]) - 0.517134547F *
    rtDW.DigitalFilter_FILT_STATES[3];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[2] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[3];
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = rtb_Sum_n;
  rtb_Sum_n = (0.0768889785F * q - -1.03686893F *
               rtDW.DigitalFilter_FILT_STATES[4]) - 0.344424844F *
    rtDW.DigitalFilter_FILT_STATES[5];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[4] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[5];
  rtDW.DigitalFilter_FILT_STATES[5] = rtDW.DigitalFilter_FILT_STATES[4];
  rtDW.DigitalFilter_FILT_STATES[4] = rtb_Sum_n;
  rtb_Sum_n = (0.0715710074F * q - -0.965154648F *
               rtDW.DigitalFilter_FILT_STATES[6]) - 0.251438677F *
    rtDW.DigitalFilter_FILT_STATES[7];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[6] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[7];
  rtDW.DigitalFilter_FILT_STATES[7] = rtDW.DigitalFilter_FILT_STATES[6];
  rtDW.DigitalFilter_FILT_STATES[6] = rtb_Sum_n;
  rtb_Sum_n = (0.264371276F * q - -0.471257478F *
               rtDW.DigitalFilter_FILT_STATES[8]) - 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtb_Rad2M[2] = (rtb_Sum_n + rtDW.DigitalFilter_FILT_STATES[8]) + 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtDW.DigitalFilter_FILT_STATES[9] = rtDW.DigitalFilter_FILT_STATES[8];
  rtDW.DigitalFilter_FILT_STATES[8] = rtb_Sum_n;
  rtb_Sum_n = (0.102997117F * arg_Wheelspeeds[3] - -1.38894427F *
               rtDW.DigitalFilter_FILT_STATES[0]) - 0.800932765F *
    rtDW.DigitalFilter_FILT_STATES[1];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[0] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[1];
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = rtb_Sum_n;
  rtb_Sum_n = (0.0867664218F * q - -1.17006886F *
               rtDW.DigitalFilter_FILT_STATES[2]) - 0.517134547F *
    rtDW.DigitalFilter_FILT_STATES[3];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[2] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[3];
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = rtb_Sum_n;
  rtb_Sum_n = (0.0768889785F * q - -1.03686893F *
               rtDW.DigitalFilter_FILT_STATES[4]) - 0.344424844F *
    rtDW.DigitalFilter_FILT_STATES[5];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[4] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[5];
  rtDW.DigitalFilter_FILT_STATES[5] = rtDW.DigitalFilter_FILT_STATES[4];
  rtDW.DigitalFilter_FILT_STATES[4] = rtb_Sum_n;
  rtb_Sum_n = (0.0715710074F * q - -0.965154648F *
               rtDW.DigitalFilter_FILT_STATES[6]) - 0.251438677F *
    rtDW.DigitalFilter_FILT_STATES[7];
  q = (2.0F * rtDW.DigitalFilter_FILT_STATES[6] + rtb_Sum_n) +
    rtDW.DigitalFilter_FILT_STATES[7];
  rtDW.DigitalFilter_FILT_STATES[7] = rtDW.DigitalFilter_FILT_STATES[6];
  rtDW.DigitalFilter_FILT_STATES[6] = rtb_Sum_n;
  rtb_Sum_n = (0.264371276F * q - -0.471257478F *
               rtDW.DigitalFilter_FILT_STATES[8]) - 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtb_Rad2M[3] = (rtb_Sum_n + rtDW.DigitalFilter_FILT_STATES[8]) + 0.0F *
    rtDW.DigitalFilter_FILT_STATES[9];
  rtDW.DigitalFilter_FILT_STATES[9] = rtDW.DigitalFilter_FILT_STATES[8];
  rtDW.DigitalFilter_FILT_STATES[8] = rtb_Sum_n;

  /* Gain: '<Root>/Rad2M' incorporates:
   *  Constant: '<Root>/Constant'
   *  Product: '<Root>/Wheels2Body'
   */
  rtb_Sum_n = rtb_Rad2M[0];
  q = rtb_Rad2M[1];
  rtb_y_c = rtb_Rad2M[2];
  FilterDifferentiatorTF_tmp = rtb_Rad2M[3];
  for (idx = 0; idx < 2; idx++) {
    /* Sum: '<Root>/Sum2' incorporates:
     *  Constant: '<Root>/Constant'
     *  Gain: '<Root>/Rad2M'
     *  Inport: '<Root>/VelRef'
     *  Product: '<Root>/Wheels2Body'
     */
    rtb_Sum2_0 = arg_VelRef[idx] - (((0.025F * rtb_Sum_n *
      rtConstP.Constant_Value[idx] + rtConstP.Constant_Value[idx + 2] * (0.025F *
      q)) + rtConstP.Constant_Value[idx + 4] * (0.025F * rtb_y_c)) +
      rtConstP.Constant_Value[idx + 6] * (0.025F * FilterDifferentiatorTF_tmp));
    rtb_Sum2[idx] = rtb_Sum2_0;

    /* Gain: '<S89>/Derivative Gain' incorporates:
     *  Gain: '<S93>/Integral Gain'
     */
    rtb_Sum2_0 *= 0.0;
    rtb_FilterCoefficient_tmp[idx] = rtb_Sum2_0;

    /* Gain: '<S99>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S91>/Filter'
     *  Gain: '<S89>/Derivative Gain'
     *  Sum: '<S91>/SumD'
     */
    rtb_FilterCoefficient[idx] = (rtb_Sum2_0 - rtDW.Filter_DSTATE[idx]) * 100.0;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Yaw'
   *  Inport: '<Root>/YawRef'
   */
  rtb_Sum_n = arg_YawRef - arg_Yaw;

  /* MATLAB Function: '<S1>/DeFlipper' */
  if (rtIsNaNF(rtb_Sum_n + 3.14159274F)) {
    rtb_y_c = (rtNaNF);
  } else if (rtIsInfF(rtb_Sum_n + 3.14159274F)) {
    rtb_y_c = (rtNaNF);
  } else if (rtb_Sum_n + 3.14159274F == 0.0F) {
    rtb_y_c = 0.0F;
  } else {
    rtb_y_c = fmodf(rtb_Sum_n + 3.14159274F, 6.28318548F);
    rEQ0 = (rtb_y_c == 0.0F);
    if (!rEQ0) {
      q = fabsf((rtb_Sum_n + 3.14159274F) / 6.28318548F);
      rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      rtb_y_c = 0.0F;
    } else if (rtb_Sum_n + 3.14159274F < 0.0F) {
      rtb_y_c += 6.28318548F;
    }
  }

  if (rtb_y_c < 0.0F) {
    rtb_y_c += 6.28318548F;
  }

  /* Gain: '<S41>/Integral Gain' incorporates:
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  rtb_Sum_n = (rtb_y_c - 3.14159274F) * 0.0F;

  /* DiscreteIntegrator: '<S44>/Integrator' */
  q = 0.005F * rtb_Sum_n + rtDW.Integrator_DSTATE_h;

  /* DiscreteTransferFcn: '<S37>/Filter Differentiator TF' incorporates:
   *  Gain: '<S35>/Derivative Gain'
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  FilterDifferentiatorTF_tmp = (rtb_y_c - 3.14159274F) * 0.4F - -0.333333343F *
    rtDW.FilterDifferentiatorTF_states;

  /* Sum: '<Root>/Sum3' incorporates:
   *  DiscreteTransferFcn: '<S37>/Filter Differentiator TF'
   *  Gain: '<S47>/Filter Coefficient'
   *  Gain: '<S49>/Proportional Gain'
   *  Inport: '<Root>/YawAccRef'
   *  MATLAB Function: '<S1>/DeFlipper'
   *  Product: '<S37>/DenCoefOut'
   *  Sum: '<S53>/Sum'
   */
  rtb_FilterDifferentiatorTF = (((rtb_y_c - 3.14159274F) * 3.0F + q) +
    (FilterDifferentiatorTF_tmp - rtDW.FilterDifferentiatorTF_states) *
    0.666666687F * 100.0F) - arg_YawAccRef;
  rtb_Rad2M[0] = rtb_FilterDifferentiatorTF;

  /* MATLAB Function: '<S4>/Desaturator' incorporates:
   *  Sum: '<Root>/Sum3'
   */
  rtb_y_c = fabsf(rtb_FilterDifferentiatorTF);
  varargin_1[0] = rtb_y_c;

  /* Sum: '<Root>/Sum3' */
  rtb_Rad2M[1] = rtb_FilterDifferentiatorTF;

  /* MATLAB Function: '<S4>/Desaturator' */
  varargin_1[1] = rtb_y_c;

  /* Sum: '<Root>/Sum3' */
  rtb_Rad2M[2] = rtb_FilterDifferentiatorTF;

  /* MATLAB Function: '<S4>/Desaturator' */
  varargin_1[2] = rtb_y_c;

  /* Sum: '<Root>/Sum3' */
  rtb_Rad2M[3] = rtb_FilterDifferentiatorTF;

  /* MATLAB Function: '<S4>/Desaturator' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  varargin_1[3] = rtb_y_c;
  if (!rtIsNaNF(rtb_y_c)) {
    idx = 1;
  } else {
    idx = 0;
    ioIdx = 2;
    exitg1 = false;
    while ((!exitg1) && (ioIdx < 5)) {
      if (!rtIsNaNF(varargin_1[ioIdx - 1])) {
        idx = ioIdx;
        exitg1 = true;
      } else {
        ioIdx++;
      }
    }
  }

  if (idx != 0) {
    rtb_y_c = varargin_1[idx - 1];
    for (ioIdx = idx + 1; ioIdx < 5; ioIdx++) {
      rtb_FilterDifferentiatorTF = varargin_1[ioIdx - 1];
      if (rtb_y_c < rtb_FilterDifferentiatorTF) {
        rtb_y_c = rtb_FilterDifferentiatorTF;
      }
    }
  }

  rtb_FilterDifferentiatorTF = rtb_y_c / 400.0F;
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

  /* Sum: '<S105>/Sum' incorporates:
   *  DiscreteIntegrator: '<S96>/Integrator'
   *  Gain: '<S101>/Proportional Gain'
   */
  rtb_Sum2_0 = (10.0 * rtb_Sum2[0] + rtDW.Integrator_DSTATE[0]) +
    rtb_FilterCoefficient[0];
  tmp = (10.0 * rtb_Sum2[1] + rtDW.Integrator_DSTATE[1]) +
    rtb_FilterCoefficient[1];

  /* Gain: '<S2>/MassFeedForward' incorporates:
   *  Constant: '<S2>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/AccRef'
   *  Product: '<S2>/Body2Wheels'
   */
  arg_AccRef_0 = arg_AccRef[0];
  arg_AccRef_1 = arg_AccRef[1];
  for (idx = 0; idx < 4; idx++) {
    /* Saturate: '<Root>/DO NOT REMOVE THIS' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Gain: '<Root>/ForceToTorque'
     *  Gain: '<S2>/MassFeedForward'
     *  Gain: '<S6>/IToV'
     *  Gain: '<S6>/TorqueToI'
     *  Gain: '<S6>/VToPWM'
     *  MATLAB Function: '<S4>/Desaturator'
     *  Product: '<Root>/Body2Wheels'
     *  Product: '<S2>/Body2Wheels'
     *  Sum: '<Root>/Sum1'
     */
    u0 = ((real32_T)((2.5F * arg_AccRef_0 * rtConstP.pooled4[idx] +
                      rtConstP.pooled4[idx + 4] * (2.5F * arg_AccRef_1)) +
                     (rtConstP.Constant1_Value[idx + 4] * tmp +
                      rtConstP.Constant1_Value[idx] * rtb_Sum2_0)) * rtb_y_c +
          rtb_Rad2M[idx] / rtb_FilterDifferentiatorTF) * 0.025F * 30.4878044F *
      0.934579432F * 0.0416666679F;
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

    /* End of Saturate: '<Root>/DO NOT REMOVE THIS' */
  }

  /* Update for DiscreteIntegrator: '<S96>/Integrator' incorporates:
   *  Gain: '<S93>/Integral Gain'
   */
  rtDW.Integrator_DSTATE[0] += 0.01 * rtb_FilterCoefficient_tmp[0];

  /* Update for DiscreteIntegrator: '<S91>/Filter' */
  rtDW.Filter_DSTATE[0] += 0.01 * rtb_FilterCoefficient[0];

  /* Update for DiscreteIntegrator: '<S96>/Integrator' incorporates:
   *  Gain: '<S93>/Integral Gain'
   */
  rtDW.Integrator_DSTATE[1] += 0.01 * rtb_FilterCoefficient_tmp[1];

  /* Update for DiscreteIntegrator: '<S91>/Filter' */
  rtDW.Filter_DSTATE[1] += 0.01 * rtb_FilterCoefficient[1];

  /* Update for DiscreteIntegrator: '<S44>/Integrator' */
  rtDW.Integrator_DSTATE_h = 0.005F * rtb_Sum_n + q;

  /* Update for DiscreteTransferFcn: '<S37>/Filter Differentiator TF' */
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
