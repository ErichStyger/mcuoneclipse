%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vSemaphoreCreateBinary)
%;**     Description :
%;**         Macro that creates a semaphore by using the existing queue
%;**         mechanism. The queue length is 1 as this is a binary
%;**         semaphore. The data size is 0 as we don't want to actually
%;**         store any data - we just want to know if the queue is empty
%;**         or full.
%;**         Binary semaphores and mutexes are very similar but have some
%;**         subtle differences: Mutexes include a priority inheritance
%;**         mechanism, binary semaphores do not. This makes binary
%;**         semaphores the better choice for implementing
%;**         synchronisation (between tasks or between tasks and an
%;**         interrupt), and mutexes the better choice for implementing
%;**         simple mutual exclusion.
%;**         A binary semaphore need not be given back once obtained, so
%;**         task synchronisation can be implemented by one
%;**         task/interrupt continuously 'giving' the semaphore while
%;**         another continuously 'takes' the semaphore. This is
%;**         demonstrated by the sample code on the
%;**         xSemaphoreGiveFromISR() documentation page.
%;**         The priority of a task that 'takes' a mutex can potentially
%;**         be raised if another task of higher priority attempts to
%;**         obtain the same mutex. The task that owns the mutex
%;**         'inherits' the priority of the task attempting to 'take' the
%;**         same mutex. This means the mutex must always be 'given' back
%;**         - otherwise the higher priority task will never be able to
%;**         obtain the mutex, and the lower priority task will never
%;**         'disinherit' the priority. An example of a mutex being used
%;**         to implement mutual exclusion is provided on the
%;**         xSemaphoreTake() documentation page.
%;**         Both mutex and binary semaphores are assigned to variables
%;**         of type xSemaphoreHandle and can be used in any API function
%;**         that takes a parameter of this type. 
%include Common\GeneralParameters.inc(27)
%;**         xSemaphore%ParxSemaphore %>27 - Handle to the created
%;** %>29 semaphore. Should be of type
%;** %>29 xSemaphoreHandle.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine