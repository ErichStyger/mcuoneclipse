%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xEventGroupGetBits)
%;**     Description :
%;**         Returns the current value of the event bits (event flags) in
%;**         an RTOS event group. This function cannot be used from an
%;**         interrupt. See xEventGroupsGetBitsFromISR() for a version
%;**         that can be used in an interrupt. 
%include Common\GeneralParameters.inc(27)
%;**         xEventGroup%ParxEventGroup %>27 - The event group being
%;** %>29 queried. The event group must have
%;** %>29 previously been created using a call to
%;** %>29 xEventGroupCreate().
%;**     Returns     :
%;**         ---%RetVal %>27 - The value of the event bits in the event
%;** %>29 group at the time xEventGroupGetBits() was
%;** %>29 called. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine