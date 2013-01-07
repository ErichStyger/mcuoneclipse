%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Bitmap)
%;**     Description :
%;**         Draws a bitmap.
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - x position of left upper corner
%;**         y%Pary %>27 - y position of left upper corner
%;**         width%Parwidth %>27 - width of bitmap in pixels
%;**         height%Parheight %>27 - height of bitmap in pixels
%;**       * data%Pardata %>27 - pointer to bitmap data (array of bits)
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine