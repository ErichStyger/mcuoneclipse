%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PtRtoTemperatur)
%;**     Description :
%;**         This method converts a Pt100 resistor value in a temperature
%;**         value.
%;**         The temperature range is from -25 degree celsius to 100
%;**         degree celsius.
%include Common\GeneralParameters.inc(27)
%;**         rx%Parrx %>27 - A Pt100 value with unit centi ohm or a
%;** %>29 Pt1000 value with unit deci ohm
%;**     Returns     :
%;**         ---%RetVal %>27 - A temperature with unit deci degree
%;** %>29 celsius.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine