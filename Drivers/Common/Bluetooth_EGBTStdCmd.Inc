%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (StdCmd)
%;**     Description :
%;**         Send standard command: "<cmd>\r
%;**         " ==> "<expectedResponse>"
%include Common\GeneralParameters.inc(27)
%;**       * cmd%Parcmd %>27 - Pointer to command string
%;**       * rxBuf%ParrxBuf %>27 - Pointer to buffer for the answer
%;**         rxBufSize%ParrxBufSize %>27 - 
%;**       * expectedResponse%ParexpectedResponse %>27 - Pointer to
%;** %>29 expected response
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine