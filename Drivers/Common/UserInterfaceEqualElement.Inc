%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (EqualElement)
%;**     Description :
%;**         Macro to compare two element pointers
%include Common\GeneralParameters.inc(27)
%;**       * elem1%Parelem1 %>27 - Pointer to element
%;**       * elem2%Parelem2 %>27 - Pointer to element which is a derived
%;** %>29 element (Icon, Header, etc).
%;**     Returns     :
%;**         ---%RetVal %>27 - if two elements are the same
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine