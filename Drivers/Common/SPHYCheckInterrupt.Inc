%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CheckInterrupt)
%;**     Description :
%;**         Called after an interrupt to check if there is any data.
%include Common\GeneralParameters.inc(27)
%;**       * sRxPacket%ParsRxPacket %>27 - Pointer to receiving data
%;** %>29 structure
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine