%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetSysMode)
%;**     Description :
%;**         Sets the SYSMOD (0x08) status register
%include Common\GeneralParameters.inc(27)
%;**         mode%Parmode %>27 - Set the system mode. 0x00
%;** %>29 (SYSMOD_STANDBY_BIT_MASK), 0x01
%;** %>29 (SYSMOD_ACTIVE_RAW_BIT_MASK) or 0x02
%;** %>29 (SYSMOD_ACTIVE_BIT_MASK)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine