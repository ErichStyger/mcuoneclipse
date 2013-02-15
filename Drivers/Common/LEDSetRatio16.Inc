%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetRatio16)
%;**     Description :
%;**         Method to specify the duty cycle. If using a PWM pin, this
%;**         means the duty cycle is set. For On/off pins, values smaller
%;**         0x7FFF means off, while values greater means on.
%include Common\GeneralParameters.inc(27)
%;**         ratio%Parratio %>27 - Ratio value, where 0 means 'off' and
%;** %>29 0xffff means 'on'
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine