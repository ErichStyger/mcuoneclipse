%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (StartSafeReverseBias)
%;**     Description :
%;**         Puts the LEDs in reverse bias mode and starts discharing
%;**         (port set as input).
%include Common\GeneralParameters.inc(27)
%;**       * portBackup%ParportBackup %>27 - Pointer to backup structure
%;** %>29 for port status (to be restored later).  It
%;** %>29 points to a %%'ModuleName'%%.PortStatus
%;** %>29 structure to be allocated by the caller.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine