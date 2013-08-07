%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetOversamplingMode)
%;**     Description :
%;**         Sets the OS (oversampling selection) bits in the CTRL_REG_1
%;**         register.
%include Common\GeneralParameters.inc(27)
%;**         bits%Parbits %>27 - Oversampling mode, one of
%;** %>29 CTRL_REG_1_OS_xxxHZ_BIT_MASK
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine