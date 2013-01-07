%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateCheckBox)
%;**     Description :
%;**         Creates a check box element
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * checkBox%ParcheckBox %>27 - Pointer to checkbox
%;**         x%Parx %>27 - x position of check box
%;**         y%Pary %>27 - y position of check box
%;**         width%Parwidth %>27 - width of the element, including text
%;**         height%Parheight %>27 - height of the element
%;**         boxLineColor%ParboxLineColor %>27 - checkbox line color
%;**         boxBgColor%ParboxBgColor %>27 - checkbox background color
%;**       * text%Partext %>27 - Pointer to description text of checkbox
%;**       * font%Parfont %>27 - Pointer to font information
%;**         txtBgColor%PartxtBgColor %>27 - text background color
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine