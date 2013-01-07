%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReverseBias)
%;**     Description :
%;**         Puts the LED in reverse bias mode and starts discharing
%;**         (port set as input).
%include Common\GeneralParameters.inc(27)
%;**       * PortBackup%ParPortBackup %>27 - Pointer to backup structure
%;** %>29 for port status (to be restored later).
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine