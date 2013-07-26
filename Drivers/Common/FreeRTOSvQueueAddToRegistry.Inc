%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vQueueAddToRegistry)
%;**     Description :
%;**         Assigns a name to a queue and adds the queue to the registry.
%include Common\GeneralParameters.inc(27)
%;**         xQueue%ParxQueue %>27 - The handle of the queue being added
%;** %>29 to the registry.
%;**       * pcQueueName%ParpcQueueName %>27 - Pointer to the name to be
%;** %>29 assigned to the queue. This is just a text
%;** %>29 string used to facilitate debugging.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine