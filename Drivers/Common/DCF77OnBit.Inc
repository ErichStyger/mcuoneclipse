%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnBit)
%;**     Description :
%;**         Event which can be called on every bit we scan in. Useful
%;**         for custom decoding of bit stream.
%include Common\GeneralParameters.inc(27)
%;**         bit%Parbit %>27 - The value of the bit (one or zero).
%;**         bitNumber%ParbitNumber %>27 - The bit number (0..59)
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine