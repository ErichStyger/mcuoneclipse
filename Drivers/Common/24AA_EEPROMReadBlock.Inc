%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadBlock)
%;**     Description :
%;**         Read a block of memory.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address where to read the memory
%;**       * data%Pardata %>27 - Pointer to a buffer where to store the
%;** %>29 data
%;**         dataSize%PardataSize %>27 - Size of buffer the data pointer
%;** %>29 is pointing to
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