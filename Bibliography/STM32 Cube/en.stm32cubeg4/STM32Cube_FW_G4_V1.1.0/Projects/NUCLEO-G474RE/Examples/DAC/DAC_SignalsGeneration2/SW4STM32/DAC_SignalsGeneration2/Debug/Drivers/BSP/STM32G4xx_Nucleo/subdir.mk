################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.c 

OBJS += \
./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.o 

C_DEPS += \
./Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.o: C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_NUCLEO_64 -c -I../../../Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/STM32G4xx_Nucleo -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

