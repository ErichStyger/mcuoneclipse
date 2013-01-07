%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnRx)
%;**     Description :
%;**         Event for having a byte received
%include Common\GeneralParameters.inc(27)
%;**         data%Pardata %>27 - The data byte we have received.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine