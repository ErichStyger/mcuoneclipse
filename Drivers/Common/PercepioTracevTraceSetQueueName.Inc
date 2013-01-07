%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceSetQueueName)
%;**     Description :
%;**         Assigns a name to a FreeRTOS Queue, Semaphore or Mutex. This
%;**         function should  be called right after creation of the
%;**         queue/mutex/semaphore. If not using this function, the
%;**         queues/mutexes/semaphores will be presented by their numeric
%;**         handle only.
%include Common\GeneralParameters.inc(27)
%;**       * queue%Parqueue %>27 - Pointer to the queue
%;**       * name%Parname %>27 - Pointer to name
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine