# roboteam_microcontroller6.0

## Generating code with STM32CubeMX
Sometimes changes to the microcontroller are made and you need to generate new code from STM32CubeMX. To keep the *USER CODE* in for example main.c the following steps should be followed.

1. Make your changes in the .ioc file
2. Move the main.c file of the board you are working from Core/Src/[board] to Core/Src files.
3. Generate code
4. Move the files back to their original location

For the other generated files like syscalls.c and stm32[version] can be copied pasted into the correct location, replacing the old files.