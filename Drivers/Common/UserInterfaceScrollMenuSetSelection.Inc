%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScrollMenuSetSelection)
%;**     Description :
%;**         Sets the selected item in the scroll menu. The method does
%;**         an overflow/underflow check.
%include Common\GeneralParameters.inc(27)
%;**       * scrollMenu%ParscrollMenu %>27 - Pointer to scrollMenu
%;**         newSelection%ParnewSelection %>27 - index (starting with
%;** %>29 zero) of the selection
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine