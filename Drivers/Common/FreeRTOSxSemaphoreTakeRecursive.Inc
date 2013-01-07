%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xSemaphoreTakeRecursive)
%;**     Description :
%;**         Macro to recursively obtain, or 'take', a mutex type
%;**         semaphore. The mutex must have previously been created using
%;**         a call to xSemaphoreCreateRecursiveMutex();
%;**         This macro must not be used on mutexes created using
%;**         xSemaphoreCreateMutex(). A mutex used recursively can be
%;**         'taken' repeatedly by the owner. The mutex doesn't become
%;**         available again until the owner has called
%;**         xSemaphoreGiveRecursive() for each successful 'take' request.
%;**         For example, if a task successfully 'takes' the same mutex 5
%;**         times then the mutex will not be available to any other task
%;**         until it has also  'given' the mutex back exactly five times.
%include Common\GeneralParameters.inc(27)
%;**         xMutex%ParxMutex %>27 - A handle to the mutex being obtained.
%;** %>29 This is the handle returned by
%;** %>29 xSemaphoreCreateRecursiveMutex();
%;**         xBlockTime%ParxBlockTime %>27 - The time in ticks to wait
%;** %>29 for the semaphore to become available.  The
%;** %>29 macro portTICK_RATE_MS can be used to
%;** %>29 convert this to a real time.  A block time
%;** %>29 of zero can be used to poll the semaphore.
%;** %>29 If the task already owns the semaphore then
%;** %>29 xSemaphoreTakeRecursive() will return
%;** %>29 immediately no matter what the value of
%;** %>29 xBlockTime.
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns pdTRUE if the semaphore was
%;** %>29 obtained.  pdFALSE if xBlockTime expired
%;** %>29 without the semaphore becoming available.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine