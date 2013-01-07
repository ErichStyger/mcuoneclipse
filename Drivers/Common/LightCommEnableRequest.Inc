%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (EnableRequest)
%;**     Description :
%;**         Call this method in order to build up a connection and to
%;**         send and receive data.
%include Common\GeneralParameters.inc(27)
%;**       * tx%Partx %>27 - Pointer to data to transmit (or NULL)
%;**       * rx%Parrx %>27 - Pointer to where to store receiving data.
%;**         nofAttempts%ParnofAttempts %>27 - Number of additional
%;** %>29 attempts to communicate. Pass 1 for just
%;** %>29 one attempt.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine