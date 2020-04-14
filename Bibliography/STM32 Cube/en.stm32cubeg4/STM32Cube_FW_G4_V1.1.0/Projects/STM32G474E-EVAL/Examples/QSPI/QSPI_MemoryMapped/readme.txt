/**
  @page QSPI_MemoryMapped QSPI memory mapped example

  @verbatim
  ******************************************************************************
  * @file    QSPI/QSPI_MemoryMapped/readme.txt
  * @author  MCD Application Team
  * @brief   QSPI memory mapped mode example.
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

This example describes how to erase part of the QSPI memory, write data in DMA mode
and access to QSPI memory in memory-mapped mode to check the data in a forever loop.

LED1 toggles each time the data have been checked
LED3 toggles as soon as an error is returned by HAL API
LED3 is on as soon as a data is wrong

In this example, HCLK is configured at 170 MHz.
QSPI prescaler is set to 1, so QSPI frequency is = HCLK/(QSPI_Prescaler+1) = 170 MHz/(1+1)

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Memory, QSPI, Erase, Read, Write, Mapped

@par Directory contents

  - QSPI/QSPI_MemoryMapped/Inc/stm32g474e_eval_conf.h     BSP configuration file
  - QSPI/QSPI_MemoryMapped/Inc/stm32g4xx_hal_conf.h HAL configuration file
  - QSPI/QSPI_MemoryMapped/Inc/stm32g4xx_it.h       Interrupt handlers header file
  - QSPI/QSPI_MemoryMapped/Inc/main.h               Header for main.c module
  - QSPI/QSPI_MemoryMapped/Src/stm32g4xx_it.c       Interrupt handlers
  - QSPI/QSPI_MemoryMapped/Src/main.c               Main program
  - QSPI/QSPI_MemoryMapped/Src/system_stm32g4xx.c   STM32G4xx system source file
  - QSPI/QSPI_MemoryMapped/Src/stm32g4xx_hal_msp.c  HAL MSP file


@par Hardware and Software environment

  - This example runs on STM32G474QETx devices.

  - This example has been tested with STM32G474E-EVAL Rev B board and can be
    easily tailored to any other supported device and development board.

  - STM32G474E-EVAL Rev B Set-up :
    - Board is configured by default to access QSPI memory

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
