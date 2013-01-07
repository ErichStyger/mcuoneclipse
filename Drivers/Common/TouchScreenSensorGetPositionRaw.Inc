%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetPositionRaw)
%;**     Description :
%;**         Reads touch screen and returns raw uncompensated X, Y
%;**         coordinates if screen is touched.
%include Common\GeneralParameters.inc(27)
%;**       * TouchPositionX%ParTouchPositionX %>27 - Pointer to variable
%;** %>29 for x position
%;**       * TouchPositionY%ParTouchPositionY %>27 - Pointer to variable
%;** %>29 for y position
%;**     Returns     :
%;**         ---%RetVal %>27 - false if screen is not touched, true if
%;** %>29 screen is touched
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine