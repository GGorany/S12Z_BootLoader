################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Driver/EEPROM_Control.c" \
"../Sources/Driver/EEPROM_S12Z.c" \
"../Sources/Driver/FLASH_Control.c" \
"../Sources/Driver/FLASH_S12Z.c" \
"../Sources/Driver/S_Record.c" \

C_SRCS += \
../Sources/Driver/EEPROM_Control.c \
../Sources/Driver/EEPROM_S12Z.c \
../Sources/Driver/FLASH_Control.c \
../Sources/Driver/FLASH_S12Z.c \
../Sources/Driver/S_Record.c \

OBJS += \
./Sources/Driver/EEPROM_Control_c.obj \
./Sources/Driver/EEPROM_S12Z_c.obj \
./Sources/Driver/FLASH_Control_c.obj \
./Sources/Driver/FLASH_S12Z_c.obj \
./Sources/Driver/S_Record_c.obj \

OBJS_QUOTED += \
"./Sources/Driver/EEPROM_Control_c.obj" \
"./Sources/Driver/EEPROM_S12Z_c.obj" \
"./Sources/Driver/FLASH_Control_c.obj" \
"./Sources/Driver/FLASH_S12Z_c.obj" \
"./Sources/Driver/S_Record_c.obj" \

C_DEPS += \
./Sources/Driver/EEPROM_Control_c.d \
./Sources/Driver/EEPROM_S12Z_c.d \
./Sources/Driver/FLASH_Control_c.d \
./Sources/Driver/FLASH_S12Z_c.d \
./Sources/Driver/S_Record_c.d \

C_DEPS_QUOTED += \
"./Sources/Driver/EEPROM_Control_c.d" \
"./Sources/Driver/EEPROM_S12Z_c.d" \
"./Sources/Driver/FLASH_Control_c.d" \
"./Sources/Driver/FLASH_S12Z_c.d" \
"./Sources/Driver/S_Record_c.d" \

OBJS_OS_FORMAT += \
./Sources/Driver/EEPROM_Control_c.obj \
./Sources/Driver/EEPROM_S12Z_c.obj \
./Sources/Driver/FLASH_Control_c.obj \
./Sources/Driver/FLASH_S12Z_c.obj \
./Sources/Driver/S_Record_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Driver/EEPROM_Control_c.obj: ../Sources/Driver/EEPROM_Control.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Driver/EEPROM_Control.args" -o "Sources/Driver/EEPROM_Control_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/%.d: ../Sources/Driver/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Driver/EEPROM_S12Z_c.obj: ../Sources/Driver/EEPROM_S12Z.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Driver/EEPROM_S12Z.args" -o "Sources/Driver/EEPROM_S12Z_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/FLASH_Control_c.obj: ../Sources/Driver/FLASH_Control.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Driver/FLASH_Control.args" -o "Sources/Driver/FLASH_Control_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/FLASH_S12Z_c.obj: ../Sources/Driver/FLASH_S12Z.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Driver/FLASH_S12Z.args" -o "Sources/Driver/FLASH_S12Z_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Driver/S_Record_c.obj: ../Sources/Driver/S_Record.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Driver/S_Record.args" -o "Sources/Driver/S_Record_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


