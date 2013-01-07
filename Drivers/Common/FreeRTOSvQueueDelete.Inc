%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vQueueDelete)
%;**     Description :
%;**         Deletes a queue that was previously created using a call to
%;**         xQueueCreate(). vQueueDelete() can also be used to delete a
%;**         semaphore.
%include Common\GeneralParameters.inc(27)
%;**         pxQueueToDelete%ParpxQueueToDelete %>27 - The handle of the
%;** %>29 queue being deleted. Semaphore handles can
%;** %>29 also be used. Queues are used to pass data
%;** %>29 between tasks and between tasks and
%;** %>29 interrupts. A queue/semaphore must not be
%;** %>29 deleted if there are any tasks that are
%;** %>29 blocked on the queue/semaphore waiting for
%;** %>29 events (sends or receives).
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine