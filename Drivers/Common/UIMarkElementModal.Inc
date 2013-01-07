%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MarkElementModal)
%;**     Description :
%;**         Marks the element as modal. Call UnMarkElementModal() at the
%;**         end of the modal sequence.
%include Common\GeneralParameters.inc(27)
%;**       * element%Parelement %>27 - Pointer to element
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine