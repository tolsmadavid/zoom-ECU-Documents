/**
  @page FMAC_Adaptive_FIR_AN5305 FMAC FIR adaptive filter

  @verbatim
  ******************************************************************************
  * @file    FMAC/FMAC_Adaptive_FIR_AN5305/readme.txt
  * @author  MCD Application Team
  * @brief   Description of FMAC_Adaptive_FIR_AN5305 example.
  ******************************************************************************
  *
  * Copyright (c) 2019 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description

How to use the FMAC peripheral to implement an adaptive FIR filter in DMA mode.

This example illustrates noise cancellation using an adaptive FIR filter.
It is be run on two input frames:
 - a gaussian noise with two tone interferers.
 - a gaussian noise with three tone interferers.
A specific coefficient set will be used for each one.
The result is a "whitened" noise.

The FMAC peripheral is configured to perform an adaptive FIR filter with
51 feed-forward taps and a gain equal to 0. The input and output
thresholds are set to 1. The clipping feature can be enabled or disabled thanks
to the compilation switch CLIP_ENABLED in main.h.

The FMAC peripheral is configured so as to use the best of its 256 x 16-bit
internal memory. This local memory is divided into three buffers:
 -   0 to  50: coefficient buffer;
 -  51 to 150: input buffer;
 - 151 to 250: output buffer;
 - 251 to 255: unused.

DMA mode is used to transfer input data from memory to the FMAC peripheral.
DMA mode is used to transfer output data from FMAC peripheral to memory.

The coefficient buffer contains the vector of feed-forward taps, named B
(size comprised in [2:127]; here, size N = 51 elements).
This buffer is initialized during the configuration step in DMA mode.

The size of the input buffer is the sum of:
 - the size of the coefficient vector B (N = 51 elements);
 - the size of the additional space D1 needed for throughput improvement
   (minimum: 0; here, D1 = 49 elements).
The input buffer is filled during the preload step in DMA mode;
new values are added in DMA mode once the preloaded ones have been consumed.

The size of the output buffer is the one of the additional space D2 needed for a
better throughput (minimum: 1; here, D2 = 100 elements).
The output buffer is read in DMA mode.

STM32 board LEDs are used to monitor the example status:
  - LED4 is ON when correct FMAC FIR results have been calculated.
  - LED5 is blinking (1 second period) if an error is detected
    in the FIR filter results or if there is an initialization or configuration error.

The filtered output is displayed in the Terminal I/O if the compilation switch
PRINT_OUTPUT is enabled in main.h.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to
      1 millisecond to have correct HAL operation.

@par Directory contents

  - FMAC/FMAC_Adaptive_FIR_AN5305/Src/main.c                  Main program
  - FMAC/FMAC_Adaptive_FIR_AN5305/Src/system_stm32g4xx.c      STM32G4xx system clock configuration file
  - FMAC/FMAC_Adaptive_FIR_AN5305/Src/stm32g4xx_it.c          Interrupt handlers
  - FMAC/FMAC_Adaptive_FIR_AN5305/Src/stm32g4xx_hal_msp.c     HAL MSP module
  - FMAC/FMAC_Adaptive_FIR_AN5305/Inc/2ToneNoise.h            Data related to a two tone noise
  - FMAC/FMAC_Adaptive_FIR_AN5305/Inc/3ToneNoise.h            Data related to a three tone noise
  - FMAC/FMAC_Adaptive_FIR_AN5305/Inc/main.h                  Main program header file
  - FMAC/FMAC_Adaptive_FIR_AN5305/Inc/stm32g4xx_hal_conf.h    HAL Configuration file
  - FMAC/FMAC_Adaptive_FIR_AN5305/Inc/stm32g4xx_it.h          Interrupt handlers header file
  - FMAC/FMAC_Adaptive_FIR_AN5305/Inc/b_g474e_dpow1_conf.h BSP configuration file


@par Hardware and Software environment

  - This example runs on STM32G474RETx devices.

  - This example has been tested with B-G474E-DPOW1 board and can be
    easily tailored to any other supported device and development board.


@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
