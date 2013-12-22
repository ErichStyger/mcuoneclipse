%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadReceivedPowerDetector)
%;**     Description :
%;**         Reads the RPD (Received Power Detector) register. 
%include Common\GeneralParameters.inc(27)
%;**       * rpd%Parrpd %>27 - Pointer to RPD bit. Bit is one for
%;** %>29 received power levels above -64 dBm, zero
%;** %>29 for less than -64 dBm.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine