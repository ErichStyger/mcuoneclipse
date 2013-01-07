%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteByte)
%;**     Description :
%;**         Writes a single byte to the sensor
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address in device where to write
%;**       * val%Parval %>27 - Pointer to where the byte to write is
%;** %>29 stored
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
