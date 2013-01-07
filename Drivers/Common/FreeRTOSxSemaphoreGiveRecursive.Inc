%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xSemaphoreGiveRecursive)
%;**     Description :
%;**         Macro to recursively release, or 'give', a mutex type
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