################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/src/ADC.c \
../driver/src/LCD.c \
../driver/src/gpio.c \
../driver/src/interrupt.c 

OBJS += \
./driver/src/ADC.o \
./driver/src/LCD.o \
./driver/src/gpio.o \
./driver/src/interrupt.o 

C_DEPS += \
./driver/src/ADC.d \
./driver/src/LCD.d \
./driver/src/gpio.d \
./driver/src/interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
driver/src/%.o: ../driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401CCUx -DDEBUG -DSTM32F401xx -I"H:/Studing/Year 3/Semester2/Electronics/lab/Final_Project/Final_Project/inc" -I"H:/Studing/Year 3/Semester2/Electronics/lab/Final_Project/Final_Project/driver/inc" -I"H:/Studing/Year 3/Semester2/Electronics/lab/Final_Project/Final_Project/CMSIS/device" -I"H:/Studing/Year 3/Semester2/Electronics/lab/Final_Project/Final_Project/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


