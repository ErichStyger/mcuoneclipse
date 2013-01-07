%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadReg)
%;**     Description :
%;**         Reads data starting from a register address from the current
%;**         device
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Device address
%;**       * data%Pardata %>27 - Pointer to data buffer where read data
%;** %>29 is stored
%;**         dataSize%PardataSize %>27 - size of data buffer in bytes
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine