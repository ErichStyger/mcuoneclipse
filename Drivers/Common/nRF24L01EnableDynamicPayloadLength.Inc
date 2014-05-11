%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (EnableDynamicPayloadLength)
%;**     Description :
%;**         Enables dynamic payload length for the give pipes
%include Common\GeneralParameters.inc(27)
%;**         pipeMask%ParpipeMask %>27 - Mask of pipes, with 1 for pipe 0,
%;** %>29 2 for pipe 1, 4 for pipe 2 and so on.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine