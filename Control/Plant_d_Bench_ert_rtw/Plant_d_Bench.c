/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Plant_d_Bench.c
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

#include "Plant_d_Bench.h"
#include "rtwtypes.h"
#include "Plant_d_Bench_private.h"
#include <math.h>
#include <emmintrin.h>
#include "Plant_d_Bench_capi.h"

/* Block states (default storage) */
DW_Plant_d_Bench_T Plant_d_Bench_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Plant_d_Bench_T Plant_d_Bench_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Plant_d_Bench_T Plant_d_Bench_Y;

/* Real-time model */
static RT_MODEL_Plant_d_Bench_T Plant_d_Bench_M_;
RT_MODEL_Plant_d_Bench_T *const Plant_d_Bench_M = &Plant_d_Bench_M_;

/*
 * Output and update for atomic system:
 *    '<S1>/Angle2Rotmat'
 *    '<S1>/Angle2Rotmat1'
 */
void Plant_d_Bench_Angle2Rotmat(real_T rtu_yaw, real_T rty_rotmat[4])
{
  real_T tmp;
  real_T tmp_0;
  tmp = sin(rtu_yaw);
  tmp_0 = cos(rtu_yaw);
  rty_rotmat[0] = tmp_0;
  rty_rotmat[2] = -tmp;
  rty_rotmat[1] = tmp;
  rty_rotmat[3] = tmp_0;
}

/*
 * Output and update for atomic system:
 *    '<S5>/MATLAB Function'
 *    '<S6>/MATLAB Function'
 *    '<S7>/MATLAB Function'
 *    '<S8>/MATLAB Function'
 */
void Plant_d_Bench_MATLABFunction(real_T rtu_relvel, real_T rtu_absvel, real_T
  rtu_whangle, real_T rtu_wheel_staticdrivetraction, real_T
  rtu_wheel_lineardrivetraction, real_T rtu_wheel_subwheels, real_T *rty_force)
{
  real_T absvel;
  absvel = fabs(rtu_absvel);
  *rty_force = (0.5 * absvel / (0.5 * absvel + 1.0) * 0.4 * sin(rtu_whangle *
    rtu_wheel_subwheels) + 1.0) * (exp(-fabs(rtu_relvel) * 1000.0) *
    rtu_wheel_staticdrivetraction + rtu_wheel_lineardrivetraction) * rtu_relvel;
}

/* Model step function */
void Plant_d_Bench_step(void)
{
  __m128d tmp;
  __m128d tmp_1;
  real_T rtb_rotmat[4];
  real_T rtb_rotmat_m[4];
  real_T tmp_0[2];
  real_T rtb_BodyVel_idx_0;
  real_T rtb_BodyVel_idx_1;
  real_T rtb_Rmotor_c_idx_1;
  real_T rtb_Rmotor_e;
  real_T rtb_Rmotor_j;
  real_T rtb_Rmotor_j_tmp;
  real_T rtb_Rmotor_m;
  real_T rtb_Sum6_0;
  real_T rtb_Sum6_idx_0;
  real_T rtb_TmpSignalConversionAtWhee_0;
  real_T rtb_WheelInertia;
  real_T rtb_WheelInertia_do;
  real_T rtb_WheelInertia_h;
  real_T rtb_WheelInertia_j;
  real_T rtb_force;
  real_T rtb_force_c;
  real_T rtb_force_j;
  real_T rtb_force_n_idx_1;

  /* MATLAB Function: '<S1>/Angle2Rotmat' incorporates:
   *  DiscreteIntegrator: '<S1>/YawInt'
   */
  Plant_d_Bench_Angle2Rotmat(Plant_d_Bench_DW.YawInt_DSTATE, rtb_rotmat_m);

  /* MATLAB Function: '<S1>/Angle2Rotmat1' incorporates:
   *  DiscreteIntegrator: '<S1>/YawInt'
   *  Gain: '<S1>/Invert'
   */
  Plant_d_Bench_Angle2Rotmat(-Plant_d_Bench_DW.YawInt_DSTATE, rtb_rotmat);

  /* Gain: '<S1>/BodyVel' incorporates:
   *  DiscreteIntegrator: '<S1>/BodyMomentum'
   */
  tmp = _mm_mul_pd(_mm_set1_pd(0.4), _mm_loadu_pd
                   (&Plant_d_Bench_DW.BodyMomentum_DSTATE[0]));
  _mm_storeu_pd(&tmp_0[0], tmp);

  /* Gain: '<S1>/BodyVel' */
  rtb_BodyVel_idx_0 = tmp_0[0];
  rtb_BodyVel_idx_1 = tmp_0[1];

  /* Product: '<S1>/IF2BFF' */
  tmp = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&rtb_rotmat[0]), _mm_set1_pd(tmp_0[0])),
                   _mm_mul_pd(_mm_loadu_pd(&rtb_rotmat[2]), _mm_set1_pd(tmp_0[1])));
  _mm_storeu_pd(&tmp_0[0], tmp);

  /* Product: '<S8>/Body2Wheels' incorporates:
   *  Constant: '<S8>/Bod2WheelsMat'
   */
  rtb_WheelInertia_j = 0.70710678118654735 * tmp_0[0] + -0.70710678118654768 *
    tmp_0[1];

  /* Product: '<S7>/Body2Wheels' incorporates:
   *  Constant: '<S7>/Bod2WheelsMat'
   */
  rtb_WheelInertia_do = -0.70710678118654768 * tmp_0[0] + -0.70710678118654746 *
    tmp_0[1];

  /* Product: '<S6>/Body2Wheels' incorporates:
   *  Constant: '<S6>/Bod2WheelsMat'
   */
  rtb_WheelInertia_h = -0.86602540378443871 * tmp_0[0] + 0.49999999999999994 *
    tmp_0[1];

  /* Product: '<S5>/Body2Wheels' incorporates:
   *  Constant: '<S5>/Bod2WheelsMat'
   */
  rtb_TmpSignalConversionAtWhee_0 = 0.86602540378443871 * tmp_0[0] +
    0.49999999999999994 * tmp_0[1];

  /* Gain: '<S16>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S16>/WheelMomentum'
   */
  rtb_WheelInertia = 99999.999999999985 * Plant_d_Bench_DW.WheelMomentum_DSTATE;

  /* Gain: '<S1>/BodyAngularVel' incorporates:
   *  DiscreteIntegrator: '<S1>/BodyAngularMomentum'
   */
  Plant_d_Bench_Y.AngVel = 50.0 * Plant_d_Bench_DW.BodyAngularMomentum_DSTATE;

  /* Gain: '<S8>/BodyRot2Trans1' incorporates:
   *  Gain: '<S5>/BodyRot2Trans1'
   *  Gain: '<S6>/BodyRot2Trans1'
   *  Gain: '<S7>/BodyRot2Trans1'
   */
  rtb_Rmotor_j_tmp = 0.081 * Plant_d_Bench_Y.AngVel;

  /* MATLAB Function: '<S8>/MATLAB Function' incorporates:
   *  Constant: '<S8>/LinearFric'
   *  Constant: '<S8>/StaticFric'
   *  Constant: '<S8>/Subwheels'
   *  DiscreteIntegrator: '<S8>/WheelAngle'
   *  Gain: '<S8>/BodyRot2Trans1'
   *  Gain: '<S8>/Rot2Trans'
   *  Product: '<S8>/Body2Wheels'
   *  Sum: '<S8>/Sum'
   *  Sum: '<S8>/TotalSlip'
   */
  Plant_d_Bench_MATLABFunction(((0.0 - rtb_WheelInertia_j) - 0.027 *
    rtb_WheelInertia) - rtb_Rmotor_j_tmp, rtb_WheelInertia_j + rtb_Rmotor_j_tmp,
    Plant_d_Bench_DW.WheelAngle_DSTATE, 100.0, 5.0, 25.0, &rtb_force);

  /* Gain: '<S14>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S14>/WheelMomentum'
   */
  rtb_WheelInertia_j = 99999.999999999985 *
    Plant_d_Bench_DW.WheelMomentum_DSTATE_j;

  /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
   *  Constant: '<S7>/LinearFric'
   *  Constant: '<S7>/StaticFric'
   *  Constant: '<S7>/Subwheels'
   *  DiscreteIntegrator: '<S7>/WheelAngle'
   *  Gain: '<S7>/Rot2Trans'
   *  Product: '<S7>/Body2Wheels'
   *  Sum: '<S7>/Sum'
   *  Sum: '<S7>/TotalSlip'
   */
  Plant_d_Bench_MATLABFunction(((0.0 - rtb_WheelInertia_do) - 0.027 *
    rtb_WheelInertia_j) - rtb_Rmotor_j_tmp, rtb_WheelInertia_do +
    rtb_Rmotor_j_tmp, Plant_d_Bench_DW.WheelAngle_DSTATE_o, 100.0, 5.0, 25.0,
    &rtb_force_j);

  /* Gain: '<S12>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S12>/WheelMomentum'
   */
  rtb_WheelInertia_do = 99999.999999999985 *
    Plant_d_Bench_DW.WheelMomentum_DSTATE_o;

  /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
   *  Constant: '<S6>/LinearFric'
   *  Constant: '<S6>/StaticFric'
   *  Constant: '<S6>/Subwheels'
   *  DiscreteIntegrator: '<S6>/WheelAngle'
   *  Gain: '<S6>/Rot2Trans'
   *  Product: '<S6>/Body2Wheels'
   *  Sum: '<S6>/Sum'
   *  Sum: '<S6>/TotalSlip'
   */
  Plant_d_Bench_MATLABFunction(((0.0 - rtb_WheelInertia_h) - 0.027 *
    rtb_WheelInertia_do) - rtb_Rmotor_j_tmp, rtb_WheelInertia_h +
    rtb_Rmotor_j_tmp, Plant_d_Bench_DW.WheelAngle_DSTATE_m, 100.0, 5.0, 25.0,
    &rtb_force_c);

  /* Gain: '<S10>/WheelInertia' incorporates:
   *  DiscreteIntegrator: '<S10>/WheelMomentum'
   */
  rtb_WheelInertia_h = 99999.999999999985 *
    Plant_d_Bench_DW.WheelMomentum_DSTATE_f;

  /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
   *  Constant: '<S5>/LinearFric'
   *  Constant: '<S5>/StaticFric'
   *  Constant: '<S5>/Subwheels'
   *  DiscreteIntegrator: '<S5>/WheelAngle'
   *  Gain: '<S5>/Rot2Trans'
   *  Product: '<S5>/Body2Wheels'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/TotalSlip'
   */
  Plant_d_Bench_MATLABFunction(((0.0 - rtb_TmpSignalConversionAtWhee_0) - 0.027 *
    rtb_WheelInertia_h) - rtb_Rmotor_j_tmp, rtb_TmpSignalConversionAtWhee_0 +
    rtb_Rmotor_j_tmp, Plant_d_Bench_DW.WheelAngle_DSTATE_l, 100.0, 5.0, 25.0,
    &rtb_Rmotor_j);

  /* SignalConversion generated from: '<S8>/Wheel2Body' incorporates:
   *  Constant: '<S8>/Bod2WheelsMat'
   *  Gain: '<S8>/StrafeTraction'
   *  Product: '<S8>/Body2Wheels'
   */
  rtb_TmpSignalConversionAtWhee_0 = (0.70710678118654768 * tmp_0[0] +
    -0.70710678118654735 * tmp_0[1]) * -0.1;

  /* SignalConversion generated from: '<S7>/Wheel2Body' incorporates:
   *  Constant: '<S7>/Bod2WheelsMat'
   *  Gain: '<S7>/StrafeTraction'
   *  Product: '<S7>/Body2Wheels'
   */
  rtb_Rmotor_j_tmp = (0.70710678118654746 * tmp_0[0] + 0.70710678118654768 *
                      tmp_0[1]) * -0.1;

  /* SignalConversion generated from: '<S6>/Wheel2Body' incorporates:
   *  Constant: '<S6>/Bod2WheelsMat'
   *  Gain: '<S6>/StrafeTraction'
   *  Product: '<S6>/Body2Wheels'
   */
  rtb_force_n_idx_1 = (-0.49999999999999994 * tmp_0[0] + 0.86602540378443871 *
                       tmp_0[1]) * -0.1;

  /* SignalConversion generated from: '<S5>/Wheel2Body' incorporates:
   *  Constant: '<S5>/Bod2WheelsMat'
   *  Gain: '<S5>/StrafeTraction'
   *  Product: '<S5>/Body2Wheels'
   */
  rtb_Rmotor_c_idx_1 = (-0.49999999999999994 * tmp_0[0] + -0.86602540378443871 *
                        tmp_0[1]) * -0.1;

  /* Gain: '<S10>/Back-EMF' */
  tmp = _mm_set1_pd(0.032800000160932541);

  /* Gain: '<S10>/Rmotor' */
  tmp_1 = _mm_set1_pd(0.93457937240600586);

  /* Sum: '<S12>/Sum' incorporates:
   *  Constant: '<S4>/ConstVbat'
   *  Gain: '<S10>/Back-EMF'
   *  Gain: '<S12>/Back-EMF'
   *  Inport: '<Root>/PWM'
   *  Product: '<S10>/PWM2V'
   *  Product: '<S12>/PWM2V'
   *  Sum: '<S10>/Sum'
   */
  _mm_storeu_pd(&tmp_0[0], _mm_mul_pd(_mm_sub_pd(_mm_set_pd(24.0F *
    Plant_d_Bench_U.PWM[1], 24.0F * Plant_d_Bench_U.PWM[0]), _mm_mul_pd(tmp,
    _mm_set_pd(rtb_WheelInertia_do, rtb_WheelInertia_h))), tmp_1));

  /* Gain: '<S10>/Rmotor' */
  rtb_Rmotor_e = tmp_0[0];

  /* Gain: '<S12>/Rmotor' */
  rtb_Rmotor_m = tmp_0[1];

  /* Sum: '<S16>/Sum' incorporates:
   *  Constant: '<S4>/ConstVbat'
   *  Gain: '<S14>/Back-EMF'
   *  Gain: '<S16>/Back-EMF'
   *  Inport: '<Root>/PWM'
   *  Product: '<S14>/PWM2V'
   *  Product: '<S16>/PWM2V'
   *  Sum: '<S14>/Sum'
   */
  _mm_storeu_pd(&tmp_0[0], _mm_mul_pd(_mm_sub_pd(_mm_set_pd(24.0F *
    Plant_d_Bench_U.PWM[3], 24.0F * Plant_d_Bench_U.PWM[2]), _mm_mul_pd(tmp,
    _mm_set_pd(rtb_WheelInertia, rtb_WheelInertia_j))), tmp_1));

  /* Outport: '<Root>/WheelCurrents' */
  Plant_d_Bench_Y.WheelCurrents[0] = rtb_Rmotor_e;
  Plant_d_Bench_Y.WheelCurrents[1] = rtb_Rmotor_m;
  Plant_d_Bench_Y.WheelCurrents[2] = tmp_0[0];
  Plant_d_Bench_Y.WheelCurrents[3] = tmp_0[1];

  /* Outport: '<Root>/Out1' incorporates:
   *  DiscreteIntegrator: '<S5>/WheelAngle'
   *  DiscreteIntegrator: '<S6>/WheelAngle'
   *  DiscreteIntegrator: '<S7>/WheelAngle'
   *  DiscreteIntegrator: '<S8>/WheelAngle'
   */
  Plant_d_Bench_Y.Out1[0] = Plant_d_Bench_DW.WheelAngle_DSTATE_l;
  Plant_d_Bench_Y.Out1[1] = Plant_d_Bench_DW.WheelAngle_DSTATE_m;
  Plant_d_Bench_Y.Out1[2] = Plant_d_Bench_DW.WheelAngle_DSTATE_o;
  Plant_d_Bench_Y.Out1[3] = Plant_d_Bench_DW.WheelAngle_DSTATE;

  /* Outport: '<Root>/Yaw' incorporates:
   *  DiscreteIntegrator: '<S1>/YawInt'
   */
  Plant_d_Bench_Y.Yaw = Plant_d_Bench_DW.YawInt_DSTATE;

  /* Sum: '<S1>/Sum6' incorporates:
   *  Constant: '<S5>/Wheel2BodMat'
   *  Constant: '<S6>/Wheel2BodMat'
   *  Constant: '<S7>/Wheel2BodMat'
   *  Constant: '<S8>/Wheel2BodMat'
   *  Product: '<S5>/Wheel2Body'
   *  Product: '<S6>/Wheel2Body'
   *  Product: '<S7>/Wheel2Body'
   *  Product: '<S8>/Wheel2Body'
   *  SignalConversion generated from: '<S5>/Wheel2Body'
   *  SignalConversion generated from: '<S6>/Wheel2Body'
   *  SignalConversion generated from: '<S7>/Wheel2Body'
   *  SignalConversion generated from: '<S8>/Wheel2Body'
   *  Sum: '<S1>/Sum7'
   *  Sum: '<S1>/Sum8'
   */
  rtb_Sum6_0 = (((-0.86602540378443871 * rtb_force_c + -0.49999999999999994 *
                  rtb_force_n_idx_1) + (0.86602540378443871 * rtb_Rmotor_j +
    -0.49999999999999994 * rtb_Rmotor_c_idx_1)) + (-0.70710678118654768 *
    rtb_force_j + 0.70710678118654746 * rtb_Rmotor_j_tmp)) +
    (0.70710678118654735 * rtb_force + 0.70710678118654768 *
     rtb_TmpSignalConversionAtWhee_0);
  rtb_Sum6_idx_0 = rtb_Sum6_0;

  /* Outport: '<Root>/BFFAcceleration' incorporates:
   *  Gain: '<S1>/BodyAccel'
   */
  Plant_d_Bench_Y.BFFAcceleration[0] = 0.4 * rtb_Sum6_0;

  /* Outport: '<Root>/Out2' incorporates:
   *  DiscreteIntegrator: '<S1>/PositionInt'
   */
  Plant_d_Bench_Y.Out2[0] = Plant_d_Bench_DW.PositionInt_DSTATE[0];

  /* Sum: '<S1>/Sum6' incorporates:
   *  Constant: '<S5>/Wheel2BodMat'
   *  Constant: '<S6>/Wheel2BodMat'
   *  Constant: '<S7>/Wheel2BodMat'
   *  Constant: '<S8>/Wheel2BodMat'
   *  Product: '<S5>/Wheel2Body'
   *  Product: '<S6>/Wheel2Body'
   *  Product: '<S7>/Wheel2Body'
   *  Product: '<S8>/Wheel2Body'
   *  SignalConversion generated from: '<S5>/Wheel2Body'
   *  SignalConversion generated from: '<S6>/Wheel2Body'
   *  SignalConversion generated from: '<S7>/Wheel2Body'
   *  SignalConversion generated from: '<S8>/Wheel2Body'
   *  Sum: '<S1>/Sum7'
   *  Sum: '<S1>/Sum8'
   */
  rtb_Sum6_0 = (((0.49999999999999994 * rtb_force_c + 0.86602540378443871 *
                  rtb_force_n_idx_1) + (0.49999999999999994 * rtb_Rmotor_j +
    -0.86602540378443871 * rtb_Rmotor_c_idx_1)) + (-0.70710678118654746 *
    rtb_force_j + 0.70710678118654768 * rtb_Rmotor_j_tmp)) +
    (-0.70710678118654768 * rtb_force + -0.70710678118654735 *
     rtb_TmpSignalConversionAtWhee_0);

  /* Outport: '<Root>/BFFAcceleration' incorporates:
   *  Gain: '<S1>/BodyAccel'
   */
  Plant_d_Bench_Y.BFFAcceleration[1] = 0.4 * rtb_Sum6_0;

  /* Outport: '<Root>/Out2' incorporates:
   *  DiscreteIntegrator: '<S1>/PositionInt'
   */
  Plant_d_Bench_Y.Out2[1] = Plant_d_Bench_DW.PositionInt_DSTATE[1];

  /* Update for DiscreteIntegrator: '<S1>/YawInt' */
  Plant_d_Bench_DW.YawInt_DSTATE += 0.01 * Plant_d_Bench_Y.AngVel;

  /* Update for DiscreteIntegrator: '<S8>/WheelAngle' */
  Plant_d_Bench_DW.WheelAngle_DSTATE += 0.01 * rtb_WheelInertia;

  /* Update for DiscreteIntegrator: '<S16>/WheelMomentum' incorporates:
   *  Gain: '<S16>/MotorGyration'
   *  Gain: '<S16>/RotFriction'
   *  Gain: '<S8>/Force2Torque'
   *  Sum: '<S16>/Sum1'
   *  Sum: '<S16>/Sum2'
   */
  Plant_d_Bench_DW.WheelMomentum_DSTATE += ((0.027 * rtb_force +
    -9.9999997473787516E-6 * rtb_WheelInertia) + 0.032800000160932541 * tmp_0[1])
    * 0.01;

  /* Update for DiscreteIntegrator: '<S1>/BodyAngularMomentum' incorporates:
   *  Gain: '<S5>/WheelForce2BodyTorque'
   *  Gain: '<S6>/WheelForce2BodyTorque'
   *  Gain: '<S7>/WheelForce2BodyTorque'
   *  Gain: '<S8>/WheelForce2BodyTorque'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum4'
   *  Sum: '<S1>/Sum5'
   */
  Plant_d_Bench_DW.BodyAngularMomentum_DSTATE += (((0.081 * rtb_force_c + 0.081 *
    rtb_Rmotor_j) + 0.081 * rtb_force_j) + 0.081 * rtb_force) * 0.01;

  /* Update for DiscreteIntegrator: '<S7>/WheelAngle' */
  Plant_d_Bench_DW.WheelAngle_DSTATE_o += 0.01 * rtb_WheelInertia_j;

  /* Update for DiscreteIntegrator: '<S14>/WheelMomentum' incorporates:
   *  Gain: '<S14>/MotorGyration'
   *  Gain: '<S14>/RotFriction'
   *  Gain: '<S7>/Force2Torque'
   *  Sum: '<S14>/Sum1'
   *  Sum: '<S14>/Sum2'
   */
  Plant_d_Bench_DW.WheelMomentum_DSTATE_j += ((0.027 * rtb_force_j +
    -9.9999997473787516E-6 * rtb_WheelInertia_j) + 0.032800000160932541 * tmp_0
    [0]) * 0.01;

  /* Update for DiscreteIntegrator: '<S6>/WheelAngle' */
  Plant_d_Bench_DW.WheelAngle_DSTATE_m += 0.01 * rtb_WheelInertia_do;

  /* Update for DiscreteIntegrator: '<S12>/WheelMomentum' incorporates:
   *  Gain: '<S12>/MotorGyration'
   *  Gain: '<S12>/RotFriction'
   *  Gain: '<S6>/Force2Torque'
   *  Sum: '<S12>/Sum1'
   *  Sum: '<S12>/Sum2'
   */
  Plant_d_Bench_DW.WheelMomentum_DSTATE_o += ((0.027 * rtb_force_c +
    -9.9999997473787516E-6 * rtb_WheelInertia_do) + 0.032800000160932541 *
    rtb_Rmotor_m) * 0.01;

  /* Update for DiscreteIntegrator: '<S5>/WheelAngle' */
  Plant_d_Bench_DW.WheelAngle_DSTATE_l += 0.01 * rtb_WheelInertia_h;

  /* Update for DiscreteIntegrator: '<S10>/WheelMomentum' incorporates:
   *  Gain: '<S10>/MotorGyration'
   *  Gain: '<S10>/RotFriction'
   *  Gain: '<S5>/Force2Torque'
   *  Sum: '<S10>/Sum1'
   *  Sum: '<S10>/Sum2'
   */
  Plant_d_Bench_DW.WheelMomentum_DSTATE_f += ((0.027 * rtb_Rmotor_j +
    -9.9999997473787516E-6 * rtb_WheelInertia_h) + 0.032800000160932541 *
    rtb_Rmotor_e) * 0.01;

  /* Update for DiscreteIntegrator: '<S1>/BodyMomentum' incorporates:
   *  Product: '<S1>/BFF2IF'
   *  Sum: '<S1>/Sum6'
   */
  Plant_d_Bench_DW.BodyMomentum_DSTATE[0] += (rtb_rotmat_m[0] * rtb_Sum6_idx_0 +
    rtb_rotmat_m[2] * rtb_Sum6_0) * 0.01;

  /* Update for DiscreteIntegrator: '<S1>/PositionInt' */
  Plant_d_Bench_DW.PositionInt_DSTATE[0] += 0.01 * rtb_BodyVel_idx_0;

  /* Update for DiscreteIntegrator: '<S1>/BodyMomentum' incorporates:
   *  Product: '<S1>/BFF2IF'
   *  Sum: '<S1>/Sum6'
   */
  Plant_d_Bench_DW.BodyMomentum_DSTATE[1] += (rtb_rotmat_m[1] * rtb_Sum6_idx_0 +
    rtb_rotmat_m[3] * rtb_Sum6_0) * 0.01;

  /* Update for DiscreteIntegrator: '<S1>/PositionInt' */
  Plant_d_Bench_DW.PositionInt_DSTATE[1] += 0.01 * rtb_BodyVel_idx_1;
}

/* Model initialize function */
void Plant_d_Bench_initialize(void)
{
  /* Registration code */

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Plant_d_Bench_InitializeDataMapInfo();
}

/* Model terminate function */
void Plant_d_Bench_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
