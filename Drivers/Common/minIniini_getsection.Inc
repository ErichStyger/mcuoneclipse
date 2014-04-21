%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ini_getsection)
%;**     Description :
%;**         Return the key inside a section
%include Common\GeneralParameters.inc(27)
%;**         idx%Paridx %>27 - The zero-based sequence number of the
%;** %>29 section to return
%;**       * Buffer%ParBuffer %>27 - A pointer to the buffer to copy into
%;**         BufferSize%ParBufferSize %>27 - The maximum number of
%;** %>29 characters to copy
%;**       * Filename%ParFilename %>27 - The name and full path of the .
%;** %>29 ini file to read from
%;**     Returns     :
%;**         ---%RetVal %>27 - The number of characters copied into the
%;** %>29 supplied buffer
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine