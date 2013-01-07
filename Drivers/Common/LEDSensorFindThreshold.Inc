%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (FindThreshold)
%;**     Description :
%;**         Returns the threshold value (us) when the LED will see the
%;**         light. It returns ERR_OK if we were able to determine a
%;**         threshold.
%;**         If you call this method with an ambient light environment,
%;**         it gives you a threshold (or a discharge time in us) at
%;**         which the sensor will sense the light. Use a value smaller
%;**         than this threshold to set the bean threshold value to
%;**         correctly recognize an incomming light.
%include Common\GeneralParameters.inc(27)
%;**       * threshold%Parthreshold %>27 - Pointer to threshold
%;**     Returns     :
%;**         ---%RetVal %>27 - error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
