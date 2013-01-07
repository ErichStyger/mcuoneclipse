%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteChar)
%;**     Description :
%;**         Function to write a character at the start point. Set the
%;**         start point with the function setCursor.
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - the character to print
%;**         color%Parcolor %>27 - Foreground color to be used (for the
%;** %>29 character pixels)
%;**       * xCursor%ParxCursor %>27 - Pointer to x position of character
%;** %>29 (upper left corner). On return this will
%;** %>29 contain the next x position.
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