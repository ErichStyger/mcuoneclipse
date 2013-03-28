%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSTaskSuspend)
%;**     Description :
%;**         This function is called to suspend a task.  The task can be
%;**         the calling task if the priority passed to OSTaskSuspend()
%;**         is the priority of the calling task or OS_PRIO_SELF.
%include Common\GeneralParameters.inc(27)
%;**         prio%Parprio %>27 - is the priority of the task to suspend.
%;** %>29 If you specify OS_PRIO_SELF, the calling
%;** %>29 task will suspend itself and rescheduling
%;** %>29 will occur.
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE               if the requested
%;** %>29 task is suspended
%;** %>29 OS_ERR_TASK_SUSPEND_IDLE  if you attempted
%;** %>29 to suspend the idle task which is not
%;** %>29 allowed.
%;** %>29 OS_ERR_PRIO_INVALID       if the priority
%;** %>29 you specify is higher that the maximum
%;** %>29 allowed (i.e. >= OS_LOWEST_PRIO) or, you
%;** %>29 have not specified OS_PRIO_SELF.
%;** %>29 OS_ERR_TASK_SUSPEND_PRIO  if the task to
%;** %>29 suspend does not exist
%;** %>29 OS_ERR_TASK_NOT_EXITS     if the task is
%;** %>29 assigned to a Mutex PIP
%;** %>29 Note: You should use this function with
%;** %>29 great care.  If you suspend a task that is
%;** %>29 waiting for an event (i.e. a message, a
%;** %>29 semaphore, a queue ...) you will prevent
%;** %>29 this task from running when the event
%;** %>29 arrives.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine