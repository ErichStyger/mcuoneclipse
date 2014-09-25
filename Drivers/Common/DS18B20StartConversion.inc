%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (StartConversion)
%;**     @brief
%;**         Starts the conversion of temperature in the sensor. 
%include Common\GeneralParameters.inc(27)
%;**         @param
%;**         uint8_t sensor_index%>27 - Index of the sensor to start to convert the 
%;**         %>29 temperature. 
%;**         @return
%;**         bool %>27 - Returns FALSE if the device is busy. 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
