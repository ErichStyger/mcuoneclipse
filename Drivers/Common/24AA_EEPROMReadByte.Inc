%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadByte)
%;**     Description :
%;**         Reads a single byte from the given memory address
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - The address where to read from memory.
%;**       * data%Pardata %>27 - Pointer to a location where to store the
%;** %>29 data
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