%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (UpdateRegion)
%;**     Description :
%;**         Updates a region of the display. This is only a stub for
%;**         this display as we are using windowing.
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - x coordinate
%;**         y%Pary %>27 - y coordinate
%;**         w%Parw %>27 - width of the region
%;**         h%Parh %>27 - Height of the region
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine