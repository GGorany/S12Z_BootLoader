################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 18
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/MCU/subdir.mk
-include Sources/COMM/subdir.mk
-include Sources/APPL/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \

EXECUTABLES_QUOTED += \

EXECUTABLES_OS_FORMAT += \

BURNER_OUTPUT_OUTPUTS += \

BURNER_OUTPUT_OUTPUTS_QUOTED += \

BURNER_OUTPUT_OUTPUTS_OS_FORMAT += \


# All Target
all: warning-messages explicit-dependencies APP.elf

# Tool invocations
APP.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/ProcessorExpert.prm
	@echo 'Building target: $@'
	@echo 'Executing target #19 $@'
	@echo 'Invoking: S12Z Linker'
	"$(S12Z_ToolsDirEnv)/linker" -ArgFile"APP.args" -O"APP.elf"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

APP.elf.s19: $(BBL_SRCS) $(EXECUTABLES)
	@echo 'Executing target #20 $@'
	@echo 'Invoking: S12Z Burner'
	"$(S12Z_ToolsDirEnv)/burner" -Ns -ViewHidden -WmsgFob"%f%e:%l:%k:%d:%m\n" -f="$<" -env"ABS_FILE=$(strip $(EXECUTABLES_OS_FORMAT))"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*.obj" "./*/*/*.obj"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(BURNER_OUTPUT_OUTPUTS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d"  $(ProjDirPath)/FLASH/APP.elf
	-@echo ' '

post-build:
	-@echo 'Re-format S-record file'
	-C:/PC_DATA/My_Files/Project_personal/S12Z_BootLoader/APPLICATION/APP/SRecCvt/sreccvt.exe -hc12 -m 100000 FFFFFF 32 -o ..\FLASH\APP.s19 ..\FLASH\APP.sx
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY: post-build

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/ProcessorExpert.prm 

warning-messages: 

