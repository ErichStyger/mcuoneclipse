%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteCommandData)
%;**     Description :
%;**         Sends multiple words to the display as commands + data
%;**         sequence
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Pointer to the data to write (nofWords
%;** %>29 of words)
%;**         nofWords%ParnofWords %>27 - number of words to send.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine