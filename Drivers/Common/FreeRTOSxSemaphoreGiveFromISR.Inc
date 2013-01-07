%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xSemaphoreGiveFromISR)
%;**     Description :
%;**         Macro to release a semaphore. The semaphore must have
%;**         previously been created with a call to
%;**         vSemaphoreCreateBinary() or xSemaphoreCreateCounting().
%;**         Mutex type semaphores (those created using a call to
%;**         xSemaphoreCreateMutex()) must not be used with this macro.
%;**         This macro can be used from an ISR.
%include Common\GeneralParameters.inc(27)
%;**         xSemaphore%ParxSemaphore %>27 - A handle to the semaphore
%;** %>29 being released. This is the handle returned
%;** %>29 when the semaphore was created.
%;**       * pxHigherPriorityTaskWoken%ParpxHigherPriorityTaskWoken %>27
%;** %>29 - xSemaphoreGiveFromISR() will set
%;** %>29 *pxHigherPriorityTaskWoken to pdTRUE if
%;** %>29 giving the semaphoree caused a task to
%;** %>29 unblock, and the unblocked task has a
%;** %>29 priority higher than the currently running
%;** %>29 task. If xSemaphoreGiveFromISR() sets this
%;** %>29 value to pdTRUE then a context switch
%;** %>29 should be requested before the interrupt is
%;** %>29 exited.
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns pdTRUE if the semaphore was given.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine