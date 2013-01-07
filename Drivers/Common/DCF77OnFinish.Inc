%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnFinish)
%;**     Description :
%;**         Event generated once we have a complete date/time record.
%include Common\GeneralParameters.inc(27)
%;**       * time%Partime %>27 - Pointer to the time scanned from the
%;** %>29 DCF77 signal.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine