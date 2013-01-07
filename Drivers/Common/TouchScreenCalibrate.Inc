%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Calibrate)
%;**     Description :
%;**         Calibrates the screen. It asks the user to touch the screen
%;**         to calculate the calibration data.
%include Common\GeneralParameters.inc(27)
%;**         fgColor%ParfgColor %>27 - color to be used for the display
%;** %>29 foreground
%;**         bgColor%ParbgColor %>27 - color to be used for the
%;** %>29 background color
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine