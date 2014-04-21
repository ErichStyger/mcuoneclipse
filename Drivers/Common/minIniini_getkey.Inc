%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ini_getkey)
%;**     Description :
%;**         Return the key inside a section
%include Common\GeneralParameters.inc(27)
%;**       * Section%ParSection %>27 - The name of the section to browse
%;** %>29 through, or NULL to browse through the keys
%;** %>29 outside any section
%;**         idx%Paridx %>27 - The zero-based sequence number of the key
%;** %>29 to return
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