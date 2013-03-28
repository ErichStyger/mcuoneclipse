%-Standard test file created by Bean Wizard 1.28
%ifdef Timer
%endif %- Timer
%if Language='ANSIC'
%if %CPUconfiguration='yes'

%if (CPUfamily = "HCS08") | (CPUfamily = "HC08") | (CPUfamily = "HCS12") | (CPUfamily = "HCS12X")
  %if (OS_CRITICAL_METHOD='2')
    %error "Method 2 is not implemented. Use method 1 or 3."
  %endif
%elif(CPUfamily = "ColdFireV1") | (CPUfamily = "MCF")
  %if (OS_CRITICAL_METHOD='1') | (OS_CRITICAL_METHOD='2')
    %error "Only method 3 is implemented"
  %endif
%else
  %error "CPU family %CPUfamily not supported!"
%endif
%endif %- %CPUconfiguration='yes'
%else %- Language (& Compiler)
  %error^ This component is not implemented in selected language & compiler !
%endif %- Language (& Compiler)
%hint This component includes the uC/OS-II RTOS sources. No licensing is required for uC/OS-II in educational use. Contact Micrium (www.micrium.com) for proper license to use uC/OS-II in commercial products.
