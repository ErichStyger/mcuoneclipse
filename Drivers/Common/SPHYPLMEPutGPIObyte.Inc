%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PLMEPutGPIObyte)
%;**     Description :
%;**         Returns a data byte for GPIOs which are configured as output.
%include Common\GeneralParameters.inc(27)
%;**         data%Pardata %>27 - The data to be written, organized as
%;** %>29 bits in the same order as the I/O ports.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine