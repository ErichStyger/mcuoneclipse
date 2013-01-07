%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskCreate)
%;**     Description :
%;**         Create a new task and add it to the list of tasks that are
%;**         ready to run.
%include Common\GeneralParameters.inc(27)
%;**         pvTaskCode%ParpvTaskCode %>27 - Pointer to the task entry
%;** %>29 function. Tasks must be implemented to
%;** %>29 never return (i.e. continuous loop).
%;**         pcName%ParpcName %>27 - A descriptive name for the task.
%;** %>29 This is mainly used to facilitate debugging.
%;** %>29 Max length defined by
%;** %>29 configMAX_TASK_NAME_LEN.
%;**         usStackDepth%ParusStackDepth %>27 - The size of the task
%;** %>29 stack specified as the number of variables
%;** %>29 the stack can hold - not the number of
%;** %>29 bytes. For example, if the stack is 16 bits
%;** %>29 wide and usStackDepth is defined as 100,
%;** %>29 200 bytes will be allocated for stack
%;** %>29 storage. The stack depth multiplied by the
%;** %>29 stack width must not exceed the maximum
%;** %>29 value that can be contained in a variable
%;** %>29 of type size_t.
%;**         pvParameters%ParpvParameters %>27 - Pointer that will be
%;** %>29 used as the parameter for the task being
%;** %>29 created.
%;**         uxPriority%ParuxPriority %>27 - The priority at which the
%;** %>29 task should run.
%;**         pvCreatedTask%ParpvCreatedTask %>27 - Used to pass back a
%;** %>29 handle by which the created task can be
%;** %>29 referenced.
%;**     Returns     :
%;**         ---%RetVal %>27 - pdPASS if the task was successfully
%;** %>29 created and added to a ready list,
%;** %>29 otherwise an error code defined in the file
%;** %>29 projdefs.h
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine