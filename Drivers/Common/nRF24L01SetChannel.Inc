%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetChannel)
%;**     Description :
%;**         Sets the radio channel (RF_CH register).
%include Common\GeneralParameters.inc(27)
%;**         channel%Parchannel %>27 - Channel number, valid channel
%;** %>29 numbers are 0x0 to 0x7F
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine