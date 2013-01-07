%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetCharWidth)
%;**     Description :
%;**         returns the width (in pixels) of a font character.
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - character for which to calculate the width
%;**       * charWidth%ParcharWidth %>27 - Pointer to width of the
%;** %>29 character in pixels (this is only for the
%;** %>29 character, without the space after the
%;** %>29 character)
%;**       * totalWidth%PartotalWidth %>27 - Pointer to the total width
%;** %>29 of the character, including to the space
%;** %>29 after the character.
%;**       * font%Parfont %>27 - Pointer to font information
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine