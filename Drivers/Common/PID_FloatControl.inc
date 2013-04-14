%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Control)
%;**     Description :
%;**         Control function. Must be called every T time. 
%include Common\GeneralParameters.inc(27)
%;**         float error%>27 - Error signal. (Reference - SystemOutput). 
%;**         uint16_t u%>27 - Pointer to the control variable. 
%;**     Returns     :
%;**         void %>27 - 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
