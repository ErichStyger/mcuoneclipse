%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetEvent)
%;**     Description :
%;**         Sets an event (number) be processed by the next HandleEvent()
%;**         call
%include Common\GeneralParameters.inc(27)
%;**         event%Parevent %>27 - The event (number) to be set so it
%;** %>29 will be called by the HandleEvent() routine
%;** %>29 later on. Note that there cannot be
%;** %>29 multiple instances of an event, and the
%;** %>29 lower the event number, the higher the
%;** %>29 priority.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine