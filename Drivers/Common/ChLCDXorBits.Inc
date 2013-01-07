%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (XorBits)
%;**     Description :
%;**         XOR's bits on the display
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - display memory address
%;**         mask%Parmask %>27 - mask of bits to XOR
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine