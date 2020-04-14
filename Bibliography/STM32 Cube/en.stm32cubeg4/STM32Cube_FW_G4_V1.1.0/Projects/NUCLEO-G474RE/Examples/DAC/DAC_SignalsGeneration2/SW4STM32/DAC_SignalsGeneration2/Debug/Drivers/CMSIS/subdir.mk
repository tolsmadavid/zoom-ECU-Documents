################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/system_stm32g4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32g4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32g4xx.o: C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/system_stm32g4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_NUCLEO_64 -c -I../../../Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/STM32G4xx_Nucleo -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/system_stm32g4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

