%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (AddDataLine)
%;**     Description :
%;**         Adds a new data line element to the graph
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to element widget
%;**       * prevDataP%ParprevDataP %>27 - Pointer to previous data point
%;** %>29 array, or NULL. Used to draw a line from
%;** %>29 the previous data point to the new data
%;** %>29 point.
%;**       * dataP%PardataP %>27 - Pointer to data point array
%;**         nofData%ParnofData %>27 - Number of data points. This
%;** %>29 specifies the number of data elements which
%;** %>29 are referenced by dataP parameter.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine