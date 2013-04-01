%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetRaw8XYZ)
%;**     Description :
%;**         Returns in an array the x, y and z accelerometer as 8bit values. 
%include Common\GeneralParameters.inc(27)
%;**         uint8_t xyz%>27 - Pointer to an array of three unsigned 8bit 
%;**         %>29 values which are used to return the accelerometer 
%;**         %>29 values. 
%;**     Returns     :
%;**         uint8_t %>27 - 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
