################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/03-HAL/02-LIGHT_SENSOR/LIGHT_program.c 

OBJS += \
./Src/03-HAL/02-LIGHT_SENSOR/LIGHT_program.o 

C_DEPS += \
./Src/03-HAL/02-LIGHT_SENSOR/LIGHT_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/03-HAL/02-LIGHT_SENSOR/%.o Src/03-HAL/02-LIGHT_SENSOR/%.su: ../Src/03-HAL/02-LIGHT_SENSOR/%.c Src/03-HAL/02-LIGHT_SENSOR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-03-2d-HAL-2f-02-2d-LIGHT_SENSOR

clean-Src-2f-03-2d-HAL-2f-02-2d-LIGHT_SENSOR:
	-$(RM) ./Src/03-HAL/02-LIGHT_SENSOR/LIGHT_program.d ./Src/03-HAL/02-LIGHT_SENSOR/LIGHT_program.o ./Src/03-HAL/02-LIGHT_SENSOR/LIGHT_program.su

.PHONY: clean-Src-2f-03-2d-HAL-2f-02-2d-LIGHT_SENSOR

