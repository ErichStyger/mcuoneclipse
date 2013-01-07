%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetCharHeight)
%;**     Description :
%;**         returns the height (in pixels) of a font character.
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - character for which to calculate the width
%;**       * charHeight%ParcharHeight %>27 - Pointer to height of the
%;** %>29 character in pixels.
%;**       * totalHeight%PartotalHeight %>27 - Pointer to the total
%;** %>29 height of the character, including to the
%;** %>29 space below the character.
%;**       * font%Parfont %>27 - Pointer to font information
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine