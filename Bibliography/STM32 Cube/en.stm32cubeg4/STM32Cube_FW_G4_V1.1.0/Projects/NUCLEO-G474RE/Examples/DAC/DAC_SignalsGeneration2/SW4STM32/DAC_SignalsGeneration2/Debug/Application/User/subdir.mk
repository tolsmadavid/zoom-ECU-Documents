################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/main.c \
C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/stm32g4xx_hal_msp.c \
C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/stm32g4xx_it.c 

OBJS += \
./Application/User/main.o \
./Application/User/stm32g4xx_hal_msp.o \
./Application/User/stm32g4xx_it.o 

C_DEPS += \
./Application/User/main.d \
./Application/User/stm32g4xx_hal_msp.d \
./Application/User/stm32g4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/main.o: C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_NUCLEO_64 -c -I../../../Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/STM32G4xx_Nucleo -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32g4xx_hal_msp.o: C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/stm32g4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_NUCLEO_64 -c -I../../../Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/STM32G4xx_Nucleo -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32g4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32g4xx_it.o: C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/Src/stm32g4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_NUCLEO_64 -c -I../../../Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/STM32G4xx_Nucleo -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32g4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

