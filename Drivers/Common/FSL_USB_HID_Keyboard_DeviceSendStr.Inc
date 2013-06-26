%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendStr)
%;**     Description :
%;**         Sends a string to the HID host. This function will translate
%;**         the string into the correct status messages
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string to be sent
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine