%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSQPend)
%;**     Description :
%;**         This function waits for a message to be sent to a queue
%include Common\GeneralParameters.inc(27)
%;**       * pevent%Parpevent %>27 - Pointer to the event control block
%;** %>29 associated with the desired queue
%;**         timeout%Partimeout %>27 - is an optional timeout period (in
%;** %>29 clock ticks).  If non-zero, your task will
%;** %>29 wait for a message to arrive at the queue
%;** %>29 up to the amount of time specified by this
%;** %>29 argument.  If you specify 0, however, your
%;** %>29 task will wait forever at the specified
%;** %>29 queue or, until a message arrives.
%;**       * perr%Parperr %>27 - Pointer to where an error message will
%;** %>29 be deposited.  Possible error messages are:
%;** %>29 OS_ERR_NONE         The call was successful
%;** %>29 and your task received a message.
%;** %>29 OS_ERR_TIMEOUT      A message was not
%;** %>29 received within the specified 'timeout'.
%;** %>29 OS_ERR_PEND_ABORT   The wait on the queue
%;** %>29 was aborted.
%;** %>29 OS_ERR_EVENT_TYPE   You didn't pass a
%;** %>29 pointer to a queue
%;** %>29 OS_ERR_PEVENT_NULL  If 'pevent' is a NULL
%;** %>29 pointer
%;** %>29 OS_ERR_PEND_ISR     If you called this
%;** %>29 function from an ISR and the result would
%;** %>29 lead to a suspension.
%;** %>29 OS_ERR_PEND_LOCKED  If you called this
%;** %>29 function with the scheduler is locked
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine