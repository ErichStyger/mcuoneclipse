%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadMem)
%;**     Description :
%;**         Read from the display memory
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - display memory address
%;**     Returns     :
%;**         ---%RetVal %>27 - memory byte
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine