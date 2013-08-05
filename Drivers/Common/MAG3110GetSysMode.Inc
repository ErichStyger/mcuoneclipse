%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetSysMode)
%;**     Description :
%;**         Returns the SYSMOD (0x08) status
%include Common\GeneralParameters.inc(27)
%;**       * mode%Parmode %>27 - Pointer to where to store the value.
%;** %>29 Returns 0x00 (STANDBY), 0x01 (ACTIVE, raw
%;** %>29 data) or 0x02 (ACTIVE, non-RAW data)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine