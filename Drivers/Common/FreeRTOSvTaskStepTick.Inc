%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskStepTick)
%;**     Description :
%;**          If the RTOS is configured to use tickless idle
%;**         functionality then the tick interrupt will be stopped, and
%;**         the microcontroller placed into a low power state, whenever
%;**         the Idle task is the only task able to execute. Upon exiting
%;**         the low power state the tick count value must be corrected
%;**         to account for the time that passed while it was stopped.
%;**         If a FreeRTOS port includes a default
%;**         portSUPPRESS_TICKS_AND_SLEEP() implementation, then
%;**         vTaskStepTick() is used internally to ensure the correct
%;**         tick count value is maintained. vTaskStepTick() is a public
%;**         API function to allow the default
%;**         portSUPPRESS_TICKS_AND_SLEEP() implementation to be
%;**         overridden, and for a portSUPPRESS_TICKS_AND_SLEEP() to be
%;**         provided if the port being used does not provide a default. 
%include Common\GeneralParameters.inc(27)
%;**         xTicksToJump%ParxTicksToJump %>27 - The number of RTOS ticks
%;** %>29 that have passed since the tick interrupt
%;** %>29 was stopped. For correct operation the
%;** %>29 parameter must be less than or equal to the
%;** %>29 portSUPPRESS_TICKS_AND_SLEEP() parameter. 
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine