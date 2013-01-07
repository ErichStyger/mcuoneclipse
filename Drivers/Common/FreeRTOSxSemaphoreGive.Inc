%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xSemaphoreGive)
%;**     Description :
%;**         Macro to release a semaphore. The semaphore must have
%;**         previously been created with a call to
%;**         vSemaphoreCreateBinary(), xSemaphoreCreateMutex() or
%;**         xSemaphoreCreateCounting(), and obtained using
%;**         sSemaphoreTake().
%;**         This must not be used from an ISR. See
%;**         xSemaphoreGiveFromISR() for an alternative which can be used
%;**         from an ISR.
%;**         This macro must also not be used on semaphores created using
%;**         xSemaphoreCreateRecursiveMutex().
%;**         xSemaphoreGive() is part of the fully featured intertask
%;**         communications API. xSemaphoreAltGive() is the alternative
%;**         API equivalent. Both versions require the same parameters
%;**         and return the same values. 
%include Common\GeneralParameters.inc(27)
%;**         xMutex%ParxMutex %>27 - A handle to the mutex being released,
%;** %>29 or 'given'.  This is the handle returned by
%;** %>29 xSemaphoreCreateMutex();
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns pdTRUE if the semaphore was given.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine