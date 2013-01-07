%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (getUTIresults)
%;**     Description :
%;**         This method returns the result of the measurements.
%;**         This method needs a pointer to a word array with the length
%;**         of number of sensor elements (UTI-Mode dependent).
%;**         The unit of the results are UTI-mode dependent. Please check
%;**         the code comment of the calculation in the phasesToRorC
%;**         method.
%include Common\GeneralParameters.inc(27)
%;**       * pUtiResults%ParpUtiResults %>27 - Pointer to result of
%;** %>29 measured sensor elements from UTI
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine