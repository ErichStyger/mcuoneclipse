%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Read2)
%;**     Description :
%;**         Read the second word from the transceiver.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Address in the transceiver to read from.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine