################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MCU/EEPROM_S12Z.c" \
"../Sources/MCU/MCU_SYSTEM.c" \

C_SRCS += \
../Sources/MCU/EEPROM_S12Z.c \
../Sources/MCU/MCU_SYSTEM.c \

OBJS += \
./Sources/MCU/EEPROM_S12Z_c.obj \
./Sources/MCU/MCU_SYSTEM_c.obj \

OBJS_QUOTED += \
"./Sources/MCU/EEPROM_S12Z_c.obj" \
"./Sources/MCU/MCU_SYSTEM_c.obj" \

C_DEPS += \
./Sources/MCU/EEPROM_S12Z_c.d \
./Sources/MCU/MCU_SYSTEM_c.d \

C_DEPS_QUOTED += \
"./Sources/MCU/EEPROM_S12Z_c.d" \
"./Sources/MCU/MCU_SYSTEM_c.d" \

OBJS_OS_FORMAT += \
./Sources/MCU/EEPROM_S12Z_c.obj \
./Sources/MCU/MCU_SYSTEM_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU/EEPROM_S12Z_c.obj: ../Sources/MCU/EEPROM_S12Z.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/MCU/EEPROM_S12Z.args" -o "Sources/MCU/EEPROM_S12Z_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCU/%.d: ../Sources/MCU/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/MCU/MCU_SYSTEM_c.obj: ../Sources/MCU/MCU_SYSTEM.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/MCU/MCU_SYSTEM.args" -o "Sources/MCU/MCU_SYSTEM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


