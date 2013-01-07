%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateHeader)
%;**     Description :
%;**         Initializes the header for the window
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * header%Parheader %>27 - Pointer to header
%;**       * text%Partext %>27 - Pointer to text to display in header
%;**       * font%Parfont %>27 - Pointer to font callbacks
%;**         bgColor%ParbgColor %>27 - background color for header
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine