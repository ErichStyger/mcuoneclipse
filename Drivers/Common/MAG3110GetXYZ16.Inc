%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetXYZ16)
%;**     Description :
%;**         Returns in an array the x, y and z sensor values as 16bit
%;**         values. Note that for this method the FAST_READ flag shall
%;**         not be set.
%include Common\GeneralParameters.inc(27)
%;**       * xyz%Parxyz %>27 - Pointer to an array of three signed 16bit
%;** %>29 values which are used to return the
%;** %>29 accelerometer values.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, ERR_OK for no error.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine