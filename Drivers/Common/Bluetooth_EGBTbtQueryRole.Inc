%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryRole)
%;**     Description :
%;**         Returns the current device role
%include Common\GeneralParameters.inc(27)
%;**       * role%Parrole %>27 - Pointer to character which will hold the
%;** %>29 role ('0' for slave, '1' for master or '2'
%;** %>29 for slave-loop)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine