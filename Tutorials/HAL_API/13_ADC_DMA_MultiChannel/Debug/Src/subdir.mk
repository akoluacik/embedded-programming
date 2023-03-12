################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/dma.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/dma.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/dma.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"D:/Codes/Embedded Programming/Tutorials/HAL_API/13_ADC_DMA_MultiChannel/Inc" -I"D:/Codes/Embedded Programming/Tutorials/HAL_API/13_ADC_DMA_MultiChannel/Drivers/CMSIS/Include" -I"D:/Codes/Embedded Programming/Tutorials/HAL_API/13_ADC_DMA_MultiChannel/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Codes/Embedded Programming/Tutorials/HAL_API/13_ADC_DMA_MultiChannel/Drivers/STM32F4xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/dma.d ./Src/dma.o ./Src/dma.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

