%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteBlock)
%;**     Description :
%;**         Writes a block of data to the EEPROM
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address of memory
%;**       * data%Pardata %>27 - Pointer to the data
%;**         dataSize%PardataSize %>27 - Size of data
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible values
%;** %>29 ERR_OK - OK
%;** %>29 ERR_OVERFLOW - data block passed has either
%;** %>29 size of zero or exceeds internal buffer
%;** %>29 size
%;** %>29 otherwise it can return an error code of
%;** %>29 the underlying communication protocol.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine