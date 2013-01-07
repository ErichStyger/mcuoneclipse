%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Box)
%;**     Description :
%;**         Draws a rectangle box (filled)
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - x left upper coordinate
%;**         y%Pary %>27 - y left upper coordinate
%;**         width%Parwidth %>27 - Widht in pixels
%;**         height%Parheight %>27 - Height in pixels
%;**         lineWidth%ParlineWidth %>27 - width of the line
%;**         color%Parcolor %>27 - 1 for setting pixels, 0 for clearing
%;** %>29 it.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine