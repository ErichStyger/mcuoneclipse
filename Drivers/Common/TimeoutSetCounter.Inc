%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetCounter)
%;**     Description :
%;**         Sets the counter to a new value and returns the value just
%;**         prior to the call.
%include Common\GeneralParameters.inc(27)
%;**         handle%Parhandle %>27 - Counter handle which shall get a new
%;** %>29 value.
%;**         nofTicks%ParnofTicks %>27 - New value (tick count) of the
%;** %>29 timeout counter. Pass zero to have it
%;** %>29 expire immediately.
%;**     Returns     :
%;**         ---%RetVal %>27 - Value of counter before reset.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine