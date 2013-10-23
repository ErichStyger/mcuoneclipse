%-Standard test file created by Bean Wizard 1.33
%if Language='ANSIC'
%if (CPUfamily = "Kinetis")
%else
  %error "this component is only supported for ARM/Kinetis!"
%endif %-(CPUfamily = "Kinetis")
%else %- Language (& Compiler)
  %error^ This component is not implemented in selected language & compiler !
%endif %- Language (& Compiler)
