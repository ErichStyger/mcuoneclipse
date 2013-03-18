%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetCounter)
%;**     Description :
%;**         Initializes a new timeout counter and returns the handle to
%;**         it. At the end, use LeaveCounter() to free up the resource.
%include Common\GeneralParameters.inc(27)
%;**         nofTicks%ParnofTicks %>27 - Number of ticks for the counter
%;** %>29 until it expires.
%;**     Returns     :
%;**         ---%RetVal %>27 - Handle to the counter, to be used for
%;** %>29 further API calls.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine