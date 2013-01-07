%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SelectDevice)
%;**     Description :
%;**         Configures the I2C address to be used for the memory. With
%;**         this multiple devices attached to the bus can be addressed.
%include Common\GeneralParameters.inc(27)
%;**         addrI2C%ParaddrI2C %>27 - I2C Address of the memory device,
%;** %>29 formed by the address pins.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%;** %>29 ERR_VALUE - address exceeds address pins of
%;** %>29 device type used
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine