%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btDeleteAuthenticatedDeviceFromListStr)
%;**     Description :
%;**         Deletes an authenticated device from the list
%include Common\GeneralParameters.inc(27)
%;**       * addrString%ParaddrString %>27 - Pointer to address in NAP,
%;** %>29 UAP,LAP format.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine