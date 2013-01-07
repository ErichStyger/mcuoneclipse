%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskEndScheduler)
%;**     Description :
%;**         Stops the real time kernel tick. All created tasks will be
%;**         automatically deleted and multitasking (either preemptive or
%;**         cooperative) will stop. Execution then resumes from the
%;**         point where vTaskStartScheduler() was called, as if
%;**         vTaskStartScheduler() had just returned.
%;**         See the demo application file main. c in the demo/PC
%;**         directory for an example that uses vTaskEndScheduler ().
%;**         vTaskEndScheduler () requires an exit function to be defined
%;**         within the portable layer (see vPortEndScheduler () in port.
%;**         c for the PC port). This performs hardware specific
%;**         operations such as stopping the kernel tick.
%;**         vTaskEndScheduler () will cause all of the resources
%;**         allocated by the kernel to be freed - but will not free
%;**         resources allocated by application tasks.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine