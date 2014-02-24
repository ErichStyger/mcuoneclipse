%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xEventGroupCreate)
%;**     Description :
%;**          Create a new RTOS event group. This function cannot be
%;**         called from an interrupt.
%;**         Event groups are stored in variables of type
%;**         EventGroupHandle_t. The number of bits (or flags)
%;**         implemented within an event group is 8 if
%;**         configUSE_16_BIT_TICKS is set to 1, or 24 if
%;**         configUSE_16_BIT_TICKS is set to 0. The dependency on
%;**         configUSE_16_BIT_TICKS results from the data type used for
%;**         thread local storage in the internal implementation of RTOS
%;**         tasks. 
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Event Group Handle. If the event group was
%;** %>29 created then a handle to the event group is
%;** %>29 returned. If there was insufficient
%;** %>29 FreeRTOS heap available to create the event
%;** %>29 group then NULL is returned. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine