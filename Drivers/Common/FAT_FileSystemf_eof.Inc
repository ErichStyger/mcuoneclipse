%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (f_eof)
%;**     Description :
%;**         Wrapper to to the f_eof() macro. Returns 1 if at the end of
%;**         the file, 0 otherwise.
%include Common\GeneralParameters.inc(27)
%;**       * fp%Parfp %>27 - Pointer to file object
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine