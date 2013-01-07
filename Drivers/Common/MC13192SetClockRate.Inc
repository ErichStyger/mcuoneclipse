%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetClockRate)
%;**     Description :
%;**         Set the CLKO frequency
%include Common\GeneralParameters.inc(27)
%;**         u8Freq%Paru8Freq %>27 - frequency to be used. 0 = 16 MHz, 1
%;** %>29 = 8 MHz, 2 = 4 MHz, 3 = 2 MHz, 4 = 1 MHz, 5
%;** %>29 = 62.5 kHz, 6 = 32.768+ kHz, 7 = 16.393+ kHz
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine