%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetAddress)
%;**     Description :
%;**         Sets the I2C address of the device to communicate with. The
%;**         address will be stored in a global variable in the component..
%;**         Disable this method if you do not need it.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Device address (to be added to the base
%;** %>29 address), i.e. starts with zero.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine