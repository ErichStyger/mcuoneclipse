%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PutVal)
%;**     Description :
%;**         Shifts a byte into the shift register
%include Common\GeneralParameters.inc(27)
%;**         Val%ParVal %>27 - byte value to be shifted in. The least
%;** %>29 significant bit will show up at pin QH, the
%;** %>29 most significant bit at pin QA. Note that
%;** %>29 the shift register output pins are
%;** %>29 changing/shifting during shift operation.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine