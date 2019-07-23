################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/COMM/CAN.c" \

C_SRCS += \
../Sources/COMM/CAN.c \

OBJS += \
./Sources/COMM/CAN_c.obj \

OBJS_QUOTED += \
"./Sources/COMM/CAN_c.obj" \

C_DEPS += \
./Sources/COMM/CAN_c.d \

C_DEPS_QUOTED += \
"./Sources/COMM/CAN_c.d" \

OBJS_OS_FORMAT += \
./Sources/COMM/CAN_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/COMM/CAN_c.obj: ../Sources/COMM/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/COMM/CAN.args" -o "Sources/COMM/CAN_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/COMM/%.d: ../Sources/COMM/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


