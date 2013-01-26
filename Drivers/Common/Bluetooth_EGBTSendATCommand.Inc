%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendATCommand)
%;**     Description :
%;**         Sends an AT command string (with the AT in it) to the module.
%include Common\GeneralParameters.inc(27)
%;**       * cmd%Parcmd %>27 - Pointer to AT command string with the AT
%;** %>29 in it
%;**       * rxBuf%ParrxBuf %>27 - Pointer to buffer for the response
%;** %>29 from the device
%;**         rxBufSize%ParrxBufSize %>27 - size of the receiving buffer
%;** %>29 in bytes
%;**       * expectedTailStr%ParexpectedTailStr %>27 - Pointer to the
%;** %>29 function will read from the device until
%;** %>29 the expected tail string is read. Typically
%;** %>29 this is "OK" terminated by backslash r and
%;** %>29 backslash n
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine