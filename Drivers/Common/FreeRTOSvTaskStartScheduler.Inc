%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskStartScheduler)
%;**     Description :
%;**         Starts the real time kernel tick processing. After calling
%;**         the kernel has control over which tasks are executed and
%;**         when.
%;**         The idle task is created automatically when
%;**         vTaskStartScheduler() is called.
%;**         If vTaskStartScheduler() is successful the function will not
%;**         return until an executing task calls vTaskEndScheduler().
%;**         The function might fail and return immediately if there is
%;**         insufficient RAM available for the idle task to be created.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine