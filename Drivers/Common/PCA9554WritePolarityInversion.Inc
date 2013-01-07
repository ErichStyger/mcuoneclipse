%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WritePolarityInversion)
%;**     Description :
%;**         Writes the polarity inversion register.
%;**         This register allows the user to invert the polarity of the
%;**         Input Port register data. If a bit in
%;**         this register is set (written with ‘1’), the corresponding
%;**         Input Port data is inverted. If a bit in
%;**         this register is cleared (written with a ‘0’), the Input
%;**         Port data polarity is retained.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - register value
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine