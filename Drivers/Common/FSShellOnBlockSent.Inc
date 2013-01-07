%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnBlockSent)
%;**     Description :
%;**         This event is called after the last character from the
%;**         output buffer is moved to the transmitter. 
%include Common\GeneralParameters.inc(27)
%;**       * UserDataPtr%ParUserDataPtr %>27 - Pointer to the user or
%;** %>29 RTOS specific data. This pointer is passed
%;** %>29 as the parameter of Init method.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine