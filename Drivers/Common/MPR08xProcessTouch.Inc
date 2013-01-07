%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ProcessTouch)
%;**     Description :
%;**         Reads the sensor data and dispatches it to the corresponding
%;**         events. If the interrupts are enabled, this method is called
%;**         automatically in the interrupt service routine. Otherwise
%;**         you have to call this function from your application in
%;**         order to read the sensor (instantaneous mode).
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine