%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ini_putl)
%;**     Description :
%;**         Writes a long integral value for a given section and key.
%;**         Method is only enabled if 'Read only' is set to  'no' in the
%;**         properties.
%include Common\GeneralParameters.inc(27)
%;**       * Section%ParSection %>27 - The name of the section to write
%;** %>29 the value in
%;**       * Key%ParKey %>27 - The name of the entry to write
%;**         Value%ParValue %>27 - The value to write
%;**       * Filename%ParFilename %>27 - The name and full path of the .
%;** %>29 ini file to write to
%;**     Returns     :
%;**         ---%RetVal %>27 - 1 if successful, otherwise 0
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine