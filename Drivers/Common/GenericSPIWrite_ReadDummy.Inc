%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Write_ReadDummy)
%;**     Description :
%;**         Writes a value to the SPI bus and ignores the value read
%;**         back from the bus.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - The value to be shifted to the bus.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
