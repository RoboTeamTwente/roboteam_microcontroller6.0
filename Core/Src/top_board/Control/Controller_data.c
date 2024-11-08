/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.107
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Nov  7 15:57:08 2024
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
  /* Expression: Dinv
   * Referenced by: '<Root>/Constant'
   */
  { 0.49248050117294279, 0.41421356237309509, -0.49248050117294279,
    0.41421356237309509, -0.4387912809451866, -0.41421356237309509,
    0.49248050117294279, -0.41421356237309509 },

  /* Expression: Dmat
   * Referenced by: '<Root>/Constant1'
   */
  { 0.86602540378443871, -0.86602540378443871, -0.70710678118654757,
    0.70710678118654757, 0.49999999999999994, 0.49999999999999994,
    -0.70710678118654746, -0.70710678118654746 },

  /* Pooled Parameter (Expression: Dmat)
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S111>/BodyForceCouplingMatrix'
   */
  { 0.866025388F, -0.866025388F, -0.707106769F, 0.707106769F, 0.5F, 0.5F,
    -0.707106769F, -0.707106769F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
