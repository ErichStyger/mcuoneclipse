%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (UpdateElementNoRefresh)
%;**     Description :
%;**         Paints an element to the window, with no explicit refresh
%include Common\GeneralParameters.inc(27)
%;**       * parent%Parparent %>27 - Pointer to element
%;**       * element%Parelement %>27 - Pointer to element
%;**         updateAll%ParupdateAll %>27 - if the element needs to be
%;** %>29 updated in any case.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine