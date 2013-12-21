%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueReceiveFromISR)
%;**     Description :
%;**         A version of xQueueReceive() that can be called from an ISR.
%;**         Unlike xQueueReceive(), xQueueReceiveFromISR() does not
%;**         permit a block time to be specified.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue from which
%;** %>29 the data is to be received.
%;**         pvBuffer%ParpvBuffer %>27 - A pointer to the memory into
%;** %>29 which the data received from the queue will
%;** %>29 be copied.The length of the buffer must be
%;** %>29 at least equal to the queue item size (set
%;** %>29 when the queue was created).
%;**       * pxHigherPriorityTaskWoken%ParpxHigherPriorityTaskWoken %>27
%;** %>29 - Pointer to A task may be blocked waiting
%;** %>29 for space to become available on the queue.
%;** %>29 If xQueueReceiveFromISR() causes such a
%;** %>29 task to unblock then
%;** %>29 *pxHigherPriorityTaskWoken will get set to
%;** %>29 pdTRUE, otherwise
%;** %>29 *pxHigherPriorityTaskWoken will remain
%;** %>29 unchanged.
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