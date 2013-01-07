%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetTimeDate)
%;**     Description :
%;**         Returns the time and date from the device.
%include Common\GeneralParameters.inc(27)
%;**       * time%Partime %>27 - Pointer to time
%;**       * date%Pardate %>27 - Pointer to date
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine