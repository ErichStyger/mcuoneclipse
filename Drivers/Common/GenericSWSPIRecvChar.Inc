%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (RecvChar)
%;**     Description :
%;**         If any data received, this method returns one character,
%;**         otherwise it returns an error code (it does not wait for
%;**         data).
%include Common\GeneralParameters.inc(27)
%;**       * Chr%ParChr %>27 - A pointer to the received character.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%;** %>29 ERR_RXEMPTY - No data in receiver
%;** %>29 ERR_OVERRUN - Overrun error is detected
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
