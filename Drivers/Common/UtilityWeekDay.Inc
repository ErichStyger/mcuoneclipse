%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WeekDay)
%;**     Description :
%;**         Returns the weekday for a given date >= 1.Jan.1900
%include Common\GeneralParameters.inc(27)
%;**         year%Paryear %>27 - year in YYYY format
%;**         month%Parmonth %>27 - month of the year (1: January, 2:
%;** %>29 February, etc)
%;**         day%Parday %>27 - day of the moth (starting with 1)
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns the weekday, 0 for Sunday, 1 for
%;** %>29 Monday, 2 for Tuesday, etc.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine