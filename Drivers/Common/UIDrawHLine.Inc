%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (DrawHLine)
%;**     Description :
%;**         Paints a horizontal line in the element
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to widget
%;**         x%Parx %>27 - x position, relative to window
%;**         y%Pary %>27 - y position, relative to window
%;**         w%Parw %>27 - width of line
%;**         color%Parcolor %>27 - color to be used
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
