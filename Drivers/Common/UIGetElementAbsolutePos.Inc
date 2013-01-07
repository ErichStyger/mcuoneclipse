%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetElementAbsolutePos)
%;**     Description :
%;**         Returns in x and y the absolute screen position of the
%;**         element.
%include Common\GeneralParameters.inc(27)
%;**       * elem%Parelem %>27 - Pointer to element
%;**       * xp%Parxp %>27 - pointer to x position
%;**       * yp%Paryp %>27 - Pointer to y position
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine