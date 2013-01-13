%-Standard test file created by Bean Wizard 1.28
%if Language='ANSIC'
%else %- Language (& Compiler)
  %error^ This bean is not implemented in selected language & compiler !
%endif %- Language (& Compiler)
%if %NofBytesInKey <. %ReqNofBytesInKey
  %error Not enough bytes in key. Required are %ReqNofBytesInKey bytes.
%endif
