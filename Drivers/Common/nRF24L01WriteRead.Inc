%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteRead)
%;**     Description :
%;**         Writes a byte and reads back one byte
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - Value to write to the bus
%;**     Returns     :
%;**         ---%RetVal %>27 - Value read from the bus
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine