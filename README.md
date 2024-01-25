# roboteam_microcontroller6.0

## Generating code with STM32CubeMX
Sometimes changes to the microcontroller are made and you need to generate new code from STM32CubeMX. To keep the *USER CODE* in for example main.c the following steps should be followed.

1. Make your changes in the .ioc file
2. Move the main.c/h, stm32[version]_it.c/h and stm[version]_hal_msp.c/h files of the board you are working to Core/Src and Core/Inc for .c and .h files respectively
3. Generate code
4. Move the files back to their original location