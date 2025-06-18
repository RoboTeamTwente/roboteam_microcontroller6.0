/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Plant_d_Bench_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Plant_d_Bench_capi_host.h"
#define sizeof(...)                    ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "Plant_d_Bench.h"
#include "Plant_d_Bench_capi.h"
#include "Plant_d_Bench_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block states information */
static const rtwCAPI_States rtBlockStates[] = {
  /* addrMapIndex, contStateStartIndex, blockPath,
   * stateName, pathAlias, dWorkIndex, dataTypeIndex, dimIndex,
   * fixPtIdx, sTimeIndex, isContinuous, hierInfoIdx, flatElemIdx
   */
  { 0, -1, TARGET_STRING("Plant_d_Bench/Subsystem Reference/BodyAngularMomentum"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 1, -1, TARGET_STRING("Plant_d_Bench/Subsystem Reference/BodyMomentum"),
    TARGET_STRING("DSTATE"), "", 0, 0, 1, 0, 0, 0, -1, 0 },

  { 2, -1, TARGET_STRING("Plant_d_Bench/Subsystem Reference/PositionInt"),
    TARGET_STRING("DSTATE"), "", 0, 0, 1, 0, 0, 0, -1, 0 },

  { 3, -1, TARGET_STRING("Plant_d_Bench/Subsystem Reference/YawInt"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 4, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly0/WheelAngle"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 5, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly1/WheelAngle"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 6, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly2/WheelAngle"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 7, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly3/WheelAngle"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 8, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly0/Wheel/WheelMomentum"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 9, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly1/Wheel/WheelMomentum"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 10, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly2/Wheel/WheelMomentum"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  { 11, -1, TARGET_STRING(
    "Plant_d_Bench/Subsystem Reference/WheelAssembly3/Wheel/WheelMomentum"),
    TARGET_STRING("DSTATE"), "", 0, 0, 0, 0, 0, 0, -1, 0 },

  {
    0, -1, (NULL), (NULL), (NULL), 0, 0, 0, 0, 0, 0, -1, 0
  }
};

#ifndef HOST_CAPI_BUILD

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &Plant_d_Bench_DW.BodyAngularMomentum_DSTATE,/* 0: Discrete State */
  &Plant_d_Bench_DW.BodyMomentum_DSTATE[0],/* 1: Discrete State */
  &Plant_d_Bench_DW.PositionInt_DSTATE[0],/* 2: Discrete State */
  &Plant_d_Bench_DW.YawInt_DSTATE,     /* 3: Discrete State */
  &Plant_d_Bench_DW.WheelAngle_DSTATE_l,/* 4: Discrete State */
  &Plant_d_Bench_DW.WheelAngle_DSTATE_m,/* 5: Discrete State */
  &Plant_d_Bench_DW.WheelAngle_DSTATE_o,/* 6: Discrete State */
  &Plant_d_Bench_DW.WheelAngle_DSTATE, /* 7: Discrete State */
  &Plant_d_Bench_DW.WheelMomentum_DSTATE_f,/* 8: Discrete State */
  &Plant_d_Bench_DW.WheelMomentum_DSTATE_o,/* 9: Discrete State */
  &Plant_d_Bench_DW.WheelMomentum_DSTATE_j,/* 10: Discrete State */
  &Plant_d_Bench_DW.WheelMomentum_DSTATE,/* 11: Discrete State */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  { "double", "real_T", 0, 0, sizeof(real_T), (uint8_T)SS_DOUBLE, 0, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  2,                                   /* 2 */
  1                                    /* 3 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.01, 0.0
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    (int8_T)0, (uint8_T)0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { (NULL), 0,
    (NULL), 0,
    (NULL), 0 },

  { (NULL), 0,
    (NULL), 0 },

  { rtBlockStates, 12 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 4034693339U,
    3285025948U,
    1806050483U,
    3636129167U },
  (NULL), 0,
  (boolean_T)0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  Plant_d_Bench_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void Plant_d_Bench_InitializeDataMapInfo(void)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(Plant_d_Bench_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(Plant_d_Bench_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(Plant_d_Bench_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(Plant_d_Bench_M->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(Plant_d_Bench_M->DataMapInfo.mmi,
    rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(Plant_d_Bench_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(Plant_d_Bench_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(Plant_d_Bench_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void Plant_d_Bench_host_InitializeDataMapInfo(Plant_d_Bench_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, (NULL));

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, (NULL));

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, (NULL));

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
