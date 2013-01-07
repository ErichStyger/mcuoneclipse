%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteReg)
%;**     Description :
%;**         Writes data starting from a register address to the current
%;**         device
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address in device
%;**       * data%Pardata %>27 - Pointer to data to write
%;**         dataSize%PardataSize %>27 - Size of data in bytes
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine