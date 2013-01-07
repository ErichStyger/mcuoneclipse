%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetFontHeight)
%;**     Description :
%;**         returns the height (in pixels) of a font.
%include Common\GeneralParameters.inc(27)
%;**       * font%Parfont %>27 - Pointer to font information
%;**       * charHeight%ParcharHeight %>27 - Pointer to height of the
%;** %>29 character in pixels.
%;**       * totalHeight%PartotalHeight %>27 - Pointer to the total
%;** %>29 height of the character, including to the
%;** %>29 space below the character.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine