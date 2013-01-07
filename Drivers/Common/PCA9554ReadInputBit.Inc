%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadInputBit)
%;**     Description :
%;**         Reads a bit from the input register.
%include Common\GeneralParameters.inc(27)
%;**         bitNo%ParbitNo %>27 - Bit number, starting with 0
%;**     Returns     :
%;**         ---%RetVal %>27 - zero if bit is cleared, non-zero otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine