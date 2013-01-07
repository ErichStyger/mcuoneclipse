%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ClickElement)
%;**     Description :
%;**         Method for clicking on an element in the window
%include Common\GeneralParameters.inc(27)
%;**       * screen%Parscreen %>27 - Pointer to screen
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * element%Parelement %>27 - Pointer to element
%;**         kind%Parkind %>27 - Event to be handled
%;**         data%Pardata %>27 - pointer to optional data, or NULL
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine