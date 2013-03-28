%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSTaskResume)
%;**     Description :
%;**         This function is called to resume a previously suspended
%;**         task.  This is the only call that will remove an explicit
%;**         task suspension.
%include Common\GeneralParameters.inc(27)
%;**         prio%Parprio %>27 - is the priority of the task to resume.
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE                if the
%;** %>29 requested task is resumed
%;** %>29 OS_ERR_PRIO_INVALID        if the priority
%;** %>29 you specify is higher that the maximum
%;** %>29 allowed (i.e. >= OS_LOWEST_PRIO)
%;** %>29 OS_ERR_TASK_RESUME_PRIO    if the task to
%;** %>29 resume does not exist
%;** %>29 OS_ERR_TASK_NOT_EXIST      if the task is
%;** %>29 assigned to a Mutex PIP
%;** %>29 OS_ERR_TASK_NOT_SUSPENDED  if the task to
%;** %>29 resume has not been suspended
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine