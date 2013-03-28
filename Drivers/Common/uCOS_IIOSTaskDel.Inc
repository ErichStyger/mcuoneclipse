%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSTaskDel)
%;**     Description :
%;**         This function allows you to delete a task.  The calling task
%;**         can delete itself by its own priority number.  The deleted
%;**         task is returned to the dormant state and can be
%;**         re-activated by creating the deleted task again.
%include Common\GeneralParameters.inc(27)
%;**         prio%Parprio %>27 - is the priority of the task to delete.
%;** %>29 Note that you can explicitely delete the
%;** %>29 current task without knowing its priority
%;** %>29 level by setting 'prio' to OS_PRIO_SELF.
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE             if the call is
%;** %>29 successful
%;** %>29 OS_ERR_TASK_DEL_IDLE    if you attempted to
%;** %>29 delete uC/OS-II's idle task
%;** %>29 OS_ERR_PRIO_INVALID     if the priority you
%;** %>29 specify is higher that the maximum allowed
%;** %>29 (i.e. >= OS_LOWEST_PRIO) or, you have not
%;** %>29 specified OS_PRIO_SELF.
%;** %>29 OS_ERR_TASK_DEL         if the task is
%;** %>29 assigned to a Mutex PIP.
%;** %>29 OS_ERR_TASK_NOT_EXIST   if the task you
%;** %>29 want to delete does not exist.
%;** %>29 OS_ERR_TASK_DEL_ISR     if you tried to
%;** %>29 delete a task from an ISR
%;** %>29 Notes:
%;** %>29 1) To reduce interrupt latency, OSTaskDel()
%;** %>29 'disables' the task:
%;** %>29 a) by making it not ready
%;** %>29 b) by removing it from any wait lists
%;** %>29 c) by preventing OSTimeTick() from making
%;** %>29 the task ready to run.
%;** %>29 The task can then be 'unlinked' from the
%;** %>29 miscellaneous structures in uC/OS-II.
%;** %>29 2) The function OS_Dummy() is called after
%;** %>29 OS_EXIT_CRITICAL() because, on most
%;** %>29 processors, the next instruction following
%;** %>29 the enable interrupt instruction is ignored.
%;** %>29 3) An ISR cannot delete a task.
%;** %>29 4) The lock nesting counter is incremented
%;** %>29 because, for a brief instant, if the
%;** %>29 current task is being deleted, the current
%;** %>29 task would not be able to be rescheduled
%;** %>29 because it is removed from the ready list.
%;** %>29 Incrementing the nesting counter prevents
%;** %>29 another task from being schedule.  This
%;** %>29 means that an ISR would return to the
%;** %>29 current task which is being deleted.  The
%;** %>29 rest of the deletion would thus be able to
%;** %>29 be completed.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine