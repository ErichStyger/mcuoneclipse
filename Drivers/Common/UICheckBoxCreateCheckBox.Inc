%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateCheckBox)
%;**     Description :
%;**         Creates a new CheckBox widget element
%include Common\GeneralParameters.inc(27)
%;**       * parent%Parparent %>27 - Pointer to parent element
%;**       * checkBox%ParcheckBox %>27 - Pointer to widget
%;**         x%Parx %>27 - x position of check box
%;**         y%Pary %>27 - y position of check box
%;**         width%Parwidth %>27 - width of element, including text
%;**         height%Parheight %>27 - height of the element
%;**         boxLineColor%ParboxLineColor %>27 - checkbox line color
%;**         boxBgColor%ParboxBgColor %>27 - checkbox background color
%;**       * text%Partext %>27 - Pointer to description text of checkbox
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine