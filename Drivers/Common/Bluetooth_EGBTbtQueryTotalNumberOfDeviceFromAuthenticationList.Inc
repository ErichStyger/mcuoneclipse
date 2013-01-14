%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryTotalNumberOfDeviceFromAuthenticationList)
%;**     Description :
%;**         
%include Common\GeneralParameters.inc(27)
%;**       * nofDevices%ParnofDevices %>27 - Pointer to where to return
%;** %>29 the number of authenticated devices in list.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine