%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (phasesToRorC)
%;**     Description :
%;**         This method calculates with the time of phases the values of
%;**         the sensor types, which are connected.
%include Common\GeneralParameters.inc(27)
%;**       * pCycle%ParpCycle %>27 - Pointer to a array with the phases
%;** %>29 of a cycle
%;**       * pUtiResults%ParpUtiResults %>27 - Pointer to a array to save
%;** %>29 the calculated values of the sensor
%;** %>29 elements.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine