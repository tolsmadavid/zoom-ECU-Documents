/**
  @page COMP_OutputBlanking COMP example
  
  @verbatim
  ******************************************************************************
  * @file    Examples/COMP/COMP_OutputBlanking/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the COMP output blanking Example
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

How to use the comparator-peripheral output blanking feature. The purpose of the
output blanking feature in motor control is to prevent tripping of the current
regulation upon short current spikes at the beginning of the PWM period.

In this example COMP1 and TIM2 are used:
COMP1 is configured as following:
 - Non Inverting input is connected to PB1
 - Inverting input is connected to VREFINT (1.22V)
 - Output is available on PF4 (pin 57 on connector CN6)
 - Blanking source is connected internally to TIM2 TIM_CHANNEL_3


TIM2 is configured as following:
 - TIM2 frequency is 1kHz.
 - TIM2 TIM_CHANNEL_3  (PA2 - pin 43 on connector CN6) configured in PWM mode.
 - Timer channel intended to be connected to an external device (motor, ...) in user application:
   TIM2 TIM_CHANNEL_1 (PA0 - pin 45 on connector CN6) configured in PWM mode.
 - Both these PWM are running at same frequency of TIM2.

Connection needed:
 - either connect COMP1 input (PB1 - pin 33 on connector CN6) to TIM2 TIM_CHANNEL_1 (PA0 - pin 45 on connector CN6).
 - either connect COMP1 input (PB1 - pin 33 on connector CN6) to a signal generator, at the frequency of TIM2 (to have comparator input signal frequency matching blanking signal frequency). To do this, possibility to use TIM2 TIM_CHANNEL_1 (PA0 - pin 45 on connector CN6) as trigger of signal generator).
 
Comparator output signal expected:
 - Between t=0us and t=27.7us: Comparator positive input at level high, blanking source at level high.
   Blanking source is high, therefore comparator output is forced to level low.
   (otherwise, as comparator positive input is higher than negative input, comparator output would have been high.)
 - Between t=27.7us and t=duty cycle pulse: Comparator positive input at level high, blanking source at level low.
   Comparator positive input is higher than negative input, blanking source is low, therefore comparator output is high.
 - Between t=duty cycle pulse and t=period: Comparator positive input at level low, blanking source at level low.
   Comparator positive input is higher than negative input, therefore comparator output is low.

STM32G474E-EVAL Rev B board's LED is be used to monitor the program execution status:
  - LED1 is toggling every 500ms when test pass successfully.
  - LED1 is "ON" when an error occurred.

@note Care must be taken when using HAL_Delay(), this function provides 
      accurate delay (in milliseconds) based on variable incremented in SysTick ISR. 
      This implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower) than the 
      peripheral interrupt. Otherwise the caller ISR process will be blocked. 
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set 
      to 1 millisecond to have correct HAL operation.

@par Keywords

comparator, output blanking.

@par Directory contents 

  - COMP/COMP_OutputBlanking/Inc/stm32g474e_eval_conf.h     BSP configuration file
  - COMP/COMP_OutputBlanking/Inc/stm32g4xx_hal_conf.h    HAL configuration file
  - COMP/COMP_OutputBlanking/Inc/stm32g4xx_it.h          COMP interrupt handlers header file
  - COMP/COMP_OutputBlanking/Inc/main.h                  Header for main.c module
  - COMP/COMP_OutputBlanking/Src/stm32g4xx_it.c          COMP interrupt handlers
  - COMP/COMP_OutputBlanking/Src/main.c                  Main program
  - COMP/COMP_OutputBlanking/Src/stm32g4xx_hal_msp.c     HAL MSP file 
  - COMP/COMP_OutputBlanking/Src/system_stm32g4xx.c      STM32G4xx system source file


@par Hardware and Software environment

  - This example runs on STM32G474xx devices.

  - This example has been tested with STM32G474E-EVAL Rev B board and can be
    easily tailored to any other supported device and development board.

  - 
    


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
