################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/CANComm.c" \
"../Generated_Code/CANPHY0.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/IO_Map.c" \
"../Generated_Code/LED_GR.c" \
"../Generated_Code/LED_ORG.c" \
"../Generated_Code/LED_RED.c" \
"../Generated_Code/LED_YEL.c" \
"../Generated_Code/Timer_1ms.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/CANComm.c \
../Generated_Code/CANPHY0.c \
../Generated_Code/Cpu.c \
../Generated_Code/IO_Map.c \
../Generated_Code/LED_GR.c \
../Generated_Code/LED_ORG.c \
../Generated_Code/LED_RED.c \
../Generated_Code/LED_YEL.c \
../Generated_Code/Timer_1ms.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/CANComm_c.obj \
./Generated_Code/CANPHY0_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/LED_GR_c.obj \
./Generated_Code/LED_ORG_c.obj \
./Generated_Code/LED_RED_c.obj \
./Generated_Code/LED_YEL_c.obj \
./Generated_Code/Timer_1ms_c.obj \
./Generated_Code/Vectors_c.obj \

OBJS_QUOTED += \
"./Generated_Code/CANComm_c.obj" \
"./Generated_Code/CANPHY0_c.obj" \
"./Generated_Code/Cpu_c.obj" \
"./Generated_Code/IO_Map_c.obj" \
"./Generated_Code/LED_GR_c.obj" \
"./Generated_Code/LED_ORG_c.obj" \
"./Generated_Code/LED_RED_c.obj" \
"./Generated_Code/LED_YEL_c.obj" \
"./Generated_Code/Timer_1ms_c.obj" \
"./Generated_Code/Vectors_c.obj" \

C_DEPS += \
./Generated_Code/CANComm_c.d \
./Generated_Code/CANPHY0_c.d \
./Generated_Code/Cpu_c.d \
./Generated_Code/IO_Map_c.d \
./Generated_Code/LED_GR_c.d \
./Generated_Code/LED_ORG_c.d \
./Generated_Code/LED_RED_c.d \
./Generated_Code/LED_YEL_c.d \
./Generated_Code/Timer_1ms_c.d \
./Generated_Code/Vectors_c.d \

C_DEPS_QUOTED += \
"./Generated_Code/CANComm_c.d" \
"./Generated_Code/CANPHY0_c.d" \
"./Generated_Code/Cpu_c.d" \
"./Generated_Code/IO_Map_c.d" \
"./Generated_Code/LED_GR_c.d" \
"./Generated_Code/LED_ORG_c.d" \
"./Generated_Code/LED_RED_c.d" \
"./Generated_Code/LED_YEL_c.d" \
"./Generated_Code/Timer_1ms_c.d" \
"./Generated_Code/Vectors_c.d" \

OBJS_OS_FORMAT += \
./Generated_Code/CANComm_c.obj \
./Generated_Code/CANPHY0_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/LED_GR_c.obj \
./Generated_Code/LED_ORG_c.obj \
./Generated_Code/LED_RED_c.obj \
./Generated_Code/LED_YEL_c.obj \
./Generated_Code/Timer_1ms_c.obj \
./Generated_Code/Vectors_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/CANComm_c.obj: ../Generated_Code/CANComm.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/CANComm.args" -o "Generated_Code/CANComm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Generated_Code/CANPHY0_c.obj: ../Generated_Code/CANPHY0.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/CANPHY0.args" -o "Generated_Code/CANPHY0_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu_c.obj: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/Cpu.args" -o "Generated_Code/Cpu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_Map_c.obj: ../Generated_Code/IO_Map.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/IO_Map.args" -o "Generated_Code/IO_Map_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_GR_c.obj: ../Generated_Code/LED_GR.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/LED_GR.args" -o "Generated_Code/LED_GR_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_ORG_c.obj: ../Generated_Code/LED_ORG.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/LED_ORG.args" -o "Generated_Code/LED_ORG_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_RED_c.obj: ../Generated_Code/LED_RED.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/LED_RED.args" -o "Generated_Code/LED_RED_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_YEL_c.obj: ../Generated_Code/LED_YEL.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/LED_YEL.args" -o "Generated_Code/LED_YEL_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Timer_1ms_c.obj: ../Generated_Code/Timer_1ms.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/Timer_1ms.args" -o "Generated_Code/Timer_1ms_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors_c.obj: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Generated_Code/Vectors.args" -o "Generated_Code/Vectors_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


