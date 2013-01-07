%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (DrawColorBitmap)
%;**     Description :
%;**         Draws a color bitmap. Pixel data is in 3-3-2 RGB format.
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - x position of left upper corner
%;**         y%Pary %>27 - y position of left upper corner
%;**         image%Parimage %>27 - Pointer to image structure and
%;** %>29 information.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine