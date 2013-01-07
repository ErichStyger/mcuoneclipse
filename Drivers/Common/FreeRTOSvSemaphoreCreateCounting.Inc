%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vSemaphoreCreateCounting)
%;**     Description :
%;**         Macro that creates a counting semaphore by using the
%;**         existing queue mechanism.
%;**         Counting semaphores are typically used for two things:
%;**         1. Counting events.
%;**         In this usage scenario an event handler will 'give' a
%;**         semaphore each time an event occurs (incrementing the
%;**         semaphore count value), and a handler task will 'take' a
%;**         semaphore each time it processes an event (decrementing the
%;**         semaphore count value). The count value is therefore the
%;**         difference between the number of events that have occurred
%;**         and the number that have been processed. In this case it is
%;**         desirable for the initial count value to be zero.
%;**         2. Resource management.
%;**         In this usage scenario the count value indicates the number
%;**         of resources available. To obtain control of a resource a
%;**         task must first obtain a semaphore - decrementing the
%;**         semaphore count value. When the count value reaches zero
%;**         there are no free resources. When a task finishes with the
%;**         resource it 'gives' the semaphore back - incrementing the
%;**         semaphore count value. In this case it is desirable for the
%;**         initial count value to be equal to the maximum count value,
%;**         indicating that all resources are free.
%include Common\GeneralParameters.inc(27)
%;**         uxMaxCount%ParuxMaxCount %>27 - The maximum count value that
%;** %>29 can be reached. When the semaphore reaches
%;** %>29 this value it can no longer be 'given'.
%;**         uxInitialCount%ParuxInitialCount %>27 - The count value
%;** %>29 assigned to the semaphore when it is
%;** %>29 created.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine