%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskResumeAll)
%;**     Description :
%;**         Resumes real time kernel activity following a call to
%;**         vTaskSuspendAll (). After a call to xTaskSuspendAll () the
%;**         kernel will take control of which task is executing at any
%;**         time.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - If resuming the scheduler caused a context
%;** %>29 switch then pdTRUE is returned, otherwise
%;** %>29 pdFALSE is returned.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine