%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueSelectFromSet)
%;**     Description :
%;**         xQueueSelectFromSet() selects from the members of a queue
%;**         set a queue or semaphore that either contains data (in the
%;**         case of a queue) or is available to take (in the case of a
%;**         semaphore). xQueueSelectFromSet() effectively allows a task
%;**         to block (pend) on a read operation on all the queues and
%;**         semaphores in a queue set simultaneously. 
%include Common\GeneralParameters.inc(27)
%;**         xQueueSet%ParxQueueSet %>27 - The queue set on which the
%;** %>29 task will (potentially) block. 
%;**         xBlockTimeTicks%ParxBlockTimeTicks %>27 - The maximum time,
%;** %>29 in ticks, that the calling task will remain
%;** %>29 in the Blocked state (with other tasks
%;** %>29 executing) to wait for a member of the
%;** %>29 queue set to be ready for a successful
%;** %>29 queue read or semaphore take operation. 
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