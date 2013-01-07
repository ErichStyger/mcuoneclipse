%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (taskENTER_CRITICAL)
%;**     Description :
%;**         Macro to mark the start of a critical code region.
%;**         Preemptive context switches cannot occur when in a critical
%;**         region.
%;**         NOTE: This may alter the stack (depending on the portable
%;**         implementation) so must be used with care!
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine