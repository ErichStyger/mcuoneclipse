%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (RemoveWindow)
%;**     Description :
%;**         Removes a window from the screen.
%include Common\GeneralParameters.inc(27)
%;**       * screen%Parscreen %>27 - Pointer to screen
%;**       * window%Parwindow %>27 - Pointer to window structure
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine