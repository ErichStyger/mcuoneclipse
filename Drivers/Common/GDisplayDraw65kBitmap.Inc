%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Draw65kBitmap)
%;**     Description :
%;**         Draws a 65k color bitmap (compressed or uncompressed)
%include Common\GeneralParameters.inc(27)
%;**         x1%Parx1 %>27 - left upper starting corner
%;**         y1%Pary1 %>27 - left upper starting corner
%;**         x2%Parx2 %>27 - right lower corner
%;**         y2%Pary2 %>27 - right lower corner
%;**       * bmp%Parbmp %>27 - Pointer to bitmap
%;**         compressed%Parcompressed %>27 - 
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine