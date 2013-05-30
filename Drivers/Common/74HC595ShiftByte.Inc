%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ShiftByte)
%;**     Description :
%;**         Shift a byte to the shift register. The most significant bit
%;**         will be on output pin 0. Use Latch() to show the data on the
%;**         output pins.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - 8bit value to be shifted
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine