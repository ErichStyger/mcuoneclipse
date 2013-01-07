%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadByte)
%;**     Description :
%;**         Reads a single byte from the sensor
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address in device where to read from
%;**       * val%Parval %>27 - Pointer to where to store the byte read
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
