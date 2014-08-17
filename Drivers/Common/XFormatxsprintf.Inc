%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xsprintf)
%;**     Description :
%;**         sprintf() like function
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - Pointer to buffer to be written
%;**       * fmt%Parfmt %>27 - Pointer to formatting string
%;**         argList%ParargList %>27 - Open Argument List
%;**     Returns     :
%;**         ---%RetVal %>27 - number of characters written, negative for
%;** %>29 error case
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine