%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ini_gets)
%;**     Description :
%;**         Return the string for a given section and key.
%include Common\GeneralParameters.inc(27)
%;**       * Section%ParSection %>27 - The name of the section to search
%;** %>29 for
%;**       * Key%ParKey %>27 - Pointer to the name of the entry to find
%;** %>29 the value of
%;**       * DefValue%ParDefValue %>27 - Pointer to the default value in
%;** %>29 the event of a failed read
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