%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (isWriteProtected)
%;**     Description :
%;**         Determines if the card is write protected. Note that this is
%;**         an indicator only, as it is still possible to write to the
%;**         card even if the write protection is set on the card!
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - True if the card has the write protection
%;** %>29 set, false otherwise
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine