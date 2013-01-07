%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Write)
%;**     Description :
%;**         Write from the device
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - device memory address
%;**       * buf%Parbuf %>27 - Pointer to read buffer
%;**         bufSize%ParbufSize %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine