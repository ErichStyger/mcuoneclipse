%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ConstantCarrierWave)
%;**     Description :
%;**         Put the transceiver into contant carrier wave output for
%;**         testing. The output power of a radio is a critical factor
%;**         for achieving wanted range. Output power is also the first
%;**         test
%include Common\GeneralParameters.inc(27)
%;**         turnOn%ParturnOn %>27 - Set to true to start constant
%;** %>29 carrier wave, false to stop it.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine