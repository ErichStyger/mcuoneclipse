%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteDataWord)
%;**     Description :
%;**         Writes a single word to the bus
%include Common\GeneralParameters.inc(27)
%;**         data%Pardata %>27 - Word to send
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine