%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (StopSafeReverseBias)
%;**     Description :
%;**         Reverts the port status back to previous mode.
%include Common\GeneralParameters.inc(27)
%;**       * portBackup%ParportBackup %>27 - Pointer to backup structure
%;** %>29 for port status.  It points to a
%;** %>29 %%'ModuleName'%%.PortStatus structure to be
%;** %>29 allocated by the caller.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine