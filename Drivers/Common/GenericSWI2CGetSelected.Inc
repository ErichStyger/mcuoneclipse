%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetSelected)
%;**     Description :
%;**         When working as a MASTER, this method returns the
%;**         identification address value of the slave, which is
%;**         currently selected for communication with the master. If the
%;**         current slave uses 10-bit slave addressing, the method
%;**         returns the first 7 bits only, which involves 10-bit
%;**         addressing (11110XX), including two MSBs of the slave
%;**         address (XX). This method is not able to return the rest
%;**         value of 10-bit slave address. This method is available only
%;**         if the component is in MASTER mode.
%include Common\GeneralParameters.inc(27)
%;**       * Slv%ParSlv %>27 - A pointer to the current selected slave
%;** %>29 address value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%;** %>29 ERR_SPEED - This device does not work in
%;** %>29 the active speed mode
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine