%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteReg)
%;**     Description :
%;**         Writes to a device register address
%include Common\GeneralParameters.inc(27)
%;**         reg%Parreg %>27 - register address
%;**         val%Parval %>27 - Value to write
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine