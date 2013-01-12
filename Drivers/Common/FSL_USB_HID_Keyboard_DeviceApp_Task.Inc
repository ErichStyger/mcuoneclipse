%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (App_Task)
%;**     Description :
%;**         Application task to be called periodically from the main
%;**         task.
%include Common\GeneralParameters.inc(27)
%;**       * txBuf%PartxBuf %>27 - Pointer to temporary buffer used to
%;** %>29 transmit data over USB. Should be equal or
%;** %>29 greater than the endpoint buffer size. Data
%;** %>29 will be sent in an asynchronous way, so
%;** %>29 make sure the buffer is *not* on the stack.
%;** %>29 This buffer must be available until the
%;** %>29 next transmission.
%;**         txBufSize%PartxBufSize %>27 - Size of the buffer in bytes
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, returns ERR_OK if USB
%;** %>29 enumeration has been finished, error code
%;** %>29 otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
