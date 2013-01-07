%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (UpdateRegion)
%;**     Description :
%;**         Update a region of the display.
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - x coordinate
%;**         y%Pary %>27 - y coordinate
%;**         w%Parw %>27 - Width of the update region
%;**         h%Parh %>27 - height of the update region
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine