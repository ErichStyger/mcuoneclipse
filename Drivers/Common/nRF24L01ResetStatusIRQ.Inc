%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ResetStatusIRQ)
%;**     Description :
%;**         Reset the given flags mask of status bits
%include Common\GeneralParameters.inc(27)
%;**         flags%Parflags %>27 - Flags, one or more of
%;** %>29 RF24_STATUS_RX_DR, RF24_STATUS_TX_DS,
%;** %>29 RF24_STATUS_MAX_RT
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine