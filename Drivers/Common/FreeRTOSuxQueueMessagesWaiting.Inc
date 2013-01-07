%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (uxQueueMessagesWaiting)
%;**     Description :
%;**         Queries the number of items that are currently held within a
%;**         queue.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue being
%;** %>29 queried.
%;**     Returns     :
%;**         ---%RetVal %>27 - The number of items that are held within
%;** %>29 the queue being queried.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine