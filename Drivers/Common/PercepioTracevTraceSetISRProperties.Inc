%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceSetISRProperties)
%;**     Description :
%;**         Registers an Interrupt Service Routine in the recorder
%;**         library, This must be called before using
%;**         vTraceStoreISRBegin to store ISR events. This is typically
%;**         called in the startup of the system, before the scheduler is
%;**         started. Method is always enabled if 'Include ISR tracing'
%;**         is set to 'yes' in the properties.
%include Common\GeneralParameters.inc(27)
%;**         handle%Parhandle %>27 - handle to be used
%;**       * name%Parname %>27 - Pointer to name
%;**         prioritiy%Parprioritiy %>27 - priority
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine