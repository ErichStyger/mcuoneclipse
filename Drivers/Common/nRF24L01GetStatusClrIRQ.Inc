%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetStatusClrIRQ)
%;**     Description :
%;**         Returns the device status byte and clears any IRQ bits in
%;**         the status register.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - status byte
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine