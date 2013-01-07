%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (InitCommChannel)
%;**     Description :
%;**         Method to initialize communication to the LCD. Needed if the
%;**         bus to the LCD is shared with other components and settings
%;**         are different.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine