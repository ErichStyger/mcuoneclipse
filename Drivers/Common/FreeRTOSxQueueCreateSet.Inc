%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xQueueCreateSet)
%;**     Description :
%;**         Queue sets provide a mechanism to allow an RTOS task to
%;**         block (pend) on a read operation from multiple RTOS queues
%;**         or semaphores simultaneously. Note that there are simpler
%;**         alternatives to using queue sets. See the Blocking on
%;**         Multiple Objects page for more information.
%include Common\GeneralParameters.inc(27)
%;**         uxEventQueueLength%ParuxEventQueueLength %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - If the queue set is created successfully
%;** %>29 then a handle to the created queue set is
%;** %>29 returned. Otherwise NULL is returned. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine