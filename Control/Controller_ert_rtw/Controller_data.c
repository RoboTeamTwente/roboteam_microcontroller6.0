/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Expression: Dforce
   * Referenced by: '<S6>/Constant1'
   */
  { 1.1547005383792515, -1.1547005383792515, -1.4142135623730949,
    1.4142135623730949, 2.0000000000000004, 2.0000000000000004,
    -1.4142135623730951, -1.4142135623730951 },

  /* Pooled Parameter (Expression: Dmat)
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S65>/BodyForceCouplingMatrix'
   */
  { 0.866025388F, -0.866025388F, -0.707106769F, 0.707106769F, 0.5F, 0.5F,
    -0.707106769F, -0.707106769F },

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S4>/Constant'
   */
  { 0.492480487F, 0.414213568F, -0.492480487F, 0.414213568F, -0.438791275F,
    -0.414213568F, 0.492480487F, -0.414213568F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
