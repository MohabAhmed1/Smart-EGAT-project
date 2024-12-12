################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/CJSON/subdir.mk
-include Src/03-HAL/03-RELAY/subdir.mk
-include Src/03-HAL/02-LIGHT_SENSOR/subdir.mk
-include Src/03-HAL/01-TEMP_SENSOR/subdir.mk
-include Src/02-SERVICE/OS/subdir.mk
-include Src/01-MCAL/12-ADC/subdir.mk
-include Src/01-MCAL/11-USART/subdir.mk
-include Src/01-MCAL/10-PWM/subdir.mk
-include Src/01-MCAL/09-SPI/subdir.mk
-include Src/01-MCAL/08-TIM/subdir.mk
-include Src/01-MCAL/07-I2C/subdir.mk
-include Src/01-MCAL/06-AFIO/subdir.mk
-include Src/01-MCAL/05-EXTI/subdir.mk
-include Src/01-MCAL/04-NVIC/subdir.mk
-include Src/01-MCAL/03-STK/subdir.mk
-include Src/01-MCAL/02-DIO/subdir.mk
-include Src/01-MCAL/01-PORT/subdir.mk
-include Src/01-MCAL/00-RCC/subdir.mk
-include Src/00-LIB/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SMART_EGAT
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SMART_EGAT.elf \

MAP_FILES += \
SMART_EGAT.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SMART_EGAT.list \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: SMART_EGAT.elf secondary-outputs

# Tool invocations
SMART_EGAT.elf SMART_EGAT.map: $(OBJS) $(USER_OBJS) E:\Embedded\ Systems\ARM_Projects\Test_task\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SMART_EGAT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Embedded Systems\ARM_Projects\Test_task\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SMART_EGAT.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SMART_EGAT.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SMART_EGAT.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SMART_EGAT.elf SMART_EGAT.list SMART_EGAT.map default.size.stdout
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex SMART_EGAT.elf  SMART_EGAT.hex
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets
