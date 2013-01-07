%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (IsPresent)
%;**     Description :
%;**         Function checks if a DCF receiver is present. As the signal
%;**         is open drain with a pull-up, we can detect a receiver in
%;**         case we get a low signal. This function checks if there is a
%;**         receiver present for at most ~200 ms as a positive pulse may
%;**         last at least 200 ms.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine