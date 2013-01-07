%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (uxQueueMessagesWaitingfromISR)
%;**     Description :
%;**         A version of uxQueueMessagesWaiting() that can be used from
%;**         inside an interrupt service routine.
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