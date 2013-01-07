%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteByte)
%;**     Description :
%;**         Writes a single byte to specified address
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - The address inside the EEPROM
%;**         data%Pardata %>27 - The data value to write
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible values
%;** %>29 ERR_OK - OK
%;** %>29 otherwise it can return an error code of
%;** %>29 the underlying communication protocol.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine