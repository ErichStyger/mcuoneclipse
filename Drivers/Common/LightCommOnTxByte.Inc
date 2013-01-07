%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnTxByte)
%;**     Description :
%;**         Event after having sent a byte.
%include Common\GeneralParameters.inc(27)
%;**         data%Pardata %>27 - The byte we just have sent.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
