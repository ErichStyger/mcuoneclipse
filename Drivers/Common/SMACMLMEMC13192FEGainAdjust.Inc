%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MLMEMC13192FEGainAdjust)
%;**     Description :
%;**         Adjust the transceiver gain compensator
%include Common\GeneralParameters.inc(27)
%;**         u8GainValue%Paru8GainValue %>27 - Gain compensation value (0
%;** %>29 to 255. 128 is center point)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine