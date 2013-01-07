%-Standard test file created by Bean Wizard 1.31
%if (%Compiler = "CodeWarriorColdFireV1") | (%Compiler = "CodeWarriorMCF")
%elif %Compiler = "CodeWarriorRS08CC"
%elif %Compiler = "MetrowerksHC08CC"
%elif %Compiler = "MetrowerksHCS08CC"
%elif %Compiler = "MetrowerksHC12CC"
%elif %Compiler = "MetrowerksHC12XCC"
%else
  %warning "Unknown compiler %Compiler"
%endif
