%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (isDiskPresent)
%;**     Description :
%;**         Determines if the disk is present or not (e.g. disk inserted).
%include Common\GeneralParameters.inc(27)
%;**       * drvStr%PardrvStr %>27 - drive string, "" or "0" or "1"
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if file system is write protected
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine