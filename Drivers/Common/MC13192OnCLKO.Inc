%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnCLKO)
%;**     Description :
%;**         Event called when CLKO changes
%include Common\GeneralParameters.inc(27)
%;**         freq%Parfreq %>27 - Frequency value. 0 for 16 MHz, 1 for 8
%;** %>29 MHz, 2 for 4 MHz, 3 for 2 MHz, 4 for 1 MHz,
%;** %>29 5 for 62.5 kHz, 6 for 32.786 kHz, 7 for 16.
%;** %>29 393 kHz
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine