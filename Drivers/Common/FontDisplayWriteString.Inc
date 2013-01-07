%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteString)
%;**     Description :
%;**         Function to write a string or character at the startpoint.
%;**         Set the startpoint with the function setCursor.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to the character string
%;**         color%Parcolor %>27 - Foreground color to be used (for the
%;** %>29 character pixels)
%;**       * xCursor%ParxCursor %>27 - Pointer to x position of first
%;** %>29 character (upper left corner). On return
%;** %>29 this will contain the next y position.
%;**       * yCursor%ParyCursor %>27 - Pointer to y position of character
%;** %>29 (upper left corner). On return this will
%;** %>29 contain the next y position.
%;**       * font%Parfont %>27 - Pointer to font information
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine