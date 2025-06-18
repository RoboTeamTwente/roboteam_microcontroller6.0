/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Plant_d_Bench_private.h
 *
 * Code generated for Simulink model 'Plant_d_Bench'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed May 21 14:50:43 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Plant_d_Bench_private_h_
#define Plant_d_Bench_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "Plant_d_Bench_types.h"
#include "Plant_d_Bench.h"

extern void Plant_d_Bench_Angle2Rotmat(real_T rtu_yaw, real_T rty_rotmat[4]);
extern void Plant_d_Bench_MATLABFunction(real_T rtu_relvel, real_T rtu_absvel,
  real_T rtu_whangle, real_T rtu_wheel_staticdrivetraction, real_T
  rtu_wheel_lineardrivetraction, real_T rtu_wheel_subwheels, real_T *rty_force);

#endif                                 /* Plant_d_Bench_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
