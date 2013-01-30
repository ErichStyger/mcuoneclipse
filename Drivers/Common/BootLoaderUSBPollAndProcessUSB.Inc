%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PollAndProcessUSB)
%;**     Description :
%;**         Poll and process the USB packets. It returns and changes the
%;**         status through the argument.
%include Common\GeneralParameters.inc(27)
%;**       * fileStatus%ParfileStatus %>27 - Pointer to file status
%;** %>29 information
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine