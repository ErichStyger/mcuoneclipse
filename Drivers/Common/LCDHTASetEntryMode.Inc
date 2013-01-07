%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetEntryMode)
%;**     Description :
%;**         Configures the display entry mode, if the cursor has to
%;**         shift and/or if the display shall shift content while
%;**         displaying text.
%include Common\GeneralParameters.inc(27)
%;**         increment%Parincrement %>27 - Increments (TRUE) or
%;** %>29 decrements (FALSE) the display address by 1
%;** %>29 when a character code is written into or
%;** %>29 read from DDRAM. The cursor or blinking
%;** %>29 moves to the right when incremented by 1
%;** %>29 and to the left when decremented by 1.
%;**         shiftLeft%ParshiftLeft %>27 - The display does not shift if
%;** %>29 the 'shift' is FALSE. If 'shift' is TRUE,
%;** %>29 it will seem as if the cursor does not move
%;** %>29 but the display does.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine