%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanTime)
%;**     Description :
%;**         Scans a time string in the format "hh:mm:ss,hh" with the
%;**         part for the ",hh" is optional.
%include Common\GeneralParameters.inc(27)
%;**         str%Parstr %>27 - Pointer to the string to be scanned. The
%;** %>29 function advances the pointer.
%;**       * hour%Parhour %>27 - Pointer to where to store the hour value
%;**       * minute%Parminute %>27 - Pointer to where to store the minute
%;** %>29 value
%;**       * second%Parsecond %>27 - Pointer to where to store the second
%;** %>29 value
%;**       * hSecond%ParhSecond %>27 - Pointer to scans the hundreds of
%;** %>29 second part. If not present in string, zero
%;** %>29 is stored
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine