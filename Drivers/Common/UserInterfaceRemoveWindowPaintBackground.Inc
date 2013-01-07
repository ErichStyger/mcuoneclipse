%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (RemoveWindowPaintBackground)
%;**     Description :
%;**         Removes a window from the screen and repaints the background
%;**         of it.
%include Common\GeneralParameters.inc(27)
%;**       * screen%Parscreen %>27 - Pointer to screen
%;**       * window%Parwindow %>27 - Pointer to window structure
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine