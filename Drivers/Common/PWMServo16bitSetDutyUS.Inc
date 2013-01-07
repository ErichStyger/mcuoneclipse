%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetDutyUS)
%;**     Description :
%;**         This method sets the new duty value of the output signal.
%;**         The duty is expressed in microseconds as a 16-bit unsigned
%;**         integer number.
%include Common\GeneralParameters.inc(27)
%;**         Time%ParTime %>27 - new duty cycle in micro seconds
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine