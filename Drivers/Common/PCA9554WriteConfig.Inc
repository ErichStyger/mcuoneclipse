%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteConfig)
%;**     Description :
%;**         Writes the configuration register.
%;**         This register configures the directions of the I/O pins. If
%;**         a bit in this register is set, the
%;**         corresponding port pin is enabled as an input with
%;**         high-impedance output driver. If a bit in
%;**         this register is cleared, the corresponding port pin is
%;**         enabled as an output. At reset, the
%;**         I/Os are configured as inputs with a weak pull-up to VDD.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - register value
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine