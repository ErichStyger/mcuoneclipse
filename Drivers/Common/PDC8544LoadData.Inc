%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (LoadData)
%;**     Description :
%;**         Loads an array of display data bytes to the display. The
%;**         array is representing the display bitmap.
%include Common\GeneralParameters.inc(27)
%;**         index%Parindex %>27 - Starting position/byte within image
%;** %>29 for data.
%;**         numBytes%ParnumBytes %>27 - Number of bytes of image data to
%;** %>29 load
%;**       * data%Pardata %>27 - Pointer to data
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine