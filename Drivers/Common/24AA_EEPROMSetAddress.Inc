%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetAddress)
%;**     Description :
%;**         Configures the I2C address to be used for the memory. With
%;**         this multiple devices attached to the bus can be addressed.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address of the memory device.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine