%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateScrollMenu)
%;**     Description :
%;**         Creates a new scroll menu item
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to 
%;**       * scrollMenu%ParscrollMenu %>27 - Pointer to scrollMenu element
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**       * text%Partext %>27 - Pointer to text
%;**       * font%Parfont %>27 - Pointer to font callbacks
%;**         bgColor%ParbgColor %>27 - background color of menu
%;**         lineColor%ParlineColor %>27 - Line color of menu
%;**         boxBgColor%ParboxBgColor %>27 - Color to be used to fill the
%;** %>29 box background
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine