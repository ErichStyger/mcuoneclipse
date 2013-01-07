%-Standard test file created by Bean Wizard 1.26
%if Language='ANSIC'
%else %- Language (& Compiler)
  %error^ This bean is not implemented in selected language & compiler !
%endif %- Language (& Compiler)

%if %LCD_Nof_Lines > "2"
  %error only up to 2 LCD lines are supported!
%endif
