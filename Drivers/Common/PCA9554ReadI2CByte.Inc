%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadI2CByte)
%;**     Description :
%;**         Reads a byte from the I2C device at the given register
%;**         address.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Device register address
%;**       * chp%Parchp %>27 - Pointer to byte where to store the value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine