/*
 * Subsystem_sid.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Subsystem_sf".
 *
 * Model version              : 1.2
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Wed May 21 15:16:46 2025
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 * SOURCES: Subsystem_sf.c
 */

/* statically allocated instance data for model: Subsystem */
{
  {
    /* Local SimStruct for the generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* block I/O */
    {
      static B_Subsystem_T sfcnB;
      void *b = (real_T *) &sfcnB;
      ssSetLocalBlockIO(rts, b);
      (void) memset(b, 0,
                    sizeof(B_Subsystem_T));
    }

    /* model checksums */
    ssSetChecksumVal(rts, 0, 2807606390U);
    ssSetChecksumVal(rts, 1, 3434409786U);
    ssSetChecksumVal(rts, 2, 576953699U);
    ssSetChecksumVal(rts, 3, 2104914407U);
  }
}
