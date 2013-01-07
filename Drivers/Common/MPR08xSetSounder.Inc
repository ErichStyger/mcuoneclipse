%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetSounder)
%;**     Description :
%;**         Configures the sounder/buzzer at runtime. Do NOT call this
%;**         function inside ProcessTouch().
%include Common\GeneralParameters.inc(27)
%;**         enable%Parenable %>27 - If sounder shall be enabled or not.
%;**         clickPeriod%ParclickPeriod %>27 - The click period controls
%;** %>29 the length of the sounder click. 0 gives a
%;** %>29 10 ms period, and 1 gives a 20 ms click
%;** %>29 period.
%;**         frequency%Parfrequency %>27 - Controls the frequency of the
%;** %>29 driven output. A value of 0 gives 1 kHz,
%;** %>29 and 1 gives 2 kHz
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine