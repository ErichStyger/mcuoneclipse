%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MsgSendListRecursiveBottomUp)
%;**     Description :
%;**         Broadcasts recursively events to the elements. It traverses
%;**         the tree list in a recursive way and sends the messages
%;**         bottom-up.
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to element
%;**         kind%Parkind %>27 - 
%;**         pData%ParpData %>27 - 
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine