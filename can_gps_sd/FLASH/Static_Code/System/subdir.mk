################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Static_Code/System/CPU_Init.c" \
"../Static_Code/System/Peripherals_Init.c" \
"../Static_Code/System/Vectors.c" \

C_SRCS += \
../Static_Code/System/CPU_Init.c \
../Static_Code/System/Peripherals_Init.c \
../Static_Code/System/Vectors.c \

OBJS += \
./Static_Code/System/CPU_Init.o \
./Static_Code/System/Peripherals_Init.o \
./Static_Code/System/Vectors.o \

C_DEPS += \
./Static_Code/System/CPU_Init.d \
./Static_Code/System/Peripherals_Init.d \
./Static_Code/System/Vectors.d \

OBJS_QUOTED += \
"./Static_Code/System/CPU_Init.o" \
"./Static_Code/System/Peripherals_Init.o" \
"./Static_Code/System/Vectors.o" \

C_DEPS_QUOTED += \
"./Static_Code/System/CPU_Init.d" \
"./Static_Code/System/Peripherals_Init.d" \
"./Static_Code/System/Vectors.d" \

OBJS_OS_FORMAT += \
./Static_Code/System/CPU_Init.o \
./Static_Code/System/Peripherals_Init.o \
./Static_Code/System/Vectors.o \


# Each subdirectory must supply rules for building sources it contributes
Static_Code/System/CPU_Init.o: ../Static_Code/System/CPU_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Static_Code/System/CPU_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Static_Code/System/CPU_Init.o"
	@echo 'Finished building: $<'
	@echo ' '

Static_Code/System/Peripherals_Init.o: ../Static_Code/System/Peripherals_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Static_Code/System/Peripherals_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Static_Code/System/Peripherals_Init.o"
	@echo 'Finished building: $<'
	@echo ' '

Static_Code/System/Vectors.o: ../Static_Code/System/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Static_Code/System/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Static_Code/System/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '


