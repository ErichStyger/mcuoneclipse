%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetPosition)
%;**     Description :
%;**         Decides if the screen has been touched or not, and returns
%;**         the touch position
%include Common\GeneralParameters.inc(27)
%;**       * TouchPositionX%ParTouchPositionX %>27 - Pointer to position
%;** %>29 variable for X coordinate
%;**       * TouchPositionY%ParTouchPositionY %>27 - Pointer to position
%;** %>29 variable for Y coordinate
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if display has been touched, FALSE
%;** %>29 otherwise
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine