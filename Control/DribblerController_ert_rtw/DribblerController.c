/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DribblerController.c
 *
 * Code generated for Simulink model 'DribblerController'.
 *
 * Model version                  : 2.4
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 10 17:20:10 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DribblerController.h"
#include "rtwtypes.h"
#include "rt_nonfinite.h"

/* Block states (default storage) */
DW_DribblerController_T DribblerController_DW;

/* Real-time model */
static RT_MODEL_DribblerController_T DribblerController_M_;
RT_MODEL_DribblerController_T *const DribblerController_M =
  &DribblerController_M_;

/* Model step function */
void DribblerController_step(real_T arg_encoder, boolean_T ballsensor_hasBall,
  real_T arg_current, real_T *arg_motor_effort)
{
  real_T Diff;
  real_T rtb_Filter_a;
  real_T rtb_Integrator_c;
  real_T rtb_Sum;
  real_T rtb_Sum_j;
  real_T rtb_TSamp;
  int32_T n;
  int32_T srcIdx;

  /* SampleTimeMath: '<S2>/TSamp' incorporates:
   *  Inport: '<Root>/encoder'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp = arg_encoder * 100.0;

  /* Sum: '<S2>/Diff' incorporates:
   *  UnitDelay: '<S2>/UD'
   *
   * Block description for '<S2>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S2>/UD':
   *
   *  Store in Global RAM
   */
  Diff = rtb_TSamp - DribblerController_DW.UD_DSTATE;

  /* DiscreteFir: '<S3>/Digital Filter' */
  /* Reverse the coefficients */
  for (srcIdx = 0; srcIdx < 51; srcIdx++) {
    DribblerController_DW.DigitalFilter_simRevCoeff[50 - srcIdx] =
      DribblerController_ConstP.DigitalFilter_Coefficients[srcIdx];
  }

  /* Reverse copy the states from States_Dwork to ContextBuff_Dwork */
  for (srcIdx = 0; srcIdx < 50; srcIdx++) {
    DribblerController_DW.DigitalFilter_simContextBuf[49 - srcIdx] =
      DribblerController_DW.DigitalFilter_states[srcIdx];
  }

  /* Copy the initial part of input to ContextBuff_Dwork */
  DribblerController_DW.DigitalFilter_simContextBuf[50] = Diff;
  for (srcIdx = 0; srcIdx < 1; srcIdx++) {
    rtb_Filter_a = 0.0;
    for (n = 0; n < 51; n++) {
      rtb_Filter_a += DribblerController_DW.DigitalFilter_simRevCoeff[n] *
        DribblerController_DW.DigitalFilter_simContextBuf[n];
    }

    /* store output sample */
  }

  /* Shift state buffer when input buffer is shorter than state buffer */
  for (srcIdx = 48; srcIdx >= 0; srcIdx--) {
    DribblerController_DW.DigitalFilter_states[srcIdx + 1] =
      DribblerController_DW.DigitalFilter_states[srcIdx];
  }

  /* Reverse copy the states from input to States_Dwork */
  DribblerController_DW.DigitalFilter_states[0] = Diff;

  /* End of DiscreteFir: '<S3>/Digital Filter' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Inport: '<Root>/ball_detec'
   */
  if (ballsensor_hasBall) {
    srcIdx = 200;
  } else {
    srcIdx = 0;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Switch: '<Root>/Switch'
   */
  rtb_Integrator_c = (real_T)srcIdx - rtb_Filter_a;

  /* Gain: '<S95>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S87>/Filter'
   *  Sum: '<S87>/SumD'
   */
  Diff = (rtb_Integrator_c - DribblerController_DW.Filter_DSTATE) * 100.0;

  /* Sum: '<S102>/Sum' incorporates:
   *  DiscreteIntegrator: '<S92>/Integrator'
   */
  rtb_Sum = (rtb_Integrator_c + DribblerController_DW.Integrator_DSTATE) + Diff;

  /* Switch: '<S100>/Switch2' incorporates:
   *  Constant: '<Root>/Constant2'
   *  RelationalOperator: '<S100>/LowerRelop1'
   *  RelationalOperator: '<S100>/UpperRelop'
   *  Switch: '<S100>/Switch'
   */
  if (rtb_Sum > 0.32) {
    rtb_Filter_a = 0.32;
  } else if (rtb_Sum < DribblerController_ConstB.Gain) {
    /* Switch: '<S100>/Switch' */
    rtb_Filter_a = DribblerController_ConstB.Gain;
  } else {
    rtb_Filter_a = rtb_Sum;
  }

  /* End of Switch: '<S100>/Switch2' */

  /* Sum: '<S84>/SumI4' incorporates:
   *  Sum: '<S84>/SumI2'
   */
  rtb_Integrator_c += rtb_Filter_a - rtb_Sum;

  /* Signum: '<Root>/Sign' incorporates:
   *  UnitDelay: '<Root>/Unit Delay'
   */
  if (rtIsNaN(DribblerController_DW.UnitDelay_DSTATE)) {
    rtb_Sum = (rtNaN);
  } else if (DribblerController_DW.UnitDelay_DSTATE < 0.0) {
    rtb_Sum = -1.0;
  } else {
    rtb_Sum = (DribblerController_DW.UnitDelay_DSTATE > 0.0);
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/current'
   *  Product: '<Root>/Product'
   *  Signum: '<Root>/Sign'
   */
  rtb_Filter_a -= rtb_Sum * arg_current;

  /* Gain: '<S42>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S34>/Filter'
   *  Sum: '<S34>/SumD'
   */
  rtb_Sum = (rtb_Filter_a - DribblerController_DW.Filter_DSTATE_b) * 100.0;

  /* Sum: '<S48>/Sum' incorporates:
   *  DiscreteIntegrator: '<S39>/Integrator'
   *  Gain: '<S44>/Proportional Gain'
   */
  rtb_Sum_j = (2.0 * rtb_Filter_a + DribblerController_DW.Integrator_DSTATE_a) +
    rtb_Sum;

  /* Saturate: '<S46>/Saturation' */
  if (rtb_Sum_j > 1.0) {
    DribblerController_DW.UnitDelay_DSTATE = 1.0;
  } else if (rtb_Sum_j < -1.0) {
    DribblerController_DW.UnitDelay_DSTATE = -1.0;
  } else {
    DribblerController_DW.UnitDelay_DSTATE = rtb_Sum_j;
  }

  /* End of Saturate: '<S46>/Saturation' */

  /* Outport: '<Root>/motor_effort' incorporates:
   *  UnitDelay: '<Root>/Unit Delay'
   */
  *arg_motor_effort = DribblerController_DW.UnitDelay_DSTATE;

  /* Update for UnitDelay: '<S2>/UD'
   *
   * Block description for '<S2>/UD':
   *
   *  Store in Global RAM
   */
  DribblerController_DW.UD_DSTATE = rtb_TSamp;

  /* Update for DiscreteIntegrator: '<S87>/Filter' */
  DribblerController_DW.Filter_DSTATE += 0.01 * Diff;

  /* Update for DiscreteIntegrator: '<S92>/Integrator' */
  DribblerController_DW.Integrator_DSTATE += 0.01 * rtb_Integrator_c;

  /* Update for DiscreteIntegrator: '<S39>/Integrator' incorporates:
   *  Sum: '<S31>/SumI2'
   *  Sum: '<S31>/SumI4'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  DribblerController_DW.Integrator_DSTATE_a +=
    ((DribblerController_DW.UnitDelay_DSTATE - rtb_Sum_j) + rtb_Filter_a) * 0.01;

  /* Update for DiscreteIntegrator: '<S34>/Filter' */
  DribblerController_DW.Filter_DSTATE_b += 0.01 * rtb_Sum;
}

/* Model initialize function */
void DribblerController_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void DribblerController_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
