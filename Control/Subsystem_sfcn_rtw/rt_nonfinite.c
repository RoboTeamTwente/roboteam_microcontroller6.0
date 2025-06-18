

        /*
    * rt_nonfinite.c
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
    */




    
#include "rtwtypes.h"

#include "rt_nonfinite.h"

#include "math.h"


    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

                real_T rtNaN = -(real_T)NAN;



                real_T rtInf = (real_T)INFINITY;



                real_T rtMinusInf = -(real_T)INFINITY;



                real32_T rtNaNF = -(real32_T)NAN;



                real32_T rtInfF = (real32_T)INFINITY;



                real32_T rtMinusInfF = -(real32_T)INFINITY;






        /* Test if value is infinite */
         boolean_T rtIsInf(real_T value) {
        return (boolean_T)isinf(value);
    }
    
    /* Test if single-precision value is infinite */
         boolean_T rtIsInfF(real32_T value) {
        return (boolean_T)isinf(value);
    }
    
    /* Test if value is not a number */
         boolean_T rtIsNaN(real_T value) {
        return (boolean_T)(isnan(value) != 0);
    }
    
    /* Test if single-precision value is not a number */
         boolean_T rtIsNaNF(real32_T value) {
        return (boolean_T)(isnan(value) != 0);
    }
    


    

    

    

    
