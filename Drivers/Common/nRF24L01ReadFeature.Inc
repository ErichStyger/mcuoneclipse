%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadFeature)
%;**     Description :
%;**         Reads the FEATURE register
%include Common\GeneralParameters.inc(27)
%;**       * featureMask%ParfeatureMask %>27 - Pointer to value of
%;** %>29 FEATURE register
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine