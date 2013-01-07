%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (StopSafeReverseBias)
%;**     Description :
%;**         Restores the port to its original settings using the saved
%;**         port state.
%include Common\GeneralParameters.inc(27)
%;**       * portBackup%ParportBackup %>27 - Pointer to backup structure
%;** %>29 for port status to be restored. It points
%;** %>29 to a %%'ModuleName'%%.PortStatus structure
%;** %>29 to be allocated by the caller.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine