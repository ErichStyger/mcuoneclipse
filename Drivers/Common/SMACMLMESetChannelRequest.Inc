%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MLMESetChannelRequest)
%;**     Description :
%;**         Set the transceiver operating channel
%include Common\GeneralParameters.inc(27)
%;**         u8Channel%Paru8Channel %>27 - Channel to operate on
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine