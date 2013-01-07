%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xatoi)
%;**     Description :
%;**         Custom atoi() (ascii to int) implementation by Elm Chan
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string to scan. Returns until
%;** %>29 where it has scanned.
%;**       * res%Parres %>27 - Pointer to where to store the result
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine