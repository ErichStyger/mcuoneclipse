%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetShiftClockPolarity)
%;**     Description :
%;**         Sets the shift clock polarity at runtime. Output data will
%;**         be shifted on the selected edge polarity.
%include Common\GeneralParameters.inc(27)
%;**         Edge%ParEdge %>27 - Edge polarity, possible values:
%;** %>29 0-falling edge,
%;** %>29 1-rising edge.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
