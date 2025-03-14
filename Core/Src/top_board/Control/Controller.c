/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 2.29
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Feb 11 15:35:57 2025
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

/* External inputs (root inport signals with default storage) */
ExtU rtU;
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
  return (boolean_T)isinf(value);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)isinf(value);
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
void Controller_step(real32_T arg_Encoders[4], real32_T arg_YawRate, real32_T
                     arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef,
                     real32_T arg_AccRef[2], real32_T arg_YawRateRef, real32_T
                     arg_YawAccRef, real32_T arg_Accelerometer[2], real32_T
                     arg_Motorefforts[4], real32_T arg_Debug[32], real32_T
                     arg_Velest[2], real32_T *arg_AFL, real32_T arg_VBat)
{
  real_T params[16];
  real_T z_posminconst[4];
  real_T tmp;
  int32_T i;
  int32_T idx;
  real32_T rtb_Rad2M1[4];
  real32_T rtb_y[4];
  real32_T rtb_FilterCoefficient[2];
  real32_T rtb_FilterCoefficient_tmp[2];
  real32_T rtb_Saturation[2];
  real32_T rtb_Sum2[2];
  real32_T rtb_Sum_o[2];
  real32_T DigitalFilter_TEMP_STATES;
  real32_T DigitalFilter_TEMP_STATES_idx_0;
  real32_T DigitalFilter_TEMP_STATES_idx_1;
  real32_T DigitalFilter_TEMP_STATES_idx_2;
  real32_T FilterDifferentiatorTF_tmp;
  real32_T Integrator;
  real32_T arg_AccRef_0;
  real32_T arg_AccRef_1;
  real32_T rtb_FilterDifferentiatorTF;
  real32_T rtb_Reciprocal;
  real32_T rtb_RotInertiaFeedforward;
  real32_T rtb_Saturation_0;
  real32_T rtb_Saturation_1;
  real32_T rtb_Sum;
  real32_T rtb_y_d;
  real32_T u0;
  boolean_T eq_signs[4];
  boolean_T rEQ0;
  static const real_T b[16] = { 0.487679493914719, 0.362439663999906,
    0.400408293666698, 0.373047227302758, 0.03581172782683, 0.036702678870859,
    0.034616181149416, 0.036516068519141, -0.903990540061869,
    -2.0339902783469559, -0.993340223619706, 4.43856711221243,
    1.2658652985065639, 1.036757957843577, 1.244729721334767, 1.057087869495094
  };

  boolean_T exitg1;

  /* Copy value for root inport '<Root>/Encoders' since it is accessed globally */
  {
    int32_T i;
    for (i = 0; i < 4; i++) {
      rtU.Encoders[i] = arg_Encoders[i];
    }
  }

  UNUSED_PARAMETER(arg_YawRate);
  UNUSED_PARAMETER(arg_Accelerometer);

  /* SignalConversion generated from: '<Root>/Vector Concatenate1' incorporates:
   *  Outport: '<Root>/Debug'
   */
  memset(&arg_Debug[8], 0, 24U * sizeof(real32_T));

  /* S-Function (sdspbiquad): '<S3>/Digital Filter' incorporates:
   *  Inport: '<Root>/Encoders'
   */
  DigitalFilter_TEMP_STATES = (0.245237276F * rtU.Encoders[0] - -0.509525478F *
    rtDW.DigitalFilter_FILT_STATES[0]) - 0.0F * rtDW.DigitalFilter_FILT_STATES[1];
  DigitalFilter_TEMP_STATES_idx_0 = DigitalFilter_TEMP_STATES;
  rtDW.DigitalFilter[0] = (DigitalFilter_TEMP_STATES +
    rtDW.DigitalFilter_FILT_STATES[0]) + 0.0F * rtDW.DigitalFilter_FILT_STATES[1];
  DigitalFilter_TEMP_STATES = (0.245237276F * rtU.Encoders[1] - -0.509525478F *
    rtDW.DigitalFilter_FILT_STATES[2]) - 0.0F * rtDW.DigitalFilter_FILT_STATES[3];
  DigitalFilter_TEMP_STATES_idx_1 = DigitalFilter_TEMP_STATES;
  rtDW.DigitalFilter[1] = (DigitalFilter_TEMP_STATES +
    rtDW.DigitalFilter_FILT_STATES[2]) + 0.0F * rtDW.DigitalFilter_FILT_STATES[3];
  DigitalFilter_TEMP_STATES = (0.245237276F * rtU.Encoders[2] - -0.509525478F *
    rtDW.DigitalFilter_FILT_STATES[4]) - 0.0F * rtDW.DigitalFilter_FILT_STATES[5];
  DigitalFilter_TEMP_STATES_idx_2 = DigitalFilter_TEMP_STATES;
  rtDW.DigitalFilter[2] = (DigitalFilter_TEMP_STATES +
    rtDW.DigitalFilter_FILT_STATES[4]) + 0.0F * rtDW.DigitalFilter_FILT_STATES[5];
  DigitalFilter_TEMP_STATES = (0.245237276F * rtU.Encoders[3] - -0.509525478F *
    rtDW.DigitalFilter_FILT_STATES[6]) - 0.0F * rtDW.DigitalFilter_FILT_STATES[7];
  rtDW.DigitalFilter[3] = (DigitalFilter_TEMP_STATES +
    rtDW.DigitalFilter_FILT_STATES[6]) + 0.0F * rtDW.DigitalFilter_FILT_STATES[7];

  /* Gain: '<S5>/Rad2M1' */
  rtb_Rad2M1[0] = 0.027F * rtDW.DigitalFilter[0];
  rtb_Rad2M1[1] = 0.027F * rtDW.DigitalFilter[1];
  rtb_Rad2M1[2] = 0.027F * rtDW.DigitalFilter[2];
  rtb_Rad2M1[3] = 0.027F * rtDW.DigitalFilter[3];

  /* S-Function (sdspstatfcns): '<S5>/Mean' */
  rtb_FilterDifferentiatorTF = (((rtb_Rad2M1[0] + rtb_Rad2M1[1]) + rtb_Rad2M1[2])
    + rtb_Rad2M1[3]) / 4.0F;
  idx = 1;

  /* Sum: '<S5>/Sum1' */
  rtb_y_d = rtb_Rad2M1[0] - rtb_FilterDifferentiatorTF;
  rtb_Rad2M1[0] = rtb_y_d;

  /* MATLAB Function: '<S5>/MATLAB Function' */
  rtb_RotInertiaFeedforward = rtb_y_d * 0.0712164491F;

  /* Sum: '<S5>/Sum1' */
  rtb_y_d = rtb_Rad2M1[1] - rtb_FilterDifferentiatorTF;
  rtb_Rad2M1[1] = rtb_y_d;

  /* MATLAB Function: '<S5>/MATLAB Function' */
  rtb_RotInertiaFeedforward += rtb_y_d * -0.319719762F;

  /* Sum: '<S5>/Sum1' */
  rtb_y_d = rtb_Rad2M1[2] - rtb_FilterDifferentiatorTF;
  rtb_Rad2M1[2] = rtb_y_d;

  /* MATLAB Function: '<S5>/MATLAB Function' */
  rtb_RotInertiaFeedforward += rtb_y_d * 0.360715747F;

  /* Sum: '<S5>/Sum1' */
  rtb_y_d = rtb_Rad2M1[3] - rtb_FilterDifferentiatorTF;

  /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Sum: '<S5>/Sum1'
   */
  rtb_Sum = (rtb_y_d * -0.112212442F + rtb_RotInertiaFeedforward) * 0.5F;
  rtb_RotInertiaFeedforward = rtb_Rad2M1[0] - rtb_Sum * 0.142432898F;
  Integrator = rtb_Rad2M1[1] - rtb_Sum * -0.639439523F;
  FilterDifferentiatorTF_tmp = rtb_Rad2M1[2] - rtb_Sum * 0.721431494F;
  rtb_Sum = rtb_y_d - rtb_Sum * -0.224424884F;
  for (i = 0; i < 2; i++) {
    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S5>/Constant'
     *  Product: '<S5>/Wheels2Body'
     */
    rtb_y_d = ((rtConstP.Constant_Value_h[i + 2] * Integrator +
                rtConstP.Constant_Value_h[i] * rtb_RotInertiaFeedforward) +
               rtConstP.Constant_Value_h[i + 4] * FilterDifferentiatorTF_tmp) +
      rtConstP.Constant_Value_h[i + 6] * rtb_Sum;
    rtb_Sum_o[i] = rtb_y_d;

    /* Sum: '<Root>/Sum2' incorporates:
     *  Inport: '<Root>/VelRef'
     *  Sum: '<S5>/Sum'
     */
    rtb_y_d = arg_VelRef[i] - rtb_y_d;

    /* Gain: '<S98>/Derivative Gain' incorporates:
     *  Gain: '<S102>/Integral Gain'
     */
    rtb_Reciprocal = 0.0F * rtb_y_d;
    rtb_FilterCoefficient_tmp[i] = rtb_Reciprocal;

    /* Gain: '<S108>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S100>/Filter'
     *  Gain: '<S98>/Derivative Gain'
     *  Sum: '<S100>/SumD'
     */
    rtb_Reciprocal = (rtb_Reciprocal - rtDW.Filter_DSTATE[i]) * 100.0F;
    rtb_FilterCoefficient[i] = rtb_Reciprocal;

    /* Sum: '<S114>/Sum' incorporates:
     *  DiscreteIntegrator: '<S105>/Integrator'
     */
    rtb_y_d = (rtb_y_d + rtDW.Integrator_DSTATE[i]) + rtb_Reciprocal;
    rtb_Sum2[i] = rtb_y_d;

    /* Saturate: '<S112>/Saturation' */
    if (rtb_y_d > 5.4666667F) {
      rtb_Saturation[i] = 5.4666667F;
    } else if (rtb_y_d < -5.4666667F) {
      rtb_Saturation[i] = -5.4666667F;
    } else {
      rtb_Saturation[i] = rtb_y_d;
    }

    /* End of Saturate: '<S112>/Saturation' */
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Yaw'
   *  Inport: '<Root>/YawRef'
   */
  rtb_Sum = arg_YawRef - arg_Yaw;

  /* MATLAB Function: '<S1>/DeFlipper' */
  if (rtIsNaNF(rtb_Sum + 3.14159274F)) {
    rtb_y_d = (rtNaNF);
  } else if (rtIsInfF(rtb_Sum + 3.14159274F)) {
    rtb_y_d = (rtNaNF);
  } else if (rtb_Sum + 3.14159274F == 0.0F) {
    rtb_y_d = 0.0F;
  } else {
    rtb_y_d = fmodf(rtb_Sum + 3.14159274F, 6.28318548F);
    rEQ0 = (rtb_y_d == 0.0F);
    if (!rEQ0) {
      rtb_Sum = fabsf((rtb_Sum + 3.14159274F) / 6.28318548F);
      rEQ0 = !(fabsf(rtb_Sum - floorf(rtb_Sum + 0.5F)) > 1.1920929E-7F * rtb_Sum);
    }

    if (rEQ0) {
      rtb_y_d = 0.0F;
    } else if (rtb_y_d < 0.0F) {
      rtb_y_d += 6.28318548F;
    }
  }

  /* Gain: '<S44>/Integral Gain' incorporates:
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  rtb_Sum = (rtb_y_d - 3.14159274F) * 0.1F;

  /* DiscreteIntegrator: '<S47>/Integrator' */
  Integrator = 0.005F * rtb_Sum + rtDW.Integrator_DSTATE_h;

  /* DiscreteTransferFcn: '<S40>/Filter Differentiator TF' incorporates:
   *  MATLAB Function: '<S1>/DeFlipper'
   */
  FilterDifferentiatorTF_tmp = (rtb_y_d - 3.14159274F) - -0.6F *
    rtDW.FilterDifferentiatorTF_states;

  /* Sum: '<Root>/Sum3' incorporates:
   *  DiscreteTransferFcn: '<S40>/Filter Differentiator TF'
   *  Gain: '<Root>/RotInertiaFeedforward'
   *  Gain: '<S50>/Filter Coefficient'
   *  Gain: '<S52>/Proportional Gain'
   *  Inport: '<Root>/YawAccRef'
   *  MATLAB Function: '<S1>/CubicCompensator'
   *  MATLAB Function: '<S1>/DeFlipper'
   *  Product: '<S40>/DenCoefOut'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S56>/Sum'
   */
  rtb_y_d = ((((rtb_y_d - 3.14159274F) * 9.0F + Integrator) +
              (FilterDifferentiatorTF_tmp - rtDW.FilterDifferentiatorTF_states) *
              0.8F * 50.0F) + rt_powf_snf(rtb_y_d - 3.14159274F, 3.0F) * 100.0F)
    + 15.2415791F * arg_YawAccRef;
  rtb_Rad2M1[0] = rtb_y_d;

  /* MATLAB Function: '<S4>/Desaturator' incorporates:
   *  Sum: '<Root>/Sum3'
   */
  rtb_RotInertiaFeedforward = fabsf(rtb_y_d);
  rtb_y[0] = rtb_RotInertiaFeedforward;

  /* Sum: '<Root>/Sum3' */
  rtb_Rad2M1[1] = rtb_y_d;

  /* MATLAB Function: '<S4>/Desaturator' */
  rtb_y[1] = rtb_RotInertiaFeedforward;

  /* Sum: '<Root>/Sum3' */
  rtb_Rad2M1[2] = rtb_y_d;

  /* MATLAB Function: '<S4>/Desaturator' */
  rtb_y[2] = rtb_RotInertiaFeedforward;

  /* Sum: '<Root>/Sum3' */
  rtb_Rad2M1[3] = rtb_y_d;

  /* MATLAB Function: '<S4>/Desaturator' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  rtb_y[3] = rtb_RotInertiaFeedforward;
  if (rtIsNaNF(rtb_RotInertiaFeedforward)) {
    idx = 0;
    i = 2;
    exitg1 = false;
    while ((!exitg1) && (i < 5)) {
      if (!rtIsNaNF(rtb_y[i - 1])) {
        idx = i;
        exitg1 = true;
      } else {
        i++;
      }
    }
  }

  if (idx != 0) {
    rtb_RotInertiaFeedforward = rtb_y[idx - 1];
    for (i = idx + 1; i < 5; i++) {
      rtb_FilterDifferentiatorTF = rtb_y[i - 1];
      if (rtb_RotInertiaFeedforward < rtb_FilterDifferentiatorTF) {
        rtb_RotInertiaFeedforward = rtb_FilterDifferentiatorTF;
      }
    }
  }

  rtb_y_d = rtb_RotInertiaFeedforward / 5.4666667F;
  if (1.0F - rtb_y_d < 0.0F) {
    rtb_RotInertiaFeedforward = 0.0F;
  } else if (rtIsNaNF(1.0F - rtb_y_d)) {
    rtb_RotInertiaFeedforward = 0.0F;
  } else {
    rtb_RotInertiaFeedforward = 1.0F - rtb_y_d;
  }

  if (rtb_y_d < 1.0F) {
    rtb_y_d = 1.0F;
  } else if (rtIsNaNF(rtb_y_d)) {
    rtb_y_d = 1.0F;
  }

  /* Product: '<S68>/Body2Wheels' incorporates:
   *  Constant: '<S68>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/VelRef'
   */
  rtb_Reciprocal = arg_VelRef[1];
  rtb_FilterDifferentiatorTF = arg_VelRef[0];

  /* MATLAB Function: '<S68>/MATLAB Function' incorporates:
   *  Constant: '<S68>/BodyForceCouplingMatrix'
   *  Constant: '<S68>/Roborad'
   *  Inport: '<Root>/VelRef'
   *  Inport: '<Root>/YawRateRef'
   *  Product: '<S68>/Body2Wheels'
   */
  for (idx = 0; idx < 4; idx++) {
    rtb_y[idx] = rtConstP.BodyForceCouplingMatrix_Value_d[idx + 4] *
      rtb_Reciprocal + rtConstP.BodyForceCouplingMatrix_Value_d[idx] *
      rtb_FilterDifferentiatorTF;
  }

  rtb_FilterDifferentiatorTF = rt_atan2f_snf(arg_VelRef[1], arg_VelRef[0]);
  memcpy(&params[0], &b[0], sizeof(real_T) << 4U);
  params[4] = 2.0518608615485667;
  params[5] = 2.1029085961242022;
  params[6] = 1.9833610827218562;
  params[7] = 2.0922166105573092;
  if (sinf(1.00267613F * rtb_FilterDifferentiatorTF + 1.04719758F) >= 0.0F) {
    z_posminconst[0] = sinf(2.05186081F * rtb_FilterDifferentiatorTF + (real32_T)
      params[8]) * (real32_T)params[0] + (real32_T)params[12];
  } else {
    z_posminconst[0] = -(sinf(2.05186081F * rtb_FilterDifferentiatorTF +
      (real32_T)params[8]) * (real32_T)params[0] + (real32_T)params[12]);
  }

  if (sinf(1.00267613F * rtb_FilterDifferentiatorTF - 1.04719758F) >= 0.0F) {
    z_posminconst[1] = sinf(2.10290861F * rtb_FilterDifferentiatorTF + (real32_T)
      params[9]) * (real32_T)params[1] + (real32_T)params[13];
  } else {
    z_posminconst[1] = -(sinf(2.10290861F * rtb_FilterDifferentiatorTF +
      (real32_T)params[9]) * (real32_T)params[1] + (real32_T)params[13]);
  }

  if (sinf(1.00267613F * rtb_FilterDifferentiatorTF - 2.3561945F) >= 0.0F) {
    z_posminconst[2] = sinf(1.98336112F * rtb_FilterDifferentiatorTF + (real32_T)
      params[10]) * (real32_T)params[2] + (real32_T)params[14];
  } else {
    z_posminconst[2] = -(sinf(1.98336112F * rtb_FilterDifferentiatorTF +
      (real32_T)params[10]) * (real32_T)params[2] + (real32_T)params[14]);
  }

  if (sinf(1.00267613F * rtb_FilterDifferentiatorTF + 2.3561945F) >= 0.0F) {
    z_posminconst[3] = sinf(2.09221649F * rtb_FilterDifferentiatorTF + (real32_T)
      params[11]) * (real32_T)params[3] + (real32_T)params[15];
  } else {
    z_posminconst[3] = -(sinf(2.09221649F * rtb_FilterDifferentiatorTF +
      (real32_T)params[11]) * (real32_T)params[3] + (real32_T)params[15]);
  }

  if (rtIsNaNF(rtb_y[0])) {
    rtb_FilterDifferentiatorTF = (rtNaNF);
  } else if (rtb_y[0] < 0.0F) {
    rtb_FilterDifferentiatorTF = -1.0F;
  } else {
    rtb_FilterDifferentiatorTF = (real32_T)(rtb_y[0] > 0.0F);
  }

  rtb_y[0] = rtb_FilterDifferentiatorTF;
  if (rtIsNaN(z_posminconst[0])) {
    tmp = (rtNaN);
  } else if (z_posminconst[0] < 0.0) {
    tmp = -1.0;
  } else {
    tmp = (z_posminconst[0] > 0.0);
  }

  eq_signs[0] = (rtb_FilterDifferentiatorTF == tmp);
  if (rtIsNaNF(rtb_y[1])) {
    rtb_FilterDifferentiatorTF = (rtNaNF);
  } else if (rtb_y[1] < 0.0F) {
    rtb_FilterDifferentiatorTF = -1.0F;
  } else {
    rtb_FilterDifferentiatorTF = (real32_T)(rtb_y[1] > 0.0F);
  }

  rtb_y[1] = rtb_FilterDifferentiatorTF;
  if (rtIsNaN(z_posminconst[1])) {
    tmp = (rtNaN);
  } else if (z_posminconst[1] < 0.0) {
    tmp = -1.0;
  } else {
    tmp = (z_posminconst[1] > 0.0);
  }

  eq_signs[1] = (rtb_FilterDifferentiatorTF == tmp);
  if (rtIsNaNF(rtb_y[2])) {
    rtb_FilterDifferentiatorTF = (rtNaNF);
  } else if (rtb_y[2] < 0.0F) {
    rtb_FilterDifferentiatorTF = -1.0F;
  } else {
    rtb_FilterDifferentiatorTF = (real32_T)(rtb_y[2] > 0.0F);
  }

  rtb_y[2] = rtb_FilterDifferentiatorTF;
  if (rtIsNaN(z_posminconst[2])) {
    tmp = (rtNaN);
  } else if (z_posminconst[2] < 0.0) {
    tmp = -1.0;
  } else {
    tmp = (z_posminconst[2] > 0.0);
  }

  eq_signs[2] = (rtb_FilterDifferentiatorTF == tmp);
  if (rtIsNaNF(rtb_y[3])) {
    rtb_FilterDifferentiatorTF = (rtNaNF);
  } else if (rtb_y[3] < 0.0F) {
    rtb_FilterDifferentiatorTF = -1.0F;
  } else {
    rtb_FilterDifferentiatorTF = (real32_T)(rtb_y[3] > 0.0F);
  }

  rtb_y[3] = rtb_FilterDifferentiatorTF;
  if (rtIsNaN(z_posminconst[3])) {
    tmp = (rtNaN);
  } else if (z_posminconst[3] < 0.0) {
    tmp = -1.0;
  } else {
    tmp = (z_posminconst[3] > 0.0);
  }

  eq_signs[3] = (rtb_FilterDifferentiatorTF == tmp);
  rtb_FilterDifferentiatorTF = rt_hypotf_snf(arg_VelRef[0], arg_VelRef[1]) /
    0.081F;
  rtb_Reciprocal = 0.5F - cosf(fabsf(arg_YawRateRef / rtb_FilterDifferentiatorTF)
    * 3.14159274F) * 0.5F;
  if (fabsf(arg_YawRateRef) > rtb_FilterDifferentiatorTF) {
    rtb_Reciprocal = 1.0F;
  }

  /* Gain: '<S2>/MassFeedForward' incorporates:
   *  Constant: '<S2>/BodyForceCouplingMatrix'
   *  Inport: '<Root>/AccRef'
   *  Product: '<S2>/Body2Wheels'
   */
  arg_AccRef_0 = arg_AccRef[0];
  arg_AccRef_1 = arg_AccRef[1];

  /* Product: '<S7>/Body2Wheels' incorporates:
   *  Constant: '<S7>/Constant1'
   */
  rtb_Saturation_0 = rtb_Saturation[1];
  rtb_Saturation_1 = rtb_Saturation[0];
  for (i = 0; i < 4; i++) {
    /* MATLAB Function: '<S68>/MATLAB Function' */
    rtb_FilterDifferentiatorTF = rtb_y[i];
    rEQ0 = eq_signs[i];
    rtb_FilterDifferentiatorTF = ((real32_T)(params[i + 12] * (real_T)!rEQ0) *
      rtb_FilterDifferentiatorTF + (real32_T)(z_posminconst[i] * (real_T)rEQ0)) *
      (1.0F - rtb_Reciprocal) + rtb_Reciprocal * rtb_FilterDifferentiatorTF;
    rtb_y[i] = rtb_FilterDifferentiatorTF;

    /* Saturate: '<Root>/DO NOT REMOVE THIS' incorporates:
     *  Constant: '<S2>/BodyForceCouplingMatrix'
     *  Constant: '<S7>/Constant1'
     *  Gain: '<Root>/ForceToTorque'
     *  Gain: '<S2>/MassFeedForward'
     *  Gain: '<S6>/IToV'
     *  Gain: '<S6>/OmegaToV'
     *  Gain: '<S6>/TorqueToI'
     *  Inport: '<Root>/Vbat'
     *  MATLAB Function: '<S4>/Desaturator'
     *  Product: '<Root>/Divide'
     *  Product: '<S2>/Body2Wheels'
     *  Product: '<S7>/Body2Wheels'
     *  Sum: '<Root>/Sum1'
     *  Sum: '<S6>/Sum'
     */
    u0 = ((((real32_T)((2.5F * arg_AccRef_0 *
                        rtConstP.BodyForceCouplingMatrix_Value[i] +
                        rtConstP.BodyForceCouplingMatrix_Value[i + 4] * (2.5F *
               arg_AccRef_1)) + (rtConstP.Constant1_Value_f[i + 4] *
              rtb_Saturation_0 + rtConstP.Constant1_Value_f[i] *
              rtb_Saturation_1)) * rtb_RotInertiaFeedforward + rtb_Rad2M1[i] /
            rtb_y_d) * 0.027F * 30.4878044F * 0.934579372F + 0.0328F *
           rtDW.DigitalFilter[i]) + rtb_FilterDifferentiatorTF) / arg_VBat;
    if (u0 > 1.0F) {
      u0 = 1.0F;
    } else if (u0 < -1.0F) {
      u0 = -1.0F;
    }

    rtb_Rad2M1[i] = u0;

    /* End of Saturate: '<Root>/DO NOT REMOVE THIS' */

    /* Outport: '<Root>/Motorefforts' */
    arg_Motorefforts[i] = u0;

    /* SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
     *  Outport: '<Root>/Debug'
     */
    arg_Debug[i] = u0;

    /* SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
     *  Outport: '<Root>/Debug'
     */
    arg_Debug[i + 4] = rtb_FilterDifferentiatorTF;
  }

  /* Outport: '<Root>/Velest' */
  arg_Velest[0] = rtb_Sum_o[0];
  arg_Velest[1] = rtb_Sum_o[1];

  /* Outport: '<Root>/AFL' incorporates:
   *  Constant: '<Root>/Forcelimit'
   */
  *arg_AFL = 5.4666667F;

  /* Update for S-Function (sdspbiquad): '<S3>/Digital Filter' */
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = DigitalFilter_TEMP_STATES_idx_0;
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = DigitalFilter_TEMP_STATES_idx_1;
  rtDW.DigitalFilter_FILT_STATES[5] = rtDW.DigitalFilter_FILT_STATES[4];
  rtDW.DigitalFilter_FILT_STATES[4] = DigitalFilter_TEMP_STATES_idx_2;
  rtDW.DigitalFilter_FILT_STATES[7] = rtDW.DigitalFilter_FILT_STATES[6];
  rtDW.DigitalFilter_FILT_STATES[6] = DigitalFilter_TEMP_STATES;

  /* Update for DiscreteIntegrator: '<S105>/Integrator' incorporates:
   *  Gain: '<S102>/Integral Gain'
   *  Sum: '<S97>/SumI2'
   *  Sum: '<S97>/SumI4'
   */
  rtDW.Integrator_DSTATE[0] += ((rtb_Saturation[0] - rtb_Sum2[0]) +
    rtb_FilterCoefficient_tmp[0]) * 0.01F;

  /* Update for DiscreteIntegrator: '<S100>/Filter' */
  rtDW.Filter_DSTATE[0] += 0.01F * rtb_FilterCoefficient[0];

  /* Update for DiscreteIntegrator: '<S105>/Integrator' incorporates:
   *  Gain: '<S102>/Integral Gain'
   *  Sum: '<S97>/SumI2'
   *  Sum: '<S97>/SumI4'
   */
  rtDW.Integrator_DSTATE[1] += ((rtb_Saturation[1] - rtb_Sum2[1]) +
    rtb_FilterCoefficient_tmp[1]) * 0.01F;

  /* Update for DiscreteIntegrator: '<S100>/Filter' */
  rtDW.Filter_DSTATE[1] += 0.01F * rtb_FilterCoefficient[1];

  /* Update for DiscreteIntegrator: '<S47>/Integrator' */
  rtDW.Integrator_DSTATE_h = 0.005F * rtb_Sum + Integrator;

  /* Update for DiscreteTransferFcn: '<S40>/Filter Differentiator TF' */
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
