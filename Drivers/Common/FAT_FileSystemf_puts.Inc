%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (f_puts)
%;**     Description :
%;**         Put a string to the file
%include Common\GeneralParameters.inc(27)
%;**       * buff%Parbuff %>27 - A character to be output
%;**         fil%Parfil %>27 - Pointer to the file object
%;**     Returns     :
%;**         ---%RetVal %>27 - number of characters written.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine