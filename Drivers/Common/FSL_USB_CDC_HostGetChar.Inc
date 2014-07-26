%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetChar)
%;**     Description :
%;**         Receives a character from the USB interface. Function is not
%;**         blocking if there is no character in the input buffer.
%include Common\GeneralParameters.inc(27)
%;**       * Chr%ParChr %>27 - Pointer to where to store the character
%;** %>29 received
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, ERR_OK for success,
%;** %>29 ERR_RXEMPTY if nothing is in RX buffer.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
