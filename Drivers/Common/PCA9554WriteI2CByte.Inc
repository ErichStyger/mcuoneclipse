%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteI2CByte)
%;**     Description :
%;**         Writes a byte to the I2C device at the given register
%;**         address.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - device register
%;**         ch%Parch %>27 - value to write
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine