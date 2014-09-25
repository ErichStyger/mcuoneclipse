%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Waitms)
%;**     @brief
%;**         Programs a pause between instruccions. 
%include Common\GeneralParameters.inc(27)
%;**         @param
%;**         uint8_t key%>27 - Key to identificate the period end, applies 
%;**         %>29 only if OnWaitEnd evet is enabled.  (Valid 
%;**         %>29 range 0 - 31) 
%;**         @param
%;**         uint16_t time_ms%>27 - Value of time to wait. 
%;**         @return
%;**         bool %>27 - Returns false if the program buffer or the time buffer 
%;**         is full. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
