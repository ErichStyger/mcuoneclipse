%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryMultipleUserIOPins)
%;**     Description :
%;**         Queries ultiple User I/O pins
%include Common\GeneralParameters.inc(27)
%;**       * mask%Parmask %>27 - Pointer to 12 Bit mask (0 for clear/low
%;** %>29 level, 1 for set/high level). Mapping to
%;** %>29 pins: 
%;** %>29 (x)(10)(x)(x)(7)(6)(5)(4)(3)(2)(x)(x) with
%;** %>29 (x) as 'don not care'.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine