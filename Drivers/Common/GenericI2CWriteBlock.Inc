%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteBlock)
%;**     Description :
%;**         Write a block to the device.
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Data write buffer
%;**         dataSize%PardataSize %>27 - 
%;**         flags%Parflags %>27 - flags for the transaction
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine