%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetSelectedElement)
%;**     Description :
%;**         Returns the currently selected element, or NULL.
%include Common\GeneralParameters.inc(27)
%;**       * screen%Parscreen %>27 - Pointer to current screen
%;**       * pElement%ParpElement %>27 - Pointer to element pointer used
%;** %>29 as output
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if there is a selected element. In
%;** %>29 this case the pointer to it is returned.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
