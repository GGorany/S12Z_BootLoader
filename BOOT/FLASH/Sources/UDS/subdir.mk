################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/UDS/network_layer.c" \
"../Sources/UDS/uds_service.c" \
"../Sources/UDS/uds_status.c" \
"../Sources/UDS/uds_support.c" \
"../Sources/UDS/uds_util.c" \

C_SRCS += \
../Sources/UDS/network_layer.c \
../Sources/UDS/uds_service.c \
../Sources/UDS/uds_status.c \
../Sources/UDS/uds_support.c \
../Sources/UDS/uds_util.c \

OBJS += \
./Sources/UDS/network_layer_c.obj \
./Sources/UDS/uds_service_c.obj \
./Sources/UDS/uds_status_c.obj \
./Sources/UDS/uds_support_c.obj \
./Sources/UDS/uds_util_c.obj \

OBJS_QUOTED += \
"./Sources/UDS/network_layer_c.obj" \
"./Sources/UDS/uds_service_c.obj" \
"./Sources/UDS/uds_status_c.obj" \
"./Sources/UDS/uds_support_c.obj" \
"./Sources/UDS/uds_util_c.obj" \

C_DEPS += \
./Sources/UDS/network_layer_c.d \
./Sources/UDS/uds_service_c.d \
./Sources/UDS/uds_status_c.d \
./Sources/UDS/uds_support_c.d \
./Sources/UDS/uds_util_c.d \

C_DEPS_QUOTED += \
"./Sources/UDS/network_layer_c.d" \
"./Sources/UDS/uds_service_c.d" \
"./Sources/UDS/uds_status_c.d" \
"./Sources/UDS/uds_support_c.d" \
"./Sources/UDS/uds_util_c.d" \

OBJS_OS_FORMAT += \
./Sources/UDS/network_layer_c.obj \
./Sources/UDS/uds_service_c.obj \
./Sources/UDS/uds_status_c.obj \
./Sources/UDS/uds_support_c.obj \
./Sources/UDS/uds_util_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/UDS/network_layer_c.obj: ../Sources/UDS/network_layer.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/UDS/network_layer.args" -o "Sources/UDS/network_layer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/UDS/%.d: ../Sources/UDS/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/UDS/uds_service_c.obj: ../Sources/UDS/uds_service.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/UDS/uds_service.args" -o "Sources/UDS/uds_service_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/UDS/uds_status_c.obj: ../Sources/UDS/uds_status.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/UDS/uds_status.args" -o "Sources/UDS/uds_status_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/UDS/uds_support_c.obj: ../Sources/UDS/uds_support.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/UDS/uds_support.args" -o "Sources/UDS/uds_support_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/UDS/uds_util_c.obj: ../Sources/UDS/uds_util.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/UDS/uds_util.args" -o "Sources/UDS/uds_util_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


