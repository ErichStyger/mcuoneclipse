%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CoordinateInsideElement)
%;**     Description :
%;**         check if a coordinate is inside element
%include Common\GeneralParameters.inc(27)
%;**       * coord%Parcoord %>27 - Pointer to global coordinate
%;**       * element%Parelement %>27 - Pointer to element
%;**     Returns     :
%;**         ---%RetVal %>27 - returns true if coordinate is inside the
%;** %>29 element
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine