%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btFindDeviceFromAuthenticatedDeviceListStr)
%;**     Description :
%;**         Find Device from Authenticated Device List
%include Common\GeneralParameters.inc(27)
%;**       * addrString%ParaddrString %>27 - Pointer to address in NAP,
%;** %>29 UAP,LAP format
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine