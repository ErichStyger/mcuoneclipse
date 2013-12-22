%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteFeature)
%;**     Description :
%;**         Writes the FEATURE register
%include Common\GeneralParameters.inc(27)
%;**         featureMask%ParfeatureMask %>27 - Mask of FEATURE, e.g.
%;** %>29 FEATURE_EN_DPL
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine