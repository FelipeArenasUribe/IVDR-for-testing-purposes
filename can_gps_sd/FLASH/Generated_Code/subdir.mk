################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/CS1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/FAT1.c" \
"../Generated_Code/KSDK1.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/SD1.c" \
"../Generated_Code/SM1.c" \
"../Generated_Code/SS1.c" \
"../Generated_Code/TMOUT1.c" \
"../Generated_Code/TmDt1.c" \
"../Generated_Code/UTIL1.c" \
"../Generated_Code/WAIT1.c" \
"../Generated_Code/ff.c" \

C_SRCS += \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/FAT1.c \
../Generated_Code/KSDK1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SD1.c \
../Generated_Code/SM1.c \
../Generated_Code/SS1.c \
../Generated_Code/TMOUT1.c \
../Generated_Code/TmDt1.c \
../Generated_Code/UTIL1.c \
../Generated_Code/WAIT1.c \
../Generated_Code/ff.c \

OBJS += \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/FAT1.o \
./Generated_Code/KSDK1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SD1.o \
./Generated_Code/SM1.o \
./Generated_Code/SS1.o \
./Generated_Code/TMOUT1.o \
./Generated_Code/TmDt1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/WAIT1.o \
./Generated_Code/ff.o \

C_DEPS += \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/FAT1.d \
./Generated_Code/KSDK1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SD1.d \
./Generated_Code/SM1.d \
./Generated_Code/SS1.d \
./Generated_Code/TMOUT1.d \
./Generated_Code/TmDt1.d \
./Generated_Code/UTIL1.d \
./Generated_Code/WAIT1.d \
./Generated_Code/ff.d \

OBJS_QUOTED += \
"./Generated_Code/CS1.o" \
"./Generated_Code/Cpu.o" \
"./Generated_Code/FAT1.o" \
"./Generated_Code/KSDK1.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/SD1.o" \
"./Generated_Code/SM1.o" \
"./Generated_Code/SS1.o" \
"./Generated_Code/TMOUT1.o" \
"./Generated_Code/TmDt1.o" \
"./Generated_Code/UTIL1.o" \
"./Generated_Code/WAIT1.o" \
"./Generated_Code/ff.o" \

C_DEPS_QUOTED += \
"./Generated_Code/CS1.d" \
"./Generated_Code/Cpu.d" \
"./Generated_Code/FAT1.d" \
"./Generated_Code/KSDK1.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/SD1.d" \
"./Generated_Code/SM1.d" \
"./Generated_Code/SS1.d" \
"./Generated_Code/TMOUT1.d" \
"./Generated_Code/TmDt1.d" \
"./Generated_Code/UTIL1.d" \
"./Generated_Code/WAIT1.d" \
"./Generated_Code/ff.d" \

OBJS_OS_FORMAT += \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/FAT1.o \
./Generated_Code/KSDK1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SD1.o \
./Generated_Code/SM1.o \
./Generated_Code/SS1.o \
./Generated_Code/TMOUT1.o \
./Generated_Code/TmDt1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/WAIT1.o \
./Generated_Code/ff.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/CS1.o: ../Generated_Code/CS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/FAT1.o: ../Generated_Code/FAT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/FAT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/FAT1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/KSDK1.o: ../Generated_Code/KSDK1.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/KSDK1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/KSDK1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SD1.o: ../Generated_Code/SD1.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SD1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SD1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SM1.o: ../Generated_Code/SM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SM1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SM1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SS1.o: ../Generated_Code/SS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/SS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/SS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TMOUT1.o: ../Generated_Code/TMOUT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TMOUT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TMOUT1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TmDt1.o: ../Generated_Code/TmDt1.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TmDt1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TmDt1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/UTIL1.o: ../Generated_Code/UTIL1.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/UTIL1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/UTIL1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/WAIT1.o: ../Generated_Code/WAIT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/WAIT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/WAIT1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ff.o: ../Generated_Code/ff.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ff.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ff.o"
	@echo 'Finished building: $<'
	@echo ' '


