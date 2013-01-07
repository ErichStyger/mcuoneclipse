%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SelectSlave)
%;**     Description :
%;**         Selects the slave device on the bus.
%include Common\GeneralParameters.inc(27)
%;**         i2cAddr%Pari2cAddr %>27 - I2C Address of device
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine