%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SelectNextElement)
%;**     Description :
%;**         Selects the next (or previous) element in the window
%include Common\GeneralParameters.inc(27)
%;**       * screen%Parscreen %>27 - Pointer to screen
%;**         forward%Parforward %>27 - if set to TRUE, selects the next
%;** %>29 element, otherwise selects the previous one.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine