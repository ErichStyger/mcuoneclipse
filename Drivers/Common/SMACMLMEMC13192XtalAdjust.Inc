%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MLMEMC13192XtalAdjust)
%;**     Description :
%;**         Adjust the transceiver crystal trim value
%include Common\GeneralParameters.inc(27)
%;**         u8ReqValue%Paru8ReqValue %>27 - Trim Value (0-255)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine