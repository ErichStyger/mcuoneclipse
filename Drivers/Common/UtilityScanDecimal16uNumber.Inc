%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanDecimal16uNumber)
%;**     Description :
%;**         Scans a decimal 16bit unsigned number
%include Common\GeneralParameters.inc(27)
%;**         str%Parstr %>27 - String to scan. It returns as well until
%;** %>29 where it has scanned
%;**       * val%Parval %>27 - Pointer to value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine