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
%;**       * pWindow%ParpWindow %>27 - Pointer to window pointer. Returns
%;** %>29 here a pointer to the window of the
%;** %>29 selected item, or NULL.
%;**       * pElement%ParpElement %>27 - Pointer to element pointer.
%;** %>29 Returns here a pointer to the element of
%;** %>29 the selected item, or NULL.
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if there is a selected element. In
%;** %>29 this case the pointer to it is returned.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine