%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetResolution)
%;**     @brief
%;**          
%include Common\GeneralParameters.inc(27)
%;**         @param
%;**         uint8_t config_bits%>27 - Two bits resolution config value: \<br\>\<b\>0b00\</b\> 
%;**         %>29 - 9 bits.\<br\>\<b\>0b01\</b\> - 10 bits.\<br\>\<b\>0b10\</b\> 
%;**         %>29 - 11 bits.\<br\>\<b\>0b11\</b\> - 12 bits. 
%;**         @param
%;**         uint8_t sensor_index%>27 - Index of the sensor to set the resolution. 
%;**         @return
%;**         bool %>27 - 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
