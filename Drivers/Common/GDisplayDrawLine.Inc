%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (DrawLine)
%;**     Description :
%;**         Draws a line using the Bresenham method
%include Common\GeneralParameters.inc(27)
%;**         xstart%Parxstart %>27 - x start coordinate
%;**         ystart%Parystart %>27 - y start coordinate
%;**         xend%Parxend %>27 - x end coordinate
%;**         yend%Paryend %>27 - y end coordinate
%;**         color%Parcolor %>27 - color to be used for the line
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine