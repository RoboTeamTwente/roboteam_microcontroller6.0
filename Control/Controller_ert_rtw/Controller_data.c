/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Sep 23 16:23:19 2024
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
  /* Pooled Parameter (Expression: [cos(front_angle), sin(front_angle); -cos(front_angle), sin(front_angle); -cos(back_angle), -sin(back_angle); cos(back_angle), -sin(back_angle)])
   * Referenced by:
   *   '<S2>/BodyForceCouplingMatrix'
   *   '<S58>/BodyForceCouplingMatrix'
   */
  { 0.866025388F, -0.866025388F, -0.707106769F, 0.707106769F, 0.5F, 0.5F,
    -0.707106769F, -0.707106769F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
