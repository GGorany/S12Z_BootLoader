################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/APPL/LED.c" \

C_SRCS += \
../Sources/APPL/LED.c \

OBJS += \
./Sources/APPL/LED_c.obj \

OBJS_QUOTED += \
"./Sources/APPL/LED_c.obj" \

C_DEPS += \
./Sources/APPL/LED_c.d \

C_DEPS_QUOTED += \
"./Sources/APPL/LED_c.d" \

OBJS_OS_FORMAT += \
./Sources/APPL/LED_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/APPL/LED_c.obj: ../Sources/APPL/LED.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/APPL/LED.args" -o "Sources/APPL/LED_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/APPL/%.d: ../Sources/APPL/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


