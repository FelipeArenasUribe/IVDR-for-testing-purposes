################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/GPIO.c" \
"../Sources/MSCAN.c" \
"../Sources/PIT.c" \
"../Sources/UART.c" \
"../Sources/main.c" \
"../Sources/mcu.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/GPIO.c \
../Sources/MSCAN.c \
../Sources/PIT.c \
../Sources/UART.c \
../Sources/main.c \
../Sources/mcu.c \

OBJS += \
./Sources/Events.o \
./Sources/GPIO.o \
./Sources/MSCAN.o \
./Sources/PIT.o \
./Sources/UART.o \
./Sources/main.o \
./Sources/mcu.o \

C_DEPS += \
./Sources/Events.d \
./Sources/GPIO.d \
./Sources/MSCAN.d \
./Sources/PIT.d \
./Sources/UART.d \
./Sources/main.d \
./Sources/mcu.d \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/GPIO.o" \
"./Sources/MSCAN.o" \
"./Sources/PIT.o" \
"./Sources/UART.o" \
"./Sources/main.o" \
"./Sources/mcu.o" \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/GPIO.d" \
"./Sources/MSCAN.d" \
"./Sources/PIT.d" \
"./Sources/UART.d" \
"./Sources/main.d" \
"./Sources/mcu.d" \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/GPIO.o \
./Sources/MSCAN.o \
./Sources/PIT.o \
./Sources/UART.o \
./Sources/main.o \
./Sources/mcu.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/GPIO.o: ../Sources/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MSCAN.o: ../Sources/MSCAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/MSCAN.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/MSCAN.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PIT.o: ../Sources/PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PIT.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UART.o: ../Sources/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcu.o: ../Sources/mcu.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcu.o"
	@echo 'Finished building: $<'
	@echo ' '


