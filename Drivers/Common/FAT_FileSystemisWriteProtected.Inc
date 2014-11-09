%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (isWriteProtected)
%;**     Description :
%;**         Determines if the file system is write protected.
%include Common\GeneralParameters.inc(27)
%;**       * drvStr%PardrvStr %>27 - Pointer to drive string, e.g. "" or
%;** %>29 "0"
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if file system is write protected
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine