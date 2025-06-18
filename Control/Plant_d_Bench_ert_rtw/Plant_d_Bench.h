/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Plant_d_Bench.h
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

#ifndef Plant_d_Bench_h_
#define Plant_d_Bench_h_
#ifndef Plant_d_Bench_COMMON_INCLUDES_
#define Plant_d_Bench_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Plant_d_Bench_COMMON_INCLUDES_ */

#include "Plant_d_Bench_types.h"
#include "rtw_modelmap.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T YawInt_DSTATE;                /* '<S1>/YawInt' */
  real_T BodyMomentum_DSTATE[2];       /* '<S1>/BodyMomentum' */
  real_T WheelAngle_DSTATE;            /* '<S8>/WheelAngle' */
  real_T WheelMomentum_DSTATE;         /* '<S16>/WheelMomentum' */
  real_T BodyAngularMomentum_DSTATE;   /* '<S1>/BodyAngularMomentum' */
  real_T WheelAngle_DSTATE_o;          /* '<S7>/WheelAngle' */
  real_T WheelMomentum_DSTATE_j;       /* '<S14>/WheelMomentum' */
  real_T WheelAngle_DSTATE_m;          /* '<S6>/WheelAngle' */
  real_T WheelMomentum_DSTATE_o;       /* '<S12>/WheelMomentum' */
  real_T WheelAngle_DSTATE_l;          /* '<S5>/WheelAngle' */
  real_T WheelMomentum_DSTATE_f;       /* '<S10>/WheelMomentum' */
  real_T PositionInt_DSTATE[2];        /* '<S1>/PositionInt' */
} DW_Plant_d_Bench_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T PWM[4];                     /* '<Root>/PWM' */
} ExtU_Plant_d_Bench_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Out1[4];                      /* '<Root>/Out1' */
  real_T Out2[2];                      /* '<Root>/Out2' */
  real_T AngVel;                       /* '<Root>/AngVel' */
  real_T Yaw;                          /* '<Root>/Yaw' */
  real_T WheelCurrents[4];             /* '<Root>/WheelCurrents' */
  real_T BFFAcceleration[2];           /* '<Root>/BFFAcceleration' */
} ExtY_Plant_d_Bench_T;

/* Real-time Model Data Structure */
struct tag_RTM_Plant_d_Bench_T {
  const char_T * volatile errorStatus;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;
};

/* Block states (default storage) */
extern DW_Plant_d_Bench_T Plant_d_Bench_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Plant_d_Bench_T Plant_d_Bench_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Plant_d_Bench_T Plant_d_Bench_Y;

/* Model entry point functions */
extern void Plant_d_Bench_initialize(void);
extern void Plant_d_Bench_step(void);
extern void Plant_d_Bench_terminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Plant_d_Bench_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_Plant_d_Bench_T *const Plant_d_Bench_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Sum' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<S1>/Sum2' : Unused code path elimination
 * Block '<S5>/Relvel' : Unused code path elimination
 * Block '<S5>/Wheelvel' : Unused code path elimination
 * Block '<S6>/Relvel' : Unused code path elimination
 * Block '<S6>/Wheelvel' : Unused code path elimination
 * Block '<S7>/Relvel' : Unused code path elimination
 * Block '<S7>/Wheelvel' : Unused code path elimination
 * Block '<S8>/Relvel' : Unused code path elimination
 * Block '<S8>/Wheelvel' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Plant_d_Bench'
 * '<S1>'   : 'Plant_d_Bench/Subsystem Reference'
 * '<S2>'   : 'Plant_d_Bench/Subsystem Reference/Angle2Rotmat'
 * '<S3>'   : 'Plant_d_Bench/Subsystem Reference/Angle2Rotmat1'
 * '<S4>'   : 'Plant_d_Bench/Subsystem Reference/Subsystem Reference4'
 * '<S5>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly0'
 * '<S6>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly1'
 * '<S7>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly2'
 * '<S8>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly3'
 * '<S9>'   : 'Plant_d_Bench/Subsystem Reference/WheelAssembly0/MATLAB Function'
 * '<S10>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly0/Wheel'
 * '<S11>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly1/MATLAB Function'
 * '<S12>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly1/Wheel'
 * '<S13>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly2/MATLAB Function'
 * '<S14>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly2/Wheel'
 * '<S15>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly3/MATLAB Function'
 * '<S16>'  : 'Plant_d_Bench/Subsystem Reference/WheelAssembly3/Wheel'
 */
#endif                                 /* Plant_d_Bench_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
