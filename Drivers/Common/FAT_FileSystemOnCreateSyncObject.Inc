%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnCreateSyncObject)
%;**     Description :
%;**         If the file system is set to be reentrant, then this event
%;**         is called after the sync object (semaphore) creation. That
%;**         would allow e.g. for Percepio trace to name the object so it
%;**         can be tracked.
%include Common\GeneralParameters.inc(27)
%;**       * sobj%Parsobj %>27 - Pointer to the sync object
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine