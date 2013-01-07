%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetRecoveryThroughReset)
%;**     Description :
%;**         Called in case we were going through reset because of low
%;**         power recovery.
%include Common\GeneralParameters.inc(27)
%;**         value%Parvalue %>27 - the value to be set
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine