%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ini_getf)
%;**     Description :
%;**         Return the long integral value for a given section and key.
%include Common\GeneralParameters.inc(27)
%;**       * Section%ParSection %>27 - The name of the section to search
%;** %>29 for
%;**       * Key%ParKey %>27 - Pointer to the name of the entry to find
%;** %>29 the value of
%;**         DefValue%ParDefValue %>27 - Default value in the event of a
%;** %>29 failed read
%;**       * Filename%ParFilename %>27 - The name and full path of the .
%;** %>29 ini file to read from
%;**     Returns     :
%;**         ---%RetVal %>27 - The value located at Key
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine