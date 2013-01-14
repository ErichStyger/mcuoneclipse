%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetPairingPasskey)
%;**     Description :
%;**         Sets the pairing passkey
%include Common\GeneralParameters.inc(27)
%;**       * pwd%Parpwd %>27 - Pointer to new pairing passkey
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine