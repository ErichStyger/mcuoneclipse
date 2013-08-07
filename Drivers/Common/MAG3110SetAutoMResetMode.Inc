%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetAutoMResetMode)
%;**     Description :
%;**         Turns the AUTO_MRST_EN (Automatic Magnetic Sensor Reset) bit
%;**         in CTRL_REG_2 on or off
%include Common\GeneralParameters.inc(27)
%;**         on%Paron %>27 - if to turn the AUTO_MRST_EN mode on or off
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine