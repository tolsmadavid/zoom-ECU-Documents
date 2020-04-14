################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32G4xx_Nucleo/subdir.mk
-include Application/User/subdir.mk
-include Application/SW4STM32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DAC_SignalsGeneration2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DAC_SignalsGeneration2.list \

OBJCOPY_HEX += \
DAC_SignalsGeneration2.hex \


# All Target
all: DAC_SignalsGeneration2.elf secondary-outputs

# Tool invocations
DAC_SignalsGeneration2.elf: $(OBJS) $(USER_OBJS) ../STM32G474RETx_FLASH.ld
	arm-none-eabi-gcc -o "DAC_SignalsGeneration2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../STM32G474RETx_FLASH.ld" --specs=nosys.specs -Wl,-Map="DAC_SignalsGeneration2.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DAC_SignalsGeneration2.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DAC_SignalsGeneration2.list"
	@echo 'Finished building: $@'
	@echo ' '

DAC_SignalsGeneration2.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "DAC_SignalsGeneration2.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
