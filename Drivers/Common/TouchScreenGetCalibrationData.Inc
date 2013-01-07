%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetCalibrationData)
%;**     Description :
%;**         Returns the calibration data (e.g. to the caller who will
%;**         store it on a permanent storage).
%include Common\GeneralParameters.inc(27)
%;**       * calibData%ParcalibData %>27 - Pointer to pointer to the
%;** %>29 calibration data. Here the method returns
%;** %>29 the pointer to the data.
%;**       * nofBytes%ParnofBytes %>27 - Pointer to number of bytes. Here
%;** %>29 the method returns the size of the
%;** %>29 calibration data.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine