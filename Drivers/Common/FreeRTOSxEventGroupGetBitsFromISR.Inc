%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xEventGroupGetBitsFromISR)
%;**     Description :
%;**         A version of xEventGroupGetBits() that can be called from an
%;**         interrupt. 
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