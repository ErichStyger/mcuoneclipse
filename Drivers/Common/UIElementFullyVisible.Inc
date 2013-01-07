%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ElementFullyVisible)
%;**     Description :
%;**         Returns TRUE if element is fully visible (and not overlapped
%;**         by something else like another window)
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to element
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if element is fully visible, FALSE
%;** %>29 otherwise
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine