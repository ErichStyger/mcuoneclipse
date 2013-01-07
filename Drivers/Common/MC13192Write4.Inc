%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Write4)
%;**     Description :
%;**         Writes 32bit (dword) data to the transceiver. The data is in
%;**         big endian format, and it writes it to the transceiver
%;**         (which has little endian memory layout).
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Transceiver start address where to write
%;** %>29 the data.
%;**         val%Parval %>27 - Value to write to the register, in big
%;** %>29 endian format.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine