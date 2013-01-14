%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetMultipleUserIOPins)
%;**     Description :
%;**         Sets or clears multiple User I/O pins
%include Common\GeneralParameters.inc(27)
%;**         mask%Parmask %>27 - 12 Bit mask (0 for clear/low level, 1
%;** %>29 for set/high level). Mapping to pins: 
%;** %>29 (x)(10)(x)(x)(7)(6)(5)(4)(3)(2)(x)(x) with
%;** %>29 (x) as 'don not care'.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine