%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteToLine)
%;**     Description :
%;**         Function to write a string or character at the startpoint.
%;**         Set the startpoint with the function setCursor.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to the character array
%;**         color%Parcolor %>27 - Foreground color to be used (for the
%;** %>29 character pixels)
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine