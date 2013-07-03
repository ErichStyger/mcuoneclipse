%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskGetTickCountFromISR)
%;**     Description :
%;**         A version of xTaskGetTickCount() that can be called from an
%;**         ISR. 
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - The count of ticks since
%;** %>29 vTaskStartScheduler was called. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine