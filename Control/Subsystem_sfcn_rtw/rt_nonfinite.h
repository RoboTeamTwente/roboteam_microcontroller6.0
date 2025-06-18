

        /*
    * rt_nonfinite.h
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


    #ifndef rt_nonfinite_h_
    #define rt_nonfinite_h_



    
#include "rtwtypes.h"


    

    

    

    

    

    

    

    

    

    

    

    

    

    

    
    
                extern real_T rtInf;



                extern real_T rtMinusInf;



                extern real_T rtNaN;



                extern real32_T rtInfF;



                extern real32_T rtMinusInfF;



                extern real32_T rtNaNF;




        extern boolean_T rtIsInf(real_T value);
            extern boolean_T rtIsInfF(real32_T value);
            extern boolean_T rtIsNaN(real_T value);
            extern boolean_T rtIsNaNF(real32_T value);
    
    


    

    

    

    

    

    #endif /* rt_nonfinite_h_ */
