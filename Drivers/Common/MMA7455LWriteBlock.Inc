%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteBlock)
%;**     Description :
%;**         Writes multiple bytes to the sensor (max 10)
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - First address in device where to write
%;**       * buf%Parbuf %>27 - Pointer to where the bytes to write are
%;** %>29 stored
%;**         bufSize%ParbufSize %>27 - Number of bytes to write
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
