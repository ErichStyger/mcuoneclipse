%--------------------------------------------------------------------
%- Common support file
%-
%- Parameters:     - none
%- Defined symbols:
%-      - CPU_FAMILY – Alias to CPUfamily macro
%-      - COMPILER_MW - Defined for Metrowerks compilers
%-      - COMPILER_HIX - Defined for HIWARE compilers
%-      - CTAB - Setting of tab position in source code for comments
%-
%define CPU_FAMILY %CPUfamily
%-
%if (%Compiler = "CodeWarriorColdFireV1") | (%Compiler = "CodeWarriorMCF") | (%Compiler = "CodeWarriorARM") | (%Compiler = "MetrowerksDSP")
  %define COMPILER_MW
%elif %Compiler = "CodeWarriorRS08CC"
%elif %Compiler = "MetrowerksHC08CC"
%elif %Compiler = "MetrowerksHCS08CC"
%elif %Compiler = "MetrowerksHC12CC"
%elif %Compiler = "MetrowerksHC12XCC"
%elif %Compiler = "IARARM"
%elif %Compiler = "GNUC"
%elif %Compiler = "ARM_CC" %- ARM Keil compiler
%else
  %warning "Unknown compiler %Compiler"
%endif
%if (CPU_FAMILY = "HCS08") | (CPU_FAMILY = "HC08") | (CPU_FAMILY = "RS08")  | (CPU_FAMILY = "HCS12X") | (CPU_FAMILY = "HCS12")
  %- define a macro for the HIWARE/8/16bit compiler
  %define COMPILER_HIX
%endif
%-
%- **********************************************************************
%- Macros for formatting
%- **********************************************************************
%- default comment tab position
%define CTAB 45