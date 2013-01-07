%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetPixel)
%;**     Description :
%;**         Clears a pixel in the display buffer
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - Pixel x position
%;**         y%Pary %>27 - Pixel y position
%;**     Returns     :
%;**         ---%RetVal %>27 - Pixel value
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine