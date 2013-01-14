%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetIACStr)
%;**     Description :
%;**         Sets the Inquire Access Code string
%include Common\GeneralParameters.inc(27)
%;**       * iac%Pariac %>27 - Pointer to new Inquire Access Code string
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine