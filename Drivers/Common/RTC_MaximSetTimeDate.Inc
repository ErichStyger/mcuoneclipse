%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetTimeDate)
%;**     Description :
%;**         Sets the date and time.
%include Common\GeneralParameters.inc(27)
%;**       * time%Partime %>27 - Pointer to time to be set
%;**       * date%Pardate %>27 - Pointer to date to be set
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine