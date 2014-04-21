%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ini_getbool)
%;**     Description :
%;**         Return a boolean key.  A true boolean is found if one of the
%;**         following is matched:
%;**         - A string starting with 'y' or 'Y'
%;**         - A string starting with 't' or 'T'
%;**         - A string starting with '1'
%;**         A false boolean is found if one of the following is matched:
%;**         - A string starting with 'n' or 'N'
%;**         - A string starting with 'f' or 'F'
%;**         - A string starting with '0'
%include Common\GeneralParameters.inc(27)
%;**       * Section%ParSection %>27 - The name of the section to search
%;** %>29 for
%;**       * Key%ParKey %>27 - The name of the entry to find the value of
%;**         DefValue%ParDefValue %>27 - Default value in the event of a
%;** %>29 failed read; it should be zero (0) or one
%;** %>29 (1).
%;**       * Filename%ParFilename %>27 - The name and full path of the .
%;** %>29 ini file to read from
%;**     Returns     :
%;**         ---%RetVal %>27 - The true/false flag as interpreted at Key
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine