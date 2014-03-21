%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnBlockReceived)
%;**     Description :
%;**         This event is called when the requested number of data is
%;**         moved to the input buffer. This method is available only if
%;**         the ReceiveBlock method is enabled.
%include Common\GeneralParameters.inc(27)
%;**       * UserDataPtr%ParUserDataPtr %>27 - Pointer to the user or
%;** %>29 RTOS specific data. The pointer is passed
%;** %>29 as the parameter of Init method. 
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine