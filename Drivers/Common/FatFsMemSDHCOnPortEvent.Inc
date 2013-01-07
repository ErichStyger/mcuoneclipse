%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnPortEvent)
%;**     Description :
%;**         Called if defined event on any pin of the port occured.
%;**         OnPortEvent event and GPIO interrupt must be enabled. See
%;**         SetPortEventMask() and GetPortEventMask() methods. 
%include Common\GeneralParameters.inc(27)
%;**       * UserDataPtr%ParUserDataPtr %>27 - Pointer to RTOS device
%;** %>29 data structure pointer.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine