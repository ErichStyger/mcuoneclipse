%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (AssignText)
%;**     Description :
%;**         Changes the text of the element. The method will use the
%;**         pointer to the new text provided. The caller is responsible
%;**         to deallocate the previous text if necessary.
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * elem%Parelem %>27 - Pointer to the element.
%;**       * txt%Partxt %>27 - Pointer to new text. Note that this text
%;** %>29 has to be different from the element text
%;** %>29 shown, and this text will become the new
%;** %>29 element text.
%;**     Returns     :
%;**         ---%RetVal %>27 - error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine