
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DribblerController.c
 *
 * Code generated for Simulink model 'DribblerController'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Dec 24 22:58:45 2024
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
 void DribblerController_step(real_T arg_encoder, boolean_T arg_ball_detec,
   real_T arg_current, real_T *arg_motor_effort)
 {
   real_T Diff;
   real_T rtb_Filter;
   real_T rtb_Filter_k;
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
     rtb_Filter = 0.0;
     for (n = 0; n < 51; n++) {
       rtb_Filter += DribblerController_DW.DigitalFilter_simRevCoeff[n] *
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
   if (arg_ball_detec) {
     srcIdx = 200;
   } else {
     srcIdx = 0;
   }
 
   /* Sum: '<Root>/Sum' incorporates:
    *  Switch: '<Root>/Switch'
    */
   rtb_Filter_k = (real_T)srcIdx - rtb_Filter;
 
   /* Gain: '<S92>/Filter Coefficient' incorporates:
    *  DiscreteIntegrator: '<S84>/Filter'
    *  Gain: '<S82>/Derivative Gain'
    *  Sum: '<S84>/SumD'
    */
   Diff = (0.0 * rtb_Filter_k - DribblerController_DW.Filter_DSTATE) * 100.0;
 
   /* Sum: '<S99>/Sum' incorporates:
    *  DiscreteIntegrator: '<S89>/Integrator'
    */
   rtb_Sum = (rtb_Filter_k + DribblerController_DW.Integrator_DSTATE) + Diff;
 
   /* Switch: '<S97>/Switch2' incorporates:
    *  Constant: '<Root>/Constant2'
    *  RelationalOperator: '<S97>/LowerRelop1'
    *  RelationalOperator: '<S97>/UpperRelop'
    *  Switch: '<S97>/Switch'
    */
   if (rtb_Sum > 3.0) {
     rtb_Filter = 3.0;
   } else if (rtb_Sum < DribblerController_ConstB.Gain) {
     /* Switch: '<S97>/Switch' */
     rtb_Filter = DribblerController_ConstB.Gain;
   } else {
     rtb_Filter = rtb_Sum;
   }
 
   /* End of Switch: '<S97>/Switch2' */
 
   /* Sum: '<S81>/SumI4' incorporates:
    *  Sum: '<S81>/SumI2'
    */
   rtb_Filter_k += rtb_Filter - rtb_Sum;
 
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
   rtb_Filter -= rtb_Sum * arg_current;
 
   /* Gain: '<S41>/Filter Coefficient' incorporates:
    *  DiscreteIntegrator: '<S33>/Filter'
    *  Gain: '<S31>/Derivative Gain'
    *  Sum: '<S33>/SumD'
    */
   rtb_Sum = (0.0 * rtb_Filter - DribblerController_DW.Filter_DSTATE_b) * 100.0;
 
   /* Sum: '<S47>/Sum' incorporates:
    *  DiscreteIntegrator: '<S38>/Integrator'
    */
   rtb_Sum_j = (rtb_Filter + DribblerController_DW.Integrator_DSTATE_a) + rtb_Sum;
 
   /* Saturate: '<S45>/Saturation' */
   if (rtb_Sum_j > 1.0) {
     DribblerController_DW.UnitDelay_DSTATE = 1.0;
   } else if (rtb_Sum_j < -1.0) {
     DribblerController_DW.UnitDelay_DSTATE = -1.0;
   } else {
     DribblerController_DW.UnitDelay_DSTATE = rtb_Sum_j;
   }
 
   /* End of Saturate: '<S45>/Saturation' */
 
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
 
   /* Update for DiscreteIntegrator: '<S84>/Filter' */
   DribblerController_DW.Filter_DSTATE += 0.01 * Diff;
 
   /* Update for DiscreteIntegrator: '<S89>/Integrator' */
   DribblerController_DW.Integrator_DSTATE += 0.01 * rtb_Filter_k;
 
   /* Update for DiscreteIntegrator: '<S33>/Filter' */
   DribblerController_DW.Filter_DSTATE_b += 0.01 * rtb_Sum;
 
   /* Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
    *  Sum: '<S30>/SumI2'
    *  Sum: '<S30>/SumI4'
    *  UnitDelay: '<Root>/Unit Delay'
    */
   DribblerController_DW.Integrator_DSTATE_a +=
     ((DribblerController_DW.UnitDelay_DSTATE - rtb_Sum_j) + rtb_Filter) * 0.01;
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
 has popup