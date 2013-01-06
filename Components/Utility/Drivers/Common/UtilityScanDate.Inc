%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanDate)
%;**     Description :
%;**         Scans a date in the format "dd.mm.yyyy" or "dd-mm-yyyy". For
%;**         yy it will expand it to 20yy.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to the string to be scanned. The
%;** %>29 function advances the pointer.
%;**       * day%Parday %>27 - Pointer to where to store the day value
%;**       * month%Parmonth %>27 - Pointer to where to store the month
%;** %>29 value
%;**       * year%Paryear %>27 - Pointer to where to store the year value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine