%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateButton)
%;**     Description :
%;**         Creates a new button element
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to 
%;**       * button%Parbutton %>27 - Pointer to button element
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**       * text%Partext %>27 - Pointer to text
%;**       * font%Parfont %>27 - Pointer to font callbacks
%;**         btnColor%ParbtnColor %>27 - background color of button
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine