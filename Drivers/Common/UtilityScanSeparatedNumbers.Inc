%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanSeparatedNumbers)
%;**     Description :
%;**         Scans multiple numbers separated by character, e.g. "123.68.
%;**         5.3"
%include Common\GeneralParameters.inc(27)
%;**         str%Parstr %>27 - String to scan. It returns as well until
%;** %>29 where it has scanned
%;**       * values%Parvalues %>27 - Pointer to array where to store the
%;** %>29 values
%;**         nofValues%ParnofValues %>27 - Number of values in the array
%;**         separator%Parseparator %>27 - Character separator, e.g. '.'
%;**         numberType%ParnumberType %>27 - type of number to scan
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine