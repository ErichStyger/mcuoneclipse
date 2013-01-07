%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadByte)
%;**     Description :
%;**         Read from the device RAM
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - device memory address, with zero as the
%;** %>29 RAM start address
%;**       * buf%Parbuf %>27 - Pointer to read buffer
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine