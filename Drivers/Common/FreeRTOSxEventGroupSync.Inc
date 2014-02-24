%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xEventGroupSync)
%;**     Description :
%;**          Atomically set bits (flags) within an RTOS event group,
%;**         then wait for a combination of bits to be set within the
%;**         same event group. This functionality is typically used to
%;**         synchronise multiple tasks (often called a task rendezvous),
%;**         where each task has to wait for the other tasks to reach a
%;**         synchronisation point before proceeding.
%;**         This function cannot be used from an interrupt.
%;**         The function will return before its block time expires if
%;**         the bits specified by the uxBitsToWait parameter are set, or
%;**         become set within that time. In this case all the bits
%;**         specified by uxBitsToWait will be automatically cleared
%;**         before the function returns. 
%include Common\GeneralParameters.inc(27)
%;**         xEventGroup%ParxEventGroup %>27 - The event group in which
%;** %>29 the bits are being set and tested. The
%;** %>29 event group must have previously been
%;** %>29 created using a call to xEventGroupCreate().
%;**         uxBitsToSet%ParuxBitsToSet %>27 - The bit or bits to set in
%;** %>29 the event group before determining if (and
%;** %>29 possibly waiting for), all the bits
%;** %>29 specified by the uxBitsToWait parameter are
%;** %>29 set. For example, set uxBitsToSet to 0x04
%;** %>29 to set bit 2 within the event group. 
%;**         uxBitsToWaitFor%ParuxBitsToWaitFor %>27 - A bitwise value
%;** %>29 that indicates the bit or bits to test
%;** %>29 inside the event group. For example, set
%;** %>29 uxBitsToWaitFor to 0x05 to wait for bits 0
%;** %>29 and bit 2. Set uxBitsToWaitFor to 0x07 to
%;** %>29 wait for bit 0 and bit 1 and bit 2. Etc. 
%;**         xTicksToWait%ParxTicksToWait %>27 - The maximum amount of
%;** %>29 time (specified in 'ticks') to wait for all
%;** %>29 the bits specified by the uxBitsToWaitFor
%;** %>29 parameter value to become set. 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine