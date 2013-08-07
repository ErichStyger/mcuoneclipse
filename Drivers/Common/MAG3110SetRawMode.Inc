%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetRawMode)
%;**     Description :
%;**         Turns the RAW (Raw or data output correction) bit in
%;**         CTRL_REG_2 on or off
%include Common\GeneralParameters.inc(27)
%;**         on%Paron %>27 - if to turn the RAW mode on or off
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine