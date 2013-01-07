%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadBlock)
%;**     Description :
%;**         Reads multiple bytes from the sensor
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - First address in device where to read
%;** %>29 from
%;**       * buf%Parbuf %>27 - Pointer to where to store the bytes read
%;**         bufSize%ParbufSize %>27 - Number of bytes to read
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
