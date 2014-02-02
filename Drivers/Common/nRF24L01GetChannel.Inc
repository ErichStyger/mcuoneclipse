%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetChannel)
%;**     Description :
%;**         Returns the radio channel (RF_CH register).
%include Common\GeneralParameters.inc(27)
%;**       * channel%Parchannel %>27 - Pointer to where to store the
%;** %>29 channel number.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine