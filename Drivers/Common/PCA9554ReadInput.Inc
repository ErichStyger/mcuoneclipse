%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadInput)
%;**     Description :
%;**         Reads a byte from the input register.
%;**         This register is a read-only port. It reflects the incoming
%;**         logic levels of the pins, regardless
%;**         of whether the pin is defined as an input or an output by
%;**         Register 3. Writes to this register
%;**         have no effect. The default is determined by the externally
%;**         applied logic level, normally ‘1’ when no
%;**         external signal externally applied because of the internal
%;**         pull-up resistors.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - output port value
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine