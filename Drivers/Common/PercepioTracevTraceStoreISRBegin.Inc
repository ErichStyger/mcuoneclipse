%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceStoreISRBegin)
%;**     Description :
%;**         Registers the beginning of an Interrupt Service Routine.
%;**         This must not be interrupted by another ISR containing
%;**         recorder library calls, so if allowing nested ISRs this must
%;**         be called with interrupts disabled.  Method is always
%;**         enabled if 'Include ISR tracing' is set to 'yes' in the
%;**         properties.
%include Common\GeneralParameters.inc(27)
%;**         id%Parid %>27 - ID of the ISR
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine