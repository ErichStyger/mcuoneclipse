%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteReg8)
%;**     Description :
%;**         Write an 8bit device register
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - device memory map address
%;**         val%Parval %>27 - value to write
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine