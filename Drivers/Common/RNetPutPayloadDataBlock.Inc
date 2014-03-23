%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PutPayloadDataBlock)
%;**     Description :
%;**         Send an application payload data block.
%include Common\GeneralParameters.inc(27)
%;**       * appPayload%ParappPayload %>27 - Pointer to 
%;**         appPayloadSize%ParappPayloadSize %>27 - 
%;**         msgType%ParmsgType %>27 - 
%;**         dstAddr%PardstAddr %>27 - 
%;**         flags%Parflags %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine