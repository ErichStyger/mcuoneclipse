%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xEventGroupWaitBits)
%;**     Description :
%;**          Read bits within an RTOS event group, optionally entering
%;**         the Blocked state (with a timeout) to wait for a bit or
%;**         group of bits to become set. This function cannot be called
%;**         from an interrupt. 
%include Common\GeneralParameters.inc(27)
%;**         xEventGroup%ParxEventGroup %>27 - The event group in which
%;** %>29 the bits are being tested. The event group
%;** %>29 must have previously been created using a
%;** %>29 call to xEventGroupCreate(). 
%;**         uxBitsToWaitFor%ParuxBitsToWaitFor %>27 - A bitwise value
%;** %>29 that indicates the bit or bits to test
%;** %>29 inside the event group. For example, to
%;** %>29 wait for bit 0 and/or bit 2 set
%;** %>29 uxBitsToWaitFor to 0x05. To wait for bits 0
%;** %>29 and/or bit 1 and/or bit 2 set
%;** %>29 uxBitsToWaitFor to 0x07. Etc.
%;** %>29 uxBitsToWaitFor must not be set to 0. 
%;**         xClearOnExit%ParxClearOnExit %>27 - If xClearOnExit is set
%;** %>29 to pdTRUE then any bits set in the value
%;** %>29 passed as the uxBitsToWaitFor parameter
%;** %>29 will be cleared in the event group before
%;** %>29 xEventGroupWaitBits() returns if
%;** %>29 xEventGroupWaitBits() returns for any
%;** %>29 reason other than a timeout. The timeout
%;** %>29 value is set by the xTicksToWait parameter.
%;** %>29 If xClearOnExit is set to pdFALSE then the
%;** %>29 bits set in the event group are not altered
%;** %>29 when the call to xEventGroupWaitBits()
%;** %>29 returns. 
%;**         xWaitForAllBits%ParxWaitForAllBits %>27 - xWaitForAllBits is
%;** %>29 used to create either a logical AND test
%;** %>29 (where all bits must be set) or a logical
%;** %>29 OR test (where one or more bits must be set)
%;** %>29 as follows:
%;** %>29 If xWaitForAllBits is set to pdTRUE then
%;** %>29 xEventGroupWaitBits() will return when
%;** %>29 either all the bits set in the value passed
%;** %>29 as the uxBitsToWaitFor parameter are set in
%;** %>29 the event group or the specified block time
%;** %>29 expires.
%;** %>29 If xWaitForAllBits is set to pdFALSE then
%;** %>29 xEventGroupWaitBits() will return when any
%;** %>29 of the bits set in the value passed as the
%;** %>29 uxBitsToWaitFor parameter are set in the
%;** %>29 event group or the specified block time
%;** %>29 expires. 
%;**         xTicksToWait%ParxTicksToWait %>27 - The maximum amount of
%;** %>29 time (specified in 'ticks') to wait for
%;** %>29 one/all (depending on the xWaitForAllBits
%;** %>29 value) of the bits specified by
%;** %>29 uxBitsToWaitFor to become set. 
%;**     Returns     :
%;**         ---%RetVal %>27 - EventBits_t: The value of the event group
%;** %>29 at the time either the event bits being
%;** %>29 waited for became set, or the block time
%;** %>29 expired. The current value of the event
%;** %>29 bits in an event group will be different to
%;** %>29 the returned value if a higher priority
%;** %>29 task or interrupt changed the value of an
%;** %>29 event bit between the calling task leaving
%;** %>29 the Blocked state and exiting the
%;** %>29 xEventGroupWaitBits() function.
%;** %>29 Test the return value to know which bits
%;** %>29 were set. If xEventGroupWaitBits() returned
%;** %>29 because its timeout expired then not all
%;** %>29 the bits being waited for will be set. If
%;** %>29 xEventGroupWaitBits() returned because the
%;** %>29 bits it was waiting for were set then the
%;** %>29 returned value is the event group value
%;** %>29 before any bits were automatically cleared
%;** %>29 because the xClearOnExit parameter was set
%;** %>29 to pdTRUE. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine