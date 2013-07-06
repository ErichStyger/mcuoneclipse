%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (vOnPreSleepProcessing)
%;**     Description :
%;**         Used in tickless idle mode only, but required in this mode.
%;**         Hook for the application to enter low power mode.
%include Common\GeneralParameters.inc(27)
%;**         expectedIdleTicks%ParexpectedIdleTicks %>27 - expected idle
%;** %>29 time, in ticks
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine