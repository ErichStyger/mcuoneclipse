%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskCallApplicationTaskHook)
%;**     Description :
%;**          A 'tag' value can be assigned to each task. Normally this
%;**         value is for the use of the application only and the RTOS
%;**         kernel does not access it. However, it is possible to use
%;**         the tag to assign a hook (or callback) function to a task -
%;**         the hook function being executed by calling
%;**         xTaskCallApplicationTaskHook(). Each task can define its own
%;**         callback, or simply not define a callback at all.
%;**         Although it is possible to use the first function parameter
%;**         to call the hook function of any task, the most common use
%;**         of task hook function is with the trace hook macros, as per
%;**         the example given below.
%;**         Task hook functions must have type pdTASK_HOOK_CODE, that is
%;**         take a void * parameter, and return a value of type
%;**         portBASE_TYPE. The void * parameter can be used to pass any
%;**         information into the hook function. 
%include Common\GeneralParameters.inc(27)
%;**         xTask%ParxTask %>27 - The handle of the task whose hook
%;** %>29 function is being called. Passing NULL as
%;** %>29 xTask will call the hook function
%;** %>29 associated with the currently executing
%;** %>29 task.
%;**       * pvParameter%ParpvParameter %>27 - The value to pass to the
%;** %>29 hook function. This can be a pointer to a
%;** %>29 structure, or simply a numeric value.
%;**     Returns     :
%;**         ---%RetVal %>27 - return value
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine