%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PaintAllElements)
%;**     Description :
%;**         Sends a PAINT message to all elements in the tree
%include Common\GeneralParameters.inc(27)
%;**       * rootElement%ParrootElement %>27 - Pointer to the root element
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine