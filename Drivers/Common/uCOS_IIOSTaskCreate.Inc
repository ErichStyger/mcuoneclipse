%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSTaskCreate)
%;**     Description :
%;**         This function is used to have uC/OS-II manage the execution
%;**         of a task.  Tasks can either be created prior to the start
%;**         of multitasking or by a running task.  A task cannot be
%;**         created by an ISR.
%include Common\GeneralParameters.inc(27)
%;**         task%Partask %>27 - is a pointer to the task's code
%;**       * p_arg%Parp_arg %>27 - Pointer to is a pointer to an optional
%;** %>29 data area which can be used to pass
%;** %>29 parameters to the task when the task first
%;** %>29 executes.
%;**       * ptos%Parptos %>27 - Pointer to is a pointer to the task's
%;** %>29 top of stack.  If the configuration
%;** %>29 constant OS_STK_GROWTH is set to 1, the
%;** %>29 stack is assumed to grow downward (i.e.
%;** %>29 from high memory to low memory).  'pstk'
%;** %>29 will thus point to the highest (valid)
%;** %>29 memory location of the stack.  If
%;** %>29 OS_STK_GROWTH is set to 0, 'pstk' will
%;** %>29 point to the lowest memory location of the
%;** %>29 stack and the stack will grow with
%;** %>29 increasing memory locations.
%;**         prio%Parprio %>27 - is the task's priority.  A unique
%;** %>29 priority MUST be assigned to each task and
%;** %>29 the lower the number, the higher the
%;** %>29 priority.
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE             if the function
%;** %>29 was successful.
%;** %>29 OS_PRIO_EXIT            if the task
%;** %>29 priority already exist (each task MUST have
%;** %>29 a unique priority).
%;** %>29 OS_ERR_PRIO_INVALID     if the priority you
%;** %>29 specify is higher that the maximum allowed
%;** %>29 (i.e. >= OS_LOWEST_PRIO)
%;** %>29 OS_ERR_TASK_CREATE_ISR  if you tried to
%;** %>29 create a task from an ISR.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine