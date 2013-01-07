%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadOutput)
%;**     Description :
%;**         Reads a byte from the output register.
%;**         This register reflects the outgoing logic levels of the pins
%;**         defined as outputs by Register 3.
%;**         Bit values in this register have no effect on pins defined
%;**         as inputs. Reads from this register
%;**         return the value that is in the flip-flop controlling the
%;**         output selection, not the actual pin
%;**         value.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - output port value
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine