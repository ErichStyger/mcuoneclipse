%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskDelay)
%;**     Description :
%;**         Delay a task for a given number of ticks. The actual time
%;**         that the task remains blocked depends on the tick rate. The
%;**         constant portTICK_RATE_MS can be used to calculate real time
%;**         from the tick rate - with the resolution of one tick period.
%;**         vTaskDelay() specifies a time at which the task wishes to
%;**         unblock relative to the time at which vTaskDelay() is called.
%;**         For example, specifying a block period of 100 ticks will
%;**         cause the task to unblock 100 ticks after vTaskDelay() is
%;**         called. vTaskDelay() does not therefore provide a good
%;**         method of controlling the frequency of a cyclical task as
%;**         the path taken through the code, as well as other task and
%;**         interrupt activity, will effect the frequency at which
%;**         vTaskDelay() gets called and therefore the time at which the
%;**         task next executes. See vTaskDelayUntil() for an alternative
%;**         API function designed to facilitate fixed frequency
%;**         execution. It does this by specifying an absolute time
%;**         (rather than a relative time) at which the calling task
%;**         should unblock. 
%include Common\GeneralParameters.inc(27)
%;**         xTicksToDelay%ParxTicksToDelay %>27 - The amount of time, in
%;** %>29 tick periods, that the calling task should
%;** %>29 block.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine