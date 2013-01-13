%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MLMEDozeRequest)
%;**     Description :
%;**         Doze the transceiver (low current, CLKO <= 1MHz)
%include Common\GeneralParameters.inc(27)
%;**         u32Timeout%Paru32Timeout %>27 - 32bit timout period
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine