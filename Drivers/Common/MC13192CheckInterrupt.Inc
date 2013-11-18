%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CheckInterrupt)
%;**     Description :
%;**         Needs to be called after interrupt received from the
%;**         transceiver to check the state and to create the events.
%include Common\GeneralParameters.inc(27)
%;**         dataIndicationCallback%PardataIndicationCallback %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine