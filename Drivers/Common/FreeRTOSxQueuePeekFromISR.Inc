%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueuePeekFromISR)
%;**     Description :
%;**         A version of xQueuePeek() that can be used from an interrupt
%;**         service routine (ISR). Reads an item from a queue, but does
%;**         not remove the item from the queue. Therefore the same item
%;**         would be returned the next time xQueueReceive() or
%;**         xQueuePeek() was called on the same queue.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue from which
%;** %>29 the data is to be read.
%;**         pvBuffer%ParpvBuffer %>27 - A pointer to the memory into
%;** %>29 which the data read from the queue will be
%;** %>29 copied. The length of the buffer must be at
%;** %>29 least equal to the queue item size (set
%;** %>29 when the queue was created).
%;**         xTicksToWait%ParxTicksToWait %>27 - The number of ticks for
%;** %>29 which the calling task should be held in
%;** %>29 the Blocked state to wait for data to
%;** %>29 become available from the queue should the
%;** %>29 queue already be empty.
%;** %>29 A value of zero will prevent the calling
%;** %>29 task from entering the Blocked state.
%;** %>29 If INCLUDE_vTaskSuspend is set to 1 then a
%;** %>29 value of portMAX_DELAY will hold the task
%;** %>29 in the Blocked state indefinitely to wait
%;** %>29 for data.
%;**     Returns     :
%;**         ---%RetVal %>27 - pdPASS: Data was successfully read from
%;** %>29 the queue. If a block time was specified
%;** %>29 then the calling task may have been
%;** %>29 temporarily placed into the Blocked state
%;** %>29 to wait for data to become available and
%;** %>29 data did become available before the block
%;** %>29 time expired.
%;** %>29 errQUEUE_EMPTY: The queue was empty so no
%;** %>29 date could be read form the queue. If a
%;** %>29 block time was specified then the calling
%;** %>29 task may have been temporarily placed into
%;** %>29 the Blocked state to wait for data to
%;** %>29 become available, but no data became
%;** %>29 available before the block time expired.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine