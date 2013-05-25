%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanDevice)
%;**     Description :
%;**         Checks if a device responds on the bus with an ACK.
%include Common\GeneralParameters.inc(27)
%;**         i2cAddr%Pari2cAddr %>27 - 7bit I2C device address
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine