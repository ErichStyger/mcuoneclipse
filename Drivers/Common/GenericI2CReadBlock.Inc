%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadBlock)
%;**     Description :
%;**         Read from the device a block.
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Read buffer
%;**         dataSize%PardataSize %>27 - Size of read buffer
%;**         flags%Parflags %>27 - flags for the transaction
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine