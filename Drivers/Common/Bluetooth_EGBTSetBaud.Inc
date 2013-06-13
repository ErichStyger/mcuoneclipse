%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetBaud)
%;**     Description :
%;**         Sets the baud rate of the device.
%include Common\GeneralParameters.inc(27)
%;**         baud%Parbaud %>27 - 1200, 2400, 4800, 9600, 19200, 38400,
%;** %>29 57600, 115200
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine