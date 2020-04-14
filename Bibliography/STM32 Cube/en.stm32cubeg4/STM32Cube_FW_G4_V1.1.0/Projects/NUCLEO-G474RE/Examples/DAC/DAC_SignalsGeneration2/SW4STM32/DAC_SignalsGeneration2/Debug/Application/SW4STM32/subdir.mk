################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/SW4STM32/startup_stm32g474xx.s 

OBJS += \
./Application/SW4STM32/startup_stm32g474xx.o 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32g474xx.o: C:/Users/David\ Tolsma/Documents/WWU\ -\ EE\ Capstone\ Project/STM32\ Cube/en.stm32cubeg4/STM32Cube_FW_G4_V1.1.0/Projects/NUCLEO-G474RE/Examples/DAC/DAC_SignalsGeneration2/SW4STM32/startup_stm32g474xx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

