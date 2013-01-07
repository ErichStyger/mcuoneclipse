%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xSemaphoreTake)
%;**     Description :
%;**         Macro to obtain a semaphore. The semaphore must have
%;**         previously been created with a call to
%;**         vSemaphoreCreateBinary(), xSemaphoreCreateMutex() or
%;**         xSemaphoreCreateCounting().
%;**         This macro must not be called from an ISR.
%;**         xQueueReceiveFromISR() can be used to take a semaphore from
%;**         within an interrupt if required, although this would not be
%;**         a normal operation. Semaphores use queues as their
%;**         underlying mechanism, so functions are to some extent
%;**         interoperable.
%;**         xSemaphoreTake() is part of the fully featured intertask
%;**         communications API. xSemaphoreAltTake() is the alternative
%;**         API equivalent. Both versions require the same parameters
%;**         and return the same values.
%include Common\GeneralParameters.inc(27)
%;**         xMutex%ParxMutex %>27 - A handle to the mutex being obtained.
%;** %>29 This is the handle returned by
%;** %>29 xSemaphoreCreateMutex();
%;**         xBlockTime%ParxBlockTime %>27 - The time in ticks to wait
%;** %>29 for the semaphore to become available.  The
%;** %>29 macro portTICK_RATE_MS can be used to
%;** %>29 convert this to a real time.  A block time
%;** %>29 of zero can be used to poll the semaphore.
%;** %>29 If the task already owns the semaphore then
%;** %>29 xSemaphoreTakeRecursive() will return
%;** %>29 immediately no matter what the value of
%;** %>29 xBlockTime. Specifying the block time as
%;** %>29 portMAX_DELAY will cause the task to block
%;** %>29 indefinitely (without a timeout).
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns pdTRUE if the semaphore was
%;** %>29 obtained.  pdFALSE if xBlockTime expired
%;** %>29 without the semaphore becoming available.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine