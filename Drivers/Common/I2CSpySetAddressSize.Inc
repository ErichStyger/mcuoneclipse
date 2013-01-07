%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetAddressSize)
%;**     Description :
%;**         Specifies the address size of the I2C device memory
%include Common\GeneralParameters.inc(27)
%;**         size%Parsize %>27 - Either 1 (8bit), 2 (16bit), 3 (24bit),
%;** %>29 or 4 (32bit)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine