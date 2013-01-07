%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetMenuText)
%;**     Description :
%;**         Sets the menu text. Items in the menu are separated by \r.
%include Common\GeneralParameters.inc(27)
%;**       * widget%Parwidget %>27 - Pointer to widget
%;**         menuText%ParmenuText %>27 - Menutext with items separated by
%;** %>29 \\r.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine