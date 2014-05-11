%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetFifoStatus)
%;**     Description :
%;**         Returns the FIFO_STATUS register value
%include Common\GeneralParameters.inc(27)
%;**       * status%Parstatus %>27 - Pointer to where to store the FIFO
%;** %>29 status value.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine