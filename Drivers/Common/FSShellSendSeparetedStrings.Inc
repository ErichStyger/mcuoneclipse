%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendSeparetedStrings)
%;**     Description :
%;**         Prints a string using an I/O function, formated for the
%;**         'help' command
%include Common\GeneralParameters.inc(27)
%;**       * strA%ParstrA %>27 - Pointer to first string
%;**       * strB%ParstrB %>27 - Pointer to second string
%;**         tabChar%PartabChar %>27 - Character to be used as separator
%;**         tabPos%PartabPos %>27 - Position of the tab character
%;**         io%Pario %>27 - I/O callbacks to be used for printing.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine