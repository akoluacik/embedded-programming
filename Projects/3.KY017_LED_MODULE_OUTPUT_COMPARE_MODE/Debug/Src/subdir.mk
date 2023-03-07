################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/TIMx.c \
../Src/ky017ledmodule_config.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/TIMx.o \
./Src/ky017ledmodule_config.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/TIMx.d \
./Src/ky017ledmodule_config.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411xE -DUSE_HAL_DRIVER -c -I../Inc -I"D:/Codes/Embedded Programming/Projects/3.KY017_LED_MODULE_OUTPUT_COMPARE_MODE/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Codes/Embedded Programming/Projects/3.KY017_LED_MODULE_OUTPUT_COMPARE_MODE/Drivers/CMSIS/Include" -I"D:/Codes/Embedded Programming/Projects/3.KY017_LED_MODULE_OUTPUT_COMPARE_MODE/Drivers/STM32F4xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/TIMx.d ./Src/TIMx.o ./Src/TIMx.su ./Src/ky017ledmodule_config.d ./Src/ky017ledmodule_config.o ./Src/ky017ledmodule_config.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

