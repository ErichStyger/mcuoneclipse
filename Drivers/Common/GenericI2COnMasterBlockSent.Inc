%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnMasterBlockSent)
%;**     Description :
%;**         This event is called when I2C in master mode finishes the
%;**         transmission of the data successfully. This event is not
%;**         available for the SLAVE mode and if MasterSendBlock is
%;**         disabled. 
%include Common\GeneralParameters.inc(27)
%;**       * UserDataPtr%ParUserDataPtr %>27 - Pointer to the user or
%;** %>29 RTOS specific data. This pointer is passed
%;** %>29 as the parameter of Init method.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
