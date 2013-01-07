%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (DrawLine)
%;**     Description :
%;**         Paints a line into the element
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to widget
%;**         x0%Parx0 %>27 - x position, relative to window
%;**         y0%Pary0 %>27 - y position, relative to window
%;**         x1%Parx1 %>27 - lower right corner x coordinate
%;**         y1%Pary1 %>27 - lower right corner y coordinate
%;**         color%Parcolor %>27 - color to be used
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
