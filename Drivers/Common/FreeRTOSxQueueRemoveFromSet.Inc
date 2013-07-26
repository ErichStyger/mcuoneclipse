%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueRemoveFromSet)
%;**     Description :
%;**         Remove an RTOS queue or semaphore from a queue set. An RTOS
%;**         queue or semaphore can only be removed from a queue set if
%;**         the queue or semaphore is empty. 
%include Common\GeneralParameters.inc(27)
%;**         xQueueOrSemaphore%ParxQueueOrSemaphore %>27 - The handle of
%;** %>29 the queue or semaphore being removed from
%;** %>29 the queue set (cast to an
%;** %>29 xQueueSetMemberHandle type). 
%;**         xQueueSet%ParxQueueSet %>27 - The handle of the queue set in
%;** %>29 which the queue or semaphore is included.
%;**     Returns     :
%;**         ---%RetVal %>27 - If the queue or semaphore was successfully
%;** %>29 added to the queue set then pdPASS is
%;** %>29 returned. If the queue could not be
%;** %>29 successfully added to the queue set because
%;** %>29 it is already a member of a different queue
%;** %>29 set then pdFAIL is returned. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine