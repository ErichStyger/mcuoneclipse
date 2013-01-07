%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetThreshold)
%;**     Description :
%;**         Returns the threshold value (us) where the LED will see the
%;**         light. It returns 0 in case no light has been seen.
%include Common\GeneralParameters.inc(27)
%;**       * threshold%Parthreshold %>27 - Pointer to threshold
%;**     Returns     :
%;**         ---%RetVal %>27 - error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine