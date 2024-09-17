/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Sep 17 13:51:16 2024
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

/* Block signals and states (default storage) */
DW rtDW;

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

/* Model step function */
void Controller_step(real32_T arg_Wheelspeeds[4], real32_T arg_YawRate, real32_T
                     arg_Yaw, real32_T arg_VelRef[2], real32_T arg_YawRef,
                     real32_T arg_AccRef[2], real_T arg_YawRateRef, real_T
                     arg_YawAccRef, real32_T arg_Motorefforts[4])
{
  real32_T rtb_FilterCoefficient;
  real32_T rtb_Saturation;
  real32_T rtb_Sum;
  UNUSED_PARAMETER(arg_Wheelspeeds);
  UNUSED_PARAMETER(arg_YawRate);
  UNUSED_PARAMETER(arg_VelRef);
  UNUSED_PARAMETER(arg_AccRef);
  UNUSED_PARAMETER(arg_YawRateRef);
  UNUSED_PARAMETER(arg_YawAccRef);

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Yaw'
   *  Inport: '<Root>/YawRef'
   */
  rtb_Sum = arg_YawRef - arg_Yaw;

  /* Gain: '<S38>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S30>/Filter'
   *  Gain: '<S28>/Derivative Gain'
   *  Sum: '<S30>/SumD'
   */
  rtb_FilterCoefficient = (0.0F * rtb_Sum - rtDW.Filter_DSTATE) * 100.0F;

  /* Sum: '<S44>/Sum' incorporates:
   *  DiscreteIntegrator: '<S35>/Integrator'
   * */
  rtb_Sum += rtDW.Integrator_DSTATE;
  rtb_Saturation = rtb_Sum + rtb_FilterCoefficient;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Saturation > 0.1F) {
    rtb_Saturation = 0.1F;
  } else if (rtb_Saturation < -1.0F) {
    rtb_Saturation = -1.0F;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Outport: '<Root>/Motorefforts' incorporates:
   *  Product: '<Root>/Product'
   */
  arg_Motorefforts[0] = rtb_Saturation;
  arg_Motorefforts[1] = rtb_Saturation;
  arg_Motorefforts[2] = rtb_Saturation;
  arg_Motorefforts[3] = rtb_Saturation;

  /* Update for DiscreteIntegrator: '<S35>/Integrator' */
  rtDW.Integrator_DSTATE = rtb_Sum;

  /* Update for DiscreteIntegrator: '<S30>/Filter' */
  rtDW.Filter_DSTATE += rtb_FilterCoefficient;
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
