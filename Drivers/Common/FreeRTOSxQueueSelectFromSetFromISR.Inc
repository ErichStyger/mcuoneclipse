%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueSelectFromSetFromISR)
%;**     Description :
%;**         A version of xQueueSelectFromSet() that can be used from an
%;**         interrupt service routine (ISR). 
%include Common\GeneralParameters.inc(27)
%;**         xQueueSet%ParxQueueSet %>27 - The queue set being queried.
%;** %>29 It is not possible to block on a read as
%;** %>29 this function is designed to be used from
%;** %>29 an interrupt. 
%;**     Returns     :
%;**         ---%RetVal %>27 - xQueueSelectFromSet() will return the
%;** %>29 handle of a queue (cast to a
%;** %>29 xQueueSetMemberHandle type) contained in
%;** %>29 the queue set that contains data, or the
%;** %>29 handle of a semaphore (cast to a
%;** %>29 xQueueSetMemberHandle type) contained in
%;** %>29 the queue set that is available, or NULL if
%;** %>29 no such queue or semaphore exists before
%;** %>29 before the specified block time expires. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine