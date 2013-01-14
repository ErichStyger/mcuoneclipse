%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetUserPinIO)
%;**     Description :
%;**         Sets or clears a user I/O pin
%include Common\GeneralParameters.inc(27)
%;**         portNumber%ParportNumber %>27 - Portnumer, available port
%;** %>29 numbers are 2, 3, 4, 5, 6, 7 and 10.
%;**         on%Paron %>27 - If port is on (logic high) or off (logic
%;** %>29 low)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine