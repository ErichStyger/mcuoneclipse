%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetCalibrationData)
%;**     Description :
%;**         Returns the calibration data (e.g. to the caller who will
%;**         store it on a permanent storage).
%include Common\GeneralParameters.inc(27)
%;**       * calibData%ParcalibData %>27 - Pointer to pointer to the
%;** %>29 calibration data
%;**         nofBytes%ParnofBytes %>27 - Number of bytes.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine