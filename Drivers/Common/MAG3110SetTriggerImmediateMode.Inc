%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetTriggerImmediateMode)
%;**     Description :
%;**         Turns the TM (Trigger Immediate Measurement) bit in
%;**         CTRL_REG_1 on or off
%include Common\GeneralParameters.inc(27)
%;**         on%Paron %>27 - if to turn the TM mode on or off
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine