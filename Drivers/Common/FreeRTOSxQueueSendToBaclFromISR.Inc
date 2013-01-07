%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueSendToBaclFromISR)
%;**     Description :
%;**         Versions of xQueueSendToBack() API functions that can be
%;**         called from an ISR. Unlike xQueueSendToBack() these
%;**         functions do not permit a block time to be specified.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue to which the
%;** %>29 data is to be sent.
%;**         pvItemToQueue%ParpvItemToQueue %>27 - A pointer to the data
%;** %>29 to be sent to the queue. The size of the
%;** %>29 data that can be sent to a queue was
%;** %>29 defined when the queue was created.
%;**       * pxHigherPriorityTaskWoken%ParpxHigherPriorityTaskWoken %>27
%;** %>29 - xQueueSendFromISR() will set
%;** %>29 *pxHigherPriorityTaskWoken to pdTRUE if
%;** %>29 sending to the queue caused a task to
%;** %>29 unblock, and the unblocked task has a
%;** %>29 priority higher than the currently running
%;** %>29 task. If xQueueSendFromISR() sets this
%;** %>29 value to pdTRUE then a context switch
%;** %>29 should be performed before the interrupt is
%;** %>29 exited.
%;**     Returns     :
%;**         ---%RetVal %>27 - pdPASS: Data was successfully sent to the
%;** %>29 queue. If a block time was specified then
%;** %>29 the calling task may have been temporarily
%;** %>29 placed into the Blocked state to wait for
%;** %>29 space to become available and space did
%;** %>29 become available before the block time
%;** %>29 expired.
%;** %>29 errQUEUE_FULL: The queue is already full so
%;** %>29 no data could be sent to the queue. If a
%;** %>29 block time was specified then the calling
%;** %>29 task may have been temporarily placed into
%;** %>29 the Blocked state to wait for space to
%;** %>29 become available, but no space became
%;** %>29 available before the block time expired.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine