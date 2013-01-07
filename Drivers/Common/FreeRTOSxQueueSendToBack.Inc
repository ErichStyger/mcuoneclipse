%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueSendToBack)
%;**     Description :
%;**         Sends an item to the back of a queue.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue to which the
%;** %>29 data is to be sent.
%;**         pvItemToQueue%ParpvItemToQueue %>27 - A pointer to the data
%;** %>29 to be sent to the queue. The size of the
%;** %>29 data that can be sent to a queue was
%;** %>29 defined when the queue was created.
%;**         xTicksToWait%ParxTicksToWait %>27 - The number of ticks for
%;** %>29 which the calling task should be held in
%;** %>29 the Blocked state to wait for space to
%;** %>29 become available on the queue should the
%;** %>29 queue already be full.
%;** %>29 A value of zero will prevent the calling
%;** %>29 task from entering the Blocked state.
%;** %>29 If INCLUDE_vTaskSuspend is set to 1 then a
%;** %>29 value of portMAX_DELAY will hold the task
%;** %>29 in the Blocked state indefinitely to wait
%;** %>29 for space to become available on the queue.
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