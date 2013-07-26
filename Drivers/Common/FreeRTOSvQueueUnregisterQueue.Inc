%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vQueueUnregisterQueue)
%;**     Description :
%;**         Removes a queue from the queue registry. 
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue being
%;** %>29 removed from the registry.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine