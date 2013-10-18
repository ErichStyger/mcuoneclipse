%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (EnableAutoAck)
%;**     Description :
%;**         Enables Auto-Acknowledgment for the given pipe(s) (RF_EN_AA
%;**         register).
%include Common\GeneralParameters.inc(27)
%;**         pipes%Parpipes %>27 - mask of pipes to be enabled (ENAA_P0
%;** %>29 to ENAA_P5)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine