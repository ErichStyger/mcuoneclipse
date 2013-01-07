%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskDelayUntil)
%;**     Description :
%;**         Delay a task until a specified time. This function can be
%;**         used by cyclical tasks to ensure a constant execution
%;**         frequency.
%;**         This function differs from vTaskDelay() in one important
%;**         aspect: vTaskDelay() specifies a time at which the task
%;**         wishes to unblock relative to the time at which vTaskDelay()
%;**         is called, whereas vTaskDelayUntil() specifies an absolute
%;**         time at which the task wishes to unblock.
%;**         vTaskDelay() will cause a task to block for the specified
%;**         number of ticks from the time vTaskDelay() is called. It is
%;**         therefore difficult to use vTaskDelay() by itself to
%;**         generate a fixed execution frequency as the time between a
%;**         task unblocking following a call to vTaskDelay() and that
%;**         task next calling vTaskDelay() may not be fixed [the task
%;**         may take a different path though the code between calls, or
%;**         may get interrupted or preempted a different number of times
%;**         each time it executes].
%;**         Whereas vTaskDelay() specifies a wake time relative to the
%;**         time at which the function is called, vTaskDelayUntil()
%;**         specifies the absolute (exact) time at which it wishes to
%;**         unblock.
%;**         It should be noted that vTaskDelayUntil() will return
%;**         immediately (without blocking) if it is used to specify a
%;**         wake time that is already in the past. Therefore a task
%;**         using vTaskDelayUntil() to execute periodically will have to
%;**         re-calculate its required wake time if the periodic
%;**         execution is halted for any reason (for example, the task is
%;**         temporarily placed into the Suspended state) causing the
%;**         task to miss one or more periodic executions. This can be
%;**         detected by checking the variable passed by reference as the
%;**         pxPreviousWakeTime parameter against the current tick count.
%;**         This is however not necessary under most usage scenarios.
%;**         The constant portTICK_RATE_MS can be used to calculate real
%;**         time from the tick rate - with the resolution of one tick
%;**         period.
%;**         This function must not be called while the scheduler has
%;**         been suspended by a call to vTaskSuspendAll(). 
%include Common\GeneralParameters.inc(27)
%;**         pxPreviousWakeTime%ParpxPreviousWakeTime %>27 - Pointer to a
%;** %>29 variable that holds the time at which the
%;** %>29 task was last unblocked. The variable must
%;** %>29 be initialised with the current time prior
%;** %>29 to its first use (see the example below).
%;** %>29 Following this the variable is
%;** %>29 automatically updated within
%;** %>29 vTaskDelayUntil(). 
%;**         xTimeIncrement%ParxTimeIncrement %>27 - The cycle time
%;** %>29 period. The task will be unblocked at time
%;** %>29 (*pxPreviousWakeTime + xTimeIncrement).
%;** %>29 Calling vTaskDelayUntil with the same
%;** %>29 xTimeIncrement parameter value will cause
%;** %>29 the task to execute with a fixed interval
%;** %>29 period. 
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine