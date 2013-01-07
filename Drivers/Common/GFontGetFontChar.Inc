%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetFontChar)
%;**     Description :
%;**         Returns for a given character the corresponding font bitmap.
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - The character for that a bitmap is required.
%;**     Returns     :
%;**         ---%RetVal %>27 - Character font bitmap
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine