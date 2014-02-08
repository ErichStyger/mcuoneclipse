%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ProbeACK)
%;**     Description :
%;**         Accesses the bus to check if the device responds with an ACK
%;**         (ACK polling).
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Data write buffer
%;**         dataSize%PardataSize %>27 - 
%;**         flags%Parflags %>27 - flags for the transaction
%;**         WaitTimeUS%ParWaitTimeUS %>27 - Waiting time in microseconds
%;** %>29 to wait for the ACK on the bus.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine