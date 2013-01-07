%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SelectSlave)
%;**     Description :
%;**         When working as a MASTER, this method selects a new slave
%;**         for communication by its slave address value. Any send or
%;**         receive method are directed to or from the selected device,
%;**         until a new slave device is selected by this method. If the
%;**         selected slave uses 10-bit slave addressing, as the
%;**         parameter 7 bits must be passed, which involves 10-bit
%;**         addressing (11110XX), including two MSBs of slave address
%;**         (XX). The second byte of the 10-bit slave address must be
%;**         sent to the slave as a general character of send methods.
%;**         This method is available only if the component is in MASTER
%;**         mode.
%include Common\GeneralParameters.inc(27)
%;**         Slv%ParSlv %>27 - Slave address value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%;** %>29 ERR_SPEED - This device does not work in
%;** %>29 the active speed mode
%;** %>29 ERR_DISABLED -  Device is disabled
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine