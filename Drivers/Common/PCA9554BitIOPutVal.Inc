%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PutVal)
%;**     Description :
%;**         The specified output value is set. If the direction is
%;**         [output], it writes the value to the pin. (Method is
%;**         available only if the direction = _[output]_).
%include Common\GeneralParameters.inc(27)
%;**         Val%ParVal %>27 - Output value. Possible values:
%;** %>29 <false> - logical "0" (Low level)
%;** %>29 <true> - logical "1" (High level)
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine