%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (RecvChar)
%;**     Description :
%;**         Receives a character from the Bluetooth serial bridge
%include Common\GeneralParameters.inc(27)
%;**       * ch%Parch %>27 - Pointer to character buffer
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine