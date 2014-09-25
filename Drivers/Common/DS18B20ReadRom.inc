%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadRom)
%;**     @brief
%;**         Starts to read the rom code and saves it in memory. 
%include Common\GeneralParameters.inc(27)
%;**         @param
%;**         uint8_t sensor_index%>27 -  
%;**         @return
%;**         bool %>27 - Returns FALSE if the device is busy in another operation. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
