%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xEventGroupSetBits)
%;**     Description :
%;**          Set bits (flags) within an RTOS event group. This function
%;**         cannot be called from an interrupt.
%;**         xEventGroupSetBitsFromISR() is a version that can be called
%;**         from an interrupt.
%;**         Setting bits in an event group will automatically unblock
%;**         tasks that are blocked waiting for the bits. 
%include Common\GeneralParameters.inc(27)
%;**         xEventGroup%ParxEventGroup %>27 - The event group in which
%;** %>29 the bits are to be set. The event group
%;** %>29 must have previously been created using a
%;** %>29 call to xEventGroupCreate(). 
%;**         uxBitsToSet%ParuxBitsToSet %>27 - A bitwise value that
%;** %>29 indicates the bit or bits to set in the
%;** %>29 event group. For example, set uxBitsToSet
%;** %>29 to 0x08 to set only bit 3. Set uxBitsToSet
%;** %>29 to 0x09 to set bit 3 and bit 0. 
%;**     Returns     :
%;**         ---%RetVal %>27 - The value of the event group at the time
%;** %>29 the call to xEventGroupSetBits() returns.
%;** %>29 There are two reasons why the returned
%;** %>29 value might have the bits specified by the
%;** %>29 uxBitsToSet parameter cleared:
%;** %>29 If setting a bit results in a task that was
%;** %>29 waiting for the bit leaving the blocked
%;** %>29 state then it is possible the bit will have
%;** %>29 been cleared automatically (see the
%;** %>29 xClearBitOnExit parameter of
%;** %>29 xEventGroupWaitBits()).
%;** %>29 Any unblocked (or otherwise Ready state)
%;** %>29 task that has a priority above that of the
%;** %>29 task that called xEventGroupSetBits() will
%;** %>29 execute and may change the event group
%;** %>29 value before the call to
%;** %>29 xEventGroupSetBits() returns.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine