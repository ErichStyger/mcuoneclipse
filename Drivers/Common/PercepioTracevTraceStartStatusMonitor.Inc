%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceStartStatusMonitor)
%;**     Description :
%;**         This starts a task to monitor the state of the recorder.
%;**         This task periodically prints a line to the console window,
%;**         which shows the number of events recorded and the latest
%;**         timestamp. This task calls vTracePortEnd when the recorder
%;**         has been stopped, where custom actions can be added, e.g.,
%;**         to store the trace to a file if a file system is available
%;**         on the device.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine