%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Hide)
%;**     Description :
%;**         Using this command, the content of the display can be made
%;**         hidden (either with a white or black screen). The content of
%;**         the display will not be lost.
%include Common\GeneralParameters.inc(27)
%;**         black%Parblack %>27 - if set to TRUE, then the display will
%;** %>29 be black, otherwise it will be white.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine