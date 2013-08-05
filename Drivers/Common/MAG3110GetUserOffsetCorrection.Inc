%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetUserOffsetCorrection)
%;**     Description :
%;**         Returns the user offset correction values from the device
%include Common\GeneralParameters.inc(27)
%;**       * x%Parx %>27 - Pointer to where to store the x offset
%;**       * y%Pary %>27 - Pointer to where to store the y offset
%;**       * z%Parz %>27 - Pointer to where to store the z offset
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine