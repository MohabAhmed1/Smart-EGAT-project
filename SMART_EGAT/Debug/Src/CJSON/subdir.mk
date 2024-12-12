################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CJSON/cJSON.c 

OBJS += \
./Src/CJSON/cJSON.o 

C_DEPS += \
./Src/CJSON/cJSON.d 


# Each subdirectory must supply rules for building sources it contributes
Src/CJSON/%.o Src/CJSON/%.su: ../Src/CJSON/%.c Src/CJSON/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-CJSON

clean-Src-2f-CJSON:
	-$(RM) ./Src/CJSON/cJSON.d ./Src/CJSON/cJSON.o ./Src/CJSON/cJSON.su

.PHONY: clean-Src-2f-CJSON

