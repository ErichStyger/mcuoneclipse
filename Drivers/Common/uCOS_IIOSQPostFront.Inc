%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSQPostFront)
%;**     Description :
%;**         This function sends a message to a queue but unlike OSQPost(),
%;**         the message is posted at the front instead of the end of the
%;**         queue.  Using OSQPostFront() allows you to send 'priority'
%;**         messages.
%include Common\GeneralParameters.inc(27)
%;**       * pevent%Parpevent %>27 - Pointer to is a pointer to the event
%;** %>29 control block associated with the desired
%;** %>29 queue
%;**       * pmsg%Parpmsg %>27 - Pointer to the message to send.
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE: The call was successful and
%;** %>29 the message was sent
%;** %>29 OS_ERR_Q_FULL: If the queue cannot accept
%;** %>29 any more messages because it is full.
%;** %>29 OS_ERR_EVENT_TYPE: If you didn't pass a
%;** %>29 pointer to a queue.
%;** %>29 OS_ERR_PEVENT_NULL: If 'pevent' is a NULL
%;** %>29 pointer
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine