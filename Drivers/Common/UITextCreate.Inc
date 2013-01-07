%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Create)
%;**     Description :
%;**         Creates a text element
%include Common\GeneralParameters.inc(27)
%;**       * parent%Parparent %>27 - Pointer to parent element. If NULL,
%;** %>29 then the widget will not be added to the
%;** %>29 list of widgets.
%;**       * txtw%Partxtw %>27 - Pointer to text widget
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine