%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueCreate)
%;**     Description :
%;**         Creates a queue.
%include Common\GeneralParameters.inc(27)
%;**         uxQueueLength%ParuxQueueLength %>27 - The maximum number of
%;** %>29 items the queue can hold at any time.
%;**         uxItemSize%ParuxItemSize %>27 - The size in bytes of each
%;** %>29 item the queue will hold.
%;**     Returns     :
%;**         ---%RetVal %>27 - A handle to the created queue is returned
%;** %>29 provided the queue was created successfully.
%;** %>29 NULL is returned if the queue cannot be
%;** %>29 created because there is too little heap
%;** %>29 RAM available.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine