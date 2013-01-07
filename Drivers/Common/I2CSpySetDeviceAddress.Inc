%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetDeviceAddress)
%;**     Description :
%;**         Sets the I2C Device address to be used
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - I2C 7bit address
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine