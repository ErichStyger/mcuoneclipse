%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Create)
%;**     Description :
%;**         Creates a new header widget element
%include Common\GeneralParameters.inc(27)
%;**       * parent%Parparent %>27 - Pointer to parent element
%;**       * header%Parheader %>27 - Pointer to header
%;**         x%Parx %>27 - x coordinate
%;**         y%Pary %>27 - y coordinate
%;**         width%Parwidth %>27 - width of the widget, zero for auto size
%;**         height%Parheight %>27 - height of the header, zero for auto
%;** %>29 size
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine