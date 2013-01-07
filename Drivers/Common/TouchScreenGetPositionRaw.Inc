%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetPositionRaw)
%;**     Description :
%;**         Decides if the screen has been touched or not, and returns
%;**         the raw touch position
%include Common\GeneralParameters.inc(27)
%;**       * RawTouchPositionX%ParRawTouchPositionX %>27 - Pointer to
%;** %>29 position variable for X value
%;**       * RawTouchPositionY%ParRawTouchPositionY %>27 - Pointer to
%;** %>29 position variable for Y value
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if display has been touched, FALSE
%;** %>29 otherwise
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine