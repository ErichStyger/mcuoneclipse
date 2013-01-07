%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnFault)
%;**     Description :
%;**         This event is called in case of a fault sensor condition.
%;**         You can disable this event if you are not interested in it
%;**         in order to save code size.
%include Common\GeneralParameters.inc(27)
%;**         reason%Parreason %>27 - reason of fault: 1 for short to VSS
%;** %>29 detected, 2 for short to VDD detected, 3
%;** %>29 for FIFO overflow (see ON_MPR083_FAULT_xxx
%;** %>29 defines).
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine