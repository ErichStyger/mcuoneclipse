%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateScrollMenu)
%;**     Description :
%;**         Creates a scroll menu widget
%include Common\GeneralParameters.inc(27)
%;**       * parent%Parparent %>27 - Pointer to parent element
%;**       * widget%Parwidget %>27 - Pointer to widget
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         menuText%ParmenuText %>27 - Menutext, item are separated by \
%;** %>29 \r
%;**         handler%Parhandler %>27 - optional user handler, NULL if not
%;** %>29 used
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine