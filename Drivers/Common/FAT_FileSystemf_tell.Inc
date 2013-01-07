%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (f_tell)
%;**     Description :
%;**         Wrapper to to the f_tell() macro. Returns the file
%;**         read/write pointer (0 on file open).
%include Common\GeneralParameters.inc(27)
%;**       * fp%Parfp %>27 - Pointer to file object
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine