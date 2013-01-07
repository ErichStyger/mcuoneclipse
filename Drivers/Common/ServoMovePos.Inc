%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MovePos)
%;**     Description :
%;**         Moves the servo to a given position
%include Common\GeneralParameters.inc(27)
%;**         pos%Parpos %>27 - position of the servo, from 0 to 255.
%;**         timeMs%PartimeMs %>27 - Time in ms for the movement
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine