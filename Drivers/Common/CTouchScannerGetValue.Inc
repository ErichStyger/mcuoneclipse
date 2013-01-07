%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetValue)
%;**     Description :
%;**         Returns the average value for the given electrode
%include Common\GeneralParameters.inc(27)
%;**       * value%Parvalue %>27 - Pointer to where to store the value
%;**         electrodeNr%ParelectrodeNr %>27 - button index (starting
%;** %>29 with zero)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine