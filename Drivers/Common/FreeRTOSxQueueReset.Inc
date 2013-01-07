%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueReset)
%;**     Description :
%;**         Reset a queue back to its original empty state.  pdPASS is
%;**         returned if the queue is successfully reset.  pdFAIL is
%;**         returned if the queue could not be reset because there are
%;**         tasks blocked on the queue waiting to either receive from
%;**         the queue or send to the queue.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue to reset.
%;**     Returns     :
%;**         ---%RetVal %>27 - pdPASS is returned if the queue is
%;** %>29 successfully reset. pdFAIL is returned if
%;** %>29 the queue could not be reset because there
%;** %>29 are tasks blocked on the queue waiting to
%;** %>29 either receive from the queue or send to
%;** %>29 the queue.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine