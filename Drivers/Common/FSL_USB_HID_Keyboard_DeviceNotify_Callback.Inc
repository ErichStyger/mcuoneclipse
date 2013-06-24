%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (App_Param_Callback)
%;**     Description :
%;**         This function is called whenever a HID class request is
%;**         received. This function handles these class requests.
%include Common\GeneralParameters.inc(27)
%;**         request%Parrequest %>27 - request type
%;**         value%Parvalue %>27 - report type and ID
%;**         wIndex%ParwIndex %>27 - 
%;**       * data%Pardata %>27 - Pointer to the data
%;**       * size%Parsize %>27 - size of the transfer
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine