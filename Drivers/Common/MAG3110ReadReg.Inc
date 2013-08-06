%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadReg)
%;**     Description :
%;**         Reads from a device register address
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Device register address
%;**       * val%Parval %>27 - Pointer to where to store the value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine