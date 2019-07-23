################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/starts12z.c" \

C_SRCS += \
../Project_Settings/Startup_Code/starts12z.c \

OBJS += \
./Project_Settings/Startup_Code/starts12z_c.obj \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/starts12z_c.obj" \

C_DEPS += \
./Project_Settings/Startup_Code/starts12z_c.d \

C_DEPS_QUOTED += \
"./Project_Settings/Startup_Code/starts12z_c.d" \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/starts12z_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/starts12z_c.obj: ../Project_Settings/Startup_Code/starts12z.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Project_Settings/Startup_Code/starts12z.args" -o "Project_Settings/Startup_Code/starts12z_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/starts12z_c.d: ../Project_Settings/Startup_Code/starts12z.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


