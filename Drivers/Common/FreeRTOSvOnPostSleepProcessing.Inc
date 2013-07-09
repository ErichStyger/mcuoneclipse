%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (vOnPostSleepProcessing)
%;**     Description :
%;**         Event called after the CPU woke up after low power mode.
%;**         This event is optional.
%include Common\GeneralParameters.inc(27)
%;**         expectedIdleTicks%ParexpectedIdleTicks %>27 - expected idle
%;** %>29 time, in ticks
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine