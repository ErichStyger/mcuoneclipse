%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryMostRecentlyUsedAuthenticatedDevice)
%;**     Description :
%;**         Query Most Recently Used Authenticated Device
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - Pointer to buffer where to the 48bit
%;** %>29 address string in NAP:UAP:LAP format.
%;**         bufSize%ParbufSize %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine