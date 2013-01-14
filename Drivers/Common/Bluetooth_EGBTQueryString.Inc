%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (QueryString)
%;**     Description :
%;**         get string from device: "<cmd>\r
%;**         " ==> "<response><string>\r
%;**         OK\r
%;**         "
%include Common\GeneralParameters.inc(27)
%;**       * cmd%Parcmd %>27 - Pointer to command string
%;**       * expectedResponse%ParexpectedResponse %>27 - Pointer to
%;** %>29 expected response string
%;**       * string%Parstring %>27 - Pointer to buffer where to store the
%;** %>29 string value
%;**         stringSize%ParstringSize %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine