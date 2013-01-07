%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xSemaphoreGetMutexHolder)
%;**     Description :
%;**         Returns the holder of a mutex or semaphore. If xMutex is
%;**         indeed a mutex type semaphore, return the current mutex
%;**         holder. If xMutex is not a mutex type semaphore, or the
%;**         mutex is available (not held by a task), return NULL. Note:
%;**         This Is is a good way of determining if the calling task is
%;**         the mutex holder, but not a good way of determining the
%;**         identity of the mutex holder as the holder may change
%;**         between the function exiting and the returned value being
%;**         tested.
%include Common\GeneralParameters.inc(27)
%;**         xSemaphore%ParxSemaphore %>27 - A handle to the semaphore.
%;**     Returns     :
%;**         ---%RetVal %>27 - Not NULL if the calling task is the holder
%;** %>29 of the mutex, NULL otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine