%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ChangeText)
%;**     Description :
%;**         Changes the text of the element. The method will erase the
%;**         existing text and replaces it with the new text, and copies
%;**         the new text into the existing buffer (that's why you need
%;**         to provide the size of the existing buffer as well).
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * elem%Parelem %>27 - Pointer to the element.
%;**         dstTextSize%PardstTextSize %>27 - Size in bytes of existing
%;** %>29 text.
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