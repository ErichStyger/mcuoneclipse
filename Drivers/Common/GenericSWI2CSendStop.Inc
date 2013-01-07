%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendStop)
%;**     Description :
%;**         When working as a MASTER, if the 'Automatic stop condition'
%;**         property value is 'no', this method sends a valid stop
%;**         condition to the serial data line of the I2C bus to
%;**         terminate the communication on the bus after using send
%;**         methods. This method is enabled only if the component is in
%;**         MASTER mode and 'Automatic stop condition' property value is
%;**         'no'
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%;** %>29 ERR_SPEED - This device does not work in
%;** %>29 the active speed mode
%;** %>29 ERR_DISABLED - Device is disabled
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine