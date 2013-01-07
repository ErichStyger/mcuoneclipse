%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (UpdateFull)
%;**     Description :
%;**         Updates the image on the display. This is needed in case the
%;**         display requires a periodic refresh. For display using
%;**         windowing, this function may be implemented as dummy stub,
%;**         as the display content already is written.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine