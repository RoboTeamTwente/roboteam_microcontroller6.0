/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 2.30
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 10 17:14:12 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Controller.h"

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Expression: wheels.Dforce
   * Referenced by: '<S8>/Constant1'
   */
  { 1.1547005383792515, -1.1547005383792515, -1.4142135623730949,
    1.4142135623730949, 2.0000000000000004, 2.0000000000000004,
    -1.4142135623730951, -1.4142135623730951 },

  /* Computed Parameter: BodyForceCouplingMatrix_Value
   * Referenced by: '<S2>/BodyForceCouplingMatrix'
   */
  { 1.15470052F, -1.15470052F, -1.41421354F, 1.41421354F, 2.0F, 2.0F,
    -1.41421354F, -1.41421354F },

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S6>/Constant'
   */
  { 0.492480487F, 0.414213568F, -0.492480487F, 0.414213568F, -0.438791275F,
    -0.414213568F, 0.492480487F, -0.414213568F },

  /* Computed Parameter: BodyForceCouplingMatrix_Value_d
   * Referenced by: '<S69>/BodyForceCouplingMatrix'
   */
  { 0.866025388F, -0.866025388F, -0.707106769F, 0.707106769F, 0.5F, 0.5F,
    -0.707106769F, -0.707106769F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
