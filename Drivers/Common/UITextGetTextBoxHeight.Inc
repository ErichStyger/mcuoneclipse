%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetTextBoxHeight)
%;**     Description :
%;**         Returns the height of the text based on font information. As
%;**         the text might be multiline with \r, it will return the
%;**         total height, not only of one line.
%include Common\GeneralParameters.inc(27)
%;**       * widget%Parwidget %>27 - Pointer to widget
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine